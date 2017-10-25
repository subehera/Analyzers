import FWCore.ParameterSet.Config as cms

process = cms.Process("NtrkDistribution")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100000

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
)


# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'root://cms-xrd-global.cern.ch//store/user/davidlw/L1MinimumBiasHF1/RecoSkim2015_2015DLowPU_ReTracking_v4/151109_223122/0000/pPb_HM_1.root'
    )
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True),
    #SkipEvent = cms.untracked.vstring('ProductNotFound')
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     #fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/NtrkDistribution/test/ntrkdist.root')
     fileName = cms.string('ntrkdist.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
#from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Express_v15', '')
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
from Analyzers.NtrkDistribution.hltFilter_cff import *
process.defaultTrigSel = hltpp13MBA.clone()

# Load HI event selection modules
#process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('Configuration.EventContent.EventContentHeavyIons_cff')

#centrality
#process.load("RecoHI.HiCentralityAlgos.pACentrality_cfi")

#Pileup filter
from Analyzers.NtrkDistribution.PPPileUpVertexFilter_cff import *
process.PUfilter = pileupVertexFilterCut_dz10_GplusPP


# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.NtrkDistribution.ntrkdist_cfi")
process.defaultAnalysis = process.defaultNtrkDist.clone()

process.p = cms.Path(process.defaultTrigSel *             # Select MB events
                     #process.collisionEventSelectionPA * # PA event selection
                     process.PUfilter *                   # PU filter
                     #process.pACentrality *              # Centrality
                     process.defaultAnalysis)             # Run the analyzer
