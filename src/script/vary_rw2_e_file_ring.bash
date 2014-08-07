#! /bin/bash

# Script for multiple runs with different num_edges. (for the special case of 1d ring).

if (( $# != 8 ))
then
	echo "Usage: $0 <nagents> <totaltime> <int_range> <init_method> <network> <update_method> <convergence_check_period> <# of runs>"
	exit 1
else

	str1='nohup nice multirun_rw2_ring.bash '$1' '$2
	str2=$3' '$4' '$5' '$6' '$7' '$8
	gawk -v st1="$str1" -v st2="$str2" '{system(st1" "$2" "$1" "st2)}' nedges

mail -s `pwd` suhanree@gmail.com < '.'
fi
