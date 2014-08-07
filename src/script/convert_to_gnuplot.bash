#! /bin/bash

# Script for converting the data for gnuplot 3d plot.

if (( $# != 3 ))
then
	echo "Usage: $0 <nagents> <int_range> <# of runs>"
	exit 1
else

	filename1="summary_n"$1"_e"
	filename2="_i"$2"_sigma.sorted"
	gawk -v n=$3 -v st1="$filename1" -v st2="$filename2" '{
		filename=st1""$1""st2;
		for (i=0;i<n;i++) {
			getline d < filename;
			print NR-1, i, d;
			print NR, i, d;
			print "";
			print NR-1, i+1, d;
			print NR, i+1, d;
			print "";
		};
		print "";
	}' nedges

fi
