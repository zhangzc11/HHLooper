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
#include "bbbb_vs_bkg.h"
#include "scalefactors.h"

using namespace std;

int lumi = 137000.0;
TTJetsScaleFactors ttjets_sf;
TRandom3* r_nominal = new TRandom3(0);

float FatJetMassCorrection(string year, float mass, int type=0)
{
    //type=0: nominal
    //type=-1: jms only
    //type=-2: jmr only
    //type=1: jms down
    //type=2: jms up
    //type=3: jmr down
    //type=4: jmr up
    float* jmsValues;//{nominal, down, up}
    if(year == "2016")
      {
        float tmp_jms[] = {1.00, 0.9906, 1.0094};
        jmsValues = tmp_jms;
      }
    else if(year == "2017")
      {
        //float tmp_jms[] = {0.982, 0.978, 0.986};
        float tmp_jms[] = {1.0016, 0.978, 0.986};
        jmsValues = tmp_jms;
      }
    else if(year == "2018")
      {
        float tmp_jms[] = {0.997, 0.993, 1.001};
        jmsValues = tmp_jms;
      }
    else
      {
        std::cout << "year is not acceptable! Use: 2016, 2017, 2018" << std::endl;
        exit(EXIT_FAILURE);
      }

    float* jmrValues;//{nominal, down, up}
    if(year == "2016")
      {
        //float tmp_jmr[] = {1.00, 1.0, 1.2};
        float tmp_jmr[] = {1.00, 1.0, 1.09};
        jmrValues = tmp_jmr;
      }
    else if(year == "2017")
      {
        //float tmp_jmr[] = {1.09, 1.04, 1.14}; // percent of resolution
        //float tmp_jmr[] = {1.043, 1.00, 1.09};
        float tmp_jmr[] = {1.03, 1.00, 1.07};
        jmrValues = tmp_jmr;
      }
    else if(year == "2018")
      {
        //float tmp_jmr[] = {1.24, 1.20, 1.28}; //percent of resolution
        float tmp_jmr[] = {1.065, 1.031, 1.099};
        jmrValues = tmp_jmr;
      }
    else
      {
        std::cout << "year is not acceptable! Use: 2016, 2017, 2018" << std::endl;
        exit(EXIT_FAILURE);
      }

    float  result = mass;
    if(type==0) result = jmsValues[0]*mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[0] -1.0 ) );
    if(type==-1) result = jmsValues[0]*mass;
    if(type==-2) result = mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[0] -1.0 ) );
    if(type==1) result = jmsValues[1]*mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[0] -1.0 ) );
    if(type==2) result = jmsValues[2]*mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[0] -1.0 ) );
    if(type==3) result = jmsValues[0]*mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[1] -1.0 ) );
    if(type==4) result = jmsValues[0]*mass*( 1.0 + r_nominal->Gaus( 0.0, jmrValues[2] -1.0 ) );
    return result;
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
//if(input.find("qcd") != std::string::npos) lumi = lumi*0.72;

bool isTTJets =  false;
if(input.find("ttbar") != std::string::npos) isTTJets = true;

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


if(doSystematics)
{
histograms.addHistogram("fatJet2MassSD",   "; j_{2} soft drop mass (GeV); Events", 46,   40.,    500.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 0); } );
histograms.addHistogram("fatJet2MassSD_JMSDown",   "; j_{2} soft drop mass (GeV); Events", 46,   40.,    500.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 1); } );
histograms.addHistogram("fatJet2MassSD_JMSUp",   "; j_{2} soft drop mass (GeV); Events", 46,   40.,    500.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 2); } );
histograms.addHistogram("fatJet2MassSD_JMRDown",   "; j_{2} soft drop mass (GeV); Events", 46,   40.,    500.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 3); } );
histograms.addHistogram("fatJet2MassSD_JMRUp",   "; j_{2} soft drop mass (GeV); Events", 46,   40.,    500.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 4); } );
}

