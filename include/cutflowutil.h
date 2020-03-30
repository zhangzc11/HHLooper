#ifndef cutflowutil_h
#define cutflowutil_h

#include <tuple>
#include <vector>
#include <map>
#include "TH1.h"
#include "TH2.h"
#include "TString.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sys/ioctl.h>
#include <functional>

#define TREEMAPSTRING std::string
#define CUTFLOWMAPSTRING TString
#define DATA c_str

namespace RooUtil
{
    namespace CutflowUtil
    {

        class CutNameList
        {
            public:
            std::vector<TString> cutlist;
            CutNameList() {}
            CutNameList(const CutNameList& cutnamelist) { cutlist = cutnamelist.cutlist; }
            void clear() { cutlist.clear(); }
            void addCutName(TString cutname) { cutlist.push_back(cutname); }
        };

        class CutNameListMap
        {
            public:
            std::map<TString, CutNameList> cutlists;
            std::vector<TString> cutlist;
            CutNameList& operator[] (TString name) { return cutlists[name]; }
            void clear() { cutlists.clear(); }
            std::map<TString, std::vector<TString>> getStdVersion()
            {
                std::map<TString, std::vector<TString>> obj_cutlists;
                for (auto& cl : cutlists)
                    obj_cutlists[cl.first] = cl.second.cutlist;
                return obj_cutlists;
            }
        };

        std::tuple<std::map<CUTFLOWMAPSTRING, TH1F*>, std::map<CUTFLOWMAPSTRING, TH1F*>> createCutflowHistograms(CutNameListMap& cutlists, TString syst="");
        std::tuple<std::map<CUTFLOWMAPSTRING, TH1F*>, std::map<CUTFLOWMAPSTRING, TH1F*>> createCutflowHistograms(std::map<TString, std::vector<TString>>& cutlists, TString syst="");
        void saveCutflowHistograms(std::map<CUTFLOWMAPSTRING, TH1F*>& cutflows, std::map<CUTFLOWMAPSTRING, TH1F*>& rawcutflows);

    }

