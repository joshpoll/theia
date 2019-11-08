'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var React = require("react");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function compileSCon(sc) {
  return /* Atom */Block.__(0, [String(sc[0])]);
}

function compileAtExp(a) {
  switch (a.tag | 0) {
    case /* SCON */0 :
        return compileSCon(a[0]);
    case /* ID */1 :
        return /* Atom */Block.__(0, [a[0]]);
    case /* RECORD */2 :
        var match = a[0];
        if (match !== undefined) {
          return /* Apply2 */Block.__(1, [
                    /* :: */[
                      "{",
                      /* :: */[
                        "}",
                        /* [] */0
                      ]
                    ],
                    /* :: */[
                      compileExpRow(match),
                      /* [] */0
                    ]
                  ]);
        } else {
          return /* Atom */Block.__(0, ["()"]);
        }
    case /* LET */3 :
        return /* Apply2 */Block.__(1, [
                  /* :: */[
                    "let ",
                    /* :: */[
                      " in ",
                      /* :: */[
                        " end",
                        /* [] */0
                      ]
                    ]
                  ],
                  /* :: */[
                    compileDec(a[0]),
                    /* :: */[
                      compileExp(a[1]),
                      /* [] */0
                    ]
                  ]
                ]);
    case /* PAR */4 :
        return /* Apply2 */Block.__(1, [
                  /* :: */[
                    "(",
                    /* :: */[
                      ")",
                      /* [] */0
                    ]
                  ],
                  /* :: */[
                    compileExp(a[0]),
                    /* [] */0
                  ]
                ]);
    
  }
}

function compileValBind(vb) {
  if (vb[2] !== undefined) {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "SMLToTheiaIR.re",
            65,
            2
          ]
        ];
  }
  return /* Apply2 */Block.__(1, [
            /* :: */[
              React.createElement(React.Fragment, undefined),
              /* :: */[
                " = ",
                /* :: */[
                  React.createElement(React.Fragment, undefined),
                  /* [] */0
                ]
              ]
            ],
            /* :: */[
              compileAtPat(vb[0][0]),
              /* :: */[
                compileExp(vb[1]),
                /* [] */0
              ]
            ]
          ]);
}

function compileExp(e) {
  switch (e.tag | 0) {
    case /* ATEXP */0 :
        return compileAtExp(e[0]);
    case /* APP */1 :
        return /* Apply2 */Block.__(1, [
                  /* :: */[
                    React.createElement(React.Fragment, undefined),
                    /* :: */[
                      " ",
                      /* :: */[
                        React.createElement(React.Fragment, undefined),
                        /* [] */0
                      ]
                    ]
                  ],
                  /* :: */[
                    compileExp(e[0]),
                    /* :: */[
                      compileAtExp(e[1]),
                      /* [] */0
                    ]
                  ]
                ]);
    case /* FN */2 :
        return /* Apply2 */Block.__(1, [
                  /* :: */[
                    "fn ",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ],
                  /* :: */[
                    compileMatch(e[0]),
                    /* [] */0
                  ]
                ]);
    
  }
}

function compileExpRow(param) {
  var rest = param[2];
  var exp = param[1];
  var lab = param[0];
  if (rest !== undefined) {
    return /* Apply2 */Block.__(1, [
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* :: */[
                  "=",
                  /* :: */[
                    ", ",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ]
              ],
              /* :: */[
                /* Atom */Block.__(0, [lab]),
                /* :: */[
                  compileExp(exp),
                  /* :: */[
                    compileExpRow(rest),
                    /* [] */0
                  ]
                ]
              ]
            ]);
  } else {
    return /* Apply2 */Block.__(1, [
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* :: */[
                  "=",
                  /* :: */[
                    React.createElement(React.Fragment, undefined),
                    /* [] */0
                  ]
                ]
              ],
              /* :: */[
                /* Atom */Block.__(0, [lab]),
                /* :: */[
                  compileExp(exp),
                  /* [] */0
                ]
              ]
            ]);
  }
}

function compileAtPat(a) {
  return /* Atom */Block.__(0, [a[0]]);
}

function compileDec(d) {
  return /* Apply2 */Block.__(1, [
            /* :: */[
              "val ",
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* [] */0
              ]
            ],
            /* :: */[
              compileValBind(d[0]),
              /* [] */0
            ]
          ]);
}

function compileMatch(m) {
  var match = m[1];
  var mr = m[0];
  if (match !== undefined) {
    return /* Apply2 */Block.__(1, [
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* :: */[
                  React.createElement(React.Fragment, undefined, React.createElement("br", undefined), "| "),
                  /* :: */[
                    React.createElement(React.Fragment, undefined),
                    /* [] */0
                  ]
                ]
              ],
              /* :: */[
                compileMRule(mr),
                /* :: */[
                  compileMatch(match),
                  /* [] */0
                ]
              ]
            ]);
  } else {
    return compileMRule(mr);
  }
}

