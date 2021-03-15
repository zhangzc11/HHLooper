#!/usr/bin/env python

import sys
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
#import matplotlib.pyplot as plt
from xgboost import XGBClassifier
from xgboost import plot_tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, roc_curve
#import root_pandas as rp
import numpy as np
import pandas as pd
import math
import pickle as pickle
import ROOT as root
import uproot3 as uproot

#################
##Preliminaries
#################

#USAGE
#python append_xgboost_discriminator_to_tree.py <folder_name> <input_file_name> <year> <bkg_type> <bdt_type>

root.gROOT.Reset()

print(sys.argv)
folder     = sys.argv[1]
input_file = sys.argv[2]
_year      = '2017'
_bkg_type  = 'ttbar'##options are <qcd> and <ttbar>
_bdt_type  = 'basic0'

if len(sys.argv) >= 4:
    _year  = sys.argv[3]#<2016> <2017> <2018>
if len(sys.argv) >= 5:
    _bkg_type  = sys.argv[4]##options are <qcd>, <ttbar>, and <qcd_and_ttbar>
if len(sys.argv) >= 6:
    _bdt_type  = sys.argv[5]#<basic0>, <basic1>, <basic2>, <enhanced>, <enhanced_v2>

print(folder, input_file, _year, _bkg_type, _bdt_type)
#exit()
#signal
#folder = '/Users/cmorgoth/git/HHLooper/python/xgboost/data/v7/combined/2017/'
#FileName = folder + 'WWZAnalysis_WWZJetsTo4L2Nu_4f_TuneCUETP8M1_13TeV_aMCatNLOFxFx_pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'
#FileName = folder + 'WWZAnalysis_WZTo3LNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'
#FileName = folder + 'WWZAnalysis_ZZTo4L_13TeV_powheg_pythia8_1pb_weighted_lep34Mass_ZZDiscriminator'

#FileName = folder + input_file
FileName = input_file


#File = root.TFile(FileName)
File = root.TFile(FileName,'update')
Tree = File.Get('tree')
Nevents = File.Get('NEvents')



test_name = 'ReadingXgBoostModel'

_model_name = 'models/model_xgboost_training_weights_' + _bkg_type + '_' + _year + '_bdt_' + _bdt_type +'.pkl'

if _bdt_type == 'basic0':
    variables =   [
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],

    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   5000.],

    ]
elif _bdt_type == 'basic1':
    variables =   [
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],

    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   5000.],

    ]
elif _bdt_type == 'basic2':
    variables =   [
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],

    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   5000.],
    ['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    ['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    ['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    ['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],

    ]
