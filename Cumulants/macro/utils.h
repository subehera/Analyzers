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

   // loop on TChain
   void
   loopOnChain(TChain* ch, int harm, 
               std::vector< std::vector< std::vector<double> > > &qNM,
               std::vector< std::vector< std::vector<double> > > &wqNM,
               int analyzedEvts)
   {
      int noff = 0, mult = 0;
      std::vector<double>  CNM( static_cast<int>( qNM.size()), -999.);
      std::vector<double> wCNM( static_cast<int>(wqNM.size()), -999.);

      // Init branches
      LOG_S(INFO) << "Trying to get branch 'Noff'";
      if(!ch->SetBranchAddress("Noff", &noff))
      {
         LOG_S(ERROR) << "Branch 'Noff' does not exist!!! Code stopped";
         return;
      }
      LOG_S(INFO) << "Trying to get branch 'Mult'";
      if(!ch->SetBranchAddress("Mult", &mult))
      {
         LOG_S(ERROR) << "Branch 'Mult' does not exist!!! Code stopped";
         return;
      }

      for(int ibr = 0; ibr < static_cast<int>(qNM.size())*2; ibr+=2)
      {
         LOG_S(INFO) << "Trying to get branch " << Form("'C%d%d'", harm, ibr+2);
         if(!ch->SetBranchAddress(Form("C%d%d", harm, ibr+2), &CNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("C%d%d", harm, ibr+2) << "' does not exist!!! Code stopped";
            return;
         }
         LOG_S(INFO) << "Trying to get branch " << Form("wC%d%d", harm, ibr+2);
         if(!ch->SetBranchAddress(Form("wC%d%d", harm, ibr+2), &wCNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("wC%d%d", harm, ibr+2) << "' does not exist!!! Code stopped";
            return;
         }
      }

      // Get N entries
      int nentries = ch->GetEntries();
      LOG_S(INFO) << "Number of events available in the tree is: " << nentries;

      int ievt = 0;
      if(analyzedEvts <= 0) analyzedEvts = nentries;
      LOG_S(INFO) << "Number of events that will be analyzed: " << analyzedEvts;
      LOG_S(INFO) << "This represent " << (double)analyzedEvts / (double)nentries * 100. 
                  << "% of the available statistics";

      // Loop over events
      while (ievt <= analyzedEvts) 
      {
         ch->GetEntry(ievt);

         if(!(ievt%1000))
         {
            std::cout << 
            "\rievt = " << ievt 
            <<
            ", tree number = " << ch->GetTreeNumber()
            <<
            " ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)analyzedEvts)*100  << " %" 
            << std::flush;
         }
        
         // Skip event if multiplicity is zero 
         if(mult <= 0) 
         {
            ++ievt;
            continue;
         }

         // Compute cumulants
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
             qNM[ibr][noff][mult] +=  CNM[ibr];
            wqNM[ibr][noff][mult] += wCNM[ibr];
         }        

         // Next event
         ++ievt;
      }

      std::cout << std::endl;

   }

   void cumulant(const std::vector< std::vector< std::vector<double> > > &qNM,
                 const std::vector< std::vector< std::vector<double> > > &wqNM,
                 std::vector< std::vector<double> > &cNM,
                 std::vector< std::vector<double> > &wcNM,
                 int order, int inoff, int iref)
   {
      switch(order)
      {
         case 0:
            if( wqNM[order][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] - 
                                     2*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]
                                      *qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref] ) 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. &&
                wqNM[order-2][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   -
                                     9*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] +
                                    12*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] ) 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. &&
                wqNM[order-2][inoff][iref] != 0. &&
                wqNM[order-3][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   -
                                    16*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] -
                                    18*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] +
                                   144*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] 
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] -
                                   144*qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] )
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         default:
            LOG_S(ERROR) << "Not defined order";
            break;
      }
   }

   // rebin results
   void
   rebinning(const std::vector< std::vector< std::vector<double> > > &qNM,
             const std::vector< std::vector< std::vector<double> > > &wqNM,
             std::vector< std::vector<double> > &cNM,
             std::vector< std::vector<double> > &wcNM,
             std::vector< std::vector<double> > &cNMreb,
             std::vector< std::vector<double> > &wcNMreb,
             int nbins, int binarray[])
   {
      //LOG_S(WARNING) << "THIS IS ONLY GOING TO WORK UP TO c_{n}{4}";
      LOG_S(INFO) << "Combining multiplicity bin for each N_{trk}^{offline} bin";
      for(unsigned int iord = 0; iord < static_cast<unsigned int>(cNM.size()); ++iord)
      {
         for(unsigned int inoff = 0; inoff < static_cast<int>(qNM[iord].size()); ++inoff)
         {
            for(unsigned int iref = 0; iref < static_cast<int>(qNM[iord][inoff].size()); ++iref)
            {
               cumulant(qNM, wqNM, cNM, wcNM, iord, inoff, iref);
            }
         }
      }

      for(unsigned int iord = 0; iord < static_cast<unsigned int>(cNM.size()); ++iord)
      {
         for(unsigned int inoff = 0; inoff < static_cast<int>(qNM[0].size()); ++inoff)
         {
            if(wcNM[iord][inoff] != 0.) cNM[iord][inoff] /= wcNM[iord][inoff];
            else                        cNM[iord][inoff] = 0.;
         }
      }

      LOG_S(INFO) << "Rebinning in larger N_{trk}_{offline} bins now";
      for(unsigned int iord = 0; iord < static_cast<unsigned int>(cNMreb.size()); ++iord)
      {
         int inoff = 0;
         for(unsigned int ibin = 0; ibin < nbins; ++ibin)
         {
            while( inoff >= binarray[ibin] && inoff < binarray[ibin+1] )
            {
                  cNMreb[iord][ibin]  += cNM[iord][inoff] * wcNM[iord][inoff];
                  wcNMreb[iord][ibin] += wcNM[iord][inoff];
                  ++inoff;
            }

            if(wcNMreb[iord][ibin] != 0.) cNMreb[iord][ibin] /= wcNMreb[iord][ibin];
            else                          cNMreb[iord][ibin] = 0.;
         }
      }
   }

   // fill histograms
   void
   fillHistograms(std::vector< std::vector<double> > cNM, 
                  std::vector< std::vector<double> > cNMreb, 
                  std::vector<TH1D*> hcN, 
                  std::vector<TH1D*> hcNreb)
   {
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         for(int ibin = 0; ibin < hcN[iord]->GetNbinsX(); ++ibin)
         {
            hcN[iord]->SetBinContent(ibin+1, cNM[iord][ibin]);
         }

         for(int ibin = 0; ibin < hcNreb[iord]->GetNbinsX(); ++ibin)
         {
            hcNreb[iord]->SetBinContent(ibin+1, cNMreb[iord][ibin]);
         }
      }
   }

   // process TChain
   void 
   process(TFile* fin,       TFile* fout, 
           int noffmax,      int multmax, 
           int cumumaxorder, int harm, 
           int nbins,        int binarray[], 
           int analyzedEvts) 
   {
      //init Tree
      TChain* ch = new TChain();
      initChain(fin, ch);

      LOG_S(INFO) << "Number of trees in the TChain: " << ch->GetNtrees();
      LOG_S(INFO) << "Maximum cumulant order to be computed: " << cumumaxorder;

      //init vectors
      // -- 2D vector correlator (numerator and denominator)
      std::vector < std::vector< std::vector<double> > >  
      qNM( cumumaxorder / 2,
           std::vector< std::vector<double> > ( noffmax, 
                                                std::vector<double>(multmax, 0.) ) );
      std::vector < std::vector< std::vector<double> > >  
      wqNM( cumumaxorder / 2,
            std::vector< std::vector<double> > ( noffmax, 
                                                 std::vector<double>(multmax, 0.) ) );
      // -- cumulant after multipilicity bin re-combination
      std::vector < std::vector<double> >  
      cNM( cumumaxorder / 2,
           std::vector<double>( noffmax, 0.) );
      std::vector < std::vector<double> >  
      wcNM( cumumaxorder / 2,
            std::vector<double>( noffmax, 0.) );
      // -- cumulant after rebinning in noff
      std::vector < std::vector<double> >  
      cNMreb( cumumaxorder / 2,
              std::vector<double>( noffmax, 0.) );
      std::vector < std::vector<double> >  
      wcNMreb( cumumaxorder / 2,
               std::vector<double>( noffmax, 0.) );

      //Loop on chain an fill stuff!!!
      LOG_S(INFO) << "Looping on TChain...";
      loopOnChain(ch, harm, qNM, wqNM, analyzedEvts);

      //Rebinning
      LOG_S(INFO) << "Rebinning cumulants...";
      rebinning(qNM, wqNM, cNM, wcNM, cNMreb, wcNMreb, nbins, binarray);

      //Fill histograms
      // -- init histograms
      std::vector<TH1D*> hcN;
      hcN.resize(cNM.size());
  
      std::vector<TH1D*> hcNreb;
      hcNreb.resize(cNMreb.size());
      // ---- Create a temporaty table for binning
      double *tmp = new double[nbins+1];
      for(int i = 0; i < nbins+1; ++i)
      {
         tmp[i] = (double) binarray[i];
      }
      // ---- Allocate memory for histograms
      for(int iord = 0; iord < hcN.size(); ++iord)
      {
         hcN[iord]    = new TH1D(Form("hC%d%d",          harm, 2*iord+2), "", 
                                 noffmax, 0., noffmax);
         hcNreb[iord] = new TH1D(Form("hC%d%d_rebinned", harm, 2*iord+2), "", 
                                 nbins, tmp);
      }
      delete[] tmp;

      // -- fill them 
      fillHistograms(cNM, cNMreb, hcN, hcNreb);

      //Jacknife it to get errors

      //Write histo
      fout->cd();
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         hcN[iord]  ->Write();
         hcNreb[iord]->Write();
      }
   }

}
