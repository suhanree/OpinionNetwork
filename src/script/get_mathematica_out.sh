#! /bin/sh
echo "data=Import[\"test\",\"Table\"]" > temp.m
echo "ArrayPlot[data]" >> temp.m
echo "Export[\"test.eps\",%]" >> temp.m

math < temp.m > /dev/null
rm temp.m
