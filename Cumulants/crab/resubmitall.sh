#!/bin/bash

for i in `ls -d Cumulant*/*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   crab resubmit -d $i --maxmemory 3000
   sleep 1
   echo "---------------------------------------------"
   echo " " 
done
