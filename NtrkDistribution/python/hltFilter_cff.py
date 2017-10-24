import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#high multiplicity path
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





