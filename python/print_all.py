import ROOT as r
import sys

if __name__ == "__main__":
	inputDir = sys.argv[1]
	for region in ["SR1", "SR2", "SR3"]:
		f_sig = r.TFile(inputDir+"/bbbb.root")
		f_qcd = r.TFile(inputDir+"/qcd.root")
		f_data = r.TFile(inputDir+"/data.root")
		SR=region+"FatJetsSDMassCut__yield"
		sideband="SideBand"+region+"J1MassFatJetsSDMassCut__yield"
		h_sig_SR = f_sig.Get(SR)
		h_qcd_SR = f_qcd.Get(SR)
		h_qcd_sideband = f_qcd.Get(sideband)
		h_data_sideband = f_data.Get(sideband)
		print("signal,  "+region+", "+str(h_sig_SR.Integral()))
		print("qcd,  "+region+", (before scale) "+str(h_qcd_SR.Integral()))
		print("qcd,  "+region+", (after scale) "+str(h_qcd_SR.Integral() * h_data_sideband.Integral() / h_qcd_sideband.Integral() ))
		print("qcd,  "+region+", (scale) "+str(h_data_sideband.Integral() / h_qcd_sideband.Integral() ))
	
	for ifile in ["bbbb.root", "qcd.root", "data.root"]:
		fin = r.TFile(inputDir+"/"+ifile)
		for ih in ["M1", "N1", "M2", "N2", "D", "E"]:
			h1 = fin.Get("ControlRegion"+ih+"__yield")
			print(ifile+", "+ih+", "+str(h1.Integral()))
