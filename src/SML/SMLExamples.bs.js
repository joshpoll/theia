'use strict';

var Block = require("bs-platform/lib/js/block.js");

var ex0 = "\n{\"node\": \"Program\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 2 }, \"args\": [\n  {\"node\": \"STRDECTopDec\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n    {\"node\": \"DECStrDec\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n      {\"node\": \"VALDec\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n        {\"node\": \"Seq\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n        ]}\n,        {\"node\": \"PLAINValBind\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n          {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n            {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n              {\"node\": \"LongVId\", \"args\": [\"it\"]}\n            ]}\n          ]}\n,          {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n            {\"node\": \"SCONAtExp\", \"sourceMap\": { \"file\": \"ex0.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n              {\"node\": \"INTSCon\", \"args\": [5]}\n            ]}\n          ]}\n,null        ]}\n      ]}\n    ]}\n,null  ]}\n,null]}\n";

var ex1 = "\n{\"node\": \"Program\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 4 }, \"args\": [\n  {\"node\": \"STRDECTopDec\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n    {\"node\": \"DECStrDec\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n      {\"node\": \"VALDec\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n        {\"node\": \"Seq\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n        ]}\n,        {\"node\": \"PLAINValBind\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n          {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n            {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n              {\"node\": \"LongVId\", \"args\": [\"it\"]}\n            ]}\n          ]}\n,          {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n            {\"node\": \"LETAtExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 5, \"col2\": 3 }, \"args\": [\n              {\"node\": \"VALDec\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 2, \"line2\": 3, \"col2\": 0 }, \"args\": [\n                {\"node\": \"Seq\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 3, \"col1\": 0, \"line2\": 3, \"col2\": 0 }, \"args\": [\n                ]}\n,                {\"node\": \"PLAINValBind\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 6, \"line2\": 3, \"col2\": 0 }, \"args\": [\n                  {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 6, \"line2\": 2, \"col2\": 7 }, \"args\": [\n                    {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 6, \"line2\": 2, \"col2\": 7 }, \"args\": [\n                      {\"node\": \"LongVId\", \"args\": [\"x\"]}\n                    ]}\n                  ]}\n,                  {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 10, \"line2\": 2, \"col2\": 11 }, \"args\": [\n                    {\"node\": \"SCONAtExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 2, \"col1\": 10, \"line2\": 2, \"col2\": 11 }, \"args\": [\n                      {\"node\": \"INTSCon\", \"args\": [5]}\n                    ]}\n                  ]}\n,null                ]}\n              ]}\n,              {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 4, \"col1\": 2, \"line2\": 4, \"col2\": 3 }, \"args\": [\n                {\"node\": \"IDAtExp\", \"sourceMap\": { \"file\": \"ex1.sml\", \"line1\": 4, \"col1\": 2, \"line2\": 4, \"col2\": 3 }, \"args\": [\n                  {\"node\": \"LongVId\", \"args\": [\"x\"]}\n                ]}\n              ]}\n            ]}\n          ]}\n,null        ]}\n      ]}\n    ]}\n,null  ]}\n,null]}\n";

var ex2 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
              /* ATPAT */[/* ID */["x"]],
              /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[34]])]),
              undefined
            ]]]),
      undefined
    ]]);

var ex3 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* SEQ */Block.__(1, [
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["x"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[34]])]),
                  undefined
                ]]]),
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["y"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[17]])]),
                  undefined
                ]]])
        ]),
      undefined
    ]]);

var ex4 = /* AtExp */Block.__(0, [/* RECORD */Block.__(2, [undefined])]);

var ex5 = /* AtExp */Block.__(0, [/* RECORD */Block.__(2, [/* EXPROW */[
          "1",
          /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[5]])]),
          undefined
        ]])]);

var ex6 = /* AtExp */Block.__(0, [/* RECORD */Block.__(2, [/* EXPROW */[
          "1",
          /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[5]])]),
          /* EXPROW */[
            "2",
            /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[78]])]),
            undefined
          ]
        ]])]);

var ex7 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* SEQ */Block.__(1, [
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["x"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[34]])]),
                  undefined
                ]]]),
          /* SEQ */Block.__(1, [
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["y"]],
                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[17]])]),
                      undefined
                    ]]]),
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["z"]],
                      /* APP */Block.__(1, [
                          /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                          /* RECORD */Block.__(2, [/* EXPROW */[
                                "1",
                                /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[5]])]),
                                /* EXPROW */[
                                  "2",
                                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[78]])]),
                                  undefined
                                ]
                              ]])
                        ]),
                      undefined
                    ]]])
            ])
        ]),
      undefined
    ]]);

