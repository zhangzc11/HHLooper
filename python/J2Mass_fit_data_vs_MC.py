import ROOT as rt
import numpy as np
import os

rt.gStyle.SetOptStat(0)
rt.gStyle.SetOptFit(111)

leftMargin   = 0.13
rightMargin  = 0.01
topMargin    = 0.07
bottomMargin = 0.12

baseDir = "/var/www/html/sharebox/HH/yield_AN_ttbar_cor/combine/"

#BDTbins =  ["1v24", "2v24", "3v24", "4v24"]
#x_bounds = [0.00, 0.0024, 0.0054, 0.0118, 0.10]

BDTbins =  ["1v8p2", "2v8p2", "3v8p2", "4v8p2"]
x_bounds = [0.00, 0.00008, 0.0002, 0.0004, 0.001]

y_values_data = []
ey_values_data = []
y_values_mc = []
ey_values_mc = []

os.system("mkdir -p plots")

myC = rt.TCanvas("myC","myC", 600, 600)
for idx in range(len(BDTbins)):
    file_this = rt.TFile(baseDir+"TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD.root")
    hist_this =  file_this.Get("TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD_bkg_5_stack_6_stack_6")
    hist_this_data =  file_this.Get("TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD_data")

    hist_this.SetMarkerStyle(21)
    hist_this.Draw()
    f1 = rt.TF1("gaus","gaus(0)",  135.0, 210.0)
    f1.SetLineColor(rt.kRed)
    hist_this.Fit(f1, "", "", 135.0, 210.0)
    y_values_mc.append(f1.GetParameter(1))
    ey_values_mc.append(f1.GetParError(1))
    myC.SaveAs("plots/TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD.pdf")
    myC.SaveAs("plots/TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD.png")

    hist_this_data.SetMarkerStyle(21)
    hist_this_data.Draw()
    upperFit = 210.0
    if idx == 3:
        upperFit = 300.0
    f1_data = rt.TF1("gaus","gaus(0)",  135.0, upperFit)
    f1_data.SetLineColor(rt.kRed)
    hist_this_data.Fit(f1_data, "", "", 135.0, upperFit)
    y_values_data.append(f1_data.GetParameter(1))
    ey_values_data.append(f1_data.GetParError(1))
    myC.SaveAs("plots/TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD_data.pdf")
    myC.SaveAs("plots/TTBarCRBDT"+BDTbins[idx]+"__fatJet2MassSD_data.png")

print(y_values_data)
print(ey_values_data)
print(y_values_mc)
print(ey_values_mc)

rt.gStyle.SetOptFit(0)

myC2 = rt.TCanvas("myC2","myC2", 600, 600)

hist_mass_vs_BDT_data = rt.TH1F("mass_vs_BDT_data", ";  event BDT; Jet2 mass (GeV); ", len(x_bounds)-1, np.array(x_bounds))
hist_mass_vs_BDT_mc = rt.TH1F("mass_vs_BDT_mc", ";  event BDT; Jet2 mass (GeV); ", len(x_bounds)-1, np.array(x_bounds))
for idx in range(len(y_values_mc)):
    hist_mass_vs_BDT_data.SetBinContent(idx+1, y_values_data[idx])
    hist_mass_vs_BDT_data.SetBinError(idx+1, ey_values_data[idx])
    hist_mass_vs_BDT_mc.SetBinContent(idx+1, y_values_mc[idx])
    hist_mass_vs_BDT_mc.SetBinError(idx+1, ey_values_mc[idx])
#myC.SetLogx(1)

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

hist_mass_vs_BDT_data.GetYaxis().SetTitleOffset(1.25)
hist_mass_vs_BDT_data.SetMarkerStyle(20)
hist_mass_vs_BDT_data.SetMarkerColor(rt.kRed)
hist_mass_vs_BDT_data.SetLineColor(rt.kRed)
hist_mass_vs_BDT_data.SetLineWidth(2)
hist_mass_vs_BDT_mc.SetMarkerStyle(21)
hist_mass_vs_BDT_mc.SetMarkerColor(rt.kBlue)
hist_mass_vs_BDT_mc.SetLineColor(rt.kBlue)
hist_mass_vs_BDT_mc.SetLineWidth(2)

hist_mass_vs_BDT_data.GetYaxis().SetTitleSize(0.08)
hist_mass_vs_BDT_data.GetYaxis().SetLabelSize(0.045)
hist_mass_vs_BDT_data.GetYaxis().SetTitleOffset(0.8)
hist_mass_vs_BDT_data.Draw("E")
hist_mass_vs_BDT_data.GetYaxis().SetRangeUser(165,175)
hist_mass_vs_BDT_mc.Draw("sameE")

leg = rt.TLegend(0.7, 0.60, 0.97, 0.88)
leg.SetFillStyle(0)
leg.SetBorderSize(0)
leg.SetTextFont(42)
leg.SetTextSize(0.07)
leg.AddEntry(hist_mass_vs_BDT_data, "data", "ep")
leg.AddEntry(hist_mass_vs_BDT_mc, "mc", "ep")
leg.Draw()


pad2.cd()
pad2.SetGridy(1)
ratio = hist_mass_vs_BDT_data.Clone("ratio_data_over_mc")
ratio.Divide(hist_mass_vs_BDT_mc)
ratio.GetYaxis().SetTitle("data/mc")
ratio.GetYaxis().SetRangeUser(0.95,1.05)
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
ratio.GetXaxis().SetNdivisions(505)


myC2.SaveAs("plots/mass_vs_BDT_data_vs_mc_"+BDTbins[0][1:]+".pdf")
myC2.SaveAs("plots/mass_vs_BDT_data_vs_mc_"+BDTbins[0][1:]+".png")
myC2.SaveAs("plots/mass_vs_BDT_data_vs_mc_"+BDTbins[0][1:]+".C")
