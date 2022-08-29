ls
n="empty"
until [ $n = "a" ] || [ $n = "r" ]
do
	read -p "Do you want to add or remove line numbers? (a/r): " n
done

if [ $n = "a" ]; then
	read -p "File Name: " fileName
	sed '/./=' $fileName | sed '/./N; s/\n/ /' > tempFile.txt
	rm $fileName
	cp tempFile.txt $fileName
        rm tempFile.txt
fi
if [ $n = "r" ]; then
	read -p "File Name: " fileName
	sed 's/ *[0-9]*.//' $fileName > tempFile.txt
	rm $fileName
	cp tempFile.txt $fileName
	rm tempFile.txt
fi
