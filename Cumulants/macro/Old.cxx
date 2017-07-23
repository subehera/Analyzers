//C++ headers
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

//ROOT headers
#include <TStyle.h>
#include <TChain.h>
#include <TTreeIndex.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TFile.h>
#include <TProfile.h>
#include <TGraphErrors.h>

//USER headers

int analyzedEvts = -1;
int colors[9] = {
    kBlue+1, 
    kRed+1, 
    kGreen+1,
    kBlack,
    kMagenta+1,
    kOrange,
    kOrange+2,
    kCyan+1,
    kViolet 
                }; 

bool isProcess = true;

int noffMax;
int multMax;

//-------------------
//Function declaration
   //--- Check Arg
bool checkArg(int argc, char** argv)
{
   printf ("This program was called with \"%s\".\n",argv[0]);

   if (argc > 1)
   {
     for (int count = 1; count < argc; count++)
     {
       printf("argv[%d] = %s\n", count, argv[count]);
     }
   }
   else
   {
     printf("The command had no arguments or an invalid number of arguments.\n");
     printf("Default configuration will be used.\n");
     return false;
   }

   return true;
}

   //--- Init histos
void SetHistoStyle(TH1D*& hist, int color, std::string xtitle, std::string ytitle);
void SetHistoStyle(TH2D*& hist,std::string option, std::string xtitle, std::string ytitle);
void initHist(TH1D*& hist, int color, std::string histname, std::string xtitle, std::string ytitle);
void initHist(TH2D*& hist, std::string histname, std::string xtitle, std::string ytitle, int binx, int biny);
void initHist(TH1D*& hist, int color, std::string histname, int nbins, double binval[], std::string xtitle, std::string ytitle);
void initBaseHist(int nhist, std::vector<TH1D*>& hist, std::string histname, std::string xtitle, std::string ytitle);
void drawBaseHist(int nhist, std::vector<TH1D*> hist, std::string outFileName);
void drawCumuHist(TH2D* hist, std::vector<TH2D*> hist_var, TH2D* histW, std::vector<TH2D*> histW_var, std::string outFileName);
void drawCHist(TH1D* hist, std::string outFileName);
TH2D* getFromFile(std::string outFileName, std::string name);
void drawGraphFromHist(TGraphErrors*& gr, TH1D* hist, std::string evtclass, std::string outFileName, const int nhist);

   //--- InitChain
void initChain(TFile* fin, TChain* ch)
{
   const int nkey = fin->GetNkeys();
   for(int ikey = 0; ikey < nkey; ++ikey)
   {
      TString keyName = fin->GetName();
      keyName.Append("/");
      keyName.Append(fin->GetListOfKeys()->At(ikey)->GetName());
      keyName.Append("/trEvent");

      std::cout <<
      "PlotVnVm::INFO::TTree named " << keyName.Data() << " will be added to the TChain"
      << std::endl;
      ch->Add(keyName.Data());
   }
}

   //--- Loop on chain