function compileMRule(mr) {
  return /* Apply2 */Block.__(1, [
            /* :: */[
              React.createElement(React.Fragment, undefined),
              /* :: */[
                " => ",
                /* :: */[
                  React.createElement(React.Fragment, undefined),
                  /* [] */0
                ]
              ]
            ],
            /* :: */[
              compileAtPat(mr[0][0]),
              /* :: */[
                compileExp(mr[1]),
                /* [] */0
              ]
            ]
          ]);
}

function compilePat(p) {
  return compileAtPat(p[0]);
}

function compileSVal(sv) {
  return /* Value2 */Block.__(8, [
            /* [] */0,
            /* :: */[
              /* Atom */Block.__(0, [String(sv[0])]),
              /* [] */0
            ]
          ]);
}

function compileVal_(v) {
  switch (v.tag | 0) {
    case /* SVAL */0 :
        return compileSVal(v[0]);
    case /* BASVAL */1 :
        return /* Value2 */Block.__(8, [
                  /* [] */0,
                  /* :: */[
                    /* Apply2 */Block.__(1, [
                        /* :: */[
                          "builtin ",
                          /* :: */[
                            React.createElement(React.Fragment, undefined),
                            /* [] */0
                          ]
                        ],
                        /* :: */[
                          /* Atom */Block.__(0, [v[0]]),
                          /* [] */0
                        ]
                      ]),
                    /* [] */0
                  ]
                ]);
    case /* VID */2 :
        return /* Value2 */Block.__(8, [
                  /* [] */0,
                  /* :: */[
                    /* Atom */Block.__(0, [v[0]]),
                    /* [] */0
                  ]
                ]);
    case /* RECORD */3 :
        var r = v[0];
        if (r) {
          return /* Value2 */Block.__(8, [
                    /* [] */0,
                    /* :: */[
                      /* Apply2 */Block.__(1, [
                          /* :: */[
                            "{",
                            /* :: */[
                              "}",
                              /* [] */0
                            ]
                          ],
                          /* :: */[
                            compileRecord(r),
                            /* [] */0
                          ]
                        ]),
                      /* [] */0
                    ]
                  ]);
        } else {
          return /* Value2 */Block.__(8, [
                    /* [] */0,
                    /* :: */[
                      /* Atom */Block.__(0, ["()"]),
                      /* [] */0
                    ]
                  ]);
        }
    case /* FCNCLOSURE */4 :
        return /* Value2 */Block.__(8, [
                  /* :: */[
                    "closure",
                    /* [] */0
                  ],
                  /* :: */[
                    compileMatch(v[0]),
                    /* :: */[
                      compileEnv(v[1]),
                      /* :: */[
                        compileEnv(v[2]),
                        /* [] */0
                      ]
                    ]
                  ]
                ]);
    
  }
}

function compileRecord(r) {
  if (r) {
    var r$1 = r[1];
    var match = r[0];
    var v = match[1];
    var l = match[0];
    if (r$1) {
      return /* Apply2 */Block.__(1, [
                /* :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    "=",
                    /* :: */[
                      ", ",
                      /* :: */[
                        React.createElement(React.Fragment, undefined),
                        /* [] */0
                      ]
                    ]
                  ]
                ],
                /* :: */[
                  /* Atom */Block.__(0, [l]),
                  /* :: */[
                    compileVal_(v),
                    /* :: */[
                      compileRecord(r$1),
                      /* [] */0
                    ]
                  ]
                ]
              ]);
    } else {
      return /* Apply2 */Block.__(1, [
                /* :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    "=",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* :: */[
                  /* Atom */Block.__(0, [l]),
                  /* :: */[
                    compileVal_(v),
                    /* [] */0
                  ]
                ]
              ]);
    }
  } else {
    return /* Atom */Block.__(0, [React.createElement(React.Fragment, undefined)]);
  }
}

function compileKVs(param) {
  return /* KV2 */Block.__(7, [/* tuple */[
              /* Atom */Block.__(0, [param[0]]),
              compileVal_(param[1])
            ]]);
}

function compileEnv(e) {
  return /* Map2 */Block.__(5, [List.rev(List.map(compileKVs, e))]);
}

