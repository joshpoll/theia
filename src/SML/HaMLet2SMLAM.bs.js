'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");

function sourceMap(json) {
  return /* record */[
          /* file */Json_decode.field("file", Json_decode.string, json),
          /* line1 */Json_decode.field("line1", Json_decode.$$int, json),
          /* col1 */Json_decode.field("col1", Json_decode.$$int, json),
          /* line2 */Json_decode.field("line2", Json_decode.$$int, json),
          /* col2 */Json_decode.field("col2", Json_decode.$$int, json)
        ];
}

function intscon(json) {
  return /* INTSCon */Block.__(0, [List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(Json_decode.$$int, param);
                      }), json))]);
}

function scontatexp(json) {
  return /* SCONAtExp */Block.__(1, [
            Json_decode.field("sourceMap", sourceMap, json),
            List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(node, param);
                      }), json))
          ]);
}

function atexp(json) {
  return /* ATExp */Block.__(2, [
            Json_decode.field("sourceMap", sourceMap, json),
            List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(node, param);
                      }), json))
          ]);
}

function longvid(json) {
  return /* LongVId */Block.__(3, [List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(Json_decode.string, param);
                      }), json))]);
}

function idatpat(json) {
  return /* IDAtPat */Block.__(4, [
            Json_decode.field("sourceMap", sourceMap, json),
            List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(node, param);
                      }), json))
          ]);
}

function atpat(json) {
  return /* ATPat */Block.__(5, [
            Json_decode.field("sourceMap", sourceMap, json),
            List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(node, param);
                      }), json))
          ]);
}

function plainvalbind(json) {
  return /* PLAINValBind */Block.__(6, [
            Json_decode.field("sourceMap", sourceMap, json),
            Json_decode.field("args", (function (param) {
                    return Json_decode.tuple3(node, node, (function (param) {
                                  return Json_decode.nullAs(undefined, param);
                                }), param);
                  }), json)
          ]);
}

function seq(json) {
  return /* Seq */Block.__(7, [Json_decode.field("sourceMap", sourceMap, json)]);
}

function valdec(json) {
  return /* VALDec */Block.__(8, [
            Json_decode.field("sourceMap", sourceMap, json),
            Json_decode.field("args", (function (param) {
                    return Json_decode.tuple2(node, node, param);
                  }), json)
          ]);
}

function decstrdec(json) {
  return /* DECStrDec */Block.__(9, [
            Json_decode.field("sourceMap", sourceMap, json),
            List.hd(Json_decode.field("args", (function (param) {
                        return Json_decode.list(node, param);
                      }), json))
          ]);
}

function strdectopdec(json) {
  return /* STRDECTopDec */Block.__(10, [
            Json_decode.field("sourceMap", sourceMap, json),
            Json_decode.field("args", (function (param) {
                    return Json_decode.pair(node, (function (param) {
                                  return Json_decode.nullAs(undefined, param);
                                }), param);
                  }), json)
          ]);
}

function program(json) {
  return /* Program */Block.__(11, [
            Json_decode.field("sourceMap", sourceMap, json),
            Json_decode.field("args", (function (param) {
                    return Json_decode.pair(node, (function (param) {
                                  return Json_decode.nullAs(undefined, param);
                                }), param);
                  }), json)
          ]);
}

function node(json) {
  return Json_decode.andThen((function (s) {
                switch (s) {
                  case "ATExp" :
                      return atexp;
                  case "ATPat" :
                      return atpat;
                  case "DECStrDec" :
                      return decstrdec;
                  case "IDAtPat" :
                      return idatpat;
                  case "INTSCon" :
                      return intscon;
                  case "LongVId" :
                      return longvid;
                  case "PLAINValBind" :
                      return plainvalbind;
                  case "Program" :
                      return program;
                  case "SCONAtExp" :
                      return scontatexp;
                  case "STRDECTopDec" :
                      return strdectopdec;
                  case "Seq" :
                      return seq;
                  case "VALDec" :
                      return valdec;
                  default:
                    return Pervasives.failwith("Unknown node type: " + s);
                }
              }), (function (param) {
                return Json_decode.field("node", Json_decode.string, param);
              }), json);
}

var Decode = {
  sourceMap: sourceMap,
  intscon: intscon,
  scontatexp: scontatexp,
  atexp: atexp,
  longvid: longvid,
  idatpat: idatpat,
  atpat: atpat,
  plainvalbind: plainvalbind,
  seq: seq,
  valdec: valdec,
  decstrdec: decstrdec,
  strdectopdec: strdectopdec,
  program: program,
  node: node
};

