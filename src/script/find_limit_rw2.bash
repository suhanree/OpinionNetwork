#! /bin/bash

# Script to find the upper and lower limits of the number of clusters for RW2.

if (( $# != 2 ))
then 
	echo "Usage: $0 <highest op_threshold * 1000> <output filename>"
	exit 1
fi

if [ -f $2 ]; then
	rm -f $2
fi

for ((i=1; i<=$1; i++))
do
	if (( $i < 10 ))
	then
		op="0.00"$i
	elif (( $i < 100 ))
	then
		op="0.0"$i
	else 
		op="0."$i
	fi
	filename="summary_n1000_e0_g0.5_op"$op"_ag0.1_t100000_opclusters"

	if [ -f $filename ]
	then
		gawk -v thres=$op \
   		'BEGIN{
			lower=1000;
			upper=0;
			cnt=0;
		}{
   			if ($1=="time") {
				if (cnt!=0) {
					if (cnt< lower)
						lower=cnt;
					if (cnt>upper)
						upper=cnt;
					number[cnt]++;
				};
				cnt=0;
			}
			else
				cnt++;
   		} END{
			if (cnt!=0) {
				if (cnt< lower)
					lower=cnt;
				if (cnt>upper)
					upper=cnt;
				number[cnt]++;
			};
			printf "%5.3f\t%d\t%d\t: ", thres, lower, upper
			for (i=1;i<1000;i++)
				if (number[i]!=0) printf "%d(%d), ", i, number[i];
			printf "%s", "\n"
   		}' $filename >> $2
	fi
done

