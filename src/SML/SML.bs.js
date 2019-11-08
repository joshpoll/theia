'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var Util$ReasonReactExamples = require("../Theia/Util.bs.js");
var TheiaUtil$ReasonReactExamples = require("../Theia/TheiaUtil.bs.js");

function apply(f, v) {
  switch (f) {
    case "+" :
        if (v.tag === /* RECORD */3) {
          var match = v[0];
          if (match) {
            var match$1 = match[0];
            if (match$1[0] === "1") {
              var match$2 = match$1[1];
              if (match$2.tag) {
                return Pervasives.failwith("unknown built-in function: " + f);
              } else {
                var match$3 = match[1];
                if (match$3) {
                  var match$4 = match$3[0];
                  if (match$4[0] === "2") {
                    var match$5 = match$4[1];
                    if (match$5.tag) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else if (match$3[1]) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else {
                      return /* SVAL */Block.__(0, [/* INT */[match$2[0][0] + match$5[0][0] | 0]]);
                    }
                  } else {
                    return Pervasives.failwith("unknown built-in function: " + f);
                  }
                } else {
                  return Pervasives.failwith("unknown built-in function: " + f);
                }
              }
            } else {
              return Pervasives.failwith("unknown built-in function: " + f);
            }
          } else {
            return Pervasives.failwith("unknown built-in function: " + f);
          }
        } else {
          return Pervasives.failwith("unknown built-in function: " + f);
        }
    case "-" :
        if (v.tag === /* RECORD */3) {
          var match$6 = v[0];
          if (match$6) {
            var match$7 = match$6[0];
            if (match$7[0] === "1") {
              var match$8 = match$7[1];
              if (match$8.tag) {
                return Pervasives.failwith("unknown built-in function: " + f);
              } else {
                var match$9 = match$6[1];
                if (match$9) {
                  var match$10 = match$9[0];
                  if (match$10[0] === "2") {
                    var match$11 = match$10[1];
                    if (match$11.tag) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else if (match$9[1]) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else {
                      return /* SVAL */Block.__(0, [/* INT */[match$8[0][0] - match$11[0][0] | 0]]);
                    }
                  } else {
                    return Pervasives.failwith("unknown built-in function: " + f);
                  }
                } else {
                  return Pervasives.failwith("unknown built-in function: " + f);
                }
              }
            } else {
              return Pervasives.failwith("unknown built-in function: " + f);
            }
          } else {
            return Pervasives.failwith("unknown built-in function: " + f);
          }
        } else {
          return Pervasives.failwith("unknown built-in function: " + f);
        }
    case "<" :
        if (v.tag === /* RECORD */3) {
          var match$12 = v[0];
          if (match$12) {
            var match$13 = match$12[0];
            if (match$13[0] === "1") {
              var match$14 = match$13[1];
              if (match$14.tag) {
                return Pervasives.failwith("unknown built-in function: " + f);
              } else {
                var match$15 = match$12[1];
                if (match$15) {
                  var match$16 = match$15[0];
                  if (match$16[0] === "2") {
                    var match$17 = match$16[1];
                    if (match$17.tag) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else if (match$15[1]) {
                      return Pervasives.failwith("unknown built-in function: " + f);
                    } else if (match$14[0][0] < match$17[0][0]) {
                      return /* VID */Block.__(2, ["true"]);
                    } else {
                      return /* VID */Block.__(2, ["false"]);
                    }
                  } else {
                    return Pervasives.failwith("unknown built-in function: " + f);
                  }
                } else {
                  return Pervasives.failwith("unknown built-in function: " + f);
                }
              }
            } else {
              return Pervasives.failwith("unknown built-in function: " + f);
            }
          } else {
            return Pervasives.failwith("unknown built-in function: " + f);
          }
        } else {
          return Pervasives.failwith("unknown built-in function: " + f);
        }
    default:
      return Pervasives.failwith("unknown built-in function: " + f);
  }
}

