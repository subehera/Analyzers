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
    #config.JobType.maxMemoryMB = 2500
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/cumulants_mb_4sub_sc_cfg.py'
    config.Data.unitsPerJob = 10
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    #config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumuNew/'
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

    config.General.requestName = 'pp2015E_cumulants_4sub_b1_sc_v1'
    config.Data.inputDataset = '/MinimumBias1/Run2015E-PromptReco-v1/AOD'
    config.Data.outputDatasetTag = 'pp2015E_cumulants_4sub_sc_v1'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b2_sc_v1'
    config.Data.inputDataset = '/MinimumBias2/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b3_sc_v1'
    config.Data.inputDataset = '/MinimumBias3/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b4_sc_v1'
    config.Data.inputDataset = '/MinimumBias4/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b5_sc_v1'
    config.Data.inputDataset = '/MinimumBias5/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b6_sc_v1'
    config.Data.inputDataset = '/MinimumBias6/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b7_sc_v1'
    config.Data.inputDataset = '/MinimumBias7/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b8_sc_v1'
    config.Data.inputDataset = '/MinimumBias8/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b9_sc_v1'
    config.Data.inputDataset = '/MinimumBias9/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b10_sc_v1'
    config.Data.inputDataset = '/MinimumBias10/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b11_sc_v1'
    config.Data.inputDataset = '/MinimumBias11/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b12_sc_v1'
    config.Data.inputDataset = '/MinimumBias12/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b13_sc_v1'
    config.Data.inputDataset = '/MinimumBias13/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b14_sc_v1'
    config.Data.inputDataset = '/MinimumBias14/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b15_sc_v1'
    config.Data.inputDataset = '/MinimumBias15/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b16_sc_v1'
    config.Data.inputDataset = '/MinimumBias16/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b17_sc_v1'
    config.Data.inputDataset = '/MinimumBias17/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b18_sc_v1'
    config.Data.inputDataset = '/MinimumBias18/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b19_sc_v1'
    config.Data.inputDataset = '/MinimumBias19/Run2015E-PromptReco-v1/AOD'
    submit(config)

    config.General.requestName = 'pp2015E_cumulants_4sub_b20_sc_v1'
    config.Data.inputDataset = '/MinimumBias20/Run2015E-PromptReco-v1/AOD'
    submit(config)
