#! /bin/bash

# Script to count the numbers of different outcomes based on simulation runs.
# This is especially for the network stats (clustering coeff, and mean distance)
# Unlike previous scripts (stat2, stat3), this also has an option for running 
# 	simulations
# Simulations only calculate network stats for a specific time, so that value
#	has to be given, too.

if (( $# != 15 ))
then 
	echo "Usage: $0 <nagents> <X> <Y> <g> <op_thres> <shape> <topology> <num_edges> <ag_threshold> <neighbor_type> <movement_type> <simulation> <network_time> <update_method> <# of runs>"
	echo "  simulation: -1 (no simulations, using previous tgz summary files), 1 (simulations will be run)."
	exit 1
fi

pos=`expr index  $8 123456789`
if (( $pos != 0 )); then
	num_edge=`expr substr $8 $pos 8`
else
	num_edge=0
fi
if (( $num_edge < 0 )); then
	evalue="File"
else
	evalue=$8
fi

if (( ${12} > 0 )); then
	multirun_rw2_netstat.bash $1 ${13} $2 $3 $4 $5 $6 $7 0 $evalue $9 0 ${10} ${11} ${14} ${15}
fi

filename="netstat_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_e"$evalue"_ag"$9"_ne"${10}"_mo"${11}
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

if [ -f ../$filename1".tgz" ]; then
	tar zxf ../$filename1".tgz"
else
	echo "File, "$filename1".tgz doesn't exist."
	cd ..
	rm -rf $temp_dir
	exit 1
fi

if [ -f ../$filename1"_cm" ]; then
	rm -f ../$filename1"_cm"
fi

for ((j=1; j<=${15}; j++))
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
	else 
		filename_s=$filename1"_"$j
	fi

	gawk '{
		if ($1=="clustering_coeff") {
			cc=$2;
		};
		if ($1=="mean_distance") {
			md=$2;
		};
		}END{print cc, md;}' $filename_s >> ../$filename1"_cm"
done

gawk -v nagents=$1 -v xsize=$2 -v ysize=$3 -v g=$4 -v thres=$5 -v nedge=$num_edge 'BEGIN{
	cnt=0; 
	ave1=0; sum1=0; sd1u=0; sd1d=0; min1=0; max1=0;
	ave2=0; sum2=0; sd2u=0; sd2d=0; min2=0; max2=0;
	} {
		if ($1>0 && $2>0) {
			value1[cnt]=$1;
			value2[cnt]=$2;
			cnt++;
		};
	} END{
		for (j=0;j<cnt;j++) {
			ave1+=value1[j]; 
			ave2+=value2[j]; 
		};
		if (cnt>0) {
			ave1/=cnt;
			min1=ave1; max1=ave1;
			ave2/=cnt;
			min2=ave2; max2=ave2;
		};
		cnt1u=0;cnt1d=0;
		cnt2u=0;cnt2d=0;
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

			if (value2[j]>=ave2) {
				sum2u+=(value2[j]-ave2)*(value2[j]-ave2);
				cnt2u++;
			}
			else {
				sum2d+=(value2[j]-ave2)*(value2[j]-ave2);
				cnt2d++;
			};
			if (value2[j]>max2) max2=value2[j];
			if (value2[j]<min2) min2=value2[j];
		};
		if (cnt1u>0) sd1u=sqrt(sum1u/cnt1u);
		if (cnt1d>0) sd1d=sqrt(sum1d/cnt1d);
		if (cnt2u>0) sd2u=sqrt(sum2u/cnt2u);
		if (cnt2d>0) sd2d=sqrt(sum2d/cnt2d);
		print nagents, xsize, ysize, g, thres, nedge, ave1, sd1u, sd1d, max1, min1, ave2, sd2u, sd2d, max2, min2, cnt;}' ../$filename1"_cm" >> ../$filename
cd ..
rm -rf $temp_dir
