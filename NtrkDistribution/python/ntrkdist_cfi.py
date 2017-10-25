import FWCore.ParameterSet.Config as cms

defaultNtrkDist = cms.EDAnalyzer('NtrkDistribution', #Analyzer named: Correspond to the class name in 'plugin' folder
                             #Track collection
                             tracks    = cms.InputTag('generalTracks'),
                             #Vertex collection
                             vertex    = cms.InputTag('offlinePrimaryVertices'),
                             #Calorimeter tower collection
                             caloTower = cms.InputTag('towerMaker'),
                             #Centrality
                             centralitySrc    = cms.InputTag("hiCentrality"),
                             centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
                             #Vertex selection
                             minvz         = cms.untracked.double(-150.0), 
                             maxvz         = cms.untracked.double(150.0),
                             maxrho        = cms.untracked.double(100.),
                             isBVselByMult = cms.untracked.bool(True),
                             #Multiplicity selection
                             noffmin       = cms.untracked.int32(0),
                             noffmax       = cms.untracked.int32(100000),
                             ptnoffmin     = cms.untracked.double(0.4),
                             ptnoffmax     = cms.untracked.double(100000),
                             dzdzerrornoff = cms.untracked.double(3.0),
                             d0d0errornoff = cms.untracked.double(3.0),
                             pterrorptnoff = cms.untracked.double(0.1),
                             #Track selection
                             etamin    = cms.untracked.double(-2.4),
                             etamax    = cms.untracked.double(2.4),
                             ptmin     = cms.untracked.double(0.3),
                             ptmax     = cms.untracked.double(3.0),
                             dzdzerror = cms.untracked.double(3.0),
                             d0d0error = cms.untracked.double(3.0),
                             pterrorpt = cms.untracked.double(0.1),
                             #Acc X Eff
                             fname = cms.untracked.InputTag('trkEff_pp_all_74X_origin.root'),
                             effmultbin = cms.untracked.vint32(0,10000)
)
