import ROOT as r
import sys

if __name__ == "__main__":
	inputDir = sys.argv[1]
	for region in ["SR1", "SR2", "SR3"]:
		f_sig = r.TFile(inputDir+"/bbbb.root")
		f_bkg = r.TFile(inputDir+"/bkg.root")
		f_data = r.TFile(inputDir+"/data.root")
		SR=region+"FatJetsSDMassCut__yield"
		sideband="SideBand"+region+"J1MassFatJetsSDMassCut__yield"
		h_sig_SR = f_sig.Get(SR)
		h_bkg_SR = f_bkg.Get(SR)
		h_bkg_sideband = f_bkg.Get(sideband)
		h_data_sideband = f_data.Get(sideband)
		print("signal,  "+region+", "+str(h_sig_SR.Integral()))
		print("bkg,  "+region+", (before scale) "+str(h_bkg_SR.Integral()))
		print("bkg,  "+region+", (after scale) "+str(h_bkg_SR.Integral() * h_data_sideband.Integral() / h_bkg_sideband.Integral() ))
		print("bkg,  "+region+", (scale) "+str(h_data_sideband.Integral() / h_bkg_sideband.Integral() ))
		print("bkg,  "+region+", sideband, "+str(h_bkg_sideband.Integral() ))
		print("data,  "+region+", sideband, "+str(h_data_sideband.Integral() ))
	
	for ifile in ["bbbb.root", "bkg.root", "data.root"]:
		fin = r.TFile(inputDir+"/"+ifile)
		events = []
		for ih in ["M1", "N1", "M2", "N2", "D", "E"]:
			h1 = fin.Get("ControlRegion"+ih+"__yield")
			events.append(h1.Integral())
			print(ifile+", "+ih+", "+str(h1.Integral()))
		if ifile == "data.root":
			TF1=events[0]/events[1]
			TF2=events[2]/events[3]
			print("bkg prediction, A = "+str(events[4]*TF1*TF2))
			print("bkg prediction, B = "+str(events[4]*TF2))
			print("bkg prediction, C = "+str(events[4]*TF1))
