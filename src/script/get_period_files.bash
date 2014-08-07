#! /bin/bash

if (( $# != 2 ))
then
	echo "Usage: $0 <filename> <kind>"
	echo " kind: 1(N), 2(X), 3(Y), 4 (g), 5 (op)"
else
	if (( $2==1 )); then
		gawk '{print $1, $18}' $1 > "vary_n.per0"
		gawk '{print $1, $19}' $1 > "vary_n.per1"
		gawk '{print $1, $20}' $1 > "vary_n.per2"
		gawk '{print $1, $21}' $1 > "vary_n.per3"
		gawk '{print $1, $22}' $1 > "vary_n.per4"
		gawk '{print $1, $23}' $1 > "vary_n.per5"
		gawk '{print $1, $24}' $1 > "vary_n.per6"
		gawk '{print $1, $25}' $1 > "vary_n.per7"
	elif (( $2==2 )); then
		gawk '{print $2, $18}' $1 > "vary_x.per0"
		gawk '{print $2, $19}' $1 > "vary_x.per1"
		gawk '{print $2, $20}' $1 > "vary_x.per2"
		gawk '{print $2, $21}' $1 > "vary_x.per3"
		gawk '{print $2, $22}' $1 > "vary_x.per4"
		gawk '{print $2, $23}' $1 > "vary_x.per5"
		gawk '{print $2, $24}' $1 > "vary_x.per6"
		gawk '{print $2, $25}' $1 > "vary_x.per7"
	elif (( $2==3 )); then
		gawk '{print $3, $18}' $1 > "vary_ny.per0"
		gawk '{print $3, $19}' $1 > "vary_ny.per1"
		gawk '{print $3, $20}' $1 > "vary_ny.per2"
		gawk '{print $3, $21}' $1 > "vary_ny.per3"
		gawk '{print $3, $22}' $1 > "vary_ny.per4"
		gawk '{print $3, $23}' $1 > "vary_ny.per5"
		gawk '{print $3, $24}' $1 > "vary_ny.per6"
		gawk '{print $3, $25}' $1 > "vary_ny.per7"
	elif (( $2==4 )); then
		gawk '{print $4, $18}' $1 > "vary_g.per0"
		gawk '{print $4, $19}' $1 > "vary_g.per1"
		gawk '{print $4, $20}' $1 > "vary_g.per2"
		gawk '{print $4, $21}' $1 > "vary_g.per3"
		gawk '{print $4, $22}' $1 > "vary_g.per4"
		gawk '{print $4, $23}' $1 > "vary_g.per5"
		gawk '{print $4, $24}' $1 > "vary_g.per6"
		gawk '{print $4, $25}' $1 > "vary_g.per7"
	else
		gawk '{print $5, $18}' $1 > "vary_op.per0"
		gawk '{print $5, $19}' $1 > "vary_op.per1"
		gawk '{print $5, $20}' $1 > "vary_op.per2"
		gawk '{print $5, $21}' $1 > "vary_op.per3"
		gawk '{print $5, $22}' $1 > "vary_op.per4"
		gawk '{print $5, $23}' $1 > "vary_op.per5"
		gawk '{print $5, $24}' $1 > "vary_op.per6"
		gawk '{print $5, $25}' $1 > "vary_op.per7"
	fi
fi
