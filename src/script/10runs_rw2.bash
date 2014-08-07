#! /bin/bash

echo "nagents $1" >> param.in
echo "nagents $1" >> par_sta.in
for ((i=0; i<$1; i++))
do
	f_k=$i
done
echo "f_k $f_k" >> par_sta.in
tail=n$1

echo "out_ag_snapshot_file out_ag0.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag0.$tail" >> par_sta.in
echo "out_file gr0.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr0.$tail.out > a0.$tail.sta

echo "rseed1 200" >> param.in
echo "rseed2 200" >> param.in
echo "out_ag_snapshot_file out_ag1.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag1.$tail" >> par_sta.in
echo "out_file gr1.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr1.$tail.out > a1.$tail.sta

echo "rseed1 300" >> param.in
echo "rseed2 300" >> param.in
echo "out_ag_snapshot_file out_ag2.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag2.$tail" >> par_sta.in
echo "out_file gr2.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr2.$tail.out > a2.$tail.sta

echo "rseed1 400" >> param.in
echo "rseed2 400" >> param.in
echo "out_ag_snapshot_file out_ag3.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag3.$tail" >> par_sta.in
echo "out_file gr3.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr3.$tail.out > a3.$tail.sta

echo "rseed1 500" >> param.in
echo "rseed2 500" >> param.in
echo "out_ag_snapshot_file out_ag4.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag4.$tail" >> par_sta.in
echo "out_file gr4.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr4.$tail.out > a4.$tail.sta

echo "rseed1 600" >> param.in
echo "rseed2 600" >> param.in
echo "out_ag_snapshot_file out_ag5.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag5.$tail" >> par_sta.in
echo "out_file gr5.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr5.$tail.out > a5.$tail.sta

echo "rseed1 700" >> param.in
echo "rseed2 700" >> param.in
echo "out_ag_snapshot_file out_ag6.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag6.$tail" >> par_sta.in
echo "out_file gr6.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr6.$tail.out > a6.$tail.sta

echo "rseed1 800" >> param.in
echo "rseed2 800" >> param.in
echo "out_ag_snapshot_file out_ag7.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag7.$tail" >> par_sta.in
echo "out_file gr7.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr7.$tail.out > a7.$tail.sta

echo "rseed1 900" >> param.in
echo "rseed2 900" >> param.in
echo "out_ag_snapshot_file out_ag8.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag8.$tail" >> par_sta.in
echo "out_file gr8.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr8.$tail.out > a8.$tail.sta

echo "rseed1 1000" >> param.in
echo "rseed2 1000" >> param.in
echo "out_ag_snapshot_file out_ag9.$tail" >> param.in
RW2Sim param.in
echo "in_file out_ag9.$tail" >> par_sta.in
echo "out_file gr9.$tail.out" >> par_sta.in
Stat par_sta.in
gawk '{if ($2==0) print $1, $3;}' gr9.$tail.out > a9.$tail.sta

cat a?.$tail.sta | sort -n -k1,1 | gawk '{if ($1!=0 && $1!=bef) {print bef, sum/cnt; sum=0; cnt=0;}; sum+=$2; cnt++; bef=$1;}' > ave.$tail.sta
