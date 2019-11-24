open TheiaViz;

let rec applyStyleToId = (style, targetId, {id, theiaVizADT}) => {
  let applyStyleToId = applyStyleToId(style, targetId);
  /* TODO: might be more elegant to set style to empty here if id doesn't match */
  {
    id,
    theiaVizADT:
      if (targetId == id) {
        switch (theiaVizADT) {
        | Atom(re) => Atom(<div style> re </div>)
        | Apply(ops, args, renderApply) =>
          Apply(
            List.map(applyStyleToId, ops),
            List.map(applyStyleToId, args),
            (ops, args) => <div style> {renderApply(ops, args)} </div>,
          )
        | HSequence(l, s) =>
          HSequence(List.map(applyStyleToId, l), s |> ReactDOMRe.Style.combine(style))
        | VSequence(l, s) =>
          VSequence(List.map(applyStyleToId, l), s |> ReactDOMRe.Style.combine(style))
        | Map(mapHeader, l, renderMapHeader, renderKV, renderMap) =>
          Map(
            mapHeader,
            List.map(
              ({keyRender, valueRender}) =>
                {
                  keyRender: applyStyleToId(keyRender),
                  valueRender: applyStyleToId(valueRender),
                },
              l,
            ),
            mh =>
              renderMapHeader(mh)
              |> (
                ({keyHeaderRender, valueHeaderRender}) => {
                  keyHeaderRender: <div style> keyHeaderRender </div>,
                  valueHeaderRender: <div style> valueHeaderRender </div>,
                }
              ),
            kv => <div style> {renderKV(kv)} </div>,
            (mh, l) => <div style> {renderMap(mh, l)} </div>,
          )
        | Kont(focus, evalCtxts, renderEC) =>
          Kont(
            applyStyleToId(focus),
            List.map(
              ({opsRender, argsRender, holePosRender}) =>
                {
                  opsRender: List.map(applyStyleToId, opsRender),
                  argsRender: List.map(applyStyleToId, argsRender),
                  holePosRender,
                },
              evalCtxts,
            ),
            (l, d, ec, f) => <div style> {renderEC(l, d, ec, f)} </div>,
          )
        | Value(_, _, render) => theiaVizADT /* TODO!! */
        | Cell(name, children, renderCell) =>
          Cell(
            name,
            List.map(applyStyleToId, children),
            l => <div style> {renderCell(l)} </div>,
          )
        };
      } else {
        switch (theiaVizADT) {
        | Atom(_) => theiaVizADT
        | Apply(ops, args, renderApply) =>
          Apply(List.map(applyStyleToId, ops), List.map(applyStyleToId, args), renderApply)
        | HSequence(l, style) => HSequence(List.map(applyStyleToId, l), style)
        | VSequence(l, style) => VSequence(List.map(applyStyleToId, l), style)
        | Map(mapHeader, l, renderMapHeader, renderKV, renderMap) =>
          Map(
            mapHeader,
            List.map(
              ({keyRender, valueRender}) =>
                {
                  keyRender: applyStyleToId(keyRender),
                  valueRender: applyStyleToId(valueRender),
                },
              l,
            ),
            renderMapHeader,
            renderKV,
            renderMap,
          )
        | Kont(focus, evalCtxts, renderEC) =>
          Kont(
            applyStyleToId(focus),
            List.map(
              ({opsRender, argsRender, holePosRender}) =>
                {
                  opsRender: List.map(applyStyleToId, opsRender),
                  argsRender: List.map(applyStyleToId, argsRender),
                  holePosRender,
                },
              evalCtxts,
            ),
            renderEC,
          )
        | Value(_, _, render) => theiaVizADT /* TODO!! */
        | Cell(name, children, renderCell) =>
          Cell(name, List.map(applyStyleToId, children), renderCell)
        };
      },
  };
};