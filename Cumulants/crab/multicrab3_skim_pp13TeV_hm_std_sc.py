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
    #config.JobType.maxMemoryMB = 2500
    config.JobType.maxJobRuntimeMin = 2750
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.unitsPerJob = 15
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
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

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_std_hlt105_noHM85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_85Off_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_std_hlt105_noHM85_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_std_hlt135_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015BLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_std_hlt105_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_std_hlt105_noHM85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_85Off_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_std_hlt105_noHM85_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_std_hlt135_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicity85/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-82adf6f67a5a8a894d71b010d31c18ec/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_std_hlt105_sc_v1'

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicity/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-266f47bcc90a343001055b934437977e/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_std_hlt105_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_std_hlt135_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016G_MD2Run279489_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_std_hlt105_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_std_hlt135_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016H_MD34_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_std_hlt105_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_std_hlt135_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_std_hlt85_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt85_std_sc_cfg.py'
    config.Data.inputDataset = '/HighMultiplicityEOF/davidlw-RecoSkim2016_2016B_VdMScan_HM_v1-120ac2c4f6b9f3699b9331175dcc4953/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_std_hlt85_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_std_hlt105_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt105_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_std_hlt105_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_std_hlt135_sc_v1'
    config.JobType.psetName = '../cfg/cumulants_hlt135_std_sc_cfg.py'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_std_hlt135_sc_v1'
    submit(config)