var ex8 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* SEQ */Block.__(1, [
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["x"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[34]])]),
                  undefined
                ]]]),
          /* SEQ */Block.__(1, [
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["y"]],
                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[17]])]),
                      undefined
                    ]]]),
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["z"]],
                      /* APP */Block.__(1, [
                          /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                          /* RECORD */Block.__(2, [/* EXPROW */[
                                "1",
                                /* ATEXP */Block.__(0, [/* PAR */Block.__(4, [/* APP */Block.__(1, [
                                            /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                                            /* RECORD */Block.__(2, [/* EXPROW */[
                                                  "1",
                                                  /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["x"])]),
                                                  /* EXPROW */[
                                                    "2",
                                                    /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["y"])]),
                                                    undefined
                                                  ]
                                                ]])
                                          ])])]),
                                /* EXPROW */[
                                  "2",
                                  /* ATEXP */Block.__(0, [/* PAR */Block.__(4, [/* APP */Block.__(1, [
                                              /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                                              /* RECORD */Block.__(2, [/* EXPROW */[
                                                    "1",
                                                    /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["y"])]),
                                                    /* EXPROW */[
                                                      "2",
                                                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[2]])]),
                                                      undefined
                                                    ]
                                                  ]])
                                            ])])]),
                                  undefined
                                ]
                              ]])
                        ]),
                      undefined
                    ]]])
            ])
        ]),
      undefined
    ]]);

var ex9 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* SEQ */Block.__(1, [
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["x"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[34]])]),
                  undefined
                ]]]),
          /* SEQ */Block.__(1, [
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["y"]],
                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[17]])]),
                      undefined
                    ]]]),
              /* SEQ */Block.__(1, [
                  /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                          /* ATPAT */[/* ID */["z"]],
                          /* APP */Block.__(1, [
                              /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                              /* RECORD */Block.__(2, [/* EXPROW */[
                                    "1",
                                    /* ATEXP */Block.__(0, [/* PAR */Block.__(4, [/* APP */Block.__(1, [
                                                /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                                                /* RECORD */Block.__(2, [/* EXPROW */[
                                                      "1",
                                                      /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["x"])]),
                                                      /* EXPROW */[
                                                        "2",
                                                        /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["y"])]),
                                                        undefined
                                                      ]
                                                    ]])
                                              ])])]),
                                    /* EXPROW */[
                                      "2",
                                      /* ATEXP */Block.__(0, [/* PAR */Block.__(4, [/* APP */Block.__(1, [
                                                  /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                                                  /* RECORD */Block.__(2, [/* EXPROW */[
                                                        "1",
                                                        /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["y"])]),
                                                        /* EXPROW */[
                                                          "2",
                                                          /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[2]])]),
                                                          undefined
                                                        ]
                                                      ]])
                                                ])])]),
                                      undefined
                                    ]
                                  ]])
                            ]),
                          undefined
                        ]]]),
                  /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                          /* ATPAT */[/* ID */["q"]],
                          /* APP */Block.__(1, [
                              /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["+"])]),
                              /* RECORD */Block.__(2, [/* EXPROW */[
                                    "1",
                                    /* ATEXP */Block.__(0, [/* ID */Block.__(1, ["z"])]),
                                    /* EXPROW */[
                                      "2",
                                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[1]])]),
                                      undefined
                                    ]
                                  ]])
                            ]),
                          undefined
                        ]]])
                ])
            ])
        ]),
      undefined
    ]]);

var ex10 = /* TopDec */Block.__(6, [/* STRDEC */[
      /* SEQ */Block.__(1, [
          /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                  /* ATPAT */[/* ID */["a"]],
                  /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[1]])]),
                  undefined
                ]]]),
          /* SEQ */Block.__(1, [
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["b"]],
                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[2]])]),
                      undefined
                    ]]]),
              /* DEC */Block.__(0, [/* VAL */[/* PLAIN */[
                      /* ATPAT */[/* ID */["a"]],
                      /* ATEXP */Block.__(0, [/* SCON */Block.__(0, [/* INT */[3]])]),
                      undefined
                    ]]])
            ])
        ]),
      undefined
    ]]);

