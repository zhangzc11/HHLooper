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
bool saveSkim = false;

if(argc > 5)
{
  std::string s_skim = argv[5];
  if(s_skim == "1" || s_skim == "skim" || s_skim == "yes") saveSkim= true; 
}

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
TFile *outfile_skim;
if(saveSkim) outfile_skim = new TFile(("hists/"+label+"/"+outputFileName.replace(outputFileName.find(".root"), 5, "_skim.root")).c_str(), "recreate");

RooUtil::Cutflow cutflow;
RooUtil::Histograms histograms;


//************define histograms**********//
histograms.addHistogram("yield",               "; yield; Events",                      1,    0.,   1.,    [&]() { return 0; } );
histograms.addHistogram("ChsMET_pt",           "; p_{T}^{miss} (GeV); Events",         200,   0.,   500.,  [&]() { return hh.ChsMET_pt(); } );
histograms.addHistogram("hh_pt",               "; p_{T}^{HH} (GeV); Events",           200,   0.,   900.,  [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_eta",               "; #eta^{HH}; Events",                 200,   -5.0,  5.0,  [&]() { return hh.hh_eta(); } );
histograms.addHistogram("hh_phi",               "; #Phi^{HH}; Events",                 200,   -3.2,  3.2,  [&]() { return hh.hh_phi(); } );
histograms.addHistogram("hh_mass",             "; m_{HH} (GeV); Events",               200,   0.,  1500.,  [&]() { return hh.hh_mass(); } );
histograms.addHistogram("FatJet1_area",        "; fat j_{1} area; Events",             200,   1.5,   2.5,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_area()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_area",        "; fat j_{2} area; Events",             200,   1.5,   2.5,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_area()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_msoftdrop",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   200.,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_msoftdrop()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_msoftdrop",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   200.,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_msoftdrop()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_btagDDBvL",   "; j_{1} DDB tagger; Events",           200,   0.7,  1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_btagDDBvL()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_btagDDBvL",   "; j_{2} DDB tagger; Events",           200,   0.7,  1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_btagDDBvL()[FatJet2_idx] : -999; } );
//histograms.addHistogram("FatJet1_btagHbb",     "; j_{1} Hbb tagger; Events",           200,  -1.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_btagHbb()[FatJet1_idx] : -999; } );
//histograms.addHistogram("FatJet2_btagHbb",     "; j_{2} Hbb tagger; Events",           200,  -1.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_btagHbb()[FatJet2_idx] : -999; } );
//histograms.addHistogram("FatJet1_deepTagHbb",  "; j_{1} deepTagHbb tagger; Events",    200,   0.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_deepTagHbb()[FatJet1_idx] : -999; } );
//histograms.addHistogram("FatJet2_deepTagHbb",  "; j_{2} deepTagHbb tagger; Events",    200,   0.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_deepTagHbb()[FatJet2_idx] : -999; } );
//histograms.addHistogram("FatJet1_deepTagMDHbb","; j_{1} deepTagMDHbb tagger; Events",  200,   0.,   1.0,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_deepTagMDHbb()[FatJet1_idx] : -999; } );
//histograms.addHistogram("FatJet2_deepTagMDHbb","; j_{2} deepTagMDHbb tagger; Events",  200,   0.,   1.0,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_deepTagMDHbb()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet1_pt",          "; p_{T}^{j1} (GeV); Events",           200,   0.,   900.,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet1_eta",          "; #eta^{j1}; Events",                 200,   -2.5,  2.5,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_eta()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet1_phi",          "; #Phi^{j1}; Events",                 200,  -3.2,   3.2,  [&]() { return (FatJet1_idx>=0) ? hh.FatJet_phi()[FatJet1_idx] : -999; } );
histograms.addHistogram("FatJet2_pt",          "; p_{T}^{j2} (GeV); Events",           200,   0.,   900.,  [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet2_eta",          "; #eta^{j2}; Events",                 200,   -2.5,  2.5,  [&]() { return (FatJet2_idx>=0) ? hh.FatJet_eta()[FatJet2_idx] : -999; } );
histograms.addHistogram("FatJet2_phi",          "; #Phi^{j2}; Events",                 200,  -3.2,   3.2,  [&]() { return (FatJet2_idx>=0) ? hh.FatJet_phi()[FatJet2_idx] : -999; } );
//histograms.addHistogram("FatJet1_HminDR",      "; min DR(j_{1}, H); Events",           200,   0.,   5.,    [&]() { return (FatJet1_idx>=0) ? hh.FatJet_HminDR()[FatJet1_idx] : -999; } );
//histograms.addHistogram("FatJet2_HminDR",      "; min DR(j_{2}, H); Events",           200,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_HminDR()[FatJet2_idx] : -999; } );
histograms.addHistogram("abs_dEta_j1j2",       "; #Delta#eta(j_{1}, j_{2}); Events",   200,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? fabs(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx]): -999; } );
histograms.addHistogram("abs_dPhi_j1j2",       "; #Delta#Phi(j_{1}, j_{2}); Events",   200,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? fabs(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx]): -999; } );
histograms.addHistogram("abs_dR_j1j2",       "; #DeltaR(j_{1}, j_{2}); Events",        200,   0.,   5.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? sqrt((hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])*(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])  + (hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx])*(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx])): -999; } );
histograms.addHistogram("ptj1_over_mhh",       "; p_{T}^{j1}/m_{HH}; Events",         200,   0.,   1.,    [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] / hh.hh_mass() :-999; } );
histograms.addHistogram("ptj2_over_mhh",       "; p_{T}^{j2}/m_{HH}; Events",         200,   0.,   1.,    [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] / hh.hh_mass() :-999; } );
histograms.addHistogram("ptj1_over_mj1",       "; p_{T}^{j1}/m_{j1}; Events",         200,   0.,   10.,   [&]() { return (FatJet1_idx>=0) ? hh.FatJet_pt()[FatJet1_idx] / hh.FatJet_msoftdrop()[FatJet1_idx] :-999; } );
histograms.addHistogram("ptj2_over_mj2",       "; p_{T}^{j2}/m_{j2}; Events",         200,   0.,   10.,   [&]() { return (FatJet1_idx>=0 && FatJet2_idx>=0) ? hh.FatJet_pt()[FatJet2_idx] / hh.FatJet_msoftdrop()[FatJet2_idx] :-999; } );

