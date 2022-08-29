read input

echo "NoSpaces${input}Boi"

allThreads=(1 2 4 8 16 32 64 128)

for i in ${!allThreads[@]}; do
	echo ${allThreads[$i]}
done

allThreads+=(256 512)

for i in ${!allThreads[@]}; do
        echo ${allThreads[$i]}
done
