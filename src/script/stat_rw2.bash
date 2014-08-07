#! /bin/bash

# Script to calculate the average and standard deviation for num_edges, nclusters, and time for all runs.

if (( $# != 3 ))
then 
	echo "Usage: $0 <filename1> <filename2> <filename3>"
else
   gawk 'BEGIN{cnt=0} {value[cnt++]=$1;} END{if (cnt>0) {for (j=0;j<cnt;j++) ave+=value[j]; ave/=cnt;\
	for (k=0;k<cnt;k++) sum+=(value[k]-ave)*(value[k]-ave);\
	sd=sqrt(sum/cnt); print ave, sd;}}' $1 > temp4587a
   gawk 'BEGIN{cnt=0} {value[cnt++]=$1;} END{if (cnt>0) {for (j=0;j<cnt;j++) ave+=value[j]; ave/=cnt;\
	for (k=0;k<cnt;k++) sum+=(value[k]-ave)*(value[k]-ave);\
	sd=sqrt(sum/cnt); print ave, sd;}}' $2 >> temp4587a
   gawk 'BEGIN{cnt=0} {value[cnt++]=$1;} END{if (cnt>0) {for (j=0;j<cnt;j++) ave+=value[j]; ave/=cnt;\
	for (k=0;k<cnt;k++) sum+=(value[k]-ave)*(value[k]-ave);\
	sd=sqrt(sum/cnt); print ave, sd;}}' $3 >> temp4587a
   gawk 'BEGIN{cnt=0;} {value[cnt]=$1; sd[cnt]=$2; cnt++;} END{if (cnt>0) {print \
   	value[0], value[1], value[2], sd[0], sd[1], sd[2];}}' temp4587a
   rm -f temp4587a
fi
