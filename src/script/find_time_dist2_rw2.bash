#! /bin/bash

# Script to find the cumulative distributions of convergence time, P(>t).
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
	for (i=0;i<=nbin;i++) 
		cnt[i]=0;
		cumu[i]=0;
	total=0;}{
 	ibin=int($1/width);
	if (ibin<nbin) {
		cnt[ibin]++;
	}
	else {
		cnt[nbin]++;
	};
	}END{
	for (i=0;i<=nbin;i++) {
		for (j=i;j<=nbin;j++) cumu[i]+=cnt[j];
   		print i*width, cumu[i], cumu[i]/cumu[0], log(cumu[i]/cumu[0])/log(10);
	};
   	}' $4