void loopOnChain(TChain* ch, int nSub, std::string evtclass,
                 std::vector<TH1D*> histBaseMult, std::vector<TH1D*> histBaseEvtClass,
                 TH2D* qNM, TH2D* qwNM,
                 std::vector<TH2D*> qNM_var, std::vector<TH2D*> qwNM_var)
{
   int classifier = 0, mult = 0, cent = -1;
   double  CN2 = -999.,  CN4 = -999.; 
   double wCN2 = -999., wCN4 = -999.;


   //Init branches
   ch->SetBranchAddress(Form("%s", evtclass.c_str()), &classifier);
   ch->SetBranchAddress("Mult", &mult);

   ch->SetBranchAddress("C22", &CN2);
   ch->SetBranchAddress("C24", &CN4);

   ch->SetBranchAddress("wC22", &wCN2);
   ch->SetBranchAddress("wC24", &wCN4);

   int nentries = ch->GetEntries();
   std::cout <<
   "PlotVnVm::INFO::We are going to run over: " << nentries << " events." 
   << std::endl << 
   "PlotVnVm::INFO::Fraction of events removed in each sub-sample: " << (int)(nentries/nSub) << " events."
   << std::endl;


   std::vector< std::vector< std::vector<double> > > 
   vqNM(qNM->GetNbinsY(), 
        std::vector< std::vector<double> > (qNM->GetNbinsX(), 
                                            std::vector<double>(multMax,0.)));
   std::vector< std::vector< std::vector<double> > > 
   vwqNM(qwNM->GetNbinsY(), 
       std::vector< std::vector<double> > (qwNM->GetNbinsX(), 
                                           std::vector<double>(multMax,0.)));


   std::vector< std::vector< std::vector < std::vector<double> > > > 
   vqNM_var(qNM->GetNbinsY(), 
            std::vector< std::vector< std::vector<double> > > (qNM->GetNbinsX(), 
                                                               std::vector< std::vector<double> >(multMax,
                                                                                                  std::vector<double>(nSub, 0.))));
   std::vector< std::vector< std::vector < std::vector<double> > > >
   vwqNM_var(qwNM->GetNbinsY(), 
           std::vector< std::vector< std::vector<double> > > (qwNM->GetNbinsX(), 
                                                              std::vector< std::vector<double> >(multMax,
                                                                                                 std::vector<double>(nSub, 0.))));
   //Loop over events
   int ievt = 0;
   if(analyzedEvts <= 0) analyzedEvts = nentries;

   while (ievt <= analyzedEvts) 
   {
      ch->GetEntry(ievt);

      if(!(ievt%100))
      {
         std::cout << 
         "\rPlotVnVm::INFO:: ievt = " << ievt 
         <<
         ", tree number = " << ch->GetTreeNumber()
         <<
         " ~~~> " << std::setprecision(3) << (double)((double)ievt / (double)analyzedEvts)*100  << " %" 
         << std::flush;
      }
      
      if(mult == 0) 
      {
         ++ievt;
         continue;
      }

      histBaseMult[ch->GetNtrees()]        ->Fill(mult); 
      histBaseEvtClass[ch->GetNtrees()]    ->Fill(classifier);
      histBaseMult[ch->GetTreeNumber()]    ->Fill(mult); 
      histBaseEvtClass[ch->GetTreeNumber()]->Fill(classifier);

      //Get mult, noff or cent
      int cbin = -1;
      cbin = (int) classifier;
      if(cbin < 0) 
      {
         ++ievt;
         //std::cout << 
         //"PlotVnVm::INFO:: ~~~> ievt = " << ievt << " has no centrality defined" 
         //<< std::endl;
         continue;
      }

      int cmult = (int) mult;
      if(cmult <= 0)
      {
         ++ievt;
         //std::cout << 
         //"PlotVnVm::INFO:: ~~~> ievt = " << ievt << " has no multiplicity defined" 
         //<< std::endl; 
         continue;
      }
      if(cmult >= multMax)
      {
         ++ievt;
         //std::cout << 
         //"PlotVnVm::INFO:: ~~~> ievt = " << ievt << " has out of range multiplicity" 
         //<< std::endl; 
         continue;
      }


      //N2 particle correlators
      vqNM[0][cbin][cmult] += CN2;
      //N4 particle correlators
      vqNM[1][cbin][cmult] += CN4;

      //weights
      //N2 particle correlators
      vwqNM[0][cbin][cmult] += wCN2;
      //N4 particle correlators
      vwqNM[1][cbin][cmult] += wCN4;

      // --- Variance
      int ntest = rand() % nSub;

      for(int itest = 0; itest < nSub; ++itest)
      {
         if(itest != ntest)
         {
            //N2 particle correlators
            vqNM_var[0][cbin][cmult][itest] += CN2;
            //N4 particle correlators
            vqNM_var[1][cbin][cmult][itest] += CN4;

            //weights
            //N2 particle correlators
            vwqNM_var[0][cbin][cmult][itest] += wCN2;
            //N4 particle correlators
            vwqNM_var[1][cbin][cmult][itest] += wCN4;
         }
      }

      ++ievt;
   }

   std::cout << std::endl;

   //Computing CNM at fixed multiplicity

   //Filling histograms
   std::cout << 
   "PlotVnVm::INFO:: Filling 2D histograms now..." 
   << std::endl;
   for(unsigned int ibin = 0; ibin < qNM->GetNbinsX(); ++ibin)
   {
      for(unsigned int iref = 0; iref < multMax; ++iref)
      {
         if(vwqNM[0][ibin][iref] != 0.)
         {
            //N2 particle correlators
            qNM->Fill(ibin+1, 0., ( vqNM[0][ibin][iref]/vwqNM[0][ibin][iref])
                                   *vwqNM[0][ibin][iref]);
         }
         if(vwqNM[0][ibin][iref] != 0. && vwqNM[1][ibin][iref] != 0.)
         {
            //N4 particle correlators
            qNM->Fill(ibin+1, 1., (  vqNM[1][ibin][iref]/vwqNM[1][ibin][iref] - 
                                   2*vqNM[0][ibin][iref]/vwqNM[0][ibin][iref] * vqNM[0][ibin][iref]/vwqNM[0][ibin][iref])
                                    *vwqNM[1][ibin][iref]);
         }

         if(vwqNM[0][ibin][iref] >= 0.)
         {
            //weights
            //N2 particle correlators
            qwNM->Fill(ibin+1, 0., vwqNM[0][ibin][iref]);
         }
         if(vwqNM[1][ibin][iref] >= 0.)
         {
            //weights
            //N4 particle correlators
            qwNM->Fill(ibin+1, 1., vwqNM[1][ibin][iref]);
         }

         for(int itest = 0; itest < nSub; ++itest)
         {
            if(vwqNM_var[0][ibin][iref][itest] != 0.)
            {
               //N2 particle correlators
               qNM_var[itest]->Fill(ibin+1, 0., ( vqNM_var[0][ibin][iref][itest]/vwqNM_var[0][ibin][iref][itest])
                                                 *vwqNM_var[0][ibin][iref][itest]);
            }
            if(vwqNM_var[0][ibin][iref][itest] != 0. && vwqNM_var[1][ibin][iref][itest] != 0.)
            {
               //N4 particle correlators
               qNM_var[itest]->Fill(ibin+1, 1., (  vqNM_var[1][ibin][iref][itest]/vwqNM_var[1][ibin][iref][itest] - 
                                                 2*vqNM_var[0][ibin][iref][itest]/vwqNM_var[0][ibin][iref][itest] * vqNM_var[0][ibin][iref][itest]/vwqNM_var[0][ibin][iref][itest])
                                                  *vwqNM_var[1][ibin][iref][itest]);
            }

            if(vwqNM_var[0][ibin][iref][itest] >= 0.)
            {
               //weights
               //N2 particle correlators
               qwNM_var[itest]->Fill(ibin+1, 0., vwqNM_var[0][ibin][iref][itest]);
            }
            if(vwqNM_var[1][ibin][iref][itest] >= 0.)
            {
               //weights
               //N4 particle correlators
               qwNM_var[itest]->Fill(ibin+1, 1., vwqNM_var[1][ibin][iref][itest]);
            }
         }
      }
   }

   //Free memory from huge vectors
   vqNM.clear();
   vwqNM.clear();
   std::vector< std::vector< std::vector<double> > >().swap(vqNM);       
   std::vector< std::vector< std::vector<double> > >().swap(vwqNM); 

   vqNM_var.clear();
   vwqNM_var.clear();
   std::vector< std::vector< std::vector< std::vector<double> > > >().swap(vqNM_var);       
   std::vector< std::vector< std::vector< std::vector<double> > > >().swap(vwqNM_var); 
}

   //--- Process
