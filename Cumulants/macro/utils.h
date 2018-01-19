//file that contains some useful functions
#include "ChainBuilder.h"

namespace utils
{
   //___________________________________________________
   //
   // Setup branche names
   //___________________________________________________
   std::vector<TString> 
   SetupBranchName(int harm0, int harm1, int nsub, std::string suffix = "")
   {
      std::vector<TString> brnames;
      brnames.push_back(Form("%sC%d%d%d_17",  suffix.c_str(), harm0, harm0, 2));
      brnames.push_back(Form("%sC%d%d%d_51",  suffix.c_str(), harm0, harm1, 4));
      brnames.push_back(Form("%sC%d%d%d_119", suffix.c_str(), harm0, harm1, 6));
      brnames.push_back(Form("%sC%d%d%d",     suffix.c_str(), harm0, harm1, 8));

      if( ( nsub <= 2 && harm0 != harm1 ) || ( nsub > 2 ) )
      {
         brnames.push_back(Form("%sC%d%d%d_33", suffix.c_str(), harm0, harm1, 2));
         brnames.push_back(Form("%sC%d%d%d_18", suffix.c_str(), harm1, harm0, 2));
         brnames.push_back(Form("%sC%d%d%d_34", suffix.c_str(), harm1, harm1, 2));

      }

      if( nsub > 2 && harm0 == harm1 )
      {
         brnames.push_back(Form("%sC%d%d%d_53",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_54",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_83",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_85",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_86",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_99",  suffix.c_str(), harm0, harm1, 4));
         brnames.push_back(Form("%sC%d%d%d_101", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_102", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_123", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_125", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_126", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_183", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_187", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_189", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_190", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_215", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_219", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_221", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_222", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_231", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_235", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_237", suffix.c_str(), harm0, harm1, 6));
         brnames.push_back(Form("%sC%d%d%d_238", suffix.c_str(), harm0, harm1, 6));
      }

      return brnames;
   }

   //___________________________________________________
   //
   // Setup TChain branches
   //___________________________________________________
   void
   SetupBranch(TChain* ch, 
               int& noff, int& mult,
               std::vector<double>& CNM, std::vector<double>& wCNM,
               int harm0, int harm1, int nsub)
   {
      LOG_S(INFO) << "Trying to get branch 'Noff'";

      if(!ch->GetBranch("Noff"))
      {
         LOG_S(ERROR) << "Branch 'Noff' does not exist!!! Code stopped";
         throw std::string("Branch error type broke the code");
         return;
      }
      else
      {
         ch->SetBranchAddress("Noff", &noff);
      }
      LOG_S(INFO) << "Trying to get branch 'Mult'";
      if(!ch->GetBranch("Mult"))
      {
         LOG_S(ERROR) << "Branch 'Mult' does not exist!!! Code stopped";
         throw std::string("Branch error type broke the code");
         return;
      }
      else
      {
         ch->SetBranchAddress("Mult", &mult);
      }

      std::vector<TString> brnames  = SetupBranchName(harm0, harm1, nsub);
      std::vector<TString> wbrnames = SetupBranchName(harm0, harm1, nsub, "w");

      for(int ibr = 0; ibr < static_cast<int>(CNM.size()); ibr++)
      {
         LOG_S(INFO) << "Trying to get branch '" << brnames[ibr].Data() << "'"; 
         if(!ch->GetBranch(brnames[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << brnames[ibr] << "' does not exist!!! Code stopped";
            throw std::string("Branch error type broke the code");
            return;
         }
         else
         {
            ch->SetBranchAddress(brnames[ibr], &CNM[ibr]);
         }
         LOG_S(INFO) << "Trying to get branch '" << wbrnames[ibr].Data() << "'";
         if(!ch->GetBranch(wbrnames[ibr]))
         {
            LOG_S(ERROR) << "Branch '" << wbrnames[ibr].Data() << "' does not exist!!! Code stopped";
            throw std::string("Branch error type broke the code");
            return;
         }
         else
         {
            ch->SetBranchAddress(wbrnames[ibr], &wCNM[ibr]);
         }
      }

   }

   //___________________________________________________
   //
   // loop on TChain: correlator calculation
   //___________________________________________________
   void
   loopOnChain(TChain* ch,  int harm0,   int harm1,
               int noffmin, int noffmax, 
               std::vector< std::vector< std::vector<double> > > &qNM,
               std::vector< std::vector< std::vector<double> > > &wqNM,
               int analyzedEvts, int nsub)
   {
      int noff = 0, mult = 0;
      std::vector<double>  CNM( static_cast<int>( qNM.size()), 0.);
      std::vector<double> wCNM( static_cast<int>(wqNM.size()), 0.);

      // Init branches
      SetupBranch(ch, noff, mult, CNM, wCNM, harm0, harm1, nsub);

      // Get N entries
      int ntrees = ch->GetNtrees();
      LOG_S(INFO) << "Number of Tree in the TChain: " << ntrees;

      if( analyzedEvts == 0 || analyzedEvts < -1 )
      {
         LOG_S(ERROR) << "No entries in this TTree! Are you kidding ME?";
         LOG_S(ERROR) << "Please check you are using the right FOLDER that contains the TTree you want to look at!!!";
         return;
      }
      else if( analyzedEvts == -1 )
      {
         LOG_S(INFO) << "Analyze all events!!!";
      }
      else
      {
         LOG_S(INFO) << "Number of events that will be analyzed: " << analyzedEvts;
      }

      // Loop over events
      int ievt = 0;
      while ( (ch->GetEntry(ievt) && ievt <= analyzedEvts) ||
              (ch->GetEntry(ievt) && analyzedEvts == -1)      ) 
      {
         if(!(ievt%1000))
         {
            std::cout << 
            "\rievt = " << ievt 
            <<
            ", tree number = " << ch->GetTreeNumber()
            <<
            " ~~~> " << std::setprecision(3) << (static_cast<double>(ch->GetTreeNumber())/static_cast<double>(ntrees))*100.  << " %" 
            << std::flush;
         }
        
         // Skip event if multiplicity is zero 
         //if(mult <= 10) 
         //{
         //   ++ievt;
         //   continue;
         //}

         //Skip event if out of range
         if(noff < noffmin || noff >= noffmax)
         {
            ++ievt;
            continue;
         }

         // Compute cumulants
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
           if( noff < qNM[ibr].size() )
           {
              if( mult < qNM[ibr][noff].size() )
              {
                  qNM[ibr][noff][mult] +=  CNM[ibr];
                 wqNM[ibr][noff][mult] += wCNM[ibr];
              }
           }
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
                 int order, int inoff, int iref, int nsub)
   {
      if( nsub <= 2)
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
      else
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
   }
   
   void uncumulant(const std::vector< std::vector< std::vector<double> > > &qNM,
                   const std::vector< std::vector< std::vector<double> > > &wqNM,
                   std::vector< std::vector<double> > &cNM,
                   std::vector< std::vector<double> > &wcNM,
                   int order, int inoff, int iref, int nsub)
   {
      if( nsub <= 2 )
      {
         switch(order)
         {
            case 0:
               if( wqNM[order][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>> 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 1:
               if( wqNM[order][inoff][iref]   != 0. && 
                   wqNM[order-1][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] -   //   <<4>>
                                        2*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //-2*<<2>>^{2}
                                         *qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref] ) 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 2:
               if( wqNM[order][inoff][iref]   != 0. && 
                   wqNM[order-1][inoff][iref] != 0. &&
                   wqNM[order-2][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //    <<6>>
                                        9*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 9*<<4>><<2>>
                                         *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] + //
                                       12*qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]   //+12*<<2>>^{3}
                                         *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref]
                                         *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] ) 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 3:
               if( wqNM[order][inoff][iref]   != 0. && 
                   wqNM[order-1][inoff][iref] != 0. &&
                   wqNM[order-2][inoff][iref] != 0. &&
                   wqNM[order-3][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //     <<8>>
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
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            default:
               LOG_S(ERROR) << "Not defined order";
               break;
         }
      }
      else
      {
         switch(order)
         {
            case 0:
               if( wqNM[order][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_17 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 1:
               if( wqNM[order][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_34 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 2:
               if( wqNM[order][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_18 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 3:
               if( wqNM[order][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref] / wqNM[order][inoff][iref] ) // <<2>>_33 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 4:
               if( wqNM[order][inoff][iref] != 0. &&
                   wqNM[order-3][inoff][iref] != 0. &&
                   wqNM[order-4][inoff][iref] != 0. &&
                   wqNM[order-2][inoff][iref] != 0. &&
                   wqNM[order-1][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref] -   //   <<4>>
                                          qNM[order-4][inoff][iref] / wqNM[order-4][inoff][iref]
                                         *qNM[order-3][inoff][iref] / wqNM[order-3][inoff][iref] -
                                          qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]
                                         *qNM[order-2][inoff][iref] / wqNM[order-2][inoff][iref] )
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 5:
               if( wqNM[order][inoff][iref]   != 0. && 
                   wqNM[order-1][inoff][iref] != 0. &&
                   wqNM[order-5][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //    <<6>>
                                        9*qNM[order-1][inoff][iref] / wqNM[order-1][inoff][iref]   //- 9*<<4>><<2>>
                                         *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref] + //
                                       12*qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref]   //+12*<<2>>^{3}
                                         *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref]
                                         *qNM[order-5][inoff][iref] / wqNM[order-5][inoff][iref] ) 
                                         *wqNM[order][inoff][iref];
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            case 6:
               if( wqNM[order][inoff][iref]   != 0. && 
                   wqNM[order-1][inoff][iref] != 0. &&
                   wqNM[order-2][inoff][iref] != 0. &&
                   wqNM[order-6][inoff][iref] != 0. )
               {
                  cNM[order][inoff]  -= ( qNM[order][inoff][iref]   / wqNM[order][inoff][iref]   - //     <<8>>
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
                  wcNM[order][inoff] -= wqNM[order][inoff][iref];
               }
               break;
            default:
               LOG_S(ERROR) << "Not defined order";
               break;
         }
      }
   }
   
   //___________________________________________________
   //
   // compute v_{n}
   //___________________________________________________
   //
   // compute v_{n}
   //___________________________________________________
   double
   computeVn(int iord, double cval, int nsub)
   {
      double val = 0.;
      if( nsub <= 2)
      {
         switch(iord)
         {
            case 0:
               if (cval > 0.) val = TMath::Sqrt(cval);
               break;
            case 1:
               if (cval < 0.) val = TMath::Power(-1*cval, 1./4.);
               break;
            case 2:
               if (cval > 0.) val = TMath::Power(cval/4., 1./6.);
               break;
            case 3:
               if (cval < 0.) val = TMath::Power(-1*cval/33., 1./8.);
               break;
            default:
               LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
               break;
         }
      }
      else
      {
         switch(iord)
         {
            case 0:
               if (cval > 0.) val = TMath::Sqrt(cval);
               break;
            case 1:
               if (cval > 0.) val = TMath::Sqrt(cval);
               break;
            case 2:
               if (cval > 0.) val = TMath::Sqrt(cval);
               break;
            case 3:
               if (cval > 0.) val = TMath::Sqrt(cval);
               break;
            case 4:
               if (cval < 0.) val = TMath::Power(-1*cval, 1./4.);
               break;
            case 5:
               if (cval > 0.) val = TMath::Power(cval/4., 1./6.);
               break;
            case 6:
               if (cval < 0.) val = TMath::Power(-1*cval/33., 1./8.);
               break;
            default:
               LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
               break;
         }
      }
      return val;
   }

   //___________________________________________________
   //
   // compute v_{n} error
   //___________________________________________________
   double
   errorVn(int iord, double cval, double cvalerr, double vval, int nsub)
   {
      double val = 0;
      if( nsub <= 2 )
      {
         switch(iord)
         {
            case 0:
               cval = fabs(cval);
               val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
               break;
            case 1:
               cval = fabs(cval);
               val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
               break;
            case 2:
               cval = fabs(cval);
               val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
               break;
            case 3:
               cval = fabs(cval);
               val = 1./8. * 1./TMath::Power(cval*cval*cval*cval*cval*cval*cval/33., 1./8.) * cvalerr * vval;
               break;
            default:
               LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
               break;
         }
      }
      else
      {
         switch(iord)
         {
            case 0:
               cval = fabs(cval);
               val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
               break;
            case 1:
               cval = fabs(cval);
               val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
               break;
            case 2:
               cval = fabs(cval);
               val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
               break;
            case 3:
               cval = fabs(cval);
               val = 1./2. * 1./TMath::Sqrt(cval) * cvalerr * vval;
               break;
            case 4:
               cval = fabs(cval);
               val = 1./4. * 1./TMath::Power(cval, 3./4.) * cvalerr * vval;
               break;
            case 5:
               cval = fabs(cval);
               val = 1./6. * 1./TMath::Power(cval*cval*cval*cval*cval/4., 1./6.) * cvalerr * vval;
               break;
            case 6:
               cval = fabs(cval);
               val = 1./8. * 1./TMath::Power(cval*cval*cval*cval*cval*cval*cval/33., 1./8.) * cvalerr * vval;
               break;
            default:
               LOG_S(ERROR) << "Unknown cumulant order. Will return 0 values...";
               break;
         }
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
             int nbins, int binarray[], int nsub, bool quiet = false)
   {
      if(!quiet) LOG_S(INFO) << "Combining multiplicity bin for each N_{trk}^{offline} bin";
      for(unsigned int iord = 0; iord < static_cast<unsigned int>(cNM.size()); ++iord)
      {
         for(unsigned int inoff = 0; inoff < static_cast<int>(qNM[iord].size()); ++inoff)
         {
            for(unsigned int iref = 0; iref < static_cast<int>(qNM[iord][inoff].size()); ++iref)
            {
               cumulant(qNM, wqNM, cNM, wcNM, iord, inoff, iref, nsub);
            }
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
                  //cNMreb[iord][ibin]  += cNM[iord][inoff] * wcNM[iord][inoff];
                  cNMreb[iord][ibin]  += cNM[iord][inoff];
                  wcNMreb[iord][ibin] += wcNM[iord][inoff];
                  ++inoff;
            }

            if(wcNMreb[iord][ibin] != 0.) cNMreb[iord][ibin] /= wcNMreb[iord][ibin];
            else                          cNMreb[iord][ibin] = 0.;
         }

         for(unsigned int inoff = 0; inoff < static_cast<int>(qNM[0].size()); ++inoff)
         {
            if(wcNM[iord][inoff] != 0.) cNM[iord][inoff] /= wcNM[iord][inoff];
            else                        cNM[iord][inoff] = 0.;
         }
      }
   }

   //___________________________________________________
   //
   // fill histograms
   //___________________________________________________
   void
   fillHistograms(const std::vector< std::vector<double> >& cNM, 
                  const std::vector< std::vector<double> >& cNMreb, 
                  std::vector<TH1D*> hcN, 
                  std::vector<TH1D*> hcNreb,
                  std::vector<TH1D*> hvN, 
                  std::vector<TH1D*> hvNreb, int nsub)
   {
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         for(int ibin = 0; ibin < hcN[iord]->GetNbinsX(); ++ibin)
         {
            if( cNM[iord][ibin] != 0. ) hcN[iord]->SetBinContent(ibin+1, cNM[iord][ibin]);
            double vn = computeVn(iord, hcN[iord]->GetBinContent(ibin+1), nsub);
            if( vn != 0. ) hvN[iord]->SetBinContent(ibin+1, vn);
         }

         for(int ibin = 0; ibin < hcNreb[iord]->GetNbinsX(); ++ibin)
         {
            if( cNMreb[iord][ibin] != 0. ) hcNreb[iord]->SetBinContent(ibin+1, cNMreb[iord][ibin]);
            double vn =  computeVn(iord, hcNreb[iord]->GetBinContent(ibin+1), nsub);
            if( vn != 0. ) hvNreb[iord]->SetBinContent(ibin+1, vn);
         }
      }
   }


   //___________________________________________________
   //
   // loop on TChain: Jacknife
   //___________________________________________________
   void
   loopJacknife(TChain* ch,  int harm0, int harm1, 
                int noffmin, int noffmax, 
                const std::vector< std::vector< std::vector<double> > > &qNM,
                const std::vector< std::vector< std::vector<double> > > &wqNM,
                const std::vector< std::vector<double> > &cNM,
                const std::vector< std::vector<double> > &wcNM,
                const std::vector< std::vector<double> > &cNMreb,
                const std::vector< std::vector<double> > &wcNMreb,
                const std::vector<TH1D*> &hcN, 
                std::vector< std::vector<double> > &cNMvar,
                std::vector<int> &noffvar,
                int nbins, int binarray[], 
                int analyzedEvts, int nsub)
   {
      int noff = 0, mult = 0;
      std::vector<double>  CNM( static_cast<int>( qNM.size()), 0.);
      std::vector<double> wCNM( static_cast<int>(wqNM.size()), 0.);
      std::vector< std::vector< std::vector<double> > >  qNM_jacknife(  qNM.size(), std::vector< std::vector<double> >(  qNM[0].size(), std::vector<double>(  qNM[0][0].size(), 0.) ) );
      std::vector< std::vector< std::vector<double> > > wqNM_jacknife( wqNM.size(), std::vector< std::vector<double> >( wqNM[0].size(), std::vector<double>( wqNM[0][0].size(), 0.) ) );
      std::vector< std::vector<double> >  cNM_jacknife(  qNM.size(), std::vector<double>(  qNM[0].size(), 0.) );
      std::vector< std::vector<double> > wcNM_jacknife( wqNM.size(), std::vector<double>( wqNM[0].size(), 0.) );

      //init Tree
      LOG_S(INFO) << "Checking that the Chain is still alive: " << ch;
      if(!ch)
      {
         LOG_S(ERROR) << "The Chain dies in the process :(. ";
         return;
      }

      // Init branches
      SetupBranch(ch, noff, mult, CNM, wCNM, harm0, harm1, nsub);

      // Get N entries
      int ntrees = ch->GetNtrees();
      LOG_S(INFO) << "Number of Tree in the TChain: " << ntrees;

      if( analyzedEvts == 0 || analyzedEvts < -1 )
      {
         LOG_S(ERROR) << "No entries in this TTree! Are you kidding ME?";
         LOG_S(ERROR) << "Please check you are using the right FOLDER that contains the TTree you want to look at!!!";
         return;
      }
      else if( analyzedEvts == -1 )
      {
         LOG_S(INFO) << "Analyze all events!!!";
      }
      else
      {
         LOG_S(INFO) << "Number of events that will be analyzed: " << analyzedEvts;
      }

      // Loop over events
      int ievt = 0;
      while ( (ch->GetEntry(ievt) && ievt <= analyzedEvts) ||
              (ch->GetEntry(ievt) && analyzedEvts == -1)      ) 
      {
         ch->GetEntry(ievt);

         if(!(ievt%1000))
         {
            std::cout << 
            "\rievt = " << ievt 
            <<
            ", tree number = " << ch->GetTreeNumber()
            <<
            " ~~~> " << std::setprecision(3) << (static_cast<double>(ch->GetTreeNumber())/static_cast<double>(ntrees))*100.  << " %" 
            << std::flush;
         }
        
         // Skip event if multiplicity is zero 
         //if(mult <= 10) 
         //{
         //   ++ievt;
         //   continue;
         //}

         //Skip event if out of range
         if(noff < noffmin || noff >= noffmax)
         {
            ++ievt;
            continue;
         }

         // Compute cumulants
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
             //LOG_S(INFO) << "Branch: " << ibr << ", Noff: " << noff << ", mult: " << mult << ",CNM[ibr] = " << CNM[ibr];
              qNM_jacknife[ibr][noff][mult] =  CNM[ibr];
             wqNM_jacknife[ibr][noff][mult] = wCNM[ibr];
         }        

         // Get number of events in each Noff bins
         noffvar[noff]++;
   
         // Variance
         for(int ibr = 0; ibr < static_cast<int>(qNM.size()); ibr++)
         {
              cNM_jacknife[ibr][noff] =  cNM[ibr][noff] * wcNM[ibr][noff];
             wcNM_jacknife[ibr][noff] = wcNM[ibr][noff];
             //Remove from average
             uncumulant(qNM_jacknife,
                        wqNM_jacknife,
                        cNM_jacknife,
                        wcNM_jacknife,
                        ibr, noff, mult, nsub);

             // c{N-1} = (W{N}*c{N} - wiqi)/W{N-1}

             // Fill variance
             if( wcNM_jacknife[ibr][noff] != 0. ) cNMvar[ibr][noff] += TMath::Power(cNM_jacknife[ibr][noff]/wcNM_jacknife[ibr][noff] - hcN[ibr]->GetBinContent(noff+1), 2);

             // Start fresh again for the next event
             // qNM_jacknife[ibr][noff][mult] =  qNM[ibr][noff][mult] +  CNM[ibr];
             //wqNM_jacknife[ibr][noff][mult] = wqNM[ibr][noff][mult] + wCNM[ibr];
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
   Jacknife(TChain* ch, int harm0, int harm1,
            int noffmin, int noffmax, 
            const std::vector < std::vector< std::vector<double> > > &qNM, 
            const std::vector < std::vector< std::vector<double> > > &wqNM, 
            const std::vector< std::vector<double> > &cNM,
            const std::vector< std::vector<double> > &wcNM,
            const std::vector< std::vector<double> > &cNMreb,
            const std::vector< std::vector<double> > &wcNMreb,
            std::vector<TH1D*> &hcN, 
            std::vector<TH1D*> &hcNreb, 
            std::vector<TH1D*> &hvN, 
            std::vector<TH1D*> &hvNreb, 
            int nbins, int binarray[], 
            int analyzedEvts, int nsub)
   {
      std::vector< std::vector<double> > cNMvar( qNM.size(), std::vector<double> ( qNM[0].size(), 0.) );
      std::vector< std::vector<double> > cNMrebvar( qNM.size(), std::vector<double> ( nbins, 0.) );
      std::vector<int>                   noffvar( qNM[0].size(), 0 );

      // Loop for Jacknife
      LOG_S(INFO) << "Starting error estimation with Jacknife";
      try
      {
         loopJacknife(ch, harm0, harm1, 
                      noffmin, noffmax,
                      qNM, wqNM, 
                      cNM, wcNM, cNMreb, wcNMreb, 
                      hcN, cNMvar, noffvar, 
                      nbins, binarray, 
                      analyzedEvts, nsub);
      }
      catch(std::string const& e)
      {
         LOG_S(ERROR) << "Be careful, something might break";
         return;
      }

      LOG_S(INFO) << "End of error estimation with Jacknife";

      for(int ibr = 0; ibr < hcN.size(); ++ibr)
      {
         for(int ibin = 0; ibin < hcN[ibr]->GetNbinsX(); ++ibin)
         {
            if(cNMvar[ibr][ibin] > 0.)
            { 
               hcN[ibr]->SetBinError(ibin+1, TMath::Sqrt(cNMvar[ibr][ibin]));
               hvN[ibr]->SetBinError(ibin+1, errorVn(ibr,
                                                     hcN[ibr]->GetBinContent(ibin+1),
                                                     TMath::Sqrt(cNMvar[ibr][ibin]),
                                                     hvN[ibr]->GetBinContent(ibin+1), nsub));
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
             
            if(hcNreb[ibr]->GetBinWidth(ibin+1) != 0.) cNMrebvar[ibr][ibin] /= hcNreb[ibr]->GetBinWidth(ibin+1);

            if(cNMrebvar[ibr][ibin] > 0.)
            { 
               hcNreb[ibr]->SetBinError(ibin+1, TMath::Sqrt(cNMrebvar[ibr][ibin]));
               hvNreb[ibr]->SetBinError(ibin+1, errorVn(ibr, 
                                                        hcNreb[ibr]->GetBinContent(ibin+1),
                                                        TMath::Sqrt(cNMrebvar[ibr][ibin]),
                                                        hvNreb[ibr]->GetBinContent(ibin+1), nsub));
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
   process(TChain* ch, TFile* fout, 
           TString folder,
           int noffmin,      int noffmax, int multmax, 
           int cumumaxorder, int harm0,   int harm1, 
           int nbins,        int binarray[], 
           int analyzedEvts, int nsub) 
   {
      LOG_S(INFO) << "Number of trees in the TChain: " << ch->GetNtrees();
      LOG_S(INFO) << "Maximum cumulant order to be computed: " << cumumaxorder;

      //init vectors
      //  -- 2D vector correlator (numerator and denominator)
      std::vector < std::vector< std::vector<double> > >  
      qNM( cumumaxorder / 2,
           std::vector< std::vector<double> > ( binarray[nbins], 
                                                std::vector<double>(multmax, 0.) ) );
      std::vector < std::vector< std::vector<double> > >  
      wqNM( cumumaxorder / 2,
            std::vector< std::vector<double> > ( binarray[nbins], 
                                                 std::vector<double>(multmax, 0.) ) );
      // -- cumulant after multipilicity bin re-combination
      std::vector < std::vector<double> >  
      cNM( cumumaxorder / 2,
           std::vector<double>( binarray[nbins], 0.) );
      std::vector < std::vector<double> >  
      wcNM( cumumaxorder / 2,
            std::vector<double>( binarray[nbins], 0.) );
      // -- cumulant after rebinning in noff
      std::vector < std::vector<double> >  
      cNMreb( cumumaxorder / 2,
              std::vector<double>( nbins, 0.) );
      std::vector < std::vector<double> >  
      wcNMreb( cumumaxorder / 2,
               std::vector<double>( nbins, 0.) );

      //Loop on chain an fill stuff!!!
      LOG_S(INFO) << "Looping on TChain...";
      try
      {
         loopOnChain(ch,           harm0,   harm1, 
                     noffmin,      noffmax, 
                     qNM,          wqNM, 
                     analyzedEvts, nsub);
      }
      catch(std::string const& e)
      {
         LOG_S(ERROR) << "Be careful, something might break";
         return;
      }

      //Rebinning
      LOG_S(INFO) << "Rebinning cumulants...";
      rebinning(qNM, wqNM, cNM, wcNM, cNMreb, wcNMreb, nbins, binarray, nsub);

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
      std::vector<TString> brnames = SetupBranchName(harm0, harm1, nsub, "h");

      LOG_S(INFO) << "There are " << hcN.size() << " to be filled" ;
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

         //hvN[iord]    = dynamic_cast<TH1D*>(hcN[iord]->Clone(Form("hV%d%d%d", harm0, harm1, 2*iord+2))); 
         //hvNreb[iord] = dynamic_cast<TH1D*>(hcNreb[iord]->Clone(Form("hV%d%d%d_rebinned", harm0, harm1, 2*iord+2)));
         hvN[iord]    = new TH1D(Form("hV%d%d%d", harm0, harm1, 2*iord+2), "", noffmax, 0., noffmax); 
         hvN[iord]->SetMarkerStyle(20);
         hvN[iord]->SetMarkerColor(iord+1);
         hvN[iord]->SetLineColor(iord+1);
         hvNreb[iord] = new TH1D(Form("hV%d%d%d_rebinned", harm0, harm1, 2*iord+2), "", nbins, tmp);
         hvNreb[iord]->SetMarkerStyle(24);
         hvNreb[iord]->SetMarkerColor(iord+1);
         hvNreb[iord]->SetLineColor(iord+1);
      }

      // -- fill them 
      fillHistograms(cNM, cNMreb, hcN, hcNreb, hvN, hvNreb, nsub);
      delete[] tmp;

      //Jacknife it to get errors
      Jacknife(ch,           harm0,    harm1, 
               noffmin,      noffmax, 
               qNM,          wqNM, 
               cNM,          wcNM, 
               cNMreb,       wcNMreb, 
               hcN,          hcNreb,   hvN, hvNreb, 
               nbins,        binarray, 
               analyzedEvts, nsub);

      //Write histo
      fout->cd();
      for(int iord = 0; iord < cNM.size(); ++iord)
      {
         hcN[iord]   ->Write();
         hcNreb[iord]->Write();
         hvN[iord]   ->Write();
         hvNreb[iord]->Write();
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
