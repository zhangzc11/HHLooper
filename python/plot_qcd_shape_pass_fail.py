import ROOT as rt 
import numpy as np
import os

rt.gStyle.SetOptStat(0)
rt.gStyle.SetOptFit(0)

leftMargin   = 0.13
rightMargin  = 0.01
topMargin    = 0.07
bottomMargin = 0.12


outDir="/var/www/html/sharebox/HH/PFshapes/"

os.system("mkdir -p "+outDir)
os.system("cp index.php "+outDir)

def drawPassFail(hist_pass, hist_fail, label, region):
    myC2 = rt.TCanvas("myC2","myC2", 600, 600)

    pad1 = rt.TPad("pad1","pad1", 0.05, 0.33,0.95, 0.97)
    pad1.SetBottomMargin(0)
    pad1.SetRightMargin( rightMargin )
    pad1.SetLeftMargin( leftMargin )
    pad2 = rt.TPad("pad2","pad2", 0.05, 0.045, 0.95, 0.33)
    pad2.SetTopMargin(0.008)
    pad2.SetRightMargin( rightMargin )
    pad2.SetLeftMargin( leftMargin )
    pad2.SetBottomMargin(0.4)

    pad2.Draw()
    pad1.Draw()

    pad1.cd()

    hist_pass.GetYaxis().SetTitleOffset(1.25)
    hist_pass.SetMarkerStyle(20)
    hist_pass.SetMarkerColor(rt.kRed)
    hist_pass.SetLineColor(rt.kRed)
    hist_pass.SetLineWidth(2)
    hist_fail.SetMarkerStyle(21)
    hist_fail.SetMarkerColor(rt.kBlue)
    hist_fail.SetLineColor(rt.kBlue)
    hist_fail.SetLineWidth(2)

    hist_pass.GetYaxis().SetTitleSize(0.08)
    hist_pass.GetYaxis().SetLabelSize(0.045)
    hist_pass.GetYaxis().SetTitleOffset(0.8)
    maxY = max(hist_pass.GetMaximum(),hist_fail.GetMaximum())
    hist_pass.GetYaxis().SetRangeUser(0.0, 1.2*maxY)
    hist_pass.Draw("E")
    hist_fail.Draw("sameE")

    leg = rt.TLegend(0.6, 0.60, 0.97, 0.88)
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(42)
    leg.SetTextSize(0.07)
    leg.AddEntry(hist_pass, "pass ("+label+")", "ep")
    leg.AddEntry(hist_fail, "fail ("+label+")", "ep")
    leg.Draw()


    pad2.cd()
    pad2.SetGridy(1)
    ratio = hist_pass.Clone("ratio_data_over_mc")
    ratio.Divide(hist_fail)
    ratio.GetYaxis().SetTitle("pass/fail")
    ratio.GetYaxis().SetRangeUser(0.1,2.5)
    ratio.Draw("samePE")

    ratio.SetLineColor(1)
    ratio.SetLineWidth(2)
    ratio.SetMarkerStyle(20)
    ratio.SetMarkerColor(1)
    ratio.SetFillColorAlpha(1, 0)
    ratio.GetXaxis().SetTitleOffset(0.94)
    ratio.GetXaxis().SetTitleSize(0.18)
    ratio.GetXaxis().SetLabelSize(0.12)
    ratio.GetXaxis().SetLabelOffset(0.013)
    ratio.GetYaxis().SetTitleOffset(0.40)
    ratio.GetYaxis().SetTitleSize(0.17)
    ratio.GetYaxis().SetLabelSize(0.13)
    ratio.GetYaxis().SetTickLength(0.01)
    ratio.GetYaxis().SetNdivisions(505)


    myC2.SaveAs(outDir+"/mass_shape_pass_fail_"+label+"_"+region+".pdf")
    myC2.SaveAs(outDir+"/mass_shape_pass_fail_"+label+"_"+region+".png")
    myC2.SaveAs(outDir+"/mass_shape_pass_fail_"+label+"_"+region+".C")


vbdt="v24" # "v8p2"
inFile = rt.TFile("HHTo4BPlots_Run2_BDT"+vbdt+".root", "READ")

regions = ["Bin1", "Bin2", "Bin3"]
if vbdt ==  "v24":
    regions = ["Bin1", "Bin2", "Bin3", "Bin4"]
for region in regions:

    ##MC shape
    passName="histJet2MassBlind_"+region
    failName="histJet2Mass_fail"
    if region == "FitCR":
        passName="histJet2Mass_"+region
        failName="histJet2Mass_fail"+region

    hist_pass_MC = inFile.Get(passName+"_QCD")
    hist_fail_MC = inFile.Get(failName+"_QCD")

    hist_pass_MC.GetXaxis().SetRangeUser(50.,220.)
    hist_fail_MC.GetXaxis().SetRangeUser(50.,220.)

    hist_pass_MC.Scale(1.0/hist_pass_MC.Integral())
    hist_fail_MC.Scale(1.0/hist_fail_MC.Integral())
    drawPassFail(hist_pass_MC, hist_fail_MC, "MC", region+vbdt)

    ##Data shape
    hist_pass_Data = inFile.Get(passName+"_Data")
    hist_pass_Data.SetName(passName+"_Data_"+region)
    hist_fail_Data = inFile.Get(failName+"_Data")
    hist_fail_Data.SetName(failName+"_Data_"+region)

    for bkg in ["TTJets", "H", "VH",  "ttH", "others",  "HH"]:
        hist_pass_this = inFile.Get(passName+"_"+bkg)
        hist_fail_this = inFile.Get(failName+"_"+bkg)
        hist_pass_Data.Add(hist_pass_this, -1.0)
        hist_fail_Data.Add(hist_fail_this, -1.0)

    hist_pass_Data.GetXaxis().SetRangeUser(50.,220.)
    hist_fail_Data.GetXaxis().SetRangeUser(50.,220.)

    hist_pass_Data.Scale(1.0/hist_pass_Data.Integral())
    hist_fail_Data.Scale(1.0/hist_fail_Data.Integral())
    drawPassFail(hist_pass_Data, hist_fail_Data, "Data", region+vbdt)

    del hist_pass_MC
    del hist_pass_Data
    del hist_fail_MC
    del hist_fail_Data


