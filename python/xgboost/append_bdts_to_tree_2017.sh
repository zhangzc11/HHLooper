
#!/usr/bin/env bash

input_dir=/Users/cmorgoth/git/HHLooper/python/xgboost/data/v11/combined/2017/
input_files=${input_dir}/JetHT*.root

for _file in ${input_files}; do
  echo ${_file}
  file_name=${_file%.root}
  echo ${file_name}
  cp ${file_name}".root" ${file_name}"_BDTs.root"
  file_name=${file_name}"_BDTs.root"
  #loop over different options
  year=(2017)
  bkg_type=(qcd ttbar qcd_and_ttbar)
  #bkg_type=(qcd_and_ttbar)
  #bdt_type=(basic0 basic1 basic2 enhanced)
  bdt_type=(basic0 basic1 basic2 enhanced enhanced_v2)

  for _year in ${year[@]};do
    for _bkg_type in ${bkg_type[@]}; do
      for _bdt_type in ${bdt_type[@]}; do
        echo ${_year}" "${_bkg_type}" "${_bdt_type}
        python append_xgboost_discriminator_to_tree.py ${input_dir} ${file_name} ${_year} ${_bkg_type} ${_bdt_type}
      done
    done
  done

done

# input_dir=/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/
# file_name=GluGluToHHTo4B_node_cHHH1_TuneCP5_PSWeights_13TeV-powheg-pythia8_1pb_weighted_Mass30Skim.root
# file_name=${file_name%.root}
# cp ${input_dir}/${file_name}".root" ${input_dir}/${file_name}"_BDTs.root"
# file_name=${file_name}"_BDTs.root"
#
# echo ${file_name}
# year=(2017)
# bkg_type=(qcd ttbar)
# bdt_type=(basic0 basic1 basic2 enhanced)
#
# for _year in ${year[@]};do
#   for _bkg_type in ${bkg_type[@]}; do
#     for _bdt_type in ${bdt_type[@]}; do
#       echo ${_year}" "${_bkg_type}" "${_bdt_type}
#       python append_xgboost_discriminator_to_tree.py ${input_dir} ${file_name} ${_year} ${_bkg_type} ${_bdt_type}
#     done
#   done
# done
