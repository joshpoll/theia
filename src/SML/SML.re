/* Hardfork of previous version with a key difference: No tiered environments. Tiered environments
   were introduced for let expressions; however, their role should be subsumed by CoW. Also may
   bring this implementation closer to what would come out of the actual interpreter since each
   frame may literally be a recursive call (though not all recursive calls in the interpreter are
   represented).

   also returns val envs explicitly in many places to more closely match semantics and make
   modularity work better. Consider a list of val bindings. Each one must be evaluated in a new
   frame. That frame should return a val env so it can be added to the basis by the root frame.
   */

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
/* TODO: separate initial basis from rest of the environment so it's easier to hide.
     may be possible to achieve by ALWAYS creating a new frame at the beginning/set up rules so this
     happens.
   */
/* TODO: desugaring toggling per sugar type (e.g. buttons for ite, orelse, andalso) */

/* TODO: figure out how to do monads in reason/ocaml. there's some ppx stuff. */

/* TODO: highlight code blocks, too? Might be useful for nested let expressions. */
type hole = unit;

/* TODO: these should be annotated too */
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

and recordEnv = list((lab, valEnv))

and val_ =
  | SVAL(sVal)
  | BASVAL(basVal)
  | VID(vid)
  | VIDVAL(vid, val_) /* constructor value(?) */
  | RECORD(record)
  /* TODO: second argument should be an entire env */
  | FCNCLOSURE(match, valEnv, valEnv)

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
  | PatRow(patRow, record, recordEnv)
  | FAIL(val_)
  | ValEnv(valEnv)
  | Empty;

type ctxt =
  | LETD(hole, exp)
  | VALBINDE(pat, hole, option(valBind))
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
  | RECVB(hole)
  | RECORDPR(hole)
  | STRDECSD(hole, option(topDec))
  | FIELDP((lab, hole, option(patRow)), record, recordEnv);

type ctxts = list(ctxt);

type rewrite = {
  focus,
  ctxts,
};

type frame = {
  rewrite,
  env: valEnv,
};

type configuration = list(frame);

