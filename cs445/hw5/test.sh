if [[ $2 != "-f" ]]; then
	printf "\nMaking the files\n"
	printf "\nOutputting the output to out.txt\n"
fi

./c- -P $1.c- > out.txt

if [[ $2 != "-f" ]]; then
	printf "\nComparing test.out and out.txt\n"
fi

if [ -z "$2" ]; then
	diff -y $1.out out.txt
else
	if [[ $2 != "-f" ]]; then
                diff -y $1.out out.txt
        fi
fi

diff <(sort $1.out) <(sort out.txt) >> dummyTestData

if [ $? -ne 0 ]; then
	if [[ $2 != "-f" ]]; then
		printf "\nxxTEST WAS UNSUCCESSFULxx\n"
		printf "\nTest Complete\n"
		printf "\nIssues: (Yours: top)\n"
		diff <(sort $1.out) <(sort out.txt)
		printf "\n"
	fi
	exit 10
else
	if [[ $2 != "-f" ]]; then
		printf "\n*****TEST WAS SUCCESSFUL*****\n"
		printf "\nTest Complete\n\n"
	fi
	exit 11
fi
