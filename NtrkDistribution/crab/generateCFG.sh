#!/bin/bash
echo "Generation config file for:"
echo "HLT path ~~~>  ${1}"
echo "Dataset  ~~~>  ${2}"
echo "Version  ~~~> v${3}"
echo "Year     ~~~>  ${4}"

echo "### this is an example for running on RECO" > crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py  
echo "### the name must be changed crab.cfg for actual running" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "from CRABClient.UserUtilities import config, getUsernameFromSiteDB" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config = config()" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.General.requestName = 'pp13TeV_PromptReco_MB${3}_HLT${1}_v${2}'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.General.workArea = 'pp13TeV${4}Ana_data'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.General.transferOutputs = True" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.General.transferLogs = False" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 

echo "config.JobType.pluginName = 'Analysis'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 

#
if [ ${1} -eq 0 ]
then
echo "config.JobType.psetName = '$CMSSW_BASE/src/Analyzers/NtrkDistribution/cfg/pp13TeV_MBA_ntrkdist_cfg.py'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
elif [ ${1} -eq 1 ]
then
echo "config.JobType.psetName = '$CMSSW_BASE/src/Analyzers/NtrkDistribution/cfg/pp13TeV_MBB_ntrkdist_cfg.py'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
elif [ ${1} -eq 2 ]
then
echo "config.JobType.psetName = '$CMSSW_BASE/src/Analyzers/NtrkDistribution/cfg/pp13TeV_ZB_ntrkdist_cfg.py'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
fi

echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py

# 0 == TOTEM, 1 == VdM2015, 2 == July low PU 2015, 3 == VdM2016, 4 == MD2, 5 == MD34 
if [ ${2} -eq 0 ]
then
echo "config.Data.inputDataset = '/L1MinimumBiasHF${3}/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 1 ]
then
echo "config.Data.inputDataset = '/L1MinimumBiasHF${3}/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 2 ]
then
echo "config.Data.inputDataset = '/ZeroBias${3}/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 3 ]
then
echo "config.Data.inputDataset = '/L1MinimumBias${3}/davidlw-RecoSkim2016_2016B_VdMScan_MB${3}_v3-e83d32f7a8d5ff64616c674d8395d834/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 4 ]
then
echo "config.Data.inputDataset = '/L1MinimumBias${3}/davidlw-RecoSkim2016_2016G_MD2Run279489_MB${3}_v3-e83d32f7a8d5ff64616c674d8395d834/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 5 ]
then
echo "config.Data.inputDataset = '/L1MinimumBias${3}/davidlw-RecoSkim2016_2016H_MD34_MB${3}_v3-e83d32f7a8d5ff64616c674d8395d834/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
fi

echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.inputDBS = 'phys03'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.splitting = 'LumiBased'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.unitsPerJob = 100" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.publication = False" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.Site.storageSite = 'T2_CH_CERN'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
