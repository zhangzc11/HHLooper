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

using namespace std;

int main ( int argc, char* argv[])
{

TChain * chain = new TChain("hh");

chain->Add("data/bbbb/ggHH_toBBBB_cit_tier_1pb_weighted.root");

hh.Init(chain);


cout<<"test" <<endl;
hh.GetEntry(1);
cout<<hh.run()<<endl;
cout<<hh.hh_pt()<<endl;
for(int idx=0; idx<hh.nFatJet(); idx++)
{
 cout<<hh.FatJet_btagDDBvL()[idx]<<", ";
}
cout<<endl;

return 0;
}
