import FWCore.ParameterSet.Config as cms

process = cms.Process("Cumulants")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch///store/hidata/HIRun2015/HIMinimumBias5/AOD/02May2016-v1/00000/002C1765-9B2E-E611-BA4B-F01FAFD5992D.root')
)
process.ak4CaloJets = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doOutputJets = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(True),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(10.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nSigmaPU = cms.double(1.0),
    puPtMin = cms.double(10),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("towerMaker"),
    srcPVs = cms.InputTag("offlinePrimaryVertices"),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.ak4CaloJetsForTrk = cms.EDProducer("FastjetJetProducer",
    Active_Area_Repeats = cms.int32(1),
    GhostArea = cms.double(0.01),
    Ghost_EtaMax = cms.double(5.0),
    Rho_EtaMax = cms.double(4.4),
    doAreaDiskApprox = cms.bool(False),
    doAreaFastjet = cms.bool(False),
    doOutputJets = cms.bool(True),
    doPUOffsetCorr = cms.bool(False),
    doPVCorrection = cms.bool(True),
    doRhoFastjet = cms.bool(False),
    inputEMin = cms.double(0.0),
    inputEtMin = cms.double(0.3),
    jetAlgorithm = cms.string('AntiKt'),
    jetPtMin = cms.double(10.0),
    jetType = cms.string('CaloJet'),
    maxBadEcalCells = cms.uint32(9999999),
    maxBadHcalCells = cms.uint32(9999999),
    maxProblematicEcalCells = cms.uint32(9999999),
    maxProblematicHcalCells = cms.uint32(9999999),
    maxRecoveredEcalCells = cms.uint32(9999999),
    maxRecoveredHcalCells = cms.uint32(9999999),
    minSeed = cms.uint32(14327),
    nSigmaPU = cms.double(1.0),
    puPtMin = cms.double(10),
    rParam = cms.double(0.4),
    radiusPU = cms.double(0.5),
    src = cms.InputTag("caloTowerForTrk"),
    srcPVs = cms.InputTag("firstStepPrimaryVertices"),
    useDeterministicSeed = cms.bool(True),
    voronoiRfact = cms.double(-0.9)
)


process.caloTowerForTrk = cms.EDProducer("CaloTowersCreator",
    AllowMissingInputs = cms.bool(False),
    EBGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    EBSumThreshold = cms.double(0.2),
    EBThreshold = cms.double(0.07),
    EBWeight = cms.double(1.0),
    EBWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    EEGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    EESumThreshold = cms.double(0.45),
    EEThreshold = cms.double(0.3),
    EEWeight = cms.double(1.0),
    EEWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    EcalRecHitSeveritiesToBeExcluded = cms.vstring('kTime', 
        'kWeird', 
        'kBad'),
    EcalSeveritiesToBeUsedInBadTowers = cms.vstring(),
    EcutTower = cms.double(-1000.0),
    HBGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HBThreshold = cms.double(0.7),
    HBWeight = cms.double(1.0),
    HBWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HEDGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HEDThreshold = cms.double(0.8),
    HEDWeight = cms.double(1.0),
    HEDWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HESGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HESThreshold = cms.double(0.8),
    HESWeight = cms.double(1.0),
    HESWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HF1Grid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HF1Threshold = cms.double(0.5),
    HF1Weight = cms.double(1.0),
    HF1Weights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HF2Grid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HF2Threshold = cms.double(0.85),
    HF2Weight = cms.double(1.0),
    HF2Weights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HOGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HOThreshold0 = cms.double(1.1),
    HOThresholdMinus1 = cms.double(3.5),
    HOThresholdMinus2 = cms.double(3.5),
    HOThresholdPlus1 = cms.double(3.5),
    HOThresholdPlus2 = cms.double(3.5),
    HOWeight = cms.double(1.0),
    HOWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HcalAcceptSeverityLevel = cms.uint32(9),
    HcalAcceptSeverityLevelForRejectedHit = cms.uint32(9999),
    HcalThreshold = cms.double(-1000.0),
    MomConstrMethod = cms.int32(1),
    MomEBDepth = cms.double(0.3),
    MomEEDepth = cms.double(0.0),
    MomHBDepth = cms.double(0.2),
    MomHEDepth = cms.double(0.4),
    UseEcalRecoveredHits = cms.bool(False),
    UseEtEBTreshold = cms.bool(False),
    UseEtEETreshold = cms.bool(False),
    UseHO = cms.bool(True),
    UseHcalRecoveredHits = cms.bool(True),
    UseRejectedHitsOnly = cms.bool(False),
    UseRejectedRecoveredEcalHits = cms.bool(False),
    UseRejectedRecoveredHcalHits = cms.bool(True),
    UseSymEBTreshold = cms.bool(True),
    UseSymEETreshold = cms.bool(True),
    ecalInputs = cms.VInputTag(cms.InputTag("ecalRecHit","EcalRecHitsEB"), cms.InputTag("ecalRecHit","EcalRecHitsEE")),
    hbheInput = cms.InputTag("hbheprereco"),
    hfInput = cms.InputTag("hfreco"),
    hoInput = cms.InputTag("horeco")
)


process.calotowermaker = cms.EDProducer("CaloTowersCreator",
    AllowMissingInputs = cms.bool(False),
    EBGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    EBSumThreshold = cms.double(0.2),
    EBThreshold = cms.double(0.07),
    EBWeight = cms.double(1.0),
    EBWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    EEGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    EESumThreshold = cms.double(0.45),
    EEThreshold = cms.double(0.3),
    EEWeight = cms.double(1.0),
    EEWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    EcalRecHitSeveritiesToBeExcluded = cms.vstring('kTime', 
        'kWeird', 
        'kBad'),
    EcalSeveritiesToBeUsedInBadTowers = cms.vstring(),
    EcutTower = cms.double(-1000.0),
    HBGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HBThreshold = cms.double(0.7),
    HBWeight = cms.double(1.0),
    HBWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HEDGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HEDThreshold = cms.double(0.8),
    HEDWeight = cms.double(1.0),
    HEDWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HESGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HESThreshold = cms.double(0.8),
    HESWeight = cms.double(1.0),
    HESWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HF1Grid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HF1Threshold = cms.double(0.5),
    HF1Weight = cms.double(1.0),
    HF1Weights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HF2Grid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HF2Threshold = cms.double(0.85),
    HF2Weight = cms.double(1.0),
    HF2Weights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HOGrid = cms.vdouble(-1.0, 1.0, 10.0, 100.0, 1000.0),
    HOThreshold0 = cms.double(1.1),
    HOThresholdMinus1 = cms.double(3.5),
    HOThresholdMinus2 = cms.double(3.5),
    HOThresholdPlus1 = cms.double(3.5),
    HOThresholdPlus2 = cms.double(3.5),
    HOWeight = cms.double(1.0),
    HOWeights = cms.vdouble(1.0, 1.0, 1.0, 1.0, 1.0),
    HcalAcceptSeverityLevel = cms.uint32(9),
    HcalAcceptSeverityLevelForRejectedHit = cms.uint32(9999),
    HcalThreshold = cms.double(-1000.0),
    MomConstrMethod = cms.int32(1),
    MomEBDepth = cms.double(0.3),
    MomEEDepth = cms.double(0.0),
    MomHBDepth = cms.double(0.2),
    MomHEDepth = cms.double(0.4),
    UseEcalRecoveredHits = cms.bool(False),
    UseEtEBTreshold = cms.bool(False),
    UseEtEETreshold = cms.bool(False),
    UseHO = cms.bool(True),
    UseHcalRecoveredHits = cms.bool(True),
    UseRejectedHitsOnly = cms.bool(False),
    UseRejectedRecoveredEcalHits = cms.bool(False),
    UseRejectedRecoveredHcalHits = cms.bool(True),
    UseSymEBTreshold = cms.bool(True),
    UseSymEETreshold = cms.bool(True),
    ecalInputs = cms.VInputTag(cms.InputTag("ecalRecHit","EcalRecHitsEB"), cms.InputTag("ecalRecHit","EcalRecHitsEE")),
    hbheInput = cms.InputTag("hbhereco"),
    hfInput = cms.InputTag("hfreco"),
    hoInput = cms.InputTag("horeco")
)


process.candidateVertexArbitrator = cms.EDProducer("CandidateVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("candidateVertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("particleFlow")
)


process.candidateVertexArbitratorCtagL = cms.EDProducer("CandidateVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("candidateVertexMergerCtagL"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("particleFlow")
)


process.candidateVertexMerger = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveCandidateVertexFinder")
)


process.candidateVertexMergerCtagL = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveCandidateVertexFinderCtagL")
)


