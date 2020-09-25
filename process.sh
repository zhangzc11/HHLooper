
TAG=$1

mkdir -p hists/${TAG}/
rm -rf hists/${TAG}/*

inputBase=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HHBoost/HHTo4BNtupler_20200902_option5_combined_BDT_Jet2Xbb0p8Skim/ 
#inputBase=data/Jet2Xbb0p8Skim/


for year in 2016 2017 2018

do
 (set -x ;./HHLooper ${inputBase}/${year}/data/ data.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/qcd/  qcd.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/ttbar/ ttbar.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/HHSM/ HHSM.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/VH/ VH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/Higgs/ Higgs.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/ttH/ ttH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}/${year}/others/ others.root ${TAG} 0 >&1) &

done

sleep 1
wait

mkdir -p hists/${TAG}/combine/
hadd -k -f hists/${TAG}/combine/data.root hists/${TAG}/2016/data.root hists/${TAG}/2017/data.root hists/${TAG}/2018/data.root
hadd -k -f hists/${TAG}/combine/qcd.root hists/${TAG}/2016/qcd.root hists/${TAG}/2017/qcd.root hists/${TAG}/2018/qcd.root
hadd -k -f hists/${TAG}/combine/ttbar.root hists/${TAG}/2016/ttbar.root hists/${TAG}/2017/ttbar.root hists/${TAG}/2018/ttbar.root
hadd -k -f hists/${TAG}/combine/HHSM.root hists/${TAG}/2016/HHSM.root hists/${TAG}/2017/HHSM.root hists/${TAG}/2018/HHSM.root
hadd -k -f hists/${TAG}/combine/VH.root hists/${TAG}/2016/VH.root hists/${TAG}/2017/VH.root hists/${TAG}/2018/VH.root
hadd -k -f hists/${TAG}/combine/Higgs.root hists/${TAG}/2016/Higgs.root hists/${TAG}/2017/Higgs.root hists/${TAG}/2018/Higgs.root
hadd -k -f hists/${TAG}/combine/ttH.root hists/${TAG}/2016/ttH.root hists/${TAG}/2017/ttH.root hists/${TAG}/2018/ttH.root
hadd -k -f hists/${TAG}/combine/others.root hists/${TAG}/2016/others.root hists/${TAG}/2017/others.root hists/${TAG}/2018/others.root


hadd -k -f hists/${TAG}/combine/bkg.root hists/${TAG}/combine/qcd.root hists/${TAG}/combine/ttbar.root hists/${TAG}/combine/VH.root hists/${TAG}/combine/Higgs.root hists/${TAG}/combine/ttH.root hists/${TAG}/combine/others.root