function compileProgram(p) {
  if (p.tag === /* Program */11) {
    var match = p[1];
    var match$1 = match[1];
    var td = match[0];
    if (match$1 !== undefined) {
      return /* PROGRAM */[
              compileTopDec(td),
              compileProgram(match$1)
            ];
    } else {
      return /* PROGRAM */[
              compileTopDec(td),
              undefined
            ];
    }
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            126,
            2
          ]
        ];
  }
}

function compileTopDec(td) {
  if (td.tag === /* STRDECTopDec */10) {
    var match = td[1];
    var match$1 = match[1];
    var sd = match[0];
    if (match$1 !== undefined) {
      return /* STRDEC */[
              compileStrDec(sd),
              compileTopDec(match$1)
            ];
    } else {
      return /* STRDEC */[
              compileStrDec(sd),
              undefined
            ];
    }
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            132,
            2
          ]
        ];
  }
}

function compileStrDec(sd) {
  if (sd.tag === /* DECStrDec */9) {
    return /* DEC */Block.__(0, [compileDec(sd[1])]);
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            138,
            2
          ]
        ];
  }
}

function compileDec(d) {
  if (d.tag === /* VALDec */8) {
    return /* VAL */[compileValBind(d[1][1])];
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            143,
            2
          ]
        ];
  }
}

function compileValBind(vb) {
  if (vb.tag === /* PLAINValBind */6) {
    var match = vb[1];
    var match$1 = match[2];
    var e = match[1];
    var p = match[0];
    if (match$1 !== undefined) {
      return /* PLAIN */[
              compilePat(p),
              compileExp(e),
              compileValBind(match$1)
            ];
    } else {
      return /* PLAIN */[
              compilePat(p),
              compileExp(e),
              undefined
            ];
    }
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            148,
            2
          ]
        ];
  }
}

function compilePat(p) {
  if (p.tag === /* ATPat */5) {
    return /* ATPAT */[compileAtPat(p[1])];
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            154,
            2
          ]
        ];
  }
}

function compileAtPat(ap) {
  if (ap.tag === /* IDAtPat */4) {
    return /* ID */[compileLongVId(ap[1])];
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            159,
            2
          ]
        ];
  }
}

function compileLongVId(x) {
  if (x.tag === /* LongVId */3) {
    return x[0];
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            164,
            2
          ]
        ];
  }
}

function compileExp(e) {
  if (e.tag === /* ATExp */2) {
    return /* ATEXP */Block.__(0, [compileAtExp(e[1])]);
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            169,
            2
          ]
        ];
  }
}

function compileAtExp(a) {
  if (a.tag === /* SCONAtExp */1) {
    return /* SCON */Block.__(0, [compileSCon(a[1])]);
  } else {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            174,
            2
          ]
        ];
  }
}

function compileSCon(sc) {
  if (sc.tag) {
    throw [
          Caml_builtin_exceptions.match_failure,
          /* tuple */[
            "HaMLet2SMLAM.re",
            179,
            2
          ]
        ];
  } else {
    return /* INT */[sc[0]];
  }
}

