/* like TheiaAM but with rendering hooks */

type id = string;

type mapHeader = {
  keyHeader: option(string),
  valueHeader: option(string),
};

type mapHeaderViz = {
  keyHeaderRender: ReasonReact.reactElement,
  valueHeaderRender: ReasonReact.reactElement,
};

type theiaViz = {
  id,
  theiaVizADT,
}

and theiaVizADT =
  | Atom(ReasonReact.reactElement, render)
  | Apply(list(theiaViz), list(theiaViz), render)
  | HSequence(list(theiaViz), render, ReactDOMRe.Style.t)
  | VSequence(list(theiaViz), render, ReactDOMRe.Style.t)
  | Map(mapHeader, list(mapKeyValue), renderMapHeader, renderKV, renderMap)
  | Kont(theiaViz, list(evalCtxt), render, renderEC)
  | Value(list(string), list(theiaViz), render)
  | Cell(string, list(theiaViz), render)
and mapKeyValue = {
  keyRender: theiaViz,
  valueRender: theiaViz,
}
and evalCtxt = {
  opsRender: list(theiaViz),
  argsRender: list(theiaViz),
  holePosRender: int,
}
and render = theiaViz => ReasonReact.reactElement
and renderMapHeader = mapHeader => mapHeaderViz
and renderKV = mapKeyValue => ReasonReact.reactElement
and renderMap = (mapHeaderViz, list(ReasonReact.reactElement)) => ReasonReact.reactElement
// length, depth, ctxt, hole contents
and renderEC = (int, int, evalCtxt, ReasonReact.reactElement) => ReasonReact.reactElement;