//C++ INCLUDES
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
//ROOT
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>
#include <TRandom3.h>
//LOCAL INCLUDES
#include "hhtree.hh"
#include "anautil.h"
#include "scalefactors.h"

using namespace std;

double lumi = 139.0;
TRandom3* r_nominal = new TRandom3(0);
const float pi = 3.141592653;


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
bool saveSkim = false;
bool doSystematics = false;

if(argc > 5)
{
  std::string s_syst = argv[5];
  if(s_syst == "1" || s_syst == "syst" || s_syst == "yes") doSystematics = true; 
}

if(argc > 6)
{
  std::string s_skim = argv[6];
  if(s_skim == "1" || s_skim == "skim" || s_skim == "yes") saveSkim= true; 
}

system("mkdir -p hists");
system(("mkdir -p hists/"+label).c_str());

std::string year_ = "all";
if(input.find("2016") != std::string::npos) {year_ = "2016"; lumi = 36.2;}
if(input.find("2017") != std::string::npos) {year_ = "2017"; lumi = 44.3;}
if(input.find("2018") != std::string::npos) {year_ = "2018"; lumi = 58.5;}
system(("mkdir -p hists/"+label+"/"+year_).c_str());

bool isData = false;
if(isData_ == "1" || isData_ == "true" || isData_ == "yes" || isData_ == "True" || isData_ == "Yes") isData = true;

if(isData) lumi = 1.0;

if(outputFileName.find("HH") != std::string::npos) lumi = lumi * 2.27e-3; //HH fix


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

TChain * chain = new TChain("output");
for(int idx = 0; idx < list_chain.size(); idx++) chain->Add(list_chain[idx].c_str());
int nEntries = chain->GetEntries();
cout<<"total number of events to process: "<<nEntries<<endl;

TFile *outfile = new TFile(("hists/"+label+"/"+year_+"/"+outputFileName).c_str(), "recreate");
TFile *outfile_skim;
if(saveSkim) outfile_skim = new TFile(("hists/"+label+"/"+year_+"/"+outputFileName.replace(outputFileName.find(".root"), 5, "_skim.root")).c_str(), "recreate");

RooUtil::Cutflow cutflow;
RooUtil::Histograms histograms;


//************define histograms**********//
histograms.addHistogram("yield",               "; yield; Events",                      1,    0.,   1.,    [&]() { return 0; } );

histograms.addHistogram("gnn_score",   "; GNN score; Events", 300,   0.,   1.,  [&]() { return  hh.gnn_score(); } );

histograms.addHistogram("ph_pt1",   "; p_{T}^{#gamma 1} (GeV); Events", 300,   0.,   300.,  [&]() { return  hh.ph_pt1(); } );
histograms.addHistogram("ph_eta1",               "; #eta^{#gamma 1}; Events",                 200,   -5.0,  5.0,  [&]() { return hh.ph_eta1(); } );
histograms.addHistogram("ph_phi1",               "; #Phi^{#gamma 1}; Events",                 200,   -3.2,  3.2,  [&]() { return hh.ph_phi1(); } );

histograms.addHistogram("ph_pt2",   "; p_{T}^{#gamma 2} (GeV); Events", 300,   0.,   300.,  [&]() { return  hh.ph_pt1(); } );
histograms.addHistogram("ph_eta2",               "; #eta^{#gamma 2}; Events",                 200,   -5.0,  5.0,  [&]() { return hh.ph_eta2(); } );
histograms.addHistogram("ph_phi2",               "; #Phi^{#gamma 2}; Events",                 200,   -3.2,  3.2,  [&]() { return hh.ph_phi2(); } );

//************define cuts**********//

cutflow.setTFile(outfile);


////Pre-selection cuts
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.m_weight(); });
cutflow.addCutToLastActiveCut("CutPhPtOverMgg",       [&](){ return hh.ph_pt1()/hh.m_mgg() > 0.35 && hh.ph_pt2()/hh.m_mgg() < 0.25;}, UNITY); 
cutflow.addCutToLastActiveCut("CutMgg",       [&](){ return hh.m_mgg() > 105.0 && hh.m_mgg() < 160.0;}, UNITY); 
cutflow.addCutToLastActiveCut("CutNbVeto",       [&](){ return hh.m_nbjet_fixed80() < 2;}, UNITY); 

//book histograms for cuts
cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
cutflow.bookCutflows();

int iEntry = 0;

if(saveSkim) outfile_skim->cd();
TTree *tree_out;

float m_weight;
float ph_pt1;

if(saveSkim)
{ 
tree_out = new TTree("output", "output skim tree");
tree_out->Branch("m_weight", &m_weight, "m_weight/F");
tree_out->Branch("ph_pt1", &ph_pt1, "ph_pt1/F");
}

for(int idx = 0; idx < list_chain.size(); idx++)
{
  cout<<"[INFO] processing file: "<<list_chain[idx]<<endl;
  TTree * tree_this;
  TFile * file_this = new TFile(list_chain[idx].c_str(), "READ");
  tree_this = (TTree*)file_this->Get("output");
  hh.Init(tree_this);
  int nEntries_this = tree_this->GetEntries();
  for(int iEntry_this=0; iEntry_this<nEntries_this; iEntry_this++)
  {
	hh.GetEntry(iEntry_this);
        if(saveSkim) outfile->cd();
	cutflow.fill();
	if(saveSkim && cutflow.getCut("CutWeight").pass)
	{
	  outfile_skim->cd();	
	  m_weight = isData ?  1.0 : lumi*hh.m_weight();
	  ph_pt1 = hh.ph_pt1();

      tree_out->Fill();
	}
    //cout<<"event: "<<iEntry_this<<", m_weight: "<<hh.m_weight()<<endl;
	if(iEntry%10000 == 0) cout<<"[INFO] processing event "<<iEntry<<" / "<<nEntries<<endl;
	iEntry ++;
  }
  delete tree_this;
  file_this->Close();
  delete file_this;
}

//save histograms
cutflow.saveOutput();
outfile->Close();
if(saveSkim) 
{
 outfile_skim->cd();
 tree_out->Write();
 outfile_skim->Close();
}
cout<<"[INFO]: all  files successfully processed... ignore segfault below..."<<endl;

return 0;
}
