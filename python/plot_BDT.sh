
TAG=$1 

python plot.py -OP -i ../hists/${TAG}/ FatJet2SDMassCut__XGBBDT -s 5000 -b 5.0
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


python plot.py -i ../hists/${TAG}/ -s 500 -w FatJet2SDMassCut -n 40
python plot.py -i ../hists/${TAG}/ BDTTrainPreSelection__FatJet1_msoftdrop_v_FatJet2_msoftdrop
python plot.py -i ../hists/${TAG}/ FatJetsPtCutSR1__FatJet1_msoftdrop_v_FatJet2_msoftdrop


python plot.py -i ../hists/${TAG}/ -s 5000 -w TwoFatJets -n 40
python plot.py -i ../hists/${TAG}/ -s 5000 -w BDTTrainPreSelection -n 40
python plot.py -i ../hists/${TAG}/ -w FailFatJet2SDMassCut -n 40 -d
python plot.py -i ../hists/${TAG}/ -s 5000 BDTTrainPreSelection__XGBBDT -n 40
python plot.py -i ../hists/${TAG}/ -s 5000 BDTTrainPreSelection__FatJet2_msoftdrop -n 40
python plot.py -i ../hists/${TAG}/ FailFatJet2SDMassCut__XGBBDT -n 40 -d


python plot.py -i ../hists/${TAG}/ FailMassPassBDT1Selection__FatJet2_msoftdrop -n 40 -F
python plot.py -i ../hists/${TAG}/ FailMassPassBDT2Selection__FatJet2_msoftdrop -n 40 -F
python plot.py -i ../hists/${TAG}/ SideBandSR1J2MassFatJetsSDMassCut__FatJet2_msoftdrop -n 40 -F
python plot.py -i ../hists/${TAG}/ SideBandSR2J2MassFatJetsSDMassCut__FatJet2_msoftdrop -n 40 -F
python plot.py -i ../hists/${TAG}/ SideBandSR3J2MassFatJetsSDMassCut__FatJet2_msoftdrop -n 40 -F
