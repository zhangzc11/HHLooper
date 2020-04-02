
TAG=$1

rm hists/${TAG}/*.root

 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/data/ data.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/qcd/ qcd.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/bbbb/ bbbb.root ${TAG} 0 >&1) &

