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
/* TODO: switch program representation to {frames: list({rewrite: {focus, ctxts}, envs:
 * list(valEnv)})}
 *
 * semantics:
 *   - every function call creates a new frame. exiting a call pops a frame.
 *   - every let expression creates a new env. exiting a let pops an env
 */
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
  | RAISE(exp)
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
  | WILDCARD
  | ID(vid) /* TODO: add op */
  | RECORD(option(patRow))
  | PAR(pat)

and patRow =
  | DOTS
  | FIELD(lab, pat, option(patRow))

and pat =
  | ATPAT(atPat)
  | CON(vid, atPat);

type sVal =
  | INT(int);

type idStatus =
  | Var
  | Con
  | Exc;

type record = list((lab, val_))

and val_ =
  | SVAL(sVal)
  | BASVAL(basVal)
  | VID(vid)
  | VIDVAL(vid, val_) /* constructor value(?) */
  | RECORD(record)
  /* TODO: second argument should be an entire env */
  | FCNCLOSURE(match, list(valEnv), list(valEnv))

and valEnv = list((vid, (val_, idStatus)));

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
  | PatRow(patRow, record)
  | FAIL(val_)
  | Empty;

type ctxt =
  | LETD(hole, exp)
  | LETE(hole, hole)
  | VALBINDE(pat, hole, option(valBind))
  | VALBINDP(hole, hole, option(valBind))
  | SEQL(hole, strDec)
  | DECD(hole)
  | APPL(hole, atExp)
  | APPR(val_, hole)
  /* is that a... */
  | RECORDER(hole)
  | EXPROWE(record, lab, hole, option(expRow))
  | PROGRAML(hole, program)
  | MATCHMR(hole, option(match))
  | MRULEP(hole, exp)
  | MRULEE(hole, hole)
  | RECVB(hole)
  | RECORDPR(hole)
  | STRDECSD(hole, topDec)
  | FIELDP((lab, hole, option(patRow)), record);

type ctxts = list(ctxt);

type rewrite = {
  focus,
  ctxts,
};

type frame = {
  rewrite,
  env: list(valEnv),
};

type configuration = list(frame);

let apply = (f, v) =>
  switch (f, v) {
  | ("=", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) =>
    if (a == b) {
      VID("true");
    } else {
      VID("false");
    }
  | ("+", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) => SVAL(INT(a + b))
  | ("-", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) => SVAL(INT(a - b))
  | ("*", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) => SVAL(INT(a * b))
  | ("<", RECORD([("1", SVAL(INT(a))), ("2", SVAL(INT(b)))])) =>
    if (a < b) {
      VID("true");
    } else {
      VID("false");
    }
  | _ => failwith("unknown built-in function: " ++ f)
  };

let recOneEnv = ve =>
  List.map(
    fun
    | (x, (FCNCLOSURE(m, e, _), Var)) => (x, (FCNCLOSURE(m, e, [ve]), Var))
    | xv => xv,
    ve,
  );

let recEnv = ve =>
  List.map(
    List.map(
      fun
      | (x, (FCNCLOSURE(m, e, _), Var)) => (x, (FCNCLOSURE(m, e, ve), Var))
      | xv => xv,
    ),
    ve,
  );

