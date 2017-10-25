import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#pA 8 TeV
hltPA8MB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8MB.HLTPaths = ['HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_*_v*']
hltPA8MB.andOr = cms.bool(True)
hltPA8MB.throw = cms.bool(False)

hltPA8120 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8120.HLTPaths = ['HLT_PAFullTracks_Multiplicity120*_v*']
hltPA8120.andOr = cms.bool(True)
hltPA8120.throw = cms.bool(False)

hltPA8150 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8150.HLTPaths = ['HLT_PAFullTracks_Multiplicity120_v*','HLT_PAFullTracks_Multiplicity150*_v*']
hltPA8150.andOr = cms.bool(True)
hltPA8150.throw = cms.bool(False)

hltPA8185 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8185.HLTPaths = ['HLT_PAFullTracks_Multiplicity185*_v*']
hltPA8185.andOr = cms.bool(True)
hltPA8185.throw = cms.bool(False)

hltPA8250 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8250.HLTPaths = ['HLT_PAFullTracks_Multiplicity250_v*']
hltPA8250.andOr = cms.bool(True)
hltPA8250.throw = cms.bool(False)

#pp 13 TeV 2015
hltpp13HM220 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM220.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*','HLT_PAPixelTracks_Multiplicity190_v*']
hltpp13HM220.andOr = cms.bool(True)
hltpp13HM220.throw = cms.bool(False)

hltpp13ZB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13ZB.HLTPaths = ['HLT_ZeroBias_part*_v*']

hltpp13MBA = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13MBA.HLTPaths = ['HLT_L1MinimumBiasHF1OR_part*_v*']

hltpp13HM60 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM60.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*']

hltpp13HM60On85Off = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM60On85Off.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','!HLT_PixelTracks_Multiplicity85*_v*']
hltpp13HM60On85Off.andOr = cms.bool(False)

hltpp13HM85On = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM85On.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*']

hltpp13HM110 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM110.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_PixelTracks_Multiplicity110*_v*']

hltpp13HM80105 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM80105.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*']

hltpp13HM10513560On = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM10513560On.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','!HLT_PixelTracks_Multiplicity85*_v*']
hltpp13HM10513560On.andOr = cms.bool(False)

hltpp13HM10513585On = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM10513585On.HLTPaths = ['HLT_PixelTracks_Multiplicity85*_v*']

#pp 13 TeV 2016
hltpp13HM80 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM80.HLTPaths = ['HLT_FullTracks_Multiplicity80_v*']
hltpp13HM80.andOr = cms.bool(True)
hltpp13HM80.throw = cms.bool(False)

hltpp13HM100 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13HM100.HLTPaths = ['HLT_FullTracks_Multiplicity100_v*']
hltpp13HM100.andOr = cms.bool(True)
hltpp13HM100.throw = cms.bool(False)

hltpp13MBB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltpp13MBB.HLTPaths = ['HLT_L1MinimumBiasHF_OR_part*']
hltpp13MBB.andOr = cms.bool(True)
hltpp13MBB.throw = cms.bool(False)






