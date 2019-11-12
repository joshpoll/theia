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

type test = {
  name: string,
  example: SML.focus,
};

let trace = ({name, example}) =>
  Theia.{name, states: example |> SML.interpretTrace |> List.map(SMLToTheiaIR.smlToTheiaIR)};

let jsonToProgram = json => {
  Js.Console.log(json);
  json |> HaMLet2SMLAM.Decode.node |> HaMLet2SMLAM.compileProgram;
};

type program = {
  name: string,
  text: string,
};

let traceProgram = ({name, text}) => {
  let payload = Js.Dict.empty();
  Js.Dict.set(payload, "file_name", Js.Json.string(name));
  Js.Dict.set(payload, "program", Js.Json.string(text));
  Js.Promise.(
    Fetch.fetchWithInit(
      "http://localhost:5000",
      Fetch.RequestInit.make(
        ~method_=Post,
        ~body=Fetch.BodyInit.make(Js.Json.stringify(Js.Json.object_(payload))),
        ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
        (),
      ),
    )
    |> then_(Fetch.Response.json)
    |> then_(json => Js.Promise.resolve(trace({name, example: Program(jsonToProgram(json))})))
  );
};

let traces =
  SMLExamples.(
    [|
      {name: "ex0", text: ex0},
      {name: "ex1", text: ex1},
      {name: "ex2", text: ex2},
      {name: "ex3", text: ex3},
      {name: "ex4", text: ex4},
      {name: "ex5", text: ex5},
      {name: "ex6", text: ex6},
      {name: "ex7", text: ex7},
      {name: "ex8", text: ex8},
      {name: "ex9", text: ex9},
      {name: "ex10", text: ex10},
      {name: "ex11", text: ex11},
      {name: "ex12", text: ex12},
      {name: "ex13", text: ex13},
      {name: "lec02-1-simple", text: lec02_1_simpler},
      {name: "lec02-2-simple", text: lec02_2_simple},
      {name: "lec02-3", text: lec02_3},
    |]
  )
  |> Array.map(traceProgram);

Js.Promise.all(traces)
|> Js.Promise.then_(theiaIRTraces =>
     Js.Promise.resolve(ReactDOMRe.render(<Theia theiaIRTraces />, makeContainer("Theia")))
   ) /* ReactDOMRe.render(<DagreTest />, makeContainer("DagreTest"))*/;