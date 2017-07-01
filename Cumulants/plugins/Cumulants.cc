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

//
// constructors and destructor
//
Cumulants::Cumulants(const edm::ParameterSet& iConfig) :
  //tracks
  trackTags_(consumes<reco::TrackCollection>(iConfig.getParameter<edm::InputTag>("tracks"))),
  //vertex
  vtxTags_(consumes<reco::VertexCollection>(iConfig.getParameter<edm::InputTag>("vertex"))),
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
  //harmonic order
  harm_(iConfig.getUntrackedParameter<int>("harm")),
  cweight_(iConfig.getUntrackedParameter<bool>("cweight")),
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
   }

   //Init cumulants
   cumulant::Subset sub_1(2);
   sub_1.set(0, "pt", 0.3, 3.0);
   sub_1.set(1, "eta", -2.4, 0.);
   cumulant::Subset sub_2(2);
   sub_2.set(0, "pt", 0.3, 3.0);
   sub_2.set(1, "eta", -2.4, 0.);
   cumulant::Subset sub_3(2);
   sub_3.set(0, "pt", 0.3, 3.0);
   sub_3.set(1, "eta", 0., 2.4);
   cumulant::Subset sub_4(2);
   sub_4.set(0, "pt", 0.3, 3.0);
   sub_4.set(1, "eta", 0., 2.4);

   //Init 2-p sub-event method
   cumulant::Set set2p(2);
   set2p.setSubsetParams(0, sub_1);
   set2p.setSubsetParams(1, sub_3);
   HarmonicVector h2p(2);
   h2p[0] =  1*harm_;
   h2p[1] = -1*harm_;
   
   //Init 4-p sub-event method
   cumulant::Set set4p(4);
   set4p.setSubsetParams(0, sub_1);
   set4p.setSubsetParams(1, sub_2);
   set4p.setSubsetParams(2, sub_3);
   set4p.setSubsetParams(3, sub_4);
   HarmonicVector h4p(4);
   h4p[0] =  1*harm_;
   h4p[1] =  1*harm_;
   h4p[2] = -1*harm_;
   h4p[3] = -1*harm_;

   q2p_ = cumulant::impl2::QVectorSet(h2p, set2p, cweight_);
   q4p_ = cumulant::impl2::QVectorSet(h4p, set4p, cweight_);

   //Ouptut
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
   hEtaNoff_ = fTrkHist.make<TH1F>("hEtaNoff", "", 300, -3.,   3.);
   hPtNoff_  = fTrkHist.make<TH1F>("hPtNoff",  "", 100,  0.,  10.);
   hPhiNoff_ = fTrkHist.make<TH1F>("hPhiNoff", "", 640, -3.2,  3.2);
   // TTree
   trEvent_ = fs->make<TTree>("trEvent", "trEvent");
   trEvent_->Branch("nVtx",       &nvtx_, "nVtx/I");
   trEvent_->Branch("Noff",       &noff_, "Noff/I");
   trEvent_->Branch("Mult",       &mult_, "Mult/I");
   trEvent_->Branch(Form("C%d4",harm_),  &CN4_,  Form("C%d4/D",harm_));
   trEvent_->Branch(Form("C%d2",harm_),  &CN2_,  Form("C%d2/D",harm_));
   trEvent_->Branch(Form("wC%d4",harm_), &wCN4_, Form("wC%d4/D",harm_));
   trEvent_->Branch(Form("wC%d2",harm_), &wCN2_, Form("wC%d2/D",harm_));
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
   q2p_.reset();
   q4p_.reset();
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
       q2p_.fill(val, phi, weight);
       q4p_.fill(val, phi, weight);

       // Fill trk histograms
       hEtaTrk_->Fill(eta);
       hPtTrk_ ->Fill(pt);
       hPhiTrk_->Fill(phi);
   }


   //Compute cumulants
   CN2_  = (q2p_.getQ()[0][0].getQV()*q2p_.getQ()[0][1].getQV()).real() - q2p_.getQ()[1][0].getQV().real();
   wCN2_ = (q2p_.getQ()[0][0].getW() *q2p_.getQ()[0][1].getW()).real()  - q2p_.getQ()[1][0].getW().real();

   CN4_ = (q4p_.getQ()[0][0].getQV()*q4p_.getQ()[0][1].getQV()*q4p_.getQ()[0][2].getQV()*q4p_.getQ()[0][3].getQV()).real()
        - (q4p_.getQ()[1][0].getQV()*q4p_.getQ()[0][2].getQV()*q4p_.getQ()[0][3].getQV()).real()
        - (q4p_.getQ()[1][1].getQV()*q4p_.getQ()[0][1].getQV()*q4p_.getQ()[0][3].getQV()).real()
        - (q4p_.getQ()[1][2].getQV()*q4p_.getQ()[0][0].getQV()*q4p_.getQ()[0][3].getQV()).real()
        - (q4p_.getQ()[1][3].getQV()*q4p_.getQ()[0][1].getQV()*q4p_.getQ()[0][2].getQV()).real()
        - (q4p_.getQ()[1][4].getQV()*q4p_.getQ()[0][0].getQV()*q4p_.getQ()[0][2].getQV()).real()
        - (q4p_.getQ()[1][5].getQV()*q4p_.getQ()[0][0].getQV()*q4p_.getQ()[0][1].getQV()).real()
        + (q4p_.getQ()[1][0].getQV()*q4p_.getQ()[1][5].getQV()).real()
        + (q4p_.getQ()[1][1].getQV()*q4p_.getQ()[1][4].getQV()).real()
        + (q4p_.getQ()[1][2].getQV()*q4p_.getQ()[1][3].getQV()).real()
        + 2*(q4p_.getQ()[2][0].getQV()*q4p_.getQ()[0][3].getQV()).real()
        + 2*(q4p_.getQ()[2][1].getQV()*q4p_.getQ()[0][2].getQV()).real()
        + 2*(q4p_.getQ()[2][2].getQV()*q4p_.getQ()[0][1].getQV()).real()
        + 2*(q4p_.getQ()[2][3].getQV()*q4p_.getQ()[0][0].getQV()).real()
        - 6*q4p_.getQ()[3][0].getQV().real();
   wCN4_ = q4p_.getQ()[0][0].getW().real()*q4p_.getQ()[0][1].getW().real()*q4p_.getQ()[0][2].getW().real()*q4p_.getQ()[0][3].getW().real()
         - q4p_.getQ()[1][0].getW().real()*q4p_.getQ()[0][2].getW().real()*q4p_.getQ()[0][3].getW().real()
         - q4p_.getQ()[1][1].getW().real()*q4p_.getQ()[0][1].getW().real()*q4p_.getQ()[0][3].getW().real()
         - q4p_.getQ()[1][2].getW().real()*q4p_.getQ()[0][0].getW().real()*q4p_.getQ()[0][3].getW().real()
         - q4p_.getQ()[1][3].getW().real()*q4p_.getQ()[0][1].getW().real()*q4p_.getQ()[0][2].getW().real()
         - q4p_.getQ()[1][4].getW().real()*q4p_.getQ()[0][0].getW().real()*q4p_.getQ()[0][2].getW().real()
         - q4p_.getQ()[1][5].getW().real()*q4p_.getQ()[0][0].getW().real()*q4p_.getQ()[0][1].getW().real()
         + q4p_.getQ()[1][0].getW().real()*q4p_.getQ()[1][5].getW().real()
         + q4p_.getQ()[1][1].getW().real()*q4p_.getQ()[1][4].getW().real()
         + q4p_.getQ()[1][2].getW().real()*q4p_.getQ()[1][3].getW().real()
         + 2*q4p_.getQ()[2][0].getW().real()*q4p_.getQ()[0][3].getW().real()
         + 2*q4p_.getQ()[2][1].getW().real()*q4p_.getQ()[0][2].getW().real()
         + 2*q4p_.getQ()[2][2].getW().real()*q4p_.getQ()[0][1].getW().real()
         + 2*q4p_.getQ()[2][3].getW().real()*q4p_.getQ()[0][0].getW().real()
         - 6*q4p_.getQ()[3][0].getW().real();

   // Fill TTree
   if(mult_ > 0) trEvent_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
Cumulants::beginJob()
{
}

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
