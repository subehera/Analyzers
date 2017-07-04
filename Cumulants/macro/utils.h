//file that contains some useful functions

namespace utils
{
   // InitChain
   void 
   initChain(TFile* fin, TChain* ch)
   {
      const int nkey = fin->GetNkeys();
      for(int ikey = 0; ikey < nkey; ++ikey)
      {
         TString keyName = fin->GetName();
         keyName.Append("/");
         keyName.Append(fin->GetListOfKeys()->At(ikey)->GetName());
         keyName.Append("/trEvent");
   
         LOG_S(INFO) << "TTree named " << keyName.Data() << " will be added to the TChain";
         ch->Add(keyName.Data());
      }
   }

   // process TChain
   void 
   process(TFile* fin, TFile* fout) 
   {
      const int nhist = fin->GetNkeys() + 1;
      //init Tree
      TChain* ch = new TChain();
      initChain(fin, ch);

      LOG_S(INFO) << "Number of trees in the TChain: " << ch->GetNtrees();
   }

}
