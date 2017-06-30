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
                             #Vertex selection
                             minvz         = cms.untracked.double(-15.0), 
                             maxvz         = cms.untracked.double(15.0),
                             maxrho        = cms.untracked.double(0.2),
                             isBVselByMult = cms.untracked.bool(False),
                             #Multiplicity selection
                             noffmin       = cms.untracked.double(0.3),
                             noffmax       = cms.untracked.double(3.0),
                             ptnoffmin     = cms.untracked.double(0.3),
                             ptnoffmax     = cms.untracked.double(3.0),
                             dzdzerrornoff = cms.untracked.double(3.0),
                             d0d0errornoff = cms.untracked.double(3.0),
                             pterrorptnoff = cms.untracked.double(0.1),
                             #Track selection
                             etamin    = cms.untracked.double(0.3),
                             etamax    = cms.untracked.double(3.0),
                             ptmin     = cms.untracked.double(0.3),
                             ptmax     = cms.untracked.double(3.0),
                             dzdzerror = cms.untracked.double(3.0),
                             d0d0error = cms.untracked.double(3.0),
                             pterrorpt = cms.untracked.double(0.1),
                             #Cumulant
                             harm    = cms.untracked.int32(2),
                             cweight = cms.untracked.bool(True),
                             #Acc X Eff
                             fname = cms.untracked.InputTag('Hijing_8TeV_dataBS.root'),
                             effmultbin = cms.untracked.vint32(0,10000)
)
