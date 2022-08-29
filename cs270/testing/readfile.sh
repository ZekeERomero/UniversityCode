#!/bin/bash
input="file.txt"
while IFS= read -r line
do
	IFS=' '
	name=0
	arr=()
	read -ra ADDR <<< "$line"
	for i in "${ADDR[@]}"; do
		if (($name > 0)); then
			arr+=($i)
		else
			echo "$i"
		fi
		name=$((name+1))
	done
	declare -i sum
	IFS=+ sum="${arr[*]}"
	echo 'Average score:' $sum
	unset arr
	
done < "$input"
