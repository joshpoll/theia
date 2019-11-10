/* Compiler from SML configuration to TheiaIR */
/* TODO: so many List.revs. Maybe I should change the default? */
open SML;
open Theia;

let compileSCon = (sc: sCon) =>
  switch (sc) {
  | INT(n) => Atom(React.string(string_of_int(n)))
  };

let rec compileAtExp = a =>
  switch (a) {
  | SCON(sc) => compileSCon(sc)
  | ID(x) => Atom(React.string(x))
  | RECORD(None) => Atom(React.string("()"))
  | RECORD(Some(er)) => Apply2([React.string("{"), React.string("}")], [compileExpRow(er)])
  | LET(d, e) =>
    Apply2(
      [React.string("let "), React.string(" in "), React.string(" end")],
      [compileDec(d), compileExp(e)],
    )
  | PAR(e) => Apply2([React.string("("), React.string(")")], [compileExp(e)])
  }

and compileExpRow = (EXPROW(lab, exp, rest)) =>
  switch (rest) {
  | None =>
    Apply2([<> </>, React.string("="), <> </>], [Atom(React.string(lab)), compileExp(exp)])
  | Some(er) =>
    Apply2(
      [<> </>, React.string("="), React.string(", "), <> </>],
      [Atom(React.string(lab)), compileExp(exp), compileExpRow(er)],
    )
  }

and compileExp = e =>
  switch (e) {
  | ATEXP(a) => compileAtExp(a)
  | APP(f, x) =>
    Apply2([<> </>, React.string(" "), <> </>], [compileExp(f), compileAtExp(x)])
  | FN(m) => Apply2([React.string("fn "), <> </>], [compileMatch(m)])
  }

and compileMatch = m =>
  switch (m) {
  | MATCH(mr, None) => compileMRule(mr)
  | MATCH(mr, Some(m)) =>
    Apply2(
      [<> </>, <> <br /> {React.string("| ")} </>, <> </>],
      [compileMRule(mr), compileMatch(m)],
    )
  }

and compileMRule = mr =>
  switch (mr) {
  | MRULE(p, e) =>
    Apply2([<> </>, React.string(" => "), <> </>], [compilePat(p), compileExp(e)])
  }

and compileDec = d =>
  switch (d) {
  | VAL(vb) => Apply2([React.string("val "), <> </>], [compileValBind(vb)])
  }

and compileValBind = vb =>
  switch (vb) {
  | PLAIN(p, e, None) =>
    Apply2([<> </>, React.string(" = "), <> </>], [compilePat(p), compileExp(e)])
  | REC(vb) => Apply2([React.string("rec "), <> </>], [compileValBind(vb)])
  }

and compileAtPat = a =>
  switch (a) {
  | ID(x) => Atom(React.string(x))
  | PAR(p) => Apply2([React.string("("), React.string(")")], [compilePat(p)])
  }

and compilePat = p =>
  switch (p) {
  | ATPAT(a) => compileAtPat(a)
  };

let compileSVal = (sv: sVal) =>
  switch (sv) {
  | INT(n) => Value2([], [Atom(React.string(string_of_int(n)))])
  };

let rec compileVal_ = v =>
  switch (v) {
  | SVAL(sv) => compileSVal(sv)
  | BASVAL(b) =>
    Value2([], [Apply2([React.string("builtin "), <> </>], [Atom(React.string(b))])])
  | VID(x) => Value2([], [Atom(React.string(x))])
  | RECORD([]) => Value2([], [Atom(React.string("()"))])
  | RECORD(r) =>
    Value2([], [Apply2([React.string("{"), React.string("}")], [compileRecord(r)])])
  | FCNCLOSURE(m, e, ve) =>
    Value2(["closure"], [compileMatch(m), compileEnv(e), compileOneEnv(ve)])
  }

and compileRecord = r =>
  switch (r) {
  | [] => Atom(<> </>)
  | [(l, v)] =>
    Apply2([<> </>, React.string("="), <> </>], [Atom(React.string(l)), compileVal_(v)])
  | [(l, v), ...r] =>
    Apply2(
      [<> </>, React.string("="), React.string(", "), <> </>],
      [Atom(React.string(l)), compileVal_(v), compileRecord(r)],
    )
  }

and compileKVs = ((k, v)) => KV2((Atom(React.string(k)), compileVal_(v)))

and compileOneEnv = e => e |> List.map(compileKVs) |> List.rev |> (x => Map2(x))

and compileEnv = e => VSequence(List.map(compileOneEnv, e) |> List.rev);

let rec compileStrDec = sd =>
  switch (sd) {
  | DEC(d) => compileDec(d)
  | SEQ(sd1, sd2) =>
    Apply2(
      [<> </>, <> {React.string(";")} <br /> </>, <> </>],
      [compileStrDec(sd1), compileStrDec(sd2)],
    )
  };

let compileTopDec = td =>
  switch (td) {
  | STRDEC(sd, None) => compileStrDec(sd)
  };