elif _bdt_type == 'enhanced':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    ['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    ['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    ['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    ['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    ['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    ['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    ['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    ['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],

    ]
elif _bdt_type == 'enhanced_v2':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    ['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
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
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v5':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    #['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v5p2':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    #['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v5p3':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    #['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v6':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v7':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v8':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v8p2':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v8p3':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v9':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    ['fatJet2Eta', 'j2_eta', '$\eta^{j2}$', 40,  -2.5,  2.5],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    ['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v10':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    ['fatJet2Eta', 'j2_eta', '$\eta^{j2}$', 40,  -2.5,  2.5],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v10p2':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    ['fatJet2Eta', 'j2_eta', '$\eta^{j2}$', 40,  -2.5,  2.5],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v10p3':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    ['fatJet2Eta', 'j2_eta', '$\eta^{j2}$', 40,  -2.5,  2.5],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v11':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v12':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v13':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    #['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v14':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    #['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v15':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    #['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],


    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    ['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v16':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v17':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v18':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v19':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v20':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v21':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    ['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    ['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    ['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    ['fatJet1PNetQCDc', 'fatJet1PNetQCDc', 'fatJet1PNetQCDc', 40,  -100,   100],
    ['fatJet1PNetQCDcc', 'fatJet1PNetQCDcc', 'fatJet1PNetQCDcc', 40,  -100,   100],
    ['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v22':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
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
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    #['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v23':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    ['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],
    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    #['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    #['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v24':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    ['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],
    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    #['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    #['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]
elif _bdt_type == 'enhanced_v25':
    variables =   [
    ['hh_pt', 'hh_pt', '$p_{T}^{HH}$ (GeV)', 40, 0, 5000],
    ['hh_eta', 'hh_eta', '$\eta^{HH}$', 40, -5.0, 5.0],
    #['hh_phi', 'hh_phi', '$\phi^{HH}$', 40, -3.2, 3.2],
    ['hh_mass', 'hh_mass', '$m_{HH}$ (GeV)', 40, 0, 1500],
    ['MET', 'MET', '$MET$ (GeV)', 60, 0, 600],
    #                ['FatJet1_area', 'j1_area', 'fat j1 area', 40, 1.85, 2.15],
    #                ['FatJet2_area', 'j2_area', 'fat j2 area', 40,  1.85, 2.15],
    #['fatJet1MassSD', 'j1_m', 'j1 soft drop mass (GeV)', 40,  0.,   200.],
    #                ['fatJet1Mass', 'j2_m', 'j2 soft drop mass (GeV)', 40,  0.,   200.],

    #                ['fatJet1HasBJetCSVLoose', 'j1_CSVLoose', 'j1 DDB tagger', 3,  0,  3],
    # ['fatJet2HasBJetCSVLoose', 'j2_CSVLoose', 'j2 DDB tagger', 40,  0.78,  1.0],

    #['fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 'fatJet1Tau3OverTau2', 50,  0.0,  1.0],
    #['fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 'fatJet2Tau3OverTau2', 50,  0.0,  1.0],
    ['fatJet1MassSD', 'j1_mass_sd', '$M_{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Pt', 'j1_pt', '$p_{T}^{j1}$ (GeV)', 40,  0.,   5000.],
    ['fatJet1Eta', 'j1_eta', '$\eta^{j1}$', 40,  -2.5,  2.5],
    #['fatJet1Phi', 'j1_phi', '$\phi^{j1}$', 40,  -3.2,   3.2],
    #['fatJet1PNetXbb', 'fatJet1PNetXbb', 'fatJet1PNetXbb', 40,  -100,   100],
    #['fatJet1PNetQCDb', 'fatJet1PNetQCDb', 'fatJet1PNetQCDb', 40,  -100,   100],
    #['fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 'fatJet1PNetQCDbb', 40,  -100,   100],
    #['fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 'fatJet1PNetQCDothers', 40,  -100,   100],
    ['fatJet2Pt', 'j2_pt', '$p_{T}^{j2}$ (GeV)', 40,  0.,   500.],
    #['fatJet2PNetXbb', 'fatJet2PNetXbb', 'fatJet2PNetXbb', 40,  -100,   100],
    #['fatJet2PNetQCDb', 'fatJet2PNetQCDb', 'fatJet2PNetQCDb', 40,  -100,   100],
    #['fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 'fatJet2PNetQCDbb', 40,  -100,   100],
    #['fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 'fatJet2PNetQCDothers', 40,  -100,   100],
    #['deltaEta_j1j2', 'dEta_j1j2', '$\Delta\eta(j_{1}, j_{2})$', 40,  0.,   5.],
    #['deltaPhi_j1j2', 'dPhi_j1j2', '$\Delta\phi(j_{1}, j_{2})$', 40,  2.,   4.5],
    #['deltaR_j1j2', 'dR_j1j2', '$\Delta R(j_{1}, j_{2})$', 40,  0.,   5.],
    ['fatJet1PtOverMHH', 'ptj1Omhh', '$p_{T}^{j1}/m_{HH}$', 40,   0.,   1.],
    ['fatJet2PtOverMHH', 'ptj2Omhh', '$p_{T}^{j2}/m_{HH}$', 40,  0.,  0.7],

    #                ['ptj1_over_mj1', 'ptj1Omj1', '$p_{T}^{j1}/m_{j1}$', 40,  0.,   10.],
    #                ['ptj2_over_mj2', 'ptj2Omj2', '$p_{T}^{j2}/m_{j2}$', 40,  0.5,  10.],

    ['ptj2_over_ptj1', 'ptj2Optj1', '$p_{T}^{j2}/p_{T}^{j1}$', 40,  0.5,  1.],
    #['mj2_over_mj1', 'mj2Omj1', '$m^{j2}/m^{j1}$', 40,  0.0,  1.5],
    ]

print(len(variables))
my_variables = []
for var in variables:
    print (var[0])
    my_variables.append(var[0])
#print (variables[1:-1][0])
##Getting ROOT files into pandas
#df = rp.read_root(FileName+'.root', 'tree', columns=my_variables)
df = uproot.open(FileName)['tree'].pandas.df([row[0] for row in variables], flatten=False)


#getting a numpy array from two pandas data frames
x_test = df.values
#creating numpy array for target variables
y_test = np.zeros(len(df))


############################
# get model from file
############################
with open(_model_name,'rb') as pkl_file:
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
plt.hist(disc, bins=50, alpha=0.3)
plt.savefig('mydiscriminator_' + test_name + '.png')
print ("disc_bkg: ", disc)
#print y_pred

#############################################
##Creating a new TTree with the discriminator
#############################################

#ch = root.TChain("tree")
#ch.Add(FileName)
nEntries = Tree.GetEntries()
print ("nEntries = ", nEntries)
#*****set brances*****
#set branche satus, at first, all off
#event information
#new tree
_disc_var_name = 'disc_' + _bkg_type + '_' + _year + '_' + _bdt_type
#outFile = FileName.replace('.root','') + '_' + _disc_var_name + '.root'
#newFile = root.TFile(outFile,"RECREATE")
#ch_new = ch.CloneTree(0)


#root.gROOT.ProcessLine('struct MyStruct{float disc;};')
root.gROOT.ProcessLine("struct MyStruct{float disc;};")

from ROOT import MyStruct

# Create branches in the tree
my_s = MyStruct()
print(my_s)
print (root.addressof(my_s))
print (root.addressof(my_s,'disc'))
root.addressof(my_s,'disc')
bpt = Tree.Branch(_disc_var_name,root.addressof(my_s,'disc'), _disc_var_name+'/F');

for i in range(nEntries):
    Tree.GetEntry(i)
    if i%10000==0:
        print ("Processing event nr. %i of %i" % (i,nEntries))
    my_s.disc = disc[i]
    bpt.Fill()

Tree.Print()
# use GetCurrentFile just in case we went over the
# (customizable) maximum file size
Tree.GetCurrentFile().Write()
#Nevents.Write()
Tree.GetCurrentFile().Close()