process.generalV0Candidates = cms.EDProducer("V0Producer",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    cosThetaXYCut = cms.double(0.9998),
    cosThetaXYZCut = cms.double(-2.0),
    doKShorts = cms.bool(True),
    doLambdas = cms.bool(True),
    innerHitPosCut = cms.double(4.0),
    kShortMassCut = cms.double(0.07),
    lambdaMassCut = cms.double(0.05),
    mPiPiCut = cms.double(0.6),
    tkChi2Cut = cms.double(10.0),
    tkDCACut = cms.double(2.0),
    tkIPSigXYCut = cms.double(2.0),
    tkIPSigZCut = cms.double(-1.0),
    tkNHitsCut = cms.int32(7),
    tkPtCut = cms.double(0.35),
    trackRecoAlgorithm = cms.InputTag("generalTracks"),
    useRefTracks = cms.bool(True),
    useVertex = cms.bool(False),
    vertexFitter = cms.bool(True),
    vertices = cms.InputTag("offlinePrimaryVertices"),
    vtxChi2Cut = cms.double(15.0),
    vtxDecaySigXYCut = cms.double(10.0),
    vtxDecaySigXYZCut = cms.double(-1.0)
)


process.inclusiveCandidateSecondaryVertices = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("candidateVertexArbitrator")
)


process.inclusiveCandidateSecondaryVerticesCtagL = cms.EDProducer("CandidateVertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("candidateVertexArbitratorCtagL")
)


