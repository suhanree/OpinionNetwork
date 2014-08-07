#! /bin/bash

# Script to count the simulation results for 100 runs each.
# If the simulation runs are less than 100, this script shouldn't be used.

if (( $# != 8 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <g> <op_thres> <shape> <topology> <# of runs/100>"
	exit 1
fi

filename1="summary_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_n"
filename2="stat_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_100"
nruns=`wc $filename1 | gawk '{print $1}'`
nruns2=$(( $8 * 100 ))
if (( $nruns != $nruns2 ))
then 
	echo "Check if <# of runs> is 100 times $8."
	exit 1
fi



gawk -v nagents=$1 -v xsize=$2 -v ysize=$3 -v g=$4 -v thres=$5 'BEGIN{
	cnt=0;cnt2=0;
	for (i=-5;i<8;i++) {
		period[i]=0;
		ngroups[i+1]=0;
	};
	ave0=0;
	ave1=0;
	ave5=0;
	ave10=0;
	nline=0;
	} {
	nline++;
	if (NF==4) {
		value0[cnt]=$1;
		value1[cnt]=$2;
		value5[cnt]=$3;
		value10[cnt]=$4;
		cnt++;
	};
	if (NF==6) {
		if ($2>-0.5 || $4 >-0.5) {
			slope=($2>$4 ? $2 : $4);
			if (slope<7)
				period[slope]++;
			else
				period[7]++;
		}
		else {
			slope=$6;
			if (slope<-0.5) {
				period[-1]++;
			}
			else if (slope<5)
				period[-slope]++;
			else
				period[-5]++;
		};
		cnt2++;
	};

	if (nline%100==0) {
		for (j=0;j<cnt;j++) {
			ave0+=value0[j]; 
			ave1+=value1[j]; 
			ave5+=value5[j]; 
			ave10+=value10[j]; 
			if (value10[j]<8)
				ngroups[value10[j]]++;
			else
				ngroups[8]++;
		};
		if (cnt>0) {
			ave0/=cnt;
			ave1/=cnt;
			ave5/=cnt;
			ave10/=cnt;
		};
		print nagents, xsize, ysize, g, thres, ave0, ave1, ave5, ave10, ngroups[1],ngroups[2],ngroups[3],ngroups[4],ngroups[5],ngroups[6],ngroups[7],ngroups[8], period[0]+cnt, period[1], period[2], period[3], period[4], period[5], period[6], period[7], period[-5], period[-4], period[-3], period[-2], period[-1], cnt, cnt2;

		cnt=0;cnt2=0;
		for (i=-5;i<8;i++) {
			period[i]=0;
			ngroups[i+1]=0;
		};
		ave0=0;
		ave1=0;
		ave5=0;
		ave10=0;
	};}' $filename1 > $filename2
