/* Compiler from SML configuration to TheiaIR */
/* TODO: so many List.revs. Maybe I should change the default? */
open SML;
open TheiaAM;

let theiaStr = str => {id: str, theiaAMADT: Atom(React.string(str))};
let empty = {id: "", theiaAMADT: Atom(<> </>)};

let compileSCon = (sc: sCon) =>
  switch (sc) {
  | INT(n) => {id: "INT", theiaAMADT: Atom(React.string(string_of_int(n)))}
  };

let rec compileAtExp = a =>
  switch (a) {
  | SCON(sc) => compileSCon(sc)
  | ID(x) => {id: "ID", theiaAMADT: Atom(React.string(x))}
  | RECORD(None) => {id: "RECORD", theiaAMADT: Atom(React.string("{}"))}
  | RECORD(Some(er)) => {
      id: "RECORD",
      theiaAMADT: Apply([theiaStr("{"), theiaStr("}")], [compileExpRow(er)]),
    }
  | LET(d, e) => {
      id: "LET",
      theiaAMADT:
        Apply(
          [theiaStr("let "), theiaStr(" in "), theiaStr(" end")],
          [compileDec(d), compileExp(e)],
        ),
    }
  | PAR(e) => {
      id: "PAR",
      theiaAMADT: Apply([theiaStr("("), theiaStr(")")], [compileExp(e)]),
    }
  }

and compileExpRow = (EXPROW(lab, exp, rest)) =>
  switch (rest) {
  | None => {
      id: "EXPROW",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), empty],
          [{id: "lab", theiaAMADT: Atom(React.string(lab))}, compileExp(exp)],
        ),
    }
  | Some(er) => {
      id: "EXPROW",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), theiaStr(", "), empty],
          [
            {id: "lab", theiaAMADT: Atom(React.string(lab))},
            compileExp(exp),
            compileExpRow(er),
          ],
        ),
    }
  }

and compileExp = e =>
  switch (e) {
  | ATEXP(a) => compileAtExp(a)
  | APP(f, x) => {
      id: "APP",
      theiaAMADT: Apply([empty, theiaStr(" "), empty], [compileExp(f), compileAtExp(x)]),
    }
  | RAISE(e) => {
      id: "RAISE:",
      theiaAMADT: Apply([theiaStr("raise "), empty], [compileExp(e)]),
    }
  | FN(m) => {id: "FN", theiaAMADT: Apply([theiaStr("fn "), empty], [compileMatch(m)])}
  }

and compileMatch = m =>
  switch (m) {
  | MATCH(mr, None) => compileMRule(mr)
  | MATCH(mr, Some(m)) => {
      id: "MATCH",
      theiaAMADT:
        Apply(
          [empty, {id: "|", theiaAMADT: Atom(<> <br /> {React.string("| ")} </>)}, empty],
          [compileMRule(mr), compileMatch(m)],
        ),
    }
  }

and compileMRule = mr =>
  switch (mr) {
  | MRULE(p, e) => {
      id: "MRULE",
      theiaAMADT: Apply([empty, theiaStr(" => "), empty], [compilePat(p), compileExp(e)]),
    }
  }

and compileDec = d =>
  switch (d) {
  | VAL(vb) => {
      id: "VAL",
      theiaAMADT: Apply([theiaStr("val "), empty], [compileValBind(vb)]),
    }
  }

and compileValBind = vb =>
  switch (vb) {
  | PLAIN(p, e, None) => {
      id: "PLAIN",
      theiaAMADT: Apply([empty, theiaStr(" = "), empty], [compilePat(p), compileExp(e)]),
    }
  | REC(vb) => {
      id: "REC",
      theiaAMADT: Apply([theiaStr("rec "), empty], [compileValBind(vb)]),
    }
  }