process.inclusiveCandidateVertexFinder = cms.EDProducer("InclusiveCandidateVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        seedMax3DIPSignificance = cms.double(9999.0),
        seedMax3DIPValue = cms.double(9999.0),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    minHits = cms.uint32(8),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("particleFlow"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1.0),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveCandidateVertexFinderCtagL = cms.EDProducer("InclusiveCandidateVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(10),
        seedMax3DIPSignificance = cms.double(9999.0),
        seedMax3DIPValue = cms.double(9999.0),
        seedMin3DIPSignificance = cms.double(1.0),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    minHits = cms.uint32(8),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("particleFlow"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(1.25),
    vertexMinDLenSig = cms.double(0.25),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1.0),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.inclusiveSecondaryVertices = cms.EDProducer("VertexMerger",
    maxFraction = cms.double(0.2),
    minSignificance = cms.double(10.0),
    secondaryVertices = cms.InputTag("trackVertexArbitrator")
)


process.inclusiveVertexFinder = cms.EDProducer("InclusiveVertexFinder",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    clusterizer = cms.PSet(
        clusterMaxDistance = cms.double(0.05),
        clusterMaxSignificance = cms.double(4.5),
        clusterMinAngleCosine = cms.double(0.5),
        distanceRatio = cms.double(20),
        seedMax3DIPSignificance = cms.double(9999.0),
        seedMax3DIPValue = cms.double(9999.0),
        seedMin3DIPSignificance = cms.double(1.2),
        seedMin3DIPValue = cms.double(0.005)
    ),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    maxNTracks = cms.uint32(30),
    maximumLongitudinalImpactParameter = cms.double(0.3),
    minHits = cms.uint32(8),
    minPt = cms.double(0.8),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    useDirectVertexFitter = cms.bool(True),
    useVertexReco = cms.bool(True),
    vertexMinAngleCosine = cms.double(0.95),
    vertexMinDLen2DSig = cms.double(2.5),
    vertexMinDLenSig = cms.double(0.5),
    vertexReco = cms.PSet(
        finder = cms.string('avr'),
        primcut = cms.double(1.0),
        seccut = cms.double(3),
        smoothing = cms.bool(True)
    )
)


process.myVertexSequence = cms.EDProducer("PrimaryVertexProducer",
    TkClusParameters = cms.PSet(
        TkGapClusParameters = cms.PSet(
            zSeparation = cms.double(1.0)
        ),
        algorithm = cms.string('gap')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(3.0),
        maxNormalizedChi2 = cms.double(20.0),
        minPixelLayersWithHits = cms.int32(2),
        minPt = cms.double(0.0),
        minSiliconLayersWithHits = cms.int32(5),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("generalTracks"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    verbose = cms.untracked.bool(False),
    vertexCollections = cms.VPSet(cms.PSet(
        algorithm = cms.string('AdaptiveVertexFitter'),
        label = cms.string(''),
        maxDistanceToBeam = cms.double(1.0),
        minNdof = cms.double(0.0),
        useBeamConstraint = cms.bool(False)
    ), 
        cms.PSet(
            algorithm = cms.string('AdaptiveVertexFitter'),
            label = cms.string('WithBS'),
            maxDistanceToBeam = cms.double(1.0),
            minNdof = cms.double(2.0),
            useBeamConstraint = cms.bool(True)
        ))
)


process.offlinePrimaryVertices = cms.EDProducer("RecoChargedRefCandidatePrimaryVertexSorter",
    assignment = cms.PSet(
        maxDistanceToJetAxis = cms.double(0.07),
        maxDxyForJetAxisAssigment = cms.double(0.1),
        maxDxyForNotReconstructedPrimary = cms.double(0.01),
        maxDxySigForNotReconstructedPrimary = cms.double(2),
        maxDzForJetAxisAssigment = cms.double(0.1),
        maxDzForPrimaryAssignment = cms.double(0.03),
        maxDzSigForPrimaryAssignment = cms.double(5.0),
        maxJetDeltaR = cms.double(0.5),
        minJetPt = cms.double(25)
    ),
    jets = cms.InputTag("ak4CaloJetsForTrk"),
    particles = cms.InputTag("trackRefsForJetsBeforeSorting"),
    produceAssociationToOriginalVertices = cms.bool(False),
    produceNoPileUpCollection = cms.bool(False),
    producePileUpCollection = cms.bool(False),
    produceSortedVertices = cms.bool(True),
    qualityForPrimary = cms.int32(3),
    sorting = cms.PSet(

    ),
    usePVMET = cms.bool(True),
    vertices = cms.InputTag("unsortedOfflinePrimaryVertices")
)


process.offlinePrimaryVerticesWithBS = cms.EDProducer("RecoChargedRefCandidatePrimaryVertexSorter",
    assignment = cms.PSet(
        maxDistanceToJetAxis = cms.double(0.07),
        maxDxyForJetAxisAssigment = cms.double(0.1),
        maxDxyForNotReconstructedPrimary = cms.double(0.01),
        maxDxySigForNotReconstructedPrimary = cms.double(2),
        maxDzForJetAxisAssigment = cms.double(0.1),
        maxDzForPrimaryAssignment = cms.double(0.03),
        maxDzSigForPrimaryAssignment = cms.double(5.0),
        maxJetDeltaR = cms.double(0.5),
        minJetPt = cms.double(25)
    ),
    jets = cms.InputTag("ak4CaloJetsForTrk"),
    particles = cms.InputTag("trackRefsForJetsBeforeSorting"),
    produceAssociationToOriginalVertices = cms.bool(False),
    produceNoPileUpCollection = cms.bool(False),
    producePileUpCollection = cms.bool(False),
    produceSortedVertices = cms.bool(True),
    qualityForPrimary = cms.int32(3),
    sorting = cms.PSet(

    ),
    usePVMET = cms.bool(True),
    vertices = cms.InputTag("unsortedOfflinePrimaryVertices","WithBS")
)


process.siPixelRecHits = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("siPixelClusters")
)


process.siPixelRecHitsPreSplitting = cms.EDProducer("SiPixelRecHitConverter",
    CPE = cms.string('PixelCPEGeneric'),
    VerboseLevel = cms.untracked.int32(0),
    src = cms.InputTag("siPixelClustersPreSplitting")
)


process.sortedPrimaryVertices = cms.EDProducer("RecoChargedRefCandidatePrimaryVertexSorter",
    assignment = cms.PSet(
        maxDistanceToJetAxis = cms.double(0.07),
        maxDxyForJetAxisAssigment = cms.double(0.1),
        maxDxyForNotReconstructedPrimary = cms.double(0.01),
        maxDxySigForNotReconstructedPrimary = cms.double(2),
        maxDzForJetAxisAssigment = cms.double(0.1),
        maxDzForPrimaryAssignment = cms.double(0.03),
        maxDzSigForPrimaryAssignment = cms.double(5.0),
        maxJetDeltaR = cms.double(0.5),
        minJetPt = cms.double(25)
    ),
    jets = cms.InputTag("ak4CaloJetsForTrk"),
    particles = cms.InputTag("trackRefsForJets"),
    produceAssociationToOriginalVertices = cms.bool(False),
    produceNoPileUpCollection = cms.bool(False),
    producePileUpCollection = cms.bool(False),
    produceSortedVertices = cms.bool(True),
    qualityForPrimary = cms.int32(3),
    sorting = cms.PSet(

    ),
    usePVMET = cms.bool(True),
    vertices = cms.InputTag("offlinePrimaryVertices")
)


process.towersAboveThreshold = cms.EDProducer("CaloTowerCandidateCreator",
    minimumE = cms.double(3.0),
    minimumEt = cms.double(0.0),
    src = cms.InputTag("towerMaker"),
    verbose = cms.untracked.int32(0)
)


process.trackRefsForJets = cms.EDProducer("ChargedRefCandidateProducer",
    particleType = cms.string('pi+'),
    src = cms.InputTag("trackWithVertexRefSelector")
)


process.trackRefsForJetsBeforeSorting = cms.EDProducer("ChargedRefCandidateProducer",
    particleType = cms.string('pi+'),
    src = cms.InputTag("trackWithVertexRefSelectorBeforeSorting")
)


process.trackVertexArbitrator = cms.EDProducer("TrackVertexArbitrator",
    beamSpot = cms.InputTag("offlineBeamSpot"),
    dLenFraction = cms.double(0.333),
    dRCut = cms.double(0.4),
    distCut = cms.double(0.04),
    fitterRatio = cms.double(0.25),
    fitterSigmacut = cms.double(3),
    fitterTini = cms.double(256),
    primaryVertices = cms.InputTag("offlinePrimaryVertices"),
    secondaryVertices = cms.InputTag("vertexMerger"),
    sigCut = cms.double(5),
    trackMinLayers = cms.int32(4),
    trackMinPixels = cms.int32(1),
    trackMinPt = cms.double(0.4),
    tracks = cms.InputTag("generalTracks")
)


process.unsortedOfflinePrimaryVertices = cms.EDProducer("PrimaryVertexProducer",
    TkClusParameters = cms.PSet(
        TkDAClusParameters = cms.PSet(
            Tmin = cms.double(4.0),
            coolingFactor = cms.double(0.6),
            d0CutOff = cms.double(3.0),
            dzCutOff = cms.double(4.0),
            vertexSize = cms.double(0.01)
        ),
        algorithm = cms.string('DA_vect')
    ),
    TkFilterParameters = cms.PSet(
        algorithm = cms.string('filter'),
        maxD0Significance = cms.double(5.0),
        maxNormalizedChi2 = cms.double(20.0),
        minPixelLayersWithHits = cms.int32(2),
        minPt = cms.double(0.0),
        minSiliconLayersWithHits = cms.int32(5),
        trackQuality = cms.string('any')
    ),
    TrackLabel = cms.InputTag("generalTracks"),
    beamSpotLabel = cms.InputTag("offlineBeamSpot"),
    verbose = cms.untracked.bool(False),
    vertexCollections = cms.VPSet(cms.PSet(
        algorithm = cms.string('AdaptiveVertexFitter'),
        label = cms.string(''),
        maxDistanceToBeam = cms.double(1.0),
        minNdof = cms.double(0.0),
        useBeamConstraint = cms.bool(False)
    ), 
        cms.PSet(
            algorithm = cms.string('AdaptiveVertexFitter'),
            label = cms.string('WithBS'),
            maxDistanceToBeam = cms.double(1.0),
            minNdof = cms.double(2.0),
            useBeamConstraint = cms.bool(True)
        ))
)


process.vertexMerger = cms.EDProducer("VertexMerger",
    maxFraction = cms.double(0.7),
    minSignificance = cms.double(2),
    secondaryVertices = cms.InputTag("inclusiveVertexFinder")
)


process.NoScraping = cms.EDFilter("FilterOutScraping",
    applyfilter = cms.untracked.bool(True),
    debugOn = cms.untracked.bool(False),
    numtrack = cms.untracked.uint32(10),
    thresh = cms.untracked.double(0.25)
)


process.defaultTrigSel = cms.EDFilter("HLTHighLevel",
    HLTPaths = cms.vstring('HLT_HIL1Centralityext30100MinimumumBiasHF*'),
    TriggerResultsTag = cms.InputTag("TriggerResults","","HLT"),
    andOr = cms.bool(True),
    eventSetupPathsKey = cms.string(''),
    throw = cms.bool(False)
)


process.hfNegFilter = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegFilter3 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfNegTowers")
)


process.hfNegTowers = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(-3.0),
    etaMin = cms.double(-6.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThreshold")
)


process.hfPosFilter = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(1),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosFilter3 = cms.EDFilter("CandCountFilter",
    minNumber = cms.uint32(3),
    src = cms.InputTag("hfPosTowers")
)


process.hfPosTowers = cms.EDFilter("EtaPtMinCandSelector",
    etaMax = cms.double(6.0),
    etaMin = cms.double(3.0),
    ptMin = cms.double(0),
    src = cms.InputTag("towersAboveThreshold")
)


process.hltLevel1GTSeed = cms.EDFilter("HLTLevel1GTSeed",
    L1CollectionsTag = cms.InputTag("l1extraParticles"),
    L1GtObjectMapTag = cms.InputTag("l1GtObjectMap"),
    L1GtReadoutRecordTag = cms.InputTag("gtDigis"),
    L1MuonCollectionTag = cms.InputTag("l1extraParticles"),
    L1NrBxInEvent = cms.int32(3),
    L1SeedsLogicalExpression = cms.string(''),
    L1TechTriggerSeeding = cms.bool(False),
    L1UseAliasesForSeeding = cms.bool(True),
    L1UseL1TriggerObjectMaps = cms.bool(True),
    saveTags = cms.bool(False)
)


process.hltPixelClusterShapeFilter = cms.EDFilter("HLTPixelClusterShapeFilter",
    clusterPars = cms.vdouble(0, 0.0045),
    clusterTrunc = cms.double(2),
    inputTag = cms.InputTag("siPixelRecHits"),
    maxZ = cms.double(20.05),
    minZ = cms.double(-20),
    nhitsTrunc = cms.int32(150),
    saveTags = cms.bool(False),
    zStep = cms.double(0.2)
)


process.noBSChalo = cms.EDFilter("HLTLevel1GTSeed",
    L1CollectionsTag = cms.InputTag("l1extraParticles"),
    L1GtObjectMapTag = cms.InputTag("l1GtObjectMap"),
    L1GtReadoutRecordTag = cms.InputTag("gtDigis"),
    L1MuonCollectionTag = cms.InputTag("l1extraParticles"),
    L1NrBxInEvent = cms.int32(3),
    L1SeedsLogicalExpression = cms.string('NOT (36 OR 37 OR 38 OR 39)'),
    L1TechTriggerSeeding = cms.bool(True),
    L1UseAliasesForSeeding = cms.bool(True),
    L1UseL1TriggerObjectMaps = cms.bool(True),
    saveTags = cms.bool(False)
)


process.primaryVertexFilter = cms.EDFilter("VertexSelector",
    cut = cms.string('!isFake && abs(z) <= 25 && position.Rho <= 2 && tracksSize >= 2'),
    filter = cms.bool(True),
    src = cms.InputTag("myVertexSequence")
)


process.trackWithVertexRefSelector = cms.EDFilter("TrackWithVertexRefSelector",
    copyExtras = cms.untracked.bool(False),
    copyTrajectories = cms.untracked.bool(False),
    d0Max = cms.double(999.0),
    dzMax = cms.double(999.0),
    etaMax = cms.double(5.0),
    etaMin = cms.double(0.0),
    nVertices = cms.uint32(0),
    normalizedChi2 = cms.double(999999.0),
    numberOfLostHits = cms.uint32(999),
    numberOfValidHits = cms.uint32(0),
    numberOfValidPixelHits = cms.uint32(0),
    ptErrorCut = cms.double(0.2),
    ptMax = cms.double(500.0),
    ptMin = cms.double(0.3),
    quality = cms.string('highPurity'),
    rhoVtx = cms.double(0.2),
    src = cms.InputTag("generalTracks"),
    useVtx = cms.bool(True),
    vertexTag = cms.InputTag("offlinePrimaryVertices"),
    vtxFallback = cms.bool(True),
    zetaVtx = cms.double(1.0)
)


process.trackWithVertexRefSelectorBeforeSorting = cms.EDFilter("TrackWithVertexRefSelector",
    copyExtras = cms.untracked.bool(False),
    copyTrajectories = cms.untracked.bool(False),
    d0Max = cms.double(999.0),
    dzMax = cms.double(999.0),
    etaMax = cms.double(5.0),
    etaMin = cms.double(0.0),
    nVertices = cms.uint32(0),
    normalizedChi2 = cms.double(999999.0),
    numberOfLostHits = cms.uint32(999),
    numberOfValidHits = cms.uint32(0),
    numberOfValidPixelHits = cms.uint32(0),
    ptErrorCut = cms.double(9e+99),
    ptMax = cms.double(9e+99),
    ptMin = cms.double(0.3),
    quality = cms.string('highPurity'),
    rhoVtx = cms.double(0.2),
    src = cms.InputTag("generalTracks"),
    useVtx = cms.bool(True),
    vertexTag = cms.InputTag("unsortedOfflinePrimaryVertices"),
    vtxFallback = cms.bool(True),
    zetaVtx = cms.double(1.0)
)


process.anaSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.anaSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.anaV2 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.anaV3 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.anaV4 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.defaultCumu = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.stdAnalysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 2.4, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, -2.4, 
        -2.4, -2.4, -2.4),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(1),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.stdAnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 2.4, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, -2.4, 
        -2.4, -2.4, -2.4),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(1),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.stdAnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 2.4, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, -2.4, 
        -2.4, -2.4, -2.4),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(1),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.stdV3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 2.4, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, -2.4, 
        -2.4, -2.4, -2.4),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(1),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.stdV4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 2.4, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, -2.4, 
        -2.4, -2.4, -2.4),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(1),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2AnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2AnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2Analysis_Pt10NEG = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(2),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 10000.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 10.0, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2Analysis_Pt10POS = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(2),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 10000.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 10.0),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2V3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2V4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, 0.0, 0.0, 0.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.0, 
        0.0, 0.0, 0.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap1Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-0.5, -0.5, -0.5, -0.5, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.5, 
        0.5, 0.5, 0.5),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap1AnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-0.5, -0.5, -0.5, -0.5, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.5, 
        0.5, 0.5, 0.5),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap1AnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-0.5, -0.5, -0.5, -0.5, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.5, 
        0.5, 0.5, 0.5),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap1V3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-0.5, -0.5, -0.5, -0.5, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.5, 
        0.5, 0.5, 0.5),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap1V4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-0.5, -0.5, -0.5, -0.5, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 0.5, 
        0.5, 0.5, 0.5),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap2Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-1.0, -1.0, -1.0, -1.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 1.0, 
        1.0, 1.0, 1.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap2AnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-1.0, -1.0, -1.0, -1.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 1.0, 
        1.0, 1.0, 1.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap2AnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-1.0, -1.0, -1.0, -1.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 1.0, 
        1.0, 1.0, 1.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap2V3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-1.0, -1.0, -1.0, -1.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 1.0, 
        1.0, 1.0, 1.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub2gap2V4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(-1.0, -1.0, -1.0, -1.0, 2.4, 
        2.4, 2.4, 2.4),
    etasubmin = cms.vdouble(-2.4, -2.4, -2.4, -2.4, 1.0, 
        1.0, 1.0, 1.0),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(2),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3AnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3AnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3Analysis_Pt10MID = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(2),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 10000.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 10.0, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3V3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub3V4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(2.4, 2.4, 2.4, 0.8, -0.8, 
        -0.8, -0.8, 0.8),
    etasubmin = cms.vdouble(0.8, 0.8, 0.8, -0.8, -2.4, 
        -2.4, -2.4, -0.8),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(3),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, -1.2, 0.0, -1.2, 1.2, 
        2.4, 1.2, 2.4),
    etasubmin = cms.vdouble(-1.2, -2.4, -1.2, -2.4, 0.0, 
        1.2, 0.0, 1.2),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 2, 2, 2),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(4),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub4AnalysisSC23 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, -1.2, 0.0, -1.2, 1.2, 
        2.4, 1.2, 2.4),
    etasubmin = cms.vdouble(-1.2, -2.4, -1.2, -2.4, 0.0, 
        1.2, 0.0, 1.2),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 3, 2, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(4),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub4AnalysisSC24 = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, -1.2, 0.0, -1.2, 1.2, 
        2.4, 1.2, 2.4),
    etasubmin = cms.vdouble(-1.2, -2.4, -1.2, -2.4, 0.0, 
        1.2, 0.0, 1.2),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(2, 4, 2, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(4),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub4V3Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, -1.2, 0.0, -1.2, 1.2, 
        2.4, 1.2, 2.4),
    etasubmin = cms.vdouble(-1.2, -2.4, -1.2, -2.4, 0.0, 
        1.2, 0.0, 1.2),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(3, 3, 3, 3),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(4),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.sub4V4Analysis = cms.EDAnalyzer("Cumulants",
    branchSave = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    centralitySrc = cms.InputTag("hiCentrality"),
    cweight = cms.untracked.bool(True),
    d0d0error = cms.untracked.double(3.0),
    d0d0errornoff = cms.untracked.double(3.0),
    dzdzerror = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    effmultbin = cms.untracked.vint32(0, 260, 400, 800, 1200, 
        10000),
    etamax = cms.untracked.double(2.4),
    etamin = cms.untracked.double(-2.4),
    etasubmax = cms.vdouble(0.0, -1.2, 0.0, -1.2, 1.2, 
        2.4, 1.2, 2.4),
    etasubmin = cms.vdouble(-1.2, -2.4, -1.2, -2.4, 0.0, 
        1.2, 0.0, 1.2),
    fname = cms.untracked.InputTag("Hydjet_ppReco_default.root"),
    harm = cms.untracked.vint32(4, 4, 4, 4),
    isBVselByMult = cms.untracked.bool(True),
    maxrho = cms.untracked.double(0.2),
    maxvz = cms.untracked.double(15.0),
    minvz = cms.untracked.double(-15.0),
    noffmax = cms.untracked.int32(10000),
    noffmin = cms.untracked.int32(0),
    nsubevt = cms.untracked.int32(4),
    pterrorpt = cms.untracked.double(0.1),
    pterrorptnoff = cms.untracked.double(0.1),
    ptmax = cms.untracked.double(3.0),
    ptmin = cms.untracked.double(0.3),
    ptnoffmax = cms.untracked.double(10000.0),
    ptnoffmin = cms.untracked.double(0.4),
    ptsubmax = cms.vdouble(3.0, 3.0, 3.0, 3.0, 3.0, 
        3.0, 3.0, 3.0),
    ptsubmin = cms.vdouble(0.3, 0.3, 0.3, 0.3, 0.3, 
        0.3, 0.3, 0.3),
    tracks = cms.InputTag("generalTracks"),
    vertex = cms.InputTag("offlinePrimaryVertices")
)


