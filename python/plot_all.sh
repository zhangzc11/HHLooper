
TAG=$1 

for region in \
CutWeight \
TwoFatJets 
do
	python plot.py -i ../hists/${TAG}/ -s 5000 -w ${region} -n 40
done


for region in \
FatJetsDDBCut1 \
FatJetsPtCutSR1 
do
	python plot.py -i ../hists/${TAG}/ -s 500 -w ${region} -n 40
done



for region in \
SR1FatJetsSDMassCut \
SR2FatJetsSDMassCut \
SR3FatJetsSDMassCut 
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region} -n 40
done

for region in \
SideBandSR1J1MassFatJetsSDMassCut \
SideBandSR2J1MassFatJetsSDMassCut \
SideBandSR3J1MassFatJetsSDMassCut 
do
	python plot.py -i ../hists/${TAG}/ -s 100 -w ${region} -d -n 40
done
