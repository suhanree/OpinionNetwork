#! /bin/bash

# Script for multiple runs with different nagents and num_edges. (for the special case of 1d ring).
# Need two files: "nagents" (format: nagents, int_range min_nedges, max_nedges), "nedges" (format: nedges, time_interval)

if (( $# != 3 ))
then
	echo "Usage: $0 <totaltime> <update_method> <# of runs>"
	exit 1
else

	str1='nohup nice vary_rw2_e_file_ring2.bash'
	str2=$1
	str3=$2
	str4=$3
	gawk -v st1="$str1" -v st2="$str2" -v st3="$str3" -v st4="$str4" '{min=$1*$3; max=$1*$4; system(st1" "$1" "st2" "$2" 0 0 "st3" 100 "st4" "min" "max)}' nagents

mail -s `pwd` suhanree@gmail.com < '.'
fi