bool process(TFile* fin, std::string outputFileName, std::string evtclass, int nSub)
{
   const int nhist = fin->GetNkeys() + 1;
   //const int nhist = fin->GetNkeys() + 2;

   //init Tree
   TChain* ch = new TChain();
   initChain(fin, ch);

   std::cout <<
   "PlotVnVm::Number of trees in the TChain: " << ch->GetNtrees()
   << std::endl;

   //Create Base histograms
   std::vector<TH1D*> histBaseMult;
   std::vector<TH1D*> histBaseEvtClass;
   histBaseMult.resize(nhist); 
   histBaseEvtClass.resize(nhist);
   initBaseHist(nhist, histBaseMult, "Mult", "multiplicity", "N_{entries}");

   if     (evtclass == "Noff") initBaseHist(nhist, histBaseEvtClass, "Noff", "N_{trk}^{offline}" , "N_{entries}");
   else if(evtclass == "Cent") initBaseHist(nhist, histBaseEvtClass, "Cent", "centrality (%)"    , "N_{entries}");
   else
   {
      std::cout <<
      "PlotVnVm::ERROR: Event classifier ~~> " << evtclass.c_str() << " does not exist!!!"
      << std::endl;
      
      return false; 
   }
   //Create Cumulant histos
      //---Results
   TH2D* qNM;
   TH2D* qwNM;

   std::string xtitle = "";
   unsigned int nMax = noffMax;
   if(evtclass == "Noff") 
   {
      xtitle = "N_{trk}^{offline}";
      nMax   = 1800;
   }
   if(evtclass == "Cent") 
   {
      xtitle = "centrality (%)";
      nMax   = 200;
   }

   initHist(qNM  , Form("qNM_%s"  , evtclass.c_str()), xtitle.c_str(), "qNM"  , nMax, 2);     
   initHist(qwNM  , Form("qwNM_%s", evtclass.c_str()), xtitle.c_str(), "qwNM" , nMax, 2);     
      //---Variance
   std::vector<TH2D*> qNM_var;
   std::vector<TH2D*> qwNM_var;
   qNM_var.resize(nSub);
   qwNM_var.resize(nSub);
   for(unsigned int itest = 0; itest < nSub; ++itest)
   {
      initHist(qNM_var[itest]  , Form("qNM_%s_test%d"  , evtclass.c_str(), itest), xtitle.c_str(), "qNM"  , nMax, 2);     
      initHist(qwNM_var[itest] , Form("qwNM_%s_test%d" , evtclass.c_str(), itest), xtitle.c_str(), "qwNM" , nMax, 2);     
   } 

   //-----------------------------
   //Loop on chain an fill stuff!!!
   loopOnChain(ch, nSub, evtclass,
               histBaseMult, histBaseEvtClass,
               qNM, qwNM,
               qNM_var, qwNM_var);
   //-----------------------------

   //Write base histograms ...
   std::cout <<
   "PlotVnVm::INFO::Base histograms will be filled and saved"
   << std::endl;

   drawBaseHist(nhist, histBaseMult, outputFileName);
   drawBaseHist(nhist, histBaseEvtClass, outputFileName);

     //-- ... and delete them 

   for(int ihist = 0; ihist < nhist; ++ihist)
   {
      delete histBaseMult[ihist];
      delete histBaseEvtClass[ihist];
   }
   histBaseMult.clear(); 
   histBaseEvtClass.clear();
   std::vector<TH1D*>().swap(histBaseMult); 
   std::vector<TH1D*>().swap(histBaseEvtClass);
   //---
   //Write cumulant histogram ...
   std::cout <<
   "PlotVnVm::INFO::Cumulant histograms will be filled and saved"
   << std::endl;

   drawCumuHist(qNM, qNM_var, qwNM, qwNM_var, outputFileName);

     //-- ... and delete them
   delete qNM;
   delete qwNM;
   for(unsigned int itest = 0; itest < nSub; ++itest)
   {
      delete qNM_var[itest];
      delete qwNM_var[itest];
   }
   qNM_var.clear();
   qwNM_var.clear();
   std::vector<TH2D*>().swap(qNM_var);   
   std::vector<TH2D*>().swap(qwNM_var);   

   //Delete TChain
   ch->Delete();

   return true;
}

   //--- Computes
