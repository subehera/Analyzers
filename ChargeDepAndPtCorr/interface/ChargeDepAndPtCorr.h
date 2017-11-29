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

      // ## track selection ##
      double pTmin_; //min pt of the tracks
      double pTmax_; //max pt of the tracks
     
      // ## efficiency correction ##
      bool cweight_;            //Apply correction or not
      edm::InputTag fname_;     //ROOT file name that contains eff/(1-fake) corrections
      TFile* feff_;             //ROOT file that contains eff/(1-fake) corrections
      std::vector<TH2D*> heff_; //histograms with eff/(1-fake) correction factors
      std::vector<int> effmultbin_; //multiplicity/centrality binning for the heff histograms
 
      // ## histograms ##
      TH1F* hXBestVtx_;
      TH1F* hYBestVtx_;
      TH1F* hRhoBestVtx_;
      TH1F* hZBestVtx_;
      TH1F* hEtaTrk_;
      TH1F* hPtTrk_; 
      TH1F* hPhiTrk_;
      TH1F* hEtaCTow_;
      TH1F* hEtCTow_;
      TH1F* hPhiCTow_;
      // ## ttree ##
      TTree* trEvent_;
      int cent_;
      int nVtx_;
      int nTrk_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

