1
#!/usr/bin/env bash

#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2018/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2018/ ; do

for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2016/ ; do

#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2018/ ; do

    
    #for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/2018/ ; do
#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined/testing/2018/ ; do
    
#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option10/combined/Tau32TopSkim/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option10/combined/Tau32TopSkim/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option10/combined/Tau32TopSkim/2018/ ; do

#for input_dir in /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined_NoRandomNumbers/2016/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined_NoRandomNumbers/2017/ /Users/sixie/HH/HHLooper/python/xgboost/data/option5/combined_NoRandomNumbers/2018/  ; do



    echo "input_dir = ${input_dir}"

    #input_files=${input_dir}/*_BDTs_BDTs.root
    input_files=${input_dir}/*.root

    for _file in ${input_files}; do
	echo ${_file}
	file_name=${_file%.root}
	echo ${file_name}

	
	#cp ${file_name}".root" ${file_name}"_BDTs.root"
	#file_name=${file_name}"_BDTs.root"

	inputfilename=${file_name}".root"
	outputfilename=${file_name}"_BDTs.root"
	
	#loop over different options
	year=(Run2)
	bkg_type=(qcd_and_ttbar)
	#bdt_type=(basic0 basic1 basic2 enhanced)
	bdt_type=( enhanced_v8p2 )	

	for _year in ${year[@]};do
	    for _bkg_type in ${bkg_type[@]}; do
		for _bdt_type in ${bdt_type[@]}; do
		    echo "${inputfilename} ${outputfilename} ${_year} ${_bkg_type} ${_bdt_type}"
		    python append_xgboost_discriminator_to_tree_withSystematics.py ${inputfilename} ${outputfilename} ${_year} ${_bkg_type} ${_bdt_type}

		done 
	    done
	done
    done
done