function compileStrDec(sd) {
  if (sd.tag) {
    return /* Apply2 */Block.__(1, [
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* :: */[
                  React.createElement(React.Fragment, undefined, ";", React.createElement("br", undefined)),
                  /* :: */[
                    React.createElement(React.Fragment, undefined),
                    /* [] */0
                  ]
                ]
              ],
              /* :: */[
                compileStrDec(sd[0]),
                /* :: */[
                  compileStrDec(sd[1]),
                  /* [] */0
                ]
              ]
            ]);
  } else {
    return compileDec(sd[0]);
  }
}

function compileTopDec(td) {
  if (td[1] !== undefined) {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "SMLToTheiaIR.re",
            125,
            2
          ]
        ];
  }
  return compileStrDec(td[0]);
}

function compileProgram(p) {
  var match = p[1];
  var td = p[0];
  if (match !== undefined) {
    return /* Apply2 */Block.__(1, [
              /* :: */[
                React.createElement(React.Fragment, undefined),
                /* :: */[
                  React.createElement(React.Fragment, undefined, ";", React.createElement("br", undefined)),
                  /* :: */[
                    React.createElement(React.Fragment, undefined),
                    /* [] */0
                  ]
                ]
              ],
              /* :: */[
                compileTopDec(td),
                /* :: */[
                  compileProgram(match),
                  /* [] */0
                ]
              ]
            ]);
  } else {
    return compileTopDec(td);
  }
}

function compileFocus(f) {
  if (typeof f === "number") {
    return /* Atom */Block.__(0, [React.createElement(React.Fragment, undefined)]);
  } else {
    switch (f.tag | 0) {
      case /* AtExp */0 :
          return compileAtExp(f[0]);
      case /* Exp */1 :
          return compileExp(f[0]);
      case /* Val */2 :
          return compileVal_(f[0]);
      case /* Dec */3 :
          return compileDec(f[0]);
      case /* ValBind */4 :
          return compileValBind(f[0]);
      case /* StrDec */5 :
          return compileStrDec(f[0]);
      case /* TopDec */6 :
          return compileTopDec(f[0]);
      case /* ExpRow */7 :
          return compileExpRow(f[0]);
      case /* Record */8 :
          return compileRecord(f[0]);
      case /* Program */9 :
          return compileProgram(f[0]);
      case /* Match */10 :
          return /* VSequence */Block.__(4, [/* :: */[
                      compileMatch(f[0]),
                      /* :: */[
                        compileVal_(f[1]),
                        /* [] */0
                      ]
                    ]]);
      case /* MRule */11 :
          return /* VSequence */Block.__(4, [/* :: */[
                      compileMRule(f[0]),
                      /* :: */[
                        compileVal_(f[1]),
                        /* [] */0
                      ]
                    ]]);
      case /* Pat */12 :
          return /* VSequence */Block.__(4, [/* :: */[
                      compileAtPat(f[0][0]),
                      /* :: */[
                        compileVal_(f[1]),
                        /* [] */0
                      ]
                    ]]);
      case /* AtPat */13 :
          return /* VSequence */Block.__(4, [/* :: */[
                      compileAtPat(f[0]),
                      /* :: */[
                        compileVal_(f[1]),
                        /* [] */0
                      ]
                    ]]);
      
    }
  }
}

