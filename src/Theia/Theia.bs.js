'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var Util$ReasonReactExamples = require("./Util.bs.js");

var rlist = $$Array.of_list;

function $neg$neg(i, j) {
  var _n = j;
  var _acc = /* [] */0;
  while(true) {
    var acc = _acc;
    var n = _n;
    if (n < i) {
      return acc;
    } else {
      _acc = /* :: */[
        n,
        acc
      ];
      _n = n - 1 | 0;
      continue ;
    }
  };
}

function appNodesEq(_v1, _v2) {
  while(true) {
    var v2 = _v2;
    var v1 = _v1;
    if (v1) {
      if (v2 && Caml_obj.caml_equal(v1[0], v2[0])) {
        _v2 = v2[1];
        _v1 = v1[1];
        continue ;
      } else {
        return false;
      }
    } else if (v2) {
      return false;
    } else {
      return true;
    }
  };
}

function appNodeIn(s, _vs) {
  while(true) {
    var vs = _vs;
    if (vs) {
      if (appNodesEq(s, vs[0])) {
        return true;
      } else {
        _vs = vs[1];
        continue ;
      }
    } else {
      return false;
    }
  };
}

function prettyList(ss) {
  var loop = function (ss) {
    if (ss) {
      var ss$1 = ss[1];
      var s = ss[0];
      if (ss$1) {
        return s + (", " + loop(ss$1));
      } else {
        return s;
      }
    } else {
      return "";
    }
  };
  return "[" + (loop(ss) + "]");
}

var CompileError = Caml_exceptions.create("Theia-ReasonReactExamples.CompileError");

function splitAux(l, x) {
  if (l) {
    var h = l[0];
    var rest = splitAux(l[1], x);
    var tail_000 = /* :: */[
      h,
      List.hd(rest)
    ];
    var tail_001 = List.tl(rest);
    var tail = /* :: */[
      tail_000,
      tail_001
    ];
    if (Caml_obj.caml_equal(h, x)) {
      return /* :: */[
              /* [] */0,
              tail
            ];
    } else {
      return tail;
    }
  } else {
    return /* :: */[
            /* [] */0,
            /* [] */0
          ];
  }
}

function split(l, x) {
  if (l) {
    return List.tl(splitAux(l, x));
  } else {
    return /* [] */0;
  }
}

function theiaIRDebugPrint(k) {
  switch (k.tag | 0) {
    case /* Atom */0 :
        return "Atom()";
    case /* Apply2 */1 :
        return "Apply2(, " + (prettyList(List.map(theiaIRDebugPrint, k[1])) + ")");
    case /* EvalCtx */2 :
        return "EvalCtx(" + (debugFreezer(k[0]) + ")");
    case /* HSequence */3 :
    case /* VSequence */4 :
        return "TODO";
    case /* Map2 */5 :
        return "Map2(" + (prettyList(List.map(theiaIRDebugPrint, k[0])) + ")");
    case /* Kont2 */6 :
        return "Kont2(" + (theiaIRDebugPrint(k[0]) + (", " + (prettyList(List.map(debugFreezer, k[1])) + ")")));
    case /* KV2 */7 :
        var match = k[0];
        return "KV2(" + (theiaIRDebugPrint(match[0]) + (", " + (theiaIRDebugPrint(match[1]) + ")")));
    case /* Value2 */8 :
        return "Value2(" + (prettyList(List.map((function (s) {
                            return "\"" + (s + "\"");
                          }), k[0])) + (", " + (prettyList(List.map(theiaIRDebugPrint, k[1])) + ")")));
    case /* Cell2 */9 :
        return "Cell2(" + (k[0] + (", " + (prettyList(List.map(theiaIRDebugPrint, k[1])) + ")")));
    
  }
}

function debugFreezer(param) {
  return "evalctx(, " + (prettyList(List.map(theiaIRDebugPrint, param[/* args */1])) + (", " + (String(param[/* holePos */2]) + ")")));
}

function debugEntry2(param) {
  return theiaIRDebugPrint(param[0]) + ("->" + theiaIRDebugPrint(param[1]));
}

function theiaIRDebugPrintShort(k) {
  switch (k.tag | 0) {
    case /* Atom */0 :
        return "Tk";
    case /* Apply2 */1 :
        return "App(" + (prettyList(List.map(theiaIRDebugPrintShort, k[1])) + ")");
    case /* EvalCtx */2 :
        return "Fz";
    case /* HSequence */3 :
    case /* VSequence */4 :
        return "TODO";
    case /* Map2 */5 :
        return "Map";
    case /* Kont2 */6 :
        return "Kont";
    case /* KV2 */7 :
        return "KV";
    case /* Value2 */8 :
        return "Val(" + (prettyList(List.map(theiaIRDebugPrintShort, k[1])) + ")");
    case /* Cell2 */9 :
        return "Cell(" + (prettyList(List.map(theiaIRDebugPrintShort, k[1])) + ")");
    
  }
}

