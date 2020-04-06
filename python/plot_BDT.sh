
TAG=$1 

python plot.py -OP -i ../hists/${TAG}/ FatJet2SDMassCut__XGBBDT -s 5000 -b 3.0
python plot.py -i ../hists/${TAG}/ FailMassPassBDTSelection__FatJet2_msoftdrop -n 40 -d
#python plot.py -i ../hists/${TAG}/ -s 5000 -w FatJet2SDMassPreSelection -n 40
#python plot.py -i ../hists/${TAG}/ -s 5000 -w BDTPreSelection -n 40
#python plot.py -i ../hists/${TAG}/ -s 5000 -w FatJet2SDMassCut -n 40
python plot.py -i ../hists/${TAG}/ -s 100 -w SRBDTSelection -n 40
python plot.py -i ../hists/${TAG}/ -w FailFatJet2SDMassCut -n 40 -d
python plot.py -i ../hists/${TAG}/ -w FailBDTSelection -n 40 -d
#python plot.py -i ../hists/${TAG}/ -w BDTNonARegion -n 40 -d
#python plot.py -i ../hists/${TAG}/ -w BDTBCDSumRegion -n 40 -d
#python plot.py -i ../hists/${TAG}/ -w FailFatJet2SDMassCut -d -n 40
#python plot.py -i ../hists/${TAG}/ -w FailMassPassBDTSelection -d -n 40
#python plot.py -i ../hists/${TAG}/ -w PassMassFailBDTSelection -d -n 40
#python plot.py -i ../hists/${TAG}/ -w FailMassFailBDTSelection -d -n 40


python plot.py -i ../hists/${TAG}/ -s 5000 -w TwoFatJets -n 40
python plot.py -i ../hists/${TAG}/ TwoFatJets__FatJet1_msoftdrop_v_FatJet2_msoftdrop
python plot.py -i ../hists/${TAG}/ FatJetsPtCutSR1__FatJet1_msoftdrop_v_FatJet2_msoftdrop

