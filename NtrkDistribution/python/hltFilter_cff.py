import FWCore.ParameterSet.Config as cms

#Trigger Selection
### Comment out for the timing being assuming running on secondary dataset with trigger bit selected already
import HLTrigger.HLTfilters.hltHighLevel_cfi

#pPb 8 TeV
hltPA8MB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8MB.HLTPaths = ['HLT_PAL1MinimumBiasHF_OR_SinglePixelTrack_*_v*']
hltPA8MB.andOr = cms.bool(True)
hltPA8MB.throw = cms.bool(False)

hltPA8120 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8120.HLTPaths = ['HLT_PAFullTracks_Multiplicity120*_v*']
hltPA8120.andOr = cms.bool(True)
hltPA8120.throw = cms.bool(False)

hltPA8150 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8150.HLTPaths = ['HLT_PAFullTracks_Multiplicity120_v*','HLT_PAFullTracks_Multiplicity150*_v*']
hltPA8150.andOr = cms.bool(True)
hltPA8150.throw = cms.bool(False)

hltPA8185 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8185.HLTPaths = ['HLT_PAFullTracks_Multiplicity185*_v*']
hltPA8185.andOr = cms.bool(True)
hltPA8185.throw = cms.bool(False)

hltPA8250 = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
hltPA8250.HLTPaths = ['HLT_PAFullTracks_Multiplicity250_v*']
hltPA8250.andOr = cms.bool(True)
hltPA8250.throw = cms.bool(False)

#pPb 5 TeV
hltPA5100 = hltPA8MB.clone()
hltPA5100.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*'] 

hltPA5130 = hltPA8MB.clone()
hltPA5130.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*']

hltPA5160 = hltPA8MB.clone()
hltPA5160.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*']

hltPA5190 = hltPA8MB.clone()
hltPA5190.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*','HLT_PAPixelTracks_Multiplicity190_v*']

hltPA5220 = hltPA8MB.clone()
hltPA5220.HLTPaths = ['HLT_PAPixelTracks_Multiplicity100_v*','HLT_PAPixelTracks_Multiplicity130_v*','HLT_PAPixelTracks_Multiplicity160_v*','HLT_PAPixelTracks_Multiplicity190_v*','HLT_PAPixelTracks_Multiplicity220_v*']





