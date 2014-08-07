#! /bin/bash

# Script to calculate the average and standard deviation for the number of opinion groups.

if (( $# != 14 ))
then 
	echo "Usage: $0 <density> <X> <initial_value> <interval> <number of ysize values> <g> <op_threshold> <shape> <topology> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <# of runs>"
	exit 1
fi


for (( i=0; i<$5; i++))

do
	e=$(( $i * $4 + $3 ))
	n=$(( $1 * $2 * $e ))
	if (( $e < 10 ))
	then
		e="00000"$e
		n="00000"$n
	elif (( $e < 100 ))
	then
		e="0000"$e
		n="0000"$n
	elif (( $e < 1000 ))
	then
		e="000"$e
		n="000"$n
	elif (( $e < 10000 ))
	then
		e="00"$e
		n="00"$n
	elif (( $e < 100000 ))
	then
		e="0"$e
		n="0"$n
	fi

	stat3_rw2_noAG.bash $n $2 $e $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14}

done
