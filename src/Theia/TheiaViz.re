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
  | Atom(ReasonReact.reactElement)
  | Apply(list(theiaViz), list(theiaViz), renderApply)
  | HSequence(list(theiaViz), ReactDOMRe.Style.t)
  | VSequence(list(theiaViz), ReactDOMRe.Style.t)
  | Map(mapHeader, list(mapKeyValue), renderMapHeader, renderKV, renderMap)
  | Kont(theiaViz, list(evalCtxt), renderEC)
  | Value(list(string), list(theiaViz), renderValue)
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
/* render types */
and renderApply =
  (list(ReasonReact.reactElement), list(ReasonReact.reactElement)) => ReasonReact.reactElement
and renderCell = list(ReasonReact.reactElement) => ReasonReact.reactElement
and renderMapHeader = mapHeader => mapHeaderViz
and renderKV = mapKeyValueViz => ReasonReact.reactElement
and renderMap = (mapHeaderViz, list(ReasonReact.reactElement)) => ReasonReact.reactElement
// length, depth, ctxt, hole contents
and renderEC = (int, int, evalCtxtViz, ReasonReact.reactElement) => ReasonReact.reactElement
and renderValue = (list(string), list(ReasonReact.reactElement)) => ReasonReact.reactElement;