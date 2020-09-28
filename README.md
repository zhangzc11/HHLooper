# HHLooper
HHLooper

# Setup

```
cmsrel CMSSW_9_4_2
cd CMSSW_9_4_2/src
cmsenv
git clone git@github.com:zhangzc11/HHLooper.git
cd HHLooper
make
```

# Run looper

```
./process.sh yield_0927_v0
```

# make plots

```
cd python
./plot_all.sh yield_0927_v0
```
