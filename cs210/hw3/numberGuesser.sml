val r = Random.rand(0,Real.floor(Time.toReal(Time.now())));

fun random(low,high) = (
let
        val nextInt = Random.randRange(low,high)
        val random = nextInt r
in
        random
end
);

fun clear(num) = (
print "\n";
let
	val dummy = 0
in
	if (num > 0) then clear(num-1) else print ""
end
);

fun loop(random) = (
let
	val dummy = clear(100)
	val dummy = print "\nChoose a number: "
	val str = valOf (TextIO.inputLine TextIO.stdIn)
	val num : int = valOf (Int.fromString str)
	val dummy = if (num > random) then print "Lower!" else print ""
	val dummy = if (num < random) then print "Higher!" else print ""
	val dummy =if (num = random) then print "You got it!" else print ""
	val dummy = valOf (TextIO.inputLine TextIO.stdIn)
in	
	if (num <> random) then loop(random) else print ""
end
);

val rand = random(1,100);
loop(rand);
