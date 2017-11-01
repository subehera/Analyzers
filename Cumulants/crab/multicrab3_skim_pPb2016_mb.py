if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'CumulantMB'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
#    config.JobType.maxMemoryMB = 3000
    config.JobType.psetName = '../cfg/cumulants_cfg.py'
    config.Data.unitsPerJob = 10
#    config.Data.unitsPerJob = 40 for V0 only
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = False
    config.Site.storageSite = 'T2_US_MIT'
#    config.Site.storageSite = 'T3_US_Rice'

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

    config.General.requestName = 'pPb2016_pPb_cumulants_b1_v1'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPb_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b1_v1'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b2_v1'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b3_v1'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b4_v1'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b5_v1'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b6_v1'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b7_v1'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b8_v1'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b9_v1'
    config.Data.inputDataset = '/PAMinimumBias9/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b10_v1'
    config.Data.inputDataset = '/PAMinimumBias10/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b11_v1'
    config.Data.inputDataset = '/PAMinimumBias11/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b12_v1'
    config.Data.inputDataset = '/PAMinimumBias12/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b13_v1'
    config.Data.inputDataset = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b14_v1'
    config.Data.inputDataset = '/PAMinimumBias14/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b15_v1'
    config.Data.inputDataset = '/PAMinimumBias15/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b16_v1'
    config.Data.inputDataset = '/PAMinimumBias16/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b17_v1'
    config.Data.inputDataset = '/PAMinimumBias17/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b18_v1'
    config.Data.inputDataset = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b19_v1'
    config.Data.inputDataset = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_b20_v1'
    config.Data.inputDataset = '/PAMinimumBias20/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_Pbp_cumulants_v1'
    submit(config)
