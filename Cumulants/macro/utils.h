//file that contains some useful functions

namespace utils
{
   //___________________________________________________
   //
   // InitChain
   //___________________________________________________
   void 
   initChain(TFile* fin, TString folder, TChain* ch)
   {
      TString keyName = fin->GetName();
      keyName.Append("/");
      keyName.Append(folder.Data());
      keyName.Append("/trEvent");
   
      LOG_S(INFO) << "TTree named " << keyName.Data() << " will be added to the TChain";
      ch->Add(keyName.Data());
   }

   //___________________________________________________
   //
   // loop on TChain: correlator calculation
   //___________________________________________________
   void
   loopOnChain(TChain* ch, int harm0, int harm1, 
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

      std::vector<TString> brnames;
      brnames.push_back(Form("C%d%d%d_17", harm0, harm0, 2));
      brnames.push_back(Form("C%d%d%d_34", harm1, harm1, 2));
      brnames.push_back(Form("C%d%d%d_18", harm1, harm0, 2));
      brnames.push_back(Form("C%d%d%d_33", harm0, harm1, 2));
      brnames.push_back(Form("C%d%d%d_51", harm0, harm1, 4));
      brnames.push_back(Form("C%d%d%d_119", harm0, harm1, 6));
      brnames.push_back(Form("C%d%d%d", harm0, harm1, 8));

      std::vector<TString> wbrnames;
      wbrnames.push_back(Form("wC%d%d%d_17", harm0, harm0, 2));
      wbrnames.push_back(Form("wC%d%d%d_34", harm1, harm1, 2));
      wbrnames.push_back(Form("wC%d%d%d_18", harm1, harm0, 2));
      wbrnames.push_back(Form("wC%d%d%d_33", harm0, harm1, 2));
      wbrnames.push_back(Form("wC%d%d%d_51", harm0, harm1, 4));
      wbrnames.push_back(Form("wC%d%d%d_119", harm0, harm1, 6));
      wbrnames.push_back(Form("wC%d%d%d", harm0, harm1, 8));

      for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
      {
         LOG_S(INFO) << "Trying to get branch " << brnames[ibr].Data(); 
         if(!ch->SetBranchAddress(brnames[ibr], &CNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << brnames[ibr] << "' does not exist!!! Code stopped";
            return;
         }
         LOG_S(INFO) << "Trying to get branch " << wbrnames[ibr].Data();
         if(!ch->SetBranchAddress(wbrnames[ibr], &wCNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << wbrnames[ibr].Data() << "' does not exist!!! Code stopped";
            return;
         }
      }

      // Get N entries
      int nentries = ch->GetEntries();
      LOG_S(INFO) << "Number of events available in the tree is: " << nentries;

      if(nentries == 0)
      {
         LOG_S(ERROR) << "No entries in this TTree! Are you kidding ME?";
         LOG_S(ERROR) << "Please check you are using the right FOLDER that contains the TTree you want to look at!!!";
         return;
      }

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
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_17 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 1:
            if( wqNM[order][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_34 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 2:
            if( wqNM[order][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_18 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 3:
            if( wqNM[order][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_33 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 4:
            if( wqNM[order][inoff][iref] != 0. &&
                wqNM[order-3][inoff][iref] != 0. &&
                wqNM[order-4][inoff][iref] != 0. &&
                wqNM[order-2][inoff][iref] != 0. &&
                wqNM[order-1][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] -   //   <<4>>
                                       qNM[order-4][inoff][iref] / wqNM[order-4][inoff][iref]
                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] -
                                       qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] )
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
//            {
//               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] -   //   <<4>>
//                                     2*qNM[order-4][inoff][iref] / wqNM[order-4][inoff][iref]   //-2*<<2>>^{2}
//                                      *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] ) 
//                                      *wqNM[order][inoff][iref];
//               wcNM[order][inoff] += wqNM[order][inoff][iref];
//            }
            break;
         case 5:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. &&
                wqNM[order-5][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //    <<6>>
                                     9*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 9*<<4>><<2>>
                                      *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref] + //
                                    12*qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref]   //+12*<<2>>^{3}
                                      *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref]
                                      *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref] ) 
                                      *wqNM[order][inoff][iref];
               wcNM[order][inoff] += wqNM[order][inoff][iref];
            }
            break;
         case 6:
            if( wqNM[order][inoff][iref]   != 0. && 
                wqNM[order-1][inoff][iref] != 0. &&
                wqNM[order-2][inoff][iref] != 0. &&
                wqNM[order-6][inoff][iref] != 0. )
            {
               cNM[order][inoff]  += ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //     <<8>>
                                    16*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 16*<<6>><<2>>
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref] - //
                                    18*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //- 18*<<4>>^{2}
                                      *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] + //
                                   144*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //+144*<<4>><<2>>^{2}
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref]   //
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref] - //-144*<<2>>^{4}
                                   144*qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref]
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref]
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref]
                                      *qNM[order-6][inoff][iref] / wqNM[order-6][inoff][iref] )
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
            val = TMath::Sqrt(cval);
            break;
         case 2:
            val = TMath::Sqrt(cval);
            break;
         case 3:
            val = TMath::Sqrt(cval);
            break;
         case 4:
            val = TMath::Power(-1*cval, 1./4.);
            break;
         case 5:
            val = TMath::Power(cval/4., 1./6.);
            break;
         case 6:
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
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 2:
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 3:
            val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
            break;
         case 4:
            val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
            break;
         case 5:
            val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
            break;
         case 6:
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
   loopJacknife(TFile* fin, TString folder, int harm0, int harm1, 
                const std::vector< std::vector< std::vector<double> > > &qNM,
                const std::vector< std::vector< std::vector<double> > > &wqNM,
                const std::vector<TH1D*> &hcN, 
                std::vector< std::vector<double> > &cNMvar,
                std::vector<int> &noffvar,
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

      //init Tree
      TChain* ch = new TChain();
      initChain(fin, folder, ch);
      ch->Print();

      // Init branches
      std::vector<TString> brnames;
      brnames.push_back(Form("C%d%d%d_17", harm0, harm0, 2));
      brnames.push_back(Form("C%d%d%d_34", harm1, harm1, 2));
      brnames.push_back(Form("C%d%d%d_18", harm1, harm0, 2));
      brnames.push_back(Form("C%d%d%d_33", harm0, harm1, 2));
      brnames.push_back(Form("C%d%d%d_51", harm0, harm1, 4));
      brnames.push_back(Form("C%d%d%d_119", harm0, harm1, 6));
      brnames.push_back(Form("C%d%d%d", harm0, harm1, 8));

      std::vector<TString> wbrnames;
      wbrnames.push_back(Form("wC%d%d%d_17", harm0, harm0, 2));
      wbrnames.push_back(Form("wC%d%d%d_34", harm1, harm1, 2));
      wbrnames.push_back(Form("wC%d%d%d_18", harm1, harm0, 2));
      wbrnames.push_back(Form("wC%d%d%d_33", harm0, harm1, 2));
      wbrnames.push_back(Form("wC%d%d%d_51", harm0, harm1, 4));
      wbrnames.push_back(Form("wC%d%d%d_119", harm0, harm1, 6));
      wbrnames.push_back(Form("wC%d%d%d", harm0, harm1, 8));

      for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
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
         LOG_S(INFO) << "Trying to get branch " << brnames[ibr].Data();
         if(!ch->SetBranchAddress(brnames[ibr], &CNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << brnames[ibr].Data() << "' does not exist!!! Code stopped";
            return;
         }
         LOG_S(INFO) << "Trying to get branch " << wbrnames[ibr].Data();
         if(!ch->SetBranchAddress(wbrnames[ibr], &wCNM[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << wbrnames[ibr].Data() << "' does not exist!!! Code stopped";
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

         // Get number of events in each Noff bins
         noffvar[noff]++;
   
         // Variance
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
             // Fill variance
             cNMvar[ibr][noff] += TMath::Power(cNM_jacknife[ibr][noff] - hcN[ibr]->GetBinContent(noff+1), 2);

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

      std::cout << std::endl;
   }


   //___________________________________________________
   //
   // jacknife
   //___________________________________________________
   void
   Jacknife(TFile* fin, TString folder, int harm0, int harm1, 
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

      // Loop for Jacknife
      LOG_S(INFO) << "Starting error estimation with Jacknife";
      loopJacknife(fin, folder, harm0, harm1, qNM, wqNM, hcN, cNMvar, noffvar, nbins, binarray, analyzedEvts);
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
               hcN[ibr]->SetBinError(ibin+1, 0.*hcN[ibr]->GetBinContent(ibin+1));
               hvN[ibr]->SetBinError(ibin+1, 0.*hvN[ibr]->GetBinContent(ibin+1));
            }
         }

         //error rebinning
         for(int ibin = 0; ibin < hcNreb[ibr]->GetNbinsX(); ++ibin)
         {
            double minbin = hcNreb[ibr]->GetBinLowEdge(ibin+1);
            double maxbin = hcNreb[ibr]->GetBinLowEdge(ibin+1) + hcNreb[ibr]->GetBinWidth(ibin+1);
            int jbin = hcNreb[ibr]->GetBinLowEdge(ibin+1);
            while(hcN[ibr]->GetBinLowEdge(jbin+1) >= minbin &&  hcN[ibr]->GetBinLowEdge(jbin+1) < maxbin)
            {
               cNMrebvar[ibr][ibin] += hcN[ibr]->GetBinError(jbin+1) * hcN[ibr]->GetBinError(jbin+1);
               ++jbin;
            }
             
            cNMrebvar[ibr][ibin] /= hcNreb[ibr]->GetBinWidth(ibin+1);

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
               hcNreb[ibr]->SetBinError(ibin+1, 0.*hcNreb[ibr]->GetBinContent(ibin+1));
               hvNreb[ibr]->SetBinError(ibin+1, 0.*hvNreb[ibr]->GetBinContent(ibin+1));
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
           TString folder,
           int noffmax,      int multmax, 
           int cumumaxorder, int harm0, int harm1, 
           int nbins,        int binarray[], 
           int analyzedEvts) 
   {
      //init Tree
      TChain* ch = new TChain();
      initChain(fin, folder, ch);

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
      loopOnChain(ch, harm0, harm1, qNM, wqNM, analyzedEvts);

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
      std::vector<TString> brnames;
      brnames.push_back(Form("hC%d%d%d_17", harm0, harm0, 2));
      brnames.push_back(Form("hC%d%d%d_34", harm1, harm1, 2));
      brnames.push_back(Form("hC%d%d%d_18", harm1, harm0, 2));
      brnames.push_back(Form("hC%d%d%d_33", harm0, harm1, 2));
      brnames.push_back(Form("hC%d%d%d_51", harm0, harm1, 4));
      brnames.push_back(Form("hC%d%d%d_119", harm0, harm1, 6));
      brnames.push_back(Form("hC%d%d%d", harm0, harm1, 8));

      for(int iord = 0; iord < hcN.size(); ++iord)
      {
         hcN[iord]    = new TH1D(brnames[iord], "", 
                                 noffmax, 0., noffmax);
         hcN[iord]->SetMarkerStyle(20);
         hcN[iord]->SetMarkerColor(iord+1);
         hcN[iord]->SetLineColor(iord+1);

         hcNreb[iord] = new TH1D(Form("%s_rebinned", brnames[iord].Data()), "", 
                                 nbins, tmp);
         hcNreb[iord]->SetMarkerStyle(24);
         hcNreb[iord]->SetMarkerColor(iord+1);
         hcNreb[iord]->SetLineColor(iord+1);

         hvN[iord]    = dynamic_cast<TH1D*>(hcN[iord]->Clone(Form("hV%d%d%d", harm0, harm1, 2*iord+2))); 
         hvNreb[iord] = dynamic_cast<TH1D*>(hcNreb[iord]->Clone(Form("hV%d%d%d_rebinned", harm0, harm1, 2*iord+2)));
      }
      delete[] tmp;

      // -- reset chain 
      ch->Reset();
      delete ch;

      // -- fill them 
      fillHistograms(cNM, cNMreb, hcN, hcNreb, hvN, hvNreb);

      //Jacknife it to get errors
      //Jacknife(fin, harm0, harm1, qNM, wqNM, hcN, hcNreb, hvN, hvNreb, nbins, binarray, analyzedEvts);

      //Write histo
      fout->cd();
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         hcN[iord]   ->Write();
         hcNreb[iord]->Write();
         //hvN[iord]   ->Write();
         //hvNreb[iord]->Write();
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
