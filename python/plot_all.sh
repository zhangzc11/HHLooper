
for region in \
CutWeight \
TwoFatJets \
FatJetsDDBCut \
FatJetsSDMassCut 
do
	python plot.py -i ../hists/v_1.0_0330/ -s 100 -w ${region}
done
