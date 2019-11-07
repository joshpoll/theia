/* Parse and compile HaMLet SML ASTs to SML AM ASTs */
type sourceMap = {
  file: string,
  line1: int,
  col1: int,
  line2: int,
  col2: int,
};

type ast =
  | INTSCon(int)
  | SCONAtExp(sourceMap, ast)
  | ATExp(sourceMap, ast)
  | LongVId(string)
  | IDAtPat(sourceMap, ast)
  | ATPat(sourceMap, ast)
  | PLAINValBind(sourceMap, (ast, ast, option(ast)))
  | Seq(sourceMap)
  | VALDec(sourceMap, (ast, ast))
  | DECStrDec(sourceMap, ast)
  | STRDECTopDec(sourceMap, (ast, option(ast)))
  | Program(sourceMap, (ast, option(ast)))
  | LETAtExp(sourceMap, (ast, ast))
  | IDAtExp(sourceMap, ast)
  | APPExp(sourceMap, (ast, ast))
  | PARAtExp(sourceMap, ast);

module Decode = {
  open Json.Decode;

  let sourceMap = json => {
    {
      file: json |> field("file", string),
      line1: json |> field("line1", int),
      col1: json |> field("col1", int),
      line2: json |> field("line2", int),
      col2: json |> field("col2", int),
    };
  };

  let rec intscon = json => INTSCon(json |> field("args", list(int)) |> List.hd)

  and scontatexp = json =>
    SCONAtExp(
      json |> field("sourceMap", sourceMap),
      json |> field("args", list(node)) |> List.hd,
    )

  and atexp = json =>
    ATExp(json |> field("sourceMap", sourceMap), json |> field("args", list(node)) |> List.hd)

  and longvid = json => LongVId(json |> field("args", list(string)) |> List.hd)

  and idatpat = json =>
    IDAtPat(
      json |> field("sourceMap", sourceMap),
      json |> field("args", list(node)) |> List.hd,
    )

  and atpat = json =>
    ATPat(json |> field("sourceMap", sourceMap), json |> field("args", list(node)) |> List.hd)

  and plainvalbind = json =>
    PLAINValBind(
      json |> field("sourceMap", sourceMap),
      /* TOOD: assumes last argument is null always */
      json |> field("args", tuple3(node, node, nullAs(None))),
    )

  and seq = json => Seq(json |> field("sourceMap", sourceMap))

  and valdec = json =>
    VALDec(json |> field("sourceMap", sourceMap), json |> field("args", tuple2(node, node)))

  and decstrdec = json =>
    DECStrDec(
      json |> field("sourceMap", sourceMap),
      json |> field("args", list(node)) |> List.hd,
    )

  and strdectopdec = json =>
    STRDECTopDec(
      json |> field("sourceMap", sourceMap),
      json |> field("args", pair(node, nullAs(None))),
    )

  and program = json =>
    Program(
      json |> field("sourceMap", sourceMap),
      json |> field("args", pair(node, nullAs(None))),
    )

  and letatexp = json =>
    LETAtExp(json |> field("sourceMap", sourceMap), json |> field("args", pair(node, node)))

  and idatexp = json =>
    IDAtExp(
      json |> field("sourceMap", sourceMap),
      json |> field("args", list(node)) |> List.hd,
    )

  and appexp = json =>
    APPExp(json |> field("sourceMap", sourceMap), json |> field("args", tuple2(node, node)))

  and paratexp = json =>
    PARAtExp(
      json |> field("sourceMap", sourceMap),
      json |> field("args", list(node)) |> List.hd,
    )

  and node = json => {
    (
      field("node", string)
      |> andThen(s =>
           switch (s) {
           | "INTSCon" => intscon
           | "SCONAtExp" => scontatexp
           | "ATExp" => atexp
           | "LongVId" => longvid
           | "IDAtPat" => idatpat
           | "ATPat" => atpat
           | "PLAINValBind" => plainvalbind
           | "Seq" => seq
           | "VALDec" => valdec
           | "DECStrDec" => decstrdec
           | "STRDECTopDec" => strdectopdec
           | "Program" => program
           | "LETAtExp" => letatexp
           | "IDAtExp" => idatexp
           | "APPExp" => appexp
           | "PARAtExp" => paratexp
           | _ => failwith("Unknown node type: " ++ s)
           }
         )
    )(
      json,
    );
  };
};

let rec compileProgram = p =>
  switch (p) {
  | Program(_, (td, None)) => SML.{topDec: compileTopDec(td), rest: None}
  | Program(_, (td, Some(p))) =>
    SML.{topDec: compileTopDec(td), rest: Some(compileProgram(p))}
  }

and compileTopDec = td =>
  switch (td) {
  | STRDECTopDec(_, (sd, None)) => SML.STRDEC(compileStrDec(sd), None)
  | STRDECTopDec(_, (sd, Some(td))) => SML.STRDEC(compileStrDec(sd), Some(compileTopDec(td)))
  }

and compileStrDec = sd =>
  switch (sd) {
  | DECStrDec(_, d) => SML.DEC(compileDec(d))
  }

and compileDec = d =>
  switch (d) {
  | VALDec(_, (_, vb)) => SML.VAL(compileValBind(vb))
  }

and compileValBind = vb =>
  switch (vb) {
  | PLAINValBind(_, (p, e, None)) => SML.PLAIN(compilePat(p), compileExp(e), None)
  | PLAINValBind(_, (p, e, Some(vb))) =>
    SML.PLAIN(compilePat(p), compileExp(e), Some(compileValBind(vb)))
  }

and compilePat = p =>
  switch (p) {
  | ATPat(_, ap) => SML.ATPAT(compileAtPat(ap))
  }

and compileAtPat = ap =>
  switch (ap) {
  | IDAtPat(_, x) => SML.ID(compileLongVId(x))
  }

and compileLongVId = x =>
  switch (x) {
  | LongVId(x) => x
  }

and compileExp = e =>
  switch (e) {
  | ATExp(_, a) => SML.ATEXP(compileAtExp(a))
  | APPExp(_, (e, a)) => SML.APP(compileExp(e), compileAtExp(a))
  }

and compileAtExp = a =>
  switch (a) {
  | SCONAtExp(_, sc) => SML.SCON(compileSCon(sc))
  | LETAtExp(_, (d, e)) => SML.LET(compileDec(d), compileExp(e))
  | IDAtExp(_, x) => SML.ID(compileLongVId(x))
  | PARAtExp(_, e) => SML.PAR(compileExp(e))
  }

and compileSCon = sc =>
  switch (sc) {
  | INTSCon(n) => SML.INT(n)
  };