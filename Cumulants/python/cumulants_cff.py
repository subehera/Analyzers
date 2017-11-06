import FWCore.ParameterSet.Config as cms

from Analyzers.Cumulants.cumulants_cfi import *

sub2Analysis = defaultCumu.clone()
sub2V3Analysis = defaultCumu.clone()
sub2V3Analysis.harm = cms.untracked.vint32(3,3,3,3)
sub2V4Analysis = defaultCumu.clone()
sub2V4Analysis.harm = cms.untracked.vint32(4,4,4,4)

sub2gap1Analysis = defaultCumu.clone()
sub2gap1Analysis.etasubmin = cms.vdouble(-2.4,-2.4,-2.4,-2.4,0.5,0.5,0.5,0.5)
sub2gap1Analysis.etasubmax = cms.vdouble(-0.5,-0.5,-0.5,-0.5,2.4,2.4,2.4,2.4)
sub2gap2Analysis = defaultCumu.clone()
sub2gap2Analysis.etasubmin = cms.vdouble(-2.4,-2.4,-2.4,-2.4,1.,1.,1.,1.)
sub2gap2Analysis.etasubmax = cms.vdouble(-1.,-1.,-1.,-1.,2.4,2.4,2.4,2.4)

sub2gap1V3Analysis = sub2gap1Analysis.clone()
sub2gap1V3Analysis.harm = cms.untracked.vint32(3,3,3,3)
sub2gap1V4Analysis = sub2gap1Analysis.clone()
sub2gap1V4Analysis.harm = cms.untracked.vint32(4,4,4,4)
sub2gap2V3Analysis = sub2gap2Analysis.clone()
sub2gap2V3Analysis.harm = cms.untracked.vint32(3,3,3,3)
sub2gap2V4Analysis = sub2gap2Analysis.clone()
sub2gap2V4Analysis.harm = cms.untracked.vint32(4,4,4,4)

# c26:abb|acc
# c28:abbb|accc
sub3Analysis = defaultCumu.clone()
sub3Analysis.nsubevt = cms.untracked.int32(3)
sub3Analysis.etasubmin = cms.vdouble(0.8,0.8,0.8,-0.8,-2.4,-2.4,-2.4,-0.8)
sub3Analysis.etasubmax = cms.vdouble(2.4,2.4,2.4,0.8,-0.8,-0.8,-0.8,0.8)
sub3V3Analysis = sub3Analysis.clone()
sub3V3Analysis.harm = cms.untracked.vint32(3,3,3,3)
sub3V4Analysis = sub3Analysis.clone()
sub3V4Analysis.harm = cms.untracked.vint32(4,4,4,4)

# c26:aac|bbc
# c28:aaac|bbbc
#sub3POSAnalysis = defaultCumu.clone()
#sub3POSAnalysis.etasubmin = cms.vdouble(-0.8,0.8,-0.8,-0.8,-2.4,-2.4,0.8,-2.4)
#sub3POSAnalysis.etasubmax = cms.vdouble(0.8,2.4,0.8,0.8,-0.8,-0.8,2.4,-0.8)
#sub3POSV3Analysis = sub3POSAnalysis.clone()
#sub3POSV3Analysis.harm = cms.untracked.vint32(3,3,3,3)
#sub3POSV4Analysis = sub3POSAnalysis.clone()
#sub3POSV4Analysis.harm = cms.untracked.vint32(4,4,4,4)

# c26:acc|abb
# c28:accc|abbb
#sub3NEGAnalysis = defaultCumu.clone()
#sub3NEGAnalysis.etasubmin = cms.vdouble(-0.8,-2.4,-0.8,-0.8,0.8,0.8,-2.4,0.8)
#sub3NEGAnalysis.etasubmax = cms.vdouble(0.8,-0.8,0.8,0.8,2.4,2.4,-0.8,2.4)
#sub3NEGV3Analysis = sub3NEGAnalysis.clone()
#sub3NEGV3Analysis.harm = cms.untracked.vint32(3,3,3,3)
#sub3NEGV4Analysis = sub3NEGAnalysis.clone()
#sub3NEGV4Analysis.harm = cms.untracked.vint32(4,4,4,4)

