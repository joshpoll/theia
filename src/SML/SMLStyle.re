/* Default SML style */
open Util;
open TheiaAM;
open TheiaViz;

let rlist = l => l |> Array.of_list |> React.array;

let rec addRendering = ({id, theiaAMADT}) => {
  id,
  theiaVizADT:
    switch (theiaAMADT) {
    | Atom(re) => Atom(re, ({theiaVizADT: Atom(re, _)}) => re)
    | Apply(ops, args) =>
      Apply(
        List.map(addRendering, ops),
        List.map(addRendering, args),
        (opsViz, argsViz) =>
          Util.interleave(opsViz, argsViz) |> Util.prettierList(~parens=false, ~space=false),
      )
    | HSequence(l) =>
      HSequence(
        List.map(addRendering, l),
        ReactDOMRe.Style.make(~gridGap="20px", ~alignItems="center", ()),
      )
    | VSequence(l) =>
      VSequence(
        List.map(addRendering, l),
        ReactDOMRe.Style.make(~gridGap="20px", ~alignItems="center", ()),
      )
    | Map({keyHeader, valueHeader}, kvs) =>
      Map(
        {keyHeader, valueHeader},
        List.map(
          ({key, value}) => {keyRender: addRendering(key), valueRender: addRendering(value)},
          kvs,
        ),
        ({keyHeader, valueHeader}) => {
          let keyHeader =
            switch (keyHeader) {
            | None => Util.nbsp
            | Some(keyHeader) => keyHeader
            };
          let valueHeader =
            switch (valueHeader) {
            | None => Util.nbsp
            | Some(valueHeader) => valueHeader
            };
          {
            keyHeaderRender:
              <th
                style={ReactDOMRe.Style.make(
                  ~border="1px solid black",
                  ~paddingRight="5px",
                  ~textAlign="right",
                  (),
                )}>
                {React.string(keyHeader)}
              </th>,
            valueHeaderRender:
              <th
                style={ReactDOMRe.Style.make(
                  ~border="1px solid black",
                  ~paddingLeft="5px",
                  ~textAlign="left",
                  (),
                )}>
                {React.string(valueHeader)}
              </th>,
          };
        },
        ({keyRenderViz, valueRenderViz}) =>
          <tr>
            <td
              style={ReactDOMRe.Style.make(
                ~borderRight="1px solid black",
                ~paddingRight="5px",
                ~paddingTop="5px",
                ~textAlign="right",
                (),
              )}>
              keyRenderViz
            </td>
            <td
              style={ReactDOMRe.Style.make(
                ~borderLeft="1px solid black",
                ~paddingLeft="5px",
                ~paddingTop="5px",
                ~textAlign="left",
                (),
              )}>
              valueRenderViz
            </td>
          </tr>,
        ({keyHeaderRender, valueHeaderRender}, kvVizes) =>
          <table
            style={ReactDOMRe.Style.make(
              ~borderCollapse="collapse",
              ~borderStyle="hidden",
              ~display="inline-table",
              (),
            )}>
            <thead> <tr> keyHeaderRender valueHeaderRender </tr> </thead>
            <tbody> {kvVizes |> rlist} </tbody>
          </table>,
      )
    | Kont(focus, evalCtxts) =>
      let evalCtxtsRender =
        evalCtxts
        |> List.map(({ops, args, holePos}) =>
             {
               opsRender: List.map(addRendering, ops),
               argsRender: List.map(addRendering, args),
               holePosRender: holePos,
             }
           );
      /* TODO: use length info */
      let renderEC = (length, depth, {opsRenderViz, argsRenderViz, holePosRenderViz}, hole) => {
        let backgroundColor =
          if (hole == React.string(Util.nbsp)) {
            "red";
          } else {
            "hsla(240, 100%, " ++ string_of_int(80 - depth * 5) ++ "%, 0.33)";
          };
        ();
        let newArgs =
          Util.insert(
            <div style={ReactDOMRe.Style.make(~display="inline-block", ~backgroundColor, ())}>
              hole
            </div>,
            argsRenderViz,
            holePosRenderViz,
          );
        Util.interleave(opsRenderViz, newArgs) |> Util.prettierList(~parens=false, ~space=false);
      };
      Kont(addRendering(focus), evalCtxtsRender, renderEC);
    | Value(ops, args) =>
      let rec renderValue = ({theiaVizADT: Value(ops, args, _)}) =>
        switch (ops) {
        | [] =>
          <div
            style={ReactDOMRe.Style.make(
              ~display="inline-block",
              ~border="1px solid black",
              ~paddingTop="2px",
              ~paddingRight="2px",
              ~paddingBottom="2px",
              ~paddingLeft="2px",
              (),
            )}>
            {Theia2.render({
               id: "val args",
               theiaVizADT: HSequence(args, ReactDOMRe.Style.make(~display="inline-grid", ())),
             })}
          </div>
        | ops =>
          <div
            style={ReactDOMRe.Style.make(
              ~display="inline-block",
              ~border="1px solid #000",
              ~paddingTop="10px",
              ~paddingRight="10px",
              ~paddingBottom="10px",
              ~paddingLeft="10px",
              (),
            )}>
            <h1
              style={ReactDOMRe.Style.make(
                ~textAlign="center",
                ~marginTop="-10px",
                ~fontSize="15px",
                (),
              )}>
              <span>
                {Util.interleave(ops, 1 -- (List.length(ops) - 1) |> List.map(_ => "•"))
                 |> List.fold_left((++), "")
                 |> React.string}
              </span>
            </h1>
            {Theia2.render({
               id: "val args",
               theiaVizADT:
                 HSequence(
                   args
                   |> List.map(arg =>
                        {id: "val arg", theiaVizADT: Value([], [arg], renderValue)}
                      ),
                   ReactDOMRe.Style.make(~display="inline-grid", ()),
                 ),
             })}
          </div>
        };
      Value(ops, List.map(addRendering, args), renderValue);
    | Cell(name, children) =>
      Cell(
        name,
        List.map(addRendering, children),
        childrenViz =>
          <div
            style={ReactDOMRe.Style.make(
              ~border="1px solid #000",
              ~paddingTop="10px",
              ~paddingRight="10px",
              ~paddingBottom="10px",
              ~paddingLeft="10px",
              (),
            )}>
            <h1
              style={ReactDOMRe.Style.make(
                ~textAlign="center",
                ~marginTop="-10px",
                ~fontSize="15px",
                (),
              )}>
              <span style={ReactDOMRe.Style.make(~backgroundColor="white", ())}>
                {React.string(name)}
              </span>
            </h1>
            {rlist(childrenViz)}
          </div>,
      )
    },
};