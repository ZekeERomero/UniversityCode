if [ ! -d ".backup" ]; then
echo "Creating a backup subdirectory"
mkdir .backup
fi
for fileName in *
do
n="y"
echo "Creating backup of $fileName"
backupName=".backup/$fileName"
for backupFile in .backup/*
do
if [ $backupFile = $backupName ]
then
n="empty"
until [ $n = "y" ] || [ $n = "n" ]
do
read -p "$fileName already exists. Would you like to
replace it? (y/n): " n
done
fi
done
if [ $n = "y" ]
then
mv $fileName tempFile
cp tempFile $fileName
mv $fileName .backup
mv tempFile $fileName
fi
done
