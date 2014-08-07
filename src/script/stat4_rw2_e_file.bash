#! /bin/bash

if (( $# != 14 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <g> <op_threshold> <shape> <topology> <ag_threshold> <neighbor_type> <movement_type> <simulation> <total_time> <update_method> <# of runs>"
	exit 1
else
	str1='nohup nice stat4_rw2.bash '$1' '$2' '$3' '$4' '$5' '$6' '$7
	str2=$8' '$9' '${10}' '${11}' '${12}' '${13}' '${14}
	gawk -v st1="$str1" -v st2="$str2" '{system(st1" "$1" "st2)}' nedges

mail -s `pwd` suhanree@gmail.com < '.'
fi
