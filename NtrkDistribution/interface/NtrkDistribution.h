// -*- Header -*-
//
// Package:    Analyzers/NtrkDistribution
// Class:      NtrkDistribution
// 
/**\class NtrkDistribution NtrkDistribution.h Analyzers/NtrkDistribution/interface/NtrkDistribution.h

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
#include <vector>

// CMSSW include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

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

class NtrkDistribution : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit NtrkDistribution(const edm::ParameterSet&);
      ~NtrkDistribution();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
      int getEffNoffIndex();

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
      int cent_;

      // ## multiplicity selection (Noff)
      int noffmin_;          //minimum multiplicity of an event to be considered
      int noffmax_;          //maximum multiplicity of an event to be considered
      double ptnoffmin_;     //minimum pt cut to compute Noff
      double ptnoffmax_;     //maximum pt cut to compute Noff
      double dzdzerrornoff_; //cut on dz/dzerror of the tracks to compute Noff 
      double d0d0errornoff_; //cut on d0/d0error of the tracks to compute Noff
      double pterrorptnoff_; //cut on pterror/pt of the tracks to compute Noff
      int noff_;             //ntrk offline value for a given event
      double noffcorr_;      //ntrk offline corrected value for a given event

      // ## track selection ##
      double etamin_;    //min eta of the tracks
      double etamax_;    //max eta of the tracks
      double ptmin_;     //min pt of the tracks
      double ptmax_;     //max pt of the tracks
      double dzdzerror_; //cut on dz/dzerror of the tracks
      double d0d0error_; //cut on d0/d0error of the tracks
      double pterrorpt_; //cut on pterror/pt of the tracks
      int mult_;         //multiplicity (Nref) in a given event
      double multcorr_;  //multiplicity corrected (Nch) in a given event

      // ## vertex selection ##
      double  minvz_;         //minimum z distance wrt (0,0,0) for the vertex       
      double  maxvz_;         //maximum z distance wrt (0,0,0) for the vertex
      double  maxrho_;        //cut on rho distance for the vertex position 
      bool    isBVselByMult_; //sel best vertex based on vertex multiplicity (true) or sum p_T^2 (false)
      int     nvtx_;          //number of reconstructed vertices in a given events
      double  xBestVtx_;      //x coordinate of the best vertex
      double  yBestVtx_;      //y coordinate of the best vertex
      double  rhoBestVtx_;    //r coordinate of the best vertex
      double  zBestVtx_;      //z coordinate of the best vertex
      double  xBestVtxError_; //x coordinate error of the best vertex
      double  yBestVtxError_; //y coordinate error of the best vertex
      double  zBestVtxError_; //z coordinate error of the best vertex

      // ## file acc & eff & fake ##
      edm::InputTag fname_;         //file name that contains acc X eff corrections
      std::vector<int> effmultbin_; //Multiplicity binning of the correction 
      TFile* feff_;                 //TFile that contains 2D histos (pt, eta) with eff/(1-fak) 
      std::vector<TH2D*> heff_;     //TH2D histograms used for correction

      // ## histograms ##
      TH1F* hXBestVtx_;
      TH1F* hYBestVtx_;
      TH1F* hRhoBestVtx_;
      TH1F* hZBestVtx_;
      TH1F* hTrk_;
      TH1F* hEtaTrk_;
      TH1F* hPtTrk_; 
      TH1F* hPhiTrk_;
      TH1F* hTrkCorr_;
      TH1F* hEtaTrkCorr_;
      TH1F* hPtTrkCorr_; 
      TH1F* hPhiTrkCorr_;
      TH1F* hNoff_;
      TH1F* hEtaNoff_;
      TH1F* hPtNoff_; 
      TH1F* hPhiNoff_;
      TH1F* hNoffCorr_;
      TH1F* hEtaNoffCorr_;
      TH1F* hPtNoffCorr_; 
      TH1F* hPhiNoffCorr_;
      TH1F* hEtaCTow_;
      TH1F* hEtCTow_;
      TH1F* hPhiCTow_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

