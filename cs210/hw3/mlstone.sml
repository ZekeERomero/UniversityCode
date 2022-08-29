(* Ezequiel Romero *)

(* DISCLAIMER: Throughout this program, you will see a lot of 'val dummy'. This is a trick I used to get more out of my functions. They do not affect anything *)

(* Determine seed for game *)

val r = Random.rand(0,Real.floor(Time.toReal(Time.now())));

(* Beginning constants *)

val health = 30;
val aihealth = 30;
val mana = 1;
val emana = 1;
val round = 1;

(* All numbers are integers *)

(* All cards follow (cost, spellp, name, attack, health, ready) *)
(* The 'ready' slot determines if they are able to be played *)

(* Cards *)
val slug	=	(0,false,"Slug"		,2 ,1 ,"Not Ready");
val termite	=	(0,false,"Termite"	,1 ,4 ,"Not Ready");
val slime	=	(0,false,"Slime"	,3 ,1 ,"Not Ready");

val rat		=	(1,false,"Rat"		,2 ,2 ,"Not Ready");
val frost	=	(1,true ,"Frost"	,3 ,0 ,"Not Ready");
val healv1	=	(1,true ,"Heal v1"	,0 ,3 ,"Not Ready");
val spider	=	(1,false,"Spider"	,3 ,1 ,"Not Ready");

val direwolf	=	(2,false,"Dire Wolf"	,3 ,2 ,"Not Ready");
val zombie	=	(2,false,"Zombie"	,3 ,4 ,"Not Ready");
val flame	=	(2,true ,"Flame"	,4 ,0 ,"Not Ready");
val healv2	=	(2,true ,"Heal v2"	,0 ,4 ,"Not Ready");
val poison	=	(2,true ,"Poison"	,3 ,0 ,"Not Ready");

val goblin	= 	(3,false,"Goblin"	,3 ,5 ,"Not Ready");
val spirit	=	(3,false,"Spirit"	,5 ,1 ,"Not Ready");
val icicle	=	(3,true ,"Icicle"	,5 ,0 ,"Not Ready");
val healv3	=	(3,true ,"Heal v3"	,0 ,5 ,"Not Ready");
val skeleton	=	(3,false,"Skeleton"	,4 ,3 ,"Not Ready");

val orc		=	(4,false,"Orc"		,5 ,3 ,"Not Ready");
val icewisp	=	(4,false,"Ice Wisp"	,4 ,5 ,"Not Ready");
val lightning	=	(4,true ,"Lightning"	,6 ,0 ,"Not Ready");
val flood	=	(4,true ,"Flood"	,5 ,0 ,"Not Ready");
val healv4	=	(4,true ,"Heal v4"	,0 ,6 ,"Not Ready");

val guardian	=	(5,false,"Guardian"	,6 ,4 ,"Not Ready");
val lavaslime	=	(5,false,"Lava Slime"	,4 ,6 ,"Not Ready");
val healv5      =       (5,true ,"Heal v5"      ,0 ,7 ,"Not Ready");
val lavasplash	=	(5,true ,"Lava Splash"	,7 ,0 ,"Not Ready");
val ghost	=	(5,false,"Ghost"	,5 ,6 ,"Not Ready");

val icebeam	=	(6,true ,"Ice Beam"	,7 ,0 ,"Not Ready");
val fireball	=	(6,true ,"Fireball"	,8 ,0 ,"Not Ready");
val werewolf	=	(6,false,"Werewolf"	,7 ,6 ,"Not Ready");
val vampire	=	(6,false,"Vampire"	,6 ,7 ,"Not Ready");
val rockminion	=	(6,false,"Rock Minion"	,4 ,9 ,"Not Ready");

val demon	=	(7,false,"Demon"	,8 ,7 ,"Not Ready");
val yeti	=	(7,false,"Yeti"		,9 ,6 ,"Not Ready");
val siren	=	(7,false,"Siren"	,7 ,9 ,"Not Ready");
val healv6	=	(7,true ,"Heal v6"	,0 ,9 ,"Not Ready");
val minotaur	=	(7,false,"Minotaur"	,8 ,6 ,"Not Ready");

val dinosaur	=	(8,false,"Dinosaur"	,10,8 ,"Not Ready");
val cyclops	=	(8,false,"Cyclops"	,9 ,9 ,"Not Ready");
val firestorm	=	(8,true ,"Fire Storm"	,10,0 ,"Not Ready");
val tornado	=	(8,true ,"Tornado"	,9 ,0 ,"Not Ready");
val thunderwave	=	(8,true ,"Thunderwave"	,8 ,0 ,"Not Ready");