and compileAtPat = a =>
  switch (a) {
  | WILDCARD => {id: "WILDCARD", theiaAMADT: Atom(React.string("_"))}
  | ID(x) => {id: "ID", theiaAMADT: Atom(React.string(x))}
  | RECORD(None) => {id: "RECORD", theiaAMADT: Atom(React.string("{}"))}
  | RECORD(Some(pr)) => {
      id: "RECORD",
      theiaAMADT: Apply([theiaStr("{"), theiaStr("}")], [compilePatRow(pr)]),
    }
  | PAR(p) => {
      id: "PAR",
      theiaAMADT: Apply([theiaStr("("), theiaStr(")")], [compilePat(p)]),
    }
  }

and compilePatRow = pr =>
  switch (pr) {
  | DOTS => {id: "DOTS", theiaAMADT: Atom(React.string("..."))}
  | FIELD(l, p, None) => {
      id: "FIELD",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), empty],
          [{id: "Lab", theiaAMADT: Atom(React.string(l))}, compilePat(p)],
        ),
    }
  | FIELD(l, p, Some(pr)) => {
      id: "FIELD",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), theiaStr(", "), empty],
          [{id: "Lab", theiaAMADT: Atom(React.string(l))}, compilePat(p), compilePatRow(pr)],
        ),
    }
  }

and compilePat = p =>
  switch (p) {
  | ATPAT(a) => compileAtPat(a)
  | CON(x, ap) => {
      id: "CON",
      theiaAMADT:
        Apply(
          [empty, theiaStr(" "), empty],
          [{id: "VID", theiaAMADT: Atom(React.string(x))}, compileAtPat(ap)],
        ),
    }
  };

let compileSVal = (sv: sVal) =>
  switch (sv) {
  | INT(n) => {id: "INT", theiaAMADT: Value([], [theiaStr(string_of_int(n))])}
  };

let compileIdStatus = id =>
  switch (id) {
  | Var => theiaStr("Var")
  | Con => theiaStr("Con")
  | Exc => theiaStr("Exc")
  };

let rec compileVal_ = v =>
  switch (v) {
  | SVAL(sv) => compileSVal(sv)
  | BASVAL(b) => {
      id: "BASVAL",
      theiaAMADT:
        Value(
          [],
          [
            {id: "builtin", theiaAMADT: Apply([theiaStr("builtin "), empty], [theiaStr(b)])},
          ],
        ),
    }
  | VID(x) => {id: "VID", theiaAMADT: Value([], [theiaStr(x)])}
  | VIDVAL(vid, v) => {id: "VIDVAL", theiaAMADT: Value([vid], [compileVal_(v)])}
  | RECORD([]) => {id: "RECORD", theiaAMADT: Value([], [theiaStr("{}")])}
  | RECORD(r) => {
      id: "RECORD",
      theiaAMADT:
        Value(
          [],
          [
            {id: "", theiaAMADT: Apply([theiaStr("{"), theiaStr("}")], [compileRecord(r)])},
          ],
        ),
    }
  | FCNCLOSURE(m, e, ve) => {
      id: "FCNCLOSURE",
      theiaAMADT: Value(["closure"], [compileMatch(m), compileEnv(e), compileEnv(ve)]),
    }
  }

and compileRecord = r =>
  switch (r) {
  | [] => empty
  | [(l, v)] => {
      id: "record",
      theiaAMADT: Apply([empty, theiaStr("="), empty], [theiaStr(l), compileVal_(v)]),
    }
  | [(l, v), ...r] => {
      id: "record",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), theiaStr(", "), empty],
          [theiaStr(l), compileVal_(v), compileRecord(r)],
        ),
    }
  }

and compileRecordEnv = rve =>
  switch (rve) {
  | [] => empty
  | [(l, ve)] => {
      id: "record env",
      theiaAMADT: Apply([empty, theiaStr("="), empty], [theiaStr(l), compileEnv(ve)]),
    }
  | [(l, ve), ...rve] => {
      id: "record env",
      theiaAMADT:
        Apply(
          [empty, theiaStr("="), theiaStr(", "), empty],
          [theiaStr(l), compileEnv(ve), compileRecordEnv(rve)],
        ),
    }
  }

