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

// user include files
#include "Analyzers/ChargeDepAndPtCorr/interface/ChargeDepAndPtCorr.h"


//
// constructors and destructor
//
ChargeDepAndPtCorr::ChargeDepAndPtCorr(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
   usesResource("TFileService");

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



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
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
