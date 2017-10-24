//file that contains some useful functions

namespace utils
{
   //___________________________________________________
   //
   // InitChain
   //___________________________________________________
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

   //___________________________________________________
   //
   // loop on TChain: correlator calculation
   //___________________________________________________
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

      for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
      {
         LOG_S(INFO) << "Trying to get branch " << Form("'C%d%d'", harm, 2*ibr+2);
         if(!ch->SetBranchAddress(Form("C%d%d", harm, 2*ibr+2), &CNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("C%d%d", harm, 2*ibr+2) << "' does not exist!!! Code stopped";
            return;
         }
         LOG_S(INFO) << "Trying to get branch " << Form("wC%d%d", harm, 2*ibr+2);
         if(!ch->SetBranchAddress(Form("wC%d%d", harm, 2*ibr+2), &wCNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("wC%d%d", harm, 2*ibr+2) << "' does not exist!!! Code stopped";
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

      // Free memory from huge vectors
      CNM.clear();
      wCNM.clear();
      std::vector<double>().swap(CNM);       
      std::vector<double>().swap(wCNM); 

      std::cout << std::endl;
   }

   //___________________________________________________
   //
   // Compute cumulants
   //___________________________________________________
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
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>> 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] -   //   <<4>>
                                     2*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //-2*<<2>>^{2}
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
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //    <<6>>
                                     9*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 9*<<4>><<2>>
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] + //
                                    12*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //+12*<<2>>^{3}
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
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //     <<8>>
                                    16*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 16*<<6>><<2>>
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] - //
                                    18*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //- 18*<<4>>^{2}
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] + //
                                   144*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //+144*<<4>><<2>>^{2}
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref]   //
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] - //-144*<<2>>^{4}
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
   
   //___________________________________________________
   //
   // compute v_{n}
   //___________________________________________________
   double
   computeVn(int iord, double cval)
   {
      double val = 0.;
      switch(iord)
      {
         case 0:
            val = TMath::Sqrt(cval);
            break;
         case 1:
            val = TMath::Power(-1*cval, 1./4.);
            break;
         case 2:
            val = TMath::Power(cval/4., 1./6.);
            break;
         case 3:
            val = TMath::Power(-1*cval/33., 1./8.);
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
      return val;
   }

   //___________________________________________________
   //
   // compute v_{n} error
   //___________________________________________________
   double
   errorVn(int iord, double cval, double cvalerr, double vval)
   {
      double val = 0;
      switch(iord)
      {
         case 0:
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 1:
            val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
            break;
         case 2:
            val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
            break;
         case 3:
            val = 1./8. * 1./TMath::Power(cval*cval*cval*cval*cval*cval*cval/33., 1./8.) * cvalerr * vval;
            break;
         default:
            LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
            break;
      }
      return val;
   }

   //___________________________________________________
   //
   // rebin results
   //___________________________________________________
   void
   rebinning(const std::vector< std::vector< std::vector<double> > > &qNM,
             const std::vector< std::vector< std::vector<double> > > &wqNM,
             std::vector< std::vector<double> > &cNM,
             std::vector< std::vector<double> > &wcNM,
             std::vector< std::vector<double> > &cNMreb,
             std::vector< std::vector<double> > &wcNMreb,
             int nbins, int binarray[], bool quiet = false)
   {
      std::vector< std::vector<double> >(cNM.size(),  std::vector<double>(qNM[0].size(),  0.)).swap(cNM);
      std::vector< std::vector<double> >(wcNM.size(), std::vector<double>(wqNM[0].size(), 0.)).swap(wcNM);
      std::vector< std::vector<double> >(cNMreb.size(),  std::vector<double>(nbins,  0.)).swap(cNMreb);
      std::vector< std::vector<double> >(wcNMreb.size(), std::vector<double>(nbins,  0.)).swap(wcNMreb);
   
      if(!quiet) LOG_S(INFO) << "Combining multiplicity bin for each N_{trk}^{offline} bin";
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

      if(!quiet) LOG_S(INFO) << "Rebinning in larger N_{trk}_{offline} bins now";
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

   //___________________________________________________
   //
   // fill histograms
   //___________________________________________________
   void
   fillHistograms(std::vector< std::vector<double> > cNM, 
                  std::vector< std::vector<double> > cNMreb, 
                  std::vector<TH1D*> hcN, 
                  std::vector<TH1D*> hcNreb,
                  std::vector<TH1D*> hvN, 
                  std::vector<TH1D*> hvNreb)
   {
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         for(int ibin = 0; ibin < hcN[iord]->GetNbinsX(); ++ibin)
         {
            hcN[iord]->SetBinContent(ibin+1, cNM[iord][ibin]);
            hvN[iord]->SetBinContent(ibin+1, computeVn(iord, hcN[iord]->GetBinContent(ibin+1)));
         }

         for(int ibin = 0; ibin < hcNreb[iord]->GetNbinsX(); ++ibin)
         {
            hcNreb[iord]->SetBinContent(ibin+1, cNMreb[iord][ibin]);
            hvNreb[iord]->SetBinContent(ibin+1, computeVn(iord, hcNreb[iord]->GetBinContent(ibin+1)));
         }
      }
   }


   //___________________________________________________
   //
   // loop on TChain: Jacknife
   //___________________________________________________
   void
   loopJacknife(TFile* fin, int harm, 
                const std::vector< std::vector< std::vector<double> > > &qNM,
                const std::vector< std::vector< std::vector<double> > > &wqNM,
                const std::vector<TH1D*> &hcN, 
                const std::vector<TH1D*> &hcNreb, 
                std::vector< std::vector<double> > &cNMvar,
                std::vector<int> &noffvar,
                std::vector< std::vector<double> > &cNMrebvar,
                std::vector<int> &noffrebvar,
                int nbins, int binarray[], 
                int analyzedEvts)
   {
      int noff = 0, mult = 0;
      std::vector<double>  CNM( static_cast<int>( qNM.size()), -999.);
      std::vector<double> wCNM( static_cast<int>(wqNM.size()), -999.);
      std::vector< std::vector< std::vector<double> > > qNM_jacknife(   qNM.size(), std::vector< std::vector<double> >( qNM[0].size(), std::vector<double>( qNM[0][0].size(), 0.) ) );
      std::vector< std::vector< std::vector<double> > > wqNM_jacknife( wqNM.size(), std::vector< std::vector<double> >(wqNM[0].size(), std::vector<double>(wqNM[0][0].size(), 0.) ) );
      std::vector< std::vector<double> > cNM_jacknife( qNM.size(), std::vector<double>( qNM[0].size(), 0.) );
      std::vector< std::vector<double> > wcNM_jacknife( wqNM.size(), std::vector<double>( wqNM[0].size(), 0.) );
      std::vector< std::vector<double> > cNMreb_jacknife( qNM.size(), std::vector<double>( nbins, 0.) );
      std::vector< std::vector<double> > wcNMreb_jacknife( wqNM.size(), std::vector<double>( nbins, 0.) );

      //init Tree
      TChain* ch = new TChain();
      initChain(fin, ch);
      ch->Print();

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

      for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
      {
         LOG_S(INFO) << "Trying to get branch " << Form("'C%d%d'", harm, 2*ibr+2);
         if(!ch->SetBranchAddress(Form("C%d%d", harm, 2*ibr+2), &CNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("C%d%d", harm, 2*ibr+2) << "' does not exist!!! Code stopped";
            return;
         }
         LOG_S(INFO) << "Trying to get branch " << Form("wC%d%d", harm, 2*ibr+2);
         if(!ch->SetBranchAddress(Form("wC%d%d", harm, 2*ibr+2), &wCNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << Form("wC%d%d", harm, 2*ibr+2) << "' does not exist!!! Code stopped";
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
         if(mult <= 10) 
         {
            ++ievt;
            continue;
         }

         // Compute cumulants
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
             //LOG_S(INFO) << "Branch: " << ibr;
             qNM_jacknife[ibr][noff][mult]  = qNM[ibr][noff][mult] - CNM[ibr];
             wqNM_jacknife[ibr][noff][mult] = wqNM[ibr][noff][mult] - wCNM[ibr];
         }        

      //   //// Rebin
      //   rebinning(qNM_jacknife, wqNM_jacknife, 
      //             cNM_jacknife, wcNM_jacknife, 
      //             cNMreb_jacknife, wcNMreb_jacknife, 
      //             nbins, binarray, true);

         //// Get index for rebinned histogram
         int idx = -1;
         for(int ibin = 0; ibin < nbins; ++ibin)
         {
             if(noff >= binarray[ibin] && noff < binarray[ibin+1]) idx = ibin;
         }
         if(idx < 0) 
         {
            LOG_S(ERROR) << "No valid index found for rebinned cumulant variance estimation";
            return;
         }

         // Get number of events in each Noff bins
         noffvar[noff]++;
         noffrebvar[idx]++;
   
         // Variance
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
             // Fill variance
             cNMvar[ibr][noff] += TMath::Power(cNM_jacknife[ibr][noff] - hcN[ibr]->GetBinContent(noff+1), 2);

             // -- Filling variance for rebinned calcualtion
             cNMrebvar[ibr][idx] += TMath::Power(cNMreb_jacknife[ibr][idx] - hcNreb[ibr]->GetBinContent(idx+1), 2);

             // Start fresh again for the next event
             qNM_jacknife[ibr][noff][mult]  += CNM[ibr];
             wqNM_jacknife[ibr][noff][mult] += wCNM[ibr];
         }    
    
         // Next event
         ++ievt;
      }
      std::cout << std::endl;

      LOG_S(INFO) << "Scaling the variance by the right number of events: (N-1)/N in each N_{trk}^{offline} bin";
      // Scale var by N-1 / N events
      for(int ibr = 0; ibr < cNMvar.size(); ++ibr)
      {
         for(int inoff = 0; inoff < cNMvar[ibr].size(); ++inoff)
         {
            if(noffvar[inoff] != 0)
            {
               cNMvar[ibr][inoff] *= static_cast<double>(noffvar[inoff] - 1.) / static_cast<double>(noffvar[inoff]);
            }
            else
            {
               //LOG_S(WARNING) << "No event in this bin noff = " << inoff << " error calculation will be crap";
               cNMvar[ibr][inoff] *= 0.;
            }
         }
         for(int inoff = 0; inoff < cNMrebvar[ibr].size(); ++inoff)
         {
            if(noffrebvar[inoff] != 0)
            {
               cNMrebvar[ibr][inoff] *= static_cast<double>(noffrebvar[inoff] - 1.) / static_cast<double>(noffrebvar[inoff]);
            }
            else
            {
               //LOG_S(WARNING) << "No event in this bin noff = " << inoff << " error calculation will be crap";
               cNMrebvar[ibr][inoff] *= 0.;
            }
         }
      }
      // Reset and delete TChain
      ch->Reset();
      delete ch;

      // Free memory from huge vectors
      LOG_S(INFO) << "Let's free some space and memory now";
      CNM.clear();
      wCNM.clear();
      std::vector<double>().swap(CNM);       
      std::vector<double>().swap(wCNM);
      for(int i = 0; i < qNM_jacknife.size(); ++i)
      {
         for(int j = 0; j < qNM_jacknife[i].size(); ++j)
         {
            qNM_jacknife[i][j].clear();
            wqNM_jacknife[i][j].clear();
         } 
         qNM_jacknife[i].clear();
         wqNM_jacknife[i].clear();
      } 
      std::vector< std::vector< std::vector<double> > >().swap(qNM_jacknife);
      std::vector< std::vector< std::vector<double> > >().swap(wqNM_jacknife);
      for(int i = 0; i < cNM_jacknife.size(); ++i)
      {
         cNM_jacknife[i].clear();
         wcNM_jacknife[i].clear();
      }
      cNM_jacknife.clear();
      wcNM_jacknife.clear();
      std::vector< std::vector<double> >().swap(cNM_jacknife);
      std::vector< std::vector<double> >().swap(wcNM_jacknife);
      for(int i = 0; i < cNMreb_jacknife.size(); ++i)
      {
         cNMreb_jacknife[i].clear();
         wcNMreb_jacknife[i].clear();
      }
      cNMreb_jacknife.clear();
      wcNMreb_jacknife.clear();
      std::vector< std::vector<double> >().swap(cNMreb_jacknife);
      std::vector< std::vector<double> >().swap(wcNMreb_jacknife);

      std::cout << std::endl;
   }


   //___________________________________________________
   //
   // jacknife
   //___________________________________________________
   void
   Jacknife(TFile* fin, int harm, 
            const std::vector < std::vector< std::vector<double> > > &qNM, 
            const std::vector < std::vector< std::vector<double> > > &wqNM, 
            std::vector<TH1D*> hcN, 
            std::vector<TH1D*> hcNreb, 
            std::vector<TH1D*> hvN, 
            std::vector<TH1D*> hvNreb, 
            int nbins, int binarray[], 
            int analyzedEvts)
   {
      std::vector< std::vector<double> > cNMvar( qNM.size(), std::vector<double> ( qNM[0].size(), 0.) );
      std::vector<int>                   noffvar( qNM[0].size(), 0 );
      std::vector< std::vector<double> > cNMrebvar( qNM.size(), std::vector<double> ( nbins, 0.) );
      std::vector<int>                   noffrebvar( nbins, 0 );

      // Loop for Jacknfe
      LOG_S(INFO) << "Starting error estimation with Jacknife";
      loopJacknife(fin, harm, qNM, wqNM, hcN, hcNreb, cNMvar, noffvar, cNMrebvar, noffrebvar, nbins, binarray, analyzedEvts);
      LOG_S(INFO) << "End of error estimation with Jacknife";

      for(int ibr = 0; ibr < hcN.size(); ++ibr)
      {
         for(int ibin = 0; ibin < hcN[ibr]->GetNbinsX(); ++ibin)
         {
            if(cNMvar[ibr][ibin] > 0)
            { 
               hcN[ibr]->SetBinError(ibin+1, TMath::Sqrt(cNMvar[ibr][ibin]));
               hvN[ibr]->SetBinError(ibin+1, errorVn(ibr,
                                                     hcN[ibr]->GetBinContent(ibin+1),
                                                     TMath::Sqrt(cNMvar[ibr][ibin]),
                                                     hvN[ibr]->GetBinContent(ibin+1)));
            }
            else
            {
               hcN[ibr]->SetBinError(ibin+1, 0.);
               hvN[ibr]->SetBinError(ibin+1, 0.);
            }
         }
         for(int ibin = 0; ibin < hcNreb[ibr]->GetNbinsX(); ++ibin)
         {
            if(cNMrebvar[ibr][ibin] > 0)
            { 
               hcNreb[ibr]->SetBinError(ibin+1, TMath::Sqrt(cNMrebvar[ibr][ibin]));
               hvNreb[ibr]->SetBinError(ibin+1, errorVn(ibr, 
                                                        hcNreb[ibr]->GetBinContent(ibin+1),
                                                        TMath::Sqrt(cNMrebvar[ibr][ibin]),
                                                        hvNreb[ibr]->GetBinContent(ibin+1)));
            }
            else
            {
               hcNreb[ibr]->SetBinError(ibin+1, 0.);
               hvNreb[ibr]->SetBinError(ibin+1, 0.);
            }
         }
      }
   }


   //___________________________________________________
   //
   // process TChain
   //___________________________________________________
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
      //  -- 2D vector correlator (numerator and denominator)
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
      LOG_S(INFO) << "Fill histograms";
      // -- init histograms
      // ---- c_{n}
      std::vector<TH1D*> hcN;
      hcN.resize(cNM.size());
      std::vector<TH1D*> hcNreb;
      hcNreb.resize(cNMreb.size());
      // ---- v_{n}
      std::vector<TH1D*> hvN;
      hvN.resize(cNM.size());
      std::vector<TH1D*> hvNreb;
      hvNreb.resize(cNMreb.size());

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

         hvN[iord]    = dynamic_cast<TH1D*>(hcN[iord]->Clone()); 
         hvNreb[iord] = dynamic_cast<TH1D*>(hcNreb[iord]->Clone());
      }
      delete[] tmp;

      // -- reset chain 
      ch->Reset();
      delete ch;

      // -- fill them 
      fillHistograms(cNM, cNMreb, hcN, hcNreb, hvN, hvNreb);

      //Jacknife it to get errors
      Jacknife(fin, harm, qNM, wqNM, hcN, hcNreb, hvN, hvNreb, nbins, binarray, analyzedEvts);

      //Write histo
      fout->cd();
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         hcN[iord]  ->Write();
         hcNreb[iord]->Write();
      }

      // Free memory from huge vectors
      for(int i = 0; i < qNM.size(); ++i)
      {
         for(int j = 0; j < qNM.size(); ++j)
         {
            qNM[i][j].clear();
            wqNM[i][j].clear();
         }
         qNM[i].clear();
         wqNM[i].clear();
      }
      qNM.clear();
      wqNM.clear();
      std::vector< std::vector< std::vector<double> > >().swap(qNM);       
      std::vector< std::vector< std::vector<double> > >().swap(wqNM);
      for(int i = 0; i < cNM.size(); ++i)
      {
         cNM[i].clear();
         wcNM[i].clear();
      }
      cNM.clear();
      wcNM.clear();
      std::vector< std::vector<double> >().swap(cNM);       
      std::vector< std::vector<double> >().swap(wcNM); 
      for(int i = 0; i < cNMreb.size(); ++i)
      {
         cNMreb[i].clear();
         wcNMreb[i].clear();
      }
      cNMreb.clear();
      wcNMreb.clear();
      std::vector< std::vector<double> >().swap(cNMreb);       
      std::vector< std::vector<double> >().swap(wcNMreb); 
   }
}
