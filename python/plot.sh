
outDir=/project/projectdirs/atlas/www/zhicaiz/HH/HHLooper/

for region in CutWeight CutPhPtOverMgg CutMgg CutNbVeto PhoID HPeak
do
    python plot.py -i ../hists/20210727v0/all/ -n 30 -w $region -s 100 -o $outDir
done

