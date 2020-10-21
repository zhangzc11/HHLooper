conda uninstall cfitsio
conda uninstall curl
conda uninstall krb5
conda install -c conda-forge krb5=1.16.3
conda install -c conda-forge curl=7.64.1
conda install -c conda-forge cfitsio=3.470
conda install -c conda-forge root=6.18.00
pip install root_pandas
conda install -c conda-forge xgboost
pip install matplotlib
pip install uproot
conda install -c conda-forge tensorflow
conda install -c conda-forge keras
pip instal graphviz

#Below is for macOS
conda create -c conda-forge --name train_xgboost_5 root xgboost matplotlib pandas uproot graphviz root_pandas
conda activate train_xgboost_5
