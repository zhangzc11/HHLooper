import ROOT as r
import sys

if __name__ == "__main__":
	inputDir = sys.argv[1]
	
	for ifile in ["bbbb.root", "bkg.root", "data.root"]:
		fin = r.TFile(inputDir+"/"+ifile)
		events = []
		regions = ["SR1BDT", "SR2BDT", "FailMassPassBDT1", "FailMassPassBDT2", "PassMassFailBDT", "FailMassFailBDT"]
		region_names = ["A1", "A2", "B1", "B2", "C", "D"]
		for ih in range(len(regions)):
			h1 = fin.Get(regions[ih]+"Selection__yield")
			events.append(h1.Integral())
			if not (ih<=1 and ifile == "data.root"):
				print(ifile+", "+region_names[ih]+", "+str(h1.Integral()))
		print(ifile+", predicted A1 = B1*C/D = "+str(events[2]*events[4]/events[5]))
		print(ifile+", predicted A2 = B2*C/D = "+str(events[3]*events[4]/events[5]))