void compute(std::string outputFileName, 
             std::string evtclass, int nSub,
             int nbins, double binning[],
             const int nhist)
{
   //Write cumulant histogram ...
   std::cout <<
   "PlotVnVm::INFO::Compute cumulant in large bins"
   << std::endl;

   std::string xtitle = "";
   if     (evtclass == "Cent") xtitle = "centrality (%)";
   else if(evtclass == "Noff") xtitle = "N_{trk}^{off}";


   std::cout <<
   "PlotVnVm::INFO::Initialize histograms"
   << std::endl;

   TH1D* hCN2x = 0x0;
   TH1D* hCN4x = 0x0;

   initHist(hCN2x, colors[0], "CN2x", nbins, binning, xtitle.c_str(), "C_{n}{2}");
   initHist(hCN4x, colors[1], "CN4x", nbins, binning, xtitle.c_str(), "C_{n}{4}");

   TH1D* hVN2x = 0x0;
   TH1D* hVN4x = 0x0;

   initHist(hVN2x, colors[0], "VN2x", nbins, binning, xtitle.c_str(), "v_{n}{2}");
   initHist(hVN4x, colors[1], "VN4x", nbins, binning, xtitle.c_str(), "v_{n}{4}");

   std::vector<TH1D*> hCN2xvar;
   std::vector<TH1D*> hCN4xvar;
   hCN2xvar.resize(nSub);
   hCN4xvar.resize(nSub);

   std::vector<TH1D*> hVN2xvar;
   std::vector<TH1D*> hVN4xvar;
   hVN2xvar.resize(nSub);
   hVN4xvar.resize(nSub);

   for(int itest = 0; itest < nSub; ++itest)
   {
      hCN2xvar[itest] = 0x0; 
      hCN4xvar[itest] = 0x0;

      initHist(hCN2xvar[itest], colors[0], Form("CN2xvar%d",itest), nbins, binning, xtitle.c_str(), "C_{n}{2}");
      initHist(hCN4xvar[itest], colors[1], Form("CN4xvar%d",itest), nbins, binning, xtitle.c_str(), "C_{n}{4}");

      hVN2xvar[itest] = 0x0;
      hVN4xvar[itest] = 0x0;

      initHist(hVN2xvar[itest], colors[0], Form("V2xvar%d",itest), nbins, binning, xtitle.c_str(), "v_{n}{2}");
      initHist(hVN4xvar[itest], colors[1], Form("V4xvar%d",itest), nbins, binning, xtitle.c_str(), "v_{n}{4}");
   }

   //Get histo from files
   std::cout <<
   "PlotVnVm::INFO::Getting 2D-histograms"
   << std::endl;

   TH2D* qNM   = getFromFile(outputFileName, Form("hqNM_%s"  , evtclass.c_str()));
   TH2D* qwNM  = getFromFile(outputFileName, Form("hqwNM_%s" , evtclass.c_str()));
   std::vector<TH2D*> qNM_var;
   std::vector<TH2D*> qwNM_var;
   for(int itest = 0; itest < nSub; ++itest)
   {
      qNM_var.push_back(getFromFile(outputFileName  , Form("hqNM_%s_test%d"  , evtclass.c_str() , itest)));
      qwNM_var.push_back(getFromFile(outputFileName  , Form("hqwNM_%s_test%d"  , evtclass.c_str() , itest)));
   }

   //Calculate quantities
   std::cout <<
   "PlotVnVm::INFO::Loop for calculations"
   << std::endl;

   int trkcnter = 0;
   for(int ibin = 0; ibin < nbins; ++ibin)
   {
      double qN2x = 0.;
      double qN4x = 0.;
      double wN2x = 0.;
      double wN4x = 0.;

      std::vector<double> qN2xvar;
      std::vector<double> qN4xvar;
      std::vector<double> wN2xvar;
      std::vector<double> wN4xvar;
      qN2xvar.resize(nSub);
      qN4xvar.resize(nSub);
      wN2xvar.resize(nSub);
      wN4xvar.resize(nSub);

      for(int itest = 0; itest < nSub; ++itest)
      {
          qN2xvar[itest] = 0.;
          qN4xvar[itest] = 0.;
          wN2xvar[itest] = 0.;
          wN4xvar[itest] = 0.;
      }

      while(trkcnter < binning[ibin+1])
      {

          qN2x += qNM->GetBinContent(trkcnter+1, 1);
          qN4x += qNM->GetBinContent(trkcnter+1, 2);
         
          wN2x += qwNM->GetBinContent(trkcnter+1, 1);
          wN4x += qwNM->GetBinContent(trkcnter+1, 2);

          for(int itest = 0; itest < nSub; ++itest)
          {
             //N2 particle correlators
             qN2xvar[itest] += qNM_var[itest]->GetBinContent(trkcnter+1, 1);
             //N4 particle correlators                                             
             qN4xvar[itest] += qNM_var[itest]->GetBinContent(trkcnter+1, 2);
             //weights
             //N2 particle correlators
             wN2xvar[itest] += qwNM_var[itest]->GetBinContent(trkcnter+1, 1);
             //N4 particle correlators                                             
             wN4xvar[itest] += qwNM_var[itest]->GetBinContent(trkcnter+1, 2);
          }
          ++trkcnter;
      }

      if(wN2x != 0.) qN2x /= wN2x;
      if(wN4x != 0.) qN4x /= wN4x;

      hCN2x->SetBinContent(ibin+1, qN2x);
      hCN4x->SetBinContent(ibin+1, qN4x);

      if(qN2x >= 0.) hVN2x->SetBinContent(ibin+1, TMath::Sqrt(qN2x));
      if(qN4x <= 0.) hVN4x->SetBinContent(ibin+1, TMath::Power(-1*qN4x,1./4.));

      //Fill variance histos
      double varCN2 = 0.;
      double varCN4 = 0.;

      double varVN2 = 0.;
      double varVN4 = 0.;

      for(int itest = 0; itest < nSub; ++itest)
      {
         if(wN2xvar[itest] != 0.) qN2xvar[itest] /= wN2xvar[itest];
         if(wN4xvar[itest] != 0.) qN4xvar[itest] /= wN4xvar[itest];

         //Fill histograms
         hCN2xvar[itest]->SetBinContent(ibin+1,qN2xvar[itest]);
         hCN4xvar[itest]->SetBinContent(ibin+1,qN4xvar[itest]);

         if(qN2xvar[itest] >= 0.) hVN2xvar[itest]->SetBinContent(ibin+1,TMath::Sqrt(qN2xvar[itest]));
         if(qN4xvar[itest] <= 0.) hVN4xvar[itest]->SetBinContent(ibin+1,TMath::Power(-1*qN4xvar[itest],1./4.));

         //Get Variance
         varCN2 += (hCN2xvar[itest]->GetBinContent(ibin+1) - hCN2x->GetBinContent(ibin+1))*(hCN2xvar[itest]->GetBinContent(ibin+1) - hCN2x->GetBinContent(ibin+1)); 
         varCN4 += (hCN4xvar[itest]->GetBinContent(ibin+1) - hCN4x->GetBinContent(ibin+1))*(hCN4xvar[itest]->GetBinContent(ibin+1) - hCN4x->GetBinContent(ibin+1)); 

         varVN2 += (hVN2xvar[itest]->GetBinContent(ibin+1) - hVN2x->GetBinContent(ibin+1))*(hVN2xvar[itest]->GetBinContent(ibin+1) - hVN2x->GetBinContent(ibin+1)); 
         varVN4 += (hVN4xvar[itest]->GetBinContent(ibin+1) - hVN4x->GetBinContent(ibin+1))*(hVN4xvar[itest]->GetBinContent(ibin+1) - hVN4x->GetBinContent(ibin+1)); 
      }
      
      varCN2 *= (double) (nSub-1)/nSub;
      varCN4 *= (double) (nSub-1)/nSub;
     
      varVN2 *= (double) (nSub-1)/nSub;
      varVN4 *= (double) (nSub-1)/nSub;

      hCN2x->SetBinError(ibin+1, TMath::Sqrt(varCN2));
      hCN4x->SetBinError(ibin+1, TMath::Sqrt(varCN4));

      hVN2x->SetBinError(ibin+1, TMath::Sqrt(varVN2));
      hVN4x->SetBinError(ibin+1, TMath::Sqrt(varVN4));
   }
   
   drawCHist(hCN2x, outputFileName);
   drawCHist(hCN4x, outputFileName);
   drawCHist(hVN2x, outputFileName);
   drawCHist(hVN4x, outputFileName);

   TGraphErrors* grCN2x;
   TGraphErrors* grCN4x;
   TGraphErrors* grVN2x;
   TGraphErrors* grVN4x;
   drawGraphFromHist(grCN2x, hCN2x, evtclass, outputFileName, nhist);
   drawGraphFromHist(grCN4x, hCN4x, evtclass, outputFileName, nhist);
   drawGraphFromHist(grVN2x, hVN2x, evtclass, outputFileName, nhist);
   drawGraphFromHist(grVN4x, hVN4x, evtclass, outputFileName, nhist);
}

