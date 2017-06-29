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

#include "Analyzers/Cumulants/interface/MultiCumulants/correlations/Types.hh"
#include "Analyzers/Cumulants/interface/MultiCumulants/correlations/Result.hh"
#include "Analyzers/Cumulants/interface/MultiCumulants/correlations/QVector.hh"
#include "Analyzers/Cumulants/interface/MultiCumulants/correlations/recursive/FromQVector.hh"
#include "Analyzers/Cumulants/interface/MultiCumulants/correlations/recurrence/FromQVector.hh"

#include "Analyzers/Cumulants/interface/MultiCumulants/MultiCumulants/Subsets.h"
#include "Analyzers/Cumulants/interface/MultiCumulants/MultiCumulants/QVector.h"

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
  //track selection
  pTmin_(iConfig.getUntrackedParameter<double>("pTminTrk")),
  pTmax_(iConfig.getUntrackedParameter<double>("pTmaxTrk")),
  //harmonic order
  harm_(iConfig.getUntrackedParameter<int>("harm"))
{
   // Now do what ever initialization is needed
   usesResource("TFileService");
   edm::Service<TFileService> fs;
   // Histograms
   TFileDirectory fVtxHist  = fs->mkdir("Vertex");
   hXBestVtx_   = fVtxHist.make<TH1F>("hXvtx", "", 800, -0.2, 0.2);
   hYBestVtx_   = fVtxHist.make<TH1F>("hYvtx", "", 800, -0.2, 0.2);
   hRhoBestVtx_ = fVtxHist.make<TH1F>("hRvtx", "", 800, -0.2, 0.2);
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
   //cent_ = centBin;
   cent_ = 1;
   nVtx_ = nvtx;
   nTrk_ = ntrk;
   trEvent_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
Cumulants::beginJob()
{
        //Init standard method
        correlations::QVector qN(0, 0, false);
        correlations::HarmonicVector hcN;
        correlations::FromQVector *cqN;
        hcN = correlations::HarmonicVector(8);
        hcN[0] =  1*harm_;
        hcN[1] = -1*harm_;
        hcN[2] =  1*harm_;
        hcN[3] = -1*harm_;
        hcN[4] =  1*harm_;
        hcN[5] = -1*harm_;
        hcN[6] =  1*harm_;
        hcN[7] = -1*harm_;
        qN.resize(hcN);
        cqN = new correlations::recurrence::FromQVector(qN);


        //Init subset for subevent method
        cumulant::Subset sub1(2);
        sub1.set(0, "pt", 0.3, 3.0);
        sub1.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub2(2);
        sub2.set(0, "pt", 0.3, 3.0);
        sub2.set(1, "eta", -2.4, 0.);
        cumulant::Subset sub3(2);
        sub3.set(0, "pt", 0.3, 3.0);
        sub3.set(1, "eta", 0., 2.4);
        cumulant::Subset sub4(2);
        sub4.set(0, "pt", 0.3, 3.0);
        sub4.set(1, "eta", 0., 2.4);

        //Init 2-p sub-event method
        cumulant::Set set2(2);
        set2.setSubsetParams(0, sub1);
        set2.setSubsetParams(1, sub3);

        //Init 4-p sub-event method
        cumulant::Set set4(4);
        set4.setSubsetParams(0, sub1);
        set4.setSubsetParams(1, sub2);
        set4.setSubsetParams(2, sub3);
        set4.setSubsetParams(3, sub4);

        //Init 2-p method with subset
        HarmonicVector h(2);
        h[0] =  1*harm_;
        h[1] = -1*harm_;
        //cumulant::QVectorSet q(h, set2, false);
        //cumulant::impl1::QVectorSet q(h, set2, false);
        cumulant::impl2::QVectorSet q(h, set2, false);
        //Init 4-p method with subset
        HarmonicVector h4(4);
        h4[0] =  1*harm_;
        h4[1] =  1*harm_;
        h4[2] = -1*harm_;
        h4[3] = -1*harm_;
        //cumulant::QVectorSet q4(h4, set4, false);
        //cumulant::impl1::QVectorSet q4(h4, set4, false);
        cumulant::impl2::QVectorSet q4(h4, set4, false);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Cumulants::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Cumulants::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Cumulants);
