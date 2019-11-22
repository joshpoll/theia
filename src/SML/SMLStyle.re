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
        ({theiaVizADT: Apply(ops, args, r)}) =>
          Util.interleave(List.map(Theia2.render, ops), List.map(Theia2.render, args))
          |> Util.prettierList(~parens=false, ~space=false),
      )
    | HSequence(l) =>
      HSequence(
        List.map(addRendering, l),
        Theia2.render,
        ReactDOMRe.Style.make(~gridGap="20px", ~alignItems="center", ()),
      )
    | VSequence(l) =>
      VSequence(
        List.map(addRendering, l),
        Theia2.render,
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
        ({keyRender, valueRender}) =>
          <tr>
            <td
              style={ReactDOMRe.Style.make(
                ~borderRight="1px solid black",
                ~paddingRight="5px",
                ~paddingTop="5px",
                ~textAlign="right",
                (),
              )}>
              {Theia2.render(keyRender)}
            </td>
            <td
              style={ReactDOMRe.Style.make(
                ~borderLeft="1px solid black",
                ~paddingLeft="5px",
                ~paddingTop="5px",
                ~textAlign="left",
                (),
              )}>
              {Theia2.render(valueRender)}
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
      let renderEC = (length, depth, {opsRender, argsRender, holePosRender}, hole) => {
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
            List.map(Theia2.render, argsRender),
            holePosRender,
          );
        Util.interleave(List.map(Theia2.render, opsRender), newArgs)
        |> Util.prettierList(~parens=false, ~space=false);
      };
      Kont(addRendering(focus), evalCtxtsRender, Theia2.render, renderEC);
    | Value(ops, args) =>
      Value(
        ops,
        List.map(addRendering, args),
        ({theiaVizADT: Value(ops, args, _)}) =>
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
                 theiaVizADT:
                   HSequence(
                     args,
                     Theia2.render,
                     ReactDOMRe.Style.make(~display="inline-grid", ()),
                   ),
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
                          {id: "val arg", theiaVizADT: Value([], [arg], Theia2.render)}
                        ),
                     Theia2.render,
                     ReactDOMRe.Style.make(~display="inline-grid", ()),
                   ),
               })}
            </div>
          },
      )
    | Cell(name, children) =>
      Cell(
        name,
        List.map(addRendering, children),
        ({theiaVizADT: Cell(name, children, _)}) =>
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
            {rlist(List.map(Theia2.render, children))}
          </div>,
      )
    },
};