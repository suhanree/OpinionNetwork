#! /bin/bash

# Script to find the cumulative distributions of convergence time, P(>t) for various E values.
# Input file format: TIME

if (( $# != 19 ))
then
	echo "Usage: $0 <nagents> <X> <Y> <g> <op_thres> <shape> <topology> <initial_value> <interval> <number of num_edges values> <ag_threshold> <neighbor_type> <movement_type> <initial t> <interval t> <# if bins> <xradius> <yradius> <ycutoff>"
	exit 1
else
	for (( i=0; i<${10}; i++))
	do
		e=$(( $i * $9 + $8 ))
		if (( $e < 10 ))
		then
			e="00000"$e
		elif (( $e < 100 ))
		then
			e="0000"$e
		elif (( $e < 1000 ))
		then
			e="000"$e
		elif (( $e < 10000 ))
		then
			e="00"$e
		elif (( $e < 100000 ))
		then
			e="0"$e
		fi
   		filename="summary_n"$1"_x"$2"_y"$3"_g"$4"_o"$5"_s"$6$7"_e"$e"_ag"${11}"_ne"${12}"_mo"${13}"_time"
   		filename2="tdist_g"$4"_e"$e
   		filename3="tdist_g"$4"_e"$e"_log"
		find_time_dist2_rw2.bash ${14} ${15} ${16} $filename >  $filename2
		if (( ${17} < 1 ));then
			gawk '{if ($4>=-2 && $4!="-inf")  print $1/1000, $4}' $filename2 > $filename3
		else
			gawk -v xrad=${17} -v yrad=${18} -v ycutoff=${19} '{if (yrad>0 && $4>=ycutoff && $4!="-inf" && $4*$4/yrad/yrad+$1*$1/xrad/xrad>1)  print $1, $4}' $filename2 > $filename3
		fi
		if (( $i == 0 )); then
			temp_str="'"$filename3"' using 1:2 with linespoints"
		else
			temp_str=$temp_str", '"$filename3"' using 1:2 with linespoints"
		fi
	done

	xi=$(( ${14} / 1000 ))
	xf=$(( ${14} + ${15} * ${16} ))
	echo "set term gif" > ".gnuplot"
	echo "set output 't.gif'" >> ".gnuplot"
	echo "set xrange [$xi:$xf]" >> ".gnuplot"
	echo "set yrange [-3:0]" >> ".gnuplot"
	echo "plot "$temp_str >> ".gnuplot"
	echo "quit" >> ".gnuplot"
	gnuplot < ".gnuplot"
fi
