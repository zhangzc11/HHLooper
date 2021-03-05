
#!/usr/bin/env bash

#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2018/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2018/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/training/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/training/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/training/2018/; do
for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2018/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2018/ ; do


    echo "input_dir = ${input_dir}"

    #input_files=${input_dir}/*_BDTs_BDTs.root
    input_files=${input_dir}/*.root

    for _file in ${input_files}; do
	echo ${_file}
	file_name=${_file%.root}
	echo ${file_name}

	
	cp ${file_name}".root" ${file_name}"_BDTs.root"
	file_name=${file_name}"_BDTs.root"

	
	#loop over different options
	year=(Run2)
	bkg_type=(qcd_and_ttbar)
	#bkg_type=(qcd_and_ttbar)
	#bdt_type=(basic0 basic1 basic2 enhanced)
	bdt_type=( enhanced_v8p2 enhanced_v24 )	

	for _year in ${year[@]};do
	    for _bkg_type in ${bkg_type[@]}; do
		for _bdt_type in ${bdt_type[@]}; do
		    echo ${_year}" "${_bkg_type}" "${_bdt_type}
		    python append_xgboost_discriminator_to_tree.py ${input_dir} ${file_name} ${_year} ${_bkg_type} ${_bdt_type}
		done 
	    done
	done
    done
done
