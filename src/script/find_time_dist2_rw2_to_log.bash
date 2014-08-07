#! /bin/bash

# Script for finding slopes using least-square fit with different num_edges.

if (( $# != 3 ))
then
	echo "Usage: $0 <g> <ymax> <ymin>"
	exit 1
else

	str1='gawk -v ymax='$2' -v ymin='$3" '{if ("'$4'"<=ymax && "'$4'">=ymin) print "'$1'", "'$4'"}' tdist_g"$1"_e"
	str2='.dist > tdist_g'$1'_e'
	str3='_log'
	gawk -v st1="$str1" -v st2="$str2" -v st3="$str3" '{system(st1""$1""st2""$1""st3)}' nedges

fi
