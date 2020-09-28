#!/usr/bin/env python

import matplotlib.pyplot as plt
from xgboost import XGBClassifier
from xgboost import plot_tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, roc_curve
import root_pandas as rp
import numpy as np
import pandas as pd
import math
import cPickle as pickle
import ROOT as root
import uproot

#################
##Preliminaries
#################

root.gROOT.Reset()


#signal
folder = '/Users/cmorgoth/git/HHLooper/python/xgboost/data/signal_skim/trigger_and_mass_sd_skim/'
#FileName = folder + 'WWZAnalysis_WWZJetsTo4L2Nu_4f_TuneCUETP8M1_13TeV_aMCatNLOFxFx_pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'
#FileName = folder + 'WWZAnalysis_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'
#FileName = folder + 'WWZAnalysis_ZZTo4L_13TeV_powheg_pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'

#FileName = folder + 'bbbb_skim'
#FileName = folder + 'all_bkg_skim'
FileName = folder + 'JetHT_2017_TwoTaggedJetSkim_GoodLumi_my_skim'


File = root.TFile(FileName+'.root')
Tree = File.Get('tree')
Nevents = File.Get('NEvents')

test_name = 'ReadingXgBoostModel'

##Define variables to be used
##WWZ vs ttZ
variables =   [
                ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 900],
                ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
                ['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
                ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
                ['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


#                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
#                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
                #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
#                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

#                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
                # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

                 ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
                 ['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
                 ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   900.],
                 ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
                 ['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
                 #['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
                 #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
                 #'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
                 #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
                 ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   900.],
                 ['fatJet2Eta', 'j2_eta', '$\eta^{j2}$', 40,  -2.5,  2.5],
                 ['fatJet2Phi', 'j2_phi', '$\phi^{j2}$', 40,  -3.2,   3.2],
                 #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
                 #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
                 #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
                 #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
                 ['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
                 ['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
                 ['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
                 ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
                 ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

#                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
#                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

                 ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
                 ['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
              ]

print(len(variables))
my_variables = []
for var in variables:
    print var[0]
    my_variables.append(var[0])
#print (variables[1:-1][0])
##Getting ROOT files into pandas
#df = rp.read_root(FileName+'.root', 'tree', columns=my_variables)
df = uproot.open(FileName+'.root')['tree'].pandas.df([row[0] for row in variables], flatten=False)


#getting a numpy array from two pandas data frames
x_test = df.values
#creating numpy array for target variables
y_test = np.zeros(len(df))


############################
# get model from file
############################
with open('models/model_bbbb_vs_bkg_all_variables_v2_no_pnet_no_jet1mass_sd.pkl','rb') as pkl_file:
    model = pickle.load(pkl_file)


# make predictions for test data
y_pred = model.predict_proba(x_test)[:, 1]
print ("y_pred", y_pred)
predictions = [round(value) for value in y_pred]

#print y_pred
##########################################################
# make histogram of discriminator value for signal and bkg
##########################################################
y_frame = pd.DataFrame({'truth':y_test, 'disc':y_pred})
print ('y_frame',y_frame)
disc    = y_frame[y_frame['truth'] == 0]['disc'].values
#disc    = y_frame[y_frame['truth'] == 1]['disc'].values
plt.figure()
plt.hist(disc, normed=True, bins=50, alpha=0.3)
plt.savefig('mydiscriminator_' + test_name + '.png')
print "disc_bkg: ", disc
#print y_pred

#############################################
##Creating a new TTree with the discriminator
#############################################

ch = root.TChain("tree")
ch.Add(FileName+'.root')
nEntries = ch.GetEntries()
print "nEntries = ", nEntries
#*****set brances*****
#set branche satus, at first, all off
#event information
#new tree
outFile = FileName+'_HH_no_PNet_Discriminator.root'
newFile = root.TFile(outFile,"RECREATE")
ch_new = ch.CloneTree(0)

root.gROOT.ProcessLine("struct MyStruct{float disc_hh;};")

from ROOT import MyStruct

# Create branches in the tree
s = MyStruct()

bpt = ch_new.Branch('disc_hh',root.AddressOf(s,'disc_hh'),'disc_hh/F');

for i in range(nEntries):
    ch.GetEntry(i)
    if i%10000==0:
        print "Processing event nr. %i of %i" % (i,nEntries)
    s.disc_hh = disc[i]
    ch_new.Fill()
ch_new.Print()
# use GetCurrentFile just in case we went over the
# (customizable) maximum file size
ch_new.GetCurrentFile().Write()
Nevents.Write()
ch_new.GetCurrentFile().Close()
