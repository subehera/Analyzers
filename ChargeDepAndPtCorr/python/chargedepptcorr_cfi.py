import FWCore.ParameterSet.Config as cms

defaultCPDC = cms.EDAnalyzer('ChargeDepAndPtCorr', #Analyzer named: Correspond to the class name in 'plugin' folder
                             #Track collection
                             tracks    = cms.InputTag('hiGeneralAndPixelTracks'),
                             #Vertex collection
                             vertex    = cms.InputTag('hiSelectedVertex'),
                             #Calorimeter tower collection
                             caloTower = cms.InputTag('towerMaker'),
                             #Centrality
                             centralitySrc    = cms.InputTag("hiCentrality"),
                             centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
                             #track selection
                             pTminTrk = cms.untracked.double(0.3),
                             pTmaxTrk = cms.untracked.double(3.0),
                             #efficiency correction
                             cweight    = cms.untracked.bool(True),
                             fname      = cms.untracked.InputTag('Hijing_8TeV_MB_eff_v2.root'),
                             effmultbin = cms.untracked.vint32(0,10000)
)
