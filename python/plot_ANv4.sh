#recoil plots, Figure 21
TAG=yield_AN_ttbar
for year in 2016 2017  2018
do
    python plot.py -i ../hists/${TAG}/${year}/ -s 1 TTBarCR__hh_pt  -d 
done
#Figure 13 is just a manual fit from  Figure 12

#####ttbar BDT shapes, Figure 28
#\includegraphics[width=0.45\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRTight__EventBDTv8p2_logY.pdf}
#\includegraphics[width=0.45\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRTight__EventBDTv8p2v3_logY.pdf}

TAG=yield_AN_ttbar_cor
python plot.py -i ../hists/${TAG}/combine/ -s 1 -w TTBarCRTight__EventBDTv24 -d

#Figure 25
#\includegraphics[width=0.4\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRBDT1v8p2__fatJet2MassSD_linY.pdf}
#\includegraphics[width=0.4\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRBDT2v8p2__fatJet2MassSD_linY.pdf}
#\includegraphics[width=0.4\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRBDT3v8p2__fatJet2MassSD_linY.pdf}
#\includegraphics[width=0.4\textwidth]{figs/yield_AN_ttbar_cor/combine/TTBarCRBDT4v8p2__fatJet2MassSD_linY.pdf}

#####top mass peak vs BDT, figure 15 and 16
TAG=yield_AN_ttbar_cor
for BDTv in v8p2
do
    for  BDTbin in  1 2 3 4
    do
        python plot.py -i ../hists/${TAG}/combine/ -s 1 -w TTBarCRBDT${BDTbin}${BDTv}__fatJet2MassSD -n 40 -d
    done
done
