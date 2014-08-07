#! /bin/bash

# Script to find the distributions of opinions for each x position.

if (( $# != 5 ))
then
	echo "Usage: $0 <initial t> <interval t> <# of t values> <input file> <output file>"
	exit 1
fi

if [ -f $4 ]; then
	echo "" > /dev/null
else
	echo "Input file, $4, doesn't exist."
	exit 1
fi

for (( i=0; i<$3; i++ ))
do
	t=$(( $i * $2 + $1 ))
	if (( t < 10 )); then
		t1="00000"$t
	elif (( t < 100 )); then
		t1="0000"$t
	elif (( t < 1000 )); then
		t1="000"$t
	elif (( t < 10000 )); then
		t1="00"$t
	elif (( t < 100000 )); then
		t1="0"$t
	else
		t1=$t
	fi
	outfile=$5"_t"$t1

	gawk -v t=$t '{
   		if ($1==t) 
   			print $3, $5;
   	}' $4 > $outfile
done
