#!/bin/bash

./generateCFG.sh 0 0 0 
./generateCFG.sh 0 1 0 
./generateCFG.sh 0 2 0 

for i in `ls crab3_*.py`
do
	echo $i
	crab submit -c $i	
done
