//C++ INCLUDES
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
//ROOT
#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TROOT.h>
//LOCAL INCLUDES
#include "hhtree.hh"
#include "anautil.h"

using namespace std;

int lumi = 137000.0;

int main ( int argc, char* argv[])
{


TChain * chain = new TChain("hh");

chain->Add("data/bbbb/ggHH_toBBBB_cit_tier_1pb_weighted.root");

hh.Init(chain);

int nEntries = chain->GetEntries();



TFile *outfile = new TFile("test.root", "recreate");

RooUtil::Cutflow cutflow;
RooUtil::Histograms histograms;

//define histograms
histograms.addHistogram("yield",               1,     0.,   1.,    [&]() { return 0; } );
histograms.addHistogram("hh_pt",               180,   0.,   1000., [&]() { return hh.hh_pt(); } );
histograms.addHistogram("hh_mass",             180,   0.,   1000., [&]() { return hh.hh_mass(); } );
histograms.addHistogram("FatJet1_msoftdrop",   180,   0.,   200.,  [&]() { return hh.nFatJet() > 0 ? hh.FatJet_msoftdrop()[0] : -999; } );
histograms.addHistogram("FatJet2_msoftdrop",   180,   0.,   200.,  [&]() { return hh.nFatJet() > 1 ? hh.FatJet_msoftdrop()[1] : -999; } );
histograms.addHistogram("FatJet1_btagDDBvL",   180,   0.,   1.0,   [&]() { return hh.nFatJet() > 0 ? hh.FatJet_btagDDBvL()[0] : -999; } );
histograms.addHistogram("FatJet2_btagDDBvL",   180,   0.,   1.0,   [&]() { return hh.nFatJet() > 1 ? hh.FatJet_btagDDBvL()[1] : -999; } );

//define cuts
cutflow.setTFile(outfile);
cutflow.addCut("CutWeight", [&](){ return 1; },   [&](){ return lumi*hh.weight(); });
//cutflow.addCutToLastActiveCut("CutHLT",             [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);
cutflow.addCutToLastActiveCut("TwoFatJets",         [&](){ return hh.nFatJet() >= 2; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsDDBCut",      [&](){ return hh.FatJet_btagDDBvL()[0] > 0.8 && hh.FatJet_btagDDBvL()[1] > 0.8; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsPtCut",       [&](){ return hh.FatJet_pt()[0] > 200.0 && hh.FatJet_pt()[1] > 200.0; },   UNITY);
cutflow.addCutToLastActiveCut("FatJetsSDMassCut",   [&](){ return hh.FatJet_msoftdrop()[0] > 100.0 && hh.FatJet_msoftdrop()[0] < 160.0 && hh.FatJet_msoftdrop()[1] > 100.0 && hh.FatJet_msoftdrop()[1] < 160.0; },   UNITY);
cutflow.addCutToLastActiveCut("CutHLT",             [&](){ return hh.HLT_PFHT1050() || hh.HLT_AK8PFJet360_TrimMass30() || hh.HLT_AK8PFJet380_TrimMass30() || hh.HLT_AK8PFJet400_TrimMass30() || hh.HLT_AK8PFJet420_TrimMass30() || hh.HLT_AK8PFHT800_TrimMass50() || hh.HLT_PFJet500() || hh.HLT_AK8PFJet500() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() || hh.HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() || hh.HLT_AK8PFJet330_PFAK8BTagCSV_p17(); },              UNITY);

//book histograms for cuts
cutflow.bookHistogramsForCutAndBelow(histograms, "CutWeight");
cutflow.bookCutflows();


for(int iEntry = 0; iEntry<nEntries; iEntry++)
{
 hh.GetEntry(iEntry);
 cutflow.fill();
 if(iEntry%100 == 0) cout<<"[INFO] processing event "<<iEntry<<" / "<<nEntries<<endl;
}

cutflow.saveOutput();
outfile->Close();

return 0;
}
