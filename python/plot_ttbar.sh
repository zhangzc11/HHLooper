label=$1

python plot.py -i ../hists/${label}/combine/ -s 10 -w TTBarCR -n 20 -d
python plot.py -i ../hists/${label}/2016/ -s 10 -w TTBarCR -n 20 -d
python plot.py -i ../hists/${label}/2017/ -s 10 -w TTBarCR -n 20 -d
python plot.py -i ../hists/${label}/2018/ -s 10 -w TTBarCR -n 20 -d

for year in  2016 2017   2018
do
    python plot.py -i ../hists/${label}/${year}/ -s 1 TTBarCR__hh_pt  -d -O TTBarCR_hh_pt_${year}
done


