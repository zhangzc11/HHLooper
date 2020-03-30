#include "cutflowutil.h"
//_______________________________________________________________________________________________________
std::tuple<std::map<CUTFLOWMAPSTRING, TH1F*>, std::map<CUTFLOWMAPSTRING, TH1F*>> RooUtil::CutflowUtil::createCutflowHistograms(RooUtil::CutflowUtil::CutNameListMap& cutlists, TString syst)
{
    std::map<TString, std::vector<TString>> obj = cutlists.getStdVersion();
    return createCutflowHistograms(obj, syst);
}

//_______________________________________________________________________________________________________
std::tuple<std::map<CUTFLOWMAPSTRING, TH1F*>, std::map<CUTFLOWMAPSTRING, TH1F*>> RooUtil::CutflowUtil::createCutflowHistograms(std::map<TString, std::vector<TString>>& cutlists, TString syst)
{
    std::map<CUTFLOWMAPSTRING, TH1F*> cutflows;
    std::map<CUTFLOWMAPSTRING, TH1F*> rawcutflows;
    for (auto& cutlist : cutlists)
    {
        cutflows[(cutlist.first+syst).Data()] = new TH1F(cutlist.first+syst + "_cutflow", "", cutlist.second.size(), 0, cutlist.second.size());
        rawcutflows[(cutlist.first+syst).Data()] = new TH1F(cutlist.first+syst + "_rawcutflow", "", cutlist.second.size(), 0, cutlist.second.size());
        cutflows[(cutlist.first+syst).Data()]->Sumw2();
        rawcutflows[(cutlist.first+syst).Data()]->Sumw2();
        cutflows[(cutlist.first+syst).Data()]->SetDirectory(0);
        rawcutflows[(cutlist.first+syst).Data()]->SetDirectory(0);
        for (unsigned int i = 0; i < cutlist.second.size(); ++i)
        {
            cutflows[(cutlist.first+syst).Data()]->GetXaxis()->SetBinLabel(i+1, cutlist.second[i]);
            rawcutflows[(cutlist.first+syst).Data()]->GetXaxis()->SetBinLabel(i+1, cutlist.second[i]);
        }
    }
    return std::make_tuple(cutflows, rawcutflows);
}

//_______________________________________________________________________________________________________
void RooUtil::CutflowUtil::saveCutflowHistograms(std::map<CUTFLOWMAPSTRING, TH1F*>& cutflows, std::map<CUTFLOWMAPSTRING, TH1F*>& rawcutflows)
{
    for (auto& cutflow : cutflows) cutflow.second->Write();
    for (auto& rawcutflow : rawcutflows) rawcutflow.second->Write();
}
