'use strict';


var reasonReactBlue = "#48a9dc";

var style = "\n  body {\n    font-family: \'Fira Code\', monospace;\n  }\n\n  button {\n    background-color: white;\n    color: black;\n    box-shadow: 0 0 0 1px black;\n    border: none;\n    padding: 8px;\n    font-size: 16px;\n  }\n\n  button:active {\n    background-color: " + (String(reasonReactBlue) + ";\n    color: white;\n  }\n");

exports.reasonReactBlue = reasonReactBlue;
exports.style = style;
/* style Not a pure module */
