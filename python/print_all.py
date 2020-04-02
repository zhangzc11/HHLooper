import ROOT as r
import sys

if __name__ == "__main__":
	inputDir = sys.argv[1]
	for ifile in ["bbbb.root", "qcd.root", "data.root"]:
		fin = r.TFile(inputDir+"/"+ifile)
		for ih in ["M1", "N1", "M2", "N2", "D", "E"]:
			h1 = fin.Get("ControlRegion"+ih+"__yield")
			print(ifile+", "+ih+", "+str(h1.Integral()))
