if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    from CRABClient.UserUtilities import config, getUsernameFromSiteDB
    config = config()

    config.General.workArea = 'ChargeDepPtCorr_PbPb_pixelReReco'
    config.General.transferOutputs = True
    config.General.transferLogs = False
    config.JobType.pluginName = 'Analysis'
#    config.JobType.maxMemoryMB = 3000
    config.JobType.psetName = '../cfg/chargedepptcorr_base_cfg.py'
    config.Data.unitsPerJob = 50
    config.Data.totalUnits = -1
    config.Data.inputDBS = 'global'
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.publication = False
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

    ###############################
    #    Standard analysis        #
    ###############################
    ##### Central events 0-10% ####
    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_central_v1'
    config.JobType.psetName = '../cfg/chargedepptcorr_central_cfg.py'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_central_v1'
    submit(config)

    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_central_v2'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_central_v2'
    submit(config)

    ##### Mid-central events 10-30% ####
    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_midcentral_v1'
    config.JobType.psetName = '../cfg/chargedepptcorr_midcentral_cfg.py'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_midcentral_v1'
    submit(config)

    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_midcentral_v2'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_midcentral_v2'
    submit(config)

    ##### Mid-peripheral events 30-50% ####
    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_midperipheral_v1'
    config.JobType.psetName = '../cfg/chargedepptcorr_midperipheral_cfg.py'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_midperipheral_v1'
    submit(config)

    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_midperipheral_v2'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_midperipheral_v2'
    submit(config)

    ##### Peripheral events 50-90% ####
    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_peripheral_v1'
    config.JobType.psetName = '../cfg/chargedepptcorr_peripheral_cfg.py'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_peripheral_v1'
    submit(config)

    config.General.requestName = 'PbPb2015_pixelReReco_chgdepcorr_std_peripheral_v2'
    config.Data.inputDataset = '/HIMinimumBias2/HIRun2015-25Aug2016-v1/AOD'
    config.Data.lumiMask = '../data/JSON/Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.outputDatasetTag = 'Historgram_chgepcorr_PbPb2015_pixelReReco_std_peripheral_v2'
    submit(config)