var exITE = "\n{\"node\": \"Program\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 22 }, \"args\": [\n  {\"node\": \"STRDECTopDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 21 }, \"args\": [\n    {\"node\": \"DECStrDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 21 }, \"args\": [\n      {\"node\": \"VALDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 21 }, \"args\": [\n        {\"node\": \"Seq\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n        ]}\n,        {\"node\": \"PLAINValBind\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 21 }, \"args\": [\n          {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n            {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 1 }, \"args\": [\n              {\"node\": \"LongVId\", \"args\": [\"it\"]}\n            ]}\n          ]}\n,          {\"node\": \"APPExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 21 }, \"args\": [\n            {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 21 }, \"args\": [\n              {\"node\": \"PARAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                {\"node\": \"FNExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                  {\"node\": \"Match\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                    {\"node\": \"Mrule\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 14 }, \"args\": [\n                      {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 14 }, \"args\": [\n                        {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 14 }, \"args\": [\n                          {\"node\": \"LongVId\", \"args\": [\"true\"]}\n                        ]}\n                      ]}\n,                      {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 14 }, \"args\": [\n                        {\"node\": \"SCONAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 13, \"line2\": 1, \"col2\": 14 }, \"args\": [\n                          {\"node\": \"INTSCon\", \"args\": [1]}\n                        ]}\n                      ]}\n                    ]}\n,                    {\"node\": \"Match\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                      {\"node\": \"Mrule\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                        {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                          {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                            {\"node\": \"LongVId\", \"args\": [\"false\"]}\n                          ]}\n                        ]}\n,                        {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                          {\"node\": \"SCONAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 20, \"line2\": 1, \"col2\": 21 }, \"args\": [\n                            {\"node\": \"INTSCon\", \"args\": [2]}\n                          ]}\n                        ]}\n                      ]}\n,null                    ]}\n                  ]}\n                ]}\n              ]}\n            ]}\n,            {\"node\": \"PARAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 3, \"line2\": 1, \"col2\": 7 }, \"args\": [\n              {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 3, \"line2\": 1, \"col2\": 7 }, \"args\": [\n                {\"node\": \"IDAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/ite.sml\", \"line1\": 1, \"col1\": 3, \"line2\": 1, \"col2\": 7 }, \"args\": [\n                  {\"node\": \"LongVId\", \"args\": [\"true\"]}\n                ]}\n              ]}\n            ]}\n          ]}\n,null        ]}\n      ]}\n    ]}\n,null  ]}\n,null]}\n";

var exId = "\n{\"node\": \"Program\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 13 }, \"args\": [\n  {\"node\": \"STRDECTopDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 12 }, \"args\": [\n    {\"node\": \"DECStrDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 12 }, \"args\": [\n      {\"node\": \"VALDec\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 0, \"line2\": 1, \"col2\": 12 }, \"args\": [\n        {\"node\": \"Seq\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 12, \"line2\": 1, \"col2\": 12 }, \"args\": [\n        ]}\n,        {\"node\": \"RECValBind\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 4, \"line2\": 1, \"col2\": 12 }, \"args\": [\n          {\"node\": \"PLAINValBind\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 4, \"line2\": 1, \"col2\": 12 }, \"args\": [\n            {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 4, \"line2\": 1, \"col2\": 6 }, \"args\": [\n              {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 4, \"line2\": 1, \"col2\": 6 }, \"args\": [\n                {\"node\": \"LongVId\", \"args\": [\"id\"]}\n              ]}\n            ]}\n,            {\"node\": \"FNExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n              {\"node\": \"Match\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                {\"node\": \"Mrule\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                  {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                    {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                      {\"node\": \"LongVId\", \"args\": [\"_id10576\"]}\n                    ]}\n                  ]}\n,                  {\"node\": \"APPExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                    {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                      {\"node\": \"PARAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                        {\"node\": \"FNExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                          {\"node\": \"Match\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                            {\"node\": \"Mrule\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                              {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                                {\"node\": \"PARAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                                  {\"node\": \"ATPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                                    {\"node\": \"IDAtPat\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                                      {\"node\": \"LongVId\", \"args\": [\"x\"]}\n                                    ]}\n                                  ]}\n                                ]}\n                              ]}\n,                              {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 11, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                                {\"node\": \"IDAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 11, \"line2\": 1, \"col2\": 12 }, \"args\": [\n                                  {\"node\": \"LongVId\", \"args\": [\"x\"]}\n                                ]}\n                              ]}\n                            ]}\n,null                          ]}\n                        ]}\n                      ]}\n                    ]}\n,                    {\"node\": \"PARAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                      {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                        {\"node\": \"PARAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                          {\"node\": \"ATExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                            {\"node\": \"IDAtExp\", \"sourceMap\": { \"file\": \"../theia/src/SML/examples/id.sml\", \"line1\": 1, \"col1\": 7, \"line2\": 1, \"col2\": 8 }, \"args\": [\n                              {\"node\": \"LongVId\", \"args\": [\"_id10576\"]}\n                            ]}\n                          ]}\n                        ]}\n                      ]}\n                    ]}\n                  ]}\n                ]}\n,null              ]}\n            ]}\n,null          ]}\n        ]}\n      ]}\n    ]}\n,null  ]}\n,null]}\n";

exports.ex0 = ex0;
exports.ex1 = ex1;
exports.ex2 = ex2;
exports.ex3 = ex3;
exports.ex4 = ex4;
exports.ex5 = ex5;
exports.ex6 = ex6;
exports.ex7 = ex7;
exports.ex8 = ex8;
exports.ex9 = ex9;
exports.ex10 = ex10;
exports.exITE = exITE;
exports.exId = exId;
/* No side effect */
