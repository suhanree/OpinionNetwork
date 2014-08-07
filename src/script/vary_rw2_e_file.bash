#! /bin/bash

# Script for multiple runs with different num_edges.

if (( $# != 14 ))
then
	echo "Usage: $0 <nagents> <total_time> <X> <Y> <g> <op_thres> <shape> <topology> <time_interval> <ag_threshold> <neighbor_type> <movement_type> <update_method> <# of runs>"
	exit 1
else

	str1='nohup nice multirun_rw2.bash '$1' '$2' '$3' '$4' '$5' '$6' '$7' '$8' '$9
	str2=${10}' 2 '${11}' '${12}' '${13}' '${14}
	gawk -v st1="$str1" -v st2="$str2" '{system(st1" "$1" "st2)}' nedges

mail -s `pwd` suhanree@gmail.com < '.'
fi