sub4Analysis = defaultCumu.clone()
sub4Analysis.nsubevt = cms.untracked.int32(4)
sub4Analysis.etasubmin = cms.vdouble(-1.2,-2.4,-1.2,-2.4,0.,1.2,0.,1.2)
sub4Analysis.etasubmax = cms.vdouble(0.,-1.2,0.,-1.2,1.2,2.4,1.2,2.4)
sub4V3Analysis = sub4Analysis.clone()
sub4V3Analysis.harm = cms.untracked.vint32(3,3,3,3)
sub4V4Analysis = sub4Analysis.clone()
sub4V4Analysis.harm = cms.untracked.vint32(4,4,4,4)

stdAnalysis = defaultCumu.clone()
stdAnalysis.nsubevt = cms.untracked.int32(1)
stdAnalysis.etasubmin = cms.vdouble(-2.4,-2.4,-2.4,-2.4,-2.4,-2.4,-2.4,-2.4)
stdAnalysis.etasubmax = cms.vdouble(2.4,2.4,2.4,2.4,2.4,2.4,2.4,2.4)
stdV3Analysis = stdAnalysis.clone()
stdV3Analysis.harm = cms.untracked.vint32(3,3,3,3)
stdV4Analysis = stdAnalysis.clone()
stdV4Analysis.harm = cms.untracked.vint32(4,4,4,4)

### pt-differential cumulants
sub2Analysis_Pt10POS = defaultCumu.clone()
sub2Analysis_Pt10POS.ptsubmin = cms.vdouble(0.3,0.3,0.3,0.3,0.3,0.3,0.3,10.0)
sub2Analysis_Pt10POS.ptsubmax = cms.vdouble(3.0,3.0,3.0,3.0,3.0,3.0,3.0,10000.0)

sub2Analysis_Pt10NEG = defaultCumu.clone()
sub2Analysis_Pt10NEG.ptsubmin = cms.vdouble(0.3,0.3,0.3,10.0,0.3,0.3,0.3,0.3)
sub2Analysis_Pt10NEG.ptsubmax = cms.vdouble(3.0,3.0,3.0,10000.0,3.0,3.0,3.0,3.0)

sub3Analysis_Pt10MID = defaultCumu.clone()
sub3Analysis_Pt10MID.ptsubmin = cms.vdouble(0.3,0.3,0.3,10.,0.3,0.3,0.3,0.3)
sub3Analysis_Pt10MID.ptsubmax = cms.vdouble(3.0,3.0,3.0,10000.,3.0,3.0,3.0,3.0)

### symmetric cumulants
# default 2-subevent
sub2AnalysisSC23 = defaultCumu.clone()
sub2AnalysisSC23.harm = cms.untracked.vint32(2,3,2,3)
sub2AnalysisSC24 = defaultCumu.clone()
sub2AnalysisSC24.harm = cms.untracked.vint32(2,4,2,4)

# 2-subevent with gap 1
sub2gap1AnalysisSC23 = sub2gap1Analysis.clone()
sub2gap1AnalysisSC23.harm  = cms.untracked.vint32(2,3,2,3)
sub2gap1AnalysisSC24 = sub2gap1Analysis.clone()
sub2gap1AnalysisSC24.harm  = cms.untracked.vint32(2,4,2,4)

# 2-subevent with gap 2
sub2gap2AnalysisSC23 = sub2gap2Analysis.clone()
sub2gap2AnalysisSC23.harm  = cms.untracked.vint32(2,3,2,3)
sub2gap2AnalysisSC24 = sub2gap2Analysis.clone()
sub2gap2AnalysisSC24.harm  = cms.untracked.vint32(2,4,2,4)

# 3-subevent
sub3AnalysisSC23 = sub3Analysis.clone()
sub3AnalysisSC23.harm  = cms.untracked.vint32(2,3,2,3)
sub3AnalysisSC24 = sub3Analysis.clone()
sub3AnalysisSC24.harm  = cms.untracked.vint32(2,4,2,4)

# 4-subevent
sub4AnalysisSC23 = sub4Analysis.clone()
sub4AnalysisSC23.harm  = cms.untracked.vint32(2,3,2,3)
sub4AnalysisSC24 = sub4Analysis.clone()
sub4AnalysisSC24.harm  = cms.untracked.vint32(2,4,2,4)

# std
stdAnalysisSC23 = stdAnalysis.clone()
stdAnalysisSC23.harm  = cms.untracked.vint32(2,3,2,3)
stdAnalysisSC24 = stdAnalysis.clone()
stdAnalysisSC24.harm  = cms.untracked.vint32(2,4,2,4)
