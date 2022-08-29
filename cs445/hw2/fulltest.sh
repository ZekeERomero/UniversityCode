testC="./test.sh "
testFile="testDataA2"
clear

for FILE in testDataA2/*.c-; do
	string=${FILE/".c-"/""};
	newString=${string/"$testFile/"/""}
	printf "$newString"
	$testC $newString
	read -n 1 -s -r -p "Press Enter to Continue"
	clear
done

clear

printf "Testing Complete!\n"