//************define cuts**********//
//const float CUT_j1_pt = 300.0, CUT_j2_pt = 250.0, CUT_j1_DDB = 0.9, CUT_j2_DDB = 0.9, CUT_j1_mass_low = 100.0, CUT_j1_mass_high = 150.0, CUT_j2_mass_low = 90.0, CUT_j2_mass_high = 140.0; // baseline selection
const float CUT_j1_pt = 350.0, CUT_j2_pt = 300.0, CUT_j1_DDB = 0.905, CUT_j2_DDB = 0.902, CUT_j1_mass_low = 100.0, CUT_j1_mass_high = 140.0, CUT_j2_mass_low = 95.0, CUT_j2_mass_high = 135.0; //optimal cut
const float CUT2_j1_DDB = 0.860, CUT2_j2_DDB = 0.902, CUT3_j1_DDB = 0.905, CUT3_j2_DDB = 0.858; //additional SR
const float CUTCR_j1_DDB = 0.800, CUTCR_j2_DDB = 0.800; // cut for CR

cutflow.setTFile(outfile);
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.weight(); });
cutflow.addCutToLastActiveCut("HLTCut",             [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);
cutflow.addCutToLastActiveCut("TwoFatJets",         [&](){ return FatJet1_idx>=0 && FatJet2_idx>=0;  },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut1",      [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCutSR1",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("SR1FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);

cutflow.getCut("FatJetsPtCutSR1");
cutflow.addCutToLastActiveCut("SideBandSR1J1MassFatJetsSDMassCut",   [&](){ return (hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_low || hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_high) && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.getCut("FatJetsPtCutSR1");
cutflow.addCutToLastActiveCut("SideBandSR1J2MassFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && (hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_low || hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_high); },   UNITY);

//2nd signal region
cutflow.getCut("TwoFatJets");
cutflow.addCutToLastActiveCut("FailFatJetsDDBCut1",      [&](){ return !(hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB ); },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut2",      [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT2_j2_DDB; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCutSR2",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("SR2FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);

cutflow.getCut("FatJetsPtCutSR2");
cutflow.addCutToLastActiveCut("SideBandSR2J1MassFatJetsSDMassCut",   [&](){ return (hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_low || hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_high) && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.getCut("FatJetsPtCutSR2");
cutflow.addCutToLastActiveCut("SideBandSR2J2MassFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && (hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_low || hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_high); },   UNITY);

//3rd signal region
cutflow.getCut("TwoFatJets");
cutflow.addCutToLastActiveCut("FailFatJetsDDBCut2",      [&](){ return !(hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT2_j2_DDB ); },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut3",      [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT3_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT3_j2_DDB; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCutSR3",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("SR3FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);

cutflow.getCut("FatJetsPtCutSR3");
cutflow.addCutToLastActiveCut("SideBandSR3J1MassFatJetsSDMassCut",   [&](){ return (hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_low || hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_high) && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.getCut("FatJetsPtCutSR3");
cutflow.addCutToLastActiveCut("SideBandSR3J2MassFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && (hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_low || hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_high); },   UNITY);


//control regions
cutflow.getCut("TwoFatJets");
cutflow.addCutToLastActiveCut("preCRFatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("preCRFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);

cutflow.addCutToLastActiveCut("ControlRegionD",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet1_idx] < CUT3_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT3_j2_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] < CUT2_j2_DDB; },   UNITY);

cutflow.getCut("preCRFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("ControlRegionN1",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet1_idx] < CUT3_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUTCR_j2_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] < CUT3_j2_DDB; },   UNITY);
cutflow.getCut("preCRFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("ControlRegionM1",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT3_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUTCR_j2_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] < CUT3_j2_DDB; },   UNITY);

cutflow.getCut("preCRFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("ControlRegionN2",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUTCR_j1_DDB && hh.FatJet_btagDDBvL()[FatJet1_idx] < CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT3_j2_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] < CUT2_j2_DDB; },   UNITY);
cutflow.getCut("preCRFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("ControlRegionM2",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUTCR_j1_DDB && hh.FatJet_btagDDBvL()[FatJet1_idx] < CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT2_j2_DDB; },   UNITY);

cutflow.getCut("preCRFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("ControlRegionE",          [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUTCR_j1_DDB && hh.FatJet_btagDDBvL()[FatJet1_idx] < CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUTCR_j2_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] < CUT3_j2_DDB; },   UNITY);

////histograms for N-1 cuts
//N-1 for JetsSDMass:
cutflow.addCut("preNm1CutWeight", [&](){ return 1; },    [&](){ return isData ?  lumi : lumi*hh.weight(); });
cutflow.addCutToLastActiveCut("preNm1HLTCut",            [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);
cutflow.addCutToLastActiveCut("preNm1TwoFatJets",         [&](){ return FatJet1_idx>=0 && FatJet2_idx>=0;  },   UNITY);
cutflow.addCutToLastActiveCut("preNm1FatJetsDDBCut",      [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB; },   UNITY);
cutflow.addCutToLastActiveCut("preNm1FatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("Nm1FatJet1SDMassLeft",         [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; }, UNITY);
cutflow.getCut("preNm1FatJetsPtCut");
cutflow.addCutToLastActiveCut("Nm1FatJet1SDMassRight",         [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; }, UNITY);
cutflow.getCut("preNm1FatJetsPtCut");
cutflow.addCutToLastActiveCut("Nm1FatJet2SDMassLeft",         [&](){ return hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high && hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high; }, UNITY);
cutflow.getCut("preNm1FatJetsPtCut");
cutflow.addCutToLastActiveCut("Nm1FatJet2SDMassRight",         [&](){ return hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high; }, UNITY);

//N-1 for JetsPt
cutflow.getCut("preNm1FatJetsDDBCut");
cutflow.addCutToLastActiveCut("preNm1ForPtFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.addCutToLastActiveCut("Nm1FatJet1Pt",         [&](){ return hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; }, UNITY);
cutflow.getCut("preNm1ForPtFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("Nm1FatJet2Pt",         [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt; }, UNITY);

//N-1 for JetsDDB
cutflow.getCut("preNm1TwoFatJets");
cutflow.addCutToLastActiveCut("preNm1ForDDBFatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("preNm1ForDDBFatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.addCutToLastActiveCut("Nm1FatJet1DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB; }, UNITY);
cutflow.getCut("preNm1ForDDBFatJetsSDMassCut");
cutflow.addCutToLastActiveCut("Nm1FatJet2DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB; }, UNITY);

//2nd signal region of DDB cuts
cutflow.getCut("preNm1TwoFatJets");
cutflow.addCutToLastActiveCut("preNm1FailFatJetsDDBCut1",      [&](){ return !(hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT_j2_DDB ); },   UNITY);
cutflow.addCutToLastActiveCut("preNm1ForSR2FatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("preNm1ForSR2FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.addCutToLastActiveCut("Nm1SR2FatJet1DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT2_j2_DDB; }, UNITY);
cutflow.getCut("preNm1ForSR2FatJetsSDMassCut");
cutflow.addCutToLastActiveCut("Nm1SR2FatJet2DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB; }, UNITY);

//3rd signal region of DDB cuts
cutflow.getCut("preNm1TwoFatJets");
cutflow.addCutToLastActiveCut("preNm1FailFatJetsDDBCut2",      [&](){ return !(hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT2_j1_DDB && hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT2_j2_DDB ); },   UNITY);
cutflow.addCutToLastActiveCut("preNm1ForSR3FatJetsPtCut",       [&](){ return hh.FatJet_pt()[FatJet1_idx] > CUT_j1_pt && hh.FatJet_pt()[FatJet2_idx] > CUT_j2_pt; },   UNITY);
cutflow.addCutToLastActiveCut("preNm1ForSR3FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[FatJet1_idx] > CUT_j1_mass_low && hh.FatJet_msoftdrop()[FatJet1_idx] < CUT_j1_mass_high && hh.FatJet_msoftdrop()[FatJet2_idx] > CUT_j2_mass_low && hh.FatJet_msoftdrop()[FatJet2_idx] < CUT_j2_mass_high; },   UNITY);
cutflow.addCutToLastActiveCut("Nm1SR3FatJet1DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet2_idx] > CUT3_j2_DDB; }, UNITY);
cutflow.getCut("preNm1ForSR3FatJetsSDMassCut");
cutflow.addCutToLastActiveCut("Nm1SR3FatJet2DDB",         [&](){ return hh.FatJet_btagDDBvL()[FatJet1_idx] > CUT3_j1_DDB; }, UNITY);



//book histograms for cuts
cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet1SDMassLeft");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet1SDMassRight");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet2SDMassLeft");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet2SDMassRight");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet1Pt");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet2Pt");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet1DDB");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1FatJet2DDB");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1SR2FatJet1DDB");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1SR2FatJet2DDB");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1SR3FatJet1DDB");
cutflow.bookHistogramsForCutAndBelow(histograms, "Nm1SR3FatJet2DDB");
cutflow.bookCutflows();

int iEntry = 0;

outfile_skim->cd();
TTree *tree_out;

float weight;
float FatJet1_area;
float FatJet2_area;
float FatJet1_msoftdrop;
float FatJet2_msoftdrop;
float FatJet1_btagDDBvL;
float FatJet2_btagDDBvL;
float FatJet1_pt;
float FatJet2_pt;
float FatJet1_eta;
float FatJet2_eta;
float FatJet1_phi;
float FatJet2_phi;
float ptj1_over_mhh;
float ptj2_over_mhh;
float ptj1_over_mj1;
float ptj2_over_mj2;
float abs_dEta_j1j2;
float abs_dPhi_j1j2;
float abs_dR_j1j2;
float hh_pt;
float hh_eta;
float hh_phi;
float hh_mass;

if(saveSkim)
{ 
tree_out = new TTree("hh", "output skim tree");
tree_out->Branch("weight", &weight, "weight/F");
tree_out->Branch("FatJet1_area", &FatJet1_area, "FatJet1_area/F");
tree_out->Branch("FatJet1_msoftdrop", &FatJet1_msoftdrop, "FatJet1_msoftdrop/F");
tree_out->Branch("FatJet1_btagDDBvL", &FatJet1_btagDDBvL, "FatJet1_btagDDBvL/F");
tree_out->Branch("FatJet1_pt", &FatJet1_pt, "FatJet1_pt/F");
tree_out->Branch("FatJet1_eta", &FatJet1_eta, "FatJet1_eta/F");
tree_out->Branch("FatJet1_phi", &FatJet1_phi, "FatJet1_phi/F");
tree_out->Branch("ptj1_over_mhh", &ptj1_over_mhh, "ptj1_over_mhh/F");
tree_out->Branch("ptj1_over_mj1", &ptj1_over_mj1, "ptj1_over_mj1/F");
tree_out->Branch("FatJet2_area", &FatJet2_area, "FatJet2_area/F");
tree_out->Branch("FatJet2_msoftdrop", &FatJet2_msoftdrop, "FatJet2_msoftdrop/F");
tree_out->Branch("FatJet2_btagDDBvL", &FatJet2_btagDDBvL, "FatJet2_btagDDBvL/F");
tree_out->Branch("FatJet2_pt", &FatJet2_pt, "FatJet2_pt/F");
tree_out->Branch("FatJet2_eta", &FatJet2_eta, "FatJet2_eta/F");
tree_out->Branch("FatJet2_phi", &FatJet2_phi, "FatJet2_phi/F");
tree_out->Branch("ptj2_over_mhh", &ptj2_over_mhh, "ptj2_over_mhh/F");
tree_out->Branch("ptj2_over_mj2", &ptj2_over_mj2, "ptj2_over_mj2/F");
tree_out->Branch("abs_dEta_j1j2", &abs_dEta_j1j2, "abs_dEta_j1j2/F");
tree_out->Branch("abs_dPhi_j1j2", &abs_dPhi_j1j2, "abs_dPhi_j1j2/F");
tree_out->Branch("abs_dR_j1j2", &abs_dR_j1j2, "abs_dR_j1j2/F");
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
  tree_this = (TTree*)file_this->Get("hh");
  hh.Init(tree_this);
  int nEntries_this = tree_this->GetEntries();
  for(int iEntry_this=0; iEntry_this<nEntries_this; iEntry_this++)
  {
	hh.GetEntry(iEntry_this);
        //selectTwoFatJets(CUT_j1_DDB, CUT_j2_DDB);
        selectTwoFatJets(0.80, 0.80);
        //selectTwoFatJetsSortDDB();
        outfile->cd();
	cutflow.fill();
	if(saveSkim && cutflow.getCut("TwoFatJets").pass)
	{
	  outfile_skim->cd();	
	  weight = isData ?  1.0 : hh.weight();
	  FatJet1_area = hh.FatJet_area()[FatJet1_idx];
	  FatJet1_msoftdrop = hh.FatJet_msoftdrop()[FatJet1_idx];
	  FatJet1_btagDDBvL = hh.FatJet_btagDDBvL()[FatJet1_idx];
	  FatJet1_pt = hh.FatJet_pt()[FatJet1_idx];
	  FatJet1_eta = hh.FatJet_eta()[FatJet1_idx];
	  FatJet1_phi = hh.FatJet_phi()[FatJet1_idx];
	  ptj1_over_mhh = hh.FatJet_pt()[FatJet1_idx] / hh.hh_mass();
	  ptj1_over_mj1 = hh.FatJet_pt()[FatJet1_idx] / hh.FatJet_msoftdrop()[FatJet1_idx];
	  FatJet2_area = hh.FatJet_area()[FatJet2_idx];
	  FatJet2_msoftdrop = hh.FatJet_msoftdrop()[FatJet2_idx];
	  FatJet2_btagDDBvL = hh.FatJet_btagDDBvL()[FatJet2_idx];
	  FatJet2_pt = hh.FatJet_pt()[FatJet2_idx];
	  FatJet2_eta = hh.FatJet_eta()[FatJet2_idx];
	  FatJet2_phi = hh.FatJet_phi()[FatJet2_idx];
	  ptj2_over_mhh = hh.FatJet_pt()[FatJet2_idx] / hh.hh_mass();
	  ptj2_over_mj2 = hh.FatJet_pt()[FatJet2_idx] / hh.FatJet_msoftdrop()[FatJet2_idx];
	  abs_dEta_j1j2 = fabs(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx]);
	  abs_dPhi_j1j2 = fabs(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx]);
	  abs_dR_j1j2 = sqrt((hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])*(hh.FatJet_eta()[FatJet1_idx] - hh.FatJet_eta()[FatJet2_idx])  + (hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx])*(hh.FatJet_phi()[FatJet1_idx] - hh.FatJet_phi()[FatJet2_idx]));
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

return 0;
}
