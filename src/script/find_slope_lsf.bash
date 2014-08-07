#! /bin/bash

# Script for finding slopes using least-square fit with different num_edges.

if (( $# != 2 ))
then
	echo "Usage: $0 <g> <output filename>"
	exit 1
else

	str1='lsf '$1
	str2=$2
	gawk -v st1="$str1" -v st2="$str2" '{system(st1" "$1" "st2)}' nedges

fi