/* annotated state */
type sConAnno('a) =
  | INT_A(int, 'a);

type atExpAnno('a) =
  | SCON_A(sConAnno('a), 'a)
  | ID_A(vid, 'a)
  | RECORD_A(option(expRowAnno('a)), 'a)
  | LET_A(decAnno('a), expAnno('a), 'a)
  | PAR_A(expAnno('a), 'a)

and expRowAnno('a) =
  | EXPROW_A(lab, expAnno('a), option(expRowAnno('a)), 'a)

and expAnno('a) =
  | ATEXP_A(atExpAnno('a), 'a)
  | APP_A(expAnno('a), atExpAnno('a), 'a)
  | RAISE_A(expAnno('a), 'a)
  | FN_A(matchAnno('a), 'a)

and matchAnno('a) =
  | MATCH_A(mruleAnno('a), option(matchAnno('a)), 'a)

and mruleAnno('a) =
  | MRULE_A(patAnno('a), expAnno('a), 'a)

and decAnno('a) =
  /* no tyvar seq */
  | VAL_A(valBindAnno('a), 'a)

and valBindAnno('a) =
  | PLAIN_A(patAnno('a), expAnno('a), option(valBindAnno('a)), 'a)
  | REC_A(valBindAnno('a), 'a)

and atPatAnno('a) =
  | WILDCARD_A('a)
  | ID_A(vid, 'a) /* TODO: add op */
  | RECORD_A(option(patRowAnno('a)), 'a)
  | PAR_A(patAnno('a), 'a)

and patRowAnno('a) =
  | DOTS_A('a)
  | FIELD_A(lab, patAnno('a), option(patRowAnno('a)), 'a)

and patAnno('a) =
  | ATPAT_A(atPatAnno('a), 'a)
  | CON_A(vid, atPatAnno('a), 'a);

type sValAnno('a) =
  | INT_A(int, 'a);

type idStatusAnno('a) =
  | Var_A('a)
  | Con_A('a)
  | Exc_A('a);

type recordAnno('a) = list((lab, val_Anno('a)))

and recordEnvAnno('a) = list((lab, valEnvAnno('a)))

and val_Anno('a) =
  | SVAL_A(sValAnno('a), 'a)
  | BASVAL_A(basVal, 'a)
  | VID_A(vid, 'a)
  | VIDVAL_A(vid, val_Anno('a), 'a) /* constructor value(?) */
  | RECORD_A(recordAnno('a), 'a)
  /* TODO: second argument should be an entire env */
  | FCNCLOSURE_A(matchAnno('a), valEnvAnno('a), valEnvAnno('a), 'a)

and valEnvAnno('a) = list((vid, (val_Anno('a), idStatusAnno('a))));

type strDecAnno('a) =
  | DEC_A(decAnno('a), 'a)
  | SEQ_A(strDecAnno('a), strDecAnno('a), 'a);

type topDecAnno('a) =
  | STRDEC_A(strDecAnno('a), option(topDecAnno('a)), 'a);

type programAnno('a) =
  | PROGRAM_A(topDecAnno('a), option(programAnno('a)), 'a);

type focusAnno('a) =
  | AtExp_A(atExpAnno('a), 'a)
  | Exp_A(expAnno('a), 'a)
  | Val_A(val_Anno('a), 'a)
  | Dec_A(decAnno('a), 'a)
  | ValBind_A(valBindAnno('a), 'a)
  | StrDec_A(strDecAnno('a), 'a)
  | TopDec_A(topDecAnno('a), 'a)
  | ExpRow_A(expRowAnno('a), 'a)
  | Record_A(recordAnno('a), 'a)
  | Program_A(programAnno('a), 'a)
  | Match_A(matchAnno('a), val_Anno('a), 'a)
  | MRule_A(mruleAnno('a), val_Anno('a), 'a)
  | Pat_A(patAnno('a), val_Anno('a), 'a)
  | AtPat_A(atPatAnno('a), val_Anno('a), 'a)
  | PatRow_A(patRowAnno('a), recordAnno('a), recordEnvAnno('a), 'a)
  | FAIL_A(val_Anno('a), 'a)
  | ValEnv_A(valEnvAnno('a), 'a)
  | Empty_A('a);

type ctxtAnno('a) =
  | LETD_A(hole, expAnno('a), 'a)
  | VALBINDE_A(patAnno('a), hole, option(valBindAnno('a)), 'a)
  | SEQL_A(hole, strDecAnno('a), 'a)
  | DECD_A(hole, 'a)
  | APPL_A(hole, atExpAnno('a), 'a)
  | APPR_A(val_Anno('a), hole, 'a)
  /* is that a... */
  | RECORDER_A(hole, 'a)
  | EXPROWE_A(recordAnno('a), lab, hole, option(expRowAnno('a)), 'a)
  | PROGRAML_A(hole, programAnno('a), 'a)
  | MATCHMR_A(hole, option(matchAnno('a)), 'a)
  | MRULEP_A(hole, expAnno('a), 'a)
  | RECVB_A(hole, 'a)
  | RECORDPR_A(hole, 'a)
  | STRDECSD_A(hole, option(topDecAnno('a)), 'a)
  | FIELDP_A((lab, hole, option(patRowAnno('a))), recordAnno('a), recordEnvAnno('a), 'a);

type ctxtsAnno('a) = list(ctxtAnno('a));

type rewriteAnno('a) = {
  focusAnno: focusAnno('a),
  ctxtsAnno: ctxtsAnno('a),
};

type frameAnno('a) = {
  rewriteAnno: rewriteAnno('a),
  envAnno: valEnvAnno('a),
};

type configurationAnno('a) = list(frameAnno('a));

/* TODO: write default annotation function and annotation stripper */
let rec annotateSCon = (sc: sCon, a): sConAnno('a) =>
  switch (sc) {
  | INT(n) => INT_A(n, a)
  }

and annotateAtExp = (ae, a) =>
  switch (ae) {
  | SCON(sc) => SCON_A(annotateSCon(sc, a), a)
  | ID(vid) => ID_A(vid, a)
  | RECORD(None) => RECORD_A(None, a)
  | RECORD(Some(er)) => RECORD_A(Some(annotateExpRow(er, a)), a)
  | LET(d, e) => LET_A(annotateDec(d, a), annotateExp(e, a), a)
  | PAR(e) => PAR_A(annotateExp(e, a), a)
  }

and annotateExpRow = (er, a) =>
  switch (er) {
  | EXPROW(l, e, None) => EXPROW_A(l, annotateExp(e, a), None, a)
  | EXPROW(l, e, Some(er)) => EXPROW_A(l, annotateExp(e, a), Some(annotateExpRow(er, a)), a)
  }

and annotateExp = (e, a) =>
  switch (e) {
  | ATEXP(ae) => ATEXP_A(annotateAtExp(ae, a), a)
  | APP(e, ae) => APP_A(annotateExp(e, a), annotateAtExp(ae, e), a)
  | RAISE(e) => RAISE_A(annotateExp(e, a), a)
  | FN(m) => FN_A(annotateMatch(m, a), a)
  }

and annotateMatch = (m, a) =>
  switch (m) {
  | MATCH(mr, None) => MATCH_A(annotateMRule(mr, a), None, a)
  | MATCH(mr, Some(m)) => MATCH_A(annotateMRule(mr, a), Some(annotateMatch(m, a)), a)
  }

and annotateMRule = (mr, a) =>
  switch (mr) {
  | MRULE(p, e) => MRULE_A(annotatePat(p, a), annotateExp(e, a), a)
  }

and annotateDec = (d, a) =>
  switch (d) {
  | VAL(vb) => VAL_A(annotateValBind(vb, a), a)
  }

and annotateValBind = (vb, a) =>
  switch (vb) {
  | PLAIN(p, e, None) => PLAIN_A(annotatePat(p, a), annotateExp(e, a), None, a)
  | PLAIN(p, e, Some(vb)) =>
    PLAIN_A(annotatePat(p, a), annotateExp(e, a), Some(annotateValBind(vb, a)), a)
  | REC(vb) => REC_A(annotateValBind(vb, a), a)
  }

and annotateAtPat = (ap, a) =>
  switch (ap) {
  | WILDCARD => WILDCARD_A(a)
  | ID(vid) => ID_A(vid, a)
  | RECORD(None) => RECORD_A(None, a)
  | RECORD(Some(pr)) => RECORD_A(Some(annotatePatRow(pr, a)), a)
  | PAR(p) => PAR_A(annotatePat(p, a), a)
  }

and annotatePatRow = (pr, a) =>
  switch (pr) {
  | DOTS => DOTS_A(a)
  | FIELD(l, p, None) => FIELD_A(l, annotatePat(p, a), None, a)
  | FIELD(l, p, Some(pr)) => FIELD_A(l, annotatePat(p, a), Some(annotatePatRow(pr, a)), a)
  }

and annotatePat = (p, a) =>
  switch (p) {
  | ATPAT(ap) => ATPAT_A(annotateAtPat(ap, a), a)
  | CON(vid, ap) => CON_A(vid, annotateAtPat(ap, a), a)
  };

let annotateSVal = (sv, a) =>
  switch (sv) {
  | INT(n) => INT_A(n, a)
  };

let annotateIdStatus = (id, a) =>
  switch (id) {
  | Var => Var_A(a)
  | Con => Con_A(a)
  | Exc => Exc_A(a)
  };

let rec annotateRecord = (r, a) => r |> List.map(((l, v)) => (l, annotateVal_(v, a)))

and annotateRecordEnv = (re, a) => re |> List.map(((l, ve)) => (l, annotateValEnv(ve, a)))

and annotateVal_ = (v, a) =>
  switch (v) {
  | SVAL(sv) => SVAL_A(annotateSVal(sv, a), a)
  | BASVAL(bv) => BASVAL_A(bv, a)
  | VID(vid) => VID_A(vid, a)
  | VIDVAL(vid, v) => VIDVAL_A(vid, annotateVal_(v, a), a)
  | RECORD(r) => RECORD_A(annotateRecord(r, a), a)
  | FCNCLOSURE(m, e, ve) =>
    FCNCLOSURE_A(annotateMatch(m, a), annotateValEnv(e, a), annotateValEnv(ve, a), a)
  }

and annotateValEnv = (ve, a) =>
  ve |> List.map(((vid, (v, i))) => (vid, (annotateVal_(v, a), annotateIdStatus(i, a))));

let rec annotateStrDec = (sd, a) =>
  switch (sd) {
  | DEC(d) => DEC_A(annotateDec(d, a), a)
  | SEQ(sd1, sd2) => SEQ_A(annotateStrDec(sd1, a), annotateStrDec(sd2, a), a)
  };

let rec annotateTopDec = (td, a) =>
  switch (td) {
  | STRDEC(sd, None) => STRDEC_A(annotateStrDec(sd, a), None, a)
  | STRDEC(sd, Some(td)) => STRDEC_A(annotateStrDec(sd, a), Some(annotateTopDec(td, a)), a)
  };

let rec annotateProgram = (p, a) =>
  switch (p) {
  | PROGRAM(td, None) => PROGRAM_A(annotateTopDec(td, a), None, a)
  | PROGRAM(td, Some(p)) => PROGRAM_A(annotateTopDec(td, a), Some(annotateProgram(p, a)), a)
  };

let annotateFocus = (f, a) =>
  switch (f) {
  | AtExp(ae) => AtExp_A(annotateAtExp(ae, a), a)
  | Exp(e) => Exp_A(annotateExp(e, a), a)
  | Val(v) => Val_A(annotateVal_(v, a), a)
  | Dec(d) => Dec_A(annotateDec(d, a), a)
  | ValBind(vb) => ValBind_A(annotateValBind(vb, a), a)
  | StrDec(sd) => StrDec_A(annotateStrDec(sd, a), a)
  | TopDec(td) => TopDec_A(annotateTopDec(td, a), a)
  | ExpRow(er) => ExpRow_A(annotateExpRow(er, a), a)
  | Record(r) => Record_A(annotateRecord(r, a), a)
  | Program(p) => Program_A(annotateProgram(p, a), a)
  | Match(m, v) => Match_A(annotateMatch(m, a), annotateVal_(v, a), a)
  | MRule(mr, v) => MRule_A(annotateMRule(mr, a), annotateVal_(v, a), a)
  | Pat(p, v) => Pat_A(annotatePat(p, a), annotateVal_(v, a), a)
  | AtPat(ap, v) => AtPat_A(annotateAtPat(ap, a), annotateVal_(v, a), a)
  | PatRow(pr, r, re) =>
    PatRow_A(annotatePatRow(pr, a), annotateRecord(r, a), annotateRecordEnv(re, a), a)
  | FAIL(v) => FAIL_A(annotateVal_(v, a), a)
  | ValEnv(ve) => ValEnv_A(annotateValEnv(ve, a), a)
  | Empty => Empty_A(a)
  };

let annotateCtxt = (c, a) =>
  switch (c) {
  | LETD((), e) => LETD_A((), annotateExp(e, a), a)
  | VALBINDE(p, (), None) => VALBINDE_A(annotatePat(p, a), (), None, a)
  | VALBINDE(p, (), Some(vb)) =>
    VALBINDE_A(annotatePat(p, a), (), Some(annotateValBind(vb, a)), a)
  | SEQL((), sd) => SEQL_A((), annotateStrDec(sd, a), a)
  | DECD () => DECD_A((), a)
  | APPL((), ae) => APPL_A((), annotateAtExp(ae, a), a)
  | APPR(v, ()) => APPR_A(annotateVal_(v, a), (), a)
  | RECORDER () => RECORDER_A((), a)
  | EXPROWE(r, l, (), None) => EXPROWE_A(annotateRecord(r, a), l, (), None, a)
  | EXPROWE(r, l, (), Some(er)) =>
    EXPROWE_A(annotateRecord(r, a), l, (), Some(annotateExpRow(er, a)), a)
  | PROGRAML((), p) => PROGRAML_A((), annotateProgram(p, a), a)
  | MATCHMR((), None) => MATCHMR_A((), None, a)
  | MATCHMR((), Some(m)) => MATCHMR_A((), Some(annotateMatch(m, a)), a)
  | MRULEP((), e) => MRULEP_A((), annotateExp(e, a), a)
  | RECVB () => RECVB_A((), a)
  | RECORDPR () => RECORDPR_A((), a)
  | STRDECSD((), None) => STRDECSD_A((), None, a)
  | STRDECSD((), Some(td)) => STRDECSD_A((), Some(annotateTopDec(td, a)), a)
  | FIELDP((l, (), None), r, re) =>
    FIELDP_A((l, (), None), annotateRecord(r, a), annotateRecordEnv(re, a), a)
  | FIELDP((l, (), Some(pr)), r, re) =>
    FIELDP_A(
      (l, (), Some(annotatePatRow(pr, a))),
      annotateRecord(r, a),
      annotateRecordEnv(re, a),
      a,
    )
  };

let annotateCtxts = (cs, a) => cs |> List.map(annotateCtxt(_, a));

let annotateRewrite = ({focus, ctxts}, a) => {
  focusAnno: annotateFocus(focus, a),
  ctxtsAnno: annotateCtxts(ctxts, a),
};

let annotateFrame = ({rewrite, env}, a) => {
  rewriteAnno: annotateRewrite(rewrite, a),
  envAnno: annotateValEnv(env, a),
};

let annotateConfiguration = (c, a) => c |> List.map(annotateFrame(a));

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

let recEnv = ve =>
  List.map(
    fun
    | (x, (FCNCLOSURE(m, e, _), Var)) => (x, (FCNCLOSURE(m, e, ve), Var))
    | xv => xv,
    ve,
  );

let uid = ref(0);

let genFresh = () => {
  uid := uid^ + 1;
  uid^;
};

type label = int;

type transition = {
  lhs: configurationAnno(option(label)),
  rhs: configurationAnno(list(label)),
};

/* TODO: type should be configuration => option({lhs: configurationAnno(option(label)), rhs: configurationAnno(list(label))}) */
let step = (c: configuration): option(transition) =>
  switch (c) {
  /* frame pop */
  // TODO: maybe this one should check for an empty focus and push the env?
  // | [
  //     {rewrite: {focus: ValEnv(ve), ctxts: []}, env: _},
  //     {rewrite: {focus: Empty, ctxts}, env},
  //     ...frames,
  //   ] =>
  //   Js.log("frame pop ValEnv");
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv(ve),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // | [
  //     {rewrite: {focus: Val(v), ctxts: []}, env: _},
  //     {rewrite: {focus: Empty, ctxts}, env},
  //     ...frames,
  //   ] =>
  //   Js.log("frame pop Val");
  //   Some([{
  //           rewrite: {
  //             focus: Val(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // | [
  //     {rewrite: {focus: FAIL(v), ctxts: []}, env: _},
  //     {rewrite: {focus: Empty, ctxts}, env},
  //     ...frames,
  //   ] =>
  //   Js.log("frame pop FAIL");
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  /* Atomic Expressions */
  // [90]
  | [{rewrite: {focus: AtExp(SCON(INT(n))), ctxts}, env}, ...frames] =>
    let anno = genFresh();
    Some({
      lhs: [
        {
          rewriteAnno: {
            focusAnno: AtExp_A(SCON_A(INT_A(n, Some(anno)), None), None),
            /* TODO: need to write default annotation functions */
            ctxtsAnno: /* annotateCtxts(ctxts) */ [],
          },
          envAnno: /* annotateEnv(env, None) */ [],
        },
        /* ...annotateFrames(frames, None) */
      ],
      rhs: [
        {
          rewriteAnno: {
            focusAnno: Val_A(SVAL_A(INT_A(n, [anno]), []), []),
            ctxtsAnno: [],
          },
          envAnno: /* annotateEnv(env, []) */ [],
        },
        /* annotateFrames(frames, []) */
      ],
    });

  // // [91]
  // | [{rewrite: {focus: AtExp(ID(x)), ctxts}, env}, ...frames] =>
  //   switch (Util.lookupOne(x, env)) {
  //   | None => None
  //   | Some((v, _)) => Some([{
  //                              rewrite: {
  //                                focus: Val(v),
  //                                ctxts,
  //                              },
  //                              env,
  //                            }, ...frames])
  //   }

  // // [92]
  // /* empty record */
  // | [{rewrite: {focus: AtExp(RECORD(None)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Val(RECORD([])),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // /* start non-empty record */
  // | [{rewrite: {focus: AtExp(RECORD(Some(er))), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ExpRow(er),
  //             ctxts: [RECORDER(), ...ctxts],
  //           },
  //           env,
  //         }, ...frames])
  // /* complete non-empty record */
  // | [{rewrite: {focus: Record(r), ctxts: [RECORDER (), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Val(RECORD(r)),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [93]
  // /* begin let traversal */
  // | [{rewrite: {focus: AtExp(LET(d, e)), ctxts: []}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Dec(d),
  //             ctxts: [LETD((), e)],
  //           },
  //           env,
  //         }, ...frames])
  // /* continue with exp */
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [LETD((), e), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Exp(e),
  //             ctxts,
  //           },
  //           env: ve @ env,
  //         }, ...frames])
  // /* push LET into a new frame */
  // | [{rewrite: {focus: AtExp(LET(d, e)), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: AtExp(LET(d, e)),
  //         ctxts: [],
  //       },
  //       env,
  //     },
  //     {
  //       rewrite: {
  //         focus: Empty,
  //         ctxts,
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])

  // // [94]
  // | [{rewrite: {focus: AtExp(PAR(e)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Exp(e),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Expression Rows */
  // // [95]
  // // start visiting
  // | [{rewrite: {focus: ExpRow(EXPROW(l, e, r)), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Exp(e),
  //         ctxts: [EXPROWE([], l, (), r), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // // mid visiting
  // | [
  //     {
  //       rewrite: {
  //         focus: Val(v),
  //         ctxts: [EXPROWE(r, l1, (), Some(EXPROW(l2, e, rest))), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Exp(e),
  //         ctxts: [EXPROWE(r @ [(l1, v)], l2, (), rest), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // // complete visiting
  // | [{rewrite: {focus: Val(v), ctxts: [EXPROWE(r, l, (), None), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Record(r @ [(l, v)]),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Expressions */
  // // [96]
  // | [{rewrite: {focus: Exp(ATEXP(a)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: AtExp(a),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // helper rule for function application
  // | [{rewrite: {focus: Exp(APP(f, x)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Exp(f),
  //             ctxts: [APPL((), x), ...ctxts],
  //           },
  //           env,
  //         }, ...frames])

  // // /* TODO: consolidate some of these rules? */
  // // [97]: no ref check
  // | [{rewrite: {focus: Val(VID(vid)), ctxts: [APPL((), a), ...ctxts]}, env}, ...frames] =>
  //   Js.log("97a");
  //   Some([
  //     {
  //       rewrite: {
  //         focus: AtExp(a),
  //         ctxts: [APPR(VID(vid), ()), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ]);
  // | [{rewrite: {focus: Val(v), ctxts: [APPR(VID(vid), ()), ...ctxts]}, env}, ...frames] =>
  //   Js.log("97b");
  //   Some([{
  //           rewrite: {
  //             focus: Val(VIDVAL(vid, v)),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // // [101]
  // /* TODO: may want a more coarse-grained traversal, not sure */
  // | [{rewrite: {focus: Val(BASVAL(f)), ctxts: [APPL((), a), ...ctxts]}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: AtExp(a),
  //         ctxts: [APPR(BASVAL(f), ()), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // | [{rewrite: {focus: Val(v), ctxts: [APPR(BASVAL(f), ()), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Val(apply(f, v)),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [102]
  // | [
  //     {rewrite: {focus: Val(FCNCLOSURE(m, e, ve)), ctxts: [APPL((), a), ...ctxts]}, env},
  //     ...frames,
  //   ] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: AtExp(a),
  //         ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // | [
  //     {rewrite: {focus: Val(v), ctxts: [APPR(FCNCLOSURE(m, e, ve), ()), ...ctxts]}, env},
  //     ...frames,
  //   ] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Match(m, v),
  //         ctxts: [],
  //       },
  //       env: recEnv(ve) @ e /* "backwards" compared to spec b/c 4.2 says lookup happens in RHS first */
  //     },
  //     {
  //       rewrite: {
  //         focus: Empty,
  //         ctxts,
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])

  // // [108]
  // | [{rewrite: {focus: Exp(FN(m)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Val(FCNCLOSURE(m, env, [])),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Matches */
  // /* begin Match traversal */
  // | [{rewrite: {focus: Match(MATCH(mr, om), v), ctxts: []}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: MRule(mr, v),
  //             ctxts: [MATCHMR((), om)],
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: Match(m, v), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Match(m, v),
  //         ctxts: [],
  //       },
  //       env,
  //     },
  //     {
  //       rewrite: {
  //         focus: Empty,
  //         ctxts,
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])

  // // [109]
  // /* mrule success */
  // | [{rewrite: {focus: Val(v), ctxts: [MATCHMR((), _), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Val(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [110]
  // | [{rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), None), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [111]
  // | [{rewrite: {focus: FAIL(v), ctxts: [MATCHMR((), Some(m)), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Match(m, v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Match Rules */
  // // [112]
  // | [{rewrite: {focus: MRule(MRULE(p, e), v), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Pat(p, v),
  //             ctxts: [MRULEP((), e), ...ctxts],
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [MRULEP((), e), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Exp(e),
  //             ctxts,
  //           },
  //           env: ve @ env,
  //         }, ...frames])

  // // [113]
  // | [{rewrite: {focus: FAIL(v), ctxts: [MRULEP((), _), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Declarations */
  // // [114ish]: should lift valenv into env
  // | [{rewrite: {focus: Dec(VAL(vb)), ctxts}, env}, ...frames] =>
  //   Js.log("114 in");
  //   Some([{
  //           rewrite: {
  //             focus: ValBind(vb),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // /* Value Bindings */
  // // [124ish]: doesn't support `and`
  // | [{rewrite: {focus: ValBind(PLAIN(p, e, vbs)), ctxts}, env}, ...frames] =>
  //   Js.log("124 in e");
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Exp(e),
  //         ctxts: [VALBINDE(p, (), vbs), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ]);
  // | [{rewrite: {focus: Val(v), ctxts: [VALBINDE(p, (), None), ...ctxts]}, env}, ...frames] =>
  //   Js.log("124 in p");
  //   Some([{
  //           rewrite: {
  //             focus: Pat(p, v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // // [126]
  // | [{rewrite: {focus: ValBind(REC(vb)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ValBind(vb),
  //             ctxts: [RECVB(), ...ctxts],
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [RECVB (), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv(recEnv(ve)),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Type Bindings */
  // /* Datatype Bindings */
  // /* Constructor Bindings */
  // /* Exception Bindings */
  // /* Atomic Patterns */
  // // [132]
  // | [{rewrite: {focus: AtPat(WILDCARD, _), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv([]),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [135-137ish]
  // | [{rewrite: {focus: AtPat(ID(x), v), ctxts}, env}, ...frames] =>
  //   switch (Util.lookupOne(x, env)) {
  //   // [135]
  //   | None
  //   | Some((_, Var)) =>
  //     Some([{
  //             rewrite: {
  //               focus: ValEnv([(x, (v, Var))]),
  //               ctxts,
  //             },
  //             env,
  //           }, ...frames])
  //   // [136]
  //   | Some((v', id)) when v == v' =>
  //     Some([{
  //             rewrite: {
  //               focus: ValEnv([]),
  //               ctxts,
  //             },
  //             env,
  //           }, ...frames])
  //   // [137]
  //   | Some((v', id)) => Some([{
  //                                rewrite: {
  //                                  focus: FAIL(v),
  //                                  ctxts,
  //                                },
  //                                env,
  //                              }, ...frames])
  //   }

  // // [138]
  // /* empty record pat */
  // /* TODO: special-casing RECORD(None) may be overkill. not sure */
  // | [{rewrite: {focus: AtPat(RECORD(None), RECORD([])), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv([]),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: AtPat(RECORD(None), v), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // /* start non-empty record pat */
  // | [{rewrite: {focus: AtPat(RECORD(Some(pr)), RECORD(r)), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: PatRow(pr, r, []),
  //         ctxts: [RECORDPR(), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // /* complete non-empty record pat */
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [RECORDPR (), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv(ve),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: FAIL(v), ctxts: [RECORDPR (), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // // [139]
  // | [{rewrite: {focus: AtPat(PAR(p), v), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Pat(p, v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* Pattern Rows */
  // // [140]
  // | [{rewrite: {focus: PatRow(DOTS, _, rve), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: ValEnv(rve |> List.map(((_, ve)) => ve) |> List.flatten),
  //         ctxts,
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])

  // // [141-142]
  // /* NOTE: SML '97 says each field should be evaluated in the original environment, but we extend it
  //    after every field. This simplifies our implementation since we don't need to maintain a
  //    temporary environment outside of `env`. This still agrees with SML '97 thanks to the
  //    left-linear pattern restriction. */
  // /* start visiting */
  // | [{rewrite: {focus: PatRow(FIELD(l, p, opr), r, ve), ctxts}, env}, ...frames] =>
  //   /* NOTE: Shouldn't fail for well-typed programs per SML '97 comments. */
  //   let Some(v) = Util.lookupOne(l, r);
  //   Some([
  //     {
  //       rewrite: {
  //         focus: Pat(p, v),
  //         ctxts: [FIELDP((l, (), opr), r, ve), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ]);
  // // [141]
  // | [
  //     {rewrite: {focus: FAIL(v), ctxts: [FIELDP((_, (), _), _, _), ...ctxts]}, env},
  //     ...frames,
  //   ] =>
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // // [142]
  // | [
  //     {rewrite: {focus: ValEnv(ve), ctxts: [FIELDP((_, (), None), _, rve), ...ctxts]}, env},
  //     ...frames,
  //   ] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: ValEnv(ve @ (rve |> List.map(((_, ve)) => ve) |> List.flatten)),
  //         ctxts,
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // /* TODO: need to propagate ValEnv through */
  // | [
  //     {
  //       rewrite: {focus: ValEnv(ve), ctxts: [FIELDP((l, (), Some(pr)), r, rve), ...ctxts]},
  //       env,
  //     },
  //     ...frames,
  //   ] =>
  //   Some([{
  //           rewrite: {
  //             focus: PatRow(pr, r, [(l, ve), ...rve]),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // /* Patterns */
  // // [143]
  // | [{rewrite: {focus: Pat(ATPAT(ap), v), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: AtPat(ap, v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* TODO: maybe consolidate 145a and b somehow? */
  // | [{rewrite: {focus: Pat(CON(con, ap), VIDVAL(vid, v)), ctxts}, env}, ...frames] =>
  //   let Some((VID(vidC), Con)) = Util.lookupOne(con, env);
  //   if (vidC == vid) {
  //     // [144]: ignores ref check
  //     Js.log("144");
  //     Js.log(con);
  //     Js.log(ap);
  //     Some([{
  //             rewrite: {
  //               focus: AtPat(ap, v),
  //               ctxts,
  //             },
  //             env,
  //           }, ...frames]);
  //   } else {
  //     // [145a]
  //     Js.log("145a");
  //     Some([{
  //             rewrite: {
  //               focus: FAIL(VIDVAL(vid, v)),
  //               ctxts,
  //             },
  //             env,
  //           }, ...frames]);
  //   };

  // // [145b]
  // | [{rewrite: {focus: Pat(CON(_, _), v), ctxts}, env}, ...frames] =>
  //   Js.log("145b");
  //   Some([{
  //           rewrite: {
  //             focus: FAIL(v),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);

  // /* ... */
  // /* Structure-level Declarations */
  // // [156]
  // | [{rewrite: {focus: StrDec(DEC(d)), ctxts}, env}, ...frames] =>
  //   Js.log("156 in");
  //   Some([{
  //           rewrite: {
  //             focus: Dec(d),
  //             ctxts: [DECD(), ...ctxts],
  //           },
  //           env,
  //         }, ...frames]);
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [DECD (), ...ctxts]}, env}, ...frames] =>
  //   Js.log("156 out");
  //   Some([{
  //           rewrite: {
  //             focus: ValEnv(ve),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames]);
  // // [160]
  // | [{rewrite: {focus: StrDec(SEQ(sd1, sd2)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: StrDec(sd1),
  //             ctxts: [SEQL((), sd2), ...ctxts],
  //           },
  //           env,
  //         }, ...frames])
  // /* TODO: propagate ValEnv */
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [SEQL((), sd2), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: StrDec(sd2),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])

  // /* ... */

  // /* Top-level Declarations */
  // // [184ish]
  // | [{rewrite: {focus: TopDec(STRDEC(sd, otd)), ctxts}, env}, ...frames] =>
  //   Js.log("184 in");
  //   Some([
  //     {
  //       rewrite: {
  //         focus: StrDec(sd),
  //         ctxts: [STRDECSD((), otd), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ]);
  // | [{rewrite: {focus: ValEnv(ve), ctxts: [STRDECSD((), td), ...ctxts]}, env}, ...frames] =>
  //   Js.log("184 out");
  //   Some([
  //     {
  //       rewrite: {
  //         focus:
  //           switch (td) {
  //           | None => Empty
  //           | Some(td) => TopDec(td)
  //           },
  //         ctxts,
  //       },
  //       env: ve @ env,
  //     },
  //     ...frames,
  //   ]);

  // /* Programs */
  // // [189ish]
  // | [{rewrite: {focus: Program(PROGRAM(td, None)), ctxts}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: TopDec(td),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
  // | [{rewrite: {focus: Program(PROGRAM(td, Some(p))), ctxts}, env}, ...frames] =>
  //   Some([
  //     {
  //       rewrite: {
  //         focus: TopDec(td),
  //         ctxts: [PROGRAML((), p), ...ctxts],
  //       },
  //       env,
  //     },
  //     ...frames,
  //   ])
  // | [{rewrite: {focus: Empty, ctxts: [PROGRAML((), p), ...ctxts]}, env}, ...frames] =>
  //   Some([{
  //           rewrite: {
  //             focus: Program(p),
  //             ctxts,
  //           },
  //           env,
  //         }, ...frames])
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
  },
];

let interpretTraceBounded = (~maxDepth=100, p) =>
  TheiaUtil.takeWhileInclusive(
    c => !isFinal(c),
    TheiaUtil.iterateMaybeMaxDepth(maxDepth, step, inject(p)),
  );
let interpretTrace = p =>
  TheiaUtil.takeWhileInclusive(c => !isFinal(c), TheiaUtil.iterateMaybe(step, inject(p)));