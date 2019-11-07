open SML;

/* example "programs" */
/* 5 */
// let ex0 = AtExp(SCON(INT(5)));
let ex0 = {|
{"node": "Program", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 2 }, "args": [
  {"node": "STRDECTopDec", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
    {"node": "DECStrDec", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
      {"node": "VALDec", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
        {"node": "Seq", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
        ]}
,        {"node": "PLAINValBind", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
          {"node": "ATPat", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
            {"node": "IDAtPat", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
              {"node": "LongVId", "args": ["it"]}
            ]}
          ]}
,          {"node": "ATExp", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
            {"node": "SCONAtExp", "sourceMap": { "file": "ex0.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
              {"node": "INTSCon", "args": [5]}
            ]}
          ]}
,null        ]}
      ]}
    ]}
,null  ]}
,null]}
|};
/* let val x = 5 in x end */
// let ex1 =
//   AtExp(LET(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(5))), None)), ATEXP(ID("x"))));
let ex1 = {|
{"node": "Program", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 4 }, "args": [
  {"node": "STRDECTopDec", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
    {"node": "DECStrDec", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
      {"node": "VALDec", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
        {"node": "Seq", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
        ]}
,        {"node": "PLAINValBind", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
          {"node": "ATPat", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
            {"node": "IDAtPat", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
              {"node": "LongVId", "args": ["it"]}
            ]}
          ]}
,          {"node": "ATExp", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
            {"node": "LETAtExp", "sourceMap": { "file": "ex1.sml", "line1": 1, "col1": 0, "line2": 5, "col2": 3 }, "args": [
              {"node": "VALDec", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 2, "line2": 3, "col2": 0 }, "args": [
                {"node": "Seq", "sourceMap": { "file": "ex1.sml", "line1": 3, "col1": 0, "line2": 3, "col2": 0 }, "args": [
                ]}
,                {"node": "PLAINValBind", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 6, "line2": 3, "col2": 0 }, "args": [
                  {"node": "ATPat", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 6, "line2": 2, "col2": 7 }, "args": [
                    {"node": "IDAtPat", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 6, "line2": 2, "col2": 7 }, "args": [
                      {"node": "LongVId", "args": ["x"]}
                    ]}
                  ]}
,                  {"node": "ATExp", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 10, "line2": 2, "col2": 11 }, "args": [
                    {"node": "SCONAtExp", "sourceMap": { "file": "ex1.sml", "line1": 2, "col1": 10, "line2": 2, "col2": 11 }, "args": [
                      {"node": "INTSCon", "args": [5]}
                    ]}
                  ]}
,null                ]}
              ]}
,              {"node": "ATExp", "sourceMap": { "file": "ex1.sml", "line1": 4, "col1": 2, "line2": 4, "col2": 3 }, "args": [
                {"node": "IDAtExp", "sourceMap": { "file": "ex1.sml", "line1": 4, "col1": 2, "line2": 4, "col2": 3 }, "args": [
                  {"node": "LongVId", "args": ["x"]}
                ]}
              ]}
            ]}
          ]}
,null        ]}
      ]}
    ]}
,null  ]}
,null]}
|};
/* val x = 34 */
let ex2 =
  TopDec(STRDEC(DEC(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(34))), None))), None));
/* val x = 34; val y = 17 */
let ex3 =
  TopDec(
    STRDEC(
      SEQ(
        DEC(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(34))), None))),
        DEC(VAL(PLAIN(ATPAT(ID("y")), ATEXP(SCON(INT(17))), None))),
      ),
      None,
    ),
  );

/* {} () */
let ex4 = AtExp(RECORD(None));
/* { 1=5 } (5,) */
let ex5 = AtExp(RECORD(Some({lab: "1", exp: ATEXP(SCON(INT(5))), rest: None})));
/* { 1=5, 2=78 } (5, 78) */
let ex6 =
  AtExp(
    RECORD(
      Some({
        lab: "1",
        exp: ATEXP(SCON(INT(5))),
        rest: Some({lab: "2", exp: ATEXP(SCON(INT(78))), rest: None}),
      }),
    ),
  );

/* TODO: no syntax sugar for records -> tuples or infix ops
     val x = 34;
     val y = 17;
     val z = + { 1=5, 2=78 }
   */
