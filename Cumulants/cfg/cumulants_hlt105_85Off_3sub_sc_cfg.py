import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 2000

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

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     #fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/Cumulants/test/cumulants.root')
     fileName = cms.string('cumulants_3sub.root')
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
process.defaultTrigSel = hltHM105_85Off.clone()

#Pileup filter
from Analyzers.Cumulants.PPPileUpVertexFilter_cff import *
process.PUFilter = pileupVertexFilterCut_dz10_GplusPP


# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cfi")
process.anaSC23 = process.sub3AnalysisSC23.clone()
process.anaSC24 = process.sub3AnalysisSC24.clone()

process.p1 = cms.Path(process.defaultTrigSel * # Select MB events
                      process.PUFilter *       # PU filter
                      process.anaSC23)         # Run the analyzer

process.p2 = cms.Path(process.defaultTrigSel * # Select MB events
                      process.PUFilter *       # PU filter
                      process.anaSC24)         # Run the analyzer
