import ROOT as r
import sys

if __name__ == "__main__":
	inputDir = sys.argv[1]
	
	for ifile in ["bbbb.root", "qcd.root", "data.root"]:
		fin = r.TFile(inputDir+"/"+ifile)
		events = []
		regions = ["SRBDT", "FailMassPassBDT", "PassMassFailBDT", "FailMassFailBDT"]
		region_names = ["A", "B", "C", "D"]
		for ih in range(len(regions)):
			h1 = fin.Get(regions[ih]+"Selection__yield")
			events.append(h1.Integral())
			if not (ih==0 and ifile == "data.root"):
				print(ifile+", "+region_names[ih]+", "+str(h1.Integral()))
		print(ifile+", predicted A = B*C/D = "+str(events[1]*events[2]/events[3]))
