import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")


# __________________ General _________________

# Configure the logger
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

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
     #'root://cms-xrd-global.cern.ch///store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/00000/002C1765-9B2E-E611-BA4B-F01FAFD5992D.root'
     'root://cms-xrd-global.cern.ch///store/group/phys_heavyions/qwang/PbPb2015/HIMinimumBias5/crab_HIMB5_ppReco_GMOVtxV0_Skim_v2/171130_055240/0000/reco_1.root'
    ),
    secondaryFileNames = cms.untracked.vstring(
     'root://cms-xrd-global.cern.ch///store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/10000/08353B18-3D22-E611-A771-F01FAFD8EDA2.root'
    )
)

# Define output file name
import os
process.TFileService = cms.Service("TFileService",
     fileName = cms.string('cumulants_PbPb_2sub.root')
)


# __________________ Detector conditions _________________

# Configure the Global Tag
# Global tag contains information about detector geometry, calibration, alignement, ...
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load("TrackingTools/TransientTrack/TransientTrackBuilder_cfi")
process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')
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
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.defaultTrigSel = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.defaultTrigSel.HLTPaths = ['HLT_HIL1Centralityext30100MinimumumBiasHF*'] # for allphysics
process.defaultTrigSel.andOr = cms.bool(True)
process.defaultTrigSel.throw = cms.bool(False)

# Load HI event selection modules
process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
#process.load('Configuration.EventContent.EventContentHeavyIons_cff')

#Reject beam scraping events standard pp configuration
process.NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)

process.primaryVertexFilter.src = cms.InputTag("GMOVertex")
process.eventSelPbPb = cms.Sequence(process.hfCoincFilter3 * process.primaryVertexFilter)

# __________________ Analyzer _________________

# Load you analyzer with initial configuration
process.load("Analyzers.Cumulants.cumulants_cff")
process.anaSC23 = process.sub2AnalysisSC23.clone()
process.anaSC24 = process.sub2AnalysisSC24.clone()

process.p3 = cms.Path(
                     process.eventSelPbPb *    # events sel
                     process.defaultTrigSel *  # Select MB events
                     process.anaSC23)          # Run the analyzer

process.p4 = cms.Path(
                     process.eventSelPbPb *    # events sel
                     process.defaultTrigSel *  # Select MB events
                     process.anaSC24)          # Run the analyzer