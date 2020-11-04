# HHLooper
HHLooper

# Setup

```
cmsrel CMSSW_9_4_2
cd CMSSW_9_4_2/src
cmsenv
git clone git@github.com:LPC-HH/HHLooper.git
cd HHLooper
make
```

# about  the looper:

All the selections are defined  in app/HHLooper.cc in the cutflow object

`cutflow.addCut`: start a cut
`cutflow.addCutToLastActiveCut`:  add a cut on top of the cut in the previous line
`cutflow.getCut`: get a cut in a cutflow
To define a cut  in addCut or addCutToLastActiveCut, you need to give the cutname, a lambda function for a bool return, and a weight 

For example, cut `SRBin2` contains the following cutflow: `CutWeight` -> `CutHLT` -> `CutfatJetsPt` -> `CutfatJetsMassSD` -> `SRBin2`


All the output histograms are defined in  app/HHLooper.cc in the histograms object

Each output histogram will have the name of `CutName__HistogramName`, i.e. by default the program saves all histograms for all cuts in the cut flow defined above


# Run looper

```
./process.sh tag0 yes
```

# Make root file for datacard
```
cd python
python prepare_card.py tag0
```

# make plots

```
cd python
./plot_all.sh tag0
```
