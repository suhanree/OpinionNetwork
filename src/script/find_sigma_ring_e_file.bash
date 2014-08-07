#! /bin/bash

# Script for multiple runs with different num_edges. (for the special case of 1d ring).

if (( $# != 3 ))
then
	echo "Usage: $0 <nagents> <int_range> <# of runs>"
	exit 1
else

	str1='find_sigma_ring.bash '$1
	str2=$2' '$3
	gawk -v st1="$str1" -v st2="$str2" '{system(st1" "$1" "st2)}' nedges

fi
