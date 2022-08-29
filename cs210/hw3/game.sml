(* This function prints the status of the game *)
fun gamestate(mana,emana,round,aihealth,health,playerHand,aiHand,playerBoard,aiBoard) = (
clear(100);
print(  "Round "^Int.toString(round)^"\n\n\n"^
        "Player Health: "^Int.toString(health)^"\n"^
        "Enemy Health: "^Int.toString(aihealth)^"\n"^
        "Player Mana: "^Int.toString(mana)^"\n"^
        "Enemy Mana: "^Int.toString(emana)^"\n") ;
print(  "\nPlayer Hand:\n");
print(  "     Name         Cost   Damage   Health   Spell\n");
pHand(playerHand);
print(  "\nEnemy Hand:\n");
print(  "     Name         Cost   Damage   Health   Spell\n");
pHand(aiHand);
print(  "\nPlayer Board:\n");
print(  "     Name         Cost   Damage   Health   Spell\n");
pBoard(playerBoard);
print(  "\nEnemy Board:\n");
print(  "     Name         Cost   Damage   Health   Spell\n");
pBoard(aiBoard);
print(  "\n");
let
	val dummy = 0;
in
	print ""
end
);
