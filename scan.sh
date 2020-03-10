#! /usr/bin/bash

#  By: Evan Wheeler
#  UCID# 30046173

# Usage: ./scan.sh [suffix] [N] [type]
# args suffix, N, type

# Checks for 3 args and exits if there are not 3
if [ $# -ne 3 ]
then
	echo "Usage: ./scan.sh [suffix] [N] [type]"
	exit 1
fi

# Store the suffix, N, and type (slows the program down but improves readability)
suffix=$1
N=$2
type=$3

# Find the total size of all files containing the suffix
totalSize=$(find . -type f -name '*'${suffix} -printf "%p	%s\n" | awk '{ x += $2 } END {print x}')

# First prints the top n files containing the suffix
# Then finds sum of the sizes in the n files
if [[ ${type} -eq '0' ]]
then
	find . -type f -name '*'${suffix} -printf "%p	%s\n" | sort -t"	" -k 2 -n | head -n ${N} | awk '{ x += $2 ; print $1 "\t" $2}'
	partialSize=$(find . -type f -name '*'${suffix} -printf "%p	%s\n" | sort -t"	" -k 2 -n | head -n ${N} | awk '{ x += $2 } END {print x}')
elif [[ ${type} -eq '1' ]]
then
	find . -type f -name '*'${suffix} -printf "%p	%s\n" | sort -t"	" -k 2 -n -r | head -n ${N} | awk '{ x += $2 ; print $1 "\t" $2}'
	partialSize=$(find . -type f -name '*'${suffix} -printf "%p	%s\n" | sort -t"	" -k 2 -n -r | head -n ${N} | awk '{ x += $2 } END {print x}')
else
	echo "Usage: ./scan.sh [suffix] [N] [type]"
	exit 1
fi

# Prints the total size of all files with the suffix
echo "Total Size:	$((totalSize))"

# Prints the size of the N files
echo "Part size:	$((partialSize))"

# Calculate the percentage |n files| / |all files|. Because bash does integer
# arithmetic the percentage will be truncated to the nearest percent
percentage=$(( ( $((partialSize)) * 100 ) / $((totalSize)) ))

# Prints the percentage
echo "Percent:	$((percentage))"
