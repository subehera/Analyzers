import FWCore.ParameterSet.Config as cms
import Analyzers.Cumulants.PPPileUpVertexFilter_cfi
pileupVertexFilterCutG = Analyzers.Cumulants.PPPileUpVertexFilter_cfi.pileupVertexFilter.clone()
pileupVertexFilterCutGloose = pileupVertexFilterCutG.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                     999., 4.5, 3.2, 3.0, 1.8, 1.8, 1.35, 0.9
                                                                                     )
                                                           )
pileupVertexFilterCutGtight = pileupVertexFilterCutG.clone(
                                                           dzCutByNtrk = cms.vdouble(
                                                                                     999., 2.0, 1.6, 1.333, 0.8, 0.8, 0.6, 0.4
                                                                                     )
                                                           )
pileupVertexFilterCutGplusNV = pileupVertexFilterCutG.clone(
                                                            dzCutByNtrk = cms.vdouble(
                                                                                      999., 999., 999., 3.0, 2.0,
                                                                                      1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                      0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                      0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                      0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                      0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                      0.0
                                                                                      ),
                                                            dxyVeto = cms.double(999.)
                                                            )
pileupVertexFilterCutE = pileupVertexFilterCutG.clone(
                                                      doDzNtrkCut = cms.bool(False),
                                                      doDxyDzCut = cms.bool(True)
                                                      )
pileupVertexFilterCutEandG = pileupVertexFilterCutG.clone(
                                                          doDzNtrkCut = cms.bool(True),
                                                          doDxyDzCut = cms.bool(True)
                                                          )
pileupVertexFilterCutW = pileupVertexFilterCutG.clone(
                                                      doDzNtrkCut = cms.bool(False),
                                                      doSurfaceCut = cms.bool(True)
                                                      )
pileupVertexFilterCutWplus = pileupVertexFilterCutG.clone(
                                                          doDzNtrkCut = cms.bool(False),
                                                          doSurfaceCut = cms.bool(True),
                                                          dxyVeto = cms.double(0.05)
                                                          )
pileupVertexFilterCutGplusplus = pileupVertexFilterCutG.clone(
                                                              doDzNtrkCut = cms.bool(False),
                                                              doSurfaceCut = cms.bool(True),
                                                              dxyVeto = cms.double(0.05),
                                                              surfaceMinDzEval = cms.double(0.0),
                                                              surfaceFunctionString = cms.string("[0]*exp([1]*(x-([3]*(y-[4])**2+[5])))+[2]"),
                                                              surfaceCutParameters = cms.vdouble(
                                                                                                 28.593,-1.525,2.636788,-1.5e-5,200.,0.0
                                                                                                 )
                                                              )
pileupVertexFilterCutGplusUpsPP = pileupVertexFilterCutG.clone(
                                                               dzCutByNtrk = cms.vdouble(
                                                                                         999., 999., 1.5, 1.0, 0.8,
                                                                                         0.6, 0.5, 0.4, 0.3, 0.2,
                                                                                         0.2, 0.2, 0.2, 0.2, 0.2,
                                                                                         0.2, 0.0
                                                                                         ),
                                                               dxyVeto = cms.double(999.)
                                                               )
pileupVertexFilterCutGplus = pileupVertexFilterCutG.clone(
                                                          dzCutByNtrk = cms.vdouble(
                                                                                    999., 999., 999., 3.0, 2.0,
                                                                                    1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                    0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                    0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                    0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                    0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                    0.0
                                                                                    ),
                                                          dxyVeto = cms.double(0.05),
                                                          dzTolerance = cms.double(9999.)
                                                          )
pileupVertexFilterCutGplusPP = pileupVertexFilterCutG.clone(
                                                            dzCutByNtrk = cms.vdouble(
                                                                                      999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                      ),
                                                            dxyVeto = cms.double(999.),
                                                            dzTolerance = cms.double(9999.)
                                                            )
pileupVertexFilterCut_dz05_Gplus = pileupVertexFilterCutG.clone(
                                                          dzCutByNtrk = cms.vdouble(
                                                                                    999., 999., 999., 3.0, 2.0,
                                                                                    1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                    0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                    0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                    0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                    0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                    0.0
                                                                                    ),
                                                          dxyVeto = cms.double(0.05),
                                                          dzTolerance = cms.double(0.5),
                                                          )
pileupVertexFilterCut_dz05_GplusPP = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                            ),
                                                                dxyVeto = cms.double(999.),
                                                                dzTolerance = cms.double(0.5),
                                                                )