and compileKVs = ((k, (v, id))) => {
  key: {
    id: "key",
    theiaAMADT: Atom(React.string(k)),
  },
  value: {
    id: "value",
    theiaAMADT: Apply([empty, theiaStr(" "), empty], [compileVal_(v), compileIdStatus(id)]),
  },
}

and compileEnv = e => {
  id: "valEnv",
  theiaAMADT:
    Map(
      {keyHeader: Some("Id"), valueHeader: Some("Value")},
      e |> List.map(compileKVs) |> List.rev,
    ),
};

let rec compileStrDec = sd =>
  switch (sd) {
  | DEC(d) => compileDec(d)
  | SEQ(sd1, sd2) => {
      id: "SEQ",
      theiaAMADT:
        Apply(
          [
            empty,
            {id: ";", theiaAMADT: Atom(<> {React.string(";")} <br /> <br /> </>)},
            empty,
          ],
          [compileStrDec(sd1), compileStrDec(sd2)],
        ),
    }
  };

let rec compileTopDec = td =>
  switch (td) {
  | STRDEC(sd, None) => compileStrDec(sd)
  | STRDEC(sd, Some(td)) => {
      id: "STRDEC",
      theiaAMADT:
        Apply(
          [empty, {id: "\\n", theiaAMADT: Atom(<> <br /> <br /> </>)}, empty],
          [compileStrDec(sd), compileTopDec(td)],
        ),
    }
  };

let rec compileProgram = p =>
  switch (p) {
  | PROGRAM(td, None) => compileTopDec(td)
  | PROGRAM(td, Some(p)) => {
      id: "PROGRAM",
      theiaAMADT:
        Apply(
          [
            empty,
            {id: ";", theiaAMADT: Atom(<> {React.string(";")} <br /> <br /> </>)},
            empty,
          ],
          [compileTopDec(td), compileProgram(p)],
        ),
    }
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
  | Match(m, v) => {
      id: "Match focus",
      theiaAMADT: HSequence([compileVal_(v), compileMatch(m)]),
    }
  | MRule(mr, v) => {
      id: "MRule focus",
      theiaAMADT: HSequence([compileVal_(v), compileMRule(mr)]),
    }
  | Pat(p, v) => {id: "Pat focus", theiaAMADT: HSequence([compileVal_(v), compilePat(p)])}
  | AtPat(ap, v) => {
      id: "AtPat focus",
      theiaAMADT: HSequence([compileVal_(v), compileAtPat(ap)]),
    }
  /* TODO: improve this */
  | PatRow(pr, r, rve) => {
      id: "PatRow focus",
      theiaAMADT: VSequence([compileRecordEnv(rve), compilePatRow(pr), compileRecord(r)]),
    }
  | FAIL(v) => {id: "FAIL", theiaAMADT: HSequence([theiaStr("FAIL"), compileVal_(v)])}
  | ValEnv(ve) => compileEnv(ve)
  | Empty => {id: "Empty", theiaAMADT: Atom(Util.nbsp)}
  };

