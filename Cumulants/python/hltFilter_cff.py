import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#high multiplicity path
hltMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltMB.HLTPaths = ['HLT_L1MinimumBiasHF_OR_part*','HLT_ZeroBias_part*_v*','HLT_L1MinimumBiasHF1OR_part*_v*']
hltMB.andOr = cms.bool(True)
hltMB.throw = cms.bool(False)

hlt120 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt120.HLTPaths = ['HLT_PAFullTracks_Multiplicity120*_v*']
hlt120.andOr = cms.bool(True)
hlt120.throw = cms.bool(False)

hlt150 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt150.HLTPaths = ['HLT_PAFullTracks_Multiplicity120_v*','HLT_PAFullTracks_Multiplicity150*_v*']
hlt150.andOr = cms.bool(True)
hlt150.throw = cms.bool(False)

hlt185 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt185.HLTPaths = ['HLT_PAFullTracks_Multiplicity185*_v*']
hlt185.andOr = cms.bool(True)
hlt185.throw = cms.bool(False)

hlt250 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hlt250.HLTPaths = ['HLT_PAFullTracks_Multiplicity250_v*']
hlt250.andOr = cms.bool(True)
hlt250.throw = cms.bool(False)

NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

primaryVertexFilterPP = cms.EDFilter("VertexSelector",
    src = cms.InputTag("offlinePrimaryVertices"),
    cut = cms.string("!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2"), 
    filter = cms.bool(True),   # otherwise it won't filter the events
)

collisionEventSelectionPP = cms.Sequence(
                                       primaryVertexFilterPP *
                                       NoScraping )
