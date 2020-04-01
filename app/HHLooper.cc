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
int FatJet1_idx = -999;
int FatJet2_idx = -999;

void selectTwoFatJets(float CUT_j1_DDB, float CUT_j2_DDB)
{
   FatJet1_idx = -999;
   FatJet2_idx = -999;
   float CUT_fatjet_DBB = CUT_j2_DDB;
   for(int idx=0; idx<hh.nFatJet(); idx++)
   {
      if(hh.FatJet_btagDDBvL()[idx] <= CUT_fatjet_DBB) continue;
      if(hh.FatJet_btagDDBvL()[idx] > CUT_j1_DDB) CUT_fatjet_DBB = CUT_j2_DDB; //this jet pass j1 cut, now only need another one pass j2 cut
      else CUT_fatjet_DBB = CUT_j1_DDB; //this jet only pass j2 cut, now need another one pass j1 cut
      if(FatJet1_idx < 0) 
      {
         FatJet1_idx = idx;
      }
      else if (FatJet2_idx < 0)
      {
         FatJet2_idx = idx;
         return;
      }
   }
   return;
}

void selectTwoFatJetsSortDDB()
{
   FatJet1_idx = -999;
   FatJet2_idx = -999;
   float max_DDB = -999.9;

   for(int idx=0; idx<hh.nFatJet(); idx++)
   {
      if(hh.FatJet_btagDDBvL()[idx] > max_DDB)
      {
         FatJet1_idx = idx;
         max_DDB = hh.FatJet_btagDDBvL()[idx];
      }
   }

   max_DDB = -999.9;
   for(int idx=0; idx<hh.nFatJet(); idx++)
   {
      if(idx == FatJet1_idx) continue;
      if(hh.FatJet_btagDDBvL()[idx] > max_DDB)
      {
         FatJet2_idx = idx;
         max_DDB = hh.FatJet_btagDDBvL()[idx];
      }
   }
   return;
}



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


//************define histograms**********//
histograms.addHistogram("yield",               "; yield; Events",                      1,    0.,   1.,    [&]() { return 0; } );
histograms.addHistogram("ChsMET_pt",           "; p_{T}^{miss} (GeV); Events",         30,   0.,   500.,  [&]() { return hh.ChsMET_pt(); } );
histograms.addHistogram("hh_pt",               "; p_{T}^{HH} (GeV); Events",           30,   0.,   900.,  [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_mass",             "; m_{HH} (GeV); Events",               30,   0.,  1500.,  [&]() { return hh.hh_mass(); } );
histograms.addHistogram("FatJet1_area",        "; fat j_{1} area; Events",             30,   1.,    3.0,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_area()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_area",        "; fat j_{2} area; Events",             30,   1.,    3.0,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_area()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_msoftdrop",   "; j_{1} soft drop mass (GeV); Events", 30,   0.,   200.,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_msoftdrop()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_msoftdrop",   "; j_{2} soft drop mass (GeV); Events", 30,   0.,   200.,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_msoftdrop()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_btagDDBvL",   "; j_{1} DDB tagger; Events",           30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_btagDDBvL()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_btagDDBvL",   "; j_{2} DDB tagger; Events",           30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_btagDDBvL()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_btagHbb",     "; j_{1} Hbb tagger; Events",           30,  -1.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_btagHbb()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_btagHbb",     "; j_{2} Hbb tagger; Events",           30,  -1.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_btagHbb()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_deepTagHbb",  "; j_{1} deepTagHbb tagger; Events",    30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_deepTagHbb()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_deepTagHbb",  "; j_{2} deepTagHbb tagger; Events",    30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_deepTagHbb()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_deepTagMDHbb","; j_{1} deepTagMDHbb tagger; Events",  30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_deepTagMDHbb()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_deepTagMDHbb","; j_{2} deepTagMDHbb tagger; Events",  30,   0.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_deepTagMDHbb()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_pt",          "; p_{T}^{j1} (GeV); Events",           30,   0.,   900.,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_pt",          "; p_{T}^{j2} (GeV); Events",           30,   0.,   900.,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] : -999; } );
//histograms.addHistogram("FatJet1_HminDR",      "; min DR(j_{1}, H); Events",           30,   0.,   5.,    [&]() { return (FatJet1_idx>=0) ? hh.FatJet_HminDR()[FatJet1_idx] : -999; } );
//histograms.addHistogram("FatJet2_HminDR",      "; min DR(j_{2}, H); Events",           30,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_HminDR()[FatJet2_idx] : -999; } );
histograms.addHistogram("abs_dEta_j1j2",       "; #Delta#eta(j_{1}, j_{2}); Events",   30,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? fabs(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx]): -999; } );
histograms.addHistogram("abs_dPhi_j1j2",       "; #Delta#Phi(j_{1}, j_{2}); Events",   30,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? fabs(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx]): -999; } );
histograms.addHistogram("abs_dR_j1j2",       "; #DeltaR(j_{1}, j_{2}); Events",        30,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? sqrt((hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])*(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])  + (hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx])*(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx])): -999; } );
histograms.addHistogram("ptj1_over_mhh",       "; p_{T}^{j1}/m_{HH}; Events",         30,   0.,   1.,    [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] / hh.hh_mass() :-999; } );
histograms.addHistogram("ptj2_over_mhh",       "; p_{T}^{j2}/m_{HH}; Events",         30,   0.,   1.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] / hh.hh_mass() :-999; } );
histograms.addHistogram("ptj1_over_mj1",       "; p_{T}^{j1}/m_{j1}; Events",         30,   0.,   10.,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] / hh.FatJet_msoftdrop()[FatJet1_idx] :-999; } );
histograms.addHistogram("ptj2_over_mj2",       "; p_{T}^{j2}/m_{j2}; Events",         30,   0.,   10.,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] / hh.FatJet_msoftdrop()[FatJet2_idx] :-999; } );

//************define cuts**********//
const float CUT_j1_pt = 300.0, CUT_j2_pt = 300.0, CUT_j1_DDB = 0.9, CUT_j2_DDB = 0.9, CUT_j1_mass_low = 110.0, CUT_j1_mass_high = 150.0, CUT_j2_mass_low = 110.0, CUT_j2_mass_high = 150.0;
cutflow.setTFile(outfile);
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.weight(); });
//cutflow.addCutToLastActiveCut("HLTCut",             [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);
cutflow.addCutToLastActiveCut("TwoFatJets",         [&](){ return FatJet1_idx>=0 && FatJet2_idx>=0;  },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut",      [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("SRFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);

cutflow.getCut("FatJetsPtCut");
cutflow.addCutToLastActiveCut("SideBandJ1MassFatJetsSDMassCut",   [&](){ return (hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_low || hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_high) && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.getCut("FatJetsPtCut");
cutflow.addCutToLastActiveCut("SideBandJ2MassFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && (hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_low || hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_high); },   UNITY);
cutflow.getCut("SRFatJetsPtCut");


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
        //selectTwoFatJets(CUT_j1_DDB, CUT_j2_DDB);
        selectTwoFatJets(0.8, 0.8);
        //selectTwoFatJetsSortDDB();
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
