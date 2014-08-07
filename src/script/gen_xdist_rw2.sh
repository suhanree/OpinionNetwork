#! /bin/bash

if (( $# != 5 ))
then
	echo "Usage: $0 <initial t> <t interval> <# of t> <xsize> <input file info>"
else

echo "set term gif" > .gnuplot
echo "set xrange [0:$4]" >> .gnuplot
echo "set yrange [0:1]" >> .gnuplot
echo "set nokey" >> .gnuplot

for (( i=0; i<$3; i++ ))
do
	t=$(( $i * $2 + $1 ))
	if (( t < 10 )); then
		t1="00000"$t
	elif (( t < 100 )); then
		t1="0000"$t
	elif (( t < 1000 )); then
		t1="000"$t
	elif (( t < 10000 )); then
		t1="00"$t
	elif (( t < 100000 )); then
		t1="0"$t
	else
		t1=$t
	fi
	filename=$5"_t"$t1
		
	echo "set title \"$5 at t=$t\"" >> .gnuplot
	echo "set output \"$filename.gif\"" >> .gnuplot
	echo "plot \"$filename\" with points" >> .gnuplot
done

gnuplot < .gnuplot

fi
