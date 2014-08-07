#! /bin/bash

# Script for finding distributions of the metastable states at a given time.

if (( $# != 4 ))
then
	echo "Usage: $0 <input filename> <# of runs> <given time> <delta(0<delta<0.5)>"
	exit 1
else

   out_filename=$1"_t"$3"p"
   for ((i=1; i<=$2; i++))
   do
	if (( $i < 10 ))
	then
		filename=$1"_000"$i"p"
	elif (( $i < 100 ))
	then
		filename=$1"_00"$i"p"
	elif (( $i < 1000 ))
	then
		filename=$1"_0"$i"p"
	elif (( $i < 10000 ))
	then
		filename=$1"_"$i"p"
	else 
		filename=$1"_0000p"
	fi

	if (( $i == 1 ))
	then
   		gawk -v time=$3 'BEGIN{period=-1;}{if ($1==time) {p=$2; period=$3;}; last=$3;}\
			END{if (period<0) {print last, 1;} else {print period, 0, p};}' $filename > $out_filename
	else
   		gawk -v time=$3 'BEGIN{period=-1;}{if ($1==time) {p=$2; period=$3;}; last=$3;}\
			END{if (period<0) {print last, 1;} else {print period, 0, p};}' $filename >> $out_filename
	fi
   done
   gawk -v delta=$4 'BEGIN{for (i=0;i<8;i++) p[i]=0;ntransition=0;}{pdiff=-1; if ($2==0) pdiff=$3+delta-int($3+delta); if ($1>1000|| pdiff>delta*2) {ntransition++} else {p[$1]++;}}END{for (i=0;i<8;i++) print i, p[i]; print "tran", ntransition;}' $out_filename
fi
