# HHLooper
HHLooper

# Setup

first time setup:

```
module load root python
conda create --name venv_root python=3.7
source activate venv_root
conda install numpy
git clone -b HHyyXX git@github.com:zhangzc11/HHLooper.git
cd HHLooper
make
```

every time login:

```
module load root python
source activate venv_root
```

# About  the looper:

All the selections are defined  in app/HHLooper.cc in the define cuts block

All histograms are defined in app/HHLooper.cc in the histograms block

Each output histogram will have the name of `CutName__HistogramName`, i.e. by default the program saves all histograms for all cuts


# Run looper

```
./process.sh 20210728v0 GNNv0

```

The first argument is a (random) label you set for the directory to store the output histograms
the second argument is the GNN version tag

# Make plots

```
cd python
./plot.sh ../hists/20210728v0/all/
```

The argument to this script is the directory where the histograms are stored
