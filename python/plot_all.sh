
TAG=$1

for region in \
CutBin1 \
CutBin2 \
CutBin3 \
CutBin4 \
SRBin1 \
SRBin2 \
SRBin3 \
SRBin4 
do
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region} -n 40
done

for region in \
J2MassSideBandBin1 \
J2MassSideBandBin2 \
J2MassSideBandBin3 \
J2MassSideBandBin4 
do
    python plot.py -i ../hists/${TAG}/combine/ -w ${region} -n 40 -d
done

