// Entry point

[@bs.val] external document: Js.t({..}) = "document";

// We're using raw DOM manipulations here, to avoid making you read
// ReasonReact when you might precisely be trying to learn it for the first
// time through the examples later.

let firaCode = document##createElement("link");
firaCode##rel #= "stylesheet";
firaCode##href #= "https://cdn.jsdelivr.net/gh/tonsky/FiraCode@1.206/distr/fira_code.css";
document##head##appendChild(firaCode);

let style = document##createElement("style");
document##head##appendChild(style);
style##innerHTML #= ExampleStyles.style;

let makeContainer = text => {
  let container = document##createElement("div");
  container##className #= "container";

  let title = document##createElement("div");
  title##className #= "containerTitle";
  title##innerText #= text;

  let content = document##createElement("div");
  content##className #= "containerContent";

  let () = container##appendChild(title);
  let () = container##appendChild(content);
  let () = document##body##appendChild(container);

  content;
};

// All 4 examples.
/* ReactDOMRe.render(
  <BlinkingGreeting>
    {React.string("Hello!")}
  </BlinkingGreeting>,
  makeContainer("Blinking Greeting"),
); */

/* ReactDOMRe.render(
  <ReducerFromReactJSDocs />,
  makeContainer("Reducer From ReactJS Docs"),
); */

/* ReactDOMRe.render(
  <FetchedDogPictures />,
  makeContainer("Fetched Dog Pictures"),
); */

/* ReactDOMRe.render(
  <ReasonUsingJSUsingReason />,
  makeContainer("Reason Using JS Using Reason"),
); */

type test = {name: string, example: SML.focus};

let tests =
  SMLExamples.[
    {name: "ex0", example: ex0},
    {name: "ex1", example: ex1},
    {name: "ex2", example: ex2},
    {name: "ex3", example: ex3},
    {name: "ex4", example: ex4},
    {name: "ex5", example: ex5},
    {name: "ex6", example: ex6},
    {name: "ex7", example: ex7},
    {name: "ex8", example: ex8},
    {name: "ex9", example: ex9},
    {name: "ex10", example: ex10},
    {name: "ex11", example: ex11},
  ]

let trace = ({name, example}) => Theia.{name, states: example |> SML.interpretTrace |> List.map(SMLToTheiaIR.smlToTheiaIR)};

ReactDOMRe.render(
  <Theia theiaIRTraces={List.map(trace, tests)} />,
  makeContainer("Theia"),
);

let line = HaMLet2SMLAM.testJson |> Json.parseOrRaise
                |> HaMLet2SMLAM.Decode.node;
Js.Console.log(line);
Js.Console.log(line |> HaMLet2SMLAM.compileProgram);
