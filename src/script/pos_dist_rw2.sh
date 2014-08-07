#! /bin/bash

# To see the spatial properties of opinions.

if (( $# != 5 )); then
	echo "Usage: $0 <init time> <interval> <# of times> <input filename> <output info>"
	exit 1
fi

for (( i=0; i<$3; i++ ))
do
	t=$(( $1 + $2 * $i ))
	for (( j=0; j<10 ;j++))
	do
		file=$5"_t"$t"."$j
		echo "-2 -2" > $file
	done
done

gawk -v out=$5 'BEGIN{time=-1;} {
	if (time!=$1) time=$1;
	if ($5<0.1) print $3, $4 >> out"_t"time".0";
	else if ($5<0.2) print $3, $4 >> out"_t"time".1";
	else if ($5<0.3) print $3, $4 >> out"_t"time".2";
	else if ($5<0.4) print $3, $4 >> out"_t"time".3";
	else if ($5<0.5) print $3, $4 >> out"_t"time".4";
	else if ($5<0.6) print $3, $4 >> out"_t"time".5";
	else if ($5<0.7) print $3, $4 >> out"_t"time".6";
	else if ($5<0.8) print $3, $4 >> out"_t"time".7";
	else if ($5<0.9) print $3, $4 >> out"_t"time".8";
	else print $3, $4 >> out"_t"time".9";
}' $4  

for (( i=0; i<$3; i++ ))
do
	t=$(( $1 + $2 * $i ))
	if (( t<10 )); then
		time="000"$t
	elif (( t<100 )); then
		time="00"$t
	elif (( t<1000 )); then
		time="0"$t
	else
		time=$t
	fi

	echo "set title \"$5 (t=$t)\"" > .gnuplot
	echo "set xrange [-1:51]" >> .gnuplot
	echo "set yrange [-1:51]" >> .gnuplot
	echo "set term gif" >> .gnuplot
	echo "set output \"$5_t$time.gif\"" >> .gnuplot
	echo "plot \\" >> .gnuplot

	for (( j=0; j<9 ;j++))
	do
		echo "   \"$5_t$t.$j\" with points,\\" >> .gnuplot
	done
	echo "   \"$5_t$t.$j\" with points" >> .gnuplot

	gnuplot < .gnuplot
	
	rm .gnuplot
	for (( j=0; j<10 ;j++))
	do
		rm $5"_t"$t"."$j
	done
done

for (( j=0; j<9 ;j++))
do
	rm $5"_t1*."$j 2> /dev/null
	rm $5"_t2*."$j 2> /dev/null
	rm $5"_t3*."$j 2> /dev/null
	rm $5"_t4*."$j 2> /dev/null
	rm $5"_t5*."$j 2> /dev/null
	rm $5"_t6*."$j 2> /dev/null
	rm $5"_t7*."$j 2> /dev/null
	rm $5"_t8*."$j 2> /dev/null
	rm $5"_t9*."$j 2> /dev/null
done

