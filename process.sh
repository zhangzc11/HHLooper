
TAG=$1

GNNtag=$2

mkdir -p hists/${TAG}/
rm -rf hists/${TAG}/*

inputBase=/global/projecta/projectdirs/atlas/zhicaiz/HH/samples/Ntuple_h026_0630


for year in 16 17 18

do
 (set -x ;./HHLooper "${inputBase}/DiHiggs/input_final_mc${year}*${GNNtag}.root" HH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/data${year}/data/data${year}/root/*${GNNtag}.root" cont.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper "${inputBase}/data${year}/data/data${year}/root/*${GNNtag}.root" data.root ${TAG} 1 >&1) &
done

sleep 1
wait

mkdir -p hists/${TAG}/all/

for proc in HH cont data 
do
    hadd -k -f hists/${TAG}/all/${proc}.root hists/${TAG}/2016/${proc}.root hists/${TAG}/2017/${proc}.root hists/${TAG}/2018/${proc}.root
done



