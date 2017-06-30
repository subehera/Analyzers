import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#high multiplicity path
hltHM80 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM80.HLTPaths = ['HLT_FullTracks_Multiplicity80_v*']
hltHM80.andOr = cms.bool(True)
hltHM80.throw = cms.bool(False)

hltHM100 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHM100.HLTPaths = ['HLT_FullTracks_Multiplicity100_v*']
hltHM100.andOr = cms.bool(True)
hltHM100.throw = cms.bool(False)

hltHMMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltHMMB.HLTPaths = ['HLT_L1MinimumBiasHF_OR_part*','HLT_ZeroBias_part*_v*','HLT_L1MinimumBiasHF1OR_part*_v*']
hltHMMB.andOr = cms.bool(True)
hltHMMB.throw = cms.bool(False)

