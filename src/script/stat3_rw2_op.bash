#! /bin/bash

# Script to calculate the average and standard deviation for the number of opinion groups.

if (( $# != 14 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <g> <initial_value*1000> <interval*1000> <number of op_thres values> <shape> <topology> <# of runs>" exit 1
fi


for (( i=0; i<$7; i++))

do
	e=$(( $i * $6 + $5 ))
	if (( $e < 10 ))
	then
		e="0.00"$e
	elif (( $e < 100 ))
	then
		e="0.0"$e
	else
		e="0."$e
	fi

	stat3_rw2.bash $1 $2 $3 $4 $e $8 $9 ${10} ${11} ${12} ${13} ${14}
done
