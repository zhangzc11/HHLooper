# HHLooper
HHLooper

# Setup

```
module load root python
git clone -b HHyyXX git@github.com:zhangzc11/HHLooper.git
cd HHLooper
make
```

# About  the looper:

All the selections are defined  in app/HHLooper.cc in the define cuts block

All histograms are defined in app/HHLooper.cc in the histograms block

Each output histogram will have the name of `CutName__HistogramName`, i.e. by default the program saves all histograms for all cuts


# Run looper

```
./HHLooper /global/projecta/projectdirs/atlas/zhicaiz/HH/samples/Ntuple_h026_0630/DiHiggs/*GNNv0.root HH.root test01 0

```

The first argument is the input ntuple (can be a file, a directory, or an expression with star);
the second argument is the output file name;
the third argument is a tag to be added to the output file directory
the last argument is a bool for whether it's data or not (not =  MC)


