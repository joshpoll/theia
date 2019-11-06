/* Parse and compile HaMLet SML ASTs to SML AM ASTs */

module P = ReludeParse.Parser;
open P.Infix; 

Js.Console.log(P.runParser("1", P.anyDigit));

/* HaMLet output for "val x = 34;" in file "test.sml" */
let test = "(Program test.sml:1.0-1.11
  (STRDECTopDec test.sml:1.0-1.10
    (DECStrDec test.sml:1.0-1.10
      (VALDec test.sml:1.0-1.10
        (Seq test.sml:1.10-1.10
        )
        (PLAINValBind test.sml:1.4-1.10
          (ATPat test.sml:1.4-1.5
            (IDAtPat test.sml:1.4-1.5
              (LongVId x)
            )
          )
          (ATExp test.sml:1.8-1.10
            (SCONAtExp test.sml:1.8-1.10
              (INTSCon 34)
            )
          )
        )
      )
    )
  )
)";

type sourceMapInfo = {file: string, l1: int, c1: int, l2: int, c2: int};

type longVId = string;

type sCon =
  | INTSCon(int)

and atExp =
  | SCONAtExp(sourceMapInfo, sCon)

and exp =
  | ATExp(sourceMapInfo, atExp)

and valBind =
  | PLAINValBind(sourceMapInfo, pat, exp)

and atPat =
  | IDAtPat(sourceMapInfo, longVId)

and pat =
  | ATPat(sourceMapInfo, atPat);

let parseBetweenParens = (p) => P.between(P.str("("), P.str(")"), P.ws *> p <* P.ws);

let parseSourceMapInfo =
  P.tuple5(
    P.anyCharNotIn([":"]) |> P.manyUntil(P.str(":")) |> P.map(Relude.List.foldRight((++), "")),
    P.anyUnsignedInt,
    P.str(".") *> P.anyUnsignedInt,
    P.str("-") *> P.anyUnsignedInt,
    P.str(".") *> P.anyUnsignedInt
  ) |> P.map(((file, l1, c1, l2, c2)) => {file, l1, c1, l2, c2});

/* TODO: not sure why I can't just use parseBetweenParens with anyStr. anyStr seems too greedy and
may be gobbling up the ) */
let parseLongVId =
  P.leftParen *>
  P.str("LongVId") *>
  P.ws *>
  (P.anyCharNotIn([")"]) |> P.manyUntil(P.str(")")) |> P.map(Relude.List.foldRight((++), "")))

let parseINTSCon =
((n) => INTSCon(n)) <$>
  parseBetweenParens(
    P.str("INTSCon") *>
    P.ws *>
    P.anyInt
  );

let parseSCon = parseINTSCon;

let parseSCONAtExp =
  (((smi, sc)) => SCONAtExp(smi, sc)) <$>
  parseBetweenParens(
    P.tuple2(
      P.str("SCONAtExp") *>
      P.ws *>
      parseSourceMapInfo,
      P.ws *> parseSCon
    )
  );

let parseAtExp = parseSCONAtExp;

let parseATExp =
  (((smi, a)) => ATExp(smi, a)) <$>
    parseBetweenParens(
      P.tuple2(
        P.str("ATExp") *>
        P.ws *>
        parseSourceMapInfo,
        P.ws *> parseAtExp
      )
    );

let parseExp = parseATExp;

let rec parsePLAINValBind =
(((smi, p, e)) => PLAINValBind(smi, p, e)) <$>
  parseBetweenParens(
    P.tuple3(
      P.str("PLAINValBind") *>
      P.ws *>
      parseSourceMapInfo,
      P.ws *> parsePat,
      P.ws *> parseExp
    )
  )

and parseValBind = parsePLAINValBind

and parseIDAtPat =
  (((smi, vid)) => IDAtPat(smi, vid)) <$>
  parseBetweenParens(
    P.tuple2(
      P.str("IDAtPat") *>
      P.ws *>
      parseSourceMapInfo,
      P.ws *> parseLongVId
    )
  )

and parseAtPat = parseIDAtPat

and parseATPat =
  (((smi, ap)) => ATPat(smi, ap)) <$>
  parseBetweenParens(
    P.tuple2(
      P.str("ATPat") *>
      P.ws *>
      parseSourceMapInfo,
      P.ws *> parseAtPat
    )
  )

and parsePat = parseATPat;

/* let output =
  parsePat
  |> P.runParser("(ATPat test.sml:1.4-1.5
            (IDAtPat test.sml:1.4-1.5
              (LongVId x)
            )
          )");
 */

let output = parseExp |> P.runParser("(ATExp test.sml:1.8-1.10
            (SCONAtExp test.sml:1.8-1.10
              (INTSCon 34)
            )
          )");