val dragon	=	(9,false,"Dragon"	,12,7 ,"Not Ready");
val healv7	=	(9,true ,"Heal v7"	,0 ,11,"Not Ready");
val serpent	=	(9,false,"Serpent"	,11,9 ,"Not Ready");
val tsunami	=	(9,true ,"Tsunami"	,11,0 ,"Not Ready");
val giant	=	(9,false,"Giant"	,10,10,"Not Ready");

val hydra	=	(10,false,"Hydra"	,11,14,"Not Ready");
val cyclone	=	(10,true ,"Cyclone"	,12,0 ,"Not Ready");
val titan	=	(10,false,"Titan"	,13,10,"Not Ready");
val deathworm	=	(10,false,"Death Worm"	,12,12,"Not Ready");
val kraken	=	(10,false,"Kraken"	,11,12 ,"Not Ready");

val worldeater	=	(11,false,"World Eater"	,15,15,"Not Ready");
val cthulu	=	(11,false,"Cthulu"	,15,15,"Not Ready");
val healv8	=	(11,true ,"Heal v8"	,0 ,15,"Not Ready");

val death	=	(12,false,"Death"	,20,20,"Not Ready");

(* This is the List of all cards. It is helpful when each player is given a random new card *)
val listOfCards = 	[slug,termite,slime,rat,frost,healv1,spider,direwolf,zombie,flame,healv2,poison,goblin,spirit,icicle,healv3,skeleton,
			orc,icewisp,lightning,flood,healv4,guardian,lavaslime,healv5,lavasplash,ghost,icebeam,fireball,tornado,thunderwave,
			dragon,healv7,serpent,tsunami,giant,hydra,cyclone,titan,deathworm,kraken,worldeater,cthulu,healv8,death];

(* This function is neat, in that it receives an upper and lower bound for a random number, which it returns *)
(* Got the Time object from Online and Random Function from class *)
fun random(low,high) = (
let
	val nextInt = Random.randRange(low,high)
	val random = nextInt r
in
	random
end
);

