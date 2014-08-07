#! /bin/bash

# Script to calculate the average and standard deviation.

if (( $# != 1 ))
then 
	echo "Usage: $0 <filename>"
else
   gawk 'BEGIN{cnt=0} {
   	if ($1!="Not" ) {
		value0[cnt]=$1;
		value10[cnt]=$2;
		value20[cnt]=$3;
		value50[cnt]=$4;
		value100[cnt]=$5;
		cnt++;
	};
   } \
   END {
   	if (cnt!=0) {
		for (j=0;j<cnt;j++) {
			ave0+=value0[j];
			ave10+=value10[j];
			ave20+=value20[j];
			ave50+=value50[j];
			ave100+=value100[j];
		};
		ave0/=cnt;
		ave10/=cnt;
		ave20/=cnt;
		ave50/=cnt;
		ave100/=cnt;
		for (k=0;k<cnt;k++) {
			sum0+=(value0[k]-ave0)*(value0[k]-ave0);
			sum10+=(value10[k]-ave10)*(value10[k]-ave10);
			sum20+=(value20[k]-ave20)*(value20[k]-ave20);
			sum50+=(value50[k]-ave50)*(value50[k]-ave50);
			sum100+=(value100[k]-ave100)*(value100[k]-ave100);
		};
		sd0=sqrt(sum0/cnt); 
		sd10=sqrt(sum10/cnt); 
		sd20=sqrt(sum20/cnt); 
		sd50=sqrt(sum50/cnt); 
		sd100=sqrt(sum100/cnt); 
		print ave0, ave10, ave20, ave50, ave100, sd0, sd10, sd20, sd50, sd100;
	};
   }' $1
fi
