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
                             #Event classifier # 0 == centrality, 1 == n_trk^offline
                             evtclassifier = cms.untracked.int32(0), 
                             centmin = cms.untracked.int32(0), 
                             centmax = cms.untracked.int32(100), 
                             noffmin = cms.untracked.int32(0), 
                             noffmax = cms.untracked.int32(10000), 
                             #Efficiency/Fake correction
                             cweight = cms.untracked.bool(True),
                             fname   = cms.untracked.InputTag("EffCorrectionsPixel_TT_pt_0_10_v2.root"),
                             effCorrBinMin = cms.untracked.vint32(0,5,10,30,50),
                             effCorrBinMax = cms.untracked.vint32(5,10,30,50,100),
                             #Vertex selection
                             nTrkAssoToVtx = cms.untracked.uint32(2),
                             selectVtxByMult = cms.untracked.bool(False),
                             zminVtx = cms.untracked.double(-15.0),
                             zmaxVtx = cms.untracked.double(15.0),
                             rhomaxVtx = cms.untracked.double(0.2),
                             #Track selection
                             dzdzerror = cms.untracked.double(3.0),
                             d0dz0rror = cms.untracked.double(3.0),
                             pTerrorpT = cms.untracked.double(0.1),
                             pTminTrk_trg = cms.untracked.vdouble(0.3),
                             pTmaxTrk_trg = cms.untracked.vdouble(3.0),
                             pTminTrk_ass = cms.untracked.vdouble(0.3),
                             pTmaxTrk_ass = cms.untracked.vdouble(3.0),
                             etaminTrk_trg = cms.untracked.double(-2.4),
                             etamaxTrk_trg = cms.untracked.double(2.4),
                             etaminTrk_ass = cms.untracked.double(-2.4),
                             etamaxTrk_ass = cms.untracked.double(2.4),
                             #Histogram binning
                             nEtaBins = cms.untracked.int32(32),
                             nPhiBins = cms.untracked.int32(32),
                             #Mixing factor
                             bkgFactor = cms.untracked.uint32(10)
)