let step = (c: configuration): option(configuration) =>
  switch (c) {
  /* Atomic Expressions */
  // [90]
  | [{rewrite: {focus: AtExp(SCON(INT(n))), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(SVAL(INT(n))),
              ctxts,
            },
            env,
          }, ...frames])

  // [91]
  | [{rewrite: {focus: AtExp(ID(x)), ctxts}, env}, ...frames] =>
    switch (Util.lookup(x, env)) {
    | None => None
    | Some((v, _)) => Some([{
                               rewrite: {
                                 focus: Val(v),
                                 ctxts,
                               },
                               env,
                             }, ...frames])
    }

  // [92]
  /* empty record */
  | [{rewrite: {focus: AtExp(RECORD(None)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(RECORD([])),
              ctxts,
            },
            env,
          }, ...frames])
  /* start non-empty record */
  | [{rewrite: {focus: AtExp(RECORD(Some(er))), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: ExpRow(er),
              ctxts: [RECORDER(), ...ctxts],
            },
            env,
          }, ...frames])
  /* complete non-empty record */
  | [{rewrite: {focus: Record(r), ctxts: [RECORDER (), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(RECORD(r)),
              ctxts,
            },
            env,
          }, ...frames])

  // [93]
  | [{rewrite: {focus: AtExp(LET(d, e)), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: Dec(d),
          ctxts: [LETD((), e), ...ctxts],
        },
        env: [[], ...env],
      },
      ...frames,
    ])
  | [{rewrite: {focus: Empty, ctxts: [LETD((), e), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Exp(e),
              ctxts: [LETE((), ()), ...ctxts],
            },
            env,
          }, ...frames])
  | [
      {rewrite: {focus: Val(v), ctxts: [LETE((), ()), ...ctxts]}, env: [_, ...env]},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: Val(v),
              ctxts,
            },
            env,
          }, ...frames])

  // [94]
  | [{rewrite: {focus: AtExp(PAR(e)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Exp(e),
              ctxts,
            },
            env,
          }, ...frames])

  /* Expression Rows */
  // [95]
  // start visiting
  | [{rewrite: {focus: ExpRow(EXPROW(l, e, r)), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: Exp(e),
          ctxts: [EXPROWE([], l, (), r), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  // mid visiting
  | [
      {
        rewrite: {
          focus: Val(v),
          ctxts: [EXPROWE(r, l1, (), Some(EXPROW(l2, e, rest))), ...ctxts],
        },
        env,
      },
      ...frames,
    ] =>
    Some([
      {
        rewrite: {
          focus: Exp(e),
          ctxts: [EXPROWE(r @ [(l1, v)], l2, (), rest), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  // complete visiting
  | [{rewrite: {focus: Val(v), ctxts: [EXPROWE(r, l, (), None), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Record(r @ [(l, v)]),
              ctxts,
            },
            env,
          }, ...frames])

  /* Expressions */
  // [96]
  | [{rewrite: {focus: Exp(ATEXP(a)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: AtExp(a),
              ctxts,
            },
            env,
          }, ...frames])

  // helper rule for function application
  | [{rewrite: {focus: Exp(APP(f, x)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Exp(f),
              ctxts: [APPL((), x), ...ctxts],
            },
            env,
          }, ...frames])

  /* TODO: consolidate some of these rules? */
  // [97]: no ref check
  | [{rewrite: {focus: Val(VID(vid)), ctxts: [APPL((), a), ...ctxts]}, env}, ...frames] =>
    Js.log("97a");
    Some([
      {
        rewrite: {
          focus: AtExp(a),
          ctxts: [APPR(VID(vid), ()), ...ctxts],
        },
        env,
      },
      ...frames,
    ]);
  | [{rewrite: {focus: Val(v), ctxts: [APPR(VID(vid), ()), ...ctxts]}, env}, ...frames] =>
    Js.log("97b");
    Some([{
            rewrite: {
              focus: Val(VIDVAL(vid, v)),
              ctxts,
            },
            env,
          }, ...frames]);

  // [101]
  /* TODO: may want a more coarse-grained traversal, not sure */
  | [{rewrite: {focus: Val(BASVAL(f)), ctxts: [APPL((), a), ...ctxts]}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: AtExp(a),
          ctxts: [APPR(BASVAL(f), ()), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [{rewrite: {focus: Val(v), ctxts: [APPR(BASVAL(f), ()), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(apply(f, v)),
              ctxts,
            },
            env,
          }, ...frames])

  // [102]
  | [
      {rewrite: {focus: Val(FCNCLOSURE(m, e, ve)), ctxts: [APPL((), a), ...ctxts]}, env},
      ...frames,
    ] =>
    Some([
      {
        rewrite: {
          focus: AtExp(a),
          ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [
      {rewrite: {focus: Val(v), ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts]}, env},
      ...frames,
    ] =>
    Some([
      {
        rewrite: {
          focus: Match(m, v),
          ctxts: [],
        },
        env: recEnv(ve) @ e /* "backwards" compared to spec b/c 4.2 says lookup happens in RHS first */
      },
      {
        rewrite: {
          focus: Empty,
          ctxts,
        },
        env,
      },
      ...frames,
    ])
  /* return from function call */
  | [
      {rewrite: {focus: Val(v), ctxts: []}, env: _},
      {rewrite: {focus: Empty, ctxts}, env},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: Val(v),
              ctxts,
            },
            env,
          }, ...frames])
  // [108]
  | [{rewrite: {focus: Exp(FN(m)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(FCNCLOSURE(m, env, [])),
              ctxts,
            },
            env,
          }, ...frames])

  /* Matches */
  /* TODO: there might be some way to combine env adding in pattern matches and val bindings */
  | [{rewrite: {focus: Match(MATCH(mr, om), v), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: MRule(mr, v),
          ctxts: [MATCHMR((), om), ...ctxts],
        },
        env: [[], ...env],
      },
      ...frames,
    ])

  // [109]
  /* mrule success */
  | [
      {rewrite: {focus: Val(v), ctxts: [MATCHMR((), _), ...ctxts]}, env: [_, ...env]},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: Val(v),
              ctxts,
            },
            env,
          }, ...frames])

  // [110]
  | [
      {rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), None), ...ctxts]}, env: [_, ...env]},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames])

  // [111]
  | [
      {rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), Some(m)), ...ctxts]}, env: [_, ...env]},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: Match(m, v),
              ctxts,
            },
            env,
          }, ...frames])

  /* Match Rules */
  // [112]
  | [{rewrite: {focus: MRule(MRULE(p, e), v), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Pat(p, v),
              ctxts: [MRULEP((), e), ...ctxts],
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: Empty, ctxts: [MRULEP((), e), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Exp(e),
              ctxts: [MRULEE((), ()), ...ctxts],
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: Val(v), ctxts: [MRULEE((), ()), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Val(v),
              ctxts,
            },
            env,
          }, ...frames])

  // [113]
  | [{rewrite: {focus: FAIL(v), ctxts: [MRULEP((), _), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames])

  /* Declarations */
  // [114ish]: should lift valenv into env
  | [{rewrite: {focus: Dec(VAL(vb)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: ValBind(vb),
              ctxts,
            },
            env,
          }, ...frames])

  /* Value Bindings */
  // [124ish]: doesn't support `and`
  | [{rewrite: {focus: ValBind(PLAIN(p, e, vbs)), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: Exp(e),
          ctxts: [VALBINDE(p, (), vbs), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [{rewrite: {focus: Val(v), ctxts: [VALBINDE(p, (), None), ...ctxts]}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: Pat(p, v),
          ctxts: [VALBINDP((), (), None), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [{rewrite: {focus: Empty, ctxts: [VALBINDP((), (), None), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])

  // [126]
  | [{rewrite: {focus: ValBind(REC(vb)), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: ValBind(vb),
          ctxts: [RECVB(), ...ctxts],
        },
        env: [[], ...env],
      },
      ...frames,
    ])
  | [{rewrite: {focus: Empty, ctxts: [RECVB (), ...ctxts]}, env: [ve, ...env]}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env: [recOneEnv(ve), ...env],
          }, ...frames])

  /* Type Bindings */
  /* Datatype Bindings */
  /* Constructor Bindings */
  /* Exception Bindings */
  /* Atomic Patterns */
  // [132]
  | [{rewrite: {focus: AtPat(WILDCARD, _), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])

  // [135-137ish]
  | [{rewrite: {focus: AtPat(ID(x), v), ctxts}, env: [ve, ...env]}, ...frames] =>
    switch (Util.lookup(x, [ve, ...env])) {
    // [135]
    | None
    | Some((_, Var)) =>
      Some([
        {
          rewrite: {
            focus: Empty,
            ctxts,
          },
          env: [[(x, (v, Var)), ...ve], ...env],
        },
        ...frames,
      ])
    // [136]
    | Some((v', id)) when v == v' =>
      Some([{
              rewrite: {
                focus: Empty,
                ctxts,
              },
              env: [ve, ...env],
            }, ...frames])
    // [137]
    | Some((v', id)) =>
      Some([{
              rewrite: {
                focus: FAIL(v),
                ctxts,
              },
              env: [ve, ...env],
            }, ...frames])
    }

  // [138]
  /* empty record pat */
  /* TODO: special-casing RECORD(None) may be overkill. not sure */
  | [{rewrite: {focus: AtPat(RECORD(None), RECORD([])), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: AtPat(RECORD(None), v), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames])
  /* start non-empty record pat */
  | [{rewrite: {focus: AtPat(RECORD(Some(pr)), RECORD(r)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: PatRow(pr, r),
              ctxts: [RECORDPR(), ...ctxts],
            },
            env,
          }, ...frames])
  /* complete non-empty record pat */
  | [{rewrite: {focus: Empty, ctxts: [RECORDPR (), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: FAIL(v), ctxts: [RECORDPR (), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames])

  // [139]
  | [{rewrite: {focus: AtPat(PAR(p), v), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Pat(p, v),
              ctxts,
            },
            env,
          }, ...frames])

  /* Pattern Rows */
  // [140]
  | [{rewrite: {focus: PatRow(DOTS, _), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])

  // [141-142]
  /* NOTE: SML '97 says each field should be evaluated in the original environment, but we extend it
     after every field. This simplifies our implementation since we don't need to maintain a
     temporary environment outside of `env`. This still agrees with SML '97 thanks to the
     left-linear pattern restriction. */
  /* start visiting */
  | [{rewrite: {focus: PatRow(FIELD(l, p, opr), r), ctxts}, env}, ...frames] =>
    /* NOTE: Shouldn't fail for well-typed programs per SML '97 comments. */
    let Some(v) = Util.lookupOne(l, r);
    Some([
      {
        rewrite: {
          focus: Pat(p, v),
          ctxts: [FIELDP((l, (), opr), r), ...ctxts],
        },
        env,
      },
      ...frames,
    ]);
  // [141]
  | [{rewrite: {focus: FAIL(v), ctxts: [FIELDP((_, (), _), _), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames])
  // [142]
  | [{rewrite: {focus: Empty, ctxts: [FIELDP((_, (), None), _), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])
  | [
      {rewrite: {focus: Empty, ctxts: [FIELDP((_, (), Some(pr)), r), ...ctxts]}, env},
      ...frames,
    ] =>
    Some([{
            rewrite: {
              focus: PatRow(pr, r),
              ctxts,
            },
            env,
          }, ...frames])
  /* Patterns */
  // [143]
  | [{rewrite: {focus: Pat(ATPAT(ap), v), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: AtPat(ap, v),
              ctxts,
            },
            env,
          }, ...frames])

  /* TODO: maybe consolidate 145a and b somehow? */
  /* | [{rewrite: {focus: Pat(CON(con, ap), VIDVAL(vid, v)), ctxts}, env}, ...frames] =>
     let Some((VID(vidC), Con)) = Util.lookup(con, env);
     if (vidC == vid) {
       // [144]: ignores ref check
       Js.log("144");
       Some([{
               rewrite: {
                 focus: AtPat(ap, v),
                 ctxts,
               },
               env,
             }, ...frames]);
     } else {
       // [145a]
       Js.log("145a");
       Some([{
               rewrite: {
                 focus: FAIL(VIDVAL(vid, v)),
                 ctxts,
               },
               env,
             }, ...frames]);
     }; */

  // [145b]
  | [{rewrite: {focus: Pat(CON(_, _), v), ctxts}, env}, ...frames] =>
    Js.log("145b");
    Some([{
            rewrite: {
              focus: FAIL(v),
              ctxts,
            },
            env,
          }, ...frames]);

  /* ... */
  /* Structure-level Declarations */
  // [156]
  | [{rewrite: {focus: StrDec(DEC(d)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Dec(d),
              ctxts: [DECD(), ...ctxts],
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: Empty, ctxts: [DECD (), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Empty,
              ctxts,
            },
            env,
          }, ...frames])
  // [160]
  | [{rewrite: {focus: StrDec(SEQ(sd1, sd2)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: StrDec(sd1),
              ctxts: [SEQL((), sd2), ...ctxts],
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: Empty, ctxts: [SEQL((), sd2), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: StrDec(sd2),
              ctxts,
            },
            env,
          }, ...frames])

  /* ... */

  /* Top-level Declarations */
  // [184ish]
  | [{rewrite: {focus: TopDec(STRDEC(sd, None)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: StrDec(sd),
              ctxts,
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: TopDec(STRDEC(sd, Some(td))), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: StrDec(sd),
          ctxts: [STRDECSD((), td), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [{rewrite: {focus: Empty, ctxts: [STRDECSD((), td), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: TopDec(td),
              ctxts,
            },
            env,
          }, ...frames])

  /* Programs */
  // [189ish]
  | [{rewrite: {focus: Program(PROGRAM(td, None)), ctxts}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: TopDec(td),
              ctxts,
            },
            env,
          }, ...frames])
  | [{rewrite: {focus: Program(PROGRAM(td, Some(p))), ctxts}, env}, ...frames] =>
    Some([
      {
        rewrite: {
          focus: TopDec(td),
          ctxts: [PROGRAML((), p), ...ctxts],
        },
        env,
      },
      ...frames,
    ])
  | [{rewrite: {focus: Empty, ctxts: [PROGRAML((), p), ...ctxts]}, env}, ...frames] =>
    Some([{
            rewrite: {
              focus: Program(p),
              ctxts,
            },
            env,
          }, ...frames])
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

let inject = e => [
  {
    rewrite: {
      focus: e,
      ctxts: [],
    },
    env: [
      [
        ("=", (BASVAL("="), Var)),
        ("+", (BASVAL("+"), Var)),
        ("-", (BASVAL("-"), Var)),
        ("*", (BASVAL("*"), Var)),
        ("<", (BASVAL("<"), Var)),
        ("true", (VID("true"), Con)),
        ("false", (VID("false"), Con)),
        ("nil", (VID("nil"), Con)),
        ("::", (VID("::"), Con)),
      ],
    ],
  },
];

let interpretTraceBounded = (~maxDepth=100, p) =>
  TheiaUtil.takeWhileInclusive(
    c => !isFinal(c),
    TheiaUtil.iterateMaybeMaxDepth(maxDepth, step, inject(p)),
  );
let interpretTrace = p =>
  TheiaUtil.takeWhileInclusive(c => !isFinal(c), TheiaUtil.iterateMaybe(step, inject(p)));