if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'CumulantHM'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
    config.JobType.maxMemoryMB = 2500
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/cumulants_hlt185_cfg.py'
    config.Data.unitsPerJob = 10
#    config.Data.unitsPerJob = 40 for V0 only
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
#    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumu/'
    config.Data.publication = False
#    config.Site.storageSite = 'T2_US_MIT'
#    config.Site.storageSite = 'T3_US_Rice'
    config.Site.storageSite = 'T2_CH_CERN'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    config.General.requestName = 'pPb2016_pPb185_cumulants_b1_v1'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb185_cumulants_b2_v1'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb185_cumulants_b3_v1'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb185_cumulants_b4_v1'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb185_cumulants_b5_v1'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb185_cumulants_b6_v1'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b1_v1'
    config.Data.inputDataset = '/PAHighMultiplicity1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b2_v1'
    config.Data.inputDataset = '/PAHighMultiplicity2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b3_v1'
    config.Data.inputDataset = '/PAHighMultiplicity3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b4_v1'
    config.Data.inputDataset = '/PAHighMultiplicity4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b5_v1'
    config.Data.inputDataset = '/PAHighMultiplicity5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp185_cumulants_b6_v1'
    config.Data.inputDataset = '/PAHighMultiplicity6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp185_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb250_cumulants_b7_v1'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb250_cumulants_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt250_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp250_cumulants_b7_v1'
    config.Data.inputDataset = '/PAHighMultiplicity7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp250_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb120_cumulants_b0_v1'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb120_cumulants_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt120_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_pPb150_cumulants_b0_v1'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb150_cumulants_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt150_cfg.py'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp120_cumulants_b0_v1'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.JobType.psetName = '../cfg/cumulants_hlt120_cfg.py'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp120_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp150_cumulants_b0_v1'
    config.Data.inputDataset = '/PAHighMultiplicity0/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.JobType.psetName = '../cfg/cumulants_hlt150_cfg.py'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp150_cumulants_v1'
    submit(config)