let rec compileProgram = p =>
  switch (p) {
  | PROGRAM(td, None) => compileTopDec(td)
  | PROGRAM(td, Some(p)) =>
    Apply2(
      [<> </>, <> {React.string(";")} <br /> </>, <> </>],
      [compileTopDec(td), compileProgram(p)],
    )
  };

let compileFocus = f =>
  switch (f) {
  | AtExp(a) => compileAtExp(a)
  | Exp(e) => compileExp(e)
  | Val(v) => compileVal_(v)
  | Dec(d) => compileDec(d)
  | ValBind(vb) => compileValBind(vb)
  | StrDec(sd) => compileStrDec(sd)
  | TopDec(td) => compileTopDec(td)
  | ExpRow(er) => compileExpRow(er)
  | Record(r) => compileRecord(r)
  | Program(p) => compileProgram(p)
  /* TODO: should use HSequence but layout is way too buggy */
  | Match(m, v) => VSequence([compileMatch(m), compileVal_(v)])
  | MRule(mr, v) => VSequence([compileMRule(mr), compileVal_(v)])
  | Pat(p, v) => VSequence([compilePat(p), compileVal_(v)])
  | AtPat(ap, v) => VSequence([compileAtPat(ap), compileVal_(v)])
  | FAIL(_) => Atom(React.string("FAIL"))
  | ValEnv(ve) => compileOneEnv(ve)
  /* TODO: visualize this better. should have a highlighting blank space or something */
  | Empty => Atom(React.string("EMPTY"))
  };

let compileCtxt = c =>
  switch (c) {
  | LETD((), e) => {
      ops: [React.string("let "), React.string(" in "), React.string(" end")],
      args: [compileExp(e)],
      holePos: 0,
    }
  | LETE((), ()) => {
      ops: [React.string("let in "), React.string(" end")],
      args: [],
      holePos: 0,
    }
  | VALBINDE(p, (), None) => {
      ops: [<> </>, React.string(" = "), <> </>],
      args: [compilePat(p)],
      holePos: 1,
    }
  | VALBINDE(_) => failwith("TODO")
  | APPL((), x) => {
      ops: [<> </>, React.string(" "), <> </>],
      args: [compileAtExp(x)],
      holePos: 0,
    }
  | APPR(f, ()) => {
      ops: [<> </>, React.string(" "), <> </>],
      args: [compileVal_(f)],
      holePos: 1,
    }
  | SEQL((), sd2) => {
      ops: [<> </>, <> {React.string(";")} <br /> </>, <> </>],
      args: [compileStrDec(sd2)],
      holePos: 0,
    }
  | DECD () => {ops: [<> </>, <> </>], args: [], holePos: 0}
  | RECORDER () => {ops: [React.string("{"), React.string("}")], args: [], holePos: 0}
  | EXPROWE([], l, (), None) => {
      ops: [<> </>, React.string("="), <> </>],
      args: [Atom(React.string(l))],
      holePos: 1,
    }
  | EXPROWE(r, l, (), None) => {
      ops: [<> </>, React.string(", "), React.string("="), <> </>],
      args: [compileRecord(r), Atom(React.string(l))],
      holePos: 2,
    }
  | EXPROWE([], l, (), Some(er)) => {
      ops: [<> </>, React.string("="), React.string(", "), <> </>],
      args: [Atom(React.string(l)), compileExpRow(er)],
      holePos: 1,
    }
  | EXPROWE(r, l, (), Some(er)) => {
      ops: [<> </>, React.string(", "), React.string("="), React.string(", "), <> </>],
      args: [compileRecord(r), Atom(React.string(l)), compileExpRow(er)],
      holePos: 2,
    }
  | PROGRAML((), p) => {
      ops: [<> </>, <> {React.string(";")} <br /> </>, <> </>],
      args: [compileProgram(p)],
      holePos: 0,
    }
  | MATCHMR((), None) => {ops: [<> </>, <> </>], args: [], holePos: 0}
  | MATCHMR((), Some(m)) => {
      ops: [<> </>, <> <br /> {React.string("| ")} </>, <> </>],
      args: [compileMatch(m)],
      holePos: 0,
    }
  | MRULEP((), e) => {
      ops: [<> </>, React.string(" => "), <> </>],
      args: [compileExp(e)],
      holePos: 0,
    }
  | MRULEE((), ()) => {ops: [React.string(" => "), <> </>], args: [], holePos: 0}
  | RECVB () => {ops: [React.string("rec "), <> </>], args: [], holePos: 0}
  };

let compileRewrite = ({focus, ctxts}) =>
  Kont2(compileFocus(focus), List.map(compileCtxt, ctxts));

let compileFrame = ({rewrite, env}) =>
  VSequence([Cell2("env", [compileEnv(env)]), Cell2("rewrite", [compileRewrite(rewrite)])]);

/* TODO: HSequence? */
let smlToTheiaIR = fs => VSequence(List.map(compileFrame, fs) |> List.rev);