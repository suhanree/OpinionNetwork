#! /bin/bash

# Script for multiple runs with different num_edges.

if (( $# != 2 ))
then
	echo "Usage: $0 <g> <E>"
	exit 1
else
	gawk -v E=$2 '{if ($1==1) cnt++}END{print E/499500, cnt/1000}' "summary_n1000_x100_y10_g"$1"_o0.5_s22_e"$2"_ag1_ne3_mo2_ngroups" >> "g"$1".ngroups"
fi
