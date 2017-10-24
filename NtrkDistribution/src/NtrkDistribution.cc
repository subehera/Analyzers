// -*- C++ -*-
//
// Package:    NtrkDistribution
// Class:      NtrkDistribution
// 
/**\class NtrkDistribution NtrkDistribution.cc Analyzers/NtrkDistribution/src/NtrkDistribution.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Maxime Guilbaud,32 4-A05,+41227674763,
//         Created:  Tue Oct 24 17:35:19 CEST 2017
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

// CMSSW include files
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

// user include files
#include "Analyzers/NtrkDistribution/interface/NtrkDistribution.h"
//
// constructors and destructor
//
NtrkDistribution::NtrkDistribution(const edm::ParameterSet& iConfig) :
  //tracks
  trackTags_(iConfig.getParameter<edm::InputTag>("tracks")),
  //vertex
  vtxTags_(iConfig.getParameter<edm::InputTag>("vertex")),
  //caloTower
  caloTowersTags_(iConfig.getParameter<edm::InputTag>("caloTower")),
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
  //file acc & eff & fake
  fname_(iConfig.getUntrackedParameter<edm::InputTag>("fname")),
  effmultbin_(iConfig.getUntrackedParameter< std::vector<int> >("effmultbin"))
{
   //now do what ever initialization is needed
   TString filename(fname_.label().c_str());
   feff_ = 0x0;
   if(!filename.IsNull())
   {
      edm::FileInPath fip(Form("Analyzers/NtrkDistribution/data/EFF/%s",filename.Data()));
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
   }

   //Ouptut
   edm::Service<TFileService> fs;
   // Histograms
   TFileDirectory fVtxHist  = fs->mkdir("Vertex");
   hXBestVtx_   = fVtxHist.make<TH1F>("hXvtx", "", 800, -0.2, 0.2);
   hYBestVtx_   = fVtxHist.make<TH1F>("hYvtx", "", 800, -0.2, 0.2);
   hRhoBestVtx_ = fVtxHist.make<TH1F>("hRvtx", "", 800, -0.2, 0.2);
   hZBestVtx_   = fVtxHist.make<TH1F>("hZvtx", "", 600, -30., 30.);
   TFileDirectory fTrkHist  = fs->mkdir("Tracks");
   hTrk_    = fTrkHist.make<TH1F>("hMult", "", 10000, 0., 10000.);
   hEtaTrk_ = fTrkHist.make<TH1F>("hEtatrk", "", 300, -3.,   3.);
   hPtTrk_  = fTrkHist.make<TH1F>("hPttrk",  "", 100,  0.,  10.);
   hPhiTrk_ = fTrkHist.make<TH1F>("hPhitrk", "", 640, -3.2,  3.2);
   hNoff_    = fTrkHist.make<TH1F>("hNoff", "", 10000, 0., 10000.);
   hEtaNoff_ = fTrkHist.make<TH1F>("hEtaNoff", "", 300, -3.,   3.);
   hPtNoff_  = fTrkHist.make<TH1F>("hPtNoff",  "", 100,  0.,  10.);
   hPhiNoff_ = fTrkHist.make<TH1F>("hPhiNoff", "", 640, -3.2,  3.2);
   TFileDirectory fCorrHist  = fs->mkdir("Corrected");
   hTrkCorr_    = fCorrHist.make<TH1F>("hMultCorr", "", 10000, 0., 10000.);
   hEtaTrkCorr_ = fCorrHist.make<TH1F>("hEtatrk", "", 300, -3.,   3.);
   hPtTrkCorr_  = fCorrHist.make<TH1F>("hPttrk",  "", 100,  0.,  10.);
   hPhiTrkCorr_ = fCorrHist.make<TH1F>("hPhitrk", "", 640, -3.2,  3.2);
   hNoffCorr_    = fCorrHist.make<TH1F>("hNoffCorr", "", 10000, 0., 10000.);
   hEtaNoffCorr_ = fCorrHist.make<TH1F>("hEtaNoff", "", 300, -3.,   3.);
   hPtNoffCorr_  = fCorrHist.make<TH1F>("hPtNoff",  "", 100,  0.,  10.);
   hPhiNoffCorr_ = fCorrHist.make<TH1F>("hPhiNoff", "", 640, -3.2,  3.2);
   TFileDirectory fCTowHist = fs->mkdir("CaloTowers");
   hEtaCTow_ = fCTowHist.make<TH1F>("hEtatow", "", 120, -6.,   6.);
   hEtCTow_  = fCTowHist.make<TH1F>("hEttow",  "", 100,  0.,  10.);
   hPhiCTow_ = fCTowHist.make<TH1F>("hPhitow", "", 640, -3.2,  3.2);
}


NtrkDistribution::~NtrkDistribution()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
NtrkDistribution::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // ----- Vertex selection -----
   // Get vertex collection by token
   edm::Handle< reco::VertexCollection > vertices;
   iEvent.getByLabel(vtxTags_, vertices);
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
        if( !itVtx->isFake() && itVtx->tracksSize() >=2 )
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
   iEvent.getByLabel(trackTags_, tracks);
   if( !tracks->size() )
   {
       edm::LogWarning ("Missing Collection") <<"Invalid or empty track collection!";
       return;
   }

   noff_     = 0; // Ntrk offline
   noffcorr_ = 0; // Ntrk offline corrected
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

       // Compute weights
       double weight = 0.0;

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

       noffcorr_ += weight;

       // Fill trk histograms
       hNoff_->Fill(noff_);
       hEtaNoff_->Fill(eta);
       hPtNoff_ ->Fill(pt);
       hPhiNoff_->Fill(phi);
       hNoffCorr_->Fill(noffcorr_);
       hEtaNoffCorr_->Fill(eta, weight);
       hPtNoffCorr_ ->Fill(pt, weight);
       hPhiNoffCorr_->Fill(phi, weight);
   }

   //Select event based on Ntrk offline selection
   if( noff_ < noffmin_ || noff_ >= noffmax_) return;

   mult_ = 0;     // Event multiplicity
   multcorr_ = 0.; // Event multiplicity corrected
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

       // Increase N valid tracks
       ++mult_;
       multcorr_ += weight;
       //std::cout << mult_ << " " << multcorr_ << std::endl;
       
       // Fill trk histograms
       hTrk_->Fill(mult_);
       hEtaTrk_->Fill(eta);
       hPtTrk_ ->Fill(pt);
       hPhiTrk_->Fill(phi);
       hTrkCorr_->Fill(multcorr_);
       hEtaTrkCorr_->Fill(eta, weight);
       hPtTrkCorr_ ->Fill(pt, weight);
       hPhiTrkCorr_->Fill(phi, weight);
   }


   // ----- Calotower selection -----
   // Get calo tower collection by token
   edm::Handle< CaloTowerCollection > calotowers;
   iEvent.getByLabel(caloTowersTags_, calotowers);
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


// ------------ method called once each job just before starting event loop  ------------
void 
NtrkDistribution::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
NtrkDistribution::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
NtrkDistribution::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

int
NtrkDistribution::getEffNoffIndex() 
{
   for( int idx = 0; idx < (int) effmultbin_.size() - 1; ++idx )
   {
      if( noff_ >= effmultbin_[idx] && noff_ < effmultbin_[idx+1] ) return idx;
   }
   return -1;  
}

//define this as a plug-in
DEFINE_FWK_MODULE(NtrkDistribution);
