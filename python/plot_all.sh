
TAG=$1


for region in \
FitCR1  \
FitCR2  \
FailFitCR1  \
FailFitCR2  \
FailSR  
do
    python plot.py -i ../hists/${TAG}/combine/ -w ${region} -n 20 -d
done

for region in \
SRBin1 \
SRBin2 \
SRBin3 \
SRBin4 
do
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region} -n 20
done

