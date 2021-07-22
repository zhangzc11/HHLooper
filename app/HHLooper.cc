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

int lumi = 137000.0;
TTJetsScaleFactors ttjets_sf;
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

std::string year_ = "2016";
if(input.find("2016") != std::string::npos) {year_ = "2016"; lumi = 35922.0;}
if(input.find("2017") != std::string::npos) {year_ = "2017"; lumi = 41480.0;}
if(input.find("2018") != std::string::npos) {year_ = "2018"; lumi = 59741.0;}
system(("mkdir -p hists/"+label+"/"+year_).c_str());

bool isData = false;
if(isData_ == "1" || isData_ == "true" || isData_ == "yes" || isData_ == "True" || isData_ == "Yes") isData = true;
if(isData) lumi = 1.0;


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

TChain * chain = new TChain("tree");
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


histograms.addHistogram("fatJet1MassSD",   "; j_{1} soft drop mass (GeV); Events", 300,   0.,   300.,  [&]() { return  hh.fatJet1MassSD(); } );


//************define cuts**********//

cutflow.setTFile(outfile);


////Pre-selection cuts
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.weight(); });
cutflow.addCutToLastActiveCut("CutHLT",       [&](){ return 1;}, UNITY); 

//book histograms for cuts
cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
cutflow.bookCutflows();

int iEntry = 0;

if(saveSkim) outfile_skim->cd();
TTree *tree_out;

float weight;
float fatJet1MassSD;
float fatJet2MassSD;
float fatJet1PNetXbb;
float fatJet2PNetXbb;
float fatJet1Pt;
float fatJet2Pt;
float fatJet1Eta;
float fatJet2Eta;
float fatJet1Phi;
float fatJet2Phi;
float fatJet1PtOverMHH;
float fatJet2PtOverMHH;
float fatJet1PtOverMSD;
float fatJet2PtOverMSD;
float abs_dEta_j1j2;
float abs_dPhi_j1j2;
float abs_dR_j1j2;
float ptj2_over_ptj1;
float mj2_over_mj1;
float hh_pt;
float hh_eta;
float hh_phi;
float hh_mass;

if(saveSkim)
{ 
tree_out = new TTree("hh", "output skim tree");
tree_out->Branch("weight", &weight, "weight/F");
tree_out->Branch("fatJet1MassSD", &fatJet1MassSD, "fatJet1MassSD/F");
tree_out->Branch("fatJet1PNetXbb", &fatJet1PNetXbb, "fatJet1PNetXbb/F");
tree_out->Branch("fatJet1Pt", &fatJet1Pt, "fatJet1Pt/F");
tree_out->Branch("fatJet1Eta", &fatJet1Eta, "fatJet1Eta/F");
tree_out->Branch("fatJet1Phi", &fatJet1Phi, "fatJet1Phi/F");
tree_out->Branch("fatJet1PtOverMHH", &fatJet1PtOverMHH, "fatJet1PtOverMHH/F");
tree_out->Branch("fatJet1PtOverMSD", &fatJet1PtOverMSD, "fatJet1PtOverMSD/F");
tree_out->Branch("fatJet2MassSD", &fatJet2MassSD, "fatJet2MassSD/F");
tree_out->Branch("fatJet2PNetXbb", &fatJet2PNetXbb, "fatJet2PNetXbb/F");
tree_out->Branch("fatJet2Pt", &fatJet2Pt, "fatJet2Pt/F");
tree_out->Branch("fatJet2Eta", &fatJet2Eta, "fatJet2Eta/F");
tree_out->Branch("fatJet2Phi", &fatJet2Phi, "fatJet2Phi/F");
tree_out->Branch("fatJet2PtOverMHH", &fatJet2PtOverMHH, "fatJet2PtOverMHH/F");
tree_out->Branch("fatJet2PtOverMSD", &fatJet2PtOverMSD, "fatJet2PtOverMSD/F");
tree_out->Branch("abs_dEta_j1j2", &abs_dEta_j1j2, "abs_dEta_j1j2/F");
tree_out->Branch("abs_dPhi_j1j2", &abs_dPhi_j1j2, "abs_dPhi_j1j2/F");
tree_out->Branch("abs_dR_j1j2", &abs_dR_j1j2, "abs_dR_j1j2/F");
tree_out->Branch("ptj2_over_ptj1", &ptj2_over_ptj1, "ptj2_over_ptj1/F");
tree_out->Branch("mj2_over_mj1", &mj2_over_mj1, "mj2_over_mj1/F");
tree_out->Branch("hh_pt", &hh_pt, "hh_pt/F");
tree_out->Branch("hh_eta", &hh_eta, "hh_eta/F");
tree_out->Branch("hh_phi", &hh_phi, "hh_phi/F");
tree_out->Branch("hh_mass", &hh_mass, "hh_mass/F");
}

for(int idx = 0; idx < list_chain.size(); idx++)
{
  cout<<"[INFO] processing file: "<<list_chain[idx]<<endl;
  TTree * tree_this;
  TFile * file_this = new TFile(list_chain[idx].c_str(), "READ");
  tree_this = (TTree*)file_this->Get("tree");
  hh.Init(tree_this);
  int nEntries_this = tree_this->GetEntries();
  for(int iEntry_this=0; iEntry_this<nEntries_this; iEntry_this++)
  {
	hh.GetEntry(iEntry_this);
        if(saveSkim) outfile->cd();
	cutflow.fill();
	//if(saveSkim && cutflow.getCut("TwofatJets").pass)
	if(saveSkim && cutflow.getCut("BDTTrainPreSelection").pass)
	{
	  outfile_skim->cd();	
	  weight = isData ?  1.0 : lumi*hh.weight()*hh.triggerEffWeight()*hh.puWeight();
	  fatJet1MassSD = hh.fatJet1MassSD();
	  fatJet1PNetXbb = hh.fatJet1PNetXbb();
	  fatJet1Pt = hh.fatJet1Pt();
	  fatJet1Eta = hh.fatJet1Eta();
	  fatJet1Phi = hh.fatJet1Phi();
	  fatJet1PtOverMHH = hh.fatJet1PtOverMHH();
	  fatJet1PtOverMSD = hh.fatJet1PtOverMSD();
	  fatJet2MassSD = hh.fatJet2MassSD();
	  fatJet2PNetXbb = hh.fatJet2PNetXbb();
	  fatJet2Pt = hh.fatJet2Pt();
	  fatJet2Eta = hh.fatJet2Eta();
	  fatJet2Phi = hh.fatJet2Phi();
	  fatJet2PtOverMHH = hh.fatJet2PtOverMHH();
	  fatJet2PtOverMSD = hh.fatJet2PtOverMSD();

	  abs_dEta_j1j2 = fabs(hh.fatJet1Eta() - hh.fatJet2Eta());
	  abs_dPhi_j1j2 = fabs(hh.fatJet1Phi() - hh.fatJet2Phi());
	  abs_dR_j1j2 = sqrt((hh.fatJet1Eta() - hh.fatJet2Eta())*(hh.fatJet1Eta() - hh.fatJet2Eta())  + (hh.fatJet1Phi() - hh.fatJet2Phi())*(hh.fatJet1Phi() - hh.fatJet2Phi()));
	  ptj2_over_ptj1 = hh.fatJet2Pt() / hh.fatJet1Pt();
	  mj2_over_mj1 = fatJet2MassSD/fatJet1MassSD;
	  hh_pt = hh.hh_pt();
	  hh_eta = hh.hh_eta();
	  hh_phi = hh.hh_phi();
	  hh_mass = hh.hh_mass();

      tree_out->Fill();
	}
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
