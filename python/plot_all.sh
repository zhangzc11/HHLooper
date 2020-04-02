
TAG=$1 

for region in \
CutWeight \
TwoFatJets \
SR1FatJetsSDMassCut \
SR2FatJetsSDMassCut \
SR3FatJetsSDMassCut 
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region} -n 40
done

for region in \
SideBandSR1J1MassFatJetsSDMassCut \
SideBandSR1J2MassFatJetsSDMassCut \
SideBandSR2J1MassFatJetsSDMassCut \
SideBandSR2J2MassFatJetsSDMassCut \
SideBandSR3J1MassFatJetsSDMassCut \
SideBandSR3J2MassFatJetsSDMassCut 
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region} -d -n 40
done
