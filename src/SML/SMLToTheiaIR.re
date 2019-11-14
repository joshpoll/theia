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
  | RECORD(None) => Atom(React.string("{}"))
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
  | RAISE(e) => Apply2([React.string("raise "), <> </>], [compileExp(e)])
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
  | WILDCARD => Atom(React.string("_"))
  | ID(x) => Atom(React.string(x))
  | RECORD(None) => Atom(React.string("{}"))
  | RECORD(Some(pr)) => Apply2([React.string("{"), React.string("}")], [compilePatRow(pr)])
  | PAR(p) => Apply2([React.string("("), React.string(")")], [compilePat(p)])
  }
/* and compileExpRow = (EXPROW(lab, exp, rest)) =>
   switch (rest) {
   | None =>
     Apply2([<> </>, React.string("="), <> </>], [Atom(React.string(lab)), compileExp(exp)])
   | Some(er) =>
     Apply2(
       [<> </>, React.string("="), React.string(", "), <> </>],
       [Atom(React.string(lab)), compileExp(exp), compileExpRow(er)],
     )
   } */
and compilePatRow = pr =>
  switch (pr) {
  | DOTS => Atom(React.string("..."))
  | FIELD(l, p, None) =>
    Apply2([<> </>, React.string("="), <> </>], [Atom(React.string(l)), compilePat(p)])
  | FIELD(l, p, Some(pr)) =>
    Apply2(
      [<> </>, React.string("="), React.string(", "), <> </>],
      [Atom(React.string(l)), compilePat(p), compilePatRow(pr)],
    )
  }

and compilePat = p =>
  switch (p) {
  | ATPAT(a) => compileAtPat(a)
  | CON(x, ap) =>
    Apply2([<> </>, React.string(" "), <> </>], [Atom(React.string(x)), compileAtPat(ap)])
  };

let compileSVal = (sv: sVal) =>
  switch (sv) {
  | INT(n) => Value2([], [Atom(React.string(string_of_int(n)))])
  };

let compileIdStatus = id =>
  switch (id) {
  | Var => Atom(React.string("Var"))
  | Con => Atom(React.string("Con"))
  | Exc => Atom(React.string("Exc"))
  };

let rec compileVal_ = v =>
  switch (v) {
  | SVAL(sv) => compileSVal(sv)
  | BASVAL(b) =>
    Value2([], [Apply2([React.string("builtin "), <> </>], [Atom(React.string(b))])])
  | VID(x) => Value2([], [Atom(React.string(x))])
  | VIDVAL(vid, v) => Value2([vid], [compileVal_(v)])
  | RECORD([]) => Value2([], [Atom(React.string("{}"))])
  | RECORD(r) =>
    Value2([], [Apply2([React.string("{"), React.string("}")], [compileRecord(r)])])
  | FCNCLOSURE(m, e, ve) =>
    Value2(["closure"], [compileMatch(m), compileEnv(e), compileEnv(ve)])
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

and compileRecordEnv = rve =>
  switch (rve) {
  | [] => Atom(<> </>)
  | [(l, ve)] =>
    Apply2([<> </>, React.string("="), <> </>], [Atom(React.string(l)), compileEnv(ve)])
  | [(l, ve), ...rve] =>
    Apply2(
      [<> </>, React.string("="), React.string(", "), <> </>],
      [Atom(React.string(l)), compileEnv(ve), compileRecordEnv(rve)],
    )
  }

and compileKVs = ((k, (v, id))) =>
  KV2((
    Atom(React.string(k)),
    Apply2([<> </>, React.string(" "), <> </>], [compileVal_(v), compileIdStatus(id)]),
  ))

and compileEnv = e =>
  e |> List.map(compileKVs) |> List.rev |> (x => Map2(x, Some("Id"), Some("Val")));

let rec compileStrDec = sd =>
  switch (sd) {
  | DEC(d) => compileDec(d)
  | SEQ(sd1, sd2) =>
    Apply2(
      [<> </>, <> {React.string(";")} <br /> <br /> </>, <> </>],
      [compileStrDec(sd1), compileStrDec(sd2)],
    )
  };

let rec compileTopDec = td =>
  switch (td) {
  | STRDEC(sd, None) => compileStrDec(sd)
  | STRDEC(sd, Some(td)) =>
    Apply2([<> </>, <> <br /> <br /> </>, <> </>], [compileStrDec(sd), compileTopDec(td)])
  };

let rec compileProgram = p =>
  switch (p) {
  | PROGRAM(td, None) => compileTopDec(td)
  | PROGRAM(td, Some(p)) =>
    Apply2(
      [<> </>, <> {React.string(";")} <br /> <br /> </>, <> </>],
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
  | Match(m, v) => HSequence([compileVal_(v), compileMatch(m)], None)
  | MRule(mr, v) => HSequence([compileVal_(v), compileMRule(mr)], None)
  | Pat(p, v) => HSequence([compileVal_(v), compilePat(p)], None)
  | AtPat(ap, v) => HSequence([compileVal_(v), compileAtPat(ap)], None)
  /* TODO: improve this */
  | PatRow(pr, r, rve) =>
    VSequence([compileRecordEnv(rve), compilePatRow(pr), compileRecord(r)], None)
  | FAIL(v) => HSequence([Atom(React.string("FAIL")), compileVal_(v)], None)
  | ValEnv(ve) => compileEnv(ve)
  | Empty => Atom(Util.nbsp)
  };

let compileCtxt = c =>
  switch (c) {
  | LETD((), e) => {
      ops: [React.string("let "), React.string(" in "), React.string(" end")],
      args: [compileExp(e)],
      holePos: 0,
    }
  | VALBINDE(p, (), None) => {
      ops: [<> </>, React.string(" = "), <> </>],
      args: [compilePat(p)],
      holePos: 1,
    }
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
      ops: [<> </>, <> {React.string(";")} <br /> <br /> </>, <> </>],
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
      ops: [<> </>, <> {React.string(";")} <br /> <br /> </>, <> </>],
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
  | RECVB () => {ops: [React.string("rec "), <> </>], args: [], holePos: 0}
  | RECORDPR () => {ops: [React.string("{"), React.string("}")], args: [], holePos: 0}
  | STRDECSD((), None) => {ops: [<> </>, <> </>], args: [], holePos: 0}
  | STRDECSD((), Some(td)) => {
      ops: [<> </>, <> <br /> <br /> </>, <> </>],
      args: [compileTopDec(td)],
      holePos: 0,
    }
  /* TODO: this printing could probably be better */
  | FIELDP((l, (), None), r, rve) => {
      ops: [<> </>, <> </>, React.string("="), <br />, <> </>],
      args: [compileRecordEnv(rve), Atom(React.string(l)), compileRecord(r)],
      holePos: 2,
    }
  | FIELDP((l, (), Some(pr)), r, rve) => {
      ops: [<> </>, <> </>, React.string("="), React.string(", "), <br />, <> </>],
      args: [
        compileRecordEnv(rve),
        Atom(React.string(l)),
        compilePatRow(pr),
        compileRecord(r),
      ],
      holePos: 2,
    }
  };

let compileRewrite = ({focus, ctxts}) =>
  Kont2(compileFocus(focus), List.map(compileCtxt, ctxts));

let compileFrame = ({rewrite, env}) =>
  Cell2(
    "frame",
    [Cell2("env", [compileEnv(env)]), Cell2("rewrite", [compileRewrite(rewrite)])],
  );

/* TODO: HSequence? */
let smlToTheiaIR = fs => VSequence(List.map(compileFrame, fs) |> List.rev, None);