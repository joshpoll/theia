open SML;

let ex0 = "5";

let ex1 = "let val x = 5 in x end";

let ex2 = "val x = 34";

let ex3 = "val x = 34;
val y = 17";

let ex4 = "()";

let ex5 = "(5, 78)";

let ex6 = "val z = 5 + 78";

let ex7 = "val x = 34;
val y = 17;
val z = 5 + 78";

let ex8 = "val x = 34;
val y = 17;
val z = (x + y) + (y + 2)";

let ex9 = "val x = 34;
val y = 17;
val z = (x + y) + (y + 2);
val q = z + 1";

let ex10 = "val a = 1;
val b = 2;
val a = 3";

let ex11 = "if true then 1 else 2";

let ex12 = "val x = 34;
val y = 17;
val z = (x + y) + (y + 2);
val q = z + 1;
val abs_of_z = if z < 0 then 0 - z else z";

let ex13 = "fun id x = x";

/* This example seems to be too big. Need to switch to lazy execution of some things to boost
   performance. */
let lec02_1 = "fun pow(x,y) =
  if y=0
  then 1
  else x * pow(x,y-1)

fun cube x =
  pow(x,3)

val sixtyfour = cube 4

val fortytwo = pow(2,2+2) + pow(4,2) + cube(2) + 2";

let lec02_1_simpler = "fun pow(x,y) =
  if y=0
  then 1
  else x * pow(x,y-1)

fun cube x =
  pow(x,3)

val sixtyfour = cube 4";