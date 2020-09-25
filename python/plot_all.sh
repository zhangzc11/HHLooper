
TAG=$1

for region in \
SRBin1 \
SRBin2 \
SRBin3 \
SRBin4 
do
    python plot.py -i ../hists/${TAG}/combine/ -s 10 -w ${region} -n 40
done
