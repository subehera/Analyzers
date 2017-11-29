import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(300) 
)

process.Timing = cms.Service("Timing",
  summaryOnly = cms.untracked.bool(True),
  useJobReport = cms.untracked.bool(False)
)

# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/data/Run2015E/MinimumBias1/AOD/PromptReco-v1/000/262/157/00000/4EEE7A2C-9991-E511-B8AA-02163E011EF7.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('cumulants_4sub.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_Prompt_ppAt5TeV_v1', '')
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
process.defaultTrigSel = hltMB.clone()

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
process.load("Analyzers.Cumulants.ppEvtSelection_cff")

#centrality
#process.load("RecoHI.HiCentralityAlgos.pACentrality_cfi")

#Pileup filter
from Analyzers.Cumulants.PPPileUpVertexFilter_cff import *
process.PUFilter = pileupVertexFilterCut_dz10_GplusPP

# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cff")
process.anaV2 = process.sub4Analysis.clone()
process.anaV3 = process.sub4V3Analysis.clone()
process.anaV4 = process.sub4V4Analysis.clone()
process.anaSC23 = process.sub4AnalysisSC23.clone()
process.anaSC24 = process.sub4AnalysisSC24.clone()

process.p = cms.Path(
                     #process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPP * # PP event selection
                     process.PUFilter *    # PU filter
                     process.anaV2)            # Run the analyzer

process.p1 = cms.Path(
                     #process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPP * # PP event selection
                     process.PUFilter *    # PU filter
                     process.anaV3)            # Run the analyzer

process.p2 = cms.Path(
                     #process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPP * # PP event selection
                     process.PUFilter *    # PU filter
                     process.anaV4)            # Run the analyzer

process.p3 = cms.Path(
                     #process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPP * # PP event selection
                     process.PUFilter *    # PU filter
                     process.anaSC23)            # Run the analyzer

process.p4 = cms.Path(
                     #process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPP * # PP event selection
                     process.PUFilter *    # PU filter
                     process.anaSC24)            # Run the analyzer
