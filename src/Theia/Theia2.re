open TheiaViz;
let rlist = l => l |> Array.of_list |> React.array;

exception CompileError(string);

/* and finally pretty printing! */
let rec render = theiaViz => {
  let {id, theiaVizADT} = theiaViz;
  // Js.log("rendering: " ++ id);
  switch (theiaVizADT) {
  | Atom(_, render) => render(theiaViz)
  | Apply(_, _, render) => render(theiaViz)
  | HSequence(l, renderElement, style) =>
    let style =
      ReactDOMRe.Style.make(~display="grid", ~gridAutoFlow="column", ~gridTemplateRows="1fr", ())
      |> ReactDOMRe.Style.combine(style);
    <div style>
      {Array.mapi(
         (i, e) => <div key={string_of_int(i)}> {renderElement(e)} </div>,
         l /* |> List.rev */
       )
       |> React.array}
    </div>;
  | VSequence(l, renderElement, style) =>
    let style =
      ReactDOMRe.Style.make(~display="grid", ~gridAutoFlow="column", ~gridTemplateRows="1fr", ())
      |> ReactDOMRe.Style.combine(style);
    <div style>
      {Array.mapi((i, e) => <div key={string_of_int(i)}> {renderElement(e)} </div>, l)  /* |> List.rev */
       |> React.array}
    </div>;
  | Map(mapHeader, l, renderMapHeader, renderKV, renderMap) =>
    renderMap(
      renderMapHeader(mapHeader),
      l
      |> Array.map(({keyRender, valueRender}) =>
           {keyRenderViz: render(keyRender), valueRenderViz: render(valueRender)}
         )
      |> Array.map(renderKV),
    )
  | Kont(focus, evalCtxts, renderFocus, renderEC) =>
    let evalCtxtsLength = List.length(evalCtxts);
    let rec renderKont = (ecs, depth) =>
      switch (ecs) {
      | [] => renderFocus(focus)
      | [ec, ...ecs] => renderEC(evalCtxtsLength, depth, ec, renderKont(ecs, depth + 1))
      };
    renderKont(
      evalCtxts
      |> List.map(({opsRender, argsRender, holePosRender}) =>
           {
             opsRenderViz: List.map(render, opsRender),
             argsRenderViz: List.map(render, argsRender),
             holePosRenderViz: holePosRender,
           }
         )
      |> List.rev,
      0,
    );
  | Value(_, _, render) => render(theiaViz)
  | Cell(_, _, render) => render(theiaViz)
  };
};

type configuration = {k: list(ReasonReact.reactElement)};

type state = {
  trace: option(list(ReasonReact.reactElement)),
  currentConfig: int,
};

type action =
  | UpdateMachineState(configuration)
  | StepBack
  | StepForward;

type print =
  | KNode
  | TheiaIR
  | TheiaIRShort
  | Json
  | Theia;

/* TODO: error handling */
let handleClick = (~theiaIRTrace, dispatch, _event) => {
  dispatch(UpdateMachineState({k: List.map(render, theiaIRTrace)}));
};

type trace = {
  name: string,
  states: list(theiaViz) // TODO: this should be theiaAM and rendering should go somewhere.
};

type traceOutput = {
  path: string,
  log: string,
  name: string,
};

[@react.component]
let make = (~theiaIRTraces: array(trace)) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | UpdateMachineState(s) => {trace: Some(s.k), currentConfig: 0}
        | StepBack => {...state, currentConfig: max(0, state.currentConfig - 1)}
        | StepForward => {
            ...state,
            currentConfig:
              min(
                state.currentConfig + 1,
                List.length(Belt.Option.getWithDefault(state.trace, [<> </>])) - 1,
              ),
          }
        },
      {trace: None, currentConfig: 0},
    );

  /* register keyboard events */
  let handleKeyPressed = e => {
    switch (Webapi.Dom.KeyboardEvent.key(e)) {
    | "ArrowLeft" => dispatch(StepBack)
    | "ArrowRight" => dispatch(StepForward)
    | _ => ()
    };
  };
  Util.useKeyPressed(handleKeyPressed);

  /* TODO: use a drop-down menu? */
  <div>
    <button onClick={_ => dispatch(StepBack)}> {React.string("<-")} </button>
    <button onClick={_ => dispatch(StepForward)}> {React.string("->")} </button>
    {theiaIRTraces
     |> Array.map(({states, name}) =>
          <button onClick={handleClick(~theiaIRTrace=states, dispatch)}>
            {React.string(name)}
          </button>
        )
     |> React.array}
    {
      let renderConfig = my_option =>
        switch (my_option) {
        | None => <> </>
        | Some(v) => v
        };

      switch (state.trace) {
      | None => <> </>
      | Some(s) =>
        /* https://www.joomlashack.com/blog/tutorials/center-and-align-items-in-css-grid/ */
        let boxSize = 10000;
        <div
          style={ReactDOMRe.Style.make(
            ~display="grid",
            ~gridTemplateColumns=
              "fit-content(350px) 20px fit-content(350px) 20px fit-content(350px)",
            ~alignItems="center",
            (),
          )}>
          <div
            style={ReactDOMRe.Style.make(
              ~float="left",
              ~maxWidth=string_of_int(boxSize) ++ "px",
              (),
            )}>
            {s->Belt.List.get(state.currentConfig)->renderConfig}
          </div>
          <div style={ReactDOMRe.Style.make(~float="left", ~textAlign="center", ())}>
            <b> {React.string("->")} </b>
          </div>
          <div
            style={ReactDOMRe.Style.make(
              ~float="left",
              ~maxWidth=string_of_int(boxSize) ++ "px",
              (),
            )}>
            {s->Belt.List.get(state.currentConfig + 1)->renderConfig}
          </div>
        </div>;
      };
    }
  </div>;
};