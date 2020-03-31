from __future__ import print_function
import numpy as np
import math
import ROOT as r
import shlex
import sys
import os

leftMargin   = 0.1
rightMargin  = 0.01
topMargin    = 0.07
bottomMargin = 0.12
r.gStyle.SetOptStat(0)
r.gStyle.SetOptFit(111)

r.gROOT.SetBatch(1)

def rebin(hists, nbin):
    return
    for hist in hists:
        if not hist: continue
        currnbin = hist.GetNbinsX()
        fac = currnbin / nbin
        if float(fac).is_integer() and fac > 0:
            hist.Rebin(fac)
def remove_underflow(hists):
    def func(hist):
        hist.SetBinContent(0, 0)
        hist.SetBinError(0, 0)
    if isinstance(hists, list):
        for hist in hists:
            func(hist)
    else:
        func(hists)
    return hists
def remove_overflow(hists):
    def func(hist):
        hist.SetBinContent(hist.GetNbinsX()+1, 0)
        hist.SetBinError(hist.GetNbinsX()+1, 0)
    if isinstance(hists, list):
        for hist in hists:
            func(hist)
    else:
        func(hists)
    return hists

def makeplot_single(
    sig_fnames_=None,
    bkg_fnames_=None,
    data_fname_=None,
    sig_legends_=None,
    bkg_legends_=None,
    sig_colors_=None,
    bkg_colors_=None,
    hist_name_=None,
    sig_scale_=1.0,
    dir_name_="plots",
    output_name_=None,
    extraoptions=None
    ):

    if sig_fnames_ == None or bkg_fnames_ == None or hist_name_ == None or sig_legends_ == None or bkg_legends_ == None:
        print("nothing to plot....")
        return
    print("making plot for "+hist_name_)
   
    s_color = [632, 617, 839, 800, 1]
    b_color = [920, 2007, 2005, 2003, 2001, 2011]
    if sig_colors_:
        s_color = sig_colors_
    if bkg_colors_:
        b_color = bkg_colors_
    
    tfs_sig = {}
    h1_sig = []
    maxY = 0.0
    if "stack_signal" in extraoptions and extraoptions["stack_signal"]:
        sig_scale_ = 1.0
        for idx in range(len(sig_legends_)):
            sig_legends_[idx] = sig_legends_[idx].split(" x ")[0]
    for idx in range(len(sig_fnames_)): 
        fn = sig_fnames_[idx]
        n = os.path.basename(fn.replace(".root", ""))
        tfs_sig[n] = r.TFile(fn)
        h1 = tfs_sig[n].Get(hist_name_)
        h1.SetName(hist_name_+"_sig_"+str(idx))
        h1.Scale(sig_scale_)
        h1.SetLineWidth(2)
        h1.SetLineColor(s_color[idx])
        print(h1.Integral())
        h1_sig.append(h1)
     
    tfs_bkg = {}
    h1_bkg = []
    for idx in range(len(bkg_fnames_)): 
        fn = bkg_fnames_[idx]
        n = os.path.basename(fn.replace(".root", ""))
        tfs_bkg[n] = r.TFile(fn)
        h1 = tfs_bkg[n].Get(hist_name_)
        h1.SetName(hist_name_+"_bkg_"+str(idx))
        h1.SetLineWidth(2)
        h1.SetLineColor(b_color[idx])
        h1.SetFillColorAlpha(b_color[idx], 1)
        print(h1.Integral())
        h1_bkg.append(h1)
    h1_data = None 

    tfs_data = {}
    if data_fname_:
        tfs_data["fdata"] = r.TFile(data_fname_)
        h1_data = tfs_data["fdata"].Get(hist_name_)
        h1_data.SetName(hist_name_+"_data")
        h1_data.SetBinErrorOption(1)
        h1_data.SetLineColor(1)
        h1_data.SetLineWidth(2)
        h1_data.SetMarkerColor(1)
        h1_data.SetMarkerStyle(20)
        print(h1_data.Integral())
    if "nbins" in extraoptions:
        rebin(h1_sig, extraoptions["nbins"])   
        rebin(h1_bkg, extraoptions["nbins"])   
        if h1_data:
            rebin([h1_data], extraoptions["nbins"])   
    if "remove_underflow" in extraoptions:
        if extraoptions["remove_underflow"]:
            remove_underflow(h1_sig)
            remove_underflow(h1_bkg)
            if h1_data:
                remove_underflow([h1_data])
    if "remove_overflow" in extraoptions:
        if extraoptions["remove_overflow"]:
            remove_overflow(h1_sig)
            remove_overflow(h1_bkg)
            if h1_data:
                remove_overflow([h1_data])
    myC = r.TCanvas("myC","myC", 600, 600)
    myC.SetTicky(1)
    pad1 = r.TPad("pad1","pad1", 0.05, 0.33,0.95, 0.97) 
    pad1.SetBottomMargin(0)
    pad1.SetRightMargin( rightMargin )
    pad1.SetLeftMargin( leftMargin ) 
    pad2 = r.TPad("pad2","pad2", 0.05, 0.045, 0.95, 0.33)
    pad2.SetBottomMargin(0.4)
    pad2.SetTopMargin(0.008)
    pad2.SetRightMargin( rightMargin )
    pad2.SetLeftMargin( leftMargin )

    pad2.Draw()
    pad1.Draw()

    pad1.cd()

    stack = r.THStack("stack", "stack")
    hist_all = h1_sig[0].Clone("hist_all")
    hist_all.Scale(1.0/sig_scale_)
    hist_s = h1_sig[0].Clone("hist_s")
    hist_b = h1_bkg[0].Clone("hist_b")
    for idx in range(len(h1_bkg)):
        stack.Add(h1_bkg[idx])
        hist_all.Add(h1_bkg[idx])
        if idx > 0:
            hist_b.Add(h1_bkg[idx])
    for idx in range(len(h1_sig)):
        if idx > 0:
            hist_temp = h1_sig[idx].Clone(h1_sig[idx].GetName()+"_temp")
            hist_temp.Scale(1.0/sig_scale_)
            hist_all.Add(hist_temp)
            hist_s.Add(h1_sig[idx])

    stack.SetTitle("")
    if "stack_signal" in extraoptions and extraoptions["stack_signal"]:
        for idx in range(len(h1_sig)):
            h1_sig[idx].SetFillColorAlpha(s_color[idx], 1)
            stack.Add(h1_sig[idx])
        if stack.GetMaximum() > maxY:
            maxY = stack.GetMaximum()
        stack.Draw("hist")
    else:
        stack.Draw("hist")
        if stack.GetMaximum() > maxY:
            maxY = stack.GetMaximum()
        for idx in range(len(h1_sig)):
            if h1_sig[idx].GetMaximum() > maxY:
                maxY = h1_sig[idx].GetMaximum()
            h1_sig[idx].Draw("samehist")
    
    if h1_data:
        if h1_data.GetMaximum() > maxY:
            maxY = h1_data.GetMaximum()
        h1_data.Draw("samePEX0")
    stack.GetYaxis().SetTitle("Events")
    stack.GetYaxis().SetTitleOffset(0.6)
    stack.GetYaxis().SetTitleSize(0.08)
    stack.GetYaxis().SetLabelSize(0.05)
    stack.GetYaxis().CenterTitle()

    leg = r.TLegend(0.65, 0.65, 0.95, 0.88)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(42)
    for idx in range(len(h1_bkg)):
        leg.AddEntry(h1_bkg[idx], bkg_legends_[idx], "F")
    for idx in range(len(h1_sig)):
        if "stack_signal" in extraoptions and extraoptions["stack_signal"]:
            leg.AddEntry(h1_sig[idx], sig_legends_[idx], "F")
        else:
            leg.AddEntry(h1_sig[idx], sig_legends_[idx], "L")
    if h1_data:
        leg.AddEntry(h1_data, "Data", "ep")
    leg.Draw()

    pad2.cd()
    pad2.SetGridy(1)
    ratio = None
    ratio_Low  = 0.0
    ratio_High  = 2.0
    if h1_data:
        ratio = h1_data.Clone("ratio")
        ratio.Divide(hist_all)
        print("debug ratio divide: "+str(h1_data.Integral()))
        print("debug ratio divide: "+str(hist_all.Integral()))
        if "ratio_range" in extraoptions:
            ratio_Low = extraoptions["ratio_range"][0]
            ratio_High = extraoptions["ratio_range"][1]
        ratio.GetYaxis().SetTitle("data/mc")
        ratio.GetYaxis().SetRangeUser(ratio_Low, ratio_High)
        ratio.Draw("same PE")
    else:
        ratio = h1_sig[0].Clone("ratio")
        ratio_High = 0.0
        for ibin in range(1,ratio.GetNbinsX()+1):
            s = hist_s.GetBinContent(ibin) / sig_scale_
            b = hist_b.GetBinContent(ibin)
            L = 0.0
            if b > 0.0:
                L = s/math.sqrt(b)
                if L > ratio_High:
                    ratio_High = L
            ratio.SetBinContent(ibin, L)
        ratio.GetYaxis().SetRangeUser(ratio_Low, ratio_High*1.2)
        ratio.GetYaxis().SetTitle("S/#sqrt{B}")
        ratio.Draw("samehist")
    ratio.SetLineColor(1)
    ratio.SetLineWidth(2)
    ratio.SetMarkerStyle(20)
    ratio.SetMarkerColor(1)
    ratio.SetFillColorAlpha(1, 0)
    ratio.GetXaxis().SetTitleOffset(0.94)
    ratio.GetXaxis().SetTitleSize(0.18)
    ratio.GetXaxis().SetLabelSize(0.12)
    ratio.GetXaxis().SetLabelOffset(0.013)
    ratio.GetYaxis().SetTitleOffset(0.32)
    ratio.GetYaxis().SetTitleSize(0.17)
    ratio.GetYaxis().SetLabelSize(0.13)
    ratio.GetYaxis().SetTickLength(0.01)
    ratio.GetYaxis().SetNdivisions(505)

    if "cutflow" in hist_name_:
        ratio.GetXaxis().SetTitle("")
    if "xaxis_label" in extraoptions and extraoptions["xaxis_label"] != None:
        x_title = extraoptions["xaxis_label"]
        ratio.GetXaxis().SetTitle(x_title)
    ratio.GetYaxis().CenterTitle()

    ##########draw CMS preliminary
    pad1.cd()
    tex1 = r.TLatex(leftMargin, 0.91, "CMS")
    tex1.SetNDC()
    tex1.SetTextFont(61)
    tex1.SetTextSize(0.070)
    tex1.SetLineWidth(2)
    tex1.Draw()
    tex2 = r.TLatex(leftMargin+0.12,0.912,"Preliminary")
    tex2.SetNDC()
    tex2.SetTextFont(52)
    tex2.SetTextSize(0.055)
    tex2.SetLineWidth(2)
    tex2.Draw()
    
    lumi_value = 137
    if "lumi_value" in extraoptions:
        lumi_value = extraoptions["lumi_value"]
    tex3 = r.TLatex(0.72,0.912,"%d"%lumi_value+" fb^{-1} (13 TeV)")
    tex3.SetNDC()
    tex3.SetTextFont(42)
    tex3.SetTextSize(0.055)
    tex3.SetLineWidth(2)
    tex3.Draw()


    outFile = dir_name_
    if output_name_:
        outFile = outFile + "/" +output_name_
    else:
        outFile = outFile + "/" + hist_name_

    print("maxY = "+str(maxY))
    stack.SetMaximum(maxY*1.3)

    #print everything into txt file
    text_file = open(outFile+"_linY.txt", "w")
    text_file.write("bin   ")
    for idx in range(len(bkg_legends_)):
        text_file.write(" | %21s"%bkg_legends_[idx])
    text_file.write(" | %21s"%("total B"))
    for idx in range(len(sig_legends_)):
        text_file.write(" | %25s"%sig_legends_[idx])
    if h1_data:
        text_file.write(" | data")
    text_file.write("\n------")
    for idx in range(24*(len(bkg_legends_) + 1)+ 29*len(sig_legends_)):
        text_file.write("-")
    if h1_data:
        text_file.write("-------")
    text_file.write("\n")
    for ibin in range(1,h1_sig[0].GetNbinsX()+1):
        text_file.write("%3d"%ibin+"   ")
        for idx in range(len(bkg_legends_)):
            text_file.write(" | %7.3f "%h1_bkg[idx].GetBinContent(ibin)+"$\\pm$"+ " %7.3f"%h1_bkg[idx].GetBinError(ibin))
        text_file.write(" | %7.3f "%hist_b.GetBinContent(ibin)+"$\\pm$"+ " %7.3f"%hist_b.GetBinError(ibin))
        for idx in range(len(sig_legends_)):
            text_file.write(" | %9.3f "%h1_bkg[idx].GetBinContent(ibin)+"$\\pm$"+ " %9.3f"%h1_bkg[idx].GetBinError(ibin))
        if h1_data:
            text_file.write(" | %d"%h1_data.GetBinContent(ibin))
        text_file.write("\n")
    text_file.close()
    os.system("cp "+outFile+"_linY.txt "+outFile+"_logY.txt")

    
    myC.SaveAs(outFile+"_linY.png")
    myC.SaveAs(outFile+"_linY.pdf")
    myC.SaveAs(outFile+"_linY.C")
    pad1.cd()
    stack.SetMaximum(maxY*10.0)
    stack.SetMinimum(0.1)
    pad1.SetLogy()
    myC.SaveAs(outFile+"_logY.png")
    myC.SaveAs(outFile+"_logY.pdf")
    myC.SaveAs(outFile+"_logY.C")

def makeplot_all(
    sig_fnames_=None,
    bkg_fnames_=None,
    data_fname_=None,
    sig_legends_=None,
    bkg_legends_=None,
    sig_colors_=None,
    bkg_colors_=None,
    regions_name_=None,
    sig_scale_=1.0,
    dir_name_="plots",
    output_name_=None,
    extraoptions=None
    ):

    if regions_name_ == None or sig_fnames_ == None:
        print("nothing to plot....")
        return
    print("making all plots in the following regions: ")
    print(regions_name_)

    hist_names = []
    for region in regions_name_:
        tf = r.TFile(sig_fnames_[0])
        for key in tf.GetListOfKeys():
            if region in key.GetName():
                hist_names.append(key.GetName())
    print("find the following histgrams to plot:")
    print(hist_names)
    for hist_name in hist_names:
        makeplot_single(sig_fnames_=sig_fnames_, bkg_fnames_ = bkg_fnames_, data_fname_=data_fname_, sig_legends_=sig_legends_, bkg_legends_=bkg_legends_, sig_colors_=sig_colors_, bkg_colors_=bkg_colors_, hist_name_=hist_name, sig_scale_=sig_scale_, dir_name_=dir_name_, extraoptions=extraoptions)


