testC="./test.sh "
testFile="testDataA3"
clear

for FILE in $testFile/*.c-; do
	string=${FILE/".c-"/""};
	printf "$string"
	$testC $string
	read -n 1 -s -r -p "Press Enter to Continue"
	clear
done

clear

printf "Testing Complete!\n"
