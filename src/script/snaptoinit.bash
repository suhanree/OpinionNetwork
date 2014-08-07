#! /bin/bash

if (( $# != 2 )); then
	echo "Usage: $0 <filename> <time>"
	exit 1
fi

filename1=$1
filename2="agents.in"

gawk -v time=$2 '{if ($1==time) print $2, $3, $4, $5, $6;}' $filename1 > $filename2