var testJson = "\n{\n  \"node\": \"Program\",\n  \"sourceMap\": {\n    \"file\": \"(input 1)\",\n    \"line1\": 1,\n    \"col1\": 0,\n    \"line2\": 1,\n    \"col2\": 10\n  },\n  \"args\": [\n    {\n      \"node\": \"STRDECTopDec\",\n      \"sourceMap\": {\n        \"file\": \"(input 1)\",\n        \"line1\": 1,\n        \"col1\": 0,\n        \"line2\": 1,\n        \"col2\": 9\n      },\n      \"args\": [\n        {\n          \"node\": \"DECStrDec\",\n          \"sourceMap\": {\n            \"file\": \"(input 1)\",\n            \"line1\": 1,\n            \"col1\": 0,\n            \"line2\": 1,\n            \"col2\": 9\n          },\n          \"args\": [\n            {\n              \"node\": \"VALDec\",\n              \"sourceMap\": {\n                \"file\": \"(input 1)\",\n                \"line1\": 1,\n                \"col1\": 0,\n                \"line2\": 1,\n                \"col2\": 9\n              },\n              \"args\": [\n                {\n                  \"node\": \"Seq\",\n                  \"sourceMap\": {\n                    \"file\": \"(input 1)\",\n                    \"line1\": 1,\n                    \"col1\": 9,\n                    \"line2\": 1,\n                    \"col2\": 9\n                  },\n                  \"args\": []\n                },\n                {\n                  \"node\": \"PLAINValBind\",\n                  \"sourceMap\": {\n                    \"file\": \"(input 1)\",\n                    \"line1\": 1,\n                    \"col1\": 4,\n                    \"line2\": 1,\n                    \"col2\": 9\n                  },\n                  \"args\": [\n                    {\n                      \"node\": \"ATPat\",\n                      \"sourceMap\": {\n                        \"file\": \"(input 1)\",\n                        \"line1\": 1,\n                        \"col1\": 4,\n                        \"line2\": 1,\n                        \"col2\": 5\n                      },\n                      \"args\": [\n                        {\n                          \"node\": \"IDAtPat\",\n                          \"sourceMap\": {\n                            \"file\": \"(input 1)\",\n                            \"line1\": 1,\n                            \"col1\": 4,\n                            \"line2\": 1,\n                            \"col2\": 5\n                          },\n                          \"args\": [\n                            {\n                              \"node\": \"LongVId\",\n                              \"args\": [\n                                \"x\"\n                              ]\n                            }\n                          ]\n                        }\n                      ]\n                    },\n                    {\n                      \"node\": \"ATExp\",\n                      \"sourceMap\": {\n                        \"file\": \"(input 1)\",\n                        \"line1\": 1,\n                        \"col1\": 8,\n                        \"line2\": 1,\n                        \"col2\": 9\n                      },\n                      \"args\": [\n                        {\n                          \"node\": \"SCONAtExp\",\n                          \"sourceMap\": {\n                            \"file\": \"(input 1)\",\n                            \"line1\": 1,\n                            \"col1\": 8,\n                            \"line2\": 1,\n                            \"col2\": 9\n                          },\n                          \"args\": [\n                            {\n                              \"node\": \"INTSCon\",\n                              \"args\": [\n                                1\n                              ]\n                            }\n                          ]\n                        }\n                      ]\n                    },\n                    null\n                  ]\n                }\n              ]\n            }\n          ]\n        },\n        null\n      ]\n    },\n    null\n  ]\n}\n";

var testJsonSmall = "\n\n{\n                  \"node\": \"PLAINValBind\",\n                  \"sourceMap\": {\n                    \"file\": \"(input 1)\",\n                    \"line1\": 1,\n                    \"col1\": 4,\n                    \"line2\": 1,\n                    \"col2\": 9\n                  },\n                  \"args\": [\n                    {\n                      \"node\": \"ATPat\",\n                      \"sourceMap\": {\n                        \"file\": \"(input 1)\",\n                        \"line1\": 1,\n                        \"col1\": 4,\n                        \"line2\": 1,\n                        \"col2\": 5\n                      },\n                      \"args\": [\n                        {\n                          \"node\": \"IDAtPat\",\n                          \"sourceMap\": {\n                            \"file\": \"(input 1)\",\n                            \"line1\": 1,\n                            \"col1\": 4,\n                            \"line2\": 1,\n                            \"col2\": 5\n                          },\n                          \"args\": [\n                            {\n                              \"node\": \"LongVId\",\n                              \"args\": [\n                                \"x\"\n                              ]\n                            }\n                          ]\n                        }\n                      ]\n                    },\n                    {\n                      \"node\": \"ATExp\",\n                      \"sourceMap\": {\n                        \"file\": \"(input 1)\",\n                        \"line1\": 1,\n                        \"col1\": 8,\n                        \"line2\": 1,\n                        \"col2\": 9\n                      },\n                      \"args\": [\n                        {\n                          \"node\": \"SCONAtExp\",\n                          \"sourceMap\": {\n                            \"file\": \"(input 1)\",\n                            \"line1\": 1,\n                            \"col1\": 8,\n                            \"line2\": 1,\n                            \"col2\": 9\n                          },\n                          \"args\": [\n                            {\n                              \"node\": \"INTSCon\",\n                              \"args\": [\n                                1\n                              ]\n                            }\n                          ]\n                        }\n                      ]\n                    },\n                    null\n                  ]\n                }\n\n";

exports.Decode = Decode;
exports.compileProgram = compileProgram;
exports.compileTopDec = compileTopDec;
exports.compileStrDec = compileStrDec;
exports.compileDec = compileDec;
exports.compileValBind = compileValBind;
exports.compilePat = compilePat;
exports.compileAtPat = compileAtPat;
exports.compileLongVId = compileLongVId;
exports.compileExp = compileExp;
exports.compileAtExp = compileAtExp;
exports.compileSCon = compileSCon;
exports.testJson = testJson;
exports.testJsonSmall = testJsonSmall;
/* No side effect */
