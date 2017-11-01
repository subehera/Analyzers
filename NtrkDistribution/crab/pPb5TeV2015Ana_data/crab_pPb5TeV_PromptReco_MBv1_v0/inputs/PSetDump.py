import FWCore.ParameterSet.Config as cms

process = cms.Process("NtrkDistribution")

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch///store/user/davidlw/PAMinBiasUPC/PA2013_FlowCorr_PromptReco_MB_Gplus_ReTracking_v18/25c9a89be536a41c8ccb3c75e9fd9358/pPb_HM_1000_1_Miz.root')
)
process.defaultAnalysis = cms.EDAnalyzer("NtrkDistribution",
    maxvz = cms.untracked.double(150.0),
    pterrorptnoff = cms.untracked.double(0.1),
    d0d0errornoff = cms.untracked.double(3.0),
    pterrorpt = cms.untracked.double(0.1),
    ptmin = cms.untracked.double(0.3),
    d0d0error = cms.untracked.double(3.0),
    noffmin = cms.untracked.int32(0),
    ptnoffmin = cms.untracked.double(0.4),
    ptmax = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    maxrho = cms.untracked.double(100.0),
    minvz = cms.untracked.double(-150.0),
    etamin = cms.untracked.double(-2.4),
    dzdzerror = cms.untracked.double(3.0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    fname = cms.untracked.InputTag("TrackCorrections_HIJING_538_OFFICIAL_Mar24.root"),
    etamax = cms.untracked.double(2.4),
    ptnoffmax = cms.untracked.double(100000),
    caloTower = cms.InputTag("towerMaker"),
    vertex = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    isBVselByMult = cms.untracked.bool(True),
    centralitySrc = cms.InputTag("hiCentrality"),
    noffmax = cms.untracked.int32(100000),
    effmultbin = cms.untracked.vint32(0, 10000)
)


process.defaultNtrkDist = cms.EDAnalyzer("NtrkDistribution",
    maxvz = cms.untracked.double(150.0),
    pterrorptnoff = cms.untracked.double(0.1),
    d0d0errornoff = cms.untracked.double(3.0),
    pterrorpt = cms.untracked.double(0.1),
    ptmin = cms.untracked.double(0.3),
    ptmax = cms.untracked.double(3.0),
    noffmin = cms.untracked.int32(0),
    centralityBinSrc = cms.InputTag("centralityBin","HFtowers"),
    d0d0error = cms.untracked.double(3.0),
    dzdzerrornoff = cms.untracked.double(3.0),
    maxrho = cms.untracked.double(100.0),
    minvz = cms.untracked.double(-150.0),
    etamin = cms.untracked.double(-2.4),
    dzdzerror = cms.untracked.double(3.0),
    ptnoffmin = cms.untracked.double(0.4),
    fname = cms.untracked.InputTag("TrackCorrections_HIJING_538_OFFICIAL_Mar24.root"),
    etamax = cms.untracked.double(2.4),
    isBVselByMult = cms.untracked.bool(True),
    caloTower = cms.InputTag("towerMaker"),
    vertex = cms.InputTag("offlinePrimaryVertices"),
    tracks = cms.InputTag("generalTracks"),
    ptnoffmax = cms.untracked.double(100000),
    effmultbin = cms.untracked.vint32(0, 10000),
    noffmax = cms.untracked.int32(100000),
    centralitySrc = cms.InputTag("hiCentrality")
)


process.p = cms.Path(process.defaultAnalysis)


process.MessageLogger = cms.Service("MessageLogger",
    suppressInfo = cms.untracked.vstring(),
    debugs = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    suppressDebug = cms.untracked.vstring(),
    cout = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    cerr_stats = cms.untracked.PSet(
        threshold = cms.untracked.string('WARNING'),
        output = cms.untracked.string('cerr'),
        optionalPSet = cms.untracked.bool(True)
    ),
    warnings = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    default = cms.untracked.PSet(

    ),
    statistics = cms.untracked.vstring('cerr_stats'),
    cerr = cms.untracked.PSet(
        INFO = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        noTimeStamps = cms.untracked.bool(False),
        FwkReport = cms.untracked.PSet(
            reportEvery = cms.untracked.int32(100000),
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(10000000)
        ),
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(10000000)
        ),
        Root_NoDictionary = cms.untracked.PSet(
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(0)
        ),
        threshold = cms.untracked.string('INFO'),
        FwkJob = cms.untracked.PSet(
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(0)
        ),
        FwkSummary = cms.untracked.PSet(
            reportEvery = cms.untracked.int32(1),
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(10000000)
        ),
        optionalPSet = cms.untracked.bool(True)
    ),
    FrameworkJobReport = cms.untracked.PSet(
        default = cms.untracked.PSet(
            limit = cms.untracked.int32(0)
        ),
        optionalPSet = cms.untracked.bool(True),
        FwkJob = cms.untracked.PSet(
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(10000000)
        )
    ),
    suppressWarning = cms.untracked.vstring(),
    errors = cms.untracked.PSet(
        placeholder = cms.untracked.bool(True)
    ),
    destinations = cms.untracked.vstring('warnings', 
        'errors', 
        'infos', 
        'debugs', 
        'cout', 
        'cerr'),
    debugModules = cms.untracked.vstring(),
    infos = cms.untracked.PSet(
        optionalPSet = cms.untracked.bool(True),
        Root_NoDictionary = cms.untracked.PSet(
            optionalPSet = cms.untracked.bool(True),
            limit = cms.untracked.int32(0)
        ),
        placeholder = cms.untracked.bool(True)
    ),
    categories = cms.untracked.vstring('FwkJob', 
        'FwkReport', 
        'FwkSummary', 
        'Root_NoDictionary'),
    fwkJobReports = cms.untracked.vstring('FrameworkJobReport')
)


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('/afs/cern.ch/user/m/mguilbau/AnalyzerForWei/CMSSW_5_3_20/src/Analyzers/NtrkDistribution/test/ntrkdist.root')
)


process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