//-------------------
//main
int main(int argc, char** argv)
{
   gStyle->SetOptStat(110);

   unsigned int nrj     = 5;
   unsigned int version = atoi(argv[1]);
   std::string evtclass = argv[2];
   std::string system   = argv[3];
   unsigned int nSub    = 5;
   std::string inputFileName  = "../test/cumulants.root";

   std::string userString = argv[4];
   std::string outputFileName = Form("../output/%s_cmsNrj%d_v%d_%s_sub%d", system.c_str(), nrj, version, evtclass.c_str(), nSub);

   if(evtclass == "Cent")
   {
      noffMax = 200;
      multMax = 2000;
   }
   else if(evtclass == "Noff")
   {
      noffMax = 1000;
      multMax = 1800;
   }

   const int nbinsCent = 10;
   double binningCent[nbinsCent+1] = {0, 10, 20, 40, 60, 80, 100, 120, 140, 160, 200}; 
   const int nbinsNoff = 34;
   double binningNoff[nbinsNoff+1] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 100, 
                                      120, 135, 150, 160, 185, 210, 230, 250, 270, 300, 
                                      330, 350, 370, 390, 420, 450, 500, 550, 600, 750,
                                      800, 850, 900, 950,
                                      (double)noffMax};

   checkArg(argc,argv);

   //output file
   if(userString != "")
   {
      outputFileName += Form("_%s", userString.c_str());
   }
   outputFileName += ".root";
   std::cout << "The output file will be: " << outputFileName.c_str() << std::endl;
      //--- Create once
   if(isProcess)
   {
      TFile fout(outputFileName.c_str(),"RECREATE");
      fout.Close();
   }

   ////path to data
   //std::string path = "";
   //if(nrj == 8)
   //{
   //   path += Form("/Volumes/Elements/%sdata/datafiles/v24/", system.c_str());
   //}
   //else
   //{
   //   path += Form("/Volumes/Elements/%sdata/datafiles/v24/", system.c_str());
   //}

   //input file
   TString fileLocation("");
   fileLocation.Append(inputFileName.c_str());
   TFile* fin = TFile::Open(fileLocation.Data(), "READ");

   std::cout << "Trying to open input file: " << fileLocation.Data() << std::endl;

   if(!fin)
   {
      std::cout <<
      "PlotVnVm::ERROR::Input file " << inputFileName << " does not exist"
      << std::endl;
      return 0;
   }
   if(!fin->IsOpen())
   {
      std::cout <<
      "PlotVnVm::ERROR::Input file " << inputFileName << " could not be open"
      << std::endl;
      return 0;
   }
   else
   {
      fin->ls();
   }

   if(isProcess) process(fin, outputFileName, evtclass, nSub);

   const int nhist = fin->GetNkeys() + 1;

   fin->Close();
   delete fin;

   
   if(evtclass == "Cent") compute(outputFileName, evtclass, nSub, nbinsCent, binningCent, nhist);
   if(evtclass == "Noff") compute(outputFileName, evtclass, nSub, nbinsNoff, binningNoff, nhist);

   return 0;
}
//-------------------
   //--- Implemetation of histos initializer
