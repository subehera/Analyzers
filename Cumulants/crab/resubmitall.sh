#!/bin/bash

for i in `ls -d Cumulant*/*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   #crab resubmit -d $i --maxmemory 2500 --maxjobruntime 2750
   #crab resubmit -d $i --maxmemory 2500 --maxjobruntime 2750 --siteblacklist=T3_UK_London_QMUL
   crab resubmit -d $i
   sleep 1
   echo "---------------------------------------------"
   echo " " 
done
