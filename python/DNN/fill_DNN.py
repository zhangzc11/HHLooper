import os, sys
import ROOT as rt
from root_numpy import root2array, tree2array, array2tree
#from root_pandas import read_root
import h5py 
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, roc_curve
import keras
import numpy as np
import numpy.lib.recfunctions as nlr
import pandas as pd

from matplotlib import pyplot as plt
import math
from math import pow

from keras.models import Sequential, Model
from keras.layers import Dense, Activation,Dropout, Input, BatchNormalization
from keras.callbacks import EarlyStopping
from keras.callbacks import ModelCheckpoint
from numpy.lib.recfunctions import append_fields
variables = ['fatJet1Pt', 'fatJet1Eta', 'fatJet1MassSD', 'fatJet1PNetXbb', 'fatJet1Tau3OverTau2', 'fatJet2Pt', 'fatJet2Eta',# 'fatJet2MassSD', 'fatJet2PNetXbb',
             'fatJet2Tau3OverTau2', 'hh_pt','hh_eta','hh_mass','MET','NJets','deltaR_j1j2','deltaEta_j1j2','fatJet3Pt', 'fatJet3Eta', 'fatJet3MassSD', 'fatJet3PNetXbb', 'fatJet3Tau3OverTau2', 
            #'fatJet1HasElectron','fatJet1HasMuon','fatJet2HasElectron','fatJet2HasMuon'
            ]
id_variables = ['run','lumi','event']
wt_variables = ['weight']
mass_variables= ['fatJet2MassSD']
QCD_bdt =['disc_qcd_and_ttbar_Run2_enhanced_v8p2']

def convert(tree, target=0):
    feature = tree2array(tree,
                        branches = id_variables+wt_variables+variables+mass_variables+QCD_bdt ,
                        #branches = variables,
                         #selection = 'disc_qcd_and_ttbar_Run2_enhanced_v8p2>0.23'
                        )
    return feature

def open_root_ntuples():
    main_paths = []
    main_paths.append('/storage/user/sixie/data/HH/20200902/SignalSelection/combined/2017/')
    main_paths.append('/storage/user/sixie/data/HH/20200902/SignalSelection/combined/2016/')
    main_paths.append('/storage/user/sixie/data/HH/20200902/SignalSelection/combined/2018/')

    #list of files used for training
    bkg_list =[] 
    sig_list=[]
    print(os.getcwd())
    os.listdir('/storage/user/idutta/CMSSW_9_4_2/src/HHLooper/python/DNN')
    bkg_list.append('ttH')
    sig_list.append('GluGluToHHTo4B')

    bkg_file =[]
    sig_file =[]

    all_file = [] # any other sample (data or MC not used in training)

    sig_fn = []
    bkg_fn = []
    all_fn = [] 
    for main_path in main_paths:
        
        directory = os.listdir(main_path)
        for name in directory:
            #print(name)
            found = 0
            for bkg_i in bkg_list:
                if (main_path+bkg_i) in (main_path+name):
                    #print(main_path+name)
                    bkg_fn.append(str(main_path+name))
                    bkg_file.append(rt.TFile.Open(str(main_path+name)))
                    found = 1
            for sig_i in sig_list:
                if (main_path+sig_i) in (main_path+name):
                    #print(main_path+name)
                    sig_fn.append(str(main_path+name))
                    sig_file.append(rt.TFile.Open(main_path+name))
                    found = 1
            if not(found):
                all_fn.append(str(main_path+name))
                all_file.append(rt.TFile.Open(str(main_path+name)))

    bkgnp = []
    for file in bkg_file:
        #print(file)
        bkgtree = file.Get("tree")
        bkgnp.append(convert(bkgtree))
        
    signp=[]    
    for file in sig_file:
        sigtree = file.Get("tree")
        signp.append(convert(sigtree))
        
    allnp = []
    for file in all_file:
        #print(file)
        alltree = file.Get("tree")
        allnp.append(convert(alltree))

    # This is a temporary fix to some branches; should be incorporated directly in the ntuples in the future    
    for i in range(len(signp)):
        #signp[i]["fatJet3Eta"][signp[i]["fatJet3Pt"] == 0] =-99.
        #signp[i]["fatJet3PNetXbb"][signp[i]["fatJet3PNetXbb"] == 0] =-99.
        #signp[i]["fatJet3Tau3OverTau2"][signp[i]["fatJet3Tau3OverTau2"] == 0] =-99.
        signp[i]['NJets'] = signp[i]['NJets']+1

        temp = -1.*np.ones_like(signp[i]['NJets'])
        signp[i] = append_fields(signp[i], 'ttHkill', temp, usemask=False)
    
    for i in range(len(bkgnp)):
        #bkgnp[i]["fatJet3Eta"][bkgnp[i]["fatJet3Pt"] == 0] =-99.
        #bkgnp[i]["fatJet3PNetXbb"][bkgnp[i]["fatJet3PNetXbb"] == 0] =-99.
        #bkgnp[i]["fatJet3Tau3OverTau2"][bkgnp[i]["fatJet3Tau3OverTau2"] == 0] =-99.
        bkgnp[i]['NJets'] = bkgnp[i]['NJets']+1
        
        temp = -1.*np.ones_like(bkgnp[i]['NJets'])
        bkgnp[i] = append_fields(bkgnp[i], 'ttHkill', temp, usemask=False)

    for i in range(len(allnp)):
        #allnp[i]["fatJet3Eta"][allnp[i]["fatJet3Pt"] == 0] =-99.
        #allnp[i]["fatJet3PNetXbb"][allnp[i]["fatJet3PNetXbb"] == 0] =-99.
        #allnp[i]["fatJet3Tau3OverTau2"][allnp[i]["fatJet3Tau3OverTau2"] == 0] =-99.
        allnp[i]['NJets'] = allnp[i]['NJets']+1

        temp = -1.*np.ones_like(allnp[i]['NJets'])
        allnp[i] = append_fields(allnp[i], 'ttHkill', temp, usemask=False)
    return bkgnp, signp, allnp, sig_fn, bkg_fn, all_fn