function seqDebugPrint(s) {
  if (typeof s === "number") {
    return "NS";
  } else {
    switch (s.tag | 0) {
      case /* Seq */0 :
          return "Seq(" + (seqDebugPrint(s[0]) + (", " + (seqDebugPrint(s[1]) + ")")));
      case /* ApplyS */1 :
          return "App(" + (prettyList(List.map(seqDebugPrint, s[0])) + ")");
      case /* FreezerS */2 :
          return "F(" + (prettyList(List.map(seqDebugPrint, s[0])) + ")");
      case /* MapS */3 :
          return "Map(" + (prettyList(List.map(seqDebugPrint, s[0])) + ")");
      case /* KVS */4 :
          return "KV(" + (seqDebugPrint(s[0]) + (", " + (seqDebugPrint(s[1]) + ")")));
      case /* CellS */5 :
          return "Cell(" + (prettyList(List.map(seqDebugPrint, s[0])) + ")");
      
    }
  }
}

var render_open_brack = React.createElement("span", {
      style: {
        color: "blue"
      }
    }, "[");

var render_close_brack = React.createElement("span", {
      style: {
        color: "blue"
      }
    }, "]");

function kn2Pretty(_$staropt$star, _k) {
  while(true) {
    var k = _k;
    var $staropt$star = _$staropt$star;
    var parens = $staropt$star !== undefined ? $staropt$star : true;
    switch (k.tag | 0) {
      case /* Atom */0 :
          return k[0];
      case /* Apply2 */1 :
          return Util$ReasonReactExamples.prettierList(parens, false, Util$ReasonReactExamples.interleave(k[0], List.map((function (eta) {
                                return kn2Pretty(undefined, eta);
                              }), k[1])));
      case /* EvalCtx */2 :
          throw [
                CompileError,
                "There shouldn't be a EvalCtx!"
              ];
      case /* HSequence */3 :
          var l = k[0];
          if (l && !l[1]) {
            return React.createElement(React.Fragment, undefined, kn2Pretty(false, l[0]));
          }
          return React.createElement("div", {
                      style: {
                        float: "left"
                      }
                    }, $$Array.of_list(List.rev(List.mapi((function (i, kn) {
                                    return React.createElement("div", {
                                                key: String(i),
                                                style: {
                                                  float: "left",
                                                  marginLeft: "10px"
                                                }
                                              }, kn2Pretty(false, kn));
                                  }), l))));
      case /* VSequence */4 :
          var l$1 = k[0];
          if (l$1 && !l$1[1]) {
            return React.createElement(React.Fragment, undefined, kn2Pretty(false, l$1[0]));
          }
          return React.createElement(React.Fragment, undefined, $$Array.of_list(List.mapi((function (i, kn) {
                                return React.createElement("div", {
                                            key: String(i),
                                            style: {
                                              marginTop: "10px"
                                            }
                                          }, kn2Pretty(false, kn));
                              }), l$1)));
      case /* Map2 */5 :
          var l$2 = k[0];
          if (l$2) {
            return React.createElement("table", {
                        style: {
                          borderCollapse: "collapse",
                          borderStyle: "hidden",
                          display: "inline-table"
                        }
                      }, React.createElement("thead", undefined, React.createElement("tr", undefined, React.createElement("th", {
                                    style: {
                                      border: "1px solid black",
                                      paddingRight: "5px",
                                      textAlign: "right"
                                    }
                                  }, "Id"), React.createElement("th", {
                                    style: {
                                      border: "1px solid black",
                                      paddingLeft: "5px",
                                      textAlign: "left"
                                    }
                                  }, "Val"))), React.createElement("tbody", undefined, $$Array.of_list(List.mapi((function (i, kv) {
                                      return React.createElement("tr", {
                                                  key: String(i)
                                                }, kn2Pretty(undefined, kv));
                                    }), l$2))));
          } else {
            _k = /* Map2 */Block.__(5, [/* :: */[
                  /* KV2 */Block.__(7, [/* tuple */[
                        /* Atom */Block.__(0, [Util$ReasonReactExamples.nbsp]),
                        /* Atom */Block.__(0, [Util$ReasonReactExamples.nbsp])
                      ]]),
                  /* [] */0
                ]]);
            _$staropt$star = undefined;
            continue ;
          }
      case /* Kont2 */6 :
          return prettyKont2List(undefined, false, k[0], List.rev(k[1]));
      case /* KV2 */7 :
          var match = k[0];
          return React.createElement(React.Fragment, undefined, React.createElement("td", {
                          style: {
                            borderRight: "1px solid black",
                            paddingTop: "5px",
                            paddingRight: "5px",
                            textAlign: "right"
                          }
                        }, kn2Pretty(undefined, match[0])), React.createElement("td", {
                          style: {
                            borderLeft: "1px solid black",
                            paddingTop: "5px",
                            paddingLeft: "5px",
                            textAlign: "left"
                          }
                        }, kn2Pretty(undefined, match[1])));
      case /* Value2 */8 :
          var ops = k[0];
          if (!ops) {
            var match$1 = k[1];
            if (match$1 && !match$1[1]) {
              return React.createElement("table", {
                          style: {
                            display: "inline-table"
                          }
                        }, React.createElement("tbody", undefined, React.createElement("tr", undefined, React.createElement("td", {
                                      style: {
                                        border: "1px solid gray"
                                      }
                                    }, kn2Pretty(false, match$1[0])))));
            }
            
          }
          return React.createElement("fieldset", {
                      style: {
                        display: "inline"
                      }
                    }, React.createElement("legend", undefined, List.fold_left((function (prim, prim$1) {
                                return prim + prim$1;
                              }), "", Util$ReasonReactExamples.interleave(ops, List.map((function (param) {
                                        return "\xe2\x80\xa2";
                                      }), $neg$neg(1, List.length(ops) - 1 | 0))))), React.createElement("table", {
                          style: {
                            display: "inline-table"
                          }
                        }, React.createElement("tbody", undefined, React.createElement("tr", undefined, $$Array.of_list(List.mapi((function (i, arg) {
                                            return React.createElement("td", {
                                                        key: String(i),
                                                        style: {
                                                          border: "1px solid gray"
                                                        }
                                                      }, kn2Pretty(false, arg));
                                          }), k[1]))))));
      case /* Cell2 */9 :
          var partial_arg = false;
          return React.createElement("fieldset", undefined, React.createElement("legend", undefined, k[0]), $$Array.of_list(List.map((function(partial_arg){
                            return function (param) {
                              return kn2Pretty(partial_arg, param);
                            }
                            }(partial_arg)), k[1])));
      
    }
  };
}

