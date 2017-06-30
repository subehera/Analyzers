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
        ''
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
process.defaultTrigSel = hltHMMB.clone()

#Pileup filter
process.load("TrackingCode.pileUpFilter.pileUpFilter_cff")
from RefFlowAna.MGCumuv24.PPPileUpVertexFilter_cff import *
process.PUFliter = pileupVertexFilterCut_dz10_GplusPP


# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cfi")
process.defaultAnalysis = process.defaultCumu.clone()

process.p = cms.Path(process.defaultTrigSel * # Select MB events
                     process.PUFilter *       # PU filter
                     process.defaultAnalysis) # Run the analyzer
