#! /bin/bash

# Script to find the distributions of convergence time.
# Input file format: TIME

if (( $# != 4 ))
then
	echo "Usage: $0 <initial t> <interval t> <# of bins> <input file>"
	exit 1
fi

if [ -f $4 ]; then
	echo "" > /dev/null
else
	echo "Input file, $4, doesn't exist."
	exit 1
fi

gawk -v t0=$1 -v width=$2 -v nbin=$3 'BEGIN{
	for (i=0;i<nbin;i++) 
		cnt[i]=0;
	total=0;}{
	conv_time=($1==20000 ? $1 : $1-100);
 	ibin=int($1/width);
	if (ibin<nbin) {
		cnt[ibin]++;
		total++;
	};
	}END{
	for (i=0;i<nbin;i++) 
   		print (i+0.5)*width, cnt[i], cnt[i]/total/width*500;
   	}' $4
