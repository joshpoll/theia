'use strict';

var List = require("bs-platform/lib/js/list.js");
var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function interleave(xs, ys) {
  if (xs) {
    return /* :: */[
            xs[0],
            interleave(ys, xs[1])
          ];
  } else {
    return ys;
  }
}

function split(list, n) {
  var _i = n;
  var _acc = /* [] */0;
  var _l = list;
  while(true) {
    var l = _l;
    var acc = _acc;
    var i = _i;
    if (l) {
      if (i === 0) {
        return /* tuple */[
                List.rev(acc),
                l
              ];
      } else {
        _l = l[1];
        _acc = /* :: */[
          l[0],
          acc
        ];
        _i = i - 1 | 0;
        continue ;
      }
    } else {
      return /* tuple */[
              List.rev(acc),
              /* [] */0
            ];
    }
  };
}

function insert(x, xs, i) {
  var match = split(xs, i);
  return Pervasives.$at(match[0], /* :: */[
              x,
              match[1]
            ]);
}

function prettierList($staropt$star, $staropt$star$1, ss) {
  var space = $staropt$star$1 !== undefined ? $staropt$star$1 : true;
  var ss$1 = List.filter((function (s) {
            return Caml_obj.caml_notequal(s, "");
          }))(ss);
  var loop = function (ss) {
    if (ss) {
      var ss$1 = ss[1];
      var s = ss[0];
      if (ss$1) {
        if (space) {
          return React.createElement(React.Fragment, undefined, s, " ", loop(ss$1));
        } else {
          return React.createElement(React.Fragment, undefined, s, loop(ss$1));
        }
      } else {
        return React.createElement(React.Fragment, undefined, s);
      }
    } else {
      return React.createElement(React.Fragment, undefined);
    }
  };
  return React.createElement(React.Fragment, undefined, loop(ss$1));
}

var nbsp = ('\u00a0');

function useKeyPressed(onKeyPressed) {
  React.useEffect((function () {
          document.addEventListener("keydown", onKeyPressed);
          return (function (param) {
                    document.removeEventListener("keydown", onKeyPressed);
                    return /* () */0;
                  });
        }), ([]));
  return /* () */0;
}

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

function lookupOne(key, _oneStack) {
  while(true) {
    var oneStack = _oneStack;
    if (oneStack) {
      var match = oneStack[0];
      if (Caml_obj.caml_equal(match[0], key)) {
        return Caml_option.some(match[1]);
      } else {
        _oneStack = oneStack[1];
        continue ;
      }
    } else {
      return ;
    }
  };
}

exports.interleave = interleave;
exports.split = split;
exports.insert = insert;
exports.prettierList = prettierList;
exports.nbsp = nbsp;
exports.useKeyPressed = useKeyPressed;
exports.$neg$neg = $neg$neg;
exports.lookupOne = lookupOne;
/* nbsp Not a pure module */