else
{
histograms.addHistogram("fatJet1MassSD",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), 0); } );
histograms.addHistogram("fatJet2MassSD",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 0); } );
histograms.addHistogram("fatJet1MassSD_JMSonly",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), -1); } );
histograms.addHistogram("fatJet2MassSD_JMSonly",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), -1); } );
histograms.addHistogram("fatJet1MassSD_JMRonly",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), -2); } );
histograms.addHistogram("fatJet2MassSD_JMRonly",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), -2); } );
histograms.addHistogram("fatJet1MassSD_JMSDown",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), 1); } );
histograms.addHistogram("fatJet2MassSD_JMSDown",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 1); } );
histograms.addHistogram("fatJet1MassSD_JMSUp",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), 2); } );
histograms.addHistogram("fatJet2MassSD_JMSUp",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 2); } );
histograms.addHistogram("fatJet1MassSD_JMRDown",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), 3); } );
histograms.addHistogram("fatJet2MassSD_JMRDown",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 3); } );
histograms.addHistogram("fatJet1MassSD_JMRUp",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet1MassSD() : FatJetMassCorrection(year_, hh.fatJet1MassSD(), 4); } );
histograms.addHistogram("fatJet2MassSD_JMRUp",   "; j_{2} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  isData ? hh.fatJet2MassSD() : FatJetMassCorrection(year_, hh.fatJet2MassSD(), 4); } );
histograms.addHistogram("fatJet1MassSD_raw",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  hh.fatJet1MassSD(); } );
histograms.addHistogram("fatJet2MassSD_raw",   "; j_{1} soft drop mass (GeV); Events", 200,   0.,   300.,  [&]() { return  hh.fatJet2MassSD(); } );

