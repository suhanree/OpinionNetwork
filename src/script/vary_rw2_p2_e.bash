#! /bin/bash

# Script for multiple runs with different num_edges. (specially modified to analyze period-2 decays)
#	It will invoke 'multirun_rw2_p2.bash' (convergence_method=4, convergence_check_period=10)
if (( $# != 18 ))
then
	echo "Usage: $0 <nagents> <total_time> <X> <Y> <g> <op_thres> <shape> <topology> <time_interval> <initial_value> <interval> <number of num_edges values> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs> <convergence_method>"
	exit 1
else

for (( i=0; i<${12}; i++))

do
	e=$(( $i * ${11} + ${10} ))
	if (( $e < 10 ))
	then
		e="00000"$e
	elif (( $e < 100 ))
	then
		e="0000"$e
	elif (( $e < 1000 ))
	then
		e="000"$e
	elif (( $e < 10000 ))
	then
		e="00"$e
	elif (( $e < 100000 ))
	then
		e="0"$e
	fi
	multirun_rw2_p2.bash $1 $2 $3 $4 $5 $6 $7 $8 $9 $e ${13} 2 ${14} ${15} ${16} ${17} ${18}

done

mail -s `pwd` suhanree@gmail.com < '.'
fi