def loadModel():
    dnn_model = keras.models.load_model("model/ttHkiller_030920.h5")
    dnn_normfactors = np.load("model/ttHkiller_030920_wts.npy")
    
    return dnn_model, dnn_normfactors


def evalModel(dnn_model, dnn_normfactors, bkgnp, signp, allnp):
    
    for i in range(len(allnp)):

        dnn_vars_others_arr = np.vstack([allnp[i][k] for k in variables]).T
        #Normalize the DNN with the normalization factors from preprocessing in training 
        dnn_vars_others_arr -= dnn_normfactors[0]
        dnn_vars_others_arr /= dnn_normfactors[1]
        dnn_pred = dnn_model.predict(dnn_vars_others_arr)
        if(len(allnp[i]['ttHkill'])):
            allnp[i]['ttHkill'] = dnn_pred[:,0]

    for i in range(len(bkgnp)):

        dnn_vars_others_arr = np.vstack([bkgnp[i][k] for k in variables]).T
        #Normalize the DNN with the normalization factors from preprocessing in training                                                                                                                    
        dnn_vars_others_arr -= dnn_normfactors[0]
        dnn_vars_others_arr /= dnn_normfactors[1]
        dnn_pred = np.array(dnn_model.predict(dnn_vars_others_arr))
        if(len(bkgnp[i]['ttHkill'])):
            bkgnp[i]['ttHkill'] = dnn_pred[:,0]

    for i in range(len(signp)):

        dnn_vars_others_arr = np.vstack([signp[i][k] for k in variables]).T
        #Normalize the DNN with the normalization factors from preprocessing in training
        dnn_vars_others_arr -= dnn_normfactors[0]
        dnn_vars_others_arr /= dnn_normfactors[1]
        dnn_pred = np.array(dnn_model.predict(dnn_vars_others_arr))
        if(len(signp[i]['ttHkill'])):
            signp[i]['ttHkill'] = dnn_pred[:,0]

    return bkgnp, signp, allnp

def convert_to_tree(nparray,file_list):
    for i in range(len(file_list)):
        file_list[i] = file_list[i].replace("sixie", "idutta")
        dir = file_list[i].rsplit('/', 1) 
        if not os.path.exists(dir[0]):
            os.makedirs(dir[0])
        os.chdir(dir[0])
        oFile = rt.TFile.Open(dir[1] ,"RECREATE")
        new_tree = array2tree(nparray[i], name='tree')
        new_tree.Write()
        oFile.Close()
    return


bkgnp, signp, allnp, sig_fn, bkg_fn, all_fn = open_root_ntuples()
model, factors = loadModel()
bkgnp_tree, signp_tree, allnp_tree = evalModel(model, factors, bkgnp, signp, allnp)

#Omit training events
for i in range(len(bkgnp_tree)): 
    bkgnp_tree[i]["ttHkill"][bkgnp_tree[i]["event"]%10 <6] =-1.
for i in range(len(signp_tree)):
    signp_tree[i]["ttHkill"][signp_tree[i]["event"]%10 <6] =-1.

convert_to_tree(bkgnp_tree, bkg_fn)
convert_to_tree(signp_tree, sig_fn)
convert_to_tree(allnp_tree, all_fn)
