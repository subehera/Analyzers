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
    config.JobType.psetName = '../cfg/cumulants_mb_3sub_sc_cfg.py'
    config.Data.unitsPerJob = 15
    config.Data.totalUnits = -1
    config.Data.splitting = 'LumiBased'
    config.Data.outLFNDirBase = '/store/group/phys_heavyions/flowcorr/SubCumuNew/'
    config.Data.publication = False
    config.Data.inputDBS = 'phys03'
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

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/ZeroBias1/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/ZeroBias2/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/ZeroBias3/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/ZeroBias4/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/ZeroBias5/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/ZeroBias6/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/ZeroBias7/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'JulyLowPU_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/ZeroBias8/davidlw-RecoSkim2015_2015BLowPU_ZB_ReTracking_v4-61cf514b424c95000f2b1b477390291b/USER'
    config.Data.outputDatasetTag = 'pp13TeV_JulyLowPU_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF1/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF2/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF3/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF4/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF5/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF6/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF7/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2015_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF8/davidlw-RecoSkim2015_2015CLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2015_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF1/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF2/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF3/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF4/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF5/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF6/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF7/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'TOTEM_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/L1MinimumBiasHF8/davidlw-RecoSkim2015_2015DLowPU_ReTracking_v4-6ca56d9a50b153298a3c6a7ed0fc5558/USER'
    config.Data.outputDatasetTag = 'pp13TeV_TOTEM_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias1/davidlw-RecoSkim2016_2016G_MD2Run279489_MB1_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias2/davidlw-RecoSkim2016_2016G_MD2Run279489_MB2_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias3/davidlw-RecoSkim2016_2016G_MD2Run279489_MB3_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias4/davidlw-RecoSkim2016_2016G_MD2Run279489_MB4_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias5/davidlw-RecoSkim2016_2016G_MD2Run279489_MB5_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias6/davidlw-RecoSkim2016_2016G_MD2Run279489_MB6_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias7/davidlw-RecoSkim2016_2016G_MD2Run279489_MB7_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias8/davidlw-RecoSkim2016_2016G_MD2Run279489_MB8_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'MD2_pp13TeV_cumulants_3sub_mb9_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias9/davidlw-RecoSkim2016_2016G_MD2Run279489_MB9_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD2_cumulants_3sub_mb9_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias1/davidlw-RecoSkim2016_2016H_MD34_MB1_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias2/davidlw-RecoSkim2016_2016H_MD34_MB2_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias3/davidlw-RecoSkim2016_2016H_MD34_MB3_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias4/davidlw-RecoSkim2016_2016H_MD34_MB4_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias5/davidlw-RecoSkim2016_2016H_MD34_MB5_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias6/davidlw-RecoSkim2016_2016H_MD34_MB6_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias7/davidlw-RecoSkim2016_2016H_MD34_MB7_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias8/davidlw-RecoSkim2016_2016H_MD34_MB8_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'MD34_pp13TeV_cumulants_3sub_mb9_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias9/davidlw-RecoSkim2016_2016H_MD34_MB9_v3-e83d32f7a8d5ff64616c674d8395d834/USER'
    config.Data.outputDatasetTag = 'pp13TeV_MD34_cumulants_3sub_mb9_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb0_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias0/davidlw-RecoSkim2016_2016B_VdMScan_MB0_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb0_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb1_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias1/davidlw-RecoSkim2016_2016B_VdMScan_MB1_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb1_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb2_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias2/davidlw-RecoSkim2016_2016B_VdMScan_MB2_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb2_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb3_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias3/davidlw-RecoSkim2016_2016B_VdMScan_MB3_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb3_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb4_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias4/davidlw-RecoSkim2016_2016B_VdMScan_MB4_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb4_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb5_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias5/davidlw-RecoSkim2016_2016B_VdMScan_MB5_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb5_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb6_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias6/davidlw-RecoSkim2016_2016B_VdMScan_MB6_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb6_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb7_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias7/davidlw-RecoSkim2016_2016B_VdMScan_MB7_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb7_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb8_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias8/davidlw-RecoSkim2016_2016B_VdMScan_MB8_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb8_sc_v1'
    submit(config)

    config.General.requestName = 'VdM2016_pp13TeV_cumulants_3sub_mb9_sc_v1'
    config.Data.inputDataset = '/L1MinimumBias9/davidlw-RecoSkim2016_2016B_VdMScan_MB9_v3-958277e0fa44e2e92209aae3b47c3ed2/USER'
    config.Data.outputDatasetTag = 'pp13TeV_VdM2016_cumulants_3sub_mb9_sc_v1'
    submit(config)

