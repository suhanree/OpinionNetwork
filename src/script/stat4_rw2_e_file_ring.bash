#! /bin/bash

if (( $# != 3 ))
then 
	echo "Usage: $0 <nagents> <int_range> <# of runs>"
	exit 1
else
	str1='stat4_rw2_ring.bash '$1
	str2=$2' '$3
	awk -v st1="$str1" -v st2="$str2" '{system(st1" "$1" "st2)}' nedges

mail -s `pwd` suhanree@gmail.com < '.'
fi
