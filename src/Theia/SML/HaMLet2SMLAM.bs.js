'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var ReludeParse = require("relude-parse/src/ReludeParse.bs.js");
var Relude_List = require("relude/src/Relude_List.bs.js");
var ReludeParse_Parser = require("relude-parse/src/ReludeParse_Parser.bs.js");

console.log(ReludeParse_Parser.runParser("1", ReludeParse_Parser.anyDigit));

function parseBetweenParens(p) {
  return ReludeParse_Parser.between(ReludeParse_Parser.str("("), ReludeParse_Parser.str(")"), Curry._2(ReludeParse_Parser.Infix.$less$star, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, p), ReludeParse_Parser.ws));
}

var parseSourceMapInfo = ReludeParse_Parser.map((function (param) {
        return /* record */[
                /* file */param[0],
                /* l1 */param[1],
                /* c1 */param[2],
                /* l2 */param[3],
                /* c2 */param[4]
              ];
      }), Curry._5(ReludeParse_Parser.tuple5, ReludeParse_Parser.map(Relude_List.foldRight((function (prim, prim$1) {
                    return prim + prim$1;
                  }), ""), ReludeParse_Parser.manyUntil(ReludeParse_Parser.str(":"), ReludeParse_Parser.anyCharNotIn(/* :: */[
                      ":",
                      /* [] */0
                    ]))), ReludeParse_Parser.anyUnsignedInt, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("."), ReludeParse_Parser.anyUnsignedInt), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("-"), ReludeParse_Parser.anyUnsignedInt), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("."), ReludeParse_Parser.anyUnsignedInt)));

var parseLongVId = Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.leftParen, ReludeParse_Parser.str("LongVId")), ReludeParse_Parser.ws), ReludeParse_Parser.map(Relude_List.foldRight((function (prim, prim$1) {
                return prim + prim$1;
              }), ""), ReludeParse_Parser.manyUntil(ReludeParse_Parser.str(")"), ReludeParse_Parser.anyCharNotIn(/* :: */[
                  ")",
                  /* [] */0
                ]))));

var parseINTSCon = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (n) {
        return /* INTSCon */[n];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("INTSCon"), ReludeParse_Parser.ws), ReludeParse_Parser.anyInt)));

var parseSCONAtExp = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (param) {
        return /* SCONAtExp */[
                param[0],
                param[1]
              ];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.tuple2, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("SCONAtExp"), ReludeParse_Parser.ws), parseSourceMapInfo), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, parseINTSCon))));

var parseATExp = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (param) {
        return /* ATExp */[
                param[0],
                param[1]
              ];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.tuple2, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("ATExp"), ReludeParse_Parser.ws), parseSourceMapInfo), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, parseSCONAtExp))));

var parsePLAINValBind = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (param) {
        return /* IDAtPat */[
                param[0],
                param[1]
              ];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.tuple2, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("IDAtPat"), ReludeParse_Parser.ws), parseSourceMapInfo), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, parseLongVId))));

var parseIDAtPat = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (param) {
        return /* IDAtPat */[
                param[0],
                param[1]
              ];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.tuple2, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("IDAtPat"), ReludeParse_Parser.ws), parseSourceMapInfo), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, parseLongVId))));

var parseATPat = Curry._2(ReludeParse_Parser.Infix.$less$$great, (function (param) {
        return /* ATPat */[
                param[0],
                param[1]
              ];
      }), parseBetweenParens(Curry._2(ReludeParse_Parser.tuple2, Curry._2(ReludeParse_Parser.Infix.$star$great, Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.str("ATPat"), ReludeParse_Parser.ws), parseSourceMapInfo), Curry._2(ReludeParse_Parser.Infix.$star$great, ReludeParse_Parser.ws, parseIDAtPat))));

var output = ReludeParse_Parser.runParser("(ATExp test.sml:1.8-1.10\n            (SCONAtExp test.sml:1.8-1.10\n              (INTSCon 34)\n            )\n          )", parseATExp);

var P = 0;

var test = "(Program test.sml:1.0-1.11\n  (STRDECTopDec test.sml:1.0-1.10\n    (DECStrDec test.sml:1.0-1.10\n      (VALDec test.sml:1.0-1.10\n        (Seq test.sml:1.10-1.10\n        )\n        (PLAINValBind test.sml:1.4-1.10\n          (ATPat test.sml:1.4-1.5\n            (IDAtPat test.sml:1.4-1.5\n              (LongVId x)\n            )\n          )\n          (ATExp test.sml:1.8-1.10\n            (SCONAtExp test.sml:1.8-1.10\n              (INTSCon 34)\n            )\n          )\n        )\n      )\n    )\n  )\n)";

var parseSCon = parseINTSCon;

var parseAtExp = parseSCONAtExp;

var parseExp = parseATExp;

var parseValBind = parsePLAINValBind;

var parseAtPat = parseIDAtPat;

var parsePat = parseATPat;

exports.P = P;
exports.test = test;
exports.parseBetweenParens = parseBetweenParens;
exports.parseSourceMapInfo = parseSourceMapInfo;
exports.parseLongVId = parseLongVId;
exports.parseINTSCon = parseINTSCon;
exports.parseSCon = parseSCon;
exports.parseSCONAtExp = parseSCONAtExp;
exports.parseAtExp = parseAtExp;
exports.parseATExp = parseATExp;
exports.parseExp = parseExp;
exports.parsePLAINValBind = parsePLAINValBind;
exports.parseValBind = parseValBind;
exports.parseIDAtPat = parseIDAtPat;
exports.parseAtPat = parseAtPat;
exports.parseATPat = parseATPat;
exports.parsePat = parsePat;
exports.output = output;
/*  Not a pure module */