process.inclusiveCandidateVertexing = cms.Sequence(process.inclusiveCandidateVertexFinder+process.candidateVertexMerger+process.candidateVertexArbitrator+process.inclusiveCandidateSecondaryVertices)


process.caloJetsForTrk = cms.Sequence(process.caloTowerForTrk+process.ak4CaloJetsForTrk)


process.inclusiveCandidateVertexingCtagL = cms.Sequence(process.inclusiveCandidateVertexFinderCtagL+process.candidateVertexMergerCtagL+process.candidateVertexArbitratorCtagL+process.inclusiveCandidateSecondaryVerticesCtagL)


process.inclusiveVertexing = cms.Sequence(process.inclusiveVertexFinder+process.vertexMerger+process.trackVertexArbitrator+process.inclusiveSecondaryVertices)


process.hfCoincFilter = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter+process.hfNegFilter)


process.hfCoincFilter3 = cms.Sequence(process.towersAboveThreshold+process.hfPosTowers+process.hfNegTowers+process.hfPosFilter3+process.hfNegFilter3)


process.eventSelPbPb = cms.Sequence(process.myVertexSequence+process.hfCoincFilter3+process.primaryVertexFilter)


process.vertexreco = cms.Sequence(process.unsortedOfflinePrimaryVertices+process.trackWithVertexRefSelectorBeforeSorting+process.trackRefsForJetsBeforeSorting+process.caloJetsForTrk+process.offlinePrimaryVertices+process.offlinePrimaryVerticesWithBS+process.generalV0Candidates+process.inclusiveVertexing)


process.collisionEventSelection = cms.Sequence(process.noBSChalo+process.hfCoincFilter3+process.primaryVertexFilter+process.siPixelRecHits+process.hltPixelClusterShapeFilter)


process.p = cms.Path(process.eventSelPbPb+process.defaultTrigSel+process.anaV2)


process.p1 = cms.Path(process.eventSelPbPb+process.defaultTrigSel+process.anaV3)


process.p2 = cms.Path(process.eventSelPbPb+process.defaultTrigSel+process.anaV4)


process.p3 = cms.Path(process.eventSelPbPb+process.defaultTrigSel+process.anaSC23)


process.p4 = cms.Path(process.eventSelPbPb+process.defaultTrigSel+process.anaSC24)


