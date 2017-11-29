#!/bin/bash

count=0
for i in `ls -d Cumulant*/*`
#for i in `ls -d Cumulant*/*std*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   #crab status -d $i --long
   crab status -d $i
   sleep 1
   echo "---------------------------------------------"
   echo " " 
   let count++
done

echo "######### Summary #######"
echo "Number of task checked: $count"
