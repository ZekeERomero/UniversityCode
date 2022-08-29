Test="./test.sh "
clear

printf "htmlTest"
$Test htmlTest
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "quote"
$Test quote
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "quoteTest"
$Test quoteTest
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "textTest"
$Test textTest
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "textTest2"
$Test textTest2
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "badchar"
$Test badchar
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "cprogram"
$Test cprogram
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "f21"
$Test f21
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "gcd"
$Test gcd
read -n 1 -s -r -p "Press Enter to Continue"

clear
printf "stringTest"
$Test stringTest
read -n 1 -s -r -p "Press Enter to Continue"

printf "\n"
clear
