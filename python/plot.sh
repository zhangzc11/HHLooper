

inputDir=$1

outDir=/project/projectdirs/atlas/www/zhicaiz/HH/HHLooper/


python plot.py -i $inputDir HPeak__gnn_score -RO  -o $outDir

for region in CutWeight CutPhPtOverMgg CutMgg CutNbVeto PhoID HPeak
do
    python plot.py -i $inputDir -n 30 -w $region -s 100 -o $outDir
done