process.MessageLogger = cms.Service("MessageLogger",
    FrameworkJobReport = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring('FwkJob', 
        'FwkReport', 
        'FwkSummary', 
        'Root_NoDictionary'),
    cerr = cms.untracked.PSet(
        FwkJob = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        FwkReport = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(10000)
        ),
        FwkSummary = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000),
            optionalPSet = cms.untracked.bool(True),
            reportEvery = cms.untracked.int32(1)
        ),
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        noTimeStamps = cms.untracked.bool(False),
        optionalPSet = cms.untracked.bool(True),
        threshold = cms.untracked.string('INFO')
    ),
    cerr_stats = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        output = cms.untracked.string('cerr'),
        threshold = cms.untracked.string('WARNING')
    ),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    debugModules = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    destinations = cms.untracked.vstring('warnings', 
        'errors', 
        'infos', 
        'debugs', 
        'cout', 
        'cerr'),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport'),
    infos = cms.untracked.PSet(
        Root_NoDictionary = cms.untracked.PSet(
            limit = cms.untracked.int32(0),
            optionalPSet = cms.untracked.bool(True)
        ),
        optionalPSet = cms.untracked.bool(True),
        placeholder = cms.untracked.bool(True)
    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    suppressDebug = cms.untracked.vstring(),
    suppressInfo = cms.untracked.vstring(),
    suppressWarning = cms.untracked.vstring(),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    )
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('cumulants_2sub.root')
)


process.Timing = cms.Service("Timing",
    summaryOnly = cms.untracked.bool(True),
    useJobReport = cms.untracked.bool(False)
)


process.CSCGeometryESModule = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    debugV = cms.untracked.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useDDD = cms.bool(True),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.CaloGeometryBuilder = cms.ESProducer("CaloGeometryBuilder",
    SelectedCalos = cms.vstring('HCAL', 
        'ZDC', 
        'CASTOR', 
        'EcalBarrel', 
        'EcalEndcap', 
        'EcalPreshower', 
        'TOWER')
)


process.CaloTopologyBuilder = cms.ESProducer("CaloTopologyBuilder")


process.CaloTowerHardcodeGeometryEP = cms.ESProducer("CaloTowerHardcodeGeometryEP")


process.CastorDbProducer = cms.ESProducer("CastorDbProducer")


process.CastorHardcodeGeometryEP = cms.ESProducer("CastorHardcodeGeometryEP")


process.DTGeometryESModule = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(True)
)


process.EcalBarrelGeometryEP = cms.ESProducer("EcalBarrelGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalElectronicsMappingBuilder = cms.ESProducer("EcalElectronicsMappingBuilder")


process.EcalEndcapGeometryEP = cms.ESProducer("EcalEndcapGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalLaserCorrectionService = cms.ESProducer("EcalLaserCorrectionService")


process.EcalPreshowerGeometryEP = cms.ESProducer("EcalPreshowerGeometryEP",
    applyAlignment = cms.bool(False)
)


process.EcalTrigTowerConstituentsMapBuilder = cms.ESProducer("EcalTrigTowerConstituentsMapBuilder",
    MapFile = cms.untracked.string('Geometry/EcalMapping/data/EndCap_TTMap.txt')
)


process.GlobalTrackingGeometryESProducer = cms.ESProducer("GlobalTrackingGeometryESProducer")


process.HcalHardcodeGeometryEP = cms.ESProducer("HcalHardcodeGeometryEP",
    HcalReLabel = cms.PSet(
        RelabelHits = cms.untracked.bool(False),
        RelabelRules = cms.untracked.PSet(
            CorrectPhi = cms.untracked.bool(False),
            Eta1 = cms.untracked.vint32(1, 2, 2, 2, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3),
            Eta16 = cms.untracked.vint32(1, 1, 2, 2, 2, 
                2, 2, 2, 2, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3),
            Eta17 = cms.untracked.vint32(1, 1, 2, 2, 3, 
                3, 3, 4, 4, 4, 
                4, 4, 5, 5, 5, 
                5, 5, 5, 5)
        )
    )
)


process.MuonDetLayerGeometryESProducer = cms.ESProducer("MuonDetLayerGeometryESProducer")


process.MuonNumberingInitialization = cms.ESProducer("MuonNumberingInitialization")


process.ParabolicParametrizedMagneticFieldProducer = cms.ESProducer("AutoParametrizedMagneticFieldProducer",
    label = cms.untracked.string('ParabolicMf'),
    valueOverride = cms.int32(-1),
    version = cms.string('Parabolic')
)


process.RPCGeometryESModule = cms.ESProducer("RPCGeometryESModule",
    compatibiltyWith11 = cms.untracked.bool(True),
    useDDD = cms.untracked.bool(True)
)


process.SiStripRecHitMatcherESProducer = cms.ESProducer("SiStripRecHitMatcherESProducer",
    ComponentName = cms.string('StandardMatcher'),
    NSigmaInside = cms.double(3.0),
    PreFilter = cms.bool(False)
)


process.StripCPEfromTrackAngleESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('StripCPEfromTrackAngle'),
    ComponentType = cms.string('StripCPEfromTrackAngle'),
    parameters = cms.PSet(
        mLC_P0 = cms.double(-0.326),
        mLC_P1 = cms.double(0.618),
        mLC_P2 = cms.double(0.3),
        mTEC_P0 = cms.double(-1.885),
        mTEC_P1 = cms.double(0.471),
        mTIB_P0 = cms.double(-0.742),
        mTIB_P1 = cms.double(0.202),
        mTID_P0 = cms.double(-1.427),
        mTID_P1 = cms.double(0.433),
        mTOB_P0 = cms.double(-1.026),
        mTOB_P1 = cms.double(0.253),
        maxChgOneMIP = cms.double(6000.0),
        useLegacyError = cms.bool(False)
    )
)


process.TrackerRecoGeometryESProducer = cms.ESProducer("TrackerRecoGeometryESProducer")


process.TransientTrackBuilderESProducer = cms.ESProducer("TransientTrackBuilderESProducer",
    ComponentName = cms.string('TransientTrackBuilder')
)


process.VolumeBasedMagneticFieldESProducer = cms.ESProducer("VolumeBasedMagneticFieldESProducerFromDB",
    debugBuilder = cms.untracked.bool(False),
    label = cms.untracked.string(''),
    valueOverride = cms.int32(-1)
)


process.ZdcHardcodeGeometryEP = cms.ESProducer("ZdcHardcodeGeometryEP")


process.fakeForIdealAlignment = cms.ESProducer("FakeAlignmentProducer",
    appendToDataLabel = cms.string('fakeForIdeal')
)


process.hcalTopologyIdeal = cms.ESProducer("HcalTopologyIdealEP",
    Exclude = cms.untracked.string(''),
    appendToDataLabel = cms.string(''),
    hcalTopologyConstants = cms.PSet(
        maxDepthHB = cms.int32(2),
        maxDepthHE = cms.int32(3),
        mode = cms.string('HcalTopologyMode::LHC')
    )
)


process.hcal_db_producer = cms.ESProducer("HcalDbProducer",
    dump = cms.untracked.vstring(''),
    file = cms.untracked.string('')
)


process.idealForDigiCSCGeometry = cms.ESProducer("CSCGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    debugV = cms.untracked.bool(False),
    useCentreTIOffsets = cms.bool(False),
    useDDD = cms.bool(True),
    useGangedStripsInME1a = cms.bool(True),
    useOnlyWiresInME1a = cms.bool(False),
    useRealWireGeometry = cms.bool(True)
)


process.idealForDigiDTGeometry = cms.ESProducer("DTGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(True)
)


process.idealForDigiTrackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string('fakeForIdeal'),
    appendToDataLabel = cms.string('idealForDigi'),
    applyAlignment = cms.bool(False),
    fromDDD = cms.bool(True)
)


process.l1GtTriggerMaskTechTrig = cms.ESProducer("L1GtTriggerMaskTechTrigTrivialProducer",
    TriggerMask = cms.vuint32(0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0, 0, 
        0, 0, 0, 0)
)


process.siPixelQualityESProducer = cms.ESProducer("SiPixelQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(cms.PSet(
        record = cms.string('SiPixelQualityFromDbRcd'),
        tag = cms.string('')
    ), 
        cms.PSet(
            record = cms.string('SiPixelDetVOffRcd'),
            tag = cms.string('')
        ))
)


process.siStripBackPlaneCorrectionDepESProducer = cms.ESProducer("SiStripBackPlaneCorrectionDepESProducer",
    BackPlaneCorrectionDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    BackPlaneCorrectionPeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripBackPlaneCorrectionRcd')
    ),
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    )
)


process.siStripGainESProducer = cms.ESProducer("SiStripGainESProducer",
    APVGain = cms.VPSet(cms.PSet(
        Label = cms.untracked.string(''),
        NormalizationFactor = cms.untracked.double(1.0),
        Record = cms.string('SiStripApvGainRcd')
    ), 
        cms.PSet(
            Label = cms.untracked.string(''),
            NormalizationFactor = cms.untracked.double(1.0),
            Record = cms.string('SiStripApvGain2Rcd')
        )),
    AutomaticNormalization = cms.bool(False),
    appendToDataLabel = cms.string(''),
    printDebug = cms.untracked.bool(False)
)


