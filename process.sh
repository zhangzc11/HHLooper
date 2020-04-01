
TAG=$1

rm hists/${TAG}/*.root

./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1.0/data/ data.root ${TAG} 1
./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1.0/qcd/ qcd.root ${TAG} 0
./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1.0/bbbb/ bbbb.root ${TAG} 0

