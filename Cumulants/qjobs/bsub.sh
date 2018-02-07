#/bin/bash
# https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs#JobSub

#jq=8nm
jq=8nh
#jq=1nd
#jq=2nd

debug=echo
bsub -R "pool>30000" -q $jq -J $8 run.sh $1 $2 $3 $4 $5 $6 $7
sleep 1
