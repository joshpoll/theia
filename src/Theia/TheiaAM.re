type id = string;

type mapHeader = {
  keyHeader: option(string),
  valueHeader: option(string),
};

type theiaAM = {
  id,
  theiaAMADT,
}

and theiaAMADT =
  | Atom(ReasonReact.reactElement)
  | Apply(list(theiaAM), list(theiaAM))
  | HSequence(list(theiaAM))
  | VSequence(list(theiaAM))
  | Map(mapHeader, list(mapKeyValue))
  | Kont(theiaAM, list(evalCtxt))
  | Value(list(string), list(theiaAM)) /* TODO: should the first arg be list(theiaAM)? Also would
  have to propogate changes to TheiaViz */
  | Cell(string, list(theiaAM))
and mapKeyValue = {
  key: theiaAM,
  value: theiaAM,
}
and evalCtxt = {
  ops: list(theiaAM),
  args: list(theiaAM),
  holePos: int,
};