process.siStripLorentzAngleDepESProducer = cms.ESProducer("SiStripLorentzAngleDepESProducer",
    LatencyRecord = cms.PSet(
        label = cms.untracked.string(''),
        record = cms.string('SiStripLatencyRcd')
    ),
    LorentzAngleDeconvMode = cms.PSet(
        label = cms.untracked.string('deconvolution'),
        record = cms.string('SiStripLorentzAngleRcd')
    ),
    LorentzAnglePeakMode = cms.PSet(
        label = cms.untracked.string('peak'),
        record = cms.string('SiStripLorentzAngleRcd')
    )
)


process.siStripQualityESProducer = cms.ESProducer("SiStripQualityESProducer",
    ListOfRecordToMerge = cms.VPSet(cms.PSet(
        record = cms.string('SiStripDetVOffRcd'),
        tag = cms.string('')
    ), 
        cms.PSet(
            record = cms.string('SiStripDetCablingRcd'),
            tag = cms.string('')
        ), 
        cms.PSet(
            record = cms.string('RunInfoRcd'),
            tag = cms.string('')
        ), 
        cms.PSet(
            record = cms.string('SiStripBadChannelRcd'),
            tag = cms.string('')
        ), 
        cms.PSet(
            record = cms.string('SiStripBadFiberRcd'),
            tag = cms.string('')
        ), 
        cms.PSet(
            record = cms.string('SiStripBadModuleRcd'),
            tag = cms.string('')
        ), 
        cms.PSet(
            record = cms.string('SiStripBadStripRcd'),
            tag = cms.string('')
        )),
    PrintDebugOutput = cms.bool(False),
    ReduceGranularity = cms.bool(False),
    ThresholdForReducedGranularity = cms.double(0.3),
    UseEmptyRunInfo = cms.bool(False),
    appendToDataLabel = cms.string('')
)


process.sistripconn = cms.ESProducer("SiStripConnectivity")


process.stripCPEESProducer = cms.ESProducer("StripCPEESProducer",
    ComponentName = cms.string('stripCPE'),
    ComponentType = cms.string('SimpleStripCPE'),
    parameters = cms.PSet(

    )
)


process.trackerGeometry = cms.ESProducer("TrackerDigiGeometryESModule",
    alignmentsLabel = cms.string(''),
    appendToDataLabel = cms.string(''),
    applyAlignment = cms.bool(True),
    fromDDD = cms.bool(True)
)


process.trackerNumberingGeometry = cms.ESProducer("TrackerGeometricDetESModule",
    appendToDataLabel = cms.string(''),
    fromDDD = cms.bool(True)
)


process.trackerParameters = cms.ESProducer("TrackerParametersESModule",
    appendToDataLabel = cms.string('')
)


process.trackerTopology = cms.ESProducer("TrackerTopologyEP",
    appendToDataLabel = cms.string('')
)


process.GlobalTag = cms.ESSource("PoolDBESSource",
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        connectionRetrialPeriod = cms.untracked.int32(10),
        connectionRetrialTimeOut = cms.untracked.int32(60),
        connectionTimeOut = cms.untracked.int32(60),
        enableConnectionSharing = cms.untracked.bool(True),
        enablePoolAutomaticCleanUp = cms.untracked.bool(False),
        enableReadOnlySessionOnUpdateConnection = cms.untracked.bool(False),
        idleConnectionCleanupPeriod = cms.untracked.int32(10),
        messageLevel = cms.untracked.int32(0)
    ),
    connect = cms.string('frontier://FrontierProd/CMS_CONDITIONS'),
    globaltag = cms.string('75X_dataRun2_PromptHI_v3'),
    toGet = cms.VPSet()
)


process.HepPDTESSource = cms.ESSource("HepPDTESSource",
    pdtFileName = cms.FileInPath('SimGeneral/HepPDTESSource/data/pythiaparticle.tbl')
)


process.L1GtTriggerMaskTechTrigRcdSource = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('L1GtTriggerMaskTechTrigRcd')
)


