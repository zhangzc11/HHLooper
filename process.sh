
TAG=$1

rm hists/${TAG}/*.root

inputBase=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/


 (set -x ;./HHLooper ${inputBase}data/ data.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper ${inputBase}qcd/  qcd.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}bbbb/ bbbb.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}ggH_amcnlo/ ggH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}VBFH/ VBFH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}WH/ WH.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper ${inputBase}ZH/ ZH.root ${TAG} 0 >&1) &

sleep 1
wait

hadd -k -f hists/${TAG}/singleH.root hists/${TAG}/*H.root
hadd -k -f hists/${TAG}/bkg.root hists/${TAG}/qcd.root hists/${TAG}/singleH.root

