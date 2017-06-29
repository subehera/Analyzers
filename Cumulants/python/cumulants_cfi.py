import FWCore.ParameterSet.Config as cms

defaultCumu = cms.EDAnalyzer('Cumulants', #Analyzer named: Correspond to the class name in 'plugin' folder
                             #Track collection
                             tracks    = cms.InputTag('generalTracks'),
                             #Vertex collection
                             vertex    = cms.InputTag('offlinePrimaryVertices'),
                             #Calorimeter tower collection
                             caloTower = cms.InputTag('towerMaker'),
                             #Centrality
                             centralitySrc    = cms.InputTag("hiCentrality"),
                             centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
                             #track selection
                             pTminTrk = cms.untracked.double(0.3),
                             pTmaxTrk = cms.untracked.double(3.0),
                             harm     = cms.untracked.int32(2),
)
