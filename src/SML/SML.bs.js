'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Util$ReasonReactExamples = require("../Theia/Util.bs.js");
var TheiaUtil$ReasonReactExamples = require("../Theia/TheiaUtil.bs.js");

function apply(f, v) {
  if (f === "+") {
    if (v.tag === /* RECORD */2) {
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
  } else {
    return Pervasives.failwith("unknown built-in function: " + f);
  }
}

function step(c) {
  var match = c[/* rewrite */0];
  var match$1 = match[/* focus */0];
  if (typeof match$1 === "number") {
    var match$2 = match[/* ctxts */1];
    if (match$2) {
      var match$3 = match$2[0];
      switch (match$3.tag | 0) {
        case /* LETD */0 :
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Exp */Block.__(1, [match$3[1]]),
                      /* ctxts */match$2[1]
                    ],
                    /* env */c[/* env */1]
                  ];
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
        default:
          return ;
      }
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
                            /* focus : Val */Block.__(2, [/* RECORD */Block.__(2, [/* [] */0])]),
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
                          /* focus : Val */Block.__(2, [/* FCNCLOSURE */Block.__(3, [
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
                  if (v.tag === /* BASVAL */1) {
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
                  } else {
                    return ;
                  }
              case /* APPR */4 :
                  var match$11 = match$9[0];
                  if (match$11.tag === /* BASVAL */1) {
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Val */Block.__(2, [apply(match$11[0], v)]),
                              /* ctxts */match$8[1]
                            ],
                            /* env */c[/* env */1]
                          ];
                  } else {
                    return ;
                  }
              case /* EXPROWE */6 :
                  var match$12 = match$9[3];
                  var l1 = match$9[1];
                  var r = match$9[0];
                  if (match$12 !== undefined) {
                    var match$13 = match$12;
                    return /* record */[
                            /* rewrite : record */[
                              /* focus : Exp */Block.__(1, [match$13[1]]),
                              /* ctxts : :: */[
                                /* EXPROWE */Block.__(6, [
                                    Pervasives.$at(r, /* :: */[
                                          /* tuple */[
                                            l1,
                                            v
                                          ],
                                          /* [] */0
                                        ]),
                                    match$13[0],
                                    /* () */0,
                                    match$13[2]
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
          var match$14 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : Exp */Block.__(1, [match$14[1]]),
                    /* ctxts : :: */[
                      /* VALBINDE */Block.__(1, [
                          match$14[0],
                          /* () */0,
                          match$14[2]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* StrDec */5 :
          var match$15 = match$1[0];
          if (match$15.tag) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : StrDec */Block.__(5, [match$15[0]]),
                      /* ctxts : :: */[
                        /* SEQL */Block.__(2, [
                            /* () */0,
                            match$15[1]
                          ]),
                        match[/* ctxts */1]
                      ]
                    ],
                    /* env */c[/* env */1]
                  ];
          } else {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Dec */Block.__(3, [match$15[0]]),
                      /* ctxts */match[/* ctxts */1]
                    ],
                    /* env */c[/* env */1]
                  ];
          }
      case /* TopDec */6 :
          var match$16 = match$1[0];
          if (match$16[1] !== undefined) {
            return ;
          } else {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : StrDec */Block.__(5, [match$16[0]]),
                      /* ctxts */match[/* ctxts */1]
                    ],
                    /* env */c[/* env */1]
                  ];
          }
      case /* ExpRow */7 :
          var match$17 = match$1[0];
          return /* record */[
                  /* rewrite : record */[
                    /* focus : Exp */Block.__(1, [match$17[1]]),
                    /* ctxts : :: */[
                      /* EXPROWE */Block.__(6, [
                          /* [] */0,
                          match$17[0],
                          /* () */0,
                          match$17[2]
                        ]),
                      match[/* ctxts */1]
                    ]
                  ],
                  /* env */c[/* env */1]
                ];
      case /* Record */8 :
          var match$18 = match[/* ctxts */1];
          if (match$18 && match$18[0].tag === /* RECORDER */5) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : Val */Block.__(2, [/* RECORD */Block.__(2, [match$1[0]])]),
                      /* ctxts */match$18[1]
                    ],
                    /* env */c[/* env */1]
                  ];
          } else {
            return ;
          }
      case /* Program */9 :
          var match$19 = match$1[0];
          var match$20 = match$19[1];
          var td = match$19[0];
          if (match$20 !== undefined) {
            return /* record */[
                    /* rewrite : record */[
                      /* focus : TopDec */Block.__(6, [td]),
                      /* ctxts : :: */[
                        /* PROGRAML */Block.__(7, [
                            /* () */0,
                            match$20
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
            /* [] */0
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
exports.step = step;
exports.isNone = isNone;
exports.isFinal = isFinal;
exports.inject = inject;
exports.interpretTraceBounded = interpretTraceBounded;
exports.interpretTrace = interpretTrace;
/* Util-ReasonReactExamples Not a pure module */
