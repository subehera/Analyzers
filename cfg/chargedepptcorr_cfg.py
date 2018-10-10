import FWCore.ParameterSet.Config as cms

process = cms.Process("ChargeDepAndPtCorr")


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
        'root://cms-xrd-global.cern.ch//store/hidata/HIRun2015/HIMinimumBias2/AOD/25Aug2016-v1/90000/34CD034C-ED6F-E611-A55F-44A842124E15.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string(os.getenv('CMSSW_BASE') + '/src/Analyzers/ChargeDepAndPtCorr/test/chargeptdepcorr.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')


# __________________ Event selection _________________

# Define the trigger selection
# TO DO: To be moved in a separate config file
process.load("HLTrigger.HLTfilters.hltHighLevel_cfi")
process.hltMB = process.hltHighLevel.clone()
process.hltMB.HLTPaths = [
               "HLT_HIL1MinimumBiasHF1AND*",
               "HLT_HIL1MinimumBiasHF2AND*"
              ]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

# Load centrality producer for centrality calculation
process.load("RecoHI.HiCentralityAlgos.CentralityBin_cfi")
process.newCentralityBin = process.centralityBin.clone()

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('HeavyIonsAnalysis.EventAnalysis.HIClusterCompatibilityFilter_cfi')
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)
process.clusterCompatibilityFilter.clusterTrunc = cms.double(2.0)


# __________________ Event selection _________________

# Load you analyzer with initial configuration
process.load("Analyzers.ChargeDepAndPtCorr.chargedepptcorr_cfi")
process.defaultAnalysis = process.defaultCPDC.clone()
process.defaultAnalysis.pTmaxTrk = cms.untracked.double(6.0) 

process.p = cms.Path(process.hfCoincFilter3 *             # Requier HF coincidence with 3 GeV  
                     process.primaryVertexFilter *        # Clean up on vertices
                     process.clusterCompatibilityFilter * # Clean up on pileup
                     process.centralityBin *              # Compute centrality
                     process.hltMB *                      # Select MB events
                     process.defaultAnalysis)             # Run the analyzer