function recEnv(ve) {
  return List.map((function (xv) {
                var match = xv[1];
                if (match.tag === /* FCNCLOSURE */4) {
                  return /* tuple */[
                          xv[0],
                          /* FCNCLOSURE */Block.__(4, [
                              match[0],
                              match[1],
                              ve
                            ])
                        ];
                } else {
                  return xv;
                }
              }), ve);
}

function step(c) {
  var match = c[/* rewrite */0];
  var match$1 = match[/* focus */0];
  if (typeof match$1 === "number") {
    var match$2 = match[/* ctxts */1];
    if (match$2) {
      var match$3 = match$2[0];
      switch (match$3.tag | 0) {
        case /* SEQL */2 :
            return /* record */[
                    /* rewrite : record */[
                      /* focus : StrDec */Block.__(5, [match$3[1]]),
                      /* ctxts */match$2[1]
                    ],
                    /* env */c[/* env */1]
                  ];
        case /* PROGRAML */7 :
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Program */Block.__(9, [match$3[1]]),
                      /* ctxts */match$2[1]
                    ],
                    /* env */c[/* env */1]
                  ];
        case /* LETD */0 :
        case /* MRULEP */9 :
            break;
        default:
          return ;
      }
      return /* record */[
              /* rewrite : record */[
                /* focus : Exp */Block.__(1, [match$3[1]]),
                /* ctxts */match$2[1]
              ],
              /* env */c[/* env */1]
            ];
    } else {
      return ;
    }
  } else {
    switch (match$1.tag | 0) {
      case /* AtExp */0 :
          var match$4 = match$1[0];
          switch (match$4.tag | 0) {
            case /* SCON */0 :
                return /* record */[
                        /* rewrite : record */[
                          /* focus : Val */Block.__(2, [/* SVAL */Block.__(0, [/* INT */[match$4[0][0]]])]),
                          /* ctxts */match[/* ctxts */1]
                        ],
                        /* env */c[/* env */1]
                      ];
            case /* ID */1 :
                var env = c[/* env */1];
                var match$5 = Util$ReasonReactExamples.lookupOne(match$4[0], env);
                if (match$5 !== undefined) {
                  return /* record */[
                          /* rewrite : record */[
                            /* focus : Val */Block.__(2, [match$5]),
                            /* ctxts */match[/* ctxts */1]
                          ],
                          /* env */env
                        ];
                } else {
                  return ;
                }
            case /* RECORD */2 :
                var match$6 = match$4[0];
                if (match$6 !== undefined) {
                  return /* record */[
                          /* rewrite : record */[
                            /* focus : ExpRow */Block.__(7, [match$6]),
                            /* ctxts : :: */[
                              /* RECORDER */Block.__(5, [/* () */0]),
                              match[/* ctxts */1]
                            ]
                          ],
                          /* env */c[/* env */1]
                        ];
                } else {
                  return /* record */[
                          /* rewrite : record */[
                            /* focus : Val */Block.__(2, [/* RECORD */Block.__(3, [/* [] */0])]),
                            /* ctxts */match[/* ctxts */1]
                          ],
                          /* env */c[/* env */1]
                        ];
                }
            case /* LET */3 :
                return /* record */[
                        /* rewrite : record */[
                          /* focus : Dec */Block.__(3, [match$4[0]]),
                          /* ctxts : :: */[
                            /* LETD */Block.__(0, [
                                /* () */0,
                                match$4[1]
                              ]),
                            match[/* ctxts */1]
                          ]
                        ],
                        /* env */c[/* env */1]
                      ];
            case /* PAR */4 :
                return /* record */[
                        /* rewrite : record */[
                          /* focus : Exp */Block.__(1, [match$4[0]]),
                          /* ctxts */match[/* ctxts */1]
                        ],
                        /* env */c[/* env */1]
                      ];
            
          }
      case /* Exp */1 :
          var match$7 = match$1[0];
          switch (match$7.tag | 0) {
            case /* ATEXP */0 :
                return /* record */[
                        /* rewrite : record */[
                          /* focus : AtExp */Block.__(0, [match$7[0]]),
                          /* ctxts */match[/* ctxts */1]
                        ],
                        /* env */c[/* env */1]
                      ];
            case /* APP */1 :
                return /* record */[
                        /* rewrite : record */[
                          /* focus : Exp */Block.__(1, [match$7[0]]),
                          /* ctxts : :: */[
                            /* APPL */Block.__(3, [
                                /* () */0,
                                match$7[1]
                              ]),
                            match[/* ctxts */1]
                          ]
                        ],
                        /* env */c[/* env */1]
                      ];
            case /* FN */2 :
                var env$1 = c[/* env */1];
                return /* record */[
                        /* rewrite : record */[
                          /* focus : Val */Block.__(2, [/* FCNCLOSURE */Block.__(4, [
                                  match$7[0],
                                  env$1,
                                  /* [] */0
                                ])]),
                          /* ctxts */match[/* ctxts */1]
                        ],
                        /* env */env$1
                      ];
            
          }
      case /* Val */2 :
          var v = match$1[0];
          var match$8 = match[/* ctxts */1];
          if (match$8) {
            var match$9 = match$8[0];
            switch (match$9.tag | 0) {
              case /* VALBINDE */1 :
                  if (match$9[2] !== undefined) {
                    return ;
                  } else {
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Empty */0,
                              /* ctxts */match$8[1]
                            ],
                            /* env : :: */[
                              /* tuple */[
                                match$9[0][0][0],
                                v
                              ],
                              c[/* env */1]
                            ]
                          ];
                  }
              case /* APPL */3 :
                  switch (v.tag | 0) {
                    case /* BASVAL */1 :
                        var match$10 = match[/* ctxts */1];
                        return /* record */[
                                /* rewrite : record */[
                                  /* focus : AtExp */Block.__(0, [match$10[0][1]]),
                                  /* ctxts : :: */[
                                    /* APPR */Block.__(4, [
                                        /* BASVAL */Block.__(1, [v[0]]),
                                        /* () */0
                                      ]),
                                    match$10[1]
                                  ]
                                ],
                                /* env */c[/* env */1]
                              ];
                    case /* FCNCLOSURE */4 :
                        var match$11 = match[/* ctxts */1];
                        return /* record */[
                                /* rewrite : record */[
                                  /* focus : AtExp */Block.__(0, [match$11[0][1]]),
                                  /* ctxts : :: */[
                                    /* APPR */Block.__(4, [
                                        /* FCNCLOSURE */Block.__(4, [
                                            v[0],
                                            v[1],
                                            v[2]
                                          ]),
                                        /* () */0
                                      ]),
                                    match$11[1]
                                  ]
                                ],
                                /* env */c[/* env */1]
                              ];
                    default:
                      return ;
                  }
              case /* APPR */4 :
                  var match$12 = match$9[0];
                  switch (match$12.tag | 0) {
                    case /* BASVAL */1 :
                        return /* record */[
                                /* rewrite : record */[
                                  /* focus : Val */Block.__(2, [apply(match$12[0], v)]),
                                  /* ctxts */match$8[1]
                                ],
                                /* env */c[/* env */1]
                              ];
                    case /* FCNCLOSURE */4 :
                        return /* record */[
                                /* rewrite : record */[
                                  /* focus : Match */Block.__(10, [
                                      match$12[0],
                                      v
                                    ]),
                                  /* ctxts */match$8[1]
                                ],
                                /* env */Pervasives.$at(recEnv(match$12[2]), match$12[1])
                              ];
                    default:
                      return ;
                  }
              case /* EXPROWE */6 :
                  var match$13 = match$9[3];
                  var l1 = match$9[1];
                  var r = match$9[0];
                  if (match$13 !== undefined) {
                    var match$14 = match$13;
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Exp */Block.__(1, [match$14[1]]),
                              /* ctxts : :: */[
                                /* EXPROWE */Block.__(6, [
                                    Pervasives.$at(r, /* :: */[
                                          /* tuple */[
                                            l1,
                                            v
                                          ],
                                          /* [] */0
                                        ]),
                                    match$14[0],
                                    /* () */0,
                                    match$14[2]
                                  ]),
                                match$8[1]
                              ]
                            ],
                            /* env */c[/* env */1]
                          ];
                  } else {
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Record */Block.__(8, [Pervasives.$at(r, /* :: */[
                                        /* tuple */[
                                          l1,
                                          v
                                        ],
                                        /* [] */0
                                      ])]),
                              /* ctxts */match$8[1]
                            ],
                            /* env */c[/* env */1]
                          ];
                  }
              case /* MATCHMR */8 :
                  return /* record */[
                          /* rewrite : record */[
                            /* focus : Val */Block.__(2, [v]),
                            /* ctxts */match$8[1]
                          ],
                          /* env */c[/* env */1]
                        ];
              default:
                return ;
            }
          } else {
            return ;
          }
      case /* Dec */3 :
          return /* record */[
                  /* rewrite : record */[
                    /* focus : ValBind */Block.__(4, [match$1[0][0]]),
                    /* ctxts */match[/* ctxts */1]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* ValBind */4 :
          var match$15 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : Exp */Block.__(1, [match$15[1]]),
                    /* ctxts : :: */[
                      /* VALBINDE */Block.__(1, [
                          match$15[0],
                          /* () */0,
                          match$15[2]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* StrDec */5 :
          var match$16 = match$1[0];
          if (match$16.tag) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : StrDec */Block.__(5, [match$16[0]]),
                      /* ctxts : :: */[
                        /* SEQL */Block.__(2, [
                            /* () */0,
                            match$16[1]
                          ]),
                        match[/* ctxts */1]
                      ]
                    ],
                    /* env */c[/* env */1]
                  ];
          } else {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Dec */Block.__(3, [match$16[0]]),
                      /* ctxts */match[/* ctxts */1]
                    ],
                    /* env */c[/* env */1]
                  ];
          }
      case /* TopDec */6 :
          var match$17 = match$1[0];
          if (match$17[1] !== undefined) {
            return ;
          } else {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : StrDec */Block.__(5, [match$17[0]]),
                      /* ctxts */match[/* ctxts */1]
                    ],
                    /* env */c[/* env */1]
                  ];
          }
      case /* ExpRow */7 :
          var match$18 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : Exp */Block.__(1, [match$18[1]]),
                    /* ctxts : :: */[
                      /* EXPROWE */Block.__(6, [
                          /* [] */0,
                          match$18[0],
                          /* () */0,
                          match$18[2]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* Record */8 :
          var match$19 = match[/* ctxts */1];
          if (match$19 && match$19[0].tag === /* RECORDER */5) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Val */Block.__(2, [/* RECORD */Block.__(3, [match$1[0]])]),
                      /* ctxts */match$19[1]
                    ],
                    /* env */c[/* env */1]
                  ];
          } else {
            return ;
          }
      case /* Program */9 :
          var match$20 = match$1[0];
          var match$21 = match$20[1];
          var td = match$20[0];
          if (match$21 !== undefined) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : TopDec */Block.__(6, [td]),
                      /* ctxts : :: */[
                        /* PROGRAML */Block.__(7, [
                            /* () */0,
                            match$21
                          ]),
                        match[/* ctxts */1]
                      ]
                    ],
                    /* env */c[/* env */1]
                  ];
          } else {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : TopDec */Block.__(6, [td]),
                      /* ctxts */match[/* ctxts */1]
                    ],
                    /* env */c[/* env */1]
                  ];
          }
      case /* Match */10 :
          var match$22 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : MRule */Block.__(11, [
                        match$22[0],
                        match$1[1]
                      ]),
                    /* ctxts : :: */[
                      /* MATCHMR */Block.__(8, [
                          /* () */0,
                          match$22[1]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* MRule */11 :
          var match$23 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : Pat */Block.__(12, [
                        match$23[0],
                        match$1[1]
                      ]),
                    /* ctxts : :: */[
                      /* MRULEP */Block.__(9, [
                          /* () */0,
                          match$23[1]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* Pat */12 :
          return /* record */[
                  /* rewrite : record */[
                    /* focus : AtPat */Block.__(13, [
                        match$1[0][0],
                        match$1[1]
                      ]),
                    /* ctxts */match[/* ctxts */1]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* AtPat */13 :
          var env$2 = c[/* env */1];
          var ctxts = match[/* ctxts */1];
          var v$1 = match$1[1];
          var match$24 = Util$ReasonReactExamples.lookupOne(match$1[0][0], env$2);
          if (match$24 !== undefined) {
            if (Caml_obj.caml_equal(v$1, match$24)) {
              return /* record */[
                      /* rewrite : record */[
                        /* focus : Empty */0,
                        /* ctxts */ctxts
                      ],
                      /* env */env$2
                    ];
            } else {
              return /* record */[
                      /* rewrite : record */[
                        /* focus : FAIL */Block.__(14, [v$1]),
                        /* ctxts */ctxts
                      ],
                      /* env */env$2
                    ];
            }
          } else {
            throw [
                  Caml_builtin_exceptions.match_failure,
                  /* tuple */[
                    "SML.re",
                    449,
                    8
                  ]
                ];
          }
      case /* FAIL */14 :
          var match$25 = match[/* ctxts */1];
          if (match$25) {
            var match$26 = match$25[0];
            var v$2 = match$1[0];
            switch (match$26.tag | 0) {
              case /* MATCHMR */8 :
                  var match$27 = match$26[1];
                  if (match$27 !== undefined) {
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Match */Block.__(10, [
                                  match$27,
                                  v$2
                                ]),
                              /* ctxts */match$25[1]
                            ],
                            /* env */c[/* env */1]
                          ];
                  } else {
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : FAIL */Block.__(14, [v$2]),
                              /* ctxts */match$25[1]
                            ],
                            /* env */c[/* env */1]
                          ];
                  }
              case /* MRULEP */9 :
                  return /* record */[
                          /* rewrite : record */[
                            /* focus : FAIL */Block.__(14, [v$2]),
                            /* ctxts */match$25[1]
                          ],
                          /* env */c[/* env */1]
                        ];
              default:
                return ;
            }
          } else {
            return ;
          }
      
    }
  }
}

function isNone(o) {
  return o === undefined;
}

function isFinal(c) {
  return false;
}

function inject(e) {
  return /* record */[
          /* rewrite : record */[
            /* focus */e,
            /* ctxts : [] */0
          ],
          /* env : :: */[
            /* tuple */[
              "+",
              /* BASVAL */Block.__(1, ["+"])
            ],
            /* :: */[
              /* tuple */[
                "-",
                /* BASVAL */Block.__(1, ["-"])
              ],
              /* :: */[
                /* tuple */[
                  "<",
                  /* BASVAL */Block.__(1, ["<"])
                ],
                /* :: */[
                  /* tuple */[
                    "true",
                    /* VID */Block.__(2, ["true"])
                  ],
                  /* :: */[
                    /* tuple */[
                      "false",
                      /* VID */Block.__(2, ["false"])
                    ],
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]
        ];
}

function interpretTraceBounded($staropt$star, p) {
  var maxDepth = $staropt$star !== undefined ? $staropt$star : 100;
  return TheiaUtil$ReasonReactExamples.takeWhileInclusive((function (c) {
                return true;
              }), TheiaUtil$ReasonReactExamples.iterateMaybeMaxDepth(maxDepth, step, inject(p)));
}

function interpretTrace(p) {
  return TheiaUtil$ReasonReactExamples.takeWhileInclusive((function (c) {
                return true;
              }), TheiaUtil$ReasonReactExamples.iterateMaybe(step, inject(p)));
}

exports.apply = apply;
exports.recEnv = recEnv;
exports.step = step;
exports.isNone = isNone;
exports.isFinal = isFinal;
exports.inject = inject;
exports.interpretTraceBounded = interpretTraceBounded;
exports.interpretTrace = interpretTrace;
/* Util-ReasonReactExamples Not a pure module */
