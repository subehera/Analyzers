#!/bin/bash
echo "Generation config file for:"
echo "HLT path ~~~>   ${1}"
echo "Dataset  ~~~>  ${2}"
echo "Version  ~~~> v${3}"

echo "### this is an example for running on RECO" > crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py  
echo "### the name must be changed crab.cfg for actual running" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "from CRABClient.UserUtilities import config, getUsernameFromSiteDB" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config = config()" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.General.requestName = 'pPb5TeV_PromptReco_MBv${2}_v${1}'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.General.workArea = 'pPb5TeV2015Ana_data'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.General.transferOutputs = True" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.General.transferLogs = False" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 

echo "config.JobType.pluginName = 'Analysis'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 

# 0 == MB, > 0 == HM
if [ ${1} -eq 0 ]
then
echo "config.JobType.psetName = '$CMSSW_BASE/src/Analyzers/NtrkDistribution/cfg/pPb5TeV_MB_ntrkdist_cfg.py'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
elif [ ${1} -eq 1 ]
then
echo "config.JobType.psetName = '$CMSSW_BASE/src/Analyzers/NtrkDistribution/cfg/pPb5TeV_MB_ntrkdist_cfg.py'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
fi

echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
# 0 == PromptReco, 1 == ReReco, 2 == Reverse 
if [ ${2} -eq 0 ]
then
echo "config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 1 ]
then
echo "config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Rereco_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
elif [ ${2} -eq 2 ]
then
echo "config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Reverse_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
fi
echo "" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.inputDBS = 'phys03'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.splitting = 'LumiBased'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.unitsPerJob = 100" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
echo "config.Data.publication = False" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py
echo "config.Site.storageSite = 'T2_CH_CERN'" >> crab3_ntrkdist_HLT_${1}_Data_${2}_v${3}.py 
