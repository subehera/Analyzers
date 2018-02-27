#ifndef CHAINBUILDER_H
#define CHAINBUILDER_H

#include <iostream>
#include <glob.h>
#include <vector>
#include <TChain.h>

class ChainBuilder
{
public:
   ChainBuilder()
   {
      ch_ = new TChain();
   }

   ~ChainBuilder() 
   {
      ch_->Reset(); 
      delete ch_;
      fileList_.clear();
      std::vector<std::string>().swap(fileList_);
      paths_.clear(); 
      std::vector<std::string>().swap(paths_);
   }

   TChain* GetChain() { return ch_; }

   void BuildChain(TString folder)
   {
      for(unsigned int ifile = 0; ifile < fileList_.size(); ++ifile)
      {
         TString keyName = fileList_[ifile];
         keyName.Append("/");
         keyName.Append(folder.Data());
         keyName.Append("/trEvent");

         //LOG_S(INFO) << "TTree named " << keyName.Data() << " will be added to the TChain";
         ch_->Add(keyName.Data());
      }
   }

   void AddDir(std::string path)
   {
      paths_.push_back(path);
   }

   void ReadDir()
   {
      for(unsigned idir = 0; idir < paths_.size(); ++idir)
      {
         std::string pattern = paths_[idir];

         std::vector<std::string> tmp = FindFiles(pattern);
         fileList_.insert( fileList_.end(), tmp.begin(), tmp.end());
         tmp.clear();
         std::vector<std::string>().swap(tmp);
      }
   }

   void PrintList()
   {
      for(std::vector<std::string>::iterator it = fileList_.begin(); it != fileList_.end(); ++it) 
      {
          std::cout << *it << std::endl;
      }
   }

   std::vector<std::string> FindFiles(const std::string& pattern)
   {
       glob_t glob_result;
       glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
       std::vector<std::string> files;

       for(unsigned int i=0;i<glob_result.gl_pathc;++i)
       {
           files.push_back(std::string(glob_result.gl_pathv[i]));
       }

       globfree(&glob_result);
       return files;
   }

   bool isEmpty()
   {
      if( fileList_.size() != 0 ) return false;
      else                        return true;
   }

private:
   std::vector<std::string> fileList_;
   std::vector<std::string> paths_;
   TChain* ch_;
};

#endif
