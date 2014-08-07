#! /bin/bash

# Script to find the correlation of opinions for x or y.

if (( $# != 5 ))
then
	echo "Usage: find_correlation.bash <1 for x & 0 for y> <xsize or ysize> <time> <input file> <output file>"
	exit 1
fi

if (( $1>1 || $1<0 )); then
	echo "The first parameter, $1, should be 1 (for x) or 0 (for y)."
	exit 1
fi

if (( $2==0 )); then
	echo "The second parameter, $2, should not be 0."
	exit 1
fi

if [ -f $4 ]; then
	echo "" > /dev/null
else
	echo "Input file, $4, doesn't exist."
	exit 1
fi

gawk -v time=$3 -v size=$2 -v x=$1 -v file=$5 'BEGIN{
	for (i=0; i<size; i++) {
		value[i]=0;
		number[i]=0;
		ave[i]=0;
		cor[i]=0;
	};
   } {
   	if ($1==time) {
		value[(x?$3:$4)]+=$5;
		number[(x?$3:$4)]++;
   	};
   } END{
   	none=1;
   	for (j=0; j<size; j++)
		if (number[j]!=0) {
			none=0;
			break;
		};
	if (none==1) exit(1);
	else {
   		for (j=0; j<size; j++) {
			if (number[j]!=0)
				ave[j]=value[j]/number[j];
			else
				ave[j]=-1;
			print j, ave[j] > file;
		};
		print "======" > file;
		half=int(size/2);
		sum=0;
		for (i=1; i<=half; i++) {
			cor[i]=0;
			for (k=0;k<size;k++) {
				l=k+i;
				if (l>=size) l-=size;
				cor[i]+=(ave[l]-ave[k]>0 ? ave[l]-ave[k] : ave[k]-ave[l]);
			};
			cor[i]/=size;
			sum+=cor[i];
			print i, cor[i] > file;
		};
		print "cor", sum/half > file;
	};
}' $4 > /dev/null
