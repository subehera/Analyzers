#!/bin/bash
rm *.py
#MD34
./generateCFG.sh 1 5 0 2016 
./generateCFG.sh 1 5 1 2016 
./generateCFG.sh 1 5 2 2016 
./generateCFG.sh 1 5 3 2016 
./generateCFG.sh 1 5 4 2016 
./generateCFG.sh 1 5 5 2016 
./generateCFG.sh 1 5 6 2016 
./generateCFG.sh 1 5 7 2016 
./generateCFG.sh 1 5 8 2016 
./generateCFG.sh 1 5 9 2016 
#MD2
./generateCFG.sh 1 4 0 2016 
./generateCFG.sh 1 4 1 2016 
./generateCFG.sh 1 4 2 2016 
./generateCFG.sh 1 4 3 2016 
./generateCFG.sh 1 4 4 2016 
./generateCFG.sh 1 4 5 2016 
./generateCFG.sh 1 4 6 2016 
./generateCFG.sh 1 4 7 2016 
./generateCFG.sh 1 4 8 2016 
./generateCFG.sh 1 4 9 2016 
#VdM2016
./generateCFG.sh 1 3 0 2016 
./generateCFG.sh 1 3 1 2016 
./generateCFG.sh 1 3 2 2016 
./generateCFG.sh 1 3 3 2016 
./generateCFG.sh 1 3 4 2016 
./generateCFG.sh 1 3 5 2016 
./generateCFG.sh 1 3 6 2016 
./generateCFG.sh 1 3 7 2016 
./generateCFG.sh 1 3 8 2016 
./generateCFG.sh 1 3 9 2016 
#JulyLowPU
./generateCFG.sh 2 2 1 2015 
./generateCFG.sh 2 2 2 2015 
./generateCFG.sh 2 2 3 2015 
./generateCFG.sh 2 2 4 2015 
./generateCFG.sh 2 2 5 2015 
./generateCFG.sh 2 2 6 2015 
./generateCFG.sh 2 2 7 2015 
./generateCFG.sh 2 2 8 2015 
#VdM2015
./generateCFG.sh 0 1 1 2015 
./generateCFG.sh 0 1 2 2015 
./generateCFG.sh 0 1 3 2015 
./generateCFG.sh 0 1 4 2015 
./generateCFG.sh 0 1 5 2015 
./generateCFG.sh 0 1 6 2015 
./generateCFG.sh 0 1 7 2015 
./generateCFG.sh 0 1 8 2015 
#TOTEM
./generateCFG.sh 0 0 1 2015 
./generateCFG.sh 0 0 2 2015 
./generateCFG.sh 0 0 3 2015 
./generateCFG.sh 0 0 4 2015 
./generateCFG.sh 0 0 5 2015 
./generateCFG.sh 0 0 6 2015 
./generateCFG.sh 0 0 7 2015 
./generateCFG.sh 0 0 8 2015 

for i in `ls crab3_*.py`
do
	echo $i
	crab submit -c $i
        sleep 1
        echo "########## Task submitted: ${i} ##########" 	
done
