#! /bin/bash

# Script to count the numbers of different outcomes based on simulation runs.

if (( $# != 12 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <g> <op_thres> <shape> <topology> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <# of runs>"
	exit 1
fi

if (( ${12} > 10000 ));then
	echo "<# of runs> cannot be greater than 10000."
	exit 1
fi

pos=`expr index  $8 123456789`
if (( $pos != 0 )); then
	num_edge=`expr substr $8 $pos 6`
else
	num_edge=0
fi
if (( $num_edge < 0 )); then
	evalue="File"
else
	evalue=$8
fi
filename="stat_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_e"$evalue"_ag"$9"_ne"${10}"_mo"${11}
if (( $num_edge != 0 )); then
	filename1="summary_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_e"$evalue"_ag"$9"_ne"${10}"_mo"${11}
else
	filename1="summary_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_ne"${10}"_mo"${11}
fi

if [ -f $filename ]; then
	rm -f $filename
fi
temp_dir="temp6789"
mkdir $temp_dir
cd $temp_dir

tar zxf ../$filename1".tgz"


if [ -f ../$filename1"_n" ]; then
	rm -f ../$filename1"_n"
fi

for ((j=1; j<=${12}; j++))
do
	if (( $j < 10 ))
	then
		filename_s=$filename1"_000"$j
	elif (( $j < 100 ))
	then
		filename_s=$filename1"_00"$j
	elif (( $j < 1000 ))
	then
		filename_s=$filename1"_0"$j
	elif (( $j < 10000 ))
	then
		filename_s=$filename1"_"$j
	else 
		filename_s=$filename1"_0000"
	fi

	gawk -v n=$1 -v topology=$7 'BEGIN{ng0=0;ng1=0;ng5=0;ng10=0;cutoff=n/100;zero=0;diff_x=0;diff_y=0;num_x=0;num_y=0;diff_p=0;num_p=0;}{\
		if ($1=="converged" && $2==0)  zero=1; 
		if (!zero && $1=="opinions") {
			ng0++;
			if ($3>=cutoff) ng1++;
			if ($3>=cutoff*5) ng5++;
			if ($3>=cutoff*10) ng10++;
		};
		if (zero && $1=="av_diff") {
			diff_x=$2;
			num_x=$3;
		};
		if (zero && $1=="av_diff_x") {
			diff_x=$2;
			num_x=$3;
		};
		if (zero && $1=="av_diff_y") {
			diff_y=$2;
			num_y=$3;
		};
		if (zero && $1=="av_diff_p") {
			diff_p=$2;
			num_p=$3;
		};
		}END{if (!zero || topology==1) print ng0, ng1, ng5, ng10; else print diff_x, num_x, diff_y, num_y, diff_p, num_p;}' $filename_s >> ../$filename1"_n"
done

gawk -v nagents=$1 -v xsize=$2 -v ysize=$3 -v g=$4 -v thres=$5 -v nedge=$num_edge 'BEGIN{cnt=0;cnt2=0;
	for (i=-5;i<8;i++) {
		period[i]=0;
		ngroups[i+1]=0;
	};
	ave0=0; sum0=0; sd0u=0; sd0d=0; min0=0; max0=0;
	ave1=0; sum1=0; sd1u=0; sd1d=0; min1=0; max1=0;
	ave5=0; sum5=0; sd5u=0; sd5d=0; min5=0; max5=0;
	ave10=0; sum10=0; sd10u=0; sd10d=0; min10=0; max10=0;
	} {
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
	}\
	END{
	for (j=0;j<cnt;j++) {
		ave0+=value0[j]; 
		ave1+=value1[j]; 
		ave5+=value5[j]; 
		ave10+=value10[j]; 
	};
	if (cnt>0) {
		ave0/=cnt;
		ave1/=cnt;
		ave5/=cnt;
		ave10/=cnt;
		min0=ave0; max0=ave0;
		min1=ave1; max1=ave1;
		min5=ave5; max5=ave5;
		min10=ave10; max10=ave10;
	};
	cnt0u=0;cnt0d=0;
	for (j=0;j<cnt;j++) {
		if (value0[j]>=ave0) {
			sum0u+=(value0[j]-ave0)*(value0[j]-ave0);
			cnt0u++;
		}
		else {
			sum0d+=(value0[j]-ave0)*(value0[j]-ave0);
			cnt0d++;
		};
		if (value0[j]>max0) max0=value0[j];
		if (value0[j]<min0) min0=value0[j];
	};
	cnt1u=0;cnt1d=0;
	for (j=0;j<cnt;j++) {
		if (value1[j]>=ave1) {
			sum1u+=(value1[j]-ave1)*(value1[j]-ave1);
			cnt1u++;
		}
		else {
			sum1d+=(value1[j]-ave1)*(value1[j]-ave1);
			cnt1d++;
		};
		if (value1[j]>max1) max1=value1[j];
		if (value1[j]<min1) min1=value1[j];
	};
	cnt5u=0;cnt5d=0;
	for (j=0;j<cnt;j++) {
		if (value5[j]>=ave5) {
			sum5u+=(value5[j]-ave5)*(value5[j]-ave5);
			cnt5u++;
		}
		else {
			sum5d+=(value5[j]-ave5)*(value5[j]-ave5);
			cnt5d++;
		};
		if (value5[j]>max5) max5=value5[j];
		if (value5[j]<min5) min5=value5[j];
	};
	cnt10u=0;cnt10d=0;
	for (j=0;j<cnt;j++) {
		if (value10[j]>=ave10) {
			sum10u+=(value10[j]-ave10)*(value10[j]-ave10);
			cnt10u++;
		}
		else {
			sum10d+=(value10[j]-ave10)*(value10[j]-ave10);
			cnt10d++;
		};
		if (value10[j]>max10) max10=value10[j];
		if (value10[j]<min10) min10=value10[j];
	};
	for (j=0;j<cnt;j++) {
		if (value10[j]<8)
			ngroups[value10[j]]++;
		else
			ngroups[8]++;
	};
	if (cnt0u>0) sd0u=sqrt(sum0u/cnt0u);
	if (cnt0d>0) sd0d=sqrt(sum0d/cnt0d);
	if (cnt1u>0) sd1u=sqrt(sum1u/cnt1u);
	if (cnt1d>0) sd1d=sqrt(sum1d/cnt1d);
	if (cnt5u>0) sd5u=sqrt(sum5u/cnt5u);
	if (cnt5d>0) sd5d=sqrt(sum5d/cnt5d);
	if (cnt10u>0) sd10u=sqrt(sum10u/cnt10u);
	if (cnt10d>0) sd10d=sqrt(sum10d/cnt10d);
	print nagents, xsize, ysize, g, thres, nedge, ave0, ave1, ave5, ave10, ngroups[1],ngroups[2],ngroups[3],ngroups[4],ngroups[5],ngroups[6],ngroups[7],ngroups[8], period[0]+cnt, period[1], period[2], period[3], period[4], period[5], period[6], period[7], period[-5], period[-4], period[-3], period[-2], period[-1], cnt, cnt2;}' ../$filename1"_n" >> ../$filename
cd ..
rm -rf $temp_dir
