
TAG=$1 

for region in \
CutWeight \
TwoFatJets \
FatJetsDDBCut \
SRFatJetsSDMassCut 
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region}
done

for region in \
SideBandJ1MassFatJetsSDMassCut \
SideBandJ2MassFatJetsSDMassCut
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region} -d
done