let compileCtxt = c =>
  switch (c) {
  | LETD((), e) => {
      ops: [theiaStr("let "), theiaStr(" in "), theiaStr(" end")],
      args: [compileExp(e)],
      holePos: 0,
    }
  | VALBINDE(p, (), None) => {
      ops: [empty, theiaStr(" = "), empty],
      args: [compilePat(p)],
      holePos: 1,
    }
  | APPL((), x) => {ops: [empty, theiaStr(" "), empty], args: [compileAtExp(x)], holePos: 0}
  | APPR(f, ()) => {ops: [empty, theiaStr(" "), empty], args: [compileVal_(f)], holePos: 1}
  | SEQL((), sd2) => {
      ops: [
        empty,
        {id: ";", theiaAMADT: Atom(<> {React.string(";")} <br /> <br /> </>)},
        empty,
      ],
      args: [compileStrDec(sd2)],
      holePos: 0,
    }
  | DECD () => {ops: [empty, empty], args: [], holePos: 0}
  | RECORDER () => {ops: [theiaStr("{"), theiaStr("}")], args: [], holePos: 0}
  | EXPROWE([], l, (), None) => {
      ops: [empty, theiaStr("="), empty],
      args: [{id: "Lab", theiaAMADT: Atom(React.string(l))}],
      holePos: 1,
    }
  | EXPROWE(r, l, (), None) => {
      ops: [empty, theiaStr(", "), theiaStr("="), empty],
      args: [compileRecord(r), {id: "Lab", theiaAMADT: Atom(React.string(l))}],
      holePos: 2,
    }
  | EXPROWE([], l, (), Some(er)) => {
      ops: [empty, theiaStr("="), theiaStr(", "), empty],
      args: [{id: "Lab", theiaAMADT: Atom(React.string(l))}, compileExpRow(er)],
      holePos: 1,
    }
  | EXPROWE(r, l, (), Some(er)) => {
      ops: [empty, theiaStr(", "), theiaStr("="), theiaStr(", "), empty],
      args: [
        compileRecord(r),
        {id: "Lab", theiaAMADT: Atom(React.string(l))},
        compileExpRow(er),
      ],
      holePos: 2,
    }
  | PROGRAML((), p) => {
      ops: [
        empty,
        {id: ";", theiaAMADT: Atom(<> {React.string(";")} <br /> <br /> </>)},
        empty,
      ],
      args: [compileProgram(p)],
      holePos: 0,
    }
  | MATCHMR((), None) => {ops: [empty, empty], args: [], holePos: 0}
  | MATCHMR((), Some(m)) => {
      ops: [empty, {id: "|", theiaAMADT: Atom(<> <br /> {React.string("| ")} </>)}, empty],
      args: [compileMatch(m)],
      holePos: 0,
    }
  | MRULEP((), e) => {
      ops: [empty, theiaStr(" => "), empty],
      args: [compileExp(e)],
      holePos: 0,
    }
  | RECVB () => {ops: [theiaStr("rec "), empty], args: [], holePos: 0}
  | RECORDPR () => {ops: [theiaStr("{"), theiaStr("}")], args: [], holePos: 0}
  | STRDECSD((), None) => {ops: [empty, empty], args: [], holePos: 0}
  | STRDECSD((), Some(td)) => {
      ops: [empty, {id: "\\n", theiaAMADT: Atom(<> <br /> <br /> </>)}, empty],
      args: [compileTopDec(td)],
      holePos: 0,
    }
  /* TODO: this printing could probably be better */
  | FIELDP((l, (), None), r, rve) => {
      ops: [empty, empty, theiaStr("="), {id: "\\n", theiaAMADT: Atom(<br />)}, empty],
      args: [
        compileRecordEnv(rve),
        {id: "Lab", theiaAMADT: Atom(React.string(l))},
        compileRecord(r),
      ],
      holePos: 2,
    }
  | FIELDP((l, (), Some(pr)), r, rve) => {
      ops: [
        empty,
        empty,
        theiaStr("="),
        theiaStr(", "),
        {id: "\\n", theiaAMADT: Atom(<br />)},
        empty,
      ],
      args: [
        compileRecordEnv(rve),
        {id: "Lab", theiaAMADT: Atom(React.string(l))},
        compilePatRow(pr),
        compileRecord(r),
      ],
      holePos: 2,
    }
  };

let compileRewrite = ({focus, ctxts}) => {
  id: "rewrite",
  theiaAMADT: Kont(compileFocus(focus), List.map(compileCtxt, ctxts)),
};

let compileFrame = ({rewrite, env}) => {
  id: "frame",
  theiaAMADT:
    Cell(
      "frame",
      [
        {id: "env", theiaAMADT: Cell("env", [compileEnv(env)])},
        {id: "rewrite", theiaAMADT: Cell("rewrite", [compileRewrite(rewrite)])},
      ],
    ),
};

let smlToTheiaAM = fs => {
  id: "sml",
  theiaAMADT: VSequence(List.map(compileFrame, fs) |> List.rev),
};