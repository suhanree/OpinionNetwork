#! /bin/bash

# Script for multiple runs with different gullibility.

if (( $# != 18 ))
then
	echo "Usage: $0 <nagents> <total_time> <X> <Y> <initial_value*10000> <interval*10000> <number of g values> <op_thres> <shape> <topology> <time_interval> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs> <convergence_method>"
else

for (( i=0; i<$7; i++))
do
	g=$(( $i * $6 + $5 ))
	if (( $g < 10 ))
	then
		g="0.000"$g
	elif (( $g < 100 ))
	then
		g="0.00"$g
	elif (( $g < 1000 ))
	then
		g="0.0"$g
	elif (( $g < 10000 ))
	then
		g="0."$g
	else
		g="1"
	fi
	multirun_rw2_p2.bash $1 $2 $3 $4 $g $8 $9 ${10} ${11} ${12} ${13} 2 ${14} ${15} ${16} ${17} ${18}
done
mail -s `pwd` suhanree@gmail.com < '.'

fi