void SetHistoStyle(TH1D*& hist,
                   int color,
                   std::string xtitle,
                   std::string ytitle)
{
      hist->SetFillColor(0);
      hist->SetMarkerStyle(20);
      hist->SetLineColor(color);
      hist->SetMarkerColor(color);

      hist->GetXaxis()->SetTitle(xtitle.c_str());
      hist->GetYaxis()->SetTitle(ytitle.c_str());
}

void SetHistoStyle(TH2D*& hist,
                   std::string option,
                   std::string xtitle,
                   std::string ytitle)
{
      hist->SetFillColor(0);
      hist->SetDrawOption(option.c_str());

      hist->GetXaxis()->SetTitle(xtitle.c_str());
      hist->GetYaxis()->SetTitle(ytitle.c_str());
}

void initHist(TH1D*& hist, 
              int color,
              std::string histname,
              std::string xtitle,
              std::string ytitle)
{
      hist = new TH1D(Form("h%s", histname.c_str()),
                      Form("%s",  histname.c_str()),
                      1000,
                      0.5, 1000.5);
      SetHistoStyle(hist, color, xtitle, ytitle);
}

void initHist(TH2D*& hist, 
              std::string histname, 
              std::string xtitle,
              std::string ytitle,
              int binx, 
              int biny)
{
   hist = new TH2D(Form("h%s", histname.c_str()),
                   Form("%s",histname.c_str()),
                   binx,
                   0., (double)binx,
                   biny,
                   0, (double)biny);
  SetHistoStyle(hist, "colz", xtitle, ytitle);
}

