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
    config.JobType.maxMemoryMB = 2500
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/cumulants_std_cfg.py'
    config.Data.unitsPerJob = 10
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    #config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumu/'
    config.Data.lumiMask = 'Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt'
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

    config.General.requestName = 'pp2015E_cumulants_std_b1_v10'
    config.JobType.psetName = '../cfg/cumulants_std_cfg.py'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2015E_cumulants_std_test'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b1_v10'
    config.JobType.psetName = '../cfg/cumulants_2sub_cfg.py'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2015E_cumulants_2sub_test'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_3sub_b1_v10'
    config.JobType.psetName = '../cfg/cumulants_3sub_cfg.py'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2015E_cumulants_3sub_test'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b1_v10'
    config.JobType.psetName = '../cfg/cumulants_4sub_cfg.py'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2015E_cumulants_4sub_test'
    submit(config)