    class CutTree
    {
        public:
            TString name; 
            CutTree* parent;
            std::vector<CutTree*> parents;
            std::vector<CutTree*> children;
            std::vector<TString> systcutnames;
            std::vector<CutTree*> systcuts;
            std::map<TString, CutTree*> systs;
            int pass;
            float weight;
            std::vector<int> systpasses;
            std::vector<float> systweights;
            bool pass_this_cut;
            float weight_this_cut;
            std::function<bool()> pass_this_cut_func;
            std::function<float()> weight_this_cut_func;
//            std::vector<TString> hists1d;
//            std::vector<std::tuple<TString, TString>> hists2d;
            std::map<TString, std::vector<std::tuple<TH1F*, std::function<float()>>>> hists1d;
            std::map<TString, std::vector<std::tuple<TH1F*, std::function<std::vector<float>()>, std::function<std::vector<float>()>>>> hists1dvec;
            std::map<TString, std::vector<std::tuple<TH2F*, std::function<float()>, std::function<float()>>>> hists2d;
            std::map<TString, std::vector<std::tuple<TH2F*, std::function<std::vector<float>()>, std::function<std::vector<float>()>, std::function<std::vector<float>()>>>> hists2dvec;
            std::vector<std::tuple<int, int, unsigned long long>> eventlist;
            CutTree(TString n) : name(n), parent(0), pass(false), weight(0) {}
            ~CutTree()
            {
                for (auto& child : children)
                {
                    if (child)
                        delete child;
                }
            }
            void writeEventList(TString ofilename)
            {
                std::ofstream outFile(ofilename);
                for (auto& tuple : eventlist)
                {
                    int run = std::get<0>(tuple);
                    int lumi = std::get<1>(tuple);
                    unsigned long long evt = std::get<2>(tuple);
                    outFile << run << ":" << lumi << ":" << evt << std::endl;
                }
                outFile.close();
            }
            void addCut(TString n)
            {
                CutTree* obj = new CutTree(n);
                obj->parent = this;
                obj->parents.push_back(this);
                children.push_back(obj);
            }
            void addSyst(TString syst)
            {
                // If already added ignore
                if (systs.find(syst) != systs.end())
                    return;
                // Syst CutTree object knows the parents, and children, however, the children does not know the syst-counter-part parent, nor the parent knows the syste-counter-part children.
                CutTree* obj = new CutTree(this->name + syst);
                systs[syst] = obj;
                systcutnames.push_back(syst);
                systcuts.push_back(obj);
                systpasses.push_back(1);
                systweights.push_back(1);
                obj->children = this->children;
                obj->parents = this->parents;
                obj->parent = this->parent;
            }
            void addHist1D(TH1F* h, std::function<float()> var, TString syst)
            {
                if (syst.IsNull())
                    hists1d["Nominal"].push_back(std::make_tuple(h, var));
                else
                    hists1d[syst].push_back(std::make_tuple(h, var));
            }
            void addHist1DVec(TH1F* h, std::function<std::vector<float>()> var, std::function<std::vector<float>()> wgt, TString syst)
            {
                if (syst.IsNull())
                    hists1dvec["Nominal"].push_back(std::make_tuple(h, var, wgt));
                else
                    hists1dvec[syst].push_back(std::make_tuple(h, var, wgt));
            }
            void addHist2D(TH2F* h, std::function<float()> varx, std::function<float()> vary, TString syst)
            {
                if (syst.IsNull())
                    hists2d["Nominal"].push_back(std::make_tuple(h, varx, vary));
                else
                    hists2d[syst].push_back(std::make_tuple(h, varx, vary));
            }
            void addHist2DVec(TH2F* h, std::function<std::vector<float>()> varx, std::function<std::vector<float>()> vary, std::function<std::vector<float>()> elemwgt, TString syst)
            {
                if (syst.IsNull())
                    hists2dvec["Nominal"].push_back(std::make_tuple(h, varx, vary, elemwgt));
                else
                    hists2dvec[syst].push_back(std::make_tuple(h, varx, vary, elemwgt));
            }
            CutTree* getCutPointer(TString n)
            {
                // If the name match then return itself
                if (name.EqualTo(n))
                {
                    return this;
                }
                else
                {
                    // Otherwise, loop over the children an if a children has the correct one return the found CutTree
                    for (auto& child : children)
                    {
                        CutTree* c = child->getCutPointer(n);
                        if (c)
                            return c;
                    }
                    return 0;
                }
            }
            // Wrapper to return the object instead of pointer
            CutTree& getCut(TString n)
            {
                CutTree* c = getCutPointer(n);
                if (c)
                {
                    return *c;
                }
                else
                {
                    //RooUtil::error(TString::Format("Asked for %s cut, but did not find the cut", n.Data()));
                    return *this;
                }
            }
            std::vector<TString> getCutList(TString n, std::vector<TString> cut_list=std::vector<TString>())
            {
                // Main idea: start from the end node provided by the first argument "n", and work your way up to the root node.
                //
                // The algorithm will first determine whether I am starting from a specific cut requested by the user or within in recursion.
                // If the cut_list.size() == 0, the function is called by the user (since no list is aggregated so far)
                // In that case, first find the pointer to the object we want and set it to "c"
                // If cut_list.size() is non-zero then take this as the cut that I am starting and I go up the chain to aggregate all the cuts prior to the requested cut
                CutTree* c = 0;
                if (cut_list.size() == 0)
                {
                    c = &getCut(n);
                    cut_list.push_back(c->name);
                }
                else
                {
                    c = this;
                    cut_list.push_back(n);
                }
                if (c->parent)
                {
                    return (c->parent)->getCutList((c->parent)->name, cut_list);
                }
                else
                {
                    std::reverse(cut_list.begin(), cut_list.end());
                    return cut_list;
                }
            }
            std::vector<TString> getEndCuts(std::vector<TString> endcuts=std::vector<TString>())
            {
                if (children.size() == 0)
                {
                    endcuts.push_back(name);
                    return endcuts;
                }
                for (auto& child : children)
                    endcuts = child->getEndCuts(endcuts);
                return endcuts;
            }
            std::vector<TString> getCutListBelow(TString n, std::vector<TString> cut_list=std::vector<TString>())
            {
                // Main idea: start from the node provided by the first argument "n", and work your way down to the ends.
                CutTree* c = 0;
                if (cut_list.size() == 0)
                {
                    c = &getCut(n);
                    cut_list.push_back(c->name);
                }
                else
                {
                    c = this;
                    cut_list.push_back(n);
                }
                if (children.size() > 0)
                {
                    for (auto& child : c->children)
                    {
                        cut_list = child->getCutListBelow(child->name, cut_list);
                    }
                    return cut_list;
                }
                else
                {
                    return cut_list;
                }
            }
            void clear()
            {
                pass = false;
                weight = 0;
                for (auto& child : children)
                    child->clear();
            }
            void addSyst(TString syst, std::vector<TString> patterns, std::vector<TString> vetopatterns=std::vector<TString>())
            {
                for (auto& pattern : patterns)
                    if (name.Contains(pattern))
                    {
                        bool veto = false;
                        for (auto& vetopattern : vetopatterns)
                        {
                            if (name.Contains(vetopattern))
                                veto = true;
                        }
                        if (not veto)
                            addSyst(syst);
                    }
                for (auto& child : children)
                    child->addSyst(syst, patterns, vetopatterns);
            }
            void clear_passbits()
            {
                pass = 0;
                weight = 0;
                for (auto& child : children)
                    child->clear_passbits();
            }
            void evaluate(TString cutsystname="", bool doeventlist=false, bool aggregated_pass=true, float aggregated_weight=1)
            {
                evaluate_use_lambda(cutsystname, doeventlist, aggregated_pass, aggregated_weight);
            }
            void evaluate_use_lambda(TString cutsystname="", bool doeventlist=false, bool aggregated_pass=true, float aggregated_weight=1)
            {
                if (!parent)
                {
                    clear_passbits();
                    pass = 1;
                    weight = 1;
                }
                else
                {
                    if (cutsystname.IsNull())
                    {
                        if (pass_this_cut_func)
                        {
                            pass = pass_this_cut_func() && aggregated_pass;
                            weight = weight_this_cut_func() * aggregated_weight;
                            if (!pass)
                                return;
                        }
                        else
                        {
                            TString msg = "cowardly passing the event because cut and weight func not set! cut name = " + name;
                            //warning(msg);
                            pass = aggregated_pass;
                            weight = aggregated_weight;
                        }
                    }
                    else
                    {
                        if (systs.find(cutsystname) == systs.end())
                        {
                            if (pass_this_cut_func)
                            {
                                pass = pass_this_cut_func() && aggregated_pass;
                                weight = weight_this_cut_func() * aggregated_weight;
                                if (!pass)
                                    return;
                            }
                            else
                            {
                                TString msg = "cowardly passing the event because cut and weight func not set! cut name = " + name;
                                //warning(msg);
                                pass = aggregated_pass;
                                weight = aggregated_weight;
                            }
                        }
                        else
                        {
                            if (systs[cutsystname]->pass_this_cut_func)
                            {
                                pass = systs[cutsystname]->pass_this_cut_func() && aggregated_pass;
                                weight = systs[cutsystname]->weight_this_cut_func() * aggregated_weight;
                                if (!pass)
                                    return;
                            }
                            else
                            {
                                TString msg = "cowardly passing the event because cut and weight func not set! cut name = " + name + " syst name = " + cutsystname;
                                //warning(msg);
                                pass = aggregated_pass;
                                weight = aggregated_weight;
                            }
                        }
                    }
                }
                for (auto& child : children)
                    child->evaluate_use_lambda(cutsystname, doeventlist, pass, weight);
            }
            void evaluate_use_internal_variable(TString cutsystname="", bool doeventlist=false, bool aggregated_pass=true, float aggregated_weight=1)
            {
                if (!parent)
                {
                    clear_passbits();
                    pass = 1;
                    weight = 1;
                }
                else
                {
                    if (cutsystname.IsNull())
                    {
                        pass = pass_this_cut && aggregated_pass;
                        weight = weight_this_cut * aggregated_weight;
                        if (!pass)
                            return;
                    }
                    else
                    {
                        if (systs.find(cutsystname) == systs.end())
                        {
                            pass = pass_this_cut && aggregated_pass;
                            weight = weight_this_cut * aggregated_weight;
                            if (!pass)
                                return;
                        }
                        else
                        {
                            pass = systs[cutsystname]->pass_this_cut && aggregated_pass;
                            weight = systs[cutsystname]->weight_this_cut * aggregated_weight;
                            if (!pass)
                                return;
                        }
                    }
                }
                for (auto& child : children)
                    child->evaluate_use_internal_variable(cutsystname, doeventlist, pass, weight);
            }
            void sortEventList()
            {
                std::sort(eventlist.begin(), eventlist.end(),
                        [](const std::tuple<int, int, unsigned long long>& a, const std::tuple<int, int, unsigned long long>& b)
                        {
                            if (std::get<0>(a) != std::get<0>(b)) return std::get<0>(a) < std::get<0>(b);
                            else if (std::get<1>(a) != std::get<1>(b)) return std::get<1>(a) < std::get<1>(b);
                            else if (std::get<2>(a) != std::get<2>(b)) return std::get<2>(a) < std::get<2>(b);
                            else return true;
                        }
                        );
            }
            void clearEventList()
            {
                eventlist.clear();
            }
            void addEventList(int run, int lumi, unsigned long long evt)
            {
                eventlist.push_back(std::make_tuple(run, lumi, evt));
            }
            void fillHistograms(TString syst, float extrawgt)
            {
                // If the cut didn't pass then stop
                if (!pass)
                    return;

                if (hists1d.size() != 0 or hists2d.size() != 0 or hists2dvec.size() != 0 or hists1dvec.size() != 0)
                {
                    TString systkey = syst.IsNull() ? "Nominal" : syst;
                    for (auto& tuple : hists1d[systkey])
                    {
                        TH1F* h = std::get<0>(tuple);
                        std::function<float()> vardef = std::get<1>(tuple);
                        h->Fill(vardef(), weight * extrawgt);
                    }
                    for (auto& tuple : hists2d[systkey])
                    {
                        TH2F* h = std::get<0>(tuple);
                        std::function<float()> varxdef = std::get<1>(tuple);
                        std::function<float()> varydef = std::get<2>(tuple);
                        h->Fill(varxdef(), varydef(), weight * extrawgt);
                    }
                    for (auto& tuple : hists1dvec[systkey])
                    {
                        TH1F* h = std::get<0>(tuple);
                        std::function<std::vector<float>()> vardef = std::get<1>(tuple);
                        std::function<std::vector<float>()> wgtdef = std::get<2>(tuple);
                        std::vector<float> varx = vardef();
                        std::vector<float> elemwgts;
                        if (wgtdef)
                            elemwgts = wgtdef();
                        for (unsigned int i = 0; i < varx.size(); ++i)
                        {
                            if (wgtdef)
                                h->Fill(varx[i], weight * extrawgt * elemwgts[i]);
                            else
                                h->Fill(varx[i], weight * extrawgt);
                        }
                    }
                    for (auto& tuple : hists2dvec[systkey])
                    {
                        TH2F* h = std::get<0>(tuple);
                        std::function<std::vector<float>()> varxdef = std::get<1>(tuple);
                        std::function<std::vector<float>()> varydef = std::get<2>(tuple);
                        std::function<std::vector<float>()> wgtdef  = std::get<3>(tuple);
                        std::vector<float> varx = varxdef();
                        std::vector<float> vary = varydef();
                        if (varx.size() != vary.size())
                        {
                            TString msg = "the vector input to be looped over do not have same length for x and y! check the variable definition for histogram ";
                            msg += h->GetName();
                            //warning(msg);
                        }
                        std::vector<float> elemwgts;
                        if (wgtdef)
                            elemwgts = wgtdef();
                        for (unsigned int i = 0; i < varx.size(); ++i)
                        {
                            if (wgtdef)
                                h->Fill(varx[i], vary[i], weight * extrawgt * elemwgts[i]);
                            else
                                h->Fill(varx[i], vary[i], weight * extrawgt);
                        }
                    }
                }
                for (auto& child : children)
                    child->fillHistograms(syst, extrawgt);
            }
    };
}

#endif
