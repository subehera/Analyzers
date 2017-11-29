#!/bin/bash

for i in `ls -d Cumulant*/*2sub*`
do

   echo " " 
   echo " " 
   echo "---------------------------------------------"
   echo $i
   echo "---------------------------------------------"
   echo " " 
   crab kill -d $i
   sleep 1
   echo "---------------------------------------------"
   echo " " 
done
