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
  //track selection
  pTmin_(iConfig.getUntrackedParameter<double>("pTminTrk")),
  pTmax_(iConfig.getUntrackedParameter<double>("pTmaxTrk"))
{
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
   trEvent_ = fs->make<TTree>("trEvent", "trEvent");
   trEvent_->Branch("centrality", &cent_, "centrality/I");
   trEvent_->Branch("nVertex",    &nVtx_, "nVertex/I");
   trEvent_->Branch("nTrk",       &nTrk_, "nTrk/I");
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

   int nvtx = 0; // N valid vertex in collection
   double xBestVtx = -999., yBestVtx = -999., rhoBestVtx = -999., zBestVtx = -999.; //Best vtx coordinates
   double xBestVtxError = -999., yBestVtxError = -999., zBestVtxError = -999.; //Best vtx error

   // Loop over vertices
   for( reco::VertexCollection::const_iterator itVtx = vertices->begin();
        itVtx != vertices->end();
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
            ++nvtx;

            //Get the first vertex as the best one (greatest sum p_{T}^{2}) 
            if( itVtx == vertices->begin() )
            {
                xBestVtx = xVtx; 
                yBestVtx = yVtx; 
                zBestVtx = zVtx; 
                xBestVtxError = xVtxError; 
                yBestVtxError = yVtxError; 
                zBestVtxError = zVtxError;

                rhoBestVtx = rho; 
            }
        }
        // Fill vtx histograms
        hXBestVtx_  ->Fill(xBestVtx);
        hYBestVtx_  ->Fill(yBestVtx);
        hRhoBestVtx_->Fill(rhoBestVtx);
        hZBestVtx_  ->Fill(zBestVtx);
   }

   // ----- Track selection -----
   // Get track collection by token
   edm::Handle< reco::TrackCollection > tracks;
   iEvent.getByToken(trackTags_, tracks);
   if( !tracks->size() )
   {
       edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
       return;
   }

   int ntrk = 0; // N valid tracks in collection

   // Loop over tracks
   for( reco::TrackCollection::const_iterator itTrk = tracks->begin();
        itTrk != tracks->end();
        ++itTrk )
   {
       // Select tracks based on proximity to best vertex
       math::XYZPoint bestvtx(xBestVtx,yBestVtx,zBestVtx);
       double dzvtx    = itTrk->dz(bestvtx);
       double dxyvtx   = itTrk->dxy(bestvtx);
       double dzerror  = sqrt(itTrk->dzError()*itTrk->dzError() + zBestVtxError*zBestVtxError);
       double dxyerror = sqrt(itTrk->d0Error()*itTrk->d0Error() + xBestVtxError*yBestVtxError);
       double pterror  = itTrk->ptError();
       // Get eta, pt, phi and charge of the track
       double eta    = itTrk->eta();
       double pt     = itTrk->pt();
       double phi    = itTrk->phi();
       double charge = itTrk->charge();

       // Select track based on quality
       if( !itTrk->quality(reco::TrackBase::highPurity) ) continue;
       if( fabs(pterror) / pt      > 0.1 ) continue;
       if( fabs(dzvtx / dzerror)   > 3.0 ) continue;
       if( fabs(dxyvtx / dxyerror) > 3.0 ) continue;
       if( pt < 0.0001 ) continue;
       if( charge == 0 ) continue;


       // Track selection for analysis
       if(pt < pTmin_ || pt > pTmax_) continue;

       // Increase N valid tracks
       ++ntrk;
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

   // Fill TTree
   cent_ = centBin;
   nVtx_ = nvtx;
   nTrk_ = ntrk;
   trEvent_->Fill();
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

//define this as a plug-in
DEFINE_FWK_MODULE(ChargeDepAndPtCorr);
