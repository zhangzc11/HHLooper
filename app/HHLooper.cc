//C++ INCLUDES
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
//ROOT
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "hhtree.hh"
#include "anautil.h"
#include <stdlib.h>

using namespace std;

int lumi = 137000.0;

int main ( int argc, char* argv[])
{

if(argc < 5) 
{
 cout<<"ERROR  - not enough arguments: need input(file, dir, or list) outputFileName label isData"<<endl;
 return 0;
}


std::string input = argv[1];
std::string outputFileName = argv[2];
std::string label = argv[3];
std::string isData_ = argv[4];

system("mkdir -p hists");
system(("mkdir -p hists/"+label).c_str());

bool isData = false;
if(isData_ == "1" || isData_ == "true" || isData_ == "yes" || isData_ == "True" || isData_ == "Yes") isData = true;
if(isData) lumi = 137.0/42.0; //scale 2017 to full run2

std::vector<std::string> list_chain;


if(input.find(".root") != std::string::npos) list_chain.push_back(input);//a file is given
else if (input.find(",") != std::string::npos)//a list is given, separated by ","
{
  int a =0;
  int b=input.find(",");
  while(1)
  {
	std::string thisFile = input.substr(a,b-a);
	list_chain.push_back(thisFile);
	a = b+1;
	if(input.find(",", a) != std::string::npos) b = input.find(",", a);
	else
	{
		b = input.size();
		std::string thisFile = input.substr(a,b-a);
		list_chain.push_back(thisFile);
	}
  }
  
}
else //a directory is given
{
  DIR* dirp = opendir(input.c_str());
  struct dirent * dp;
  while ((dp = readdir(dirp)) != NULL)
  {
	std::string thisFile = dp->d_name;
	if(thisFile.find(".root") == std::string::npos) continue;
	list_chain.push_back((input+"/"+thisFile));
  }

}

TChain * chain = new TChain("hh");
for(int idx = 0; idx < list_chain.size(); idx++) chain->Add(list_chain[idx].c_str());
int nEntries = chain->GetEntries();
cout<<"total number of events to process: "<<nEntries<<endl;

TFile *outfile = new TFile(("hists/"+label+"/"+outputFileName).c_str(), "recreate");

RooUtil::Cutflow cutflow;
RooUtil::Histograms histograms;

//define histograms
histograms.addHistogram("yield",               "; yield; Events",                      1,     0.,   1.,    [&]() { return 0; } );
histograms.addHistogram("hh_pt",               "; p_{T}^{HH} (GeV); Events",           30,   0.,   900.,  [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_mass",             "; m_{HH} (GeV); Events",               30,   0.,   900.,  [&]() { return hh.hh_mass(); } );
histograms.addHistogram("FatJet1_msoftdrop",   "; j_{1} soft drop mass (GeV); Events", 30,   0.,   200.,  [&]() { return hh.nFatJet() > 0 ? hh.FatJet_msoftdrop()[0] : -999; } );
histograms.addHistogram("FatJet2_msoftdrop",   "; j_{2} soft drop mass (GeV); Events", 30,   0.,   200.,  [&]() { return hh.nFatJet() > 1 ? hh.FatJet_msoftdrop()[1] : -999; } );
histograms.addHistogram("FatJet1_btagDDBvL",   "; j_{1} DDB tagger; Events",           30,   0.,   1.0,   [&]() { return hh.nFatJet() > 0 ? hh.FatJet_btagDDBvL()[0] : -999; } );
histograms.addHistogram("FatJet2_btagDDBvL",   "; j_{2} DDB tagger; Events",           30,   0.,   1.0,   [&]() { return hh.nFatJet() > 1 ? hh.FatJet_btagDDBvL()[1] : -999; } );
histograms.addHistogram("FatJet1_pt",          "; p_{T}^{j1} (GeV); Events",           30,   0.,   900.,  [&]() { return hh.nFatJet() > 0 ? hh.FatJet_pt()[0] : -999; } );
histograms.addHistogram("FatJet2_pt",          "; p_{T}^{j2} (GeV); Events",           30,   0.,   900.,  [&]() { return hh.nFatJet() > 1 ? hh.FatJet_pt()[1] : -999; } );

//define cuts
cutflow.setTFile(outfile);
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.weight(); });
cutflow.addCutToLastActiveCut("TwoFatJets",         [&](){ return hh.nFatJet() >= 2; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut",      [&](){ return hh.FatJet_btagDDBvL()[0] > 0.9 && hh.FatJet_btagDDBvL()[1] > 0.9; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCut",       [&](){ return hh.FatJet_pt()[0] > 300.0 && hh.FatJet_pt()[1] > 300.0; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[0] > 110.0 && hh.FatJet_msoftdrop()[0] < 150.0 && hh.FatJet_msoftdrop()[1] > 110.0 && hh.FatJet_msoftdrop()[1] < 150.0; },   UNITY);
//cutflow.addCutToLastActiveCut("HLTCut",             [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);

//book histograms for cuts
cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
cutflow.bookCutflows();

int iEntry = 0;
for(int idx = 0; idx < list_chain.size(); idx++)
{
  cout<<"[INFO] processing file: "<<list_chain[idx]<<endl;
  TTree * tree_this;
  TFile * file_this = new TFile(list_chain[idx].c_str(), "READ");
  tree_this = (TTree*)file_this->Get("hh");
  hh.Init(tree_this);
  int nEntries_this = tree_this->GetEntries();
  for(int iEntry_this=0; iEntry_this<nEntries_this; iEntry_this++)
  {
	hh.GetEntry(iEntry_this);
	cutflow.fill();
	if(iEntry%1000 == 0) cout<<"[INFO] processing event "<<iEntry<<" / "<<nEntries<<endl;
	iEntry ++;
  }
  delete tree_this;
  file_this->Close();
  delete file_this;
}

//save histograms
cutflow.saveOutput();
outfile->Close();


return 0;
}