void initHist(TH1D*& hist,
              int color, 
              std::string histname,
              int nbins,
              double binval[],
              std::string xtitle,
              std::string ytitle)
{
      hist = new TH1D(Form("h%s", histname.c_str()),
                      Form("%s",histname.c_str()),
                      nbins,
                      binval);
      SetHistoStyle(hist, color, xtitle, ytitle);
}

void initBaseHist(int nhist,
                  std::vector<TH1D*>& hist,
                  std::string histname,
                  std::string xtitle,
                  std::string ytitle)
{
   for(int ihist = 0; ihist < nhist; ++ihist)  
   {
      initHist(hist[ihist], colors[ihist], Form("%s_%d", histname.c_str(), ihist), xtitle, ytitle);
   } 
}


void drawBaseHist(int nhist,
                  std::vector<TH1D*> hist,
                  std::string outFileName)
{
   TFile* fout = new TFile(outFileName.c_str(),"UPDATE");

   for(int ihist = 0; ihist < nhist; ++ihist)  
   {
      hist[ihist]->Write();
   }

   fout->Close();
   delete fout;
}

void drawCumuHist(TH2D* hist,
                  std::vector<TH2D*> hist_var,
                  TH2D* histW,
                  std::vector<TH2D*> histW_var,
                  std::string outFileName)
{
   TFile* fout = new TFile(outFileName.c_str(),"UPDATE");

   hist->Write();
   histW->Write();
   for(int ihist = 0; ihist < hist_var.size(); ++ihist)  
   {
      hist_var[ihist]->Write();
      histW_var[ihist]->Write();
   }

   fout->Close();
   delete fout;
}

