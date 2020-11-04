import ROOT  as r
import sys



if __name__ == "__main__":
    tag = sys.argv[1]

    proc  =      ["Data", "QCD", "TTJets", "H", "VH",  "ttH", "others",  "HH", "HHc0",  "HHc5", "HHc2p45"]
    proc_file  = ["data", "qcd", "ttbar", "Higgs", "VH",  "ttH", "others",  "HHc1", "HHc0",  "HHc5", "HHc2p45"]

    systs = ["BDTMassShape", "ttJetsCorr", "BDTShape"]

    outFile =  r.TFile("HHTo4BPlots_Run2.root", "recreate")

    for idx in range(len(proc)):
        inFile_this = r.TFile("../hists/"+tag+"/combine/"+proc_file[idx]+".root",  "READ")
        print("read file "+"../hists/"+tag+"/combine/"+proc_file[idx]+".root")
        for region in ["SRBin1", "SRBin2",  "SRBin3", "SRBin4", "FailSR",  "FitCR1", "FitCR2", "FailFitCR1", "FailFitCR2", "TTBarCR"]:
            inFile_this.cd()
            hist_nominal = inFile_this.Get(region+"__fatJet2MassSD")
            outBinName=region.replace("SR",  "").replace("Fail", "fail")
            hist_nominal.SetName("histJet2Mass_"+outBinName+"_"+proc[idx])

            hists_sys = []
            for sys in systs:
                hist_Up = inFile_this.Get(region+sys+"Up__fatJet2MassSD")
                hist_Up.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_"+sys+"Up")
                hists_sys.append(hist_Up)
                hist_Down = inFile_this.Get(region+sys+"Down__fatJet2MassSD")
                hist_Down.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_"+sys+"Down")
                hists_sys.append(hist_Down)

                hist_JMSUp =  inFile_this.Get(region+"__fatJet2MassSD_JMSUp")
                hist_JMSUp.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_JMSUp")
                hists_sys.append(hist_JMSUp)
                hist_JMSDown =  inFile_this.Get(region+"__fatJet2MassSD_JMSDown")
                hist_JMSDown.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_JMSDown")
                hists_sys.append(hist_JMSDown)

                hist_JMRUp =  inFile_this.Get(region+"__fatJet2MassSD_JMRUp")
                hist_JMRUp.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_JMRUp")
                hists_sys.append(hist_JMRUp)
                hist_JMRDown =  inFile_this.Get(region+"__fatJet2MassSD_JMRDown")
                hist_JMRDown.SetName("histJet2Mass_"+outBinName+"_"+proc[idx]+"_JMRDown")
                hists_sys.append(hist_JMRDown)

            outFile.cd()
            hist_nominal.Write()
            for  hist in hists_sys:
                hist.Write()

        inFile_this.Close()
    outFile.Close()

