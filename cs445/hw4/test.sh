printf "\nMaking the files\n"
printf "\nOutputting the output to out.txt\n"
./c- -P $1.c- > out.txt
printf "\nComparing test.out and out.txt\n"
diff -y $1.out out.txt
diff <(sort $1.out) <(sort out.txt) >> dummyTestData
if [ $? -ne 0 ]; then
	printf "\nxxTEST WAS UNSUCCESSFULxx\n"
	printf "\nTest Complete\n"
	printf "\nIssues: (Yours: top)\n"
	diff <(sort $1.out) <(sort out.txt)
	printf "\n"
	exit 10
else
	printf "\n*****TEST WAS SUCCESSFUL*****\n"
	printf "\nTest Complete\n\n"
	exit 11
fi
