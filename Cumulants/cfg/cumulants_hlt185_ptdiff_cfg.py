import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
#process.load("FWCore.MessageService.MessageLogger_cfi")
#process.MessageLogger.cerr.FwkReport.reportEvery = 200

# Configure the number of maximum event the analyser run on in interactive mode
# -1 == ALL
process.maxEvents = cms.untracked.PSet( 
    input = cms.untracked.int32(-1) 
)


# __________________ I/O files _________________

# Define the input file to run on in interactive mode
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'root://cms-xrd-global.cern.ch//store/hidata/PARun2016C/PAMinimumBias1/AOD/PromptReco-v1/000/285/480/00000/040B9307-28AF-E611-AE2A-02163E013572.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('cumulants.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '80X_dataRun2_Prompt_v15', '')
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
process.defaultTrigSel = hlt185.clone()

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

#centrality
#process.load("RecoHI.HiCentralityAlgos.pACentrality_cfi")

#Pileup filter
process.load("TrackingCode.pileUpFilter.pileUpFilter_cff")


# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cfi")
process.ana_pt10_inf_pos = process.defaultCumu.clone()
process.ana_pt10_inf_pos.ptminPOIPOS = cms.untracked.double(10.)
process.ana_pt10_inf_pos.ptmaxPOIPOS = cms.untracked.double(10000.)
process.ana_pt10_inf_neg = process.defaultCumu.clone()
process.ana_pt10_inf_neg.ptminPOINEG = cms.untracked.double(10.)
process.ana_pt10_inf_neg.ptmaxPOINEG = cms.untracked.double(10000.)


process.p_pt10_inf_pos = cms.Path(process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPA * # PA event selection
                     process.olvFilter_pPb8TeV_dz1p0*    # PU filter
                     process.ana_pt10_inf_pos)            # Run the analyzer

process.p_pt10_inf_neg = cms.Path(process.defaultTrigSel *            # Select MB events
                     process.collisionEventSelectionPA * # PA event selection
                     process.olvFilter_pPb8TeV_dz1p0*    # PU filter
                     process.ana_pt10_inf_neg)            # Run the analyzer
