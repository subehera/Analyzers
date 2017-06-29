import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(10) 
)


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
     fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/Cumulants/test/cumulants.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Express_v15', '')


# __________________ Event selection _________________

# Define the trigger selection
from Analyzers.Cumulants.hltFilter_cff import *
process.defaultTrigSel = hltMB.clone()

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')
#process.defaultEvtSel = process.collisionEventSelectionPA.clone()

#Pileup filter
process.load("TrackingCode.pileUpFilter.pileUpFilter_cff")
#process.defaultPUFilter = process.olvFilter_pPb8TeV_dz1p0.clone()

# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cfi")
process.defaultAnalysis = process.defaultCumu.clone()
process.defaultAnalysis.pTmaxTrk = cms.untracked.double(6.0) 

process.p = cms.Path(#process.hfCoincFilter *
                     #process.PAprimaryVertexFilter *
                     #process.NoScraping *
                     process.defaultTrigSel *  # Select MB events
                     #process.defaultEvtSel  *  # PA event selection
                     #process.defaultPUFilter*  # PU filter
                     process.collisionEventSelectionPA *  # PA event selection
                     process.olvFilter_pPb8TeV_dz1p0*  # PU filter
                     process.defaultAnalysis)  # Run the analyzer