histograms.addHistogram("MET",           "; p_{T}^{miss} (GeV); Events",         200,   0.,   500.,  [&]() { return hh.MET(); } );
//histograms.addHistogram("hh_pt",               "; p_{T}^{HH} (GeV); Events",           {0.,50., 100., 150., 200., 250., 300., 400., 500., 600., 800., 1000.},  [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_pt",               "; p_{T}^{HH} (GeV); Events",           {0.,50., 100., 150., 300., 1000.},  [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_eta",               "; #eta^{HH}; Events",                 200,   -5.0,  5.0,  [&]() { return hh.hh_eta(); } );
histograms.addHistogram("hh_phi",               "; #Phi^{HH}; Events",                 200,   -3.2,  3.2,  [&]() { return hh.hh_phi(); } );
histograms.addHistogram("hh_mass",             "; m_{HH} (GeV); Events",               200,   0.,  1500.,  [&]() { return hh.hh_mass(); } );
histograms.addHistogram("fatJet1PNetXbb",   "; j_{1} PNet Xbb tagger; Events",           200,   0.0,  1.0,   [&]() { return  hh.fatJet1PNetXbb(); } );
histograms.addHistogram("fatJet2PNetXbb",   "; j_{2} PNet Xbb tagger; Events",           200,   0.0,  1.0,   [&]() { return  hh.fatJet2PNetXbb(); } );
histograms.addHistogram("fatJet1Pt",          "; p_{T}^{j1} (GeV); Events",           200,   0.,   900.,  [&]() { return  hh.fatJet1Pt(); } );
histograms.addHistogram("fatJet1Eta",          "; #eta^{j1}; Events",                 200,   -2.5,  2.5,  [&]() { return  hh.fatJet1Eta(); } );
histograms.addHistogram("fatJet1Phi",          "; #Phi^{j1}; Events",                 200,  -3.2,   3.2,  [&]() { return  hh.fatJet1Phi(); } );
histograms.addHistogram("fatJet2Pt",          "; p_{T}^{j2} (GeV); Events",           200,   0.,   900.,  [&]() { return  hh.fatJet2Pt(); } );
histograms.addHistogram("fatJet2Eta",          "; #eta^{j2}; Events",                 200,   -2.5,  2.5,  [&]() { return  hh.fatJet2Eta(); } );
histograms.addHistogram("fatJet2Phi",          "; #Phi^{j2}; Events",                 200,  -3.2,   3.2,  [&]() { return  hh.fatJet2Phi(); } );
histograms.addHistogram("abs_dEta_j1j2",       "; #Delta#eta(j_{1}, j_{2}); Events",   200,   0.,   5.,    [&]() { return  fabs(hh.fatJet1Eta() - hh.fatJet2Eta()); } );
histograms.addHistogram("abs_dPhi_j1j2",       "; #Delta#Phi(j_{1}, j_{2}); Events",   200,   2.,   4.5,    [&]() { return  fabs(hh.fatJet1Phi() - hh.fatJet2Phi()); } );
histograms.addHistogram("abs_dR_j1j2",       "; #DeltaR(j_{1}, j_{2}); Events",        200,   0.,   5.,    [&]() { return  sqrt((hh.fatJet1Eta() - hh.fatJet2Eta())*(hh.fatJet1Eta() - hh.fatJet2Eta())  + (hh.fatJet1Phi() - hh.    fatJet2Phi())*(hh.fatJet1Phi() - hh.fatJet2Phi())); } );
histograms.addHistogram("ptj1_over_mhh",       "; p_{T}^{j1}/m_{HH}; Events",         200,   0.,   1.,    [&]() { return  hh.fatJet1PtOverMHH(); } );
histograms.addHistogram("ptj2_over_mhh",       "; p_{T}^{j2}/m_{HH}; Events",         200,   0.,   1.,    [&]() { return  hh.fatJet2PtOverMHH(); } );
histograms.addHistogram("ptj1_over_mj1",       "; p_{T}^{j1}/m_{j1}; Events",         200,   0.,   10.,   [&]() { return  hh.fatJet1PtOverMSD(); } );
histograms.addHistogram("ptj2_over_mj2",       "; p_{T}^{j2}/m_{j2}; Events",         200,   0.,   10.,   [&]() { return  hh.fatJet2PtOverMSD(); } );
histograms.addHistogram("ptj2_over_ptj1",      "; p_{T}^{j2}/p_{T}^{j1}; Events",     200,   0.5,  1.,    [&]() { return  hh.fatJet2Pt() / hh.fatJet1Pt(); } );
histograms.addHistogram("mj2_over_mj1",      "; m^{j2}/m^{j1}; Events",               200,   0.0,  1.5,   [&]() { return  hh.fatJet2MassSD() / hh.fatJet1MassSD(); } );
histograms.addHistogram("fatJet1Tau3OverTau2",   "; j_{1} Tau3/2; Events",           200,   0.0,  1.0,   [&]() { return  hh.fatJet1Tau3OverTau2(); } );
histograms.addHistogram("fatJet2Tau3OverTau2",   "; j_{2} Tau3/2; Events",           200,   0.0,  1.0,   [&]() { return  hh.fatJet2Tau3OverTau2(); } );
histograms.addHistogram("EventBDT",   "; Event BDT; Events",           200,   0.0,  0.2,   [&]() { return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24(); } );
histograms.addHistogram("EventBDTBin2",   "; Event BDT; Events",           {0.000, 0.003,0.006,0.009, 0.0117, 0.0190,0.0280, 0.04, 0.10},   [&]() { return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24(); } );
histograms.addHistogram("EventBDTBin3",   "; Event BDT; Events",           {0.000, 0.003,0.006,0.009, 0.0117, 0.0280, 0.1},   [&]() { return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24(); } );
}

//************define cuts**********//

cutflow.setTFile(outfile);

////Pre-selection cuts
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return isData ?  lumi : lumi*hh.weight()*hh.triggerEffWeight()*hh.pileupWeight() * (isTTJets  ? ttjets_sf.getScaleFactorsFit(year_, hh.hh_pt(), 0) : 1.0); });
cutflow.addCutToLastActiveCut("CutHLT",       [&](){ return isData ? ((year_ == "2016" && (hh.HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20() || hh.HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20() || hh.HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20())) || (year_ == "2017" && (hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17())) || (year_ == "2018" && (hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4()))) : 1.0; },   UNITY);

