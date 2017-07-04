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
// logging library
#define LOGURU_IMPLEMENTATION 1
#include "../interface/MultiCumulants/vendor/loguru/loguru.hpp"
#include "../interface/MultiCumulants/vendor/cmdline.h"
//utlis include
#include "utils.h"

using namespace std;

int 
main(int argc, char** argv) {
//--------------------------------------------------------
//================ Init debug library ====================
//--------------------------------------------------------
	loguru::set_thread_name("MAIN");
	// logs everything to the debug.log file every run
	loguru::add_file("bin/debug.log", loguru::Truncate, loguru::Verbosity_MAX);

	// sometimes the "stream" form of the logger is more convenient, use LOG_S( LEVEL ) << "MESSAGE";
	// No need for an endl at the end of a line

//--------------------------------------------------------
//=========== Command parser configuration ===============
//--------------------------------------------------------
	cmdline::parser parser;
	parser.add<std::string>("output", '\0', "output file name and path", false, "../output/cnm_vnm.root");
	parser.add<std::string>("input", '\0', "input file name and path", false, "../test/cumulants.root");
	parser.add<int>("noffmax", '\0', "maximum N_{trk}^offline", false, 500);
	parser.add<int>("cumumaxorder", '\0', "maximum cumulant order", false, 4);
	parser.add<int>("harmonicorder", '\0', "maximum cumulant order", false, 2);
	parser.add<int>("nevents", '\0', "Number of events to be analyzed", false, -1);
	parser.add("process", '\0', "process TTree");
	parser.parse_check( argc, argv );

	std::cout << parser.usage() << endl;

//--------------------------------------------------------
//================== Start Analysis ======================
//--------------------------------------------------------

        gStyle->SetOptStat(110);
        std::string inputFileName  = parser.get<std::string>( "input" );
        std::string outputFileName = parser.get<std::string>( "output" );

        const int noffmax = parser.get<int>( "noffmax" );
        const int multmax = 2*noffmax;
        const int cumumaxorder  = parser.get<int>( "cumumaxorder" );
        const int harmonicorder = parser.get<int>( "harmonicorder" );
        const int nevents = parser.get<int>( "nevents" );

        const int nbins = 30;
        int binarray[nbins+1] = {0,   10,  20,  30,  40,  50,  60,  70,  80,  90,
                                 100, 110, 120, 130, 140, 150, 160, 170, 180, 190,
                                 200, 210, 220, 230, 240, 250, 260, 270, 280, 290,
                                 noffmax};

        //input file
        TFile* fin  = TFile::Open(inputFileName.c_str(), "READ");
        //output file
        TFile* fout = 0x0;
        if(parser.exist( "process" ))
        { 
           //Check that inputfile is found and properly open
           LOG_S(INFO) << "Trying to open file: " << inputFileName.c_str();

           if(!fin)
           {
              LOG_S(ERROR) << "Cannot open file: " << inputFileName.c_str() << ", file not found in the given path";
              return 0;
           }
           if(!fin->IsOpen())
           {
              LOG_S(ERROR) << "Cannot open file: " << inputFileName.c_str() << ", file might be corrupted";
              return 0;
           }
           else
           {
              LOG_S(INFO) << "File " << inputFileName.c_str() << " successfully opened!";
              fin->ls();
           }

           //if process, recreate output file
           fout = TFile::Open(outputFileName.c_str(), "RECREATE");

           //process the tree
           utils::process(fin, fout, 
                          noffmax, multmax, 
                          cumumaxorder, harmonicorder, 
                          nbins, binarray,
                          nevents);
           
        }
        else
        {
           //if no process just update the output file
           fout = TFile::Open(outputFileName.c_str(), "UPDATE");
        }

        fin->Close();
        delete fin;
   
        fout->Close();
        delete fout;
   
        return 0;
}
