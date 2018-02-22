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
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/cumulants_mb_3sub_sc_tighttrk_cfg.py'
    config.Data.unitsPerJob = 30
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
#    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumuNew/'
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

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b1_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285479-285832_HI8TeV_PromptReco_pPb_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB1_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b2_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB2_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b3_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB3_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b4_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB4_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b5_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB5_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b6_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB6_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b7_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB7_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_pPb_cumulants_3sub_b8_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_pPbMB8_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b1_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias1/PARun2016C-PromptReco-v1/AOD'
    config.Data.lumiMask = 'Cert_285952-286496_HI8TeV_PromptReco_Pbp_Collisions16_JSON_NoL1T.txt'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB1_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b2_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias2/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB2_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b3_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias3/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB3_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b4_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias4/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB4_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b5_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias5/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB5_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b6_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias6/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB6_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b7_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias7/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB7_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b8_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias8/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB8_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b9_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias9/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB9_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b10_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias10/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB10_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b11_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias11/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB11_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b12_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias12/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB12_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b13_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias13/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB13_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b14_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias14/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB14_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b15_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias15/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB15_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b16_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias16/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB16_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b17_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias17/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB17_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b18_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias18/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB18_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b19_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias19/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB19_cumulants_3sub_sc_v14'
    submit(config)

    config.General.requestName = 'pPb2016_Pbp_cumulants_3sub_b20_sc_v14'
    config.Data.inputDataset = '/PAMinimumBias20/PARun2016C-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2016_PbpMB20_cumulants_3sub_sc_v14'
    submit(config)
