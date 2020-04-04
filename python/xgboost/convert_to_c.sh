
mkdir -p models/cpp


for model in \
bbbb_vs_qcd

do
	python raw_to_cpp.py --xgb_dump=models/model_${model}.txt --num_classes=1 --func_name=${model}
	mv ${model}.h models/cpp/
done