(* This function gives the player a random card depending on what round they're in *)
(* Example: is player is on Round 5, they can receive cards that cost between 1 and 5 mana *)
fun randomDeck([],pHand,mana) = pHand |
randomDeck((a,b,c,d,e,f)::xs,pHand,mana) = (
let
	val min = if ((mana - 4) < 0) then 0
	else if ((mana - 4) > 8) then 8
	else (mana - 4)
in
	if (a < mana+1) andalso (a > min-1) then (randomDeck(xs,(a,b,c,d,e,f)::pHand,mana))
	else (randomDeck(xs,pHand,mana))
end
);

(* This function determines the size of the list given *)
fun sizeOfDeck([],counter) = counter |
sizeOfDeck((a,b,c,d,e,f)::xs,counter) = (
	(sizeOfDeck(xs,counter+1))
);

(* This function acts as a middleman, first printing what the new cards are, then giving them *)
fun printCard((a,b,c,d,e,f)::xs,pHand,player,cards) = (
        if (player = 0) andalso (cards = 1) then print (": You Recieved a "^c^" card")
        else if (player = 1) andalso (cards = 1) then print("\n: Enemy Recieved a "^c^" card\n[Press Enter]")
	else print "";
let
        val str = if (player = 1) andalso (cards = 1) then valOf (TextIO.inputLine TextIO.stdIn) else ""
in
        pHand
end
);

(* This function receives the listOfCards list and determines which cards can be received by the player *)
fun chooseCard([],num,pHand,player,cards) = pHand |
chooseCard((a,b,c,d,e,f)::xs,num,pHand,player,cards) = (
let
	val num = num-1
	val pHand = if (num = 0) then (a,b,c,d,e,f)::pHand else pHand
in
	if (num = 0) then printCard(pHand,pHand,player,cards)
	else chooseCard(xs,num,pHand,player,cards)
end
);

(* This function starts the process for finding a new card based on how much the player is supposed to receive - 'cards' *)
fun newCards(pHand,mana,cards,player) = (
let
	val deck = randomDeck(listOfCards,[],mana)
	val size = sizeOfDeck(deck,0)
	val randomNum = random(1,size)
	val pHand = if (cards <> 0) then chooseCard(deck,randomNum,pHand,player,cards) else pHand
in
	if (cards <> 0) then newCards(pHand,mana,cards-1,player)
	else pHand
end
);

(* Hands and Boards*)
(* Beginning cards are random. Some may cost 2 mana in this instance only, hence - '2' *)

(* This is the 'player hand' list *)
val playerHand = newCards([],2,3,0);

(* This is the 'minion' list *)
val playerBoard = [];

(* This is the 'ai hand' list *)
val aiHand = newCards([],2,3,0);

(* This is the 'monster' list *)
val aiBoard = [];

(* 	Game Functions	    *)

(* This function is used to clear the screen *)
fun clear a = (
print("\n");
let
      val dummy = 0
in
      if (a<1) then print("\n")
      else clear(a-1)
end
);

(* These next to functions are useless, but they were made in the early stages of the game
when I did not know another workaround. They are somewhat primative *)
(* This function is used to increment values by any number *)
fun incr (value,x) = value+x;

(* This function is used to decrement values by any number *)
fun decr (value,x) = value-x;

(* To Play or Attack with any card, laws must be met first. Then, when a player does input a legal card they want to Play,
it sends a touple - '(0,0)' back to the 'gameloop' function you will see later. This touple determines which card the player uses,
which is the first element in the touple - '(2,0)', here being 2. It does this by traversing through the player's hand until it finds the
correct card, and when it does this, it records the amount of traversals needed to get to that card, hence 2 traversals. This number is 
used through the 'gameloop' function to modify its data. Other functions use this card by again traversing through the list 2 times to
find the same card, then playing it in this case. This is the same when a player Attacks an enemy with its card. Now, in this case, the
enemy card is placed in the second element - '(2,3)', here being 3. It uses the same process as stated previously to find it, and update its data. *)

(* If a player Ends their turn or Quits the match, it will send a touple with special values - '(90,0' or '(100,0)'
which envokes special cases in the 'gameloop' function *)

(* This function determines if the player is Playing a legal card, if so, then it returns the correct touple *)
fun loop ([],str,counter,mana) = (0,0) |
        loop((a,b,c,d,e,f)::xs,str,counter,mana) = (
let
        val counter = incr(1,counter)
in
        if (str = ("Play "^c^"\n")) andalso (a < mana+1) andalso (e <> 0) andalso (d = 0) then (counter,100)
	else if (str = ("Play "^c^"\n")) andalso (a < mana+1) then (counter,0)
	else loop(xs,str,counter,mana)
end
);

(* This function determines if the player is Attacking a legal card with a legal card, if so, then it returns the correct touple *)
fun loopAttack ([],[],str,counter,counter2,mana,pHand) = (0,0) 
	| loopAttack ((a,b,c,d,e,f)::xs,[],str,counter,counter2,mana,pHand) = (
let
        val counter = incr(1,counter)
in
        if (str = ("Attack Enemy with "^c^"\n")) andalso (f = "Ready") then (counter,90)
        else loopAttack(xs,[],str,counter,counter2,mana,pHand)
end
)
	| loopAttack ([],(g,h,i,j,k,l)::ys,str,counter,counter2,mana,pHand) = (
let
	val counter2 = incr(1,counter2)
in
	if (ys = []) then (0,0)
	else loopAttack(pHand,ys,str,0,counter2,mana,pHand)
end
)
	| loopAttack((a,b,c,d,e,f)::xs,(g,h,i,j,k,l)::ys,str,counter,counter2,mana,pHand) = (
let
        val counter = incr(1,counter)
in
        if(str = ("Attack "^i^" with "^c^"\n")) andalso (h = false) andalso (f = "Ready") then (counter,counter2)
        else if (str = ("Attack Enemy with "^c^"\n")) andalso (f = "Ready") then (counter,90)
	else loopAttack(xs,(g,h,i,j,k,l)::ys,str,counter,counter2,mana,pHand)
end
);

(* This function simply explodes a given string *)
fun breakdown x = explode x;

(* This function determines the first character in a given string *)
fun firstChar (x::xs) = Char.toString(x);

(* This function displays the rules of the game before the game starts *)
fun gamerules() = (
clear(50);
print "MLStone\n";
print "-------\n\n\n";
print "Rules:\n\n";
print "Note, all the text you see here must be met exactly, i.e. you must capitalize 'Play' and 'Attack' and every card,\n";
print "and lowercase 'with'\n\n";
print "To Play a Card onto the Board from your Hand, you must have enough mana and type:\n";
print "     Play 'your card'\n";
print "For example:\n";
print "     Play Goblin\n\n";
print "To Attack an Enemy Card, you must first Play it onto the Board and wait until the next round when it's Ready.\n";
print "You cannot attack a spell card and no attacks require mana. To attack, you must type:\n";
print "     Attack 'enemy card' with 'your card'\n";
print "For example:\n";
print "     Attack Dire Wolf with Goblin\n\n";
print "To Attack the Enemy's total health, type:\n";
print "     Attack Enemy with 'your card'\n";
print "For example:\n";
print "     Attack Enemy with Goblin\n\n";
print "When you Attack with a minion, it is also damaged by the object its attacking, unless its attacking the other player's total health\n";
print "When you Attack with a spell, it is simply removed from the board\n";
print "If you Play a heal spell, it is automatically used on the players total health\n\n";
print "At the End of every round, each player gets a new card. After round 6, each player is given two cards\n\n";
print "To End your Turn, type:\n";
print "     End\n";
print "To Quit the Game, type:\n";
print "     Quit\n\n";
print "Have Fun!";
print "\n\n[Press Enter]";
let
        val str = valOf (TextIO.inputLine TextIO.stdIn)
in
        print ""
end
);

(* This function determines which route to take depending on the players input *)
(* This is mostly used to avoid overbearing functions *)
fun commands(playerHand,playerBoard,aiHand,str,mana) = (
let
        val chr = breakdown(str)
        val first = firstChar(chr)
in
        if (first = "P") then loop(playerHand,str,0,mana)
        else if (first = "A") then loopAttack(playerBoard,aiHand,str,0,1,mana,playerBoard)
        else if (str = "End\n") then (90,0)
	else if (str = "Quit\n") then (100,0)
	else (0,0)
end
);

(* This function receives the raw string literal from the player *)
fun getNumber(playerHand,playerBoard,aiHand,mana) = (
print ": ";
let
    	val str = valOf (TextIO.inputLine TextIO.stdIn)	
in
	commands(playerHand,playerBoard,aiHand,str,mana)
end
);

(* This function acts as a buffer for the player. Basically, if the player inputs an illegal command, it will
let them try again *)
fun numberGet(playerHand,playerBoard,aiHand,mana) = (
let
	val loop = getNumber(playerHand,playerBoard,aiHand,mana)
in
	if(loop = (0,0)) then numberGet(playerHand,playerBoard,aiHand,mana)
	else loop
end
);

(* When the enemy plays or attacks with a card, it uses the exact same functions as the player uses.
To play or attack with a card, it simple determines which card it can use and returns the string literal
command with the name beforehand and then uses the same functions as the player. This saved a lot of headaches *)

(* This function is a middleman to print what card the enemy is playing and then returning that text *)
fun printPlay(name) = (
let
	val dummy = print("Enemy plays "^name^"\n[Press Enter]")	
	val str = valOf (TextIO.inputLine TextIO.stdIn)
in
	("Play "^name^"\n")
end
);

(* This function determines if the card has a higher cost than the last and returns its name *)
fun highCard((a,b,c,d,e,f),max,name) = if (a+1 > max) then c else name;

(* This function determines if the card has a higher cost than the last and returns its price *)
fun findMax((a,b,c,d,e,f),max) = if (a+1 > max) then a else max;

(* This function is used to determine what card the enemy plays *)
(* The enemy plays its highest card first *)
fun playEnemy([],mana,max,name) = ("\n") |
	playEnemy((a,b,c,d,e,f)::xs,mana,max,name) = (
let
	val name = if (a < mana+1) then highCard((a,b,c,d,e,f),max,name) else name
	val max = if (a < mana+1) then findMax((a,b,c,d,e,f),max) else max
in
	if (xs = []) andalso (name <> "") then printPlay(name)
	else playEnemy(xs,mana,max,name)
end
);

(* This function is a middleman to print what cards the enemy is attacking with and against and then returning that text *)
fun printAttack(name,enemy) = (
let
        val dummy = print("Enemy attacks your "^name^" with its "^enemy^"\n[Press Enter]")
        val str = valOf (TextIO.inputLine TextIO.stdIn)
in
	("Attack "^name^" with "^enemy^"\n")
end
);

(* This function is a middleman to print what cards the enemy is attacking the player with and returning that text *)
fun printAttackEnemy(enemy) = (
let
        val dummy = print("Enemy attacks YOU with its "^enemy^"\n[Press Enter]")
        val str = valOf (TextIO.inputLine TextIO.stdIn)
in
	("Attack Enemy with "^enemy^"\n")
end
);

(* This function determines which card the enemy will attack and with what card it will do so with *)
fun attackPlayer ([],[],pHand) = "\n"
| attackPlayer ((a,b,c,d,e,f)::xs,[],pHand) = (
	if (f = "Ready") then printAttackEnemy(c)
	else attackPlayer(xs,[],pHand)
)
| attackPlayer ([],(g,h,i,j,k,l)::ys,pHand) = (
	attackPlayer(pHand,ys,pHand)
)
| attackPlayer((a,b,c,d,e,f)::xs,(g,h,i,j,k,l)::ys,pHand) = (
	if (h = false) andalso (f = "Ready") then printAttack(i,c)
	else attackPlayer(xs,(g,h,i,j,k,l)::ys,pHand)
);

(* This function decides if the enemy will Play a card or Attack a card or End its turn *)
fun chooseAction(aiHand,aiBoard,playerBoard,mana,action) = (
let
	val rand = random(0,1);
in
	if (action = 1) then playEnemy(aiHand,mana,(0-1),"")
	else if (action = 2) andalso (rand = 0) then attackPlayer(aiBoard,playerBoard,aiBoard)
	else if (action = 2) andalso (rand = 1) then attackPlayer(aiBoard,[],aiBoard)
	else if (action = 3) then "End\n"
	else "\n"
end
);

(* This function determines the text the enemy uses and sends it to commands *)
fun numberEnemy(aiHand,aiBoard,playerBoard,mana,action) = (
print "Enemy's Turn:\n: ";
let
        val str = chooseAction(aiHand,aiBoard,playerBoard,mana,action)
in
        commands(aiHand,aiBoard,playerBoard,str,mana)
end
);

(* This function creates spaces to ensure a consistent display of data *)
fun space(textsize,endsize) = (
print (" ");
let
	val textsize = incr(textsize,1)
in
	if (endsize-textsize = 1) then print ""
	else space(textsize,endsize)
end
);

(* This function displays cards in the players hand *)
fun pHand [] = () |
	pHand((a,b,c,d,e,f)::xs) = (
print(  "     "^c);
space(size(c),14);
print(	Int.toString(a) );
space(	size(Int.toString(a)),8);
print(	Int.toString(d));
space(	size(Int.toString(d)),10);
print(	Int.toString(e));
space(	size(Int.toString(e)),10);
if (b = true) then print("Yes\n") else print("No\n");
let
	val dummy = 0
in
	pHand(xs)
end
);

(* This function displays the cards on the players board *)
fun pBoard [] = () |
        pBoard((a,b,c,d,e,f)::xs) = (
print(  "     "^c);
space(size(c),14);
print( "0" );
space(  1,8);
print(  Int.toString(d));
space(  size(Int.toString(d)),10);
print(  Int.toString(e));
space(  size(Int.toString(e)),10);
if (b = true) then print("Yes") else print("No");
if (b = true) then space(3,9) else space(2,9);
print(  f^"\n");
let
        val dummy = 0
in
        pBoard(xs)
end
);

(* This function prints all of the possible cards the player can Play *)
(* If this list is empty and the 'pAttackWith" function also returns empty,
the player's turn will automaticall end *)
fun pList ([],mana,counter) = if (counter = 0) then 0 else 1 |
	pList(((a,b,c,d,e,f)::xs),mana,counter) = (
if (counter > 0) andalso (a<mana+1) then print ", " else print "";
if (a<mana+1) then print(c) else print "";
let
	val counter = if (a<mana+1) then incr(counter,1) else counter
in
	pList(xs,mana,counter)
end
);

(* This function prints all of the possible cards the player can Attack *)
fun pAttack ([],counter) = () |
        pAttack((a,b,c,d,e,f)::xs,counter) = (
if (counter > 0) andalso (b = false) then print ", " else print "";
if (b = false) then print(c) else print "";
let
        val counter = if (b = false) then incr(counter,1) else counter
in
        pAttack(xs,counter)
end
);

(* This function prints all of the possible cards the player can Attack with*)
fun pAttackWith ([],counter) = if (counter = 0) then 0 else 1 |
        pAttackWith((a,b,c,d,e,f)::xs,counter) = (
if (counter > 0) andalso (f = "Ready") then print ", " else print "";
if (f = "Ready") then print(c) else print "";
let
        val counter = if (f = "Ready") then incr(counter,1) else counter
in
        pAttackWith(xs,counter)
end
);

(* This function adds the Played card to the Board*)
fun playBoard (pBoard,[],(num,extra)) = pBoard |
	playBoard (pBoard,(a,b,c,d,e,f)::xs,(num,extra)) = (
let
	val num = decr(num,1)
in
	if(num = 0) andalso (extra = 0) then (a,b,c,d,e,f)::pBoard
	else if (num <> 89) then playBoard(pBoard,xs,(num,extra))
	else pBoard
end
);

(* This function removes the Played card from the players Hand *)
fun playHand ([],(num,extra),pHand) = pHand |
        playHand ((a,b,c,d,e,f)::xs,(num,extra),pHand) = (
let
        val num = decr(num,1)
in
        if (num <> 0 andalso extra = 0) then (playHand(xs,(num,extra),(a,b,c,d,e,f)::pHand))
        else if (num <> 0 andalso extra = 100) then (playHand(xs,(num,extra),(a,b,c,d,e,f)::pHand))
	else if (num = 89) then pHand
	else playHand(xs,(num,extra),pHand)
end
);

(* This function removes the mana used from the Played card *)
fun playMana (mana,[],(num,extra)) = mana |
        playMana (mana,(a,b,c,d,e,f)::xs,(num,extra)) = (
let
        val num = decr(num,1)
in
        if (num = 0 andalso extra = 0) then decr(mana,a)
        else if (num = 0 andalso extra = 100) then decr(mana,a)
	else if (num <> 89) then playMana(mana,xs,(num,extra))
        else mana
end
);

(* This function determines if the player Attacked anything *)
fun attackAI(num,extra) = if (extra = 0) orelse (extra = 100) then 0 else 1;

(* This function damages the Enemy with the card used by the player *)
fun damageEnemy(aihealth,[],(num,extra)) = aihealth |
	damageEnemy(aihealth,(a,b,c,d,e,f)::xs,(num,extra)) = (
let
	val num = decr(num,1)
in
	if (num = 0) andalso (extra = 90) then aihealth-d
	else damageEnemy(aihealth,xs,(num,extra))
end
);

(* This function removes any spells from the Board and makes any card used unavailable to use again *)
fun removeBoard([],(num,extra),pHand) = pHand |
	removeBoard((a,b,c,d,e,f)::xs,(num,extra),pHand) = (
let
        val num = decr(num,1)
in
        if(num <> 0) andalso (extra <> 0) andalso (extra <> 100) then (removeBoard(xs,(num,extra),(a,b,c,d,e,f)::pHand))
        else if (num = 89) then (a,b,c,d,e,f)::xs
	else if (extra = 0) orelse (extra = 100) then (a,b,c,d,e,f)::xs
        else if (num = 0) andalso (b = true) then removeBoard(xs,(num,extra),pHand)
	else if (num = 0) andalso (b = false) then removeBoard(xs,(num,extra),(a,b,c,d,e,"Not Ready")::pHand)
	else pHand
end
);

(* This function displays the end of the game if you won *)
fun youWon() = (
clear(100);
print "\nYou Won!\n\n";
let
	val dummy = 0
in
	print ""
end
);

(* This function displays the end of the game if you lost *)
fun youLost() = (
clear(100);
print "\nYou Lost!\n\n";
let
        val dummy = 0
in
        print ""
end
);

(* This function displays the end of the game if you quit *)
fun youForfeit() = (
clear(100);
print "\nYou Forfeit!\n\n";
let
	val dummy = 0
in
	print ""
end
);

(* This function damages the enemy card with the card used by the player *)
fun damageECard(damage,extra,[],enemyBoard) = enemyBoard |
        damageECard(damage,extra,(a,b,c,d,e,f)::xs,enemyBoard) = (
let
        val extra = decr(extra,1)
in
        if (extra = 0) andalso (b = false) then damageECard(damage,extra,xs,(a,b,c,d,e-damage,f)::enemyBoard)
        else damageECard(damage,extra,xs,(a,b,c,d,e,f)::enemyBoard)
end
);

(* This function determines which enemy card on the board to damage *)
fun damageEBoard([],(num,extra),aiBoard) = aiBoard |
	damageEBoard((a,b,c,d,e,f)::xs,(num,extra),aiBoard) = (
let
	val num = decr(num,1)
in
	if (num = 0) andalso (extra <> 0) andalso (extra <> 100) then damageECard(d,extra,aiBoard,[])
	else if (extra = 0) orelse (extra = 100) then aiBoard
	else damageEBoard(xs,(num,extra),aiBoard)
end
);

(* This function removes any minion card that has 0 or less health *)
fun checkCards([],pHand) = pHand |
        checkCards((a,b,c,d,e,f)::xs,pHand) =
        if(e > 0) orelse (b = true) then (checkCards(xs,(a,b,c,d,e,f)::pHand))
        else checkCards(xs,pHand);

(* This function makes all cards on the board 'ready' to use at the beginning of each round *)
fun readyBoard([],pBoard) = pBoard |
        readyBoard((a,b,c,d,e,f)::xs,pBoard) = (readyBoard(xs,(a,b,c,d,e,"Ready")::pBoard));

(* This function heals the player *)
fun heal(health,(num,extra),[]) = health |
	heal(health,(num,extra),(a,b,c,d,e,f)::xs) = (
let
	val num = decr(num,1)
in
	if (num = 0) andalso (extra = 100) then health+e
	else heal(health,(num,extra),xs)
end
);

(* This function reverses the touple to damage the attacking card with the opposing card *)
fun reverseCard(num,extra) = (extra,num);

(* This function reverses the board because every function that uses the board reverses it.
This basically reverts the Board back to what is was originally *)
fun reverseBoard([],pBoard) = pBoard |
reverseBoard((a,b,c,d,e,f)::xs,pBoard) = reverseBoard(xs,(a,b,c,d,e,f)::pBoard);

(* This command calls game.sml which contains the game state *)
use "game.sml";

fun exit() = (OS.Process.exit(OS.Process.success); false);

(* This function is the what the entire game is run on. It loops forever until the player either wins, loses, or forfeits *)
fun gameloop(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard,endturn,action,endround) = (
let
	(* These values are used throughout this loop to update the Boards if necessary*)
	val pBoard = playerBoard
	val eBoard = aiBoard

	(* These sorts of calls to the 'gamesate' display the status of the game *)
	val dummy = gamestate(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard)
	
	(* These process 'ready' up the board *)
	val playerBoard = if (endround = 1) then readyBoard(playerBoard,[]) else playerBoard
		val playerBoard = if (endround = 1) then reverseBoard(playerBoard,[]) else playerBoard
	val pBoard = playerBoard
	val aiBoard = if (endround = 1) then readyBoard(aiBoard,[]) else aiBoard
		val aiBoard = if (endround = 1) then reverseBoard(aiBoard,[]) else aiBoard
	val eBoard = aiBoard

	(* These processes give each player new cards*)

        val playerHand = if (endround = 1) then newCards(playerHand,round,1,0) else playerHand
        val aiHand = if (endround = 1) then newCards(aiHand,round,1,1) else aiHand

	val dummy = if (endround = 1) andalso (round > 5) then gamestate(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard) else print""

	val playerHand = if (endround = 1) andalso (round > 5) then newCards(playerHand,6,1,0) else playerHand
	val aiHand = if (endround = 1) andalso (round > 5) then newCards(aiHand,6,1,1) else aiHand

	(* These processes determine what the player Plays or Attacks*)	
	val dummy = if (endround = 1) then gamestate(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard) else print ""
	val dummy = if (endturn = 0) then print "Your Turn:\nCan Play: " else print ""
	val play  = if (endturn = 0) then pList(playerHand,mana,0) else 0
	val dummy = if (endturn = 0) then print "\nCan Attack: " else print ""
	val dummy = if (endturn = 0) then pAttack(aiBoard,0) else print ""
        val dummy = if (endturn = 0) then print "\nCan Attack With: " else print ""
	val attack = if (endturn = 0) then pAttackWith(playerBoard,0) else 0
	val dummy = if (endturn = 0) then print "\n" else print ""
	val cards = (0,0)
	val cards = if (endturn = 0) andalso (attack = 0) andalso (play = 0) then (90,0)
		else if (endturn = 0) then numberGet(playerHand,playerBoard,aiBoard,mana)
		else cards
	val dummy = if (endturn = 0) andalso (attack = 0) andalso (play = 0) then print ": You cannot Play nor Attack, so your turn Ends\n[Press Enter]" else print ""
	val str = if (endturn = 0) andalso (attack = 0) andalso (play = 0) then valOf (TextIO.inputLine TextIO.stdIn) else ""

	val endturn = if (endturn = 0) andalso (cards = (90,0)) then 1 else endturn
	val mana = if (endturn = 0) then playMana(mana,playerHand,cards) else mana
	val attack = if (endturn = 0) then attackAI(cards) else 0
	val health = if (endturn = 0) then heal(health,cards,playerHand) else health
	val playerBoard = if (endturn = 0) andalso (attack = 0) then playBoard(playerBoard,playerHand,cards) else playerBoard
	
	val pBoard = playerBoard
	val playerHand = if (endturn = 0) andalso (attack = 0) then playHand(playerHand,cards,[]) else playerHand
	val aihealth = if (endturn = 0) then  damageEnemy(aihealth,playerBoard,cards) else aihealth

	val aiBoard = if (endturn = 0) andalso (attack = 1) then damageEBoard(playerBoard,cards,aiBoard) else aiBoard	
		val aiBoard = if (endturn = 0) andalso (eBoard <> aiBoard) then reverseBoard(aiBoard,[]) else aiBoard
	val eBoard = aiBoard

	val reversecards = if (endturn = 0) andalso (attack = 1) then reverseCard(cards) else (0,0)
	val playerBoard = if (endturn = 0) andalso (attack = 1) then damageEBoard(aiBoard,reversecards,playerBoard) else playerBoard
		val playerBoard = if (endturn = 0) andalso (pBoard <> playerBoard) then reverseBoard(playerBoard,[]) else playerBoard
	val pBoard = playerBoard
	val playerBoard = if (endturn = 0) andalso (attack = 1) then removeBoard(playerBoard,cards,[]) else playerBoard
		val playerBoard = if (endturn = 0) andalso (pBoard <> playerBoard) then reverseBoard(playerBoard,[]) else playerBoard
	val pBoard = playerBoard

	(* These processes determine what the Enemy Plays or Attacks*)
	val enemycards = (0,0)
	val enemycards = if (endturn = 1) andalso (action <> 0) then numberEnemy(aiHand,aiBoard,playerBoard,emana,action) else enemycards
	val action = if (action < 3) andalso (endturn = 1) andalso (enemycards = (0,0)) then incr(action,1) else action
	val endturn = if (endturn = 1) andalso (enemycards = (90,0)) then 2 else endturn
	val action = if (endturn = 2) then 0 else action
	val emana = if (endturn = 1) then playMana(emana,aiHand,enemycards) else emana
	val attackP = if(endturn = 1) then attackAI(enemycards) else 0
	val aihealth = if (endturn = 1) then heal(aihealth,enemycards,aiHand) else aihealth
	val aiBoard = if (endturn = 1) andalso (attackP = 0) then playBoard(aiBoard,aiHand,enemycards) else aiBoard
	
	val eBoard = aiBoard
	val aiHand = if (endturn = 1) andalso (attackP = 0) then playHand(aiHand,enemycards,[]) else aiHand

	val health = if (endturn = 1) then damageEnemy(health,aiBoard,enemycards) else health

        val playerBoard = if (endturn = 1) andalso (attackP = 1) then damageEBoard(aiBoard,enemycards,playerBoard) else playerBoard
		val playerBoard = if (endturn = 1) andalso (pBoard <> playerBoard) then reverseBoard(playerBoard,[]) else playerBoard
	val pBoard = playerBoard
	val reverseenemycards = if (endturn = 1) andalso (attackP = 1) then reverseCard(enemycards) else (0,0)
	val aiBoard = if (endturn = 1) andalso (attackP = 1) then damageEBoard(playerBoard,reverseenemycards,aiBoard) else aiBoard
		val aiBoard = if (endturn = 1) andalso (eBoard <> aiBoard) then reverseBoard(aiBoard,[]) else aiBoard
        val eBoard = aiBoard
	val aiBoard = if (endturn = 1) andalso (attackP = 1) then removeBoard(aiBoard,enemycards,[]) else aiBoard
		val aiBoard = if (endturn = 0) andalso (eBoard <> aiBoard) then reverseBoard(aiBoard,[]) else aiBoard
	val eBoard = aiBoard

	(* If both the Player and the Enemy End their turns, these processes occur, signifying the end of the round *)
	val endround = if (endturn = 2) then 1 else 0
	val endturn = if (endround = 1) then 0 else endturn
	
	val aiBoard = checkCards(aiBoard,[])
	
	val playerBoard = checkCards(playerBoard,[])

	(* These processes update all of the game stats if it is the end of the round*)
	val round = if (endround = 1) then incr(round,1) else round
	val mana = if (endround = 1) then round else mana
	val emana = if (endround = 1) then round else emana

	(* This value determines if the player has won, lost, or quit yet*)
	val endgame = if (aihealth <= 0) then 1 else if (health <= 0) then 2 else if (cards = (100,0)) then 3 else 0
in
	(* This IF STATEMENT determines if it should run again based on the outcome of the game so far *)
	if (endgame = 0) then gameloop(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard,endturn,action,endround)
	else if (endgame = 1) then youWon()
	else if (endgame = 2) then youLost()
	else youForfeit()
end
);

(* This presents the rules first *)
gamerules();

(* This starts the game *)
gameloop(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard,0,0,0);

(* This ends the program\sml *)
exit();
