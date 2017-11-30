#!/bin/bash

for i in `ls -d Cumulant*/*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   crab resubmit -d $i --maxmemory 2500 --maxjobruntime 2750
   sleep 1
   echo "---------------------------------------------"
   echo " " 
done
