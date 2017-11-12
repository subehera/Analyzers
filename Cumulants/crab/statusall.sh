#!/bin/bash

for i in `ls -d Cumulant*/*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   crab status -d $i
   sleep 1
   echo "---------------------------------------------"
   echo " " 
done
