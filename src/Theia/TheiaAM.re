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
  | HSequence(array(theiaAM))
  | VSequence(array(theiaAM))
  | Map(mapHeader, array(mapKeyValue))
  | Kont(theiaAM, list(evalCtxt))
  | Value(list(string), list(theiaAM))
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