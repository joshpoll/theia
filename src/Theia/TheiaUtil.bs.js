'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function lookup(k, _stack) {
  while(true) {
    var stack = _stack;
    if (stack) {
      var match = stack[0];
      if (match[/* key */0] === k) {
        return Caml_option.some(match[/* value */1]);
      } else {
        _stack = stack[1];
        continue ;
      }
    } else {
      return ;
    }
  };
}

function renderEnv(renderValue, env) {
  return /* Map2 */Block.__(5, [List.map((function (param) {
                    return /* KV2 */Block.__(7, [/* tuple */[
                                /* Atom */Block.__(0, [param[/* key */0]]),
                                Curry._1(renderValue, param[/* value */1])
                              ]]);
                  }), env)]);
}

function takeWhileInclusive(p, l) {
  if (l) {
    var x = l[0];
    return /* :: */[
            x,
            Curry._1(p, x) ? takeWhileInclusive(p, l[1]) : /* [] */0
          ];
  } else {
    return /* [] */0;
  }
}

function iterateMaybeAux(f, x) {
  if (x !== undefined) {
    var x$1 = Caml_option.valFromOption(x);
    var fx = Curry._1(f, x$1);
    return /* :: */[
            x$1,
            iterateMaybeAux(f, fx)
          ];
  } else {
    return /* [] */0;
  }
}

function iterateMaybe(f, x) {
  return iterateMaybeAux(f, Caml_option.some(x));
}

function iterateMaybeAuxBounded(i, f, x) {
  if (i <= 0 || x === undefined) {
    return /* [] */0;
  } else {
    var x$1 = Caml_option.valFromOption(x);
    var fx = Curry._1(f, x$1);
    return /* :: */[
            x$1,
            iterateMaybeAuxBounded(i - 1 | 0, f, fx)
          ];
  }
}

function iterateMaybeMaxDepth(i, f, x) {
  return iterateMaybeAuxBounded(i, f, Caml_option.some(x));
}

exports.lookup = lookup;
exports.renderEnv = renderEnv;
exports.takeWhileInclusive = takeWhileInclusive;
exports.iterateMaybeAux = iterateMaybeAux;
exports.iterateMaybe = iterateMaybe;
exports.iterateMaybeAuxBounded = iterateMaybeAuxBounded;
exports.iterateMaybeMaxDepth = iterateMaybeMaxDepth;
/* No side effect */
