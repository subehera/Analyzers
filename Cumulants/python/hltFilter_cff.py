import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#high multiplicity path
hltHM85 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM85.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_FullTracks_Multiplicity80_v*']
hltHM85.andOr = cms.bool(True)
hltHM85.throw = cms.bool(False)

hltHM105 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM105.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_FullTracks_Multiplicity100_v*','HLT_FullTracks_Multiplicity80_v*']
hltHM105.andOr = cms.bool(True)
hltHM105.throw = cms.bool(False)

hltHM105_85Off = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM105_85Off.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','!HLT_PixelTracks_Multiplicity85*_v*']
hltHM105_85Off.andOr = cms.bool(False)
hltHM105_85Off.throw = cms.bool(False)

hltHM135 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM135.HLTPaths = ['HLT_PixelTracks_Multiplicity60*_v*','HLT_PixelTracks_Multiplicity85*_v*','HLT_PixelTracks_Multiplicity110_v*','HLT_FullTracks_Multiplicity100_v*','HLT_FullTracks_Multiplicity80_v*','HLT_FullTracks_Multiplicity130_v*']
hltHM135.andOr = cms.bool(True)
hltHM135.throw = cms.bool(False)

hltHMMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHMMB.HLTPaths = ['HLT_L1MinimumBiasHF_OR_part*','HLT_ZeroBias_part*_v*','HLT_L1MinimumBiasHF1OR_part*_v*']
hltHMMB.andOr = cms.bool(True)
hltHMMB.throw = cms.bool(False)
