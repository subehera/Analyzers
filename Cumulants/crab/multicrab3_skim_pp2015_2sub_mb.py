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
    config.JobType.psetName = '../cfg/cumulants_2sub_cfg.py'
    config.Data.unitsPerJob = 10
#    config.Data.unitsPerJob = 40 for V0 only
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.lumiMask = 'Cert_262081-262328_5TeV_PromptReco_Collisions15_25ns_JSON.txt'
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

    config.General.requestName = 'pp2015E_cumulants_2sub_b1_v10'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'RecoSkim2015E_cumulants_2sub_v10'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b2_v10'
    config.Data.inputDataset = '/MinimumBias2/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b3_v10'
    config.Data.inputDataset = '/MinimumBias3/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b4_v10'
    config.Data.inputDataset = '/MinimumBias4/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b5_v10'
    config.Data.inputDataset = '/MinimumBias5/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b6_v10'
    config.Data.inputDataset = '/MinimumBias6/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b7_v10'
    config.Data.inputDataset = '/MinimumBias7/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b8_v10'
    config.Data.inputDataset = '/MinimumBias8/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b9_v10'
    config.Data.inputDataset = '/MinimumBias9/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b10_v10'
    config.Data.inputDataset = '/MinimumBias10/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b11_v10'
    config.Data.inputDataset = '/MinimumBias11/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b12_v10'
    config.Data.inputDataset = '/MinimumBias12/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b13_v10'
    config.Data.inputDataset = '/MinimumBias13/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b14_v10'
    config.Data.inputDataset = '/MinimumBias14/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b15_v10'
    config.Data.inputDataset = '/MinimumBias15/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b16_v10'
    config.Data.inputDataset = '/MinimumBias16/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b17_v10'
    config.Data.inputDataset = '/MinimumBias17/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b18_v10'
    config.Data.inputDataset = '/MinimumBias18/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b19_v10'
    config.Data.inputDataset = '/MinimumBias19/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_2sub_b20_v10'
    config.Data.inputDataset = '/MinimumBias20/Run2015E-PromptReco-v1/AOD'
    submit(config)
