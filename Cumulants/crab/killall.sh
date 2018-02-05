#!/bin/bash

#for i in `ls -d CumulantHM/*2sub*`
#for i in `ls -d CumulantHM/*3sub*_*_v1`
for i in `ls -d CumulantHM/crab_pPb2016_*_4sub_*_c*`
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
