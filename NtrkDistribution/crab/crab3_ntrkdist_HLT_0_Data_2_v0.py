### this is an example for running on RECO
### the name must be changed crab.cfg for actual running

from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'pPb5TeV_PromptReco_MBv2_v0'
config.General.workArea = 'pPb5TeV2015Ana_data'
config.General.transferOutputs = True
config.General.transferLogs = False
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = '/afs/cern.ch/user/m/mguilbau/AnalyzerForWei/CMSSW_5_3_20/src/Analyzers/NtrkDistribution/cfg/pPb5TeV_MB_ntrkdist_cfg.py'

config.Data.inputDataset = '/PAMinBiasUPC/davidlw-PA2013_FlowCorr_PromptReco_MB_Gplus_Reverse_ReTracking_v18-25c9a89be536a41c8ccb3c75e9fd9358/USER'

config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 100
config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
config.Data.publication = False
config.Site.storageSite = 'T2_CH_CERN'
