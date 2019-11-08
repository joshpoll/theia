open SML;

let ex0 = "5";

let ex1 = "let val x = 5 in x end";

let ex2 = "val x = 34";

let ex3 = "val x = 34;
val y = 17";

let ex4 = "()";

let ex5 = "(5, 78)";

let ex6 = "val x = 34;
val y = 17;
val z = 5 + 78";

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
                    Some(
                      EXPROW(
                        "1",
                        ATEXP(SCON(INT(5))),
                        Some(EXPROW("2", ATEXP(SCON(INT(78))), None)),
                      ),
                    ),
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
                    Some(
                      EXPROW(
                        "1",
                        ATEXP(
                          PAR(
                            APP(
                              ATEXP(ID("+")),
                              RECORD(
                                Some(
                                  EXPROW(
                                    "1",
                                    ATEXP(ID("x")),
                                    Some(EXPROW("2", ATEXP(ID("y")), None)),
                                  ),
                                ),
                              ),
                            ),
                          ),
                        ),
                        Some(
                          EXPROW(
                            "2",
                            ATEXP(
                              PAR(
                                APP(
                                  ATEXP(ID("+")),
                                  RECORD(
                                    Some(
                                      EXPROW(
                                        "1",
                                        ATEXP(ID("y")),
                                        Some(EXPROW("2", ATEXP(SCON(INT(2))), None)),
                                      ),
                                    ),
                                  ),
                                ),
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
                      Some(
                        EXPROW(
                          "1",
                          ATEXP(
                            PAR(
                              APP(
                                ATEXP(ID("+")),
                                RECORD(
                                  Some(
                                    EXPROW(
                                      "1",
                                      ATEXP(ID("x")),
                                      Some(EXPROW("2", ATEXP(ID("y")), None)),
                                    ),
                                  ),
                                ),
                              ),
                            ),
                          ),
                          Some(
                            EXPROW(
                              "2",
                              ATEXP(
                                PAR(
                                  APP(
                                    ATEXP(ID("+")),
                                    RECORD(
                                      Some(
                                        EXPROW(
                                          "1",
                                          ATEXP(ID("y")),
                                          Some(EXPROW("2", ATEXP(SCON(INT(2))), None)),
                                        ),
                                      ),
                                    ),
                                  ),
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
              ),
            ),
            DEC(
              VAL(
                PLAIN(
                  ATPAT(ID("q")),
                  APP(
                    ATEXP(ID("+")),
                    RECORD(
                      Some(
                        EXPROW(
                          "1",
                          ATEXP(ID("z")),
                          Some(EXPROW("2", ATEXP(SCON(INT(1))), None)),
                        ),
                      ),
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

let exITE = {|
{"node": "Program", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 22 }, "args": [
  {"node": "STRDECTopDec", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 21 }, "args": [
    {"node": "DECStrDec", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 21 }, "args": [
      {"node": "VALDec", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 21 }, "args": [
        {"node": "Seq", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
        ]}
,        {"node": "PLAINValBind", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 21 }, "args": [
          {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
            {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 1 }, "args": [
              {"node": "LongVId", "args": ["it"]}
            ]}
          ]}
,          {"node": "APPExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 21 }, "args": [
            {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 21 }, "args": [
              {"node": "PARAtExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 21 }, "args": [
                {"node": "FNExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 21 }, "args": [
                  {"node": "Match", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 21 }, "args": [
                    {"node": "Mrule", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 14 }, "args": [
                      {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 14 }, "args": [
                        {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 14 }, "args": [
                          {"node": "LongVId", "args": ["true"]}
                        ]}
                      ]}
,                      {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 14 }, "args": [
                        {"node": "SCONAtExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 13, "line2": 1, "col2": 14 }, "args": [
                          {"node": "INTSCon", "args": [1]}
                        ]}
                      ]}
                    ]}
,                    {"node": "Match", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                      {"node": "Mrule", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                        {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                          {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                            {"node": "LongVId", "args": ["false"]}
                          ]}
                        ]}
,                        {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                          {"node": "SCONAtExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 20, "line2": 1, "col2": 21 }, "args": [
                            {"node": "INTSCon", "args": [2]}
                          ]}
                        ]}
                      ]}
,null                    ]}
                  ]}
                ]}
              ]}
            ]}
,            {"node": "PARAtExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 3, "line2": 1, "col2": 7 }, "args": [
              {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 3, "line2": 1, "col2": 7 }, "args": [
                {"node": "IDAtExp", "sourceMap": { "file": "../theia/src/SML/examples/ite.sml", "line1": 1, "col1": 3, "line2": 1, "col2": 7 }, "args": [
                  {"node": "LongVId", "args": ["true"]}
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

let exId = {|
{"node": "Program", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 13 }, "args": [
  {"node": "STRDECTopDec", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 12 }, "args": [
    {"node": "DECStrDec", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 12 }, "args": [
      {"node": "VALDec", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 0, "line2": 1, "col2": 12 }, "args": [
        {"node": "Seq", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 12, "line2": 1, "col2": 12 }, "args": [
        ]}
,        {"node": "RECValBind", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 4, "line2": 1, "col2": 12 }, "args": [
          {"node": "PLAINValBind", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 4, "line2": 1, "col2": 12 }, "args": [
            {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 4, "line2": 1, "col2": 6 }, "args": [
              {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 4, "line2": 1, "col2": 6 }, "args": [
                {"node": "LongVId", "args": ["id"]}
              ]}
            ]}
,            {"node": "FNExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
              {"node": "Match", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                {"node": "Mrule", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                  {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                    {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                      {"node": "LongVId", "args": ["_id10576"]}
                    ]}
                  ]}
,                  {"node": "APPExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                    {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                      {"node": "PARAtExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                        {"node": "FNExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                          {"node": "Match", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                            {"node": "Mrule", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 12 }, "args": [
                              {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                                {"node": "PARAtPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                                  {"node": "ATPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                                    {"node": "IDAtPat", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                                      {"node": "LongVId", "args": ["x"]}
                                    ]}
                                  ]}
                                ]}
                              ]}
,                              {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 11, "line2": 1, "col2": 12 }, "args": [
                                {"node": "IDAtExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 11, "line2": 1, "col2": 12 }, "args": [
                                  {"node": "LongVId", "args": ["x"]}
                                ]}
                              ]}
                            ]}
,null                          ]}
                        ]}
                      ]}
                    ]}
,                    {"node": "PARAtExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                      {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                        {"node": "PARAtExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                          {"node": "ATExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                            {"node": "IDAtExp", "sourceMap": { "file": "../theia/src/SML/examples/id.sml", "line1": 1, "col1": 7, "line2": 1, "col2": 8 }, "args": [
                              {"node": "LongVId", "args": ["_id10576"]}
                            ]}
                          ]}
                        ]}
                      ]}
                    ]}
                  ]}
                ]}
,null              ]}
            ]}
,null          ]}
        ]}
      ]}
    ]}
,null  ]}
,null]}
|};