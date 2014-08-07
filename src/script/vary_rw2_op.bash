#! /bin/bash

# Script for multiple runs with different op_threshold.

if (( $# != 17 ))
then
	echo "Usage: $0 <nagents> <total_time> <X> <Y> <g> <initial_value*1000> <interval*1000> <number of op_thres values> <shape> <topology> <time_interval> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs>"
	exit 1
else

for (( i=0; i<$8; i++))

do
	e=$(( $i * $7 + $6 ))
	if (( $e < 10 ))
	then
		e="0.00"$e
	elif (( $e < 100 ))
	then
		e="0.0"$e
	else
		e="0."$e
	fi
	multirun_rw2.bash $1 $2 $3 $4 $5 $e $9 ${10} ${11} ${12} ${13} 2 ${14} ${15} ${16} ${17}

done

mail -s `pwd` suhanree@gmail.com < '.'
fi