cutflow.addCutToLastActiveCut("CutfatJetsPt",       [&](){ return hh.fatJet1Pt() > 250.0 && hh.fatJet2Pt() > 250.0; },   UNITY);
cutflow.addCutToLastActiveCut("CutfatJetsMassSD",       [&](){ return isData ? (hh.fatJet1MassSD() > 50.0 && hh.fatJet2MassSD() > 50.0) : (FatJetMassCorrection(year_, hh.fatJet1MassSD(),0) > 50.0 && FatJetMassCorrection(year_, hh.fatJet2MassSD(), 0) > 50.0); },   UNITY);


////Signal regions - pass
cutflow.addCutToLastActiveCut("SRBin1",       [&](){ return hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.028 && hh.fatJet1PNetXbb() > 0.985 && hh.fatJet2PNetXbb() >  0.985; },   UNITY);
cutflow.addCutToLastActiveCut("J2MassSideBandBin1",       [&](){ return hh.fatJet2MassSD() <= 95 || hh.fatJet2MassSD() >= 135.0; },   UNITY);


cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("SRBin2",       [&](){ return hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0117 && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() <= 0.028 && hh.fatJet1PNetXbb() > 0.985 && hh.fatJet2PNetXbb() >  0.985; },   UNITY);
cutflow.addCutToLastActiveCut("J2MassSideBandBin2",       [&](){ return hh.fatJet2MassSD() <= 95 || hh.fatJet2MassSD() >= 135.0; },   UNITY);

cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("SRBin3",       [&](){ return (!(hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0117 && hh.fatJet1PNetXbb() > 0.985 && hh.fatJet2PNetXbb() >  0.985)) && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0063 && hh.fatJet1PNetXbb() > 0.975 && hh.fatJet2PNetXbb() >  0.975; },   UNITY);
cutflow.addCutToLastActiveCut("J2MassSideBandBin3",       [&](){ return hh.fatJet2MassSD() <= 95 || hh.fatJet2MassSD() >= 135.0; },   UNITY);

cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("SRBin4",       [&](){ return (!(hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0117 && hh.fatJet1PNetXbb() > 0.985 && hh.fatJet2PNetXbb() >  0.985)) && (!(hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0063 && hh.fatJet1PNetXbb() > 0.975 && hh.fatJet2PNetXbb() >  0.975)) && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0141 &&  ( (hh.fatJet1PNetXbb() > 0.95 && hh.fatJet2PNetXbb() >  0.975) || (hh.fatJet1PNetXbb() > 0.975 && hh.fatJet2PNetXbb() >  0.95)); },   UNITY);
cutflow.addCutToLastActiveCut("J2MassSideBandBin4",       [&](){ return hh.fatJet2MassSD() <= 95 || hh.fatJet2MassSD() >= 135.0; },   UNITY);


////Signal region - fail
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("FailSR",       [&](){ return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24() > 0.0117 && hh.fatJet2PNetXbb() < 0.95; },   UNITY);



////BDT inverted regions for F-test
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("FitCR1",       [&](){ return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.0117 && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.009 && hh.fatJet2PNetXbb() > 0.95 && hh.fatJet1PNetXbb() > 0.95; },   UNITY);
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("FitCR2",       [&](){ return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.009 && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.006 && hh.fatJet2PNetXbb() > 0.95 && hh.fatJet1PNetXbb() > 0.95; },   UNITY);
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("FailFitCR1",       [&](){ return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.0117 && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.009 && hh.fatJet2PNetXbb() < 0.95; },   UNITY);
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("FailFitCR2",       [&](){ return  hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.009 && hh.disc_qcd_and_ttbar_Run2_enhanced_v24() < 0.006 && hh.fatJet2PNetXbb() < 0.95; },   UNITY);


