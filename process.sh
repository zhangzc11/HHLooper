
TAG=$1

GNNtag=$2

mkdir -p hists/${TAG}/
rm -rf hists/${TAG}/*

inputBase=/global/projecta/projectdirs/atlas/zhicaiz/HH/samples/Ntuple_h026_0630


for year in 16a 16d 16e
do
 (set -x ;./HHLooper "${inputBase}/DiHiggs/input_final_mc${year}*${GNNtag}.root" HH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_ggH*${GNNtag}.root" ggH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_VBFH*${GNNtag}.root" VBFH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_WmH*${GNNtag}.root" WmH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_WpH*${GNNtag}.root" WpH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_ZH*${GNNtag}.root" qqZH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_ggZH*${GNNtag}.root" ggZH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_ttH*${GNNtag}.root" ttH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_bbH*${GNNtag}.root" bbH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_tWH*${GNNtag}.root" tWH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper "${inputBase}/Higgs/mc${year}/Higgs/root/*_tHjb*${GNNtag}.root" tHjb.root ${TAG} 0 >&1) &
done

for year in 16 17 18
do
 (set -x ;./HHLooper "${inputBase}/data${year}/data/data${year}/root/*${GNNtag}.root" cont.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper "${inputBase}/data${year}/data/data${year}/root/*${GNNtag}.root" data.root ${TAG} 1 >&1) &
done

sleep 1
wait

mkdir -p hists/${TAG}/all/


for year in 2016 2017 2018
do
    hadd -k -f hists/${TAG}/${year}/WH.root hists/${TAG}/${year}/WmH.root hists/${TAG}/${year}/WpH.root
    hadd -k -f hists/${TAG}/${year}/ZH.root hists/${TAG}/${year}/qqZH.root hists/${TAG}/${year}/ggZH.root
    hadd -k -f hists/${TAG}/${year}/VH.root hists/${TAG}/${year}/ZH.root hists/${TAG}/${year}/WH.root
    hadd -k -f hists/${TAG}/${year}/otherH.root hists/${TAG}/${year}/bbH.root hists/${TAG}/${year}/tWH.root hists/${TAG}/${year}/tHjb.root
    hadd -k -f hists/${TAG}/${year}/Higgs.root hists/${TAG}/${year}/VH.root hists/${TAG}/${year}/ggH.root hists/${TAG}/${year}/VBFH.root hists/${TAG}/${year}/ttH.root hists/${TAG}/${year}/otherH.root
done

for proc in HH cont data WH ZH VH otherH Higgs ggH VBFH WmH WpH qqZH ggZH ttH bbH tWH tHjb 
do
    hadd -k -f hists/${TAG}/all/${proc}.root hists/${TAG}/2016/${proc}.root hists/${TAG}/2017/${proc}.root hists/${TAG}/2018/${proc}.root
done



