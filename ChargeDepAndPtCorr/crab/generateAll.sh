#!/bin/bash

rm crab3_*_*.py
rm crab3_*_*.pyc

./generateCFG.sh 2 0
./generateCFG.sh 2 1
./generateCFG.sh 2 2
./generateCFG.sh 2 3

for i in `ls crab3_*_*.py`
do
	echo $i
	crab submit --dryrun -c $i	
done
