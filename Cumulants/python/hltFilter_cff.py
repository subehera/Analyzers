import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#high multiplicity path
hltMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltMB.HLTPaths = ['HLT_L1MinimumBiasHF_OR_part*','HLT_ZeroBias_part*_v*','HLT_L1MinimumBiasHF1OR_part*_v*']
hltMB.andOr = cms.bool(True)
hltMB.throw = cms.bool(False)

hlt60 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt60.HLTPaths = ['HLT_PixelTracks_Multiplicity60_v*']
hlt60.andOr = cms.bool(True)
hlt60.throw = cms.bool(False)

hlt85 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt85.HLTPaths = ['HLT_PixelTracks_Multiplicity85_v*']
hlt85.andOr = cms.bool(True)
hlt85.throw = cms.bool(False)

hlt110 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt110.HLTPaths = ['HLT_PixelTracks_Multiplicity110_v*']
hlt110.andOr = cms.bool(True)
hlt110.throw = cms.bool(False)

hlt135 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt135.HLTPaths = ['HLT_PixelTracks_Multiplicity135_v*']
hlt135.andOr = cms.bool(True)
hlt135.throw = cms.bool(False)

