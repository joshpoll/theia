'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Fetch = require("bs-fetch/src/Fetch.js");
var React = require("react");
var ReactDom = require("react-dom");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var SML$ReasonReactExamples = require("./SML/SML.bs.js");
var Theia$ReasonReactExamples = require("./Theia/Theia.bs.js");
var SMLExamples$ReasonReactExamples = require("./SML/SMLExamples.bs.js");
var HaMLet2SMLAM$ReasonReactExamples = require("./SML/HaMLet2SMLAM.bs.js");
var SMLToTheiaIR$ReasonReactExamples = require("./SML/SMLToTheiaIR.bs.js");
var ExampleStyles$ReasonReactExamples = require("./ExampleStyles.bs.js");

var firaCode = document.createElement("link");

firaCode.rel = "stylesheet";

firaCode.href = "https://cdn.jsdelivr.net/gh/tonsky/FiraCode@1.206/distr/fira_code.css";

document.head.appendChild(firaCode);

var style = document.createElement("style");

document.head.appendChild(style);

style.innerHTML = ExampleStyles$ReasonReactExamples.style;

function makeContainer(text) {
  var container = document.createElement("div");
  container.className = "container";
  var title = document.createElement("div");
  title.className = "containerTitle";
  title.innerText = text;
  var content = document.createElement("div");
  content.className = "containerContent";
  container.appendChild(title);
  container.appendChild(content);
  document.body.appendChild(container);
  return content;
}

function trace(param) {
  return /* record */[
          /* name */param[/* name */0],
          /* states */List.map(SMLToTheiaIR$ReasonReactExamples.smlToTheiaIR, SML$ReasonReactExamples.interpretTrace(param[/* example */1]))
        ];
}

function jsonToProgram(json) {
  console.log(json);
  return HaMLet2SMLAM$ReasonReactExamples.compileProgram(HaMLet2SMLAM$ReasonReactExamples.Decode.node(json));
}

function traceProgram(param) {
  var name = param[/* name */0];
  var payload = { };
  payload["file_name"] = name;
  payload["program"] = param[/* text */1];
  return fetch("http://localhost:5000", Fetch.RequestInit.make(/* Post */2, {
                        "Content-Type": "application/json"
                      }, Caml_option.some(JSON.stringify(payload)), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(trace(/* record */[
                                /* name */name,
                                /* example : Program */Block.__(9, [jsonToProgram(json)])
                              ]));
              }));
}

var traces = $$Array.map(traceProgram, /* array */[
      /* record */[
        /* name */"ex0",
        /* text */SMLExamples$ReasonReactExamples.ex0
      ],
      /* record */[
        /* name */"ex1",
        /* text */SMLExamples$ReasonReactExamples.ex1
      ],
      /* record */[
        /* name */"ex2",
        /* text */SMLExamples$ReasonReactExamples.ex2
      ],
      /* record */[
        /* name */"ex3",
        /* text */SMLExamples$ReasonReactExamples.ex3
      ],
      /* record */[
        /* name */"ex4",
        /* text */SMLExamples$ReasonReactExamples.ex4
      ],
      /* record */[
        /* name */"ex5",
        /* text */SMLExamples$ReasonReactExamples.ex5
      ],
      /* record */[
        /* name */"ex6",
        /* text */SMLExamples$ReasonReactExamples.ex6
      ],
      /* record */[
        /* name */"ex7",
        /* text */SMLExamples$ReasonReactExamples.ex7
      ],
      /* record */[
        /* name */"ex8",
        /* text */SMLExamples$ReasonReactExamples.ex8
      ],
      /* record */[
        /* name */"ex9",
        /* text */SMLExamples$ReasonReactExamples.ex9
      ],
      /* record */[
        /* name */"ex10",
        /* text */SMLExamples$ReasonReactExamples.ex10
      ]
    ]);

Promise.all(traces).then((function (theiaIRTraces) {
        return Promise.resolve((ReactDom.render(React.createElement(Theia$ReasonReactExamples.make, {
                              theiaIRTraces: theiaIRTraces
                            }), makeContainer("Theia")), /* () */0));
      }));

exports.firaCode = firaCode;
exports.style = style;
exports.makeContainer = makeContainer;
exports.trace = trace;
exports.jsonToProgram = jsonToProgram;
exports.traceProgram = traceProgram;
exports.traces = traces;
/* firaCode Not a pure module */