let ex7 =
  TopDec(
    STRDEC(
      SEQ(
        DEC(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(34))), None))),
        SEQ(
          DEC(VAL(PLAIN(ATPAT(ID("y")), ATEXP(SCON(INT(17))), None))),
          DEC(
            VAL(
              PLAIN(
                ATPAT(ID("z")),
                APP(
                  ATEXP(ID("+")),
                  RECORD(
                    Some({
                      lab: "1",
                      exp: ATEXP(SCON(INT(5))),
                      rest: Some({lab: "2", exp: ATEXP(SCON(INT(78))), rest: None}),
                    }),
                  ),
                ),
                None,
              ),
            ),
          ),
        ),
      ),
      None,
    ),
  );

/*
   val x = 34;
   val y = 17;
   val z = (x + y) + (y + 2)
 */
let ex8 =
  TopDec(
    STRDEC(
      SEQ(
        DEC(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(34))), None))),
        SEQ(
          DEC(VAL(PLAIN(ATPAT(ID("y")), ATEXP(SCON(INT(17))), None))),
          DEC(
            VAL(
              PLAIN(
                ATPAT(ID("z")),
                APP(
                  ATEXP(ID("+")),
                  RECORD(
                    Some({
                      lab: "1",
                      exp:
                        ATEXP(
                          PARA(
                            APP(
                              ATEXP(ID("+")),
                              RECORD(
                                Some({
                                  lab: "1",
                                  exp: ATEXP(ID("x")),
                                  rest: Some({lab: "2", exp: ATEXP(ID("y")), rest: None}),
                                }),
                              ),
                            ),
                          ),
                        ),
                      rest:
                        Some({
                          lab: "2",
                          exp:
                            ATEXP(
                              PARA(
                                APP(
                                  ATEXP(ID("+")),
                                  RECORD(
                                    Some({
                                      lab: "1",
                                      exp: ATEXP(ID("y")),
                                      rest:
                                        Some({lab: "2", exp: ATEXP(SCON(INT(2))), rest: None}),
                                    }),
                                  ),
                                ),
                              ),
                            ),
                          rest: None,
                        }),
                    }),
                  ),
                ),
                None,
              ),
            ),
          ),
        ),
      ),
      None,
    ),
  );

/*
   val x = 34;
   val y = 17;
   val z = (x + y) + (y + 2);
   val q = z + 1
 */
let ex9 =
  TopDec(
    STRDEC(
      SEQ(
        DEC(VAL(PLAIN(ATPAT(ID("x")), ATEXP(SCON(INT(34))), None))),
        SEQ(
          DEC(VAL(PLAIN(ATPAT(ID("y")), ATEXP(SCON(INT(17))), None))),
          SEQ(
            DEC(
              VAL(
                PLAIN(
                  ATPAT(ID("z")),
                  APP(
                    ATEXP(ID("+")),
                    RECORD(
                      Some({
                        lab: "1",
                        exp:
                          ATEXP(
                            PARA(
                              APP(
                                ATEXP(ID("+")),
                                RECORD(
                                  Some({
                                    lab: "1",
                                    exp: ATEXP(ID("x")),
                                    rest: Some({lab: "2", exp: ATEXP(ID("y")), rest: None}),
                                  }),
                                ),
                              ),
                            ),
                          ),
                        rest:
                          Some({
                            lab: "2",
                            exp:
                              ATEXP(
                                PARA(
                                  APP(
                                    ATEXP(ID("+")),
                                    RECORD(
                                      Some({
                                        lab: "1",
                                        exp: ATEXP(ID("y")),
                                        rest:
                                          Some({
                                            lab: "2",
                                            exp: ATEXP(SCON(INT(2))),
                                            rest: None,
                                          }),
                                      }),
                                    ),
                                  ),
                                ),
                              ),
                            rest: None,
                          }),
                      }),
                    ),
                  ),
                  None,
                ),
              ),
            ),
            DEC(
              VAL(
                PLAIN(
                  ATPAT(ID("q")),
                  APP(
                    ATEXP(ID("+")),
                    RECORD(
                      Some({
                        lab: "1",
                        exp: ATEXP(ID("z")),
                        rest: Some({lab: "2", exp: ATEXP(SCON(INT(1))), rest: None}),
                      }),
                    ),
                  ),
                  None,
                ),
              ),
            ),
          ),
        ),
      ),
      None,
    ),
  );

let ex10 =
  TopDec(
    STRDEC(
      SEQ(
        DEC(VAL(PLAIN(ATPAT(ID("a")), ATEXP(SCON(INT(1))), None))),
        SEQ(
          DEC(VAL(PLAIN(ATPAT(ID("b")), ATEXP(SCON(INT(2))), None))),
          DEC(VAL(PLAIN(ATPAT(ID("a")), ATEXP(SCON(INT(3))), None))),
        ),
      ),
      None,
    ),
  );