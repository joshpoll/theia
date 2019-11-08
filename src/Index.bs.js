'use strict';

var Json = require("@glennsl/bs-json/src/Json.bs.js");
var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
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

var tests_000 = /* record */[
  /* name */"ex2",
  /* example */SMLExamples$ReasonReactExamples.ex2
];

var tests_001 = /* :: */[
  /* record */[
    /* name */"ex3",
    /* example */SMLExamples$ReasonReactExamples.ex3
  ],
  /* :: */[
    /* record */[
      /* name */"ex4",
      /* example */SMLExamples$ReasonReactExamples.ex4
    ],
    /* :: */[
      /* record */[
        /* name */"ex5",
        /* example */SMLExamples$ReasonReactExamples.ex5
      ],
      /* :: */[
        /* record */[
          /* name */"ex6",
          /* example */SMLExamples$ReasonReactExamples.ex6
        ],
        /* :: */[
          /* record */[
            /* name */"ex7",
            /* example */SMLExamples$ReasonReactExamples.ex7
          ],
          /* :: */[
            /* record */[
              /* name */"ex8",
              /* example */SMLExamples$ReasonReactExamples.ex8
            ],
            /* :: */[
              /* record */[
                /* name */"ex9",
                /* example */SMLExamples$ReasonReactExamples.ex9
              ],
              /* :: */[
                /* record */[
                  /* name */"ex10",
                  /* example */SMLExamples$ReasonReactExamples.ex10
                ],
                /* :: */[
                  /* record */[
                    /* name */"ex0",
                    /* example : Program */Block.__(9, [HaMLet2SMLAM$ReasonReactExamples.compileProgram(HaMLet2SMLAM$ReasonReactExamples.Decode.node(Json.parseOrRaise(SMLExamples$ReasonReactExamples.ex0)))])
                  ],
                  /* :: */[
                    /* record */[
                      /* name */"ex1",
                      /* example : Program */Block.__(9, [HaMLet2SMLAM$ReasonReactExamples.compileProgram(HaMLet2SMLAM$ReasonReactExamples.Decode.node(Json.parseOrRaise(SMLExamples$ReasonReactExamples.ex1)))])
                    ],
                    /* :: */[
                      /* record */[
                        /* name */"ite",
                        /* example : Program */Block.__(9, [HaMLet2SMLAM$ReasonReactExamples.compileProgram(HaMLet2SMLAM$ReasonReactExamples.Decode.node(Json.parseOrRaise(SMLExamples$ReasonReactExamples.exITE)))])
                      ],
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]
  ]
];

var tests = /* :: */[
  tests_000,
  tests_001
];

function trace(param) {
  return /* record */[
          /* name */param[/* name */0],
          /* states */List.map(SMLToTheiaIR$ReasonReactExamples.smlToTheiaIR, SML$ReasonReactExamples.interpretTrace(param[/* example */1]))
        ];
}

ReactDom.render(React.createElement(Theia$ReasonReactExamples.make, {
          theiaIRTraces: List.map(trace, tests)
        }), makeContainer("Theia"));

function parseProgam(file_name, program, callback) {
  return fetch("http://localhost:5000", Fetch.RequestInit.make(/* Post */2, {
                        "Content-Type": "application/x-www-form-urlencoded"
                      }, Caml_option.some("file_name=" + (file_name + ("&program=" + program))), undefined, undefined, undefined, undefined, undefined, undefined, undefined, undefined)(/* () */0)).then((function (prim) {
                  return prim.json();
                })).then((function (json) {
                return Promise.resolve(Curry._1(callback, json));
              }));
}

parseProgam("ex0", "5", (function (json) {
        console.log(Json.stringify(json));
        return /* () */0;
      }));

exports.firaCode = firaCode;
exports.style = style;
exports.makeContainer = makeContainer;
exports.tests = tests;
exports.trace = trace;
exports.parseProgam = parseProgam;
/* firaCode Not a pure module */
