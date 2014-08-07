#! /bin/bash

# Script for multiple runs assuming snapshot files are already found.
# This is specifically for 1D ring shaped network. Basic structure is the ring and agents don't move while opinions can change.
# X-size will be the same as ngents, and Y-size will be one.

if (( $# != 4 )); then
	echo "Usage: $0 <nagents> <number_edges> <int_range> <# of runs>"
	echo "  number_edges: 0: no AG, different filenames, -1: file input (agraph.in)"
	exit 1
fi

if (( $4 > 10000 )); then
	echo "  Too big # of all runs (Max=10000)."
	exit 1
fi

pos1=`expr index $2 -`

if (( $pos1 == 1 )); then
   	num_edge=-1
   	evalue="File"
else
	pos2=`expr index  $2 123456789`
	if (( $pos2 != 0 )); then
		num_edge=`expr substr $2 $pos2 6`
	else
		num_edge=0
	fi
   	evalue=$2
fi
   
   mkdir temp1234
   cd temp1234

   echo "Finding the standard deviation for E="$2"."

   filename_sigma="summary_n"$1"_e"$evalue"_i"$3"_sigma"
   filename5="snapshot_n"$1"_e"$evalue"_i"$3
   tar zxf "../"$filename5".tgz"

   for ((i=1; i<=$4; i++))
   do
	if (( $i < 10 ))
	then
		filename_snap=$filename5"_000"$i
	elif (( $i < 100 ))
	then
		filename_snap=$filename5"_00"$i
	elif (( $i < 1000 ))
	then
		filename_snap=$filename5"_0"$i
	elif (( $i < 10000 ))
	then
		filename_snap=$filename5"_"$i
	else 
		filename_snap=$filename5"_0000"
	fi
	
	GetFinalValues $1 $filename_snap >> $filename_sigma
   done

   cp $filename_sigma ..
   cd ..
   rm -rf temp1234


   gawk -v nagent=$1 -v nbin=10 'BEGIN{for(i=0;i<nbin+10;i++) count[i]=0}{
   	count[int(($1+0.5/nbin)*nbin)]++;}END{for(i=0;i<nbin+5;i++) print i/nbin, count[i];}' $filename_sigma > $filename_sigma".dist"

   sort -n -k1,1 $filename_sigma > $filename_sigma".sorted"

   gawk -v numedge=$2 '{print numedge, NR-1, $1}' $filename_sigma".sorted" > $filename_sigma".sorted2"
