#! /bin/bash

# Script for multiple runs with different num_edges. (for the special case of 1d ring).

if (( $# != 10 ))
then
	echo "Usage: $0 <nagents> <totaltime> <int_range> <init_method> <network> <update_method> <convergence_check_period> <# of runs> <min_nedges> <max_nedges>"
	exit 1
else

	if (( $3 < 0 ))
	then
		int_range=0
	else
		int_range=$3
	fi

	str1='nohup nice multirun_rw2_ring.bash '$1' '$2
	str2=$3' '$4' '$5' '$6' '$7' '$8
	filename_str1='summary_n'$1
	filename_str2='_i'$int_range'_converged_bc'
	gawk -v st1="$str1" -v st2="$str2" -v min=$9 -v max=${10} -v fst1="$filename_str1" -v fst2="$filename_str2" 'BEGIN{conv=0}{
		filename=fst1"_e"$1""fst2;
		if ($1>=min && $1<=max && conv<=0.5) { 
			system(st1" "$2" "$1" "st2); 
		};
		if ( (getline < filename) >0) conv=$2;
		}' nedges
	
	if (( $6 == 4))
	then
		filename1="half_n"$1"_i"$int_range"_A"
	else
		filename1="half_n"$1"_i"$int_range"_B"
	fi

	filename="summary_n"$1"*_i"$int_range"_converged_bc"
	cat $filename > tttt
	gawk -v nagents=$1 -v k=$int_range -v rule=$6 'BEGIN{x1=0;y1=0}{if (x1!=0&& y1<0.5 && $2>=0.5) {x=$1-($2-0.5)*($1-x1)/($2-y1); print nagents, k, rule, x, x1,y1,$1,$2}; x1=$1; y1=$2}' tttt > $filename1
fi