pileupVertexFilterCut_dz05_noGplus = pileupVertexFilterCutG.clone(
                                                                dzCutByNtrk = cms.vdouble(
                                                                                          999., 0.0, 0.0, 0.0, 0.0
                                                                                          ),
                                                                dzTolerance = cms.double(0.5),
                                                                )
pileupVertexFilterCut_dz10_Gplus = pileupVertexFilterCutG.clone(
                                                                dzCutByNtrk = cms.vdouble(
                                                                                          999., 999., 999., 3.0, 2.0,
                                                                                          1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                          0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                          0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                          0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                          0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                          0.0
                                                                                          ),
                                                                dxyVeto = cms.double(0.05),
                                                                dzTolerance = cms.double(1.0),
                                                                )
pileupVertexFilterCut_dz10_GplusPP = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                            ),
                                                                dxyVeto = cms.double(999.),
                                                                dzTolerance = cms.double(1.0),
                                                                )
pileupVertexFilterCut_dz10_noGplus = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 0.0, 0.0, 0.0, 0.0
                                                                                            ),
                                                                  dzTolerance = cms.double(1.0),
                                                                  )
pileupVertexFilterCut_dz20_Gplus = pileupVertexFilterCutG.clone(
                                                                dzCutByNtrk = cms.vdouble(
                                                                                          999., 999., 999., 3.0, 2.0,
                                                                                          1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                          0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                          0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                          0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                          0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                          0.0
                                                                                          ),
                                                                dxyVeto = cms.double(0.05),
                                                                dzTolerance = cms.double(2.0),
                                                                )
pileupVertexFilterCut_dz20_GplusPP = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                            ),
                                                                dxyVeto = cms.double(999.),
                                                                dzTolerance = cms.double(2.0),
                                                                )
pileupVertexFilterCut_dz20_noGplus = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 0.0, 0.0, 0.0, 0.0
                                                                                            ),
                                                                  dzTolerance = cms.double(2.0),
                                                                  )
pileupVertexFilterCut_dz30_Gplus = pileupVertexFilterCutG.clone(
                                                                dzCutByNtrk = cms.vdouble(
                                                                                          999., 999., 999., 3.0, 2.0,
                                                                                          1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                          0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                          0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                          0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                          0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                          0.0
                                                                                          ),
                                                                dxyVeto = cms.double(0.05),
                                                                dzTolerance = cms.double(3.0),
                                                                )
pileupVertexFilterCut_dz30_GplusPP = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                            ),
                                                                dxyVeto = cms.double(999.),
                                                                dzTolerance = cms.double(3.0),
                                                                )
pileupVertexFilterCut_dz30_noGplus = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 0.0, 0.0, 0.0, 0.0
                                                                                            ),
                                                                  dzTolerance = cms.double(3.0),
                                                                  )
pileupVertexFilterCut_dz40_Gplus = pileupVertexFilterCutG.clone(
                                                                dzCutByNtrk = cms.vdouble(
                                                                                          999., 999., 999., 3.0, 2.0,
                                                                                          1.6, 1.4, 1.2, 1.1, 1.0,
                                                                                          0.9, 0.8, 0.7, 0.7, 0.6,
                                                                                          0.6, 0.5, 0.5, 0.4, 0.4,
                                                                                          0.4, 0.3, 0.3, 0.3, 0.3,
                                                                                          0.3, 0.2, 0.2, 0.2, 0.2,
                                                                                          0.0
                                                                                          ),
                                                                dxyVeto = cms.double(0.05),
                                                                dzTolerance = cms.double(4.0),
                                                                )
pileupVertexFilterCut_dz40_GplusPP = pileupVertexFilterCutG.clone(
                                                                 dzCutByNtrk = cms.vdouble(
                                                                                           999., 4.0, 4.0, 1.6, 1.0, 0.7, 0.5, 0.4, 0.3, 0.2, 0.0
                                                                                           ),
                                                               dxyVeto = cms.double(999.),
                                                               dzTolerance = cms.double(4.0),
                                                               )
pileupVertexFilterCut_dz40_noGplus = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 0.0, 0.0, 0.0, 0.0
                                                                                            ),
                                                                  dzTolerance = cms.double(4.0),
                                                                  )
pileupVertexFilterCut_vtx1 = pileupVertexFilterCutG.clone(
                                                                  dzCutByNtrk = cms.vdouble(
                                                                                            999., 0.0, 0.0, 0.0, 0.0
                                                                                            ),
                                                                  dzTolerance = cms.double(9999.),
                                                                  )

#pileupVertexFilterCut_pp = cms.Sequence( pileupVertexFilterCut_dz10_GplusPP )
pileupVertexFilterCut_pp = cms.Sequence( pileupVertexFilterCut_vtx1 )
#pileupVertexFilterCut_pp = cms.Sequence()
