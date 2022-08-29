clear
ls *.c
echo Output file name:
read name
gcc -std=c99 *.c -o $name
clear
./$name
echo Done!
exit 0

