
import numpy as np
import math
import ROOT as r
from colors import *
import shlex
import sys

leftMargin   = 0.12
rightMargin  = 0.05
topMargin    = 0.07
bottomMargin = 0.12
r.gStyle.SetOptStat(0)
r.gStyle.SetOptFit(111)
signalcolors = [632, 617, 839, 800, 1]

#####usage:
#####for cut-based:  python yield.py
#####for BDT method: python yield.py 1

if __name__ == "__main__":
	isBDT = 0
	if(len(sys.argv) > 1):
		isBDT = int(sys.argv[1])

	xlabels = ["MjjIn - ee", "MjjIn - e#mu", "MjjIn - #mu#mu", 
			   "MjjOut - ee", "MjjOut - e#mu", "MjjOut - #mu#mu",
			   "SS1J - ee", "SS1J - e#mu", "SS1J - #mu#mu",
			   "0SFOS", "1SFOS", "2SFOS","",
			   "e#mu bin 1", "e#mu bin 2","e#mu bin 3","e#mu bin 4",
			   "ee/#mu#mu bin A", "ee/#mu#mu bin B","ee/#mu#mu bin C","",
			   "5 leptons", "6 leptons"]

	if isBDT:
		xlabels = ["MjjIn - ee", "MjjIn - e#mu", "MjjIn - #mu#mu", 
				   "MjjOut - ee", "MjjOut - e#mu", "MjjOut - #mu#mu",
				   "SS1J - ee", "SS1J - e#mu", "SS1J - #mu#mu",
				   "0SFOS", "1SFOS", "2SFOS","",
				   "e#mu bin 1", "e#mu bin 2","e#mu bin 3","e#mu bin 4", "e#mu bin 5",
				   "ee/#mu#mu bin A", "ee/#mu#mu bin B","",
				   "5 leptons", "6 leptons"]

	nCh_23L = 12
	nCh_4L = 7
	nCh_56L = 2
	nCh_total = nCh_23L + nCh_4L + nCh_56L

	maxY = 250.0
	maxSig = 3.9
	if isBDT:
		maxY = 120.0
	########################SS3L part########################
	#12 channels
	nS_23L = 5 #WWW, WWZ, WZZ, ZZZ, VH
	nB_23L = 5
	sigs_23L = np.zeros((nCh_23L, nS_23L+1))
	esigs_23L = np.zeros((nCh_23L, nS_23L+1))
	sigs_names_23L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
	bkgs_23L = np.zeros((nCh_23L, nB_23L+1))
	ebkgs_23L = np.zeros((nCh_23L, nB_23L+1))
	bkgs_names = ["#gamma#rightarrow lepton", "Charge mis-id", "Nonprompt leptons", "Lost/three leptons", "Irreducible", "B"]
	L_23L = [] #L=s/sqrt(B)

	sigs_lineNums_23L = [19, 23, 27, 31, 36, 37]
	bkgs_lineNums_23L = [15, 14, 13, 11, 12, 17]
	
	obs_23L = np.zeros(nCh_23L)
	obs_lineNums_23L = [41]

	def getSS3LyieldsFromLine(line_array):
		N = []
		eN = []
		for idx in range(len(line_array)):
			if line_array[idx] == "&":
				if "<" in line_array[idx+1]:
					N.append(0.0)
					eN.append(0.0)
				elif "Obs" in line_array[0]:
					N.append(float(line_array[idx+1]))
					eN.append(0.0)
				else:
					Ns = line_array[idx+1].replace("\\","").split("$pm$")
					N.append(float(Ns[0]))
					eN.append(float(Ns[1]))
		return N, eN
	inputFileName_23L = "../../tables/SS3l/result_detailed_allsig.tex"
	if isBDT:
		inputFileName_23L = "../../tables/SS3l/result_BDT.tex"	
	with open(inputFileName_23L, "r") as yield_file:
		lineNum = 0
		for this_line in yield_file:
			lineNum += 1
			line_array = shlex.split(this_line)
			if lineNum not in sigs_lineNums_23L+bkgs_lineNums_23L+obs_lineNums_23L:
				continue
			elif lineNum in sigs_lineNums_23L:
				sig_idx = sigs_lineNums_23L.index(lineNum)
				_N, _eN = getSS3LyieldsFromLine(line_array)
				sigs_23L[:,sig_idx] = np.array(_N)
				esigs_23L[:,sig_idx] = np.array(_eN)
			elif lineNum in bkgs_lineNums_23L:
				bkg_idx = bkgs_lineNums_23L.index(lineNum)
				_N, _eN = getSS3LyieldsFromLine(line_array)
				bkgs_23L[:,bkg_idx] = np.array(_N)
				ebkgs_23L[:,bkg_idx] = np.array(_eN)
			elif lineNum in obs_lineNums_23L:
				_N, _eN = getSS3LyieldsFromLine(line_array)
				obs_23L = np.array(_N)
	#add up bkgs/sigs
	for ich in range(0, nCh_23L):
		sigs_23L[ich][nS_23L] = sum(sigs_23L[ich][i] for i in range(nS_23L))
		esigs_23L[ich][nS_23L] = math.sqrt(sum(esigs_23L[ich][i]*esigs_23L[ich][i] for i in range(nS_23L)))
		bkgs_23L[ich][nB_23L] = sum(bkgs_23L[ich][i] for i in range(nB_23L))
		ebkgs_23L[ich][nB_23L] = math.sqrt(sum(ebkgs_23L[ich][i]*ebkgs_23L[ich][i] for i in range(nB_23L)))
	#print(sigs_23L)
	#print(esigs_23L)
	#print(bkgs_23L)
	#print(ebkgs_23L)

	#print(sigs_23L)
	#print(esigs_23L)
	#print(bkgs_23L)
	#print(ebkgs_23L)

	########################plot##################

	myC = r.TCanvas("myC","myC", 1000, 600)
	myC.SetTicky(1)

	pad1 = r.TPad("pad1","pad1", 0.05, 0.33,0.95, 0.97)
	#pad1.SetTicky(1)
	pad1.SetBottomMargin(0)
	pad1.SetRightMargin( rightMargin )
	pad1.SetLeftMargin( leftMargin )

	pad2 = r.TPad("pad2","pad2", 0.05, 0.045, 0.95, 0.33)
	pad2.SetTopMargin(0.04)
	#pad2.SetTicky(1)
	pad2.SetTopMargin(0.008)
	pad2.SetBottomMargin(0.4)
	pad2.SetRightMargin( rightMargin )
	pad2.SetLeftMargin( leftMargin )
	#pad2.SetGridy()
	pad2.Draw()
	pad1.Draw()

	pad1.cd()

	stack_b_23L = r.THStack("s_b_23L","s_b_23L")
	histcolors_23L = [920, 2007, 2005, 2003, 2001, 2011]
	for ib in range(0, nB_23L):
		h1_b = r.TH1F("h1_23L_b"+str(ib), "h1_23L_b"+str(ib), nCh_23L, 0, nCh_23L)
		for idx in range(1,nCh_23L+1):
			h1_b.SetBinContent(idx, bkgs_23L[idx-1][ib])
			h1_b.SetBinError(idx, ebkgs_23L[idx-1][ib])
		h1_b.SetLineColor(histcolors_23L[ib])
		h1_b.SetFillColorAlpha(histcolors_23L[ib], 1)
		h1_b.SetLineWidth(1)
		h1_b.SetMarkerColor(histcolors_23L[ib])
		h1_b.SetMarkerSize(0)
		stack_b_23L.Add(h1_b)


	hists_sig_23L = []
	for isig in range(0, nS_23L):
		h1_s = r.TH1F("h1_23L_s"+str(isig), "h1_23L_s"+str(isig), nCh_23L, 0, nCh_23L)
		for idx in range(1,nCh_23L+1):
			h1_s.SetBinContent(idx, sigs_23L[idx-1][isig])
			h1_s.SetBinError(idx, esigs_23L[idx-1][isig])
		h1_s.SetFillColor(0)
		h1_s.SetLineColor(signalcolors[isig])
		h1_s.SetLineWidth(2)
		h1_s.SetMarkerColor(signalcolors[isig])
		h1_s.SetMarkerSize(0)
		stack_b_23L.Add(h1_s)
		hists_sig_23L.append(h1_s)

	stack_b_23L.SetMaximum(maxY)

	stack_b_23L.SetTitle("")
	stack_b_23L.Draw("hist")
	stack_b_23L.GetXaxis().SetLimits(0,nCh_total+2)
	stack_b_23L.GetYaxis().SetTitleOffset(0.52)
	stack_b_23L.GetYaxis().SetTitleSize(0.08)
	stack_b_23L.GetYaxis().SetLabelSize(0.05)
	stack_b_23L.GetYaxis().SetTitle("Events")
	stack_b_23L.GetYaxis().SetTickLength(0.01)
	stack_b_23L.GetXaxis().SetTickLength(0.00)
	stack_b_23L.GetYaxis().ChangeLabel(1, -1, -1, 31, -1, -1, "0")

	h1_obs_23L = r.TH1F("h1_23L_obs", "h1_23L_obs", nCh_23L, 0, nCh_23L)
	for idx in range(1,nCh_23L+1):
		h1_obs_23L.SetBinContent(idx, obs_23L[idx-1])
		h1_obs_23L.SetBinError(idx, math.sqrt(obs_23L[idx-1]))
	#h1_obs_23L.SetBinErrorOption(1)
	h1_obs_23L.SetLineColor(1)
	h1_obs_23L.SetMarkerColor(1)
	h1_obs_23L.SetMarkerStyle(20)
	h1_obs_23L.SetLineWidth(2)
	h1_obs_23L.Draw("samePEX0")
	#total bkg unc
	box = r.TBox(0,0,1,1,)
	box.SetFillStyle(3001)
	box.SetLineWidth(0)
	box.SetFillColor(r.kBlack)

	for idx in range(1,nCh_23L+1):
		NB = bkgs_23L[idx-1][nB_23L]
		eNB = ebkgs_23L[idx-1][nB_23L]
		box.DrawBox(idx-1, NB-0.5*eNB, idx, NB+0.5*eNB)

	legend_23L = r.TLegend(0.135,0.6,0.555,0.88)
	legend_23L.SetFillStyle(0)
	legend_23L.SetBorderSize(0)
	legend_23L.SetTextFont(42)
	legend_23L.SetNColumns(3)
	for ib in range(0, nB_23L):
		legend_23L.AddEntry("h1_23L_b"+str(nB_23L-ib-1), bkgs_names[nB_23L-ib-1], "F")
	for isig in range(0, nS_23L):
		legend_23L.AddEntry("h1_23L_s"+str(isig), sigs_names_23L[isig], "L")
	legend_23L.AddEntry(box, "Total uncertainty", "F")
	legend_23L.AddEntry("h1_23L_obs", "Observed", "ep")
	legend_23L.Draw()

	pad2.cd()
	ratio_23L = r.TH1F("h_ratio_23L","h_ratio_23L", nCh_total+2, 0, nCh_total+2)
	for idx in range(1,nCh_23L+1):
		s = sigs_23L[idx-1][nS_23L]
		b = bkgs_23L[idx-1][nB_23L]
		L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
		ratio_23L.SetBinContent(idx, L)
		#print(str(idx)+", "+str(s)+", "+str(b)+", "+str(L))
	ratio_23L.SetLineColor(r.kBlack)
	ratio_23L.SetLineWidth(2)
	ratio_23L.SetTitle("")
	ratio_23L.GetYaxis().SetTitle("L (#sigma)")

	#ratio_23L.GetXaxis().SetTitle("Bin #")
	for idx in range(1, nCh_total+3):
		ratio_23L.GetXaxis().SetBinLabel(idx, xlabels[idx-1])
	ratio_23L.LabelsOption("v")
	ratio_23L.GetYaxis().SetRangeUser(0.0,maxSig)
	ratio_23L.GetXaxis().SetTitleOffset(0.94)
	ratio_23L.GetXaxis().SetTitleSize(0.18)
	ratio_23L.GetXaxis().SetLabelSize(0.12)
	ratio_23L.GetXaxis().SetLabelOffset(0.013)
	ratio_23L.GetYaxis().SetTitleOffset(0.22)
	ratio_23L.GetYaxis().SetTitleSize(0.17)
	ratio_23L.GetYaxis().SetLabelSize(0.13)
	ratio_23L.GetYaxis().SetTickLength(0.01)
	ratio_23L.GetYaxis().SetNdivisions(505)
	ratio_23L.Draw("hist")


	##################4L part############
	nS_4L = 5
	nB_4L = 6
	sigs_4L = np.zeros((nCh_4L, nS_4L+1))
	esigs_4L = np.zeros((nCh_4L, nS_4L+1))
	sigs_names_4L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
	bkgs_4L = np.zeros((nCh_4L, nB_4L+1))
	ebkgs_4L = np.zeros((nCh_4L, nB_4L+1))
	bkgs_names = ["ZZ", "t#bar{t}Z", "tWZ", "WZ", "Higgs", "Other", "B"]
	L_4L = [] #L=s/sqrt(B)
	obs_4L = np.zeros(nCh_4L)

	idx_channel = 0
	inputFileName_4L = "../../tables/WVZMVA_v0.1.21/v9/result_detail_year_all.tex"
	if isBDT:
		inputFileName_4L = "../../tables/WVZMVA_v0.1.21/v9/result_bdt_detail_year_all.tex"
	with open(inputFileName_4L, "r") as yield_file:
		for this_line in yield_file:
			line_array = shlex.split(this_line)
			if len(line_array)<1 or line_array[0]!= "~~~~~~Bin":
				continue
			obs_4L[idx_channel] = float(line_array[4*0+3])
			for idx in range(6):
				bkgs_4L[idx_channel][idx] = float(line_array[4*(idx+8)+3])
				ebkgs_4L[idx_channel][idx] = float(line_array[4*(idx+8)+5])
			bkgs_4L[idx_channel][6] = float(line_array[4*1+3])
			ebkgs_4L[idx_channel][6] = float(line_array[4*1+5])

			sigs_4L[idx_channel][1] = float(line_array[4*2+3])
			esigs_4L[idx_channel][1] = float(line_array[4*2+5])
			sigs_4L[idx_channel][2] = float(line_array[4*4+3])
			esigs_4L[idx_channel][2] = float(line_array[4*4+5])
			sigs_4L[idx_channel][3] = float(line_array[4*6+3])
			esigs_4L[idx_channel][3] = float(line_array[4*6+5])
			VH = np.zeros(3)
			eVH = np.zeros(3)
			for idx in range(3):
				VH[idx] = float(line_array[4*(idx*2+3)+3]) 
				eVH[idx] = float(line_array[4*(idx*2+3)+5]) 
			sigs_4L[idx_channel][4] = sum(VH[i] for i in range(3))
			esigs_4L[idx_channel][4] = math.sqrt(sum(eVH[i]*eVH[i] for i in range(3)))
			sigs_4L[idx_channel][5] = sum(sigs_4L[idx_channel][i] for i in range(5))
			esigs_4L[idx_channel][5] = math.sqrt(sum(esigs_4L[idx_channel][i]*esigs_4L[idx_channel][i] for i in range(5)))

			idx_channel += 1

	#add up bkgs/sigs
	for ich in range(0, nCh_4L):
		sigs_4L[ich][nS_4L] = sum(sigs_4L[ich][i] for i in range(nS_4L))
		esigs_4L[ich][nS_4L] = math.sqrt(sum(esigs_4L[ich][i]*esigs_4L[ich][i] for i in range(nS_4L)))
		bkgs_4L[ich][nB_4L] = sum(bkgs_4L[ich][i] for i in range(nB_4L))
		ebkgs_4L[ich][nB_4L] = math.sqrt(sum(ebkgs_4L[ich][i]*ebkgs_4L[ich][i] for i in range(nB_4L)))

	#print(sigs_4L)
	#print(esigs_4L)
	#print(bkgs_4L)
	#print(ebkgs_4L)
	########################plot#####################

	multiply_4L = 10.0
	if isBDT:
		multiply_4L = 1.0
	pad1.cd()
	stack_b_4L = r.THStack("s_b_4L","s_b_4L")
	#histcolors_23L = [920, 2007, 2005, 2003, 2001, 2011]
	#histcolors_4L = [2001, 2005, 2007, 2003, 2011, 920, 2012, 2011, 2002]
	histcolors_4L =[593, 798, 871, 802, 418, 921]
	hists_b_4L = []
	for ib in range(0, nB_4L):
		h1_b = r.TH1F("h1_4L_b"+str(ib), "h1_4L_b"+str(ib), nCh_4L, nCh_23L+1, nCh_23L+nCh_4L+1)
		for idx in range(1,nCh_4L+1):
			h1_b.SetBinContent(idx, multiply_4L*bkgs_4L[idx-1][ib])
			h1_b.SetBinError(idx, multiply_4L*ebkgs_4L[idx-1][ib])
		h1_b.SetLineColor(histcolors_4L[ib])
		h1_b.SetFillColorAlpha(histcolors_4L[ib], 1)
		h1_b.SetLineWidth(1)
		h1_b.SetMarkerColor(histcolors_4L[ib])
		h1_b.SetMarkerSize(0)
		hists_b_4L.append(h1_b)

	#bkgs_names = ["ZZ", "t#bar{t}Z", "tWZ", "WZ", "Higgs", "Other", "B"]
	stack_b_4L.Add(hists_b_4L[3])
	stack_b_4L.Add(hists_b_4L[2])
	stack_b_4L.Add(hists_b_4L[5])
	stack_b_4L.Add(hists_b_4L[4])
	stack_b_4L.Add(hists_b_4L[1])
	stack_b_4L.Add(hists_b_4L[0])


	hists_sig_4L = []
	for isig in range(0, nS_4L):
		h1_s = r.TH1F("h1_4L_s"+str(isig), "h1_4L_s"+str(isig), nCh_4L, nCh_23L+1, nCh_23L+nCh_4L+1)
		for idx in range(1,nCh_4L+1):
			h1_s.SetBinContent(idx, multiply_4L*sigs_4L[idx-1][isig])
			h1_s.SetBinError(idx, multiply_4L*esigs_4L[idx-1][isig])
		h1_s.SetFillColor(0)
		h1_s.SetLineColor(signalcolors[isig])
		h1_s.SetLineWidth(2)
		h1_s.SetMarkerSize(0)
		h1_s.SetMarkerColor(signalcolors[isig])
		stack_b_4L.Add(h1_s)
		hists_sig_4L.append(h1_s)

	stack_b_4L.SetTitle("")
	stack_b_4L.Draw("histsame")

	h1_obs_4L = r.TH1F("h1_4L_obs", "h1_4L_obs", nCh_4L, nCh_23L+1, nCh_23L+nCh_4L+1)
	for idx in range(1,nCh_4L+1):
		h1_obs_4L.SetBinContent(idx, multiply_4L*obs_4L[idx-1])
		h1_obs_4L.SetBinError(idx, multiply_4L*math.sqrt(obs_4L[idx-1]))
	#h1_obs_4L.SetBinErrorOption(1)
	h1_obs_4L.SetLineColor(1)
	h1_obs_4L.SetMarkerColor(1)
	h1_obs_4L.SetMarkerStyle(20)
	h1_obs_4L.SetLineWidth(2)
	h1_obs_4L.Draw("samePEX0")

	for idx in range(1,nCh_4L+1):
		NB = multiply_4L*bkgs_4L[idx-1][nB_4L]
		eNB = multiply_4L*ebkgs_4L[idx-1][nB_4L]
		box.DrawBox(nCh_23L+idx-1+1, NB-0.5*eNB, nCh_23L+idx+1, NB+0.5*eNB)

	legend_4L = r.TLegend(0.61,0.45,0.76,0.88)
	legend_4L.SetFillStyle(0)
	legend_4L.SetBorderSize(0)
	legend_4L.SetTextFont(42)
	legend_4L.SetNColumns(2)
	for ib in [0,1,4,5,2,3]:
		legend_4L.AddEntry("h1_4L_b"+str(ib), bkgs_names[ib], "F")
	for isig in range(0, nS_4L):
		legend_4L.AddEntry("h1_4L_s"+str(isig), sigs_names_4L[isig], "L")

	legend_4L.Draw()

	pad2.cd()
	ratio_4L = r.TH1F("h_ratio_4L","h_ratio_4L", nCh_total+2, 0, nCh_total+2)
	for idx in range(1,nCh_4L+1):
		s = sigs_4L[idx-1][nS_4L]
		b = bkgs_4L[idx-1][nB_4L]
		L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
		ratio_4L.SetBinContent(idx+nCh_23L+1, L)
	ratio_4L.SetLineColor(r.kBlack)
	ratio_4L.SetLineWidth(2)
	ratio_4L.Draw("histsame")

	########################5/6L part######################
	#2 channels
	nS_56L = 5
	nB_56L = 2
	sigs_56L = np.zeros((nCh_56L, nS_56L+1))
	esigs_56L = np.zeros((nCh_56L, nS_56L+1))
	sigs_names_56L = ["WWW", "WWZ", "WZZ", "ZZZ", "VH", "S"]
	bkgs_56L = np.zeros((nCh_56L, nB_56L+1))
	ebkgs_56L = np.zeros((nCh_56L, nB_56L+1))
	bkgs_names = ["ZZ","Other", "B"]
	L_56L = [] #L=s/sqrt(B)
	obs_56L = np.zeros(nCh_56L)
	obs_56L[0] = 3.0

	sigs_lineNums_5L = [-1, -1, 20, 21, 22, -1]
	bkgs_lineNums_5L = [14, -1, -1]
	otherbkgs_lineNums_5L = [9,10,11,12,13,15,16,17,18]
	with open("../../tables/5L_yield.tex", "r") as yield_file:
		lineNum = 0
		for this_line in yield_file:
			lineNum += 1
			this_line = this_line.replace("\\","")
			line_array = shlex.split(this_line)
			if lineNum not in sigs_lineNums_5L and lineNum not in bkgs_lineNums_5L and lineNum not in otherbkgs_lineNums_5L:
				continue
			elif lineNum in sigs_lineNums_5L:
				idx = sigs_lineNums_5L.index(lineNum)
				sigs_56L[0][idx] = float(line_array[3])
				esigs_56L[0][idx] = float(line_array[5])
			elif lineNum in bkgs_lineNums_5L:
				idx = bkgs_lineNums_5L.index(lineNum)
				bkgs_56L[0][idx] = float(line_array[2])
				ebkgs_56L[0][idx] = float(line_array[4])
			elif lineNum in otherbkgs_lineNums_5L:
				bkgs_56L[0][1] += float(line_array[2])
				ebkgs_56L[0][1] = math.sqrt(ebkgs_56L[0][1]*ebkgs_56L[0][1] + float(line_array[4])*float(line_array[4]))


	sigs_lineNums_6L = [-1, -1, 19, 20, 21, -1]
	bkgs_lineNums_6L = [13, -1, -1]
	otherbkgs_lineNums_6L = [9,10,11,12,14,15,16,17]
	with open("../../tables/6L_yield.tex", "r") as yield_file:
		lineNum = 0
		for this_line in yield_file:
			lineNum += 1
			this_line = this_line.replace("\\","")
			line_array = shlex.split(this_line)
			if lineNum not in sigs_lineNums_6L and lineNum not in bkgs_lineNums_6L and lineNum not in otherbkgs_lineNums_6L:
				continue
			elif lineNum in sigs_lineNums_6L:
				idx = sigs_lineNums_6L.index(lineNum)
				sigs_56L[1][idx] = float(line_array[3])
				esigs_56L[1][idx] = float(line_array[5])
			elif lineNum in bkgs_lineNums_6L:
				idx = bkgs_lineNums_6L.index(lineNum)
				bkgs_56L[1][idx] = float(line_array[2])
				ebkgs_56L[1][idx] = float(line_array[4])
			elif lineNum in otherbkgs_lineNums_6L:
				bkgs_56L[1][1] += float(line_array[2])
				ebkgs_56L[1][1] = math.sqrt(ebkgs_56L[1][1]*ebkgs_56L[1][1] + float(line_array[4])*float(line_array[4]))

	#add up bkgs/sigs
	for ich in range(0, nCh_56L):
		sigs_56L[ich][nS_56L] = sum(sigs_56L[ich][i] for i in range(nS_56L))
		esigs_56L[ich][nS_56L] = math.sqrt(sum(esigs_56L[ich][i]*esigs_56L[ich][i] for i in range(nS_56L)))
		bkgs_56L[ich][nB_56L] = sum(bkgs_56L[ich][i] for i in range(nB_56L))
		ebkgs_56L[ich][nB_56L] = math.sqrt(sum(ebkgs_56L[ich][i]*ebkgs_56L[ich][i] for i in range(nB_56L)))

	#print(sigs_56L)
	#print(esigs_56L)
	#print(bkgs_56L)
	#print(ebkgs_56L)

	#####################plot#####################

	multiply_56L = 20.0
	if isBDT:
		multiply_56L = 10.0
	pad1.cd()
	stack_b_56L = r.THStack("s_b_56L","s_b_56L")
	histcolors_56L = [histcolors_4L[0], histcolors_4L[5]]
	hists_b_56L = []
	for ib in range(0, nB_56L):
		h1_b = r.TH1F("h1_56L_b"+str(ib), "h1_56L_b"+str(ib), nCh_56L, nCh_23L+nCh_4L+2, nCh_23L+nCh_4L+nCh_56L+2)
		for idx in range(1,nCh_56L+1):
			h1_b.SetBinContent(idx, multiply_56L*bkgs_56L[idx-1][ib])
			h1_b.SetBinError(idx, multiply_56L*ebkgs_56L[idx-1][ib])
		h1_b.SetLineColor(histcolors_56L[ib])
		h1_b.SetFillColorAlpha(histcolors_56L[ib], 1)
		h1_b.SetLineWidth(1)
		h1_b.SetMarkerColor(histcolors_56L[ib])
		h1_b.SetMarkerSize(0)
		hists_b_56L.append(h1_b)
	stack_b_56L.Add(hists_b_56L[1])
	stack_b_56L.Add(hists_b_56L[0])


	hists_sig_56L = []
	for isig in range(0, nS_56L):
		h1_s = r.TH1F("h1_56L_s"+str(isig), "h1_56L_s"+str(isig), nCh_56L, nCh_23L+nCh_4L+2, nCh_23L+nCh_4L+nCh_56L+2)
		for idx in range(1,nCh_56L+1):
			h1_s.SetBinContent(idx, multiply_56L*sigs_56L[idx-1][isig])
			h1_s.SetBinError(idx, multiply_56L*esigs_56L[idx-1][isig])
		h1_s.SetFillColor(0)
		h1_s.SetLineColor(signalcolors[isig])
		h1_s.SetLineWidth(2)
		h1_s.SetMarkerColor(signalcolors[isig])
		h1_s.SetMarkerSize(0)
		stack_b_56L.Add(h1_s)
		hists_sig_56L.append(h1_s)


	stack_b_56L.SetTitle("")
	stack_b_56L.Draw("histsame")

	h1_obs_56L = r.TH1F("h1_56L_obs", "h1_56L_obs", nCh_56L, nCh_23L+nCh_4L+2, nCh_23L+nCh_4L+nCh_56L+2)
	for idx in range(1,nCh_56L+1):
		h1_obs_56L.SetBinContent(idx, multiply_56L*obs_56L[idx-1])
		h1_obs_56L.SetBinError(idx, multiply_56L*math.sqrt(obs_56L[idx-1]))
	h1_obs_56L.SetLineColor(1)
	h1_obs_56L.SetMarkerColor(1)
	h1_obs_56L.SetMarkerStyle(20)
	h1_obs_56L.SetLineWidth(2)
	h1_obs_56L.Draw("samePEX0")

	for idx in range(1,nCh_56L+1):
		NB = multiply_56L*bkgs_56L[idx-1][nB_56L]
		eNB = multiply_56L*ebkgs_56L[idx-1][nB_56L]
		box.DrawBox(nCh_23L+nCh_4L+idx-1+2, NB-0.5*eNB, nCh_23L+nCh_4L+idx+2, NB+0.5*eNB)

	legend_56L = r.TLegend(0.89,0.45,0.955,0.88)
	legend_56L.SetFillStyle(0)
	legend_56L.SetBorderSize(0)
	legend_56L.SetTextFont(42)
	legend_56L.SetNColumns(1)
	for ib in range(0, nB_56L):
		legend_56L.AddEntry("h1_56L_b"+str(ib), bkgs_names[ib], "F")
	for isig in range(0, nS_56L):
		legend_56L.AddEntry("h1_56L_s"+str(isig), sigs_names_56L[isig], "L")

	legend_56L.Draw()

	pad2.cd()
	ratio_56L = r.TH1F("h_ratio_56L","h_ratio_56L", nCh_total+2, 0, nCh_total+2)
	for idx in range(1,nCh_56L+1):
		s = sigs_56L[idx-1][nS_56L]
		b = bkgs_56L[idx-1][nB_56L]
		L = math.sqrt(2.0*((s+b)*math.log(1+s/b) - s))
		ratio_56L.SetBinContent(idx+nCh_23L+nCh_4L+2, L)
	ratio_56L.SetLineColor(r.kBlack)
	ratio_56L.SetLineWidth(2)
	ratio_56L.Draw("histsame")

	#############draw vertical lines between SS/3L, 4L, 5/6L
	pad1.cd()

	a1 = r.TGaxis(13.0, 0.0, 13.0, maxY*1.05, 0.0, maxY*1.05/multiply_4L, 510, "S")
	a1.SetLabelSize(0.045)
	a1.SetTickSize(0.01)
	a1.SetTextSize(0.6)
	a1.SetLabelFont(42)
	a1.ChangeLabel(1, -1, -1, 31, -1, -1, "0")
	a1.Draw("same")

	a2 = r.TGaxis(21.0, 0.0, 21.0, maxY*1.05, 0.0, maxY*1.05/multiply_56L, 510, "S")
	a2.SetLabelSize(0.045)
	a2.SetTickSize(0.01)
	a2.SetTextSize(0.6)
	a2.SetLabelFont(42)
	a2.ChangeLabel(1, -1, -1, 31, -1, -1, "0")
	a2.Draw("same")

	pad2.cd()
	
	a3 = r.TGaxis(13.0, 0.0, 13.0, maxSig, 0.0, maxSig, 505, "S")
	a3.SetLabelSize(0.0)
	a3.SetTickSize(0.01)
	a3.Draw("same")
	a4 = r.TGaxis(21.0, 0.0, 21.0, maxSig, 0.0, maxSig, 505, "S")
	a4.SetLabelSize(0.0)
	a4.SetTickSize(0.01)
	a4.Draw("same")


	line3 = r.TLine(13.0,-3,13.0,0.0)
	line3.SetLineStyle(7)
	line3.Draw("same")
	line4 = r.TLine(21.0,-3,21.0,0.0)
	line4.SetLineStyle(7)
	line4.Draw("same")
	##########draw CMS preliminary
	pad1.cd()
	tex1 = r.TLatex(0.12, 0.91, "CMS")
	tex1.SetNDC()
	tex1.SetTextFont(61)
	tex1.SetTextSize(0.070)
	tex1.SetLineWidth(2)
	tex1.Draw()
	tex2 = r.TLatex(0.19,0.912,"Preliminary")
	tex2.SetNDC()
	tex2.SetTextFont(52)
	tex2.SetTextSize(0.055)
	tex2.SetLineWidth(2)
	tex2.Draw()

	tex3 = r.TLatex(0.794,0.912,"137 fb^{-1} (13 TeV)")
	tex3.SetNDC()
	tex3.SetTextFont(42)
	tex3.SetTextSize(0.055)
	tex3.SetLineWidth(2)
	tex3.Draw()

	fileName="yield"
	if isBDT:
		fileName="yield_BDT"
	myC.SaveAs(fileName+".pdf")
	myC.SaveAs(fileName+".png")