function prettyKont2List($staropt$star, $staropt$star$1, kn, fs) {
  var nestNum = $staropt$star !== undefined ? $staropt$star : 0;
  var parens = $staropt$star$1 !== undefined ? $staropt$star$1 : false;
  if (fs) {
    return prettyFreeze(nestNum, fs[0], prettyKont2List(nestNum + 1 | 0, parens, kn, fs[1]));
  } else {
    return kn2Pretty(parens, kn);
  }
}

function prettyFreeze($staropt$star, param, arg) {
  var nestNum = $staropt$star !== undefined ? $staropt$star : 0;
  var newArgs = Util$ReasonReactExamples.insert(React.createElement("div", {
            style: {
              backgroundColor: "hsla(240, 100%, " + (String(80 - Caml_int32.imul(nestNum, 10) | 0) + "%, 0.33)"),
              display: "inline"
            }
          }, arg), List.map((function (eta) {
              return kn2Pretty(undefined, eta);
            }), param[/* args */1]), param[/* holePos */2]);
  return Util$ReasonReactExamples.prettierList(false, false, Util$ReasonReactExamples.interleave(param[/* ops */0], newArgs));
}

function kn2PrettyList(xs) {
  return List.fold_left((function (s1, s2) {
                return React.createElement(React.Fragment, undefined, s1, s2);
              }), React.createElement(React.Fragment, undefined), List.map((function (s) {
                    return React.createElement("div", {
                                style: {
                                  fontSize: "14px"
                                }
                              }, kn2Pretty(undefined, s));
                  }), xs));
}

function fetchLoggedStates(file, callback) {
  return fetch(file).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Curry._1(callback, json));
              }));
}

function cellPrint(param, printer, i) {
  return React.createElement("fieldset", {
              key: String(i)
            }, React.createElement("legend", undefined, param[/* label */0]), Curry._1(printer, param[/* body */1]));
}

function cellsPrint(printer, cs) {
  return List.mapi((function (i, c) {
                return cellPrint(c, printer, i);
              }), cs);
}

function handleClick(path, log, $staropt$star, theiaIRTrace, dispatch, _event) {
  return Curry._1(dispatch, /* UpdateMachineState */[/* record */[/* k */List.map((function (eta) {
                        return kn2Pretty(undefined, eta);
                      }), theiaIRTrace)]]);
}

