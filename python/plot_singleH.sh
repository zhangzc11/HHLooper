TAG=$1

python plot.py -i ../hists/${TAG}/ TwoFatJets__FatJet1_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ TwoFatJets__FatJet2_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ SR1FatJetsSDMassCut__FatJet1_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ SR1FatJetsSDMassCut__FatJet2_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ preNm1FatJetsPtCut__FatJet1_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ preNm1FatJetsPtCut__FatJet2_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ Nm1FatJet1SDMassLeft__FatJet1_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ Nm1FatJet2SDMassLeft__FatJet2_msoftdrop -n 40 -s 100
python plot.py -i ../hists/${TAG}/ SR1FatJetsSDMassCut__yield -n 40 -s 100
python plot.py -i ../hists/${TAG}/ SideBandSR1J1MassFatJetsSDMassCut__FatJet1_msoftdrop -n 40 -d
python plot.py -i ../hists/${TAG}/ SideBandSR1J2MassFatJetsSDMassCut__FatJet2_msoftdrop -n 40 -d


