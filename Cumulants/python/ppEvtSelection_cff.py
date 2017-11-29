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
