printf "\nMaking the files\n"
make
printf "\nOutputting the output to out.txt\n"
./c- tests/$1.c- > out.txt
printf "\nComparing test.out and out.txt\n"
diff -y tests/$1.out out.txt
if [ $? -ne 0 ]; then
	printf "\nxxTEST WAS UNSUCCESSFULxx\n"
else
	printf "\n*****TEST WAS SUCCESSFUL*****\n"
fi
printf "\nTest Complete\n\n"
