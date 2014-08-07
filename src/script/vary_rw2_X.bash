#! /bin/bash

# Script for multiple runs with different xsize

if (( $# != 17 ))
then
	echo "Usage: $0 <nagents> <total_time> <initial_value> <interval> <number of X values> <Y> <g> <op_thres> <shape> <topology> <time_interval> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs>"
else

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
	then
		e="0"$e
	fi
	multirun_rw2.bash $1 $2 $e $6 $7 $8 $9 ${10} ${11} ${12} ${13} 2 ${14} ${15} ${16} ${17}
done
mail -s `pwd` suhanree@gmail.com < '.'

fi