function Theia(Props) {
  var theiaIRTraces = Props.theiaIRTraces;
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (action !== 0) {
              return /* record */[
                      /* trace */state[/* trace */0],
                      /* currentConfig */Caml_primitive.caml_int_min(state[/* currentConfig */1] + 1 | 0, List.length(Belt_Option.getWithDefault(state[/* trace */0], /* :: */[
                                    React.createElement(React.Fragment, undefined),
                                    /* [] */0
                                  ])) - 1 | 0)
                    ];
            } else {
              return /* record */[
                      /* trace */state[/* trace */0],
                      /* currentConfig */Caml_primitive.caml_int_max(0, state[/* currentConfig */1] - 1 | 0)
                    ];
            }
          } else {
            return /* record */[
                    /* trace */action[0][/* k */0],
                    /* currentConfig */0
                  ];
          }
        }), /* record */[
        /* trace */undefined,
        /* currentConfig */0
      ]);
  var dispatch = match[1];
  var state = match[0];
  var handleKeyPressed = function (e) {
    var match = e.key;
    switch (match) {
      case "ArrowLeft" :
          return Curry._1(dispatch, /* StepBack */0);
      case "ArrowRight" :
          return Curry._1(dispatch, /* StepForward */1);
      default:
        return /* () */0;
    }
  };
  Util$ReasonReactExamples.useKeyPressed(handleKeyPressed);
  var renderConfig = function (my_option) {
    if (my_option !== undefined) {
      return Caml_option.valFromOption(my_option);
    } else {
      return React.createElement(React.Fragment, undefined);
    }
  };
  var match$1 = state[/* trace */0];
  var tmp;
  if (match$1 !== undefined) {
    var s = match$1;
    tmp = React.createElement("div", {
          style: {
            display: "grid",
            alignItems: "center",
            gridTemplateColumns: "fit-content(350px) 20px fit-content(350px) 20px fit-content(350px)"
          }
        }, React.createElement("div", {
              style: {
                float: "left",
                maxWidth: String(350) + "px"
              }
            }, renderConfig(Belt_List.get(s, state[/* currentConfig */1]))), React.createElement("div", {
              style: {
                float: "left",
                textAlign: "center"
              }
            }, React.createElement("b", undefined, "->")), React.createElement("div", {
              style: {
                float: "left",
                maxWidth: String(350) + "px"
              }
            }, renderConfig(Belt_List.get(s, state[/* currentConfig */1] + 1 | 0))));
  } else {
    tmp = React.createElement(React.Fragment, undefined);
  }
  return React.createElement("div", undefined, React.createElement("button", {
                  onClick: (function (param) {
                      return Curry._1(dispatch, /* StepBack */0);
                    })
                }, "<-"), React.createElement("button", {
                  onClick: (function (param) {
                      return Curry._1(dispatch, /* StepForward */1);
                    })
                }, "->"), $$Array.of_list(List.map((function (param) {
                        var states = param[/* states */1];
                        return React.createElement("button", {
                                    onClick: (function (param) {
                                        return handleClick("", "", undefined, states, dispatch, param);
                                      })
                                  }, param[/* name */0]);
                      }), theiaIRTraces)), tmp);
}

var values = /* :: */[
  /* :: */[
    "closure",
    /* [] */0
  ],
  /* :: */[
    /* :: */[
      "muclosure",
      /* [] */0
    ],
    /* :: */[
      /* :: */[
        "cc",
        /* [] */0
      ],
      /* [] */0
    ]
  ]
];

var labels = /* :: */[
  "LAMBDA",
  /* :: */[
    "LAMBDA-SYNTAX",
    /* :: */[
      "IMP-SYNTAX",
      /* :: */[
        "FUN-UNTYPED-COMMON",
        /* :: */[
          "SML-SYNTAX",
          /* [] */0
        ]
      ]
    ]
  ]
];

var make = Theia;

exports.rlist = rlist;
exports.$neg$neg = $neg$neg;
exports.values = values;
exports.labels = labels;
exports.appNodesEq = appNodesEq;
exports.appNodeIn = appNodeIn;
exports.prettyList = prettyList;
exports.CompileError = CompileError;
exports.splitAux = splitAux;
exports.split = split;
exports.theiaIRDebugPrint = theiaIRDebugPrint;
exports.debugEntry2 = debugEntry2;
exports.debugFreezer = debugFreezer;
exports.theiaIRDebugPrintShort = theiaIRDebugPrintShort;
exports.seqDebugPrint = seqDebugPrint;
exports.render_open_brack = render_open_brack;
exports.render_close_brack = render_close_brack;
exports.kn2Pretty = kn2Pretty;
exports.prettyFreeze = prettyFreeze;
exports.prettyKont2List = prettyKont2List;
exports.kn2PrettyList = kn2PrettyList;
exports.fetchLoggedStates = fetchLoggedStates;
exports.cellPrint = cellPrint;
exports.cellsPrint = cellsPrint;
exports.handleClick = handleClick;
exports.make = make;
/* render_open_brack Not a pure module */