process.XMLIdealGeometryESSource = cms.ESSource("XMLIdealGeometryESSource",
    geomXMLFiles = cms.vstring('Geometry/CMSCommonData/data/materials.xml', 
        'Geometry/CMSCommonData/data/rotations.xml', 
        'Geometry/CMSCommonData/data/normal/cmsextent.xml', 
        'Geometry/CMSCommonData/data/cms.xml', 
        'Geometry/CMSCommonData/data/cmsMother.xml', 
        'Geometry/CMSCommonData/data/cmsTracker.xml', 
        'Geometry/CMSCommonData/data/caloBase.xml', 
        'Geometry/CMSCommonData/data/cmsCalo.xml', 
        'Geometry/CMSCommonData/data/muonBase.xml', 
        'Geometry/CMSCommonData/data/cmsMuon.xml', 
        'Geometry/CMSCommonData/data/mgnt.xml', 
        'Geometry/CMSCommonData/data/beampipe.xml', 
        'Geometry/CMSCommonData/data/cmsBeam.xml', 
        'Geometry/CMSCommonData/data/muonMB.xml', 
        'Geometry/CMSCommonData/data/muonMagnet.xml', 
        'Geometry/TrackerCommonData/data/trackerParameters.xml', 
        'Geometry/TrackerCommonData/data/pixfwdMaterials.xml', 
        'Geometry/TrackerCommonData/data/pixfwdCommon.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq1x2.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq1x5.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x3.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x4.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPlaq2x5.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPanelBase.xml', 
        'Geometry/TrackerCommonData/data/pixfwdPanel.xml', 
        'Geometry/TrackerCommonData/data/pixfwdBlade.xml', 
        'Geometry/TrackerCommonData/data/pixfwdNipple.xml', 
        'Geometry/TrackerCommonData/data/pixfwdDisk.xml', 
        'Geometry/TrackerCommonData/data/pixfwdCylinder.xml', 
        'Geometry/TrackerCommonData/data/pixfwd.xml', 
        'Geometry/TrackerCommonData/data/pixbarmaterial.xml', 
        'Geometry/TrackerCommonData/data/pixbarladder.xml', 
        'Geometry/TrackerCommonData/data/pixbarladderfull.xml', 
        'Geometry/TrackerCommonData/data/pixbarladderhalf.xml', 
        'Geometry/TrackerCommonData/data/pixbarlayer.xml', 
        'Geometry/TrackerCommonData/data/pixbarlayer0.xml', 
        'Geometry/TrackerCommonData/data/pixbarlayer1.xml', 
        'Geometry/TrackerCommonData/data/pixbarlayer2.xml', 
        'Geometry/TrackerCommonData/data/pixbar.xml', 
        'Geometry/TrackerCommonData/data/tibtidcommonmaterial.xml', 
        'Geometry/TrackerCommonData/data/tibmaterial.xml', 
        'Geometry/TrackerCommonData/data/tibmodpar.xml', 
        'Geometry/TrackerCommonData/data/tibmodule0.xml', 
        'Geometry/TrackerCommonData/data/tibmodule0a.xml', 
        'Geometry/TrackerCommonData/data/tibmodule0b.xml', 
        'Geometry/TrackerCommonData/data/tibmodule2.xml', 
        'Geometry/TrackerCommonData/data/tibstringpar.xml', 
        'Geometry/TrackerCommonData/data/tibstring0ll.xml', 
        'Geometry/TrackerCommonData/data/tibstring0lr.xml', 
        'Geometry/TrackerCommonData/data/tibstring0ul.xml', 
        'Geometry/TrackerCommonData/data/tibstring0ur.xml', 
        'Geometry/TrackerCommonData/data/tibstring0.xml', 
        'Geometry/TrackerCommonData/data/tibstring1ll.xml', 
        'Geometry/TrackerCommonData/data/tibstring1lr.xml', 
        'Geometry/TrackerCommonData/data/tibstring1ul.xml', 
        'Geometry/TrackerCommonData/data/tibstring1ur.xml', 
        'Geometry/TrackerCommonData/data/tibstring1.xml', 
        'Geometry/TrackerCommonData/data/tibstring2ll.xml', 
        'Geometry/TrackerCommonData/data/tibstring2lr.xml', 
        'Geometry/TrackerCommonData/data/tibstring2ul.xml', 
        'Geometry/TrackerCommonData/data/tibstring2ur.xml', 
        'Geometry/TrackerCommonData/data/tibstring2.xml', 
        'Geometry/TrackerCommonData/data/tibstring3ll.xml', 
        'Geometry/TrackerCommonData/data/tibstring3lr.xml', 
        'Geometry/TrackerCommonData/data/tibstring3ul.xml', 
        'Geometry/TrackerCommonData/data/tibstring3ur.xml', 
        'Geometry/TrackerCommonData/data/tibstring3.xml', 
        'Geometry/TrackerCommonData/data/tiblayerpar.xml', 
        'Geometry/TrackerCommonData/data/tiblayer0.xml', 
        'Geometry/TrackerCommonData/data/tiblayer1.xml', 
        'Geometry/TrackerCommonData/data/tiblayer2.xml', 
        'Geometry/TrackerCommonData/data/tiblayer3.xml', 
        'Geometry/TrackerCommonData/data/tib.xml', 
        'Geometry/TrackerCommonData/data/tidmaterial.xml', 
        'Geometry/TrackerCommonData/data/tidmodpar.xml', 
        'Geometry/TrackerCommonData/data/tidmodule0.xml', 
        'Geometry/TrackerCommonData/data/tidmodule0r.xml', 
        'Geometry/TrackerCommonData/data/tidmodule0l.xml', 
        'Geometry/TrackerCommonData/data/tidmodule1.xml', 
        'Geometry/TrackerCommonData/data/tidmodule1r.xml', 
        'Geometry/TrackerCommonData/data/tidmodule1l.xml', 
        'Geometry/TrackerCommonData/data/tidmodule2.xml', 
        'Geometry/TrackerCommonData/data/tidringpar.xml', 
        'Geometry/TrackerCommonData/data/tidring0.xml', 
        'Geometry/TrackerCommonData/data/tidring0f.xml', 
        'Geometry/TrackerCommonData/data/tidring0b.xml', 
        'Geometry/TrackerCommonData/data/tidring1.xml', 
        'Geometry/TrackerCommonData/data/tidring1f.xml', 
        'Geometry/TrackerCommonData/data/tidring1b.xml', 
        'Geometry/TrackerCommonData/data/tidring2.xml', 
        'Geometry/TrackerCommonData/data/tid.xml', 
        'Geometry/TrackerCommonData/data/tidf.xml', 
        'Geometry/TrackerCommonData/data/tidb.xml', 
        'Geometry/TrackerCommonData/data/tibtidservices.xml', 
        'Geometry/TrackerCommonData/data/tibtidservicesf.xml', 
        'Geometry/TrackerCommonData/data/tibtidservicesb.xml', 
        'Geometry/TrackerCommonData/data/tobmaterial.xml', 
        'Geometry/TrackerCommonData/data/tobmodpar.xml', 
        'Geometry/TrackerCommonData/data/tobmodule0.xml', 
        'Geometry/TrackerCommonData/data/tobmodule2.xml', 
        'Geometry/TrackerCommonData/data/tobmodule4.xml', 
        'Geometry/TrackerCommonData/data/tobrodpar.xml', 
        'Geometry/TrackerCommonData/data/tobrod0c.xml', 
        'Geometry/TrackerCommonData/data/tobrod0l.xml', 
        'Geometry/TrackerCommonData/data/tobrod0h.xml', 
        'Geometry/TrackerCommonData/data/tobrod0.xml', 
        'Geometry/TrackerCommonData/data/tobrod1l.xml', 
        'Geometry/TrackerCommonData/data/tobrod1h.xml', 
        'Geometry/TrackerCommonData/data/tobrod1.xml', 
        'Geometry/TrackerCommonData/data/tobrod2c.xml', 
        'Geometry/TrackerCommonData/data/tobrod2l.xml', 
        'Geometry/TrackerCommonData/data/tobrod2h.xml', 
        'Geometry/TrackerCommonData/data/tobrod2.xml', 
        'Geometry/TrackerCommonData/data/tobrod3l.xml', 
        'Geometry/TrackerCommonData/data/tobrod3h.xml', 
        'Geometry/TrackerCommonData/data/tobrod3.xml', 
        'Geometry/TrackerCommonData/data/tobrod4c.xml', 
        'Geometry/TrackerCommonData/data/tobrod4l.xml', 
        'Geometry/TrackerCommonData/data/tobrod4h.xml', 
        'Geometry/TrackerCommonData/data/tobrod4.xml', 
        'Geometry/TrackerCommonData/data/tobrod5l.xml', 
        'Geometry/TrackerCommonData/data/tobrod5h.xml', 
        'Geometry/TrackerCommonData/data/tobrod5.xml', 
        'Geometry/TrackerCommonData/data/tob.xml', 
        'Geometry/TrackerCommonData/data/tecmaterial.xml', 
        'Geometry/TrackerCommonData/data/tecmodpar.xml', 
        'Geometry/TrackerCommonData/data/tecmodule0.xml', 
        'Geometry/TrackerCommonData/data/tecmodule0r.xml', 
        'Geometry/TrackerCommonData/data/tecmodule0s.xml', 
        'Geometry/TrackerCommonData/data/tecmodule1.xml', 
        'Geometry/TrackerCommonData/data/tecmodule1r.xml', 
        'Geometry/TrackerCommonData/data/tecmodule1s.xml', 
        'Geometry/TrackerCommonData/data/tecmodule2.xml', 
        'Geometry/TrackerCommonData/data/tecmodule3.xml', 
        'Geometry/TrackerCommonData/data/tecmodule4.xml', 
        'Geometry/TrackerCommonData/data/tecmodule4r.xml', 
        'Geometry/TrackerCommonData/data/tecmodule4s.xml', 
        'Geometry/TrackerCommonData/data/tecmodule5.xml', 
        'Geometry/TrackerCommonData/data/tecmodule6.xml', 
        'Geometry/TrackerCommonData/data/tecpetpar.xml', 
        'Geometry/TrackerCommonData/data/tecring0.xml', 
        'Geometry/TrackerCommonData/data/tecring1.xml', 
        'Geometry/TrackerCommonData/data/tecring2.xml', 
        'Geometry/TrackerCommonData/data/tecring3.xml', 
        'Geometry/TrackerCommonData/data/tecring4.xml', 
        'Geometry/TrackerCommonData/data/tecring5.xml', 
        'Geometry/TrackerCommonData/data/tecring6.xml', 
        'Geometry/TrackerCommonData/data/tecring0f.xml', 
        'Geometry/TrackerCommonData/data/tecring1f.xml', 
        'Geometry/TrackerCommonData/data/tecring2f.xml', 
        'Geometry/TrackerCommonData/data/tecring3f.xml', 
        'Geometry/TrackerCommonData/data/tecring4f.xml', 
        'Geometry/TrackerCommonData/data/tecring5f.xml', 
        'Geometry/TrackerCommonData/data/tecring6f.xml', 
        'Geometry/TrackerCommonData/data/tecring0b.xml', 
        'Geometry/TrackerCommonData/data/tecring1b.xml', 
        'Geometry/TrackerCommonData/data/tecring2b.xml', 
        'Geometry/TrackerCommonData/data/tecring3b.xml', 
        'Geometry/TrackerCommonData/data/tecring4b.xml', 
        'Geometry/TrackerCommonData/data/tecring5b.xml', 
        'Geometry/TrackerCommonData/data/tecring6b.xml', 
        'Geometry/TrackerCommonData/data/tecpetalf.xml', 
        'Geometry/TrackerCommonData/data/tecpetalb.xml', 
        'Geometry/TrackerCommonData/data/tecpetal0.xml', 
        'Geometry/TrackerCommonData/data/tecpetal0f.xml', 
        'Geometry/TrackerCommonData/data/tecpetal0b.xml', 
        'Geometry/TrackerCommonData/data/tecpetal3.xml', 
        'Geometry/TrackerCommonData/data/tecpetal3f.xml', 
        'Geometry/TrackerCommonData/data/tecpetal3b.xml', 
        'Geometry/TrackerCommonData/data/tecpetal6f.xml', 
        'Geometry/TrackerCommonData/data/tecpetal6b.xml', 
        'Geometry/TrackerCommonData/data/tecpetal8f.xml', 
        'Geometry/TrackerCommonData/data/tecpetal8b.xml', 
        'Geometry/TrackerCommonData/data/tecwheel.xml', 
        'Geometry/TrackerCommonData/data/tecwheela.xml', 
        'Geometry/TrackerCommonData/data/tecwheelb.xml', 
        'Geometry/TrackerCommonData/data/tecwheelc.xml', 
        'Geometry/TrackerCommonData/data/tecwheeld.xml', 
        'Geometry/TrackerCommonData/data/tecwheel6.xml', 
        'Geometry/TrackerCommonData/data/tecservices.xml', 
        'Geometry/TrackerCommonData/data/tecbackplate.xml', 
        'Geometry/TrackerCommonData/data/tec.xml', 
        'Geometry/TrackerCommonData/data/trackermaterial.xml', 
        'Geometry/TrackerCommonData/data/tracker.xml', 
        'Geometry/TrackerCommonData/data/trackerpixbar.xml', 
        'Geometry/TrackerCommonData/data/trackerpixfwd.xml', 
        'Geometry/TrackerCommonData/data/trackertibtidservices.xml', 
        'Geometry/TrackerCommonData/data/trackertib.xml', 
        'Geometry/TrackerCommonData/data/trackertid.xml', 
        'Geometry/TrackerCommonData/data/trackertob.xml', 
        'Geometry/TrackerCommonData/data/trackertec.xml', 
        'Geometry/TrackerCommonData/data/trackerbulkhead.xml', 
        'Geometry/TrackerCommonData/data/trackerother.xml', 
        'Geometry/EcalCommonData/data/eregalgo.xml', 
        'Geometry/EcalCommonData/data/ebalgo.xml', 
        'Geometry/EcalCommonData/data/ebcon.xml', 
        'Geometry/EcalCommonData/data/ebrot.xml', 
        'Geometry/EcalCommonData/data/eecon.xml', 
        'Geometry/EcalCommonData/data/eefixed.xml', 
        'Geometry/EcalCommonData/data/eehier.xml', 
        'Geometry/EcalCommonData/data/eealgo.xml', 
        'Geometry/EcalCommonData/data/escon.xml', 
        'Geometry/EcalCommonData/data/esalgo.xml', 
        'Geometry/EcalCommonData/data/eeF.xml', 
        'Geometry/EcalCommonData/data/eeB.xml', 
        'Geometry/HcalCommonData/data/hcalrotations.xml', 
        'Geometry/HcalCommonData/data/hcalalgo.xml', 
        'Geometry/HcalCommonData/data/hcalbarrelalgo.xml', 
        'Geometry/HcalCommonData/data/hcalendcapalgo.xml', 
        'Geometry/HcalCommonData/data/hcalouteralgo.xml', 
        'Geometry/HcalCommonData/data/hcalforwardalgo.xml', 
        'Geometry/HcalCommonData/data/average/hcalforwardmaterial.xml', 
        'Geometry/HcalCommonData/data/Phase0/hcalSimNumbering.xml', 
        'Geometry/HcalCommonData/data/Phase0/hcalRecNumbering.xml', 
        'Geometry/MuonCommonData/data/mbCommon.xml', 
        'Geometry/MuonCommonData/data/mb1.xml', 
        'Geometry/MuonCommonData/data/mb2.xml', 
        'Geometry/MuonCommonData/data/mb3.xml', 
        'Geometry/MuonCommonData/data/mb4.xml', 
        'Geometry/MuonCommonData/data/muonYoke.xml', 
        'Geometry/MuonCommonData/data/mf.xml', 
        'Geometry/ForwardCommonData/data/forward.xml', 
        'Geometry/ForwardCommonData/data/bundle/forwardshield.xml', 
        'Geometry/ForwardCommonData/data/brmrotations.xml', 
        'Geometry/ForwardCommonData/data/brm.xml', 
        'Geometry/ForwardCommonData/data/totemMaterials.xml', 
        'Geometry/ForwardCommonData/data/totemRotations.xml', 
        'Geometry/ForwardCommonData/data/totemt1.xml', 
        'Geometry/ForwardCommonData/data/totemt2.xml', 
        'Geometry/ForwardCommonData/data/ionpump.xml', 
        'Geometry/MuonCommonData/data/muonNumbering.xml', 
        'Geometry/TrackerCommonData/data/trackerStructureTopology.xml', 
        'Geometry/TrackerSimData/data/trackersens.xml', 
        'Geometry/TrackerRecoData/data/trackerRecoMaterial.xml', 
        'Geometry/EcalSimData/data/ecalsens.xml', 
        'Geometry/HcalCommonData/data/hcalsenspmf.xml', 
        'Geometry/HcalSimData/data/hf.xml', 
        'Geometry/HcalSimData/data/hfpmt.xml', 
        'Geometry/HcalSimData/data/hffibrebundle.xml', 
        'Geometry/HcalSimData/data/CaloUtil.xml', 
        'Geometry/MuonSimData/data/muonSens.xml', 
        'Geometry/DTGeometryBuilder/data/dtSpecsFilter.xml', 
        'Geometry/CSCGeometryBuilder/data/cscSpecsFilter.xml', 
        'Geometry/CSCGeometryBuilder/data/cscSpecs.xml', 
        'Geometry/RPCGeometryBuilder/data/RPCSpecs.xml', 
        'Geometry/ForwardCommonData/data/brmsens.xml', 
        'Geometry/HcalSimData/data/HcalProdCuts.xml', 
        'Geometry/EcalSimData/data/EcalProdCuts.xml', 
        'Geometry/EcalSimData/data/ESProdCuts.xml', 
        'Geometry/TrackerSimData/data/trackerProdCuts.xml', 
        'Geometry/TrackerSimData/data/trackerProdCutsBEAM.xml', 
        'Geometry/MuonSimData/data/muonProdCuts.xml', 
        'Geometry/ForwardSimData/data/ForwardShieldProdCuts.xml', 
        'Geometry/CMSCommonData/data/FieldParameters.xml'),
    rootNodeName = cms.string('cms:OCMS')
)


