
outDir=/project/projectdirs/atlas/www/zhicaiz/HH/HHLooper/

for region in CutWeight CutPhPtOverMgg CutMgg CutNbVeto SREstimateFull SREstimatePeak
do
    python plot.py -i ../hists/test01/all/ -n 30 -w $region -s 100 -o $outDir
done

