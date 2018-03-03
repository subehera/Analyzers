#/bin/bash
# https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs#JobSub

#jq=8nm
jq=8nh
#jq=1nd
#jq=2nd

echo $1
echo $2
echo $3
echo $4
echo $5
echo $6
#echo $7
#echo $8
#echo $9

debug=echo
bsub -R "pool>30000" -q $jq -J $6 run.sh $1 $2 $3 $4 $5
#./run.sh $1 $2 $3 $4 $5
sleep 1
