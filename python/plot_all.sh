
TAG=$1


for region in \
FitCR  \
FailFitCR  \
FitCR1  \
FitCR2  \
FitCR3  \
FailFitCR1  \
FailFitCR2  \
FailFitCR3  \
FailSR  
do
    python plot.py -i ../hists/${TAG}/combine/ -w ${region} -n 20 -d
    python plot.py -i ../hists/${TAG}/combine/ -w ${region}__fatJet1MassSD -n 30 -d
    python plot.py -i ../hists/${TAG}/combine/ -w ${region}__fatJet2MassSD -n 30 -d
done

for region in \
SRBin1 \
SRBin2 \
SRBin3 \
SRBin4 
do
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region} -n 20
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region}__fatJet1MassSD -n 30
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region}__fatJet2MassSD -n 30
done

