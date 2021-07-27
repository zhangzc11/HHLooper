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
#include <TString.h>
#include <TROOT.h>
#include <TRandom3.h>

#include "ROOT/RDataFrame.hxx"
#include "ROOT/RVec.hxx"
#include "ROOT/RDF/RInterface.hxx"

using namespace ROOT::VecOps;
using RNode = ROOT::RDF::RNode;


using namespace std;

double lumi = 139.0;
TRandom3* r_nominal = new TRandom3(0);
const float pi = 3.141592653;


struct histogram_type{
   TString savename;
   TString title;
   int nbins;
   double xlow;
   double xhigh;
   std::string varname;
};

struct cut_type{
   TString cutname;
   std::string weight;
   RNode node;
};


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

std::string year_ = "all";
if(input.find("2016") != std::string::npos) {year_ = "2016"; lumi = 36.2;}
if(input.find("2017") != std::string::npos) {year_ = "2017"; lumi = 44.3;}
if(input.find("2018") != std::string::npos) {year_ = "2018"; lumi = 58.5;}
system(("mkdir -p hists/"+label+"/"+year_).c_str());

bool isData = false;
if(isData_ == "1" || isData_ == "true" || isData_ == "yes" || isData_ == "True" || isData_ == "Yes") isData = true;

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

//construct RDataFrame:
ROOT::RDataFrame df("output", list_chain);
auto nEntries = df.Filter("1").Count();
cout<<"total number of events to process: "<<*nEntries<<endl;


ROOT::EnableImplicitMT();

//*********************define cuts*****************//
auto df_CutWeight = df.Define("lumi", [&]() {return isData ? 1.0 : lumi;}, {}).Define("isData", [&]() {return isData;}, {}).Define("CutWeight", "isData ? lumi : lumi*m_weight");
auto df_yield = df_CutWeight.Define("yield", [&]() {return 0.0;}, {});
auto df_CutPhPtOverMgg = df_yield.Filter("ph_pt1/m_mgg > 0.35 && ph_pt2/m_mgg > 0.25", "CutPhPtOverMgg");
auto df_CutMgg = df_CutPhPtOverMgg.Filter("m_mgg > 105.0 && m_mgg < 160.0","CutMgg");
auto df_CutNbVeto = df_CutMgg.Filter("m_nbjet_fixed80 < 2", "CutNbVeto");
auto df_NTISideBand = df_CutNbVeto.Filter("(!(ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2)) && (m_mgg < 120. || m_mgg > 130.)", "NTISideBand");
auto df_NTIHPeak = df_CutNbVeto.Filter("(!(ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2)) && (m_mgg > 123. && m_mgg < 127.)", "NTIHPeak");
auto df_TISideBand = df_CutNbVeto.Filter("ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2 && (m_mgg < 120. || m_mgg > 130.)", "TISideBand");
auto df_TIHPeak = df_CutNbVeto.Filter("ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2 && (m_mgg > 123. && m_mgg < 127.)", "TIHPeak");

//calculate scale factors for continuum background
double SF1 = 1.0;
double SF2 = 1.0;
if(isData)
{
    auto hist_NTISideBand = df_NTISideBand.Histo1D({"yield_NTISideBand", "", 1, 0., 1.}, "yield", "CutWeight");
    auto hist_NTIHPeak = df_NTIHPeak.Histo1D({"yield_NTIHPeak", "", 1, 0., 1.}, "yield", "CutWeight");
    auto hist_TISideBand = df_TISideBand.Histo1D({"yield_TIHSideBand", "", 1, 0., 1.}, "yield", "CutWeight");
    auto hist_TIHPeak = df_TIHPeak.Histo1D({"yield_TIHPeak", "", 1, 0., 1.}, "yield", "CutWeight");

    SF1 = hist_NTIHPeak->Integral() / hist_NTISideBand->Integral();
    SF2 = hist_TISideBand->Integral() /hist_NTISideBand->Integral();
}

cout<<"SF1: "<<SF1<<endl;
cout<<"SF2: "<<SF2<<endl;

auto df_SR = df_CutNbVeto.Filter("ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2", "SR");
auto df_SFweight = df_CutNbVeto.Define("SF1", [&](){return SF1;}, {}).Define("SF2", [&](){return SF2;}, {}).Define("SFweight2", "CutWeight * SF2").Define("SFweight12", "CutWeight * SF1 * SF2");
auto df_SREstimateFull = df_SFweight.Filter("isData ? (!(ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2)) : (ph_isTight1 && ph_isTight2 && ph_iso1 && ph_iso2)", "SREstimateFull");
auto df_SREstimatePeak = df_SREstimateFull.Filter("m_mgg > 123. && m_mgg < 127.", "SREstimatePeak");

//************************************************//




//*******select cuts to save histogram************//
std::vector<cut_type> cuts;
cuts.push_back((cut_type){"CutWeight", "CutWeight", df_CutWeight});
cuts.push_back((cut_type){"CutMgg", "CutWeight", df_CutMgg});
cuts.push_back((cut_type){"CutNbVeto", "CutWeight", df_CutNbVeto});
cuts.push_back((cut_type){"SR", "CutWeight", df_SR});
cuts.push_back((cut_type){"SREstimateFull", "SFweight2", df_SREstimateFull});
cuts.push_back((cut_type){"SREstimatePeak", "SFweight2", df_SREstimatePeak});
//************************************************//

//******define histograms to save for each cut****//
std::vector<histogram_type> histograms;
histograms.push_back((histogram_type){"yield", "; yield; Events", 1, 0., 1., "yield"});
histograms.push_back((histogram_type){"gnn_score", "; GNN score; Events", 300, 0., 1., "gnn_score"});
histograms.push_back((histogram_type){"ph_pt1", "; p_{T}^{#gamma 1} (GeV); Events", 300, 0., 300., "ph_pt1"});
histograms.push_back((histogram_type){"ph_pt2", "; p_{T}^{#gamma 2} (GeV); Events", 300, 0., 300., "ph_pt2"});
histograms.push_back((histogram_type){"m_mgg", "; m_{#gamma#gamma} (GeV); Events", 300, 105., 160., "m_mgg"});
//************************************************//



//save histograms for all cuts:
TFile *outfile = new TFile(("hists/"+label+"/"+year_+"/"+outputFileName).c_str(), "recreate");
auto hist_yield_root = df_yield.Histo1D({cuts[0].cutname+"__"+histograms[0].savename, histograms[0].title, histograms[0].nbins, histograms[0].xlow, histograms[0].xhigh}, histograms[0].varname, cuts[0].weight);
std::vector<decltype(hist_yield_root)> hists;
hists.push_back(hist_yield_root);
for(int ic=0; ic<cuts.size(); ic++)
{
    for(int ih=0; ih<histograms.size(); ih++)
    {
        if(cuts[ic].cutname == "CutWeight" && histograms[ih].varname =="yield") continue;
        auto hist_temp = cuts[ic].node.Histo1D({cuts[ic].cutname+"__"+histograms[ih].savename, histograms[ih].title, histograms[ih].nbins, histograms[ih].xlow, histograms[ih].xhigh}, histograms[ih].varname, cuts[ic].weight);
        hists.push_back(hist_temp);
    }
}
for(int idx=0; idx<hists.size(); idx++) hists[idx]->Write();
outfile->Close();

return 0;
}
