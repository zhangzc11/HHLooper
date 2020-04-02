
TAG=$1

rm hists/${TAG}/*.root



 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/data/ data.root ${TAG} 1 >&1) &
 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/qcd/ qcd.root ${TAG} 0 >&1) &
 (set -x ;./HHLooper /mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/bbbb/ bbbb.root ${TAG} 0 >&1) &


'''
inputBase=/mnt/hadoop/store/group/phys_susy/razor/Run2Analysis/HHBoost/ntuple_v1p0/

for process in data qcd bbbb
do
   num=0
   for ifile in `ls ${inputBase}${process}`
   do
	echo processing file ${inputBase}${process}/$ifile, save to hists/${TAG}/${process}_${num}.root
	(set -x ;./HHLooper ${inputBase}${process}/${ifile} ${process}_${num}.root ${TAG} 1 >&1) &
	num=$((num+1))
   done
done

sleep 1;

wait

echo jobs finished! now hadding...
for process in data qcd bbbb
do
   hadd -k -f hists/${TAG}/${process}.root hists/${TAG}/${process}_*.root
done
'''


