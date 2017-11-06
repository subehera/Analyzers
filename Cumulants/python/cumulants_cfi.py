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
                             isBVselByMult = cms.untracked.bool(True),
                             #Multiplicity selection
                             noffmin       = cms.untracked.int32(0),
                             noffmax       = cms.untracked.int32(10000),
                             ptnoffmin     = cms.untracked.double(0.3),
                             ptnoffmax     = cms.untracked.double(3.0),
                             dzdzerrornoff = cms.untracked.double(3.0),
                             d0d0errornoff = cms.untracked.double(3.0),
                             pterrorptnoff = cms.untracked.double(0.1),
                             #Track selection
                             etamin    = cms.untracked.double(-2.4),
                             etamax    = cms.untracked.double(2.4),
                             ptmin     = cms.untracked.double(0.3),
                             ptmax     = cms.untracked.double(3.0),
                             etasubmin = cms.vdouble(-2.4,-2.4,-2.4,-2.4,0.,0.,0.,0.),
                             etasubmax = cms.vdouble(0.,0.,0.,0.,2.4,2.4,2.4,2.4),
                             ptsubmin = cms.vdouble(0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3),
                             ptsubmax = cms.vdouble(3.0,3.0,3.0,3.0,3.0,3.0,3.0,3.0),
                             dzdzerror = cms.untracked.double(3.0),
                             d0d0error = cms.untracked.double(3.0),
                             pterrorpt = cms.untracked.double(0.1),
                             #Cumulant
                             harm     = cms.untracked.vint32(2,2,2,2),
                             nsubevt     = cms.untracked.int32(2),
                             cweight  = cms.untracked.bool(True),
                             #deltaeta = cms.untracked.double(0.),
                             #Acc X Eff
                             fname = cms.untracked.InputTag('Hijing_8TeV_dataBS.root'),
                             effmultbin = cms.untracked.vint32(0,10000)
)
