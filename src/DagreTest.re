open Dagre;

type state = Graph.t;

let init = () => {
  let nodes = [
    ("0", "nil"),
    ("1", "1"),
    ("2", "2"),
    ("3", "3"),
    // ("kspacey", "Kevin Spacey"),
    // ("swilliams", "Saul Williams"),
    // ("bpitt", "Brad Pitt"),
    // ("hford", "Harrison Ford"),
    // ("lwilson", "Luke Wilson"),
    // ("kbacon", "Kevin Bacon"),
  ];
  let edges = [
    ("0", "1"),
    ("1", "2"),
    ("2", "3"),
    // ("kspacey", "swilliams"),
    // ("swilliams", "kbacon"),
    // ("bpitt", "kbacon"),
    // ("hford", "lwilson"),
    // ("lwilson", "kbacon"),
  ];

  let attrs = Graph.Attrs.make(~rankdir=Rank.Dir.LeftRight, ());
  let graph = Graph.make(~attrs, ());
  Graph.setDefaultEdgeAttrs(graph, () => {"minlen": 2});

  Belt.List.forEach(nodes, ((id, label)) =>
    Graph.setNodeWith(graph, id, Node.attrs(~label, ~width=40, ~height=40, ()))
  );

  Belt.List.forEach(edges, ((v, w)) => Graph.setEdge(graph, Edge.t(~v, ~w, ())));

  graph;
};

[@react.component]
let make = () => {
  let (state, _) = React.useState(init);

  let layout = Layout.make(state);

  <div> <DagrePlot layout /> </div>;
};