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
                             #Efficiency/Fake correction
                             cweight = cms.untracked.bool(True),
                             fname   = cms.InputTag(""),
                             effCorrByCent = cms.untracked.bool(False),
                             effCorrBinMin = cms.untracked.vint32(0),
                             effCorrBinMax = cms.untracked.vint32(10000)
                             #Vertex selection
                             nTrkAssoToVtx = cms.untracked.uint32(2),
                             selectVtxByMult = cms.untracked.bool(False),
                             #Track selection
                             dzdzerror = cms.untracked.double(3.0),
                             d0dz0rror = cms.untracked.double(3.0),
                             pTerrorpT = cms.untracked.double(0.1),
                             pTminTrk_trg = cms.untracked.vdouble(0.3),
                             pTmaxTrk_trg = cms.untracked.vdouble(3.0)
                             pTminTrk_asso = cms.untracked.vdouble(0.3),
                             pTmaxTrk_asso = cms.untracked.vdouble(3.0)
)
