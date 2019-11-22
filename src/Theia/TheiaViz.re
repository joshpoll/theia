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
  | Apply(list(theiaViz), list(theiaViz), renderApply)
  | HSequence(array(theiaViz), ReactDOMRe.Style.t)
  | VSequence(array(theiaViz), ReactDOMRe.Style.t)
  | Map(mapHeader, array(mapKeyValue), renderMapHeader, renderKV, renderMap)
  | Kont(theiaViz, list(evalCtxt), renderEC)
  | Value(list(string), list(theiaViz), render)
  | Cell(string, list(theiaViz), renderCell)
and mapKeyValue = {
  keyRender: theiaViz,
  valueRender: theiaViz,
}
and mapKeyValueViz = {
  keyRenderViz: ReasonReact.reactElement,
  valueRenderViz: ReasonReact.reactElement,
}
and evalCtxt = {
  opsRender: list(theiaViz),
  argsRender: list(theiaViz),
  holePosRender: int,
}
and evalCtxtViz = {
  opsRenderViz: list(ReasonReact.reactElement),
  argsRenderViz: list(ReasonReact.reactElement),
  holePosRenderViz: int,
}
and render = theiaViz => ReasonReact.reactElement
and renderApply =
  (list(ReasonReact.reactElement), list(ReasonReact.reactElement)) => ReasonReact.reactElement
and renderCell = list(ReasonReact.reactElement) => ReasonReact.reactElement
and renderMapHeader = mapHeader => mapHeaderViz
and renderKV = mapKeyValueViz => ReasonReact.reactElement
and renderMap = (mapHeaderViz, array(ReasonReact.reactElement)) => ReasonReact.reactElement
// length, depth, ctxt, hole contents
and renderEC = (int, int, evalCtxtViz, ReasonReact.reactElement) => ReasonReact.reactElement;