////Top control region
cutflow.getCut("CutfatJetsMassSD");
cutflow.addCutToLastActiveCut("CutfatJetsXbb",       [&](){ return hh.fatJet1PNetXbb() > 0.1 && hh.fatJet2PNetXbb() > 0.1; },   UNITY);
cutflow.addCutToLastActiveCut("TTBarCR",       [&](){ return hh.fatJet1Tau3OverTau2() < 0.46 && hh.fatJet2Tau3OverTau2() < 0.46 &&  hh.fatJet1HasBJetCSVLoose() && hh.fatJet2HasBJetCSVLoose(); },   [&]() {return isTTJets ? (TopTagSF("0.46", year_, hh.fatJet1Pt()) * TopTagSF("0.46", year_, hh.fatJet2Pt())) : 1.0;} );
cutflow.getCut("CutfatJetsXbb");
cutflow.addCutToLastActiveCut("TTBarCR2",       [&](){ return hh.fatJet1Tau3OverTau2() < 0.39 && hh.fatJet2Tau3OverTau2() < 0.39 &&  hh.fatJet1HasBJetCSVLoose() && hh.fatJet2HasBJetCSVLoose(); },   [&]() {return isTTJets ? (TopTagSF("0.40", year_, hh.fatJet1Pt()) * TopTagSF("0.40", year_, hh.fatJet2Pt())) : 1.0;} );

/****Systematics******/
if(doSystematics)
{
    cutflow.addWgtSyst("BDTMassShapeUp",  [&](){return isTTJets ?  1.0 :1.06;});
    cutflow.addWgtSyst("BDTMassShapeDown",  [&](){return isTTJets ? 1.0: 0.94;});
    cutflow.addWgtSyst("BDTShapeUp",  [&](){return isTTJets ?  1.0 : (hh.disc_qcd_and_ttbar_Run2_enhanced_v24()  < 0.0117 ? 1.179 : (hh.disc_qcd_and_ttbar_Run2_enhanced_v24()< 0.028 ? 1.097 : 1.288));});
    cutflow.addWgtSyst("BDTShapeDown",  [&](){return isTTJets ?  1.0 : (hh.disc_qcd_and_ttbar_Run2_enhanced_v24()  < 0.0117 ? 1.-0.179 : (hh.disc_qcd_and_ttbar_Run2_enhanced_v24()< 0.028 ? 1.-0.097 : 1.-0.288));});
    cutflow.addWgtSyst("ttJetsCorrUp",  [&](){return isTTJets ?  ttjets_sf.getScaleFactorsFit(year_, hh.hh_pt(), 1)/ttjets_sf.getScaleFactorsFit(year_, hh.hh_pt(), 0) : 1.0;});
    cutflow.addWgtSyst("ttJetsCorrDown",  [&](){return isTTJets ? ttjets_sf.getScaleFactorsFit(year_, hh.hh_pt(), -1)/ttjets_sf.getScaleFactorsFit(year_, hh.hh_pt(), 0) : 1.0;});
}

//book histograms for cuts
if(not doSystematics) cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
else
{
    cutflow.bookHistogramsForCut(histograms, "SRBin1");
    cutflow.bookHistogramsForCut(histograms, "SRBin2");
    cutflow.bookHistogramsForCut(histograms, "SRBin3");
    cutflow.bookHistogramsForCut(histograms, "SRBin4");
    cutflow.bookHistogramsForCut(histograms, "FailSR");
    cutflow.bookHistogramsForCut(histograms, "TTBarCR");
    cutflow.bookHistogramsForCut(histograms, "FitCR1");
    cutflow.bookHistogramsForCut(histograms, "FitCR2");
    cutflow.bookHistogramsForCut(histograms, "FailFitCR1");
    cutflow.bookHistogramsForCut(histograms, "FailFitCR2");
}
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
	  weight = isData ?  1.0 : lumi*hh.weight()*hh.triggerEffWeight()*hh.pileupWeight();
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