void drawCHist(TH1D* hist,
                std::string outFileName)
{
   TFile* fout = new TFile(outFileName.c_str(),"UPDATE");

   if(fout->GetListOfKeys()->Contains(hist->GetName()))
   {
      std::cout <<
      "PlotVnVm::WARRNING::Histo " << hist->GetName() << " already exist. It will be deleted"
      << std::endl;
      fout->Delete(Form("%s;*", hist->GetName()));
   }
   hist->Write();

   fout->Close();
   delete fout;
}

TH2D* getFromFile(std::string outFileName, std::string name)
{
   TH2D* htmp;
   TFile * fout = new TFile(outFileName.c_str(), "READ");

   htmp = (TH2D*) fout->Get(name.c_str());
   htmp->SetDirectory(0);

   fout->Close();
   delete fout; 

   return htmp;
}

void drawGraphFromHist(TGraphErrors*& gr, 
                       TH1D* hist, std::string evtclass,
                       std::string outFileName,
                       const int nhist)
{
   TFile* fout = new TFile(outFileName.c_str(),"UPDATE");
   TH1D* hevtclass = (TH1D*) fout->Get(Form("h%s_%d", evtclass.c_str(), nhist-1));
   if(fout->GetListOfKeys()->Contains(Form("graph_%s",hist->GetName())))
   {
      std::cout <<
      "PlotVnVm::WARRNING::Graph " << hist->GetName() << " already exist. It will be deleted"
      << std::endl;
      fout->Delete(Form("%s;*", Form("graph_%s",hist->GetName())));
   }

   gr = new TGraphErrors();
   gr->GetXaxis()->SetTitle(hevtclass->GetXaxis()->GetTitle());
   //gr->GetXaxis()->SetRangeUser(0, noffMax);
   gr->GetYaxis()->SetTitle(hist->GetYaxis()->GetTitle());
   gr->SetMarkerStyle(20);
   gr->SetMarkerColor(hist->GetMarkerColor());
   gr->SetLineColor(hist->GetLineColor());

   double noff = 0.;
   double errnoff = 0.;
   int cnt = 0;
   int ip =0;

   //std::cout << 
   //"PlotVnVm::TEST::Hist ~~> " << hist->GetName()
   //<< std::endl;

   for(int ibin = 0; ibin < hist->GetNbinsX(); ++ibin)
   {
      //while(hevtclass->GetBinCenter(cnt+1) <=  hist->GetBinLowEdge(ibin+1) + hist->GetBinWidth(ibin+1) &&
      //      hevtclass->GetBinCenter(cnt+1) >   hist->GetBinLowEdge(ibin+1))
      //{
      //   noff += hevtclass->GetBinCenter(cnt+1)*hevtclass->GetBinContent(cnt+1)*hevtclass->GetBinContent(cnt+1);
      //   errnoff += hevtclass->GetBinContent(cnt+1)*hevtclass->GetBinContent(cnt+1);

      //   cnt++;
      //}

      hevtclass->GetXaxis()->SetRangeUser(hist->GetBinLowEdge(ibin+1), hist->GetBinLowEdge(ibin+1) + hist->GetBinWidth(ibin+1));
      noff    = hevtclass->GetMean(); 
      errnoff = hevtclass->GetMeanError(); 

      //if(noff != 0. && errnoff != 0.)
      //{
      //   gr->SetPoint(ip, noff/errnoff, hist->GetBinContent(ibin+1));
      //   gr->SetPointError(ip, 1./TMath::Sqrt(errnoff), hist->GetBinError(ibin+1));

      //   noff = 0.;
      //   errnoff = 0.;
      //   ip++;
      //}
      if(noff != 0.)
      {
         gr->SetPoint(ip, noff, hist->GetBinContent(ibin+1));
         gr->SetPointError(ip, errnoff, hist->GetBinError(ibin+1));

         noff = 0.;
         errnoff = 0.;
         ip++;
      }
   }

   gr->Write(Form("graph_%s",hist->GetName()));

   fout->Close();
   delete fout;
}