function compileCtxt(c) {
  switch (c.tag | 0) {
    case /* LETD */0 :
        return /* record */[
                /* ops : :: */[
                  "let ",
                  /* :: */[
                    " in ",
                    /* :: */[
                      " end",
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileExp(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    case /* VALBINDE */1 :
        if (c[2] !== undefined) {
          return Pervasives.failwith("TODO");
        } else {
          return /* record */[
                  /* ops : :: */[
                    React.createElement(React.Fragment, undefined),
                    /* :: */[
                      " = ",
                      /* :: */[
                        React.createElement(React.Fragment, undefined),
                        /* [] */0
                      ]
                    ]
                  ],
                  /* args : :: */[
                    compileAtPat(c[0][0]),
                    /* [] */0
                  ],
                  /* holePos */1
                ];
        }
    case /* SEQL */2 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    React.createElement(React.Fragment, undefined, ";", React.createElement("br", undefined)),
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileStrDec(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    case /* APPL */3 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    " ",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileAtExp(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    case /* APPR */4 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    " ",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileVal_(c[0]),
                  /* [] */0
                ],
                /* holePos */1
              ];
    case /* RECORDER */5 :
        return /* record */[
                /* ops : :: */[
                  "{",
                  /* :: */[
                    "}",
                    /* [] */0
                  ]
                ],
                /* args : [] */0,
                /* holePos */0
              ];
    case /* EXPROWE */6 :
        var r = c[0];
        if (r) {
          var match = c[3];
          var l = c[1];
          if (match !== undefined) {
            return /* record */[
                    /* ops : :: */[
                      React.createElement(React.Fragment, undefined),
                      /* :: */[
                        ", ",
                        /* :: */[
                          "=",
                          /* :: */[
                            ", ",
                            /* :: */[
                              React.createElement(React.Fragment, undefined),
                              /* [] */0
                            ]
                          ]
                        ]
                      ]
                    ],
                    /* args : :: */[
                      compileRecord(r),
                      /* :: */[
                        /* Atom */Block.__(0, [l]),
                        /* :: */[
                          compileExpRow(match),
                          /* [] */0
                        ]
                      ]
                    ],
                    /* holePos */2
                  ];
          } else {
            return /* record */[
                    /* ops : :: */[
                      React.createElement(React.Fragment, undefined),
                      /* :: */[
                        ", ",
                        /* :: */[
                          "=",
                          /* :: */[
                            React.createElement(React.Fragment, undefined),
                            /* [] */0
                          ]
                        ]
                      ]
                    ],
                    /* args : :: */[
                      compileRecord(r),
                      /* :: */[
                        /* Atom */Block.__(0, [l]),
                        /* [] */0
                      ]
                    ],
                    /* holePos */2
                  ];
          }
        } else {
          var match$1 = c[3];
          var l$1 = c[1];
          if (match$1 !== undefined) {
            return /* record */[
                    /* ops : :: */[
                      React.createElement(React.Fragment, undefined),
                      /* :: */[
                        "=",
                        /* :: */[
                          ", ",
                          /* :: */[
                            React.createElement(React.Fragment, undefined),
                            /* [] */0
                          ]
                        ]
                      ]
                    ],
                    /* args : :: */[
                      /* Atom */Block.__(0, [l$1]),
                      /* :: */[
                        compileExpRow(match$1),
                        /* [] */0
                      ]
                    ],
                    /* holePos */1
                  ];
          } else {
            return /* record */[
                    /* ops : :: */[
                      React.createElement(React.Fragment, undefined),
                      /* :: */[
                        "=",
                        /* :: */[
                          React.createElement(React.Fragment, undefined),
                          /* [] */0
                        ]
                      ]
                    ],
                    /* args : :: */[
                      /* Atom */Block.__(0, [l$1]),
                      /* [] */0
                    ],
                    /* holePos */1
                  ];
          }
        }
    case /* PROGRAML */7 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    React.createElement(React.Fragment, undefined, ";", React.createElement("br", undefined)),
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileProgram(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    case /* MATCHMR */8 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    React.createElement(React.Fragment, undefined, React.createElement("br", undefined), "| "),
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileMatch(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    case /* MRULEP */9 :
        return /* record */[
                /* ops : :: */[
                  React.createElement(React.Fragment, undefined),
                  /* :: */[
                    " => ",
                    /* :: */[
                      React.createElement(React.Fragment, undefined),
                      /* [] */0
                    ]
                  ]
                ],
                /* args : :: */[
                  compileExp(c[1]),
                  /* [] */0
                ],
                /* holePos */0
              ];
    
  }
}

function compileRewrite(param) {
  return /* Kont2 */Block.__(6, [
            compileFocus(param[/* focus */0]),
            List.map(compileCtxt, param[/* ctxts */1])
          ]);
}

function smlToTheiaIR(param) {
  return /* VSequence */Block.__(4, [/* :: */[
              /* Cell2 */Block.__(9, [
                  "env",
                  /* :: */[
                    compileEnv(param[/* env */1]),
                    /* [] */0
                  ]
                ]),
              /* :: */[
                /* Cell2 */Block.__(9, [
                    "rewrite",
                    /* :: */[
                      compileRewrite(param[/* rewrite */0]),
                      /* [] */0
                    ]
                  ]),
                /* [] */0
              ]
            ]]);
}

exports.compileSCon = compileSCon;
exports.compileAtExp = compileAtExp;
exports.compileExpRow = compileExpRow;
exports.compileExp = compileExp;
exports.compileMatch = compileMatch;
exports.compileMRule = compileMRule;
exports.compileDec = compileDec;
exports.compileValBind = compileValBind;
exports.compileAtPat = compileAtPat;
exports.compilePat = compilePat;
exports.compileSVal = compileSVal;
exports.compileVal_ = compileVal_;
exports.compileRecord = compileRecord;
exports.compileKVs = compileKVs;
exports.compileEnv = compileEnv;
exports.compileStrDec = compileStrDec;
exports.compileTopDec = compileTopDec;
exports.compileProgram = compileProgram;
exports.compileFocus = compileFocus;
exports.compileCtxt = compileCtxt;
exports.compileRewrite = compileRewrite;
exports.smlToTheiaIR = smlToTheiaIR;
/* react Not a pure module */
