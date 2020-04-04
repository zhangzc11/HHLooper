
TAG=$1

rm hists/${TAG}/*.root

inputBase=/eos/cms/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/


 (set -x ;./HHLooper ${inputBase}data/ data.root ${TAG} 1 1 >&1) &
 (set -x ;./HHLooper ${inputBase}qcd/  qcd.root ${TAG} 0 1 >&1) &
 (set -x ;./HHLooper ${inputBase}bbbb/ bbbb.root ${TAG} 0 1 >&1) &


