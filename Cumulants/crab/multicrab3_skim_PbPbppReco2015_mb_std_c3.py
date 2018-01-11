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
    config.JobType.psetName = '../cfg/cumulants_mb_std_c3_cfg.py'
    config.JobType.maxJobRuntimeMin = 2750
    config.Data.unitsPerJob = 5
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    #config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumu18/'
    config.Data.lumiMask = 'Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
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

    config.General.requestName = 'PbPbppRereco2015_cumulants_std_b5_c3_v1'
    config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-02May2016-v1/AOD'
    submit(config)

    config.General.requestName = 'PbPbppRereco2015_cumulants_std_b6_c3_v1'
    config.Data.inputDataset = '/HIMinimumBias6/HIRun2015-02May2016-v1/AOD'
    submit(config)

    config.General.requestName = 'PbPbppRereco2015_cumulants_std_b7_c3_v1'
    config.Data.inputDataset = '/HIMinimumBias7/HIRun2015-02May2016-v1/AOD'
    submit(config)

    config.General.requestName = 'PbPbppRereco2015_TrkOnly_cumulants_std_b5_c3_v1'
    config.Data.lumiMask = 'Cert_263685-263757_PromptReco_HICollisions15_TrackerOnly_JSON.txt'
    config.Data.inputDataset = '/HIMinimumBias5/HIRun2015-02May2016-v1/AOD'
    submit(config)

    config.General.requestName = 'PbPbppRereco2015_TrkOnly_cumulants_std_b6_c3_v1'
    config.Data.inputDataset = '/HIMinimumBias6/HIRun2015-02May2016-v1/AOD'
    submit(config)

    config.General.requestName = 'PbPbppRereco2015_TrkOnly_cumulants_std_b7_c3_v1'
    config.Data.inputDataset = '/HIMinimumBias7/HIRun2015-02May2016-v1/AOD'
    submit(config)


