#! /bin/bash

# Script to calculate the average and standard deviation for the number of opinion groups.

if (( $# != 14 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <initial_value*100> <interval*100> <number of g values> <op_threshold> <shape> <topology> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <# of runs>"
	exit 1
fi


for (( i=0; i<$6; i++))

do
	e=$(( $i * $5 + $4 ))
	if (( $e < 10 ))
	then
		e="0.0"$e
	elif (( $e < 100 ))
	then
		e="0."$e
	else
		e="1"
	fi

	stat3_rw2.bash $1 $2 $3 $e $7 $8 $9 ${10} ${11} ${12} ${13} ${14}
done
