#for file in /var/*
#do
    #echo $file
	#whatever you need with "$file"
#done

for fileName in *
do
	fileLower=${fileName,,}
	newFile=${fileLower//_}
	if [ $fileName = $newFile ]; then
		echo "'$fileName' is not an illegal file name"
	else
		echo "Renaming '$fileName' to '$newFile'"
		mv $fileName $newFile
	fi
done
