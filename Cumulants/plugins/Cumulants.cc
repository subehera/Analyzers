// -*- C++ -*-
//
// Package:    Analyzers/Cumulants
// Class:      Cumulants
// 
/**\class Cumulants Cumulants.cc Analyzers/Cumulants/plugins/Cumulants.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Maxime Guilbaud
//         Created:  Thu, 01 Jun 2017 16:56:11 GMT
//
//

// system include files

// CMSSW include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

// user include files
#include "Analyzers/Cumulants/interface/Cumulants.h"
#include "Analyzers/Cumulants/interface/MultiCumulants/MultiCumulants/NativeMaskLUT.h"
//
// constructors and destructor
//
Cumulants::Cumulants(const edm::ParameterSet& iConfig) :
  //tracks
  trackTags_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
  //vertex
  vtxTags_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex"))),
  //caloTower
  caloTowersTags_(consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("caloTower"))),
  //centrality
  centralityTags_(consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"))),
  centralityBinTags_(consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinSrc"))),
  //multiplicity selection
  noffmin_(iConfig.getUntrackedParameter<int>("noffmin")),
  noffmax_(iConfig.getUntrackedParameter<int>("noffmax")),
  ptnoffmin_(iConfig.getUntrackedParameter<double>("ptnoffmin")),
  ptnoffmax_(iConfig.getUntrackedParameter<double>("ptnoffmax")),
  dzdzerrornoff_(iConfig.getUntrackedParameter<double>("dzdzerrornoff")),
  d0d0errornoff_(iConfig.getUntrackedParameter<double>("d0d0errornoff")),
  pterrorptnoff_(iConfig.getUntrackedParameter<double>("pterrorptnoff")),
  //track selection
  etamin_(iConfig.getUntrackedParameter<double>("etamin")),
  etamax_(iConfig.getUntrackedParameter<double>("etamax")),
  ptmin_(iConfig.getUntrackedParameter<double>("ptmin")),
  ptmax_(iConfig.getUntrackedParameter<double>("ptmax")),
  etasubmin_(iConfig.getParameter< std::vector<double> >("etasubmin")),
  etasubmax_(iConfig.getParameter< std::vector<double> >("etasubmax")),
  ptsubmin_(iConfig.getParameter< std::vector<double> >("ptsubmin")),
  ptsubmax_(iConfig.getParameter< std::vector<double> >("ptsubmax")),
  dzdzerror_(iConfig.getUntrackedParameter<double>("dzdzerror")),
  d0d0error_(iConfig.getUntrackedParameter<double>("d0d0error")),
  pterrorpt_(iConfig.getUntrackedParameter<double>("pterrorpt")),
  //vertex selection
  minvz_(iConfig.getUntrackedParameter<double>("minvz")),
  maxvz_(iConfig.getUntrackedParameter<double>("maxvz")),
  maxrho_(iConfig.getUntrackedParameter<double>("maxrho")),
  isBVselByMult_(iConfig.getUntrackedParameter<bool>("isBVselByMult")),
  nvtx_(iConfig.getUntrackedParameter<int>("nvtx",-1)),
  xBestVtx_(iConfig.getUntrackedParameter<double>("xVtx",-99999)),
  yBestVtx_(iConfig.getUntrackedParameter<double>("yVtx",-99999)),
  rhoBestVtx_(iConfig.getUntrackedParameter<double>("rhoVtx",-99999)),
  zBestVtx_(iConfig.getUntrackedParameter<double>("zVtx",-99999)),
  xBestVtxError_(iConfig.getUntrackedParameter<double>("xVtxError",-99999)),
  yBestVtxError_(iConfig.getUntrackedParameter<double>("yVtxError",-99999)),
  zBestVtxError_(iConfig.getUntrackedParameter<double>("zVtxError",-99999)),
  //harmonic order
  harm_(iConfig.getUntrackedParameter< std::vector<int> >("harm")),
  nsubevt_(iConfig.getUntrackedParameter<int>("nsubevt")), 
  cweight_(iConfig.getUntrackedParameter<bool>("cweight")),
     //2-sub event relative eta difference
//  deltaeta_(iConfig.getUntrackedParameter<double>("deltaeta")),
  //file acc & eff & fake
  fname_(iConfig.getUntrackedParameter<edm::InputTag>("fname")),
  effmultbin_(iConfig.getUntrackedParameter< std::vector<int> >("effmultbin"))
{
   TString filename(fname_.label().c_str());
   feff_ = 0x0;
   if(cweight_ && !filename.IsNull())
   {
      edm::FileInPath fip(Form("Analyzers/Cumulants/data/EFF/%s",filename.Data()));
      feff_ = new TFile(fip.fullPath().c_str(),"READ");

      heff_.resize(feff_->GetNkeys());
      if(heff_.size() != effmultbin_.size() - 1)
      {
         edm::LogWarning ("Inconsitent binning") << " Inconsistent binning for the acc X eff correction..."
                                                 << " You might have wrong setting here";
      }

      for(unsigned short ik = 0; ik < heff_.size(); ++ik)
      {
         heff_[ik] = (TH2D*) feff_->Get(feff_->GetListOfKeys()->At(ik)->GetName());
      }
      feff_->Close();
   }

   //Calculate relative difference between sub events
   // deltaeta = M means the upper bound and the lower bound of the sub event 1 and 2 respectively, will be separated by M
   // if deltaeta < 0 the 2 subevents have an overlap of size M
   // if M is larger than 4.8, this is the standard cumulant method with full overlap
   // double upper_bound_subset1 = -1.*deltaeta_/2.;
   // if( upper_bound_subset1 > 2.4 ) upper_bound_subset1 = 2.4;
   // double lower_bound_subset2 = +1.*deltaeta_/2.;
   // if( lower_bound_subset2 < -2.4 ) lower_bound_subset2 = -2.4;

   //Init cumulants
   cumulant::Subset sub_1(2);
   sub_1.set(0, "pt", ptsubmin_[0], ptsubmax_[0]);
   sub_1.set(1, "eta", etasubmin_[0], etasubmax_[0]);
   cumulant::Subset sub_2(2);
   sub_2.set(0, "pt", ptsubmin_[1], ptsubmax_[1]);
   sub_2.set(1, "eta", etasubmin_[1], etasubmax_[1]);
   cumulant::Subset sub_3(2);
   sub_3.set(0, "pt", ptsubmin_[2], ptsubmax_[2]);
   sub_3.set(1, "eta", etasubmin_[2], etasubmax_[2]);
   cumulant::Subset sub_4(2);
   sub_4.set(0, "pt", ptsubmin_[3], ptsubmax_[3]);
   sub_4.set(1, "eta", etasubmin_[3], etasubmax_[3]);
   cumulant::Subset sub_5(2);
   sub_5.set(0, "pt", ptsubmin_[4], ptsubmax_[4]);
   sub_5.set(1, "eta", etasubmin_[4], etasubmax_[4]);
   cumulant::Subset sub_6(2);
   sub_6.set(0, "pt", ptsubmin_[5], ptsubmax_[5]);
   sub_6.set(1, "eta", etasubmin_[5], etasubmax_[5]);
   cumulant::Subset sub_7(2);
   sub_7.set(0, "pt", ptsubmin_[6], ptsubmax_[6]);
   sub_7.set(1, "eta", etasubmin_[6], etasubmax_[6]);
   cumulant::Subset sub_8(2);
   sub_8.set(0, "pt", ptsubmin_[7], ptsubmax_[7]);
   sub_8.set(1, "eta", etasubmin_[7], etasubmax_[7]);


   //Init sub-event method
   cumulant::Set set(8);
   set.setSubsetParams(0, sub_1);
   set.setSubsetParams(1, sub_2);
   set.setSubsetParams(2, sub_3);
   set.setSubsetParams(3, sub_4);
   set.setSubsetParams(4, sub_5);
   set.setSubsetParams(5, sub_6);
   set.setSubsetParams(6, sub_7);
   set.setSubsetParams(7, sub_8);
   HarmonicVector h(8);
   h[0] =  1*harm_[0];
   h[1] =  1*harm_[1];
   h[2] =  1*harm_[2];
   h[3] =  1*harm_[3];
   h[4] = -1*harm_[0];
   h[5] = -1*harm_[1];
   h[6] = -1*harm_[2];
   h[7] = -1*harm_[3];

   qN_ = cumulant::QVectorSet(h, set, cweight_);

   //Ouptut
//   usesResource("TFileService");
//   edm::Service<TFileService> fs;
   // Histograms
}

void Cumulants::beginJob()
{
   TFileDirectory fVtxHist  = fs->mkdir("Vertex");
   hXBestVtx_   = fVtxHist.make<TH1F>("hXvtx", "", 80, -0.2, 0.2);
   hYBestVtx_   = fVtxHist.make<TH1F>("hYvtx", "", 80, -0.2, 0.2);
   hRhoBestVtx_ = fVtxHist.make<TH1F>("hRvtx", "", 80, -0.2, 0.2);
   hZBestVtx_   = fVtxHist.make<TH1F>("hZvtx", "", 60, -30., 30.);
   TFileDirectory fTrkHist  = fs->mkdir("Tracks");
   hEtaTrk_ = fTrkHist.make<TH1F>("hEtatrk", "", 30, -3.,   3.);
   hPtTrk_  = fTrkHist.make<TH1F>("hPttrk",  "", 10,  0.,  10.);
   hPhiTrk_ = fTrkHist.make<TH1F>("hPhitrk", "", 64, -3.2,  3.2);
   hEtaNoff_ = fTrkHist.make<TH1F>("hEtaNoff", "", 30, -3.,   3.);
   hPtNoff_  = fTrkHist.make<TH1F>("hPtNoff",  "", 10,  0.,  10.);
   hPhiNoff_ = fTrkHist.make<TH1F>("hPhiNoff", "", 64, -3.2,  3.2);
   TFileDirectory fCTowHist = fs->mkdir("CaloTowers");
   hEtaCTow_ = fCTowHist.make<TH1F>("hEtatow", "", 12, -6.,   6.);
   hEtCTow_  = fCTowHist.make<TH1F>("hEttow",  "", 10,  0.,  10.);
   hPhiCTow_ = fCTowHist.make<TH1F>("hPhitow", "", 64, -3.2,  3.2);
   // TTree
   trEvent_ = fs->make<TTree>("trEvent", "trEvent");
   trEvent_->Branch("centrality", &cent_, "centrality/I");
   trEvent_->Branch("nVtx",       &nvtx_, "nVtx/I");
   trEvent_->Branch("Noff",       &noff_, "Noff/I");
   trEvent_->Branch("Mult",       &mult_, "Mult/I");
   trEvent_->Branch(Form("C%d%d8",harm_[0],harm_[1]),  &CN8_,  Form("C%d%d8/D",harm_[0],harm_[1]));
   trEvent_->Branch(Form("C%d%d6_119",harm_[0],harm_[1]),  &CN6_119_,  Form("C%d%d6_119/D",harm_[0],harm_[1])); // 01110111
   trEvent_->Branch(Form("C%d%d4_51",harm_[0],harm_[1]),  &CN4_51_,  Form("C%d%d4_51/D",harm_[0],harm_[1])); // 00110011
   trEvent_->Branch(Form("C%d%d2_17",harm_[0],harm_[0]),  &CN2_17_,  Form("C%d%d2_17/D",harm_[0],harm_[0])); // 00010001
   trEvent_->Branch(Form("wC%d%d8",harm_[0],harm_[1]), &wCN8_, Form("wC%d%d8/D",harm_[0],harm_[1]));
   trEvent_->Branch(Form("wC%d%d6_119",harm_[0],harm_[1]),  &wCN6_119_,  Form("wC%d%d6_119/D",harm_[0],harm_[1])); // 01110111
   trEvent_->Branch(Form("wC%d%d4_51",harm_[0],harm_[1]),  &wCN4_51_,  Form("wC%d%d4_51/D",harm_[0],harm_[1])); // 00110011
   trEvent_->Branch(Form("wC%d%d2_17",harm_[0],harm_[0]), &wCN2_17_, Form("wC%d%d2_17/D",harm_[0],harm_[0])); // 00010001 

   if((nsubevt_<=2 && harm_[0]!=harm_[1]) || (nsubevt_>2)) // calculate for SC with 2sub or std method; Or higher cumulants with >2 subevents
   {
     trEvent_->Branch(Form("C%d%d2_33",harm_[0],harm_[1]),  &CN2_33_,  Form("C%d%d2_33/D",harm_[0],harm_[1])); // 00100001
     trEvent_->Branch(Form("C%d%d2_18",harm_[1],harm_[0]),  &CN2_18_,  Form("C%d%d2_18/D",harm_[1],harm_[0])); // 00010010
     trEvent_->Branch(Form("C%d%d2_34",harm_[1],harm_[1]),  &CN2_34_,  Form("C%d%d2_34/D",harm_[1],harm_[1])); // 00100010
     trEvent_->Branch(Form("wC%d%d2_33",harm_[0],harm_[1]), &wCN2_33_, Form("wC%d%d2_33/D",harm_[0],harm_[1])); // 00100001
     trEvent_->Branch(Form("wC%d%d2_18",harm_[1],harm_[0]), &wCN2_18_, Form("wC%d%d2_18/D",harm_[1],harm_[0])); // 00010010
     trEvent_->Branch(Form("wC%d%d2_34",harm_[1],harm_[1]), &wCN2_34_, Form("wC%d%d2_34/D",harm_[1],harm_[1])); // 00100010
   }

   if(nsubevt_>2 && harm_[0]==harm_[1]) // calculate for higher cumulants with >2 subevents
   {
     trEvent_->Branch(Form("C%d%d6_123",harm_[0],harm_[1]),  &CN6_123_,  Form("C%d%d6_123/D",harm_[0],harm_[1])); // 01111011
     trEvent_->Branch(Form("C%d%d6_125",harm_[0],harm_[1]),  &CN6_125_,  Form("C%d%d6_125/D",harm_[0],harm_[1])); // 01111101
     trEvent_->Branch(Form("C%d%d6_126",harm_[0],harm_[1]),  &CN6_126_,  Form("C%d%d6_126/D",harm_[0],harm_[1])); // 01111110
     trEvent_->Branch(Form("C%d%d6_183",harm_[0],harm_[1]),  &CN6_183_,  Form("C%d%d6_183/D",harm_[0],harm_[1])); // 10110111
     trEvent_->Branch(Form("C%d%d6_187",harm_[0],harm_[1]),  &CN6_187_,  Form("C%d%d6_187/D",harm_[0],harm_[1])); // 10111011
     trEvent_->Branch(Form("C%d%d6_189",harm_[0],harm_[1]),  &CN6_189_,  Form("C%d%d6_189/D",harm_[0],harm_[1])); // 10111101
     trEvent_->Branch(Form("C%d%d6_190",harm_[0],harm_[1]),  &CN6_190_,  Form("C%d%d6_190/D",harm_[0],harm_[1])); // 10111110
     trEvent_->Branch(Form("C%d%d6_215",harm_[0],harm_[1]),  &CN6_215_,  Form("C%d%d6_215/D",harm_[0],harm_[1])); // 11010111
     trEvent_->Branch(Form("C%d%d6_219",harm_[0],harm_[1]),  &CN6_219_,  Form("C%d%d6_219/D",harm_[0],harm_[1])); // 11011011 
     trEvent_->Branch(Form("C%d%d6_221",harm_[0],harm_[1]),  &CN6_221_,  Form("C%d%d6_221/D",harm_[0],harm_[1])); // 11011101
     trEvent_->Branch(Form("C%d%d6_222",harm_[0],harm_[1]),  &CN6_222_,  Form("C%d%d6_222/D",harm_[0],harm_[1])); // 11011110
     trEvent_->Branch(Form("C%d%d6_231",harm_[0],harm_[1]),  &CN6_231_,  Form("C%d%d6_231/D",harm_[0],harm_[1])); // 11100111
     trEvent_->Branch(Form("C%d%d6_235",harm_[0],harm_[1]),  &CN6_235_,  Form("C%d%d6_235/D",harm_[0],harm_[1])); // 11101011
     trEvent_->Branch(Form("C%d%d6_237",harm_[0],harm_[1]),  &CN6_237_,  Form("C%d%d6_237/D",harm_[0],harm_[1])); // 11101101
     trEvent_->Branch(Form("C%d%d6_238",harm_[0],harm_[1]),  &CN6_238_,  Form("C%d%d6_238/D",harm_[0],harm_[1])); // 11101110
     trEvent_->Branch(Form("C%d%d4_53",harm_[0],harm_[1]),  &CN4_53_,  Form("C%d%d4_53/D",harm_[0],harm_[1])); // 00110101
     trEvent_->Branch(Form("C%d%d4_54",harm_[0],harm_[1]),  &CN4_54_,  Form("C%d%d4_54/D",harm_[0],harm_[1])); // 00110110
     trEvent_->Branch(Form("C%d%d4_83",harm_[0],harm_[1]),  &CN4_83_,  Form("C%d%d4_83/D",harm_[0],harm_[1])); // 01010011
     trEvent_->Branch(Form("C%d%d4_85",harm_[0],harm_[1]),  &CN4_85_,  Form("C%d%d4_85/D",harm_[0],harm_[1])); // 01010101
     trEvent_->Branch(Form("C%d%d4_86",harm_[0],harm_[1]),  &CN4_86_,  Form("C%d%d4_86/D",harm_[0],harm_[1])); // 01010110
     trEvent_->Branch(Form("C%d%d4_99",harm_[0],harm_[1]),  &CN4_99_,  Form("C%d%d4_99/D",harm_[0],harm_[1])); // 01100011
     trEvent_->Branch(Form("C%d%d4_101",harm_[0],harm_[1]),  &CN4_101_,  Form("C%d%d4_101/D",harm_[0],harm_[1])); // 01100101
     trEvent_->Branch(Form("C%d%d4_102",harm_[0],harm_[1]),  &CN4_102_,  Form("C%d%d4_102/D",harm_[0],harm_[1])); // 01100110

     trEvent_->Branch(Form("wC%d%d6_123",harm_[0],harm_[1]),  &wCN6_123_,  Form("wC%d%d6_123/D",harm_[0],harm_[1])); // 01111011
     trEvent_->Branch(Form("wC%d%d6_125",harm_[0],harm_[1]),  &wCN6_125_,  Form("wC%d%d6_125/D",harm_[0],harm_[1])); // 01111101
     trEvent_->Branch(Form("wC%d%d6_126",harm_[0],harm_[1]),  &wCN6_126_,  Form("wC%d%d6_126/D",harm_[0],harm_[1])); // 01111110
     trEvent_->Branch(Form("wC%d%d6_183",harm_[0],harm_[1]),  &wCN6_183_,  Form("wC%d%d6_183/D",harm_[0],harm_[1])); // 10110111
     trEvent_->Branch(Form("wC%d%d6_187",harm_[0],harm_[1]),  &wCN6_187_,  Form("wC%d%d6_187/D",harm_[0],harm_[1])); // 10111011
     trEvent_->Branch(Form("wC%d%d6_189",harm_[0],harm_[1]),  &wCN6_189_,  Form("wC%d%d6_189/D",harm_[0],harm_[1])); // 10111101
     trEvent_->Branch(Form("wC%d%d6_190",harm_[0],harm_[1]),  &wCN6_190_,  Form("wC%d%d6_190/D",harm_[0],harm_[1])); // 10111110
     trEvent_->Branch(Form("wC%d%d6_215",harm_[0],harm_[1]),  &wCN6_215_,  Form("wC%d%d6_215/D",harm_[0],harm_[1])); // 11010111
     trEvent_->Branch(Form("wC%d%d6_219",harm_[0],harm_[1]),  &wCN6_219_,  Form("wC%d%d6_219/D",harm_[0],harm_[1])); // 11011011 
     trEvent_->Branch(Form("wC%d%d6_221",harm_[0],harm_[1]),  &wCN6_221_,  Form("wC%d%d6_221/D",harm_[0],harm_[1])); // 11011101
     trEvent_->Branch(Form("wC%d%d6_222",harm_[0],harm_[1]),  &wCN6_222_,  Form("wC%d%d6_222/D",harm_[0],harm_[1])); // 11011110
     trEvent_->Branch(Form("wC%d%d6_231",harm_[0],harm_[1]),  &wCN6_231_,  Form("wC%d%d6_231/D",harm_[0],harm_[1])); // 11100111
     trEvent_->Branch(Form("wC%d%d6_235",harm_[0],harm_[1]),  &wCN6_235_,  Form("wC%d%d6_235/D",harm_[0],harm_[1])); // 11101011
     trEvent_->Branch(Form("wC%d%d6_237",harm_[0],harm_[1]),  &wCN6_237_,  Form("wC%d%d6_237/D",harm_[0],harm_[1])); // 11101101
     trEvent_->Branch(Form("wC%d%d6_238",harm_[0],harm_[1]),  &wCN6_238_,  Form("wC%d%d6_238/D",harm_[0],harm_[1])); // 11101110
     trEvent_->Branch(Form("wC%d%d4_53",harm_[0],harm_[1]),  &wCN4_53_,  Form("wC%d%d4_53/D",harm_[0],harm_[1])); // 00110101
     trEvent_->Branch(Form("wC%d%d4_54",harm_[0],harm_[1]),  &wCN4_54_,  Form("wC%d%d4_54/D",harm_[0],harm_[1])); // 00110110
     trEvent_->Branch(Form("wC%d%d4_83",harm_[0],harm_[1]),  &wCN4_83_,  Form("wC%d%d4_83/D",harm_[0],harm_[1])); // 01010011
     trEvent_->Branch(Form("wC%d%d4_85",harm_[0],harm_[1]),  &wCN4_85_,  Form("wC%d%d4_85/D",harm_[0],harm_[1])); // 01010101
     trEvent_->Branch(Form("wC%d%d4_86",harm_[0],harm_[1]),  &wCN4_86_,  Form("wC%d%d4_86/D",harm_[0],harm_[1])); // 01010110
     trEvent_->Branch(Form("wC%d%d4_99",harm_[0],harm_[1]),  &wCN4_99_,  Form("wC%d%d4_99/D",harm_[0],harm_[1])); // 01100011
     trEvent_->Branch(Form("wC%d%d4_101",harm_[0],harm_[1]),  &wCN4_101_,  Form("wC%d%d4_101/D",harm_[0],harm_[1])); // 01100101
     trEvent_->Branch(Form("wC%d%d4_102",harm_[0],harm_[1]),  &wCN4_102_,  Form("wC%d%d4_102/D",harm_[0],harm_[1])); // 01100110
   }
}


Cumulants::~Cumulants()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
Cumulants::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // ----- centrality selection -----
   //// Get calo centrality collection by token
   //edm::Handle< reco::Centrality > centrality;
   //iEvent.getByToken(centralityTags_, centrality);
   //// Get calo centrality bin by token
   //edm::Handle< int > cbin;
   //iEvent.getByToken(centralityBinTags_,cbin);
   //int centBin = *cbin;
   //if(centBin < 0)
   //{
   //    edm::LogWarning ("Invalid value") <<"Invalid centrality value";
   //}


   // ----- Vertex selection -----
   // Get vertex collection by token
   edm::Handle< reco::VertexCollection > vertices;
   iEvent.getByToken(vtxTags_, vertices);
   reco::VertexCollection verticesColl = *vertices;
   if( !vertices->size() ) 
   { 
      edm::LogWarning ("Missing Collection") <<"Invalid or empty vertex collection!";
      return; 
   }

   nvtx_          = 0;     //N valid vertex in collection
   xBestVtx_      = -999.;
   yBestVtx_      = -999.; 
   rhoBestVtx_    = -999.; 
   zBestVtx_      = -999.; //Best vtx coordinates
   xBestVtxError_ = -999.; 
   yBestVtxError_ = -999.; 
   zBestVtxError_ = -999.; //Best vtx error

   // Sort vertex collection if you want to select highest multiplicity vertex as best vertex
   if(isBVselByMult_)
   {
      std::sort(verticesColl.begin(), verticesColl.end(), [](const reco::Vertex &a, const reco::Vertex &b)
      {
         if ( a.tracksSize() == b.tracksSize() ) 
            return a.chi2() < b.chi2();
         return a.tracksSize() > b.tracksSize();
      });
   }

   // Loop over vertices
   for( reco::VertexCollection::const_iterator itVtx = verticesColl.begin();
        itVtx != verticesColl.end();
        ++itVtx )
   {
        // Drop fake vertex and vertex with less than 2 tracks attached to it
        if( !itVtx->isFake() && itVtx->tracksSize()>=2 )
        {
            // x,y,z vertex position
            double xVtx = itVtx->x();
            double yVtx = itVtx->y();
            double zVtx = itVtx->z();
            // x,y,z vertex position error
            double xVtxError = itVtx->xError();
            double yVtxError = itVtx->yError();
            double zVtxError = itVtx->zError();
            // Radial vertex position                                                         
            double rho = sqrt(xVtx*xVtx + yVtx*yVtx);
            // Increase N valid vertex in the collection
            ++nvtx_;

            //Get the first vertex as the best one (greatest sum p_{T}^{2}) 
            if( itVtx == verticesColl.begin() )
            {
                xBestVtx_ = xVtx; 
                yBestVtx_ = yVtx; 
                zBestVtx_ = zVtx; 
                xBestVtxError_ = xVtxError; 
                yBestVtxError_ = yVtxError; 
                zBestVtxError_ = zVtxError;

                rhoBestVtx_ = rho; 
            }
        }
        // Fill vtx histograms
        hXBestVtx_  ->Fill(xBestVtx_);
        hYBestVtx_  ->Fill(yBestVtx_);
        hRhoBestVtx_->Fill(rhoBestVtx_);
        hZBestVtx_  ->Fill(zBestVtx_);
   }

   //Select event using vertex properties
   if ( nvtx_ <= 0 )                               return;
   if ( zBestVtx_ < minvz_ || zBestVtx_ > maxvz_ ) return;
   if ( rhoBestVtx_ > maxrho_ )                    return;


   // ----- Track selection -----
   // Get track collection by token
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(trackTags_, tracks);
   if( !tracks->size() )
   {
       edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
       return;
   }

   noff_ = 0; // Ntrk offline
   // Loop over tracks to compute Noff first
   for( reco::TrackCollection::const_iterator itTrk = tracks->begin();
        itTrk != tracks->end();
        ++itTrk )
   {
       // Select tracks based on proximity to best vertex
       math::XYZPoint bestvtx(xBestVtx_,yBestVtx_,zBestVtx_);
       double dzvtx    = itTrk->dz(bestvtx);
       double dxyvtx   = itTrk->dxy(bestvtx);
       double dzerror  = sqrt(itTrk->dzError()*itTrk->dzError() + zBestVtxError_*zBestVtxError_);
       double dxyerror = sqrt(itTrk->d0Error()*itTrk->d0Error() + xBestVtxError_*yBestVtxError_);
       double pterror  = itTrk->ptError();
       // Get eta, pt, phi and charge of the track
       double eta    = itTrk->eta();
       double pt     = itTrk->pt();
       double phi    = itTrk->phi();
       double charge = itTrk->charge();

       // Select track based on quality
       if( !itTrk->quality(reco::TrackBase::highPurity) ) continue;
       if( fabs(pterror) / pt      > pterrorptnoff_ ) continue;
       if( fabs(dzvtx / dzerror)   > dzdzerrornoff_ ) continue;
       if( fabs(dxyvtx / dxyerror) > d0d0errornoff_ ) continue;
       if( pt < 0.0001 ) continue;
       if( charge == 0 ) continue;


       // Track selection for analysis
       if(eta < -2.4 || eta > 2.4)            continue;
       if(pt < ptnoffmin_ || pt > ptnoffmax_) continue;

       // Increase N valid tracks
       ++noff_;

       // Fill trk histograms
       hEtaNoff_->Fill(eta);
       hPtNoff_ ->Fill(pt);
       hPhiNoff_->Fill(phi);
   }

   //Select event based on Ntrk offline selection
   if( noff_ < noffmin_ || noff_ >= noffmax_) return;

   //Reset QVectors to start fresh
   qN_.reset();
   mult_ = 0; // Event multiplicity
   std::vector<double> val(2,0.);

   // Loop over tracks to compute cumulants and multiplicity
   for( reco::TrackCollection::const_iterator itTrk = tracks->begin();
        itTrk != tracks->end();
        ++itTrk )
   {
       // Select tracks based on proximity to best vertex
       math::XYZPoint bestvtx(xBestVtx_,yBestVtx_,zBestVtx_);
       double dzvtx    = itTrk->dz(bestvtx);
       double dxyvtx   = itTrk->dxy(bestvtx);
       double dzerror  = sqrt(itTrk->dzError()*itTrk->dzError() + zBestVtxError_*zBestVtxError_);
       double dxyerror = sqrt(itTrk->d0Error()*itTrk->d0Error() + xBestVtxError_*yBestVtxError_);
       double pterror  = itTrk->ptError();
       // Get eta, pt, phi and charge of the track
       double eta    = itTrk->eta();
       double pt     = itTrk->pt();
       double phi    = itTrk->phi();
       double charge = itTrk->charge();

       // Select track based on quality
       if( !itTrk->quality(reco::TrackBase::highPurity) ) continue;
       if( fabs(pterror) / pt      > pterrorpt_ ) continue;
       if( fabs(dzvtx / dzerror)   > dzdzerror_ ) continue;
       if( fabs(dxyvtx / dxyerror) > d0d0error_ ) continue;
       if( pt < 0.0001 ) continue;
       if( charge == 0 ) continue;

       // Track selection for analysis
       if(eta < etamin_ || eta > etamax_) continue;
       if(pt < ptmin_ || pt > ptmax_)     continue;

       // Compute weights
       double weight = 0.0;
       if( cweight_ )
       {
           int idx = getEffNoffIndex();
           if( idx < 0 )
           {
               edm::LogError ("Wrong index") <<"Index for efficiency correction not found";
               return;
           }

	   if( feff_ && heff_[idx] ) 
           { 
              if( heff_[idx]->GetBinContent(heff_[idx]->FindBin(eta,pt)) != 0. ) 
                 weight = 1./heff_[idx]->GetBinContent(heff_[idx]->FindBin(eta,pt));
           }
       }

       // Increase N valid tracks
       ++mult_;

       // Fill qvector
       val[0] = pt;
       val[1] = eta;
       qN_.fill(val, phi, weight);

       // Fill trk histograms
       hEtaTrk_->Fill(eta);
       hPtTrk_ ->Fill(pt);
       hPhiTrk_->Fill(phi);
   }


   // ----- Calotower selection -----
   // Get calo tower collection by token
   edm::Handle< CaloTowerCollection > calotowers;
   iEvent.getByToken(caloTowersTags_, calotowers);
   if( !calotowers->size() )
   {
       edm::LogWarning ("Missing Collection") <<"Invalid or empty caloTower collection!";
       return;
   }
   // Loop over caloTowers
   for( CaloTowerCollection::const_iterator itCTow = calotowers->begin();
        itCTow != calotowers->end();
        ++itCTow )
   {
       // Get eta, pt and phi of the calo tower
       double eta  = itCTow->eta();
       double et   = itCTow->et();
       double phi  = itCTow->phi();

       // Select calo tower based on quality
       if( et < 0.01 ) continue;

       // Fill trk histograms
       hEtaCTow_->Fill(eta);
       hEtCTow_ ->Fill(et);
       hPhiCTow_->Fill(phi);
   }

   //Compute cumulants
   //WARNING: Clarity of this step to be improved in the framework
   //The correlators are represented by a binary number where each bit is one of the subset
   //In our case here:
   //   * 17  ~> 00010001
   //   * 51  ~> 00110011
   //   * 119 ~> 01110111
   //   * 255 ~> 11111111
   //
   //For SC with 2 subevent, we need following combinations
   //   * 34  ~> 00100010
   //   * 17  ~> 00010001    
   //For 4 subevent, we need following combinations
   //   * 34  ~> 00100010 for c24
   //   * 33  ~> 00100001 for c24
   //   * 18  ~> 00010010 for c24
   //   * 17  ~> 00010001 for c24   
   //   * 51  ~> 00110011 for c26 
   //   * 53  ~> 00110101 for c26
   //   * 54  ~> 00110110 for c26
   //   * 83  ~> 01010011 for c26
   //   * 85  ~> 01010101 for c26
   //   * 86  ~> 01010110 for c26
   //   * 99  ~> 01100011 for c26
   //   * 101  ~> 01100101 for c26
   //   * 102  ~> 01100110 for c26
   //For 3 subevent, we need following combinations   
   //   * 18  ~> 00010010 for c24
   //   * 17  ~> 00010001 for c24
   //For SC with 3 subevent, we need following combinations
   //   * 34  ~> 00100010 
   //   * 17  ~> 00010001 
   //For SC with 4 subevent, we need following combinations    
   //   * 34  ~> 00100010
   //   * 17  ~> 00010001    
   //As subset on the same eta region are stricly equal in this analyzer (same eta and pT range) it does not matter a lot
   //but one as to keep that in mind for further expansion of the analysis
   cumulant::QVectorMap& qNmap = qN_.getQ();

   cumulant::Correlator c2_17 = cumulant::Correlator(17, qNmap);
   CN2_17_  = c2_17.v.real(); 
   wCN2_17_ = c2_17.w.real();
   cumulant::Correlator c2_18 = cumulant::Correlator(18, qNmap);
   CN2_18_  = c2_18.v.real();
   wCN2_18_ = c2_18.w.real();
   cumulant::Correlator c2_33 = cumulant::Correlator(33, qNmap);
   CN2_33_  = c2_33.v.real();
   wCN2_33_ = c2_33.w.real();
   cumulant::Correlator c2_34 = cumulant::Correlator(34, qNmap);
   CN2_34_  = c2_34.v.real();
   wCN2_34_ = c2_34.w.real();
   cumulant::Correlator c4_51 = cumulant::Correlator(51, qNmap);
   CN4_51_  = c4_51.v.real();
   wCN4_51_ = c4_51.w.real();
   cumulant::Correlator c6_119 = cumulant::Correlator(119, qNmap);
   CN6_119_  = c6_119.v.real();
   wCN6_119_ = c6_119.w.real();
   cumulant::Correlator c8 = cumulant::Correlator(255, qNmap);
   CN8_  = c8.v.real();
   wCN8_ = c8.w.real();

   if(nsubevt_>2)
   {
     cumulant::Correlator c4_53 = cumulant::Correlator(53, qNmap);
     CN4_53_  = c4_53.v.real();
     wCN4_53_ = c4_53.w.real();
     cumulant::Correlator c4_54 = cumulant::Correlator(54, qNmap);
     CN4_54_  = c4_54.v.real();
     wCN4_54_ = c4_54.w.real();
     cumulant::Correlator c4_83 = cumulant::Correlator(83, qNmap);
     CN4_83_  = c4_83.v.real();
     wCN4_83_ = c4_83.w.real();
     cumulant::Correlator c4_85 = cumulant::Correlator(85, qNmap);
     CN4_85_  = c4_85.v.real();
     wCN4_85_ = c4_85.w.real();
     cumulant::Correlator c4_86 = cumulant::Correlator(86, qNmap);
     CN4_86_  = c4_86.v.real();
     wCN4_86_ = c4_86.w.real();
     cumulant::Correlator c4_99 = cumulant::Correlator(99, qNmap);
     CN4_99_  = c4_99.v.real();
     wCN4_99_ = c4_99.w.real();
     cumulant::Correlator c4_101 = cumulant::Correlator(101, qNmap);
     CN4_101_  = c4_101.v.real();
     wCN4_101_ = c4_101.w.real();
     cumulant::Correlator c4_102 = cumulant::Correlator(102, qNmap);
     CN4_102_  = c4_102.v.real();
     wCN4_102_ = c4_102.w.real();

     cumulant::Correlator c6_123 = cumulant::Correlator(123, qNmap);
     CN6_123_  = c6_123.v.real();
     wCN6_123_ = c6_123.w.real();
     cumulant::Correlator c6_125 = cumulant::Correlator(125, qNmap);
     CN6_125_  = c6_125.v.real();
     wCN6_125_ = c6_125.w.real();
     cumulant::Correlator c6_126 = cumulant::Correlator(126, qNmap);
     CN6_126_  = c6_126.v.real();
     wCN6_126_ = c6_126.w.real();
     cumulant::Correlator c6_183 = cumulant::Correlator(183, qNmap);
     CN6_183_  = c6_183.v.real();
     wCN6_183_ = c6_183.w.real();
     cumulant::Correlator c6_187 = cumulant::Correlator(187, qNmap);
     CN6_187_  = c6_187.v.real();
     wCN6_187_ = c6_187.w.real();
     cumulant::Correlator c6_189 = cumulant::Correlator(189, qNmap);
     CN6_189_  = c6_189.v.real();
     wCN6_189_ = c6_189.w.real();
     cumulant::Correlator c6_190 = cumulant::Correlator(190, qNmap);
     CN6_190_  = c6_190.v.real();
     wCN6_190_ = c6_190.w.real();
     cumulant::Correlator c6_215 = cumulant::Correlator(215, qNmap);
     CN6_215_  = c6_215.v.real();
     wCN6_215_ = c6_215.w.real();
     cumulant::Correlator c6_219 = cumulant::Correlator(219, qNmap);
     CN6_219_  = c6_219.v.real();
     wCN6_219_ = c6_219.w.real();
     cumulant::Correlator c6_221 = cumulant::Correlator(221, qNmap);
     CN6_221_  = c6_221.v.real();
     wCN6_221_ = c6_221.w.real();
     cumulant::Correlator c6_222 = cumulant::Correlator(222, qNmap);
     CN6_222_  = c6_222.v.real();
     wCN6_222_ = c6_222.w.real();
     cumulant::Correlator c6_231 = cumulant::Correlator(231, qNmap);
     CN6_231_  = c6_231.v.real();
     wCN6_231_ = c6_231.w.real();
     cumulant::Correlator c6_235 = cumulant::Correlator(235, qNmap);
     CN6_235_  = c6_235.v.real();
     wCN6_235_ = c6_235.w.real();
     cumulant::Correlator c6_237 = cumulant::Correlator(237, qNmap);
     CN6_237_  = c6_237.v.real();
     wCN6_237_ = c6_237.w.real();
     cumulant::Correlator c6_238 = cumulant::Correlator(238, qNmap);
     CN6_238_  = c6_238.v.real();
     wCN6_238_ = c6_238.w.real();
   }

   // Fill TTree
   //cent_ = centBin;
   cent_ = 1;
   if(mult_ > 0) trEvent_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
//void 
//Cumulants::beginJob()
//{
//}

// ------------ method called once each job just after ending the event loop  ------------
void 
Cumulants::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Cumulants::fillDescriptions(edm::ConfigurationDescriptions& descriptions) 
{
   //The following says we do not know what parameters are allowed so do no validation
   // Please change this to state exactly what you do use, even if it is no parameters
   edm::ParameterSetDescription desc;
   desc.setUnknown();
   descriptions.addDefault(desc);
}

int
Cumulants::getEffNoffIndex() 
{
   for( int idx = 0; idx < (int) effmultbin_.size() - 1; ++idx )
   {
      if( noff_ >= effmultbin_[idx] && noff_ < effmultbin_[idx+1] ) return idx;
   }
   return -1;  
}

//define this as a plug-in
DEFINE_FWK_MODULE(Cumulants);
