#! /bin/bash

# Script to calculate the average and standard deviation for the number of opinion groups.

if (( $# != 14 ))
then 
	echo "Usage: $0 <nagents> <X> <initial_value> <interval> <number of ysize values> <g> <op_threshold> <shape> <topology> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <# of runs>"
	exit 1
fi


for (( i=0; i<$5; i++))

do
	e=$(( $i * $4 + $3 ))
	if (( $e < 10 ))
	then
		e="0000"$e
	elif (( $e < 100 ))
	then
		e="000"$e
	elif (( $e < 1000 ))
	then
		e="00"$e
	elif (( $e < 10000 ))
		e="0"$e
	fi

	stat3_rw2.bash $1 $2 $e $6 $7 $8 $9 ${10} ${11} ${12} ${13} ${14}

done
