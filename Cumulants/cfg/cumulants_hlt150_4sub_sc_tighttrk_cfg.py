import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
#process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
)

#process.Timing = cms.Service("Timing",
#  summaryOnly = cms.untracked.bool(True),
#  useJobReport = cms.untracked.bool(False)
#)

# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/hidata/PARun2016C/PAHighMultiplicity0/AOD/PromptReco-v1/000/285/479/00000/3AB7179C-DCAE-E611-980E-FA163EC8DDF7.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('cumulants_hlt150_4sub.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Express_v15', '')
# Getting calib from GT
#process.GlobalTag.toGet = cms.VPSet(
#  cms.PSet(
#    record = cms.string("HeavyIonRcd"),
#    tag = cms.string("CentralityTable_HFtowersPlusTrunc200_EPOS5TeV_v80x01_mc"),
#    connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS"),
#    label = cms.untracked.string("HFtowersPlusTruncEpos")
#    )
#)


# __________________ Event selection _________________

# Define the trigger selection
from Analyzers.Cumulants.hltFilter_cff import *
process.defaultTrigSel = hlt150.clone()

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

#centrality
#process.load("RecoHI.HiCentralityAlgos.pACentrality_cfi")

#Pileup filter
process.load("TrackingCode.pileUpFilter.pileUpFilter_cff")


# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cff")
process.anaSC23 = process.sub4AnalysisSC23tighttrk.clone()
process.anaSC24 = process.sub4AnalysisSC24tighttrk.clone()

process.p3 = cms.Path(process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPA * # PA event selection
                     process.olvFilter_pPb8TeV_dz1p0*    # PU filter
                     #process.pACentrality *              # Centrality
                     process.anaSC23)            # Run the analyzer

process.p4 = cms.Path(process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPA * # PA event selection
                     process.olvFilter_pPb8TeV_dz1p0*    # PU filter
                     #process.pACentrality *              # Centrality
                     process.anaSC24)            # Run the analyzer

