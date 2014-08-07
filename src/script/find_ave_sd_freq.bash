#! /bin/bash

# Script to find the average and the standard deviation from a set of points.
# Also find the frequency dist.

if (( $# != 2 ))
then 
	echo "Usage: $0 <input file with data points> <number of bins>"
	exit 1
fi

if (( $2 % 2 == 0 )); then
	echo "Check the number of bins. It should be odd."
	exit 1
fi

filename=$1
filename2=$filename".freq"
filename3=$filename".gaussian"

gawk -v file2=$filename2 -v file3=$filename3 -v nbin=$2 'BEGIN{cnt=0; sum1=0; sum2=0; nbin2=500;
		Pi=3.141592;
	} {
	value[cnt]=$1;
	cnt++;
	}\
	END{
	for (j=0;j<cnt;j++) {
		sum1+=value[j]; 
	};
	ave=sum1/cnt;
	for (j=0;j<cnt;j++) {
		sum2+=(ave-value[j])*(ave-value[j]); 
	};
	sum2=sum2/cnt;
	sd=sqrt(sum2);
	print ave, sd;

	min=ave-sd*5;max=ave+sd*5;
	range=max-min;
	for (i=0;i<nbin;i++) {
		bin[i]=0;
	};
	for (j=0;j<cnt;j++) {
		bin[int((value[j]-min)/range*nbin)]++;
	};
	for (i=0;i<nbin;i++) {
		print min+(range/nbin)*(i+0.5), bin[i]/(range/nbin)/cnt > file2;
	};
	for (i=0;i<nbin2;i++) {
		x=min+(range/nbin2)*(i+0.5);
		y=1/(sqrt(2*Pi)*sd)*exp(-(x-ave)*(x-ave)/(2*sd*sd));
		print x, y > file3;
	};




	}' $filename
