// -*- Header -*-
//
// Package:    Analyzers/ChargeDepAndPtCorr
// Class:      ChargeDepAndPtCorr
// 
/**\class ChargeDepAndPtCorr ChargeDepAndPtCorr.h Analyzers/ChargeDepAndPtCorr/interface/ChargeDepAndPtCorr.h

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
#include <memory>

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "DataFormats/HeavyIonEvent/interface/Centrality.h"

#include "FWCore/Utilities/interface/InputTag.h"

// user include files
#include "TH1F.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class ChargeDepAndPtCorr : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit ChargeDepAndPtCorr(const edm::ParameterSet&);
      ~ChargeDepAndPtCorr();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

      void LoopVertices(const edm::Event& iEvent, const edm::EventSetup& iSetup);
      void LoopTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup, bool istrg);
      void LoopCaloTower(const edm::Event& iEvent, const edm::EventSetup& iSetup); 

      double GetEffWeight(double eta, double pt, int evtclass);

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      // ## tracks ##
      // used to select what tracks to read from configuration file
      edm::EDGetTokenT<reco::TrackCollection> trackTags_;

      // ## vertex ##
      // used to select what vertex to read from configuration file
      edm::EDGetTokenT<reco::VertexCollection> vtxTags_; 

      // ## calotower ##
      // used to select what calo tower to read from configuration file
      edm::EDGetTokenT<CaloTowerCollection> caloTowersTags_; 

      // ## centrality ##
      // used to select what centrality collection to read from configuration file
      edm::EDGetTokenT<reco::Centrality> centralityTags_;
      // used to access centrality bins 
      edm::EDGetTokenT<int> centralityBinTags_;

      // ## Eff/Fake coorection
      bool cweight_; //Apply (True) or not (False) the eff/fake correction
      edm::InputTag fname_; //Name of the file that contains the eff corrections
      bool effCorrByCent_; //Switch to centrality dependent correction instead of mult
      std::vector<int> effCorrBinMin_; //Mult/Cent binning of the eff/coor tables 
      std::vector<int> effCorrBinMax_; //Mult/Cent binning of the eff/coor tables
      TFile* feff_; //ROOT File that contains histograms used for corrections
      std::vector<TH2D*> heff_; //Histograms used for corrections (eta, pT)

      // ## Vertex variables
      int nVtx_;
      double xBestVtx_; //Best vertex X position 
      double yBestVtx_; //Best vertex Y position
      double zBestVtx_; //Best vertex Z position
      double rhoBestVtx_; //Best vertex XY position
      double xBestVtxError_; //Best vertex X error 
      double yBestVtxError_; //Best vertex Y error
      double zBestVtxError_; //Best vertex Z error
      unsigned int nTrkAssoToVtx_; //number of track requiered to be associated to a vertex
      bool selectVtxByMult_;       //False: sel best vtx by sum pT^2 True: sel best vtx with highest multiplicity

      // ## track selection ##
      int nTrk_;
      double dzdzerror_; //DCA - z  significance 
      double d0dz0rror_; //DCA - xy significance
      double pTerrorpT_; //DCA - pT resolution
      std::vector< double > pTmin_trg_; //min pt of the trigger tracks
      std::vector< double > pTmax_trg_; //max pt of the trigger tracks
      std::vector< double > pTmin_asso_; //min pt of the associated tracks
      std::vector< double > pTmax_asso_; //max pt of the associated tracks
      
      // ## histograms ##
      //~~~> Vertex
      TH1F* hXBestVtx_;
      TH1F* hYBestVtx_;
      TH1F* hRhoBestVtx_;
      TH1F* hZBestVtx_;
      //~~~> Trigger tracks
      TH1F* hEtaTrk_;
      TH1F* hPtTrk_; 
      TH1F* hPhiTrk_;
      //~~~> Associated tracks
      //~~~> Calo towers
      TH1F* hEtaCTow_;
      TH1F* hEtCTow_;
      TH1F* hPhiCTow_;
      // ## ttree ##
      //TTree* trEvent_;
      //int cent_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

