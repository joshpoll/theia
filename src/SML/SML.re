/* Building up a very wrong, very simplistic SML interpreter. Grammar is not correct. */
/* This time we're letting the program section do ALL the traversal and the rewrite do ALL the computation. */
/* Following SML 97 and HaMLet closely.
 * Big difference: closure representation uses sharing like Sorin's OCaml visualizations.
 *   Should hopefully also enable simpler recursive function representation? Maybe?
 *
 * ignoring id status, op prefix, vid is string
 *
 * for now E = VE (obviously not sustainable)
 * for now no state
 */
/* HACK: unfolding all recursive functions to small-step AM. definitely has to be a better way to do
   this!*/
/* TODO: how to represent derived forms??? */
/* TODO: how to make variable lookup more granular?? */
/* TODO: environment handling is currently WRONG b/c never removes things from the environment */
/* TODO: id status */
/* TODO: desugaring toggling per sugar type (e.g. buttons for ite, orelse, andalso) */

/* TODO: figure out how to do monads in reason/ocaml. there's some ppx stuff. */

/* TODO: highlight code blocks, too? Might be useful for nested let expressions. */
type hole = unit;

type vid = string;
type lab = string;
type basVal = string;

type sCon =
  | INT(int);

type atExp =
  | SCON(sCon)
  | ID(vid)
  | RECORD(option(expRow))
  | LET(dec, exp)
  | PAR(exp)

and expRow =
  | EXPROW(lab, exp, option(expRow))

and exp =
  | ATEXP(atExp)
  | APP(exp, atExp)
  | FN(match)

and match =
  | MATCH(mrule, option(match))

and mrule =
  | MRULE(pat, exp)

and dec =
  /* no tyvar seq */
  | VAL(valBind)

and valBind =
  | PLAIN(pat, exp, option(valBind))
  | REC(valBind)

and atPat =
  /* TODO: add op */
  | ID(vid)
  | PAR(pat)

and pat =
  | ATPAT(atPat);

type sVal =
  | INT(int);

type record = list((lab, val_))

and val_ =
  | SVAL(sVal)
  | BASVAL(basVal)
  | VID(vid)
  | RECORD(record)
  /* TODO: second argument should be an entire env */
  /* TODO: keeping the second one flat is a hack to get rec vb's to work. */
  | FCNCLOSURE(match, list(valEnv), valEnv)

and valEnv = list((vid, val_));

type strDec =
  | DEC(dec)
  | SEQ(strDec, strDec);

type topDec =
  | STRDEC(strDec, option(topDec));

type program =
  | PROGRAM(topDec, option(program));

type focus =
  | AtExp(atExp)
  | Exp(exp)
  | Val(val_)
  | Dec(dec)
  | ValBind(valBind)
  | StrDec(strDec)
  | TopDec(topDec)
  | ExpRow(expRow)
  | Record(record)
  | Program(program)
  | Match(match, val_)
  | MRule(mrule, val_)
  | Pat(pat, val_)
  | AtPat(atPat, val_)
  | FAIL(val_)
  | Empty;

type ctxt =
  | LETD(hole, exp)
  | VALBINDE(pat, hole, option(valBind))
  | SEQL(hole, strDec)
  | APPL(hole, atExp)
  | APPR(val_, hole)
  /* is that a... */
  | RECORDER(hole)
  | EXPROWE(record, lab, hole, option(expRow))
  | PROGRAML(hole, program)
  | MATCHMR(hole, option(match))
  | MRULEP(hole, exp)
  | RECVB(hole);

type ctxts = list(ctxt);

type rewrite = {
  focus,
  ctxts,
};

type configuration = {
  rewrite,
  env: list(valEnv),
};

let apply = (f, v) =>
  switch (f, v) {
  | ("+", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) => SVAL(INT(a + b))
  | ("-", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) => SVAL(INT(a - b))
  | ("<", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) =>
    if (a < b) {
      VID("true");
    } else {
      VID("false");
    }
  | _ => failwith("unknown built-in function: " ++ f)
  };

let recEnv = ve =>
  List.map(
    fun
    | (x, FCNCLOSURE(m, e, _)) => (x, FCNCLOSURE(m, e, ve))
    | xv => xv,
    ve,
  );

