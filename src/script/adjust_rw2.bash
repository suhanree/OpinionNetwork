#! /bin/bash

for ((i=10;i<301;i+=10))
do
	echo $i
	gawk -v nagents=$i '{adj=$2/nagents; print $1, adj;}' ave.n$i.sta > ave_adj.n$i.sta
done
