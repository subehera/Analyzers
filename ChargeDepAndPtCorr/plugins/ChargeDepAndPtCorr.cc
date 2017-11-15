// -*- C++ -*-
//
// Package:    Analyzers/ChargeDepAndPtCorr
// Class:      ChargeDepAndPtCorr
// 
/**\class ChargeDepAndPtCorr ChargeDepAndPtCorr.cc Analyzers/ChargeDepAndPtCorr/plugins/ChargeDepAndPtCorr.cc

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
#include "Analyzers/ChargeDepAndPtCorr/interface/ChargeDepAndPtCorr.h"


//
// constructors and destructor
//
ChargeDepAndPtCorr::ChargeDepAndPtCorr(const edm::ParameterSet& iConfig) :
  //tracks
  trackTags_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
  //vertex
  vtxTags_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex"))),
  //caloTower
  caloTowersTags_(consumes<CaloTowerCollection>(iConfig.getParameter<edm::InputTag>("caloTower"))),
  //centrality
  centralityTags_(consumes<reco::Centrality>(iConfig.getParameter<edm::InputTag>("centralitySrc"))),
  centralityBinTags_(consumes<int>(iConfig.getParameter<edm::InputTag>("centralityBinSrc"))),
  //Eff/Fake correction
  cweight_(iConfig.getUntrackedParameter<bool>("cweight")),
  fname_(iConfig.getUntrackedParameter<edm::InputTag>("fname")),
  effCorrByCent_(iConfig.getUntrackedParameter<bool>("effCorrByCent")),
  effCorrBinMin_(iConfig.getUntrackedParameter< std::vector< int > >("effCorrBinMin")),
  effCorrBinMax_(iConfig.getUntrackedParameter< std::vector< int > >("effCorrBinMax")),
  //vertex selection
  nTrkAssoToVtx_(iConfig.getUntrackedParameter<unsigned int>("nTrkAssoToVtx")),
  selectVtxByMult_(iConfig.getUntrackedParameter<bool>("selectVtxByMult")),
  //track selection
  dzdzerror_(iConfig.getUntrackedParameter<double>("dzdzerror")),
  d0dz0rror_(iConfig.getUntrackedParameter<double>("d0dz0rror")),
  pTerrorpT_(iConfig.getUntrackedParameter<double>("pTerrorpT")),
  pTmin_trg_(iConfig.getUntrackedParameter< std::vector< double > >("pTminTrk_trg")),
  pTmax_trg_(iConfig.getUntrackedParameter< std::vector< double > >("pTmaxTrk_trg")),
  pTmin_asso_(iConfig.getUntrackedParameter< std::vector< double > >("pTminTrk_asso")),
  pTmax_asso_(iConfig.getUntrackedParameter< std::vector< double > >("pTmaxTrk_asso"))
{
   //file acc & eff
   TString filename(fname_.label().c_str());
   feff_ = 0x0;
   //heff_ = 0x0;
   if(cweight_ && !filename.IsNull())
   {
      edm::FileInPath fip(Form("%s",filename.Data()));
      feff_ = new TFile(fip.fullPath().c_str(),"READ");
      heff_.resize(feff_->GetNkeys());
      for(unsigned int ik = 0; ik < heff_.size(); ++ik)
      {
          heff_[ik] = (TH2D*) feff_->Get(feff_->GetListOfKeys()->At(ik)->GetName());
      }
   }

   // Now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   // Histograms
   TFileDirectory fVtxHist  = fs->mkdir("Vertex");
   hXBestVtx_   = fVtxHist.make<TH1F>("hXvtx", "", 60,   -3.,  3.);
   hYBestVtx_   = fVtxHist.make<TH1F>("hYvtx", "", 60,   -3.,  3.);
   hRhoBestVtx_ = fVtxHist.make<TH1F>("hRvtx", "", 600,  -3.,  3.);
   hZBestVtx_   = fVtxHist.make<TH1F>("hZvtx", "", 600, -30., 30.);
   TFileDirectory fTrkHist  = fs->mkdir("Tracks");
   hEtaTrk_ = fTrkHist.make<TH1F>("hEtatrk", "", 300, -3.,   3.);
   hPtTrk_  = fTrkHist.make<TH1F>("hPttrk",  "", 100,  0.,  10.);
   hPhiTrk_ = fTrkHist.make<TH1F>("hPhitrk", "", 640, -3.2,  3.2);
   TFileDirectory fCTowHist = fs->mkdir("CaloTowers");
   hEtaCTow_ = fCTowHist.make<TH1F>("hEtatow", "", 120, -6.,   6.);
   hEtCTow_  = fCTowHist.make<TH1F>("hEttow",  "", 100,  0.,  10.);
   hPhiCTow_ = fCTowHist.make<TH1F>("hPhitow", "", 640, -3.2,  3.2);
   // TTree
   //trEvent_ = fs->make<TTree>("trEvent", "trEvent");
   //trEvent_->Branch("centrality", &cent_, "centrality/I");
   //trEvent_->Branch("nTrk",       &nTrk_, "nTrk/I");
}


ChargeDepAndPtCorr::~ChargeDepAndPtCorr()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
ChargeDepAndPtCorr::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // ----- centrality selection -----
   // Get calo centrality collection by token
   edm::Handle< reco::Centrality > centrality;
   iEvent.getByToken(centralityTags_, centrality);
   // Get calo centrality bin by token
   edm::Handle< int > cbin;
   iEvent.getByToken(centralityBinTags_,cbin);
   int centBin = *cbin;
   if(centBin < 0)
   {
       edm::LogWarning ("Invalid value") <<"Invalid centrality value";
   }


   // ----- Vertex selection -----
   // Get vertex collection by token
   edm::Handle< reco::VertexCollection > vertices;
   iEvent.getByToken(vtxTags_, vertices);
   if( !vertices->size() ) 
   { 
      edm::LogWarning ("Missing Collection") <<"Invalid or empty vertex collection!";
      return; 
   }

   nVtx_ = 0; // N valid vertex in collection
   xBestVtx_   = -999.; //Best X vtx coordinates
   yBestVtx_   = -999.; //Best Y vtx coordinates
   zBestVtx_   = -999.; //Best Z vtx coordinates
   rhoBestVtx_ = -999.; //Best transverse vtx coordinates
   xBestVtxError_ = -999.; //Best X vtx error 
   yBestVtxError_ = -999.; //Best Y vtx error 
   zBestVtxError_ = -999.; //Best Z vtx error

   // Loop over vertices
   LoopVertices(iEvent, iSetup);

   // ----- Track selection -----
   LoopTracks(iEvent, iSetup, true);
   LoopTracks(iEvent, iSetup, false);

   // ----- Calotower selection -----
   LoopCaloTower(iEvent, iSetup);

   // Fill TTree
   //cent_ = centBin;
   //trEvent_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
ChargeDepAndPtCorr::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ChargeDepAndPtCorr::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ChargeDepAndPtCorr::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

void 
ChargeDepAndPtCorr::LoopVertices(const edm::Event& iEvent, 
                                 const edm::EventSetup& iSetup)
{

   edm::Handle< reco::VertexCollection > vertices;
   iEvent.getByToken(vtxTags_, vertices);
   if(!vertices->size())
   {
      std::cout<<"Invalid or empty vertex collection!"<<std::endl;
      return;
   }

   reco::VertexCollection recoVertices = *vertices;

   if(selectVtxByMult_)
   {
       std::sort( recoVertices.begin(),
                  recoVertices.end(),
                  [](const reco::Vertex &a, const reco::Vertex &b)
                  {
                     if ( a.tracksSize() == b.tracksSize() ) return a.chi2() < b.chi2();
                          return a.tracksSize() > b.tracksSize();
                  }
                );
   }

   for( reco::VertexCollection::const_iterator itVtx = recoVertices.begin();
        itVtx != recoVertices.end();
        ++itVtx )
   {
        // Drop fake vertex and vertex with less than 2 tracks attached to it
        if( !itVtx->isFake() && itVtx->tracksSize() >= nTrkAssoToVtx_ )
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
            ++nVtx_;

            //Get the first vertex as the best one (greatest sum p_{T}^{2}) 
            if( itVtx == vertices->begin() )
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
}

void 
ChargeDepAndPtCorr::LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, 
                               bool istrg)
{
   // Get track collection by token
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(trackTags_, tracks);
   if( !tracks->size() )
   {
       edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
       return;
   }

   nTrk_ = 0; // N valid tracks in collection

   // Loop over tracks
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
       if( fabs(pterror) / pt      > dzdzerror_ ) continue;
       if( fabs(dzvtx / dzerror)   > d0dz0rror_ ) continue;
       if( fabs(dxyvtx / dxyerror) > pTerrorpT_ ) continue;
       if( pt < 0.0001 ) continue;
       if( charge == 0 ) continue;


       // Track selection for analysis
       if(pt < pTmin_trg_[0] || pt > pTmax_trg_[0]) continue;

       // Increase N valid tracks
       ++nTrk_;
       // Fill trk histograms
       hEtaTrk_->Fill(eta);
       hPtTrk_ ->Fill(pt);
       hPhiTrk_->Fill(phi);
   }
}

void 
ChargeDepAndPtCorr::LoopCaloTower(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
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
}

double ChargeDepAndPtCorr::GetEffWeight(double eta, double pt, int evtclass)
{
   double effweight = 1.0;

   //effweight = heff_[evtclass]->GetBinContent(heff_[evtclass]->FindBin(eta,pt));
   return effweight;
}

//define this as a plug-in
DEFINE_FWK_MODULE(ChargeDepAndPtCorr);