let step = (c: configuration): option(configuration) =>
  switch (c) {
  /* Atomic Expressions */
  // [90]
  | {rewrite: {focus: AtExp(SCON(INT(n))), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Val(SVAL(INT(n))),
        ctxts,
      },
      env,
    })

  // [91]
  | {rewrite: {focus: AtExp(ID(x)), ctxts}, env} =>
    switch (Util.lookup(x, env)) {
    | None => None
    | Some(v) => Some({
                   rewrite: {
                     focus: Val(v),
                     ctxts,
                   },
                   env,
                 })
    }

  // [92]
  /* empty record */
  | {rewrite: {focus: AtExp(RECORD(None)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Val(RECORD([])),
        ctxts,
      },
      env,
    })
  /* start non-empty record */
  | {rewrite: {focus: AtExp(RECORD(Some(er))), ctxts}, env} =>
    Some({
      rewrite: {
        focus: ExpRow(er),
        ctxts: [RECORDER(), ...ctxts],
      },
      env,
    })
  /* complete non-empty record */
  | {rewrite: {focus: Record(r), ctxts: [RECORDER (), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Val(RECORD(r)),
        ctxts,
      },
      env,
    })

  // [93]
  | {rewrite: {focus: AtExp(LET(d, e)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Dec(d),
        ctxts: [LETD((), e), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Empty, ctxts: [LETD((), e), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts,
      },
      env,
    })

  // [94]
  | {rewrite: {focus: AtExp(PAR(e)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts,
      },
      env,
    })

  /* Expression Rows */
  // [95]
  // start visiting
  | {rewrite: {focus: ExpRow(EXPROW(l, e, r)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts: [EXPROWE([], l, (), r), ...ctxts],
      },
      env,
    })
  // mid visiting
  | {
      rewrite: {
        focus: Val(v),
        ctxts: [EXPROWE(r, l1, (), Some(EXPROW(l2, e, rest))), ...ctxts],
      },
      env,
    } =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts: [EXPROWE(r @ [(l1, v)], l2, (), rest), ...ctxts],
      },
      env,
    })
  // complete visiting
  | {rewrite: {focus: Val(v), ctxts: [EXPROWE(r, l, (), None), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Record(r @ [(l, v)]),
        ctxts,
      },
      env,
    })

  /* Expressions */
  // [96]
  | {rewrite: {focus: Exp(ATEXP(a)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: AtExp(a),
        ctxts,
      },
      env,
    })

  // helper rule for function application
  | {rewrite: {focus: Exp(APP(f, x)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Exp(f),
        ctxts: [APPL((), x), ...ctxts],
      },
      env,
    })

  // [101]
  /* TODO: may want a more coarse-grained traversal, not sure */
  | {rewrite: {focus: Val(BASVAL(f)), ctxts: [APPL((), a), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: AtExp(a),
        ctxts: [APPR(BASVAL(f), ()), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Val(v), ctxts: [APPR(BASVAL(f), ()), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Val(apply(f, v)),
        ctxts,
      },
      env,
    })

  // [102]
  | {rewrite: {focus: Val(FCNCLOSURE(m, e, ve)), ctxts: [APPL((), a), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: AtExp(a),
        ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Val(v), ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts]}, env: _} =>
    Some({
      rewrite: {
        focus: Match(m, v),
        ctxts,
      },
      env: [recEnv(ve), ...e] /* "backwards" compared to spec b/c 4.2 says lookup happens in RHS first */
    })
  // [108]
  | {rewrite: {focus: Exp(FN(m)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Val(FCNCLOSURE(m, env, [])),
        ctxts,
      },
      env,
    })

  /* Matches */
  | {rewrite: {focus: Match(MATCH(mr, om), v), ctxts}, env} =>
    Some({
      rewrite: {
        focus: MRule(mr, v),
        ctxts: [MATCHMR((), om), ...ctxts],
      },
      env,
    })

  // [109]
  /* mrule success */
  | {rewrite: {focus: Val(v), ctxts: [MATCHMR((), _), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Val(v),
        ctxts,
      },
      env,
    })

  // [110]
  | {rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), None), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: FAIL(v),
        ctxts,
      },
      env,
    })

  // [111]
  | {rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), Some(m)), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Match(m, v),
        ctxts,
      },
      env,
    })

  /* Match Rules */
  // [112]
  | {rewrite: {focus: MRule(MRULE(p, e), v), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Pat(p, v),
        ctxts: [MRULEP((), e), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Empty, ctxts: [MRULEP((), e), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts,
      },
      env,
    })

  // [113]
  | {rewrite: {focus: FAIL(v), ctxts: [MRULEP((), _), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: FAIL(v),
        ctxts,
      },
      env,
    })

  /* Declarations */
  // [114]
  | {rewrite: {focus: Dec(VAL(vb)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: ValBind(vb),
        ctxts,
      },
      env,
    })

  /* Value Bindings */
  // [124ish]. too specialized
  | {rewrite: {focus: ValBind(PLAIN(p, e, vbs)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Exp(e),
        ctxts: [VALBINDE(p, (), vbs), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Val(v), ctxts: [VALBINDE(ATPAT(ID(x)), (), None), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Empty,
        ctxts,
      },
      env: [[(x, v)], ...env],
    })

  // [126]
  | {rewrite: {focus: ValBind(REC(vb)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: ValBind(vb),
        ctxts: [RECVB(), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Empty, ctxts: [RECVB (), ...ctxts]}, env: [e, ...env]} =>
    Some({
      rewrite: {
        focus: Empty,
        ctxts,
      },
      env: [recEnv(e), ...env],
    })

  /* Type Bindings */
  /* Datatype Bindings */
  /* Constructor Bindings */
  /* Exception Bindings */
  /* Atomic Patterns */
  // [135-137ish]
  | {rewrite: {focus: AtPat(ID(x), v), ctxts}, env} =>
    let Some(v') = Util.lookup(x, env);
    if (v == v') {
      // [136]
      Some({
        rewrite: {
          focus: Empty,
          ctxts,
        },
        env,
      });
    } else {
      // [137]
      Some({
        rewrite: {
          focus: FAIL(v),
          ctxts,
        },
        env,
      });
    };
  /* Pattern Rows */
  /* Patterns */
  // [143]
  | {rewrite: {focus: Pat(ATPAT(ap), v), ctxts}, env} =>
    Some({
      rewrite: {
        focus: AtPat(ap, v),
        ctxts,
      },
      env,
    })

  /* ... */

  /* Structure-level Declarations */
  // [156]
  | {rewrite: {focus: StrDec(DEC(d)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: Dec(d),
        ctxts,
      },
      env,
    })

  // [160]
  | {rewrite: {focus: StrDec(SEQ(sd1, sd2)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: StrDec(sd1),
        ctxts: [SEQL((), sd2), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Empty, ctxts: [SEQL((), sd2), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: StrDec(sd2),
        ctxts,
      },
      env,
    })

  /* ... */

  /* Top-level Declarations */
  // [184ish]
  | {rewrite: {focus: TopDec(STRDEC(sd, None)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: StrDec(sd),
        ctxts,
      },
      env,
    })

  /* Programs */
  // [189ish]
  | {rewrite: {focus: Program(PROGRAM(td, None)), ctxts}, env} =>
    Some({
      rewrite: {
        focus: TopDec(td),
        ctxts,
      },
      env,
    })
  | {rewrite: {focus: Program(PROGRAM(td, Some(p))), ctxts}, env} =>
    Some({
      rewrite: {
        focus: TopDec(td),
        ctxts: [PROGRAML((), p), ...ctxts],
      },
      env,
    })
  | {rewrite: {focus: Empty, ctxts: [PROGRAML((), p), ...ctxts]}, env} =>
    Some({
      rewrite: {
        focus: Program(p),
        ctxts,
      },
      env,
    })
  | _ => None
  };

/* TODO: need to detect end using program segment somehow */
let isFinal = c =>
  switch (c) {
  /* | {frames: []} => true */
  // | {frames: [{ rewrite: {rewrite: Value(_), ctxs: []} }]} => true
  | _ => false
  };

// let injectExp = (e) => { rewrite: { focus: Exp(e), ctxts: [] }, env: [] };

let inject = e => {
  rewrite: {
    focus: e,
    ctxts: [],
  },
  env: [
    [
      ("+", BASVAL("+")),
      ("-", BASVAL("-")),
      ("<", BASVAL("<")),
      ("true", VID("true")),
      ("false", VID("false")),
    ],
  ],
};

let interpretTraceBounded = (~maxDepth=100, p) =>
  TheiaUtil.takeWhileInclusive(
    c => !isFinal(c),
    TheiaUtil.iterateMaybeMaxDepth(maxDepth, step, inject(p)),
  );
let interpretTrace = p =>
  TheiaUtil.takeWhileInclusive(c => !isFinal(c), TheiaUtil.iterateMaybe(step, inject(p))) /*   }*/ /*   switch (c) */ /*     | {frames: [{rewrite: {rewrite: Some(Value(VInt(n)))}}]} => string_of_int(n*/ /* let extract = (c) =*/;