#!/bin/bash

testC="./test.sh "
testFile="testDataA4"
clear
count=0
correct=0

make clean
make

for FILE in $testFile/*.c-; do
	let count=$count+1
	string=${FILE/".c-"/""};
	
	if [[ $1 != "-f" ]]; then
		printf "$string"
	fi
	
	if [ -z "$1" ]; then
		$testC $string
	else
		$testC $string $1
	fi

	retn_code=$?

	if [ $retn_code -eq 11 ]; then
		let correct=$correct+1
	fi

	if [ -z "$1" ]; then
		read -n 1 -s -r -p "Press Enter to Continue"
	elif [[ $1 != "-f" ]]; then
		if [[ $1 == "-s" ]]; then
                        if [ $retn_code -eq 10 ]; then
                                read -n 1 -s -r -p "Press Enter to Continue"
                        fi
                else
                        read -n 1 -s -r -p "Press Enter to Continue"
                fi
	fi

	clear
done

clear

printf "Testing Complete!\n"
printf $correct
printf " out of "
printf $count
printf " correct!\n"
if [ $correct -eq $count ]; then
	printf "All were correct!\n"
fi
