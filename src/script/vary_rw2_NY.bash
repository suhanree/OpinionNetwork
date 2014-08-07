#! /bin/bash

# Script for multiple runs with different nagents & ysize (they are proportional)

if (( $# != 17 ))
then
	echo "Usage: $0 <density> <total_time> <X> <initial_value> <interval> <number of Y values> <g> <op_thres> <shape> <topology> <time_interval> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs>"
	echo "	nagetns will be (density*X*Y)."
else

for (( i=0; i<$6; i++))

do
	e=$(( $i * $5 + $4 ))
	n=$(( $1 * $3 * $e ))
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
	multirun_rw2.bash $n $2 $3 $e $7 $8 $9 ${10} ${11} ${12} ${13} 2 ${14} ${15} ${16} ${17}

done
mail -s `pwd` suhanree@gmail.com < '.'

fi