process.eegeom = cms.ESSource("EmptyESSource",
    firstValid = cms.vuint32(1),
    iovIsRunNotTime = cms.bool(True),
    recordName = cms.string('EcalMappingRcd')
)


process.es_hardcode = cms.ESSource("HcalHardcodeCalibrations",
    GainWidthsForTrigPrims = cms.bool(False),
    HERecalibration = cms.bool(False),
    HEreCalibCutoff = cms.double(20.0),
    HFRecalibration = cms.bool(False),
    HcalReLabel = cms.PSet(
        RelabelHits = cms.untracked.bool(False),
        RelabelRules = cms.untracked.PSet(
            CorrectPhi = cms.untracked.bool(False),
            Eta1 = cms.untracked.vint32(1, 2, 2, 2, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3),
            Eta16 = cms.untracked.vint32(1, 1, 2, 2, 2, 
                2, 2, 2, 2, 3, 
                3, 3, 3, 3, 3, 
                3, 3, 3, 3),
            Eta17 = cms.untracked.vint32(1, 1, 2, 2, 3, 
                3, 3, 4, 4, 4, 
                4, 4, 5, 5, 5, 
                5, 5, 5, 5)
        )
    ),
    hcalTopologyConstants = cms.PSet(
        maxDepthHB = cms.int32(2),
        maxDepthHE = cms.int32(3),
        mode = cms.string('HcalTopologyMode::LHC')
    ),
    iLumi = cms.double(-1.0),
    toGet = cms.untracked.vstring('GainWidths')
)


process.prefer("es_hardcode")

process.CondDBSetup = cms.PSet(
    DBParameters = cms.PSet(
        authenticationPath = cms.untracked.string(''),
        authenticationSystem = cms.untracked.int32(0),
        connectionRetrialPeriod = cms.untracked.int32(10),
        connectionRetrialTimeOut = cms.untracked.int32(60),
        connectionTimeOut = cms.untracked.int32(60),
        enableConnectionSharing = cms.untracked.bool(True),
        enablePoolAutomaticCleanUp = cms.untracked.bool(False),
        enableReadOnlySessionOnUpdateConnection = cms.untracked.bool(False),
        idleConnectionCleanupPeriod = cms.untracked.int32(10),
        messageLevel = cms.untracked.int32(0)
    )
)

process.HcalReLabel = cms.PSet(
    RelabelHits = cms.untracked.bool(False),
    RelabelRules = cms.untracked.PSet(
        CorrectPhi = cms.untracked.bool(False),
        Eta1 = cms.untracked.vint32(1, 2, 2, 2, 3, 
            3, 3, 3, 3, 3, 
            3, 3, 3, 3, 3, 
            3, 3, 3, 3),
        Eta16 = cms.untracked.vint32(1, 1, 2, 2, 2, 
            2, 2, 2, 2, 3, 
            3, 3, 3, 3, 3, 
            3, 3, 3, 3),
        Eta17 = cms.untracked.vint32(1, 1, 2, 2, 3, 
            3, 3, 4, 4, 4, 
            4, 4, 5, 5, 5, 
            5, 5, 5, 5)
    )
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.trackWithVertexSelectorParams = cms.PSet(
    copyExtras = cms.untracked.bool(False),
    copyTrajectories = cms.untracked.bool(False),
    d0Max = cms.double(999.0),
    dzMax = cms.double(999.0),
    etaMax = cms.double(5.0),
    etaMin = cms.double(0.0),
    nVertices = cms.uint32(0),
    normalizedChi2 = cms.double(999999.0),
    numberOfLostHits = cms.uint32(999),
    numberOfValidHits = cms.uint32(0),
    numberOfValidPixelHits = cms.uint32(0),
    ptErrorCut = cms.double(0.2),
    ptMax = cms.double(500.0),
    ptMin = cms.double(0.3),
    quality = cms.string('highPurity'),
    rhoVtx = cms.double(0.2),
    src = cms.InputTag("generalTracks"),
    useVtx = cms.bool(True),
    vertexTag = cms.InputTag("offlinePrimaryVertices"),
    vtxFallback = cms.bool(True),
    zetaVtx = cms.double(1.0)
)

