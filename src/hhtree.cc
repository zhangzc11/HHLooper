#include "hhtree.hh"
hhtree hh; 

void hhtree::Init(TTree *tree) 
{

 run_branch = tree->GetBranch("run");
 if(run_branch) run_branch->SetAddress(&run_);
 luminosityBlock_branch = tree->GetBranch("luminosityBlock");
 if(luminosityBlock_branch) luminosityBlock_branch->SetAddress(&luminosityBlock_);
 event_branch = tree->GetBranch("event");
 if(event_branch) event_branch->SetAddress(&event_);
 ChsMET_phi_branch = tree->GetBranch("ChsMET_phi");
 if(ChsMET_phi_branch) ChsMET_phi_branch->SetAddress(&ChsMET_phi_);
 ChsMET_pt_branch = tree->GetBranch("ChsMET_pt");
 if(ChsMET_pt_branch) ChsMET_pt_branch->SetAddress(&ChsMET_pt_);
 ChsMET_sumEt_branch = tree->GetBranch("ChsMET_sumEt");
 if(ChsMET_sumEt_branch) ChsMET_sumEt_branch->SetAddress(&ChsMET_sumEt_);
 h_gen_pt_branch = tree->GetBranch("h_gen_pt");
 if(h_gen_pt_branch) h_gen_pt_branch->SetAddress(h_gen_pt_);
 h_gen_eta_branch = tree->GetBranch("h_gen_eta");
 if(h_gen_eta_branch) h_gen_eta_branch->SetAddress(h_gen_eta_);
 h_gen_phi_branch = tree->GetBranch("h_gen_phi");
 if(h_gen_phi_branch) h_gen_phi_branch->SetAddress(h_gen_phi_);
 hh_fatjet_idx_branch = tree->GetBranch("hh_fatjet_idx");
 if(hh_fatjet_idx_branch) hh_fatjet_idx_branch->SetAddress(hh_fatjet_idx_);
 nFatJet_branch = tree->GetBranch("nFatJet");
 if(nFatJet_branch) nFatJet_branch->SetAddress(&nFatJet_);
 FatJet_LSmsoftdrop_branch = tree->GetBranch("FatJet_LSmsoftdrop");
 if(FatJet_LSmsoftdrop_branch) FatJet_LSmsoftdrop_branch->SetAddress(FatJet_LSmsoftdrop_);
 FatJet_LSn2b1_branch = tree->GetBranch("FatJet_LSn2b1");
 if(FatJet_LSn2b1_branch) FatJet_LSn2b1_branch->SetAddress(FatJet_LSn2b1_);
 FatJet_LSn3b1_branch = tree->GetBranch("FatJet_LSn3b1");
 if(FatJet_LSn3b1_branch) FatJet_LSn3b1_branch->SetAddress(FatJet_LSn3b1_);
 FatJet_LSpt_branch = tree->GetBranch("FatJet_LSpt");
 if(FatJet_LSpt_branch) FatJet_LSpt_branch->SetAddress(FatJet_LSpt_);
 FatJet_LSrawmsoftdrop_branch = tree->GetBranch("FatJet_LSrawmsoftdrop");
 if(FatJet_LSrawmsoftdrop_branch) FatJet_LSrawmsoftdrop_branch->SetAddress(FatJet_LSrawmsoftdrop_);
 FatJet_LSsubJet1btagDeepB_branch = tree->GetBranch("FatJet_LSsubJet1btagDeepB");
 if(FatJet_LSsubJet1btagDeepB_branch) FatJet_LSsubJet1btagDeepB_branch->SetAddress(FatJet_LSsubJet1btagDeepB_);
 FatJet_LSsubJet2btagDeepB_branch = tree->GetBranch("FatJet_LSsubJet2btagDeepB");
 if(FatJet_LSsubJet2btagDeepB_branch) FatJet_LSsubJet2btagDeepB_branch->SetAddress(FatJet_LSsubJet2btagDeepB_);
 FatJet_LStau1_branch = tree->GetBranch("FatJet_LStau1");
 if(FatJet_LStau1_branch) FatJet_LStau1_branch->SetAddress(FatJet_LStau1_);
 FatJet_LStau2_branch = tree->GetBranch("FatJet_LStau2");
 if(FatJet_LStau2_branch) FatJet_LStau2_branch->SetAddress(FatJet_LStau2_);
 FatJet_LStau3_branch = tree->GetBranch("FatJet_LStau3");
 if(FatJet_LStau3_branch) FatJet_LStau3_branch->SetAddress(FatJet_LStau3_);
 FatJet_LStau4_branch = tree->GetBranch("FatJet_LStau4");
 if(FatJet_LStau4_branch) FatJet_LStau4_branch->SetAddress(FatJet_LStau4_);
 FatJet_area_branch = tree->GetBranch("FatJet_area");
 if(FatJet_area_branch) FatJet_area_branch->SetAddress(FatJet_area_);
 FatJet_btagDDBvL_branch = tree->GetBranch("FatJet_btagDDBvL");
 if(FatJet_btagDDBvL_branch) FatJet_btagDDBvL_branch->SetAddress(FatJet_btagDDBvL_);
 FatJet_btagDDCvB_branch = tree->GetBranch("FatJet_btagDDCvB");
 if(FatJet_btagDDCvB_branch) FatJet_btagDDCvB_branch->SetAddress(FatJet_btagDDCvB_);
 FatJet_btagDDCvL_branch = tree->GetBranch("FatJet_btagDDCvL");
 if(FatJet_btagDDCvL_branch) FatJet_btagDDCvL_branch->SetAddress(FatJet_btagDDCvL_);
 FatJet_btagHbb_branch = tree->GetBranch("FatJet_btagHbb");
 if(FatJet_btagHbb_branch) FatJet_btagHbb_branch->SetAddress(FatJet_btagHbb_);
 FatJet_dRLep_branch = tree->GetBranch("FatJet_dRLep");
 if(FatJet_dRLep_branch) FatJet_dRLep_branch->SetAddress(FatJet_dRLep_);
 FatJet_deepTagHbb_branch = tree->GetBranch("FatJet_deepTagHbb");
 if(FatJet_deepTagHbb_branch) FatJet_deepTagHbb_branch->SetAddress(FatJet_deepTagHbb_);
 FatJet_deepTagHcc_branch = tree->GetBranch("FatJet_deepTagHcc");
 if(FatJet_deepTagHcc_branch) FatJet_deepTagHcc_branch->SetAddress(FatJet_deepTagHcc_);
 FatJet_deepTagHqqqq_branch = tree->GetBranch("FatJet_deepTagHqqqq");
 if(FatJet_deepTagHqqqq_branch) FatJet_deepTagHqqqq_branch->SetAddress(FatJet_deepTagHqqqq_);
 FatJet_deepTagMDHbb_branch = tree->GetBranch("FatJet_deepTagMDHbb");
 if(FatJet_deepTagMDHbb_branch) FatJet_deepTagMDHbb_branch->SetAddress(FatJet_deepTagMDHbb_);
 FatJet_deepTagMDHcc_branch = tree->GetBranch("FatJet_deepTagMDHcc");
 if(FatJet_deepTagMDHcc_branch) FatJet_deepTagMDHcc_branch->SetAddress(FatJet_deepTagMDHcc_);
 FatJet_deepTagMDHqqqq_branch = tree->GetBranch("FatJet_deepTagMDHqqqq");
 if(FatJet_deepTagMDHqqqq_branch) FatJet_deepTagMDHqqqq_branch->SetAddress(FatJet_deepTagMDHqqqq_);
 FatJet_deepTagMDQCDbb_branch = tree->GetBranch("FatJet_deepTagMDQCDbb");
 if(FatJet_deepTagMDQCDbb_branch) FatJet_deepTagMDQCDbb_branch->SetAddress(FatJet_deepTagMDQCDbb_);
 FatJet_deepTagMDQCDcc_branch = tree->GetBranch("FatJet_deepTagMDQCDcc");
 if(FatJet_deepTagMDQCDcc_branch) FatJet_deepTagMDQCDcc_branch->SetAddress(FatJet_deepTagMDQCDcc_);
 FatJet_deepTagMDWcq_branch = tree->GetBranch("FatJet_deepTagMDWcq");
 if(FatJet_deepTagMDWcq_branch) FatJet_deepTagMDWcq_branch->SetAddress(FatJet_deepTagMDWcq_);
 FatJet_deepTagMDWqq_branch = tree->GetBranch("FatJet_deepTagMDWqq");
 if(FatJet_deepTagMDWqq_branch) FatJet_deepTagMDWqq_branch->SetAddress(FatJet_deepTagMDWqq_);
 FatJet_deepTagMDZbb_branch = tree->GetBranch("FatJet_deepTagMDZbb");
 if(FatJet_deepTagMDZbb_branch) FatJet_deepTagMDZbb_branch->SetAddress(FatJet_deepTagMDZbb_);
 FatJet_deepTagMDZcc_branch = tree->GetBranch("FatJet_deepTagMDZcc");
 if(FatJet_deepTagMDZcc_branch) FatJet_deepTagMDZcc_branch->SetAddress(FatJet_deepTagMDZcc_);
 FatJet_deepTagMDZqq_branch = tree->GetBranch("FatJet_deepTagMDZqq");
 if(FatJet_deepTagMDZqq_branch) FatJet_deepTagMDZqq_branch->SetAddress(FatJet_deepTagMDZqq_);
 FatJet_deepTagQCDbb_branch = tree->GetBranch("FatJet_deepTagQCDbb");
 if(FatJet_deepTagQCDbb_branch) FatJet_deepTagQCDbb_branch->SetAddress(FatJet_deepTagQCDbb_);
 FatJet_deepTagQCDcc_branch = tree->GetBranch("FatJet_deepTagQCDcc");
 if(FatJet_deepTagQCDcc_branch) FatJet_deepTagQCDcc_branch->SetAddress(FatJet_deepTagQCDcc_);
 FatJet_deepTagWcq_branch = tree->GetBranch("FatJet_deepTagWcq");
 if(FatJet_deepTagWcq_branch) FatJet_deepTagWcq_branch->SetAddress(FatJet_deepTagWcq_);
 FatJet_deepTagWqq_branch = tree->GetBranch("FatJet_deepTagWqq");
 if(FatJet_deepTagWqq_branch) FatJet_deepTagWqq_branch->SetAddress(FatJet_deepTagWqq_);
 FatJet_deepTagZbb_branch = tree->GetBranch("FatJet_deepTagZbb");
 if(FatJet_deepTagZbb_branch) FatJet_deepTagZbb_branch->SetAddress(FatJet_deepTagZbb_);
 FatJet_deepTagZcc_branch = tree->GetBranch("FatJet_deepTagZcc");
 if(FatJet_deepTagZcc_branch) FatJet_deepTagZcc_branch->SetAddress(FatJet_deepTagZcc_);
 FatJet_deepTagZqq_branch = tree->GetBranch("FatJet_deepTagZqq");
 if(FatJet_deepTagZqq_branch) FatJet_deepTagZqq_branch->SetAddress(FatJet_deepTagZqq_);
 FatJet_eta_branch = tree->GetBranch("FatJet_eta");
 if(FatJet_eta_branch) FatJet_eta_branch->SetAddress(FatJet_eta_);
 FatJet_lsf3_branch = tree->GetBranch("FatJet_lsf3");
 if(FatJet_lsf3_branch) FatJet_lsf3_branch->SetAddress(FatJet_lsf3_);
 FatJet_mass_branch = tree->GetBranch("FatJet_mass");
 if(FatJet_mass_branch) FatJet_mass_branch->SetAddress(FatJet_mass_);
 FatJet_msoftdrop_branch = tree->GetBranch("FatJet_msoftdrop");
 if(FatJet_msoftdrop_branch) FatJet_msoftdrop_branch->SetAddress(FatJet_msoftdrop_);
 FatJet_n2b1_branch = tree->GetBranch("FatJet_n2b1");
 if(FatJet_n2b1_branch) FatJet_n2b1_branch->SetAddress(FatJet_n2b1_);
 FatJet_n3b1_branch = tree->GetBranch("FatJet_n3b1");
 if(FatJet_n3b1_branch) FatJet_n3b1_branch->SetAddress(FatJet_n3b1_);
 FatJet_phi_branch = tree->GetBranch("FatJet_phi");
 if(FatJet_phi_branch) FatJet_phi_branch->SetAddress(FatJet_phi_);
 FatJet_pt_branch = tree->GetBranch("FatJet_pt");
 if(FatJet_pt_branch) FatJet_pt_branch->SetAddress(FatJet_pt_);
 FatJet_rawFactor_branch = tree->GetBranch("FatJet_rawFactor");
 if(FatJet_rawFactor_branch) FatJet_rawFactor_branch->SetAddress(FatJet_rawFactor_);
 FatJet_rawmsoftdrop_branch = tree->GetBranch("FatJet_rawmsoftdrop");
 if(FatJet_rawmsoftdrop_branch) FatJet_rawmsoftdrop_branch->SetAddress(FatJet_rawmsoftdrop_);
 FatJet_tau1_branch = tree->GetBranch("FatJet_tau1");
 if(FatJet_tau1_branch) FatJet_tau1_branch->SetAddress(FatJet_tau1_);
 FatJet_tau2_branch = tree->GetBranch("FatJet_tau2");
 if(FatJet_tau2_branch) FatJet_tau2_branch->SetAddress(FatJet_tau2_);
 FatJet_tau3_branch = tree->GetBranch("FatJet_tau3");
 if(FatJet_tau3_branch) FatJet_tau3_branch->SetAddress(FatJet_tau3_);
 FatJet_tau4_branch = tree->GetBranch("FatJet_tau4");
 if(FatJet_tau4_branch) FatJet_tau4_branch->SetAddress(FatJet_tau4_);
 FatJet_electronIdx3SJ_branch = tree->GetBranch("FatJet_electronIdx3SJ");
 if(FatJet_electronIdx3SJ_branch) FatJet_electronIdx3SJ_branch->SetAddress(FatJet_electronIdx3SJ_);
 FatJet_idLep_branch = tree->GetBranch("FatJet_idLep");
 if(FatJet_idLep_branch) FatJet_idLep_branch->SetAddress(FatJet_idLep_);
 FatJet_jetId_branch = tree->GetBranch("FatJet_jetId");
 if(FatJet_jetId_branch) FatJet_jetId_branch->SetAddress(FatJet_jetId_);
 FatJet_muonIdx3SJ_branch = tree->GetBranch("FatJet_muonIdx3SJ");
 if(FatJet_muonIdx3SJ_branch) FatJet_muonIdx3SJ_branch->SetAddress(FatJet_muonIdx3SJ_);
 FatJet_nBHadrons_branch = tree->GetBranch("FatJet_nBHadrons");
 if(FatJet_nBHadrons_branch) FatJet_nBHadrons_branch->SetAddress(FatJet_nBHadrons_);
 FatJet_nCHadrons_branch = tree->GetBranch("FatJet_nCHadrons");
 if(FatJet_nCHadrons_branch) FatJet_nCHadrons_branch->SetAddress(FatJet_nCHadrons_);
 FatJet_nPFConstituents_branch = tree->GetBranch("FatJet_nPFConstituents");
 if(FatJet_nPFConstituents_branch) FatJet_nPFConstituents_branch->SetAddress(FatJet_nPFConstituents_);
 FatJet_subJetIdx1_branch = tree->GetBranch("FatJet_subJetIdx1");
 if(FatJet_subJetIdx1_branch) FatJet_subJetIdx1_branch->SetAddress(FatJet_subJetIdx1_);
 FatJet_subJetIdx2_branch = tree->GetBranch("FatJet_subJetIdx2");
 if(FatJet_subJetIdx2_branch) FatJet_subJetIdx2_branch->SetAddress(FatJet_subJetIdx2_);
 FatJet_Hmatch_branch = tree->GetBranch("FatJet_Hmatch");
 if(FatJet_Hmatch_branch) FatJet_Hmatch_branch->SetAddress(FatJet_Hmatch_);
 FatJet_HgenIdx_branch = tree->GetBranch("FatJet_HgenIdx");
 if(FatJet_HgenIdx_branch) FatJet_HgenIdx_branch->SetAddress(FatJet_HgenIdx_);
 FatJet_HminDR_branch = tree->GetBranch("FatJet_HminDR");
 if(FatJet_HminDR_branch) FatJet_HminDR_branch->SetAddress(FatJet_HminDR_);
 HLT_PFHT1050_branch = tree->GetBranch("HLT_PFHT1050");
 if(HLT_PFHT1050_branch) HLT_PFHT1050_branch->SetAddress(&HLT_PFHT1050_);
 HLT_AK8PFJet360_TrimMass30_branch = tree->GetBranch("HLT_AK8PFJet360_TrimMass30");
 if(HLT_AK8PFJet360_TrimMass30_branch) HLT_AK8PFJet360_TrimMass30_branch->SetAddress(&HLT_AK8PFJet360_TrimMass30_);
 HLT_AK8PFJet380_TrimMass30_branch = tree->GetBranch("HLT_AK8PFJet380_TrimMass30");
 if(HLT_AK8PFJet380_TrimMass30_branch) HLT_AK8PFJet380_TrimMass30_branch->SetAddress(&HLT_AK8PFJet380_TrimMass30_);
 HLT_AK8PFJet400_TrimMass30_branch = tree->GetBranch("HLT_AK8PFJet400_TrimMass30");
 if(HLT_AK8PFJet400_TrimMass30_branch) HLT_AK8PFJet400_TrimMass30_branch->SetAddress(&HLT_AK8PFJet400_TrimMass30_);
 HLT_AK8PFJet420_TrimMass30_branch = tree->GetBranch("HLT_AK8PFJet420_TrimMass30");
 if(HLT_AK8PFJet420_TrimMass30_branch) HLT_AK8PFJet420_TrimMass30_branch->SetAddress(&HLT_AK8PFJet420_TrimMass30_);
 HLT_AK8PFHT800_TrimMass50_branch = tree->GetBranch("HLT_AK8PFHT800_TrimMass50");
 if(HLT_AK8PFHT800_TrimMass50_branch) HLT_AK8PFHT800_TrimMass50_branch->SetAddress(&HLT_AK8PFHT800_TrimMass50_);
 HLT_PFJet500_branch = tree->GetBranch("HLT_PFJet500");
 if(HLT_PFJet500_branch) HLT_PFJet500_branch->SetAddress(&HLT_PFJet500_);
 HLT_AK8PFJet500_branch = tree->GetBranch("HLT_AK8PFJet500");
 if(HLT_AK8PFJet500_branch) HLT_AK8PFJet500_branch->SetAddress(&HLT_AK8PFJet500_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_);
 HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch = tree->GetBranch("HLT_AK8PFJet330_PFAK8BTagCSV_p17");
 if(HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch) HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch->SetAddress(&HLT_AK8PFJet330_PFAK8BTagCSV_p17_);
 hh_pt_branch = tree->GetBranch("hh_pt");
 if(hh_pt_branch) hh_pt_branch->SetAddress(&hh_pt_);
 hh_eta_branch = tree->GetBranch("hh_eta");
 if(hh_eta_branch) hh_eta_branch->SetAddress(&hh_eta_);
 hh_phi_branch = tree->GetBranch("hh_phi");
 if(hh_phi_branch) hh_phi_branch->SetAddress(&hh_phi_);
 hh_mass_branch = tree->GetBranch("hh_mass");
 if(hh_mass_branch) hh_mass_branch->SetAddress(&hh_mass_);
 hh_gen_pt_branch = tree->GetBranch("hh_gen_pt");
 if(hh_gen_pt_branch) hh_gen_pt_branch->SetAddress(&hh_gen_pt_);
 hh_gen_eta_branch = tree->GetBranch("hh_gen_eta");
 if(hh_gen_eta_branch) hh_gen_eta_branch->SetAddress(&hh_gen_eta_);
 hh_gen_phi_branch = tree->GetBranch("hh_gen_phi");
 if(hh_gen_phi_branch) hh_gen_phi_branch->SetAddress(&hh_gen_phi_);
 hh_gen_mass_branch = tree->GetBranch("hh_gen_mass");
 if(hh_gen_mass_branch) hh_gen_mass_branch->SetAddress(&hh_gen_mass_);
 weight_branch = tree->GetBranch("weight");
 if(weight_branch) weight_branch->SetAddress(&weight_);
}

void hhtree::GetEntry(unsigned int idx)
{

 index = idx;
 run_isLoaded = false;
 luminosityBlock_isLoaded = false;
 event_isLoaded = false;
 ChsMET_phi_isLoaded = false;
 ChsMET_pt_isLoaded = false;
 ChsMET_sumEt_isLoaded = false;
 h_gen_pt_isLoaded = false;
 h_gen_eta_isLoaded = false;
 h_gen_phi_isLoaded = false;
 hh_fatjet_idx_isLoaded = false;
 nFatJet_isLoaded = false;
 FatJet_LSmsoftdrop_isLoaded = false;
 FatJet_LSn2b1_isLoaded = false;
 FatJet_LSn3b1_isLoaded = false;
 FatJet_LSpt_isLoaded = false;
 FatJet_LSrawmsoftdrop_isLoaded = false;
 FatJet_LSsubJet1btagDeepB_isLoaded = false;
 FatJet_LSsubJet2btagDeepB_isLoaded = false;
 FatJet_LStau1_isLoaded = false;
 FatJet_LStau2_isLoaded = false;
 FatJet_LStau3_isLoaded = false;
 FatJet_LStau4_isLoaded = false;
 FatJet_area_isLoaded = false;
 FatJet_btagDDBvL_isLoaded = false;
 FatJet_btagDDCvB_isLoaded = false;
 FatJet_btagDDCvL_isLoaded = false;
 FatJet_btagHbb_isLoaded = false;
 FatJet_dRLep_isLoaded = false;
 FatJet_deepTagHbb_isLoaded = false;
 FatJet_deepTagHcc_isLoaded = false;
 FatJet_deepTagHqqqq_isLoaded = false;
 FatJet_deepTagMDHbb_isLoaded = false;
 FatJet_deepTagMDHcc_isLoaded = false;
 FatJet_deepTagMDHqqqq_isLoaded = false;
 FatJet_deepTagMDQCDbb_isLoaded = false;
 FatJet_deepTagMDQCDcc_isLoaded = false;
 FatJet_deepTagMDWcq_isLoaded = false;
 FatJet_deepTagMDWqq_isLoaded = false;
 FatJet_deepTagMDZbb_isLoaded = false;
 FatJet_deepTagMDZcc_isLoaded = false;
 FatJet_deepTagMDZqq_isLoaded = false;
 FatJet_deepTagQCDbb_isLoaded = false;
 FatJet_deepTagQCDcc_isLoaded = false;
 FatJet_deepTagWcq_isLoaded = false;
 FatJet_deepTagWqq_isLoaded = false;
 FatJet_deepTagZbb_isLoaded = false;
 FatJet_deepTagZcc_isLoaded = false;
 FatJet_deepTagZqq_isLoaded = false;
 FatJet_eta_isLoaded = false;
 FatJet_lsf3_isLoaded = false;
 FatJet_mass_isLoaded = false;
 FatJet_msoftdrop_isLoaded = false;
 FatJet_n2b1_isLoaded = false;
 FatJet_n3b1_isLoaded = false;
 FatJet_phi_isLoaded = false;
 FatJet_pt_isLoaded = false;
 FatJet_rawFactor_isLoaded = false;
 FatJet_rawmsoftdrop_isLoaded = false;
 FatJet_tau1_isLoaded = false;
 FatJet_tau2_isLoaded = false;
 FatJet_tau3_isLoaded = false;
 FatJet_tau4_isLoaded = false;
 FatJet_electronIdx3SJ_isLoaded = false;
 FatJet_idLep_isLoaded = false;
 FatJet_jetId_isLoaded = false;
 FatJet_muonIdx3SJ_isLoaded = false;
 FatJet_nBHadrons_isLoaded = false;
 FatJet_nCHadrons_isLoaded = false;
 FatJet_nPFConstituents_isLoaded = false;
 FatJet_subJetIdx1_isLoaded = false;
 FatJet_subJetIdx2_isLoaded = false;
 FatJet_Hmatch_isLoaded = false;
 FatJet_HgenIdx_isLoaded = false;
 FatJet_HminDR_isLoaded = false;
 HLT_PFHT1050_isLoaded = false;
 HLT_AK8PFJet360_TrimMass30_isLoaded = false;
 HLT_AK8PFJet380_TrimMass30_isLoaded = false;
 HLT_AK8PFJet400_TrimMass30_isLoaded = false;
 HLT_AK8PFJet420_TrimMass30_isLoaded = false;
 HLT_AK8PFHT800_TrimMass50_isLoaded = false;
 HLT_PFJet500_isLoaded = false;
 HLT_AK8PFJet500_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_isLoaded = false;
 HLT_AK8PFJet330_PFAK8BTagCSV_p17_isLoaded = false;
 hh_pt_isLoaded = false;
 hh_eta_isLoaded = false;
 hh_phi_isLoaded = false;
 hh_mass_isLoaded = false;
 hh_gen_pt_isLoaded = false;
 hh_gen_eta_isLoaded = false;
 hh_gen_phi_isLoaded = false;
 hh_gen_mass_isLoaded = false;
 weight_isLoaded = false;
}

const unsigned int &hhtree::run() 
{
 if(not run_isLoaded)
 {
   if(run_branch != 0) run_branch->GetEntry(index);
   else
   {
     printf("branch run_branch does not exist!\n");
exit(1);
   }
   run_isLoaded = true;
 }
 return run_;
}

const unsigned int &hhtree::luminosityBlock() 
{
 if(not luminosityBlock_isLoaded)
 {
   if(luminosityBlock_branch != 0) luminosityBlock_branch->GetEntry(index);
   else
   {
     printf("branch luminosityBlock_branch does not exist!\n");
exit(1);
   }
   luminosityBlock_isLoaded = true;
 }
 return luminosityBlock_;
}

const unsigned long int &hhtree::event() 
{
 if(not event_isLoaded)
 {
   if(event_branch != 0) event_branch->GetEntry(index);
   else
   {
     printf("branch event_branch does not exist!\n");
exit(1);
   }
   event_isLoaded = true;
 }
 return event_;
}

const float &hhtree::ChsMET_phi() 
{
 if(not ChsMET_phi_isLoaded)
 {
   if(ChsMET_phi_branch != 0) ChsMET_phi_branch->GetEntry(index);
   else
   {
     printf("branch ChsMET_phi_branch does not exist!\n");
exit(1);
   }
   ChsMET_phi_isLoaded = true;
 }
 return ChsMET_phi_;
}

const float &hhtree::ChsMET_pt() 
{
 if(not ChsMET_pt_isLoaded)
 {
   if(ChsMET_pt_branch != 0) ChsMET_pt_branch->GetEntry(index);
   else
   {
     printf("branch ChsMET_pt_branch does not exist!\n");
exit(1);
   }
   ChsMET_pt_isLoaded = true;
 }
 return ChsMET_pt_;
}

const float &hhtree::ChsMET_sumEt() 
{
 if(not ChsMET_sumEt_isLoaded)
 {
   if(ChsMET_sumEt_branch != 0) ChsMET_sumEt_branch->GetEntry(index);
   else
   {
     printf("branch ChsMET_sumEt_branch does not exist!\n");
exit(1);
   }
   ChsMET_sumEt_isLoaded = true;
 }
 return ChsMET_sumEt_;
}

const float * hhtree::h_gen_pt() 
{
 if(not h_gen_pt_isLoaded)
 {
   if(h_gen_pt_branch != 0) h_gen_pt_branch->GetEntry(index);
   else
   {
     printf("branch h_gen_pt_branch does not exist!\n");
exit(1);
   }
   h_gen_pt_isLoaded = true;
 }
 return h_gen_pt_;
}

const float * hhtree::h_gen_eta() 
{
 if(not h_gen_eta_isLoaded)
 {
   if(h_gen_eta_branch != 0) h_gen_eta_branch->GetEntry(index);
   else
   {
     printf("branch h_gen_eta_branch does not exist!\n");
exit(1);
   }
   h_gen_eta_isLoaded = true;
 }
 return h_gen_eta_;
}

const float * hhtree::h_gen_phi() 
{
 if(not h_gen_phi_isLoaded)
 {
   if(h_gen_phi_branch != 0) h_gen_phi_branch->GetEntry(index);
   else
   {
     printf("branch h_gen_phi_branch does not exist!\n");
exit(1);
   }
   h_gen_phi_isLoaded = true;
 }
 return h_gen_phi_;
}

const unsigned int * hhtree::hh_fatjet_idx() 
{
 if(not hh_fatjet_idx_isLoaded)
 {
   if(hh_fatjet_idx_branch != 0) hh_fatjet_idx_branch->GetEntry(index);
   else
   {
     printf("branch hh_fatjet_idx_branch does not exist!\n");
exit(1);
   }
   hh_fatjet_idx_isLoaded = true;
 }
 return hh_fatjet_idx_;
}

const unsigned int &hhtree::nFatJet() 
{
 if(not nFatJet_isLoaded)
 {
   if(nFatJet_branch != 0) nFatJet_branch->GetEntry(index);
   else
   {
     printf("branch nFatJet_branch does not exist!\n");
exit(1);
   }
   nFatJet_isLoaded = true;
 }
 return nFatJet_;
}

const float * hhtree::FatJet_LSmsoftdrop() 
{
 if(not FatJet_LSmsoftdrop_isLoaded)
 {
   if(FatJet_LSmsoftdrop_branch != 0) FatJet_LSmsoftdrop_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSmsoftdrop_branch does not exist!\n");
exit(1);
   }
   FatJet_LSmsoftdrop_isLoaded = true;
 }
 return FatJet_LSmsoftdrop_;
}

const float * hhtree::FatJet_LSn2b1() 
{
 if(not FatJet_LSn2b1_isLoaded)
 {
   if(FatJet_LSn2b1_branch != 0) FatJet_LSn2b1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSn2b1_branch does not exist!\n");
exit(1);
   }
   FatJet_LSn2b1_isLoaded = true;
 }
 return FatJet_LSn2b1_;
}

const float * hhtree::FatJet_LSn3b1() 
{
 if(not FatJet_LSn3b1_isLoaded)
 {
   if(FatJet_LSn3b1_branch != 0) FatJet_LSn3b1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSn3b1_branch does not exist!\n");
exit(1);
   }
   FatJet_LSn3b1_isLoaded = true;
 }
 return FatJet_LSn3b1_;
}

const float * hhtree::FatJet_LSpt() 
{
 if(not FatJet_LSpt_isLoaded)
 {
   if(FatJet_LSpt_branch != 0) FatJet_LSpt_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSpt_branch does not exist!\n");
exit(1);
   }
   FatJet_LSpt_isLoaded = true;
 }
 return FatJet_LSpt_;
}

const float * hhtree::FatJet_LSrawmsoftdrop() 
{
 if(not FatJet_LSrawmsoftdrop_isLoaded)
 {
   if(FatJet_LSrawmsoftdrop_branch != 0) FatJet_LSrawmsoftdrop_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSrawmsoftdrop_branch does not exist!\n");
exit(1);
   }
   FatJet_LSrawmsoftdrop_isLoaded = true;
 }
 return FatJet_LSrawmsoftdrop_;
}

const float * hhtree::FatJet_LSsubJet1btagDeepB() 
{
 if(not FatJet_LSsubJet1btagDeepB_isLoaded)
 {
   if(FatJet_LSsubJet1btagDeepB_branch != 0) FatJet_LSsubJet1btagDeepB_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSsubJet1btagDeepB_branch does not exist!\n");
exit(1);
   }
   FatJet_LSsubJet1btagDeepB_isLoaded = true;
 }
 return FatJet_LSsubJet1btagDeepB_;
}

const float * hhtree::FatJet_LSsubJet2btagDeepB() 
{
 if(not FatJet_LSsubJet2btagDeepB_isLoaded)
 {
   if(FatJet_LSsubJet2btagDeepB_branch != 0) FatJet_LSsubJet2btagDeepB_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LSsubJet2btagDeepB_branch does not exist!\n");
exit(1);
   }
   FatJet_LSsubJet2btagDeepB_isLoaded = true;
 }
 return FatJet_LSsubJet2btagDeepB_;
}

const float * hhtree::FatJet_LStau1() 
{
 if(not FatJet_LStau1_isLoaded)
 {
   if(FatJet_LStau1_branch != 0) FatJet_LStau1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LStau1_branch does not exist!\n");
exit(1);
   }
   FatJet_LStau1_isLoaded = true;
 }
 return FatJet_LStau1_;
}

const float * hhtree::FatJet_LStau2() 
{
 if(not FatJet_LStau2_isLoaded)
 {
   if(FatJet_LStau2_branch != 0) FatJet_LStau2_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LStau2_branch does not exist!\n");
exit(1);
   }
   FatJet_LStau2_isLoaded = true;
 }
 return FatJet_LStau2_;
}

const float * hhtree::FatJet_LStau3() 
{
 if(not FatJet_LStau3_isLoaded)
 {
   if(FatJet_LStau3_branch != 0) FatJet_LStau3_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LStau3_branch does not exist!\n");
exit(1);
   }
   FatJet_LStau3_isLoaded = true;
 }
 return FatJet_LStau3_;
}

const float * hhtree::FatJet_LStau4() 
{
 if(not FatJet_LStau4_isLoaded)
 {
   if(FatJet_LStau4_branch != 0) FatJet_LStau4_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_LStau4_branch does not exist!\n");
exit(1);
   }
   FatJet_LStau4_isLoaded = true;
 }
 return FatJet_LStau4_;
}

const float * hhtree::FatJet_area() 
{
 if(not FatJet_area_isLoaded)
 {
   if(FatJet_area_branch != 0) FatJet_area_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_area_branch does not exist!\n");
exit(1);
   }
   FatJet_area_isLoaded = true;
 }
 return FatJet_area_;
}

const float * hhtree::FatJet_btagDDBvL() 
{
 if(not FatJet_btagDDBvL_isLoaded)
 {
   if(FatJet_btagDDBvL_branch != 0) FatJet_btagDDBvL_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_btagDDBvL_branch does not exist!\n");
exit(1);
   }
   FatJet_btagDDBvL_isLoaded = true;
 }
 return FatJet_btagDDBvL_;
}

const float * hhtree::FatJet_btagDDCvB() 
{
 if(not FatJet_btagDDCvB_isLoaded)
 {
   if(FatJet_btagDDCvB_branch != 0) FatJet_btagDDCvB_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_btagDDCvB_branch does not exist!\n");
exit(1);
   }
   FatJet_btagDDCvB_isLoaded = true;
 }
 return FatJet_btagDDCvB_;
}

const float * hhtree::FatJet_btagDDCvL() 
{
 if(not FatJet_btagDDCvL_isLoaded)
 {
   if(FatJet_btagDDCvL_branch != 0) FatJet_btagDDCvL_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_btagDDCvL_branch does not exist!\n");
exit(1);
   }
   FatJet_btagDDCvL_isLoaded = true;
 }
 return FatJet_btagDDCvL_;
}

const float * hhtree::FatJet_btagHbb() 
{
 if(not FatJet_btagHbb_isLoaded)
 {
   if(FatJet_btagHbb_branch != 0) FatJet_btagHbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_btagHbb_branch does not exist!\n");
exit(1);
   }
   FatJet_btagHbb_isLoaded = true;
 }
 return FatJet_btagHbb_;
}

const float * hhtree::FatJet_dRLep() 
{
 if(not FatJet_dRLep_isLoaded)
 {
   if(FatJet_dRLep_branch != 0) FatJet_dRLep_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_dRLep_branch does not exist!\n");
exit(1);
   }
   FatJet_dRLep_isLoaded = true;
 }
 return FatJet_dRLep_;
}

const float * hhtree::FatJet_deepTagHbb() 
{
 if(not FatJet_deepTagHbb_isLoaded)
 {
   if(FatJet_deepTagHbb_branch != 0) FatJet_deepTagHbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagHbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagHbb_isLoaded = true;
 }
 return FatJet_deepTagHbb_;
}

const float * hhtree::FatJet_deepTagHcc() 
{
 if(not FatJet_deepTagHcc_isLoaded)
 {
   if(FatJet_deepTagHcc_branch != 0) FatJet_deepTagHcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagHcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagHcc_isLoaded = true;
 }
 return FatJet_deepTagHcc_;
}

const float * hhtree::FatJet_deepTagHqqqq() 
{
 if(not FatJet_deepTagHqqqq_isLoaded)
 {
   if(FatJet_deepTagHqqqq_branch != 0) FatJet_deepTagHqqqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagHqqqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagHqqqq_isLoaded = true;
 }
 return FatJet_deepTagHqqqq_;
}

const float * hhtree::FatJet_deepTagMDHbb() 
{
 if(not FatJet_deepTagMDHbb_isLoaded)
 {
   if(FatJet_deepTagMDHbb_branch != 0) FatJet_deepTagMDHbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDHbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDHbb_isLoaded = true;
 }
 return FatJet_deepTagMDHbb_;
}

const float * hhtree::FatJet_deepTagMDHcc() 
{
 if(not FatJet_deepTagMDHcc_isLoaded)
 {
   if(FatJet_deepTagMDHcc_branch != 0) FatJet_deepTagMDHcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDHcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDHcc_isLoaded = true;
 }
 return FatJet_deepTagMDHcc_;
}

const float * hhtree::FatJet_deepTagMDHqqqq() 
{
 if(not FatJet_deepTagMDHqqqq_isLoaded)
 {
   if(FatJet_deepTagMDHqqqq_branch != 0) FatJet_deepTagMDHqqqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDHqqqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDHqqqq_isLoaded = true;
 }
 return FatJet_deepTagMDHqqqq_;
}

const float * hhtree::FatJet_deepTagMDQCDbb() 
{
 if(not FatJet_deepTagMDQCDbb_isLoaded)
 {
   if(FatJet_deepTagMDQCDbb_branch != 0) FatJet_deepTagMDQCDbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDQCDbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDQCDbb_isLoaded = true;
 }
 return FatJet_deepTagMDQCDbb_;
}

const float * hhtree::FatJet_deepTagMDQCDcc() 
{
 if(not FatJet_deepTagMDQCDcc_isLoaded)
 {
   if(FatJet_deepTagMDQCDcc_branch != 0) FatJet_deepTagMDQCDcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDQCDcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDQCDcc_isLoaded = true;
 }
 return FatJet_deepTagMDQCDcc_;
}

const float * hhtree::FatJet_deepTagMDWcq() 
{
 if(not FatJet_deepTagMDWcq_isLoaded)
 {
   if(FatJet_deepTagMDWcq_branch != 0) FatJet_deepTagMDWcq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDWcq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDWcq_isLoaded = true;
 }
 return FatJet_deepTagMDWcq_;
}

const float * hhtree::FatJet_deepTagMDWqq() 
{
 if(not FatJet_deepTagMDWqq_isLoaded)
 {
   if(FatJet_deepTagMDWqq_branch != 0) FatJet_deepTagMDWqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDWqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDWqq_isLoaded = true;
 }
 return FatJet_deepTagMDWqq_;
}

const float * hhtree::FatJet_deepTagMDZbb() 
{
 if(not FatJet_deepTagMDZbb_isLoaded)
 {
   if(FatJet_deepTagMDZbb_branch != 0) FatJet_deepTagMDZbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDZbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDZbb_isLoaded = true;
 }
 return FatJet_deepTagMDZbb_;
}

const float * hhtree::FatJet_deepTagMDZcc() 
{
 if(not FatJet_deepTagMDZcc_isLoaded)
 {
   if(FatJet_deepTagMDZcc_branch != 0) FatJet_deepTagMDZcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDZcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDZcc_isLoaded = true;
 }
 return FatJet_deepTagMDZcc_;
}

const float * hhtree::FatJet_deepTagMDZqq() 
{
 if(not FatJet_deepTagMDZqq_isLoaded)
 {
   if(FatJet_deepTagMDZqq_branch != 0) FatJet_deepTagMDZqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagMDZqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagMDZqq_isLoaded = true;
 }
 return FatJet_deepTagMDZqq_;
}

const float * hhtree::FatJet_deepTagQCDbb() 
{
 if(not FatJet_deepTagQCDbb_isLoaded)
 {
   if(FatJet_deepTagQCDbb_branch != 0) FatJet_deepTagQCDbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagQCDbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagQCDbb_isLoaded = true;
 }
 return FatJet_deepTagQCDbb_;
}

const float * hhtree::FatJet_deepTagQCDcc() 
{
 if(not FatJet_deepTagQCDcc_isLoaded)
 {
   if(FatJet_deepTagQCDcc_branch != 0) FatJet_deepTagQCDcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagQCDcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagQCDcc_isLoaded = true;
 }
 return FatJet_deepTagQCDcc_;
}

const float * hhtree::FatJet_deepTagWcq() 
{
 if(not FatJet_deepTagWcq_isLoaded)
 {
   if(FatJet_deepTagWcq_branch != 0) FatJet_deepTagWcq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagWcq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagWcq_isLoaded = true;
 }
 return FatJet_deepTagWcq_;
}

const float * hhtree::FatJet_deepTagWqq() 
{
 if(not FatJet_deepTagWqq_isLoaded)
 {
   if(FatJet_deepTagWqq_branch != 0) FatJet_deepTagWqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagWqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagWqq_isLoaded = true;
 }
 return FatJet_deepTagWqq_;
}

const float * hhtree::FatJet_deepTagZbb() 
{
 if(not FatJet_deepTagZbb_isLoaded)
 {
   if(FatJet_deepTagZbb_branch != 0) FatJet_deepTagZbb_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagZbb_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagZbb_isLoaded = true;
 }
 return FatJet_deepTagZbb_;
}

const float * hhtree::FatJet_deepTagZcc() 
{
 if(not FatJet_deepTagZcc_isLoaded)
 {
   if(FatJet_deepTagZcc_branch != 0) FatJet_deepTagZcc_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagZcc_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagZcc_isLoaded = true;
 }
 return FatJet_deepTagZcc_;
}

const float * hhtree::FatJet_deepTagZqq() 
{
 if(not FatJet_deepTagZqq_isLoaded)
 {
   if(FatJet_deepTagZqq_branch != 0) FatJet_deepTagZqq_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_deepTagZqq_branch does not exist!\n");
exit(1);
   }
   FatJet_deepTagZqq_isLoaded = true;
 }
 return FatJet_deepTagZqq_;
}

const float * hhtree::FatJet_eta() 
{
 if(not FatJet_eta_isLoaded)
 {
   if(FatJet_eta_branch != 0) FatJet_eta_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_eta_branch does not exist!\n");
exit(1);
   }
   FatJet_eta_isLoaded = true;
 }
 return FatJet_eta_;
}

const float * hhtree::FatJet_lsf3() 
{
 if(not FatJet_lsf3_isLoaded)
 {
   if(FatJet_lsf3_branch != 0) FatJet_lsf3_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_lsf3_branch does not exist!\n");
exit(1);
   }
   FatJet_lsf3_isLoaded = true;
 }
 return FatJet_lsf3_;
}

const float * hhtree::FatJet_mass() 
{
 if(not FatJet_mass_isLoaded)
 {
   if(FatJet_mass_branch != 0) FatJet_mass_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_mass_branch does not exist!\n");
exit(1);
   }
   FatJet_mass_isLoaded = true;
 }
 return FatJet_mass_;
}

const float * hhtree::FatJet_msoftdrop() 
{
 if(not FatJet_msoftdrop_isLoaded)
 {
   if(FatJet_msoftdrop_branch != 0) FatJet_msoftdrop_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_msoftdrop_branch does not exist!\n");
exit(1);
   }
   FatJet_msoftdrop_isLoaded = true;
 }
 return FatJet_msoftdrop_;
}

const float * hhtree::FatJet_n2b1() 
{
 if(not FatJet_n2b1_isLoaded)
 {
   if(FatJet_n2b1_branch != 0) FatJet_n2b1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_n2b1_branch does not exist!\n");
exit(1);
   }
   FatJet_n2b1_isLoaded = true;
 }
 return FatJet_n2b1_;
}

const float * hhtree::FatJet_n3b1() 
{
 if(not FatJet_n3b1_isLoaded)
 {
   if(FatJet_n3b1_branch != 0) FatJet_n3b1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_n3b1_branch does not exist!\n");
exit(1);
   }
   FatJet_n3b1_isLoaded = true;
 }
 return FatJet_n3b1_;
}

const float * hhtree::FatJet_phi() 
{
 if(not FatJet_phi_isLoaded)
 {
   if(FatJet_phi_branch != 0) FatJet_phi_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_phi_branch does not exist!\n");
exit(1);
   }
   FatJet_phi_isLoaded = true;
 }
 return FatJet_phi_;
}

const float * hhtree::FatJet_pt() 
{
 if(not FatJet_pt_isLoaded)
 {
   if(FatJet_pt_branch != 0) FatJet_pt_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_pt_branch does not exist!\n");
exit(1);
   }
   FatJet_pt_isLoaded = true;
 }
 return FatJet_pt_;
}

const float * hhtree::FatJet_rawFactor() 
{
 if(not FatJet_rawFactor_isLoaded)
 {
   if(FatJet_rawFactor_branch != 0) FatJet_rawFactor_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_rawFactor_branch does not exist!\n");
exit(1);
   }
   FatJet_rawFactor_isLoaded = true;
 }
 return FatJet_rawFactor_;
}

const float * hhtree::FatJet_rawmsoftdrop() 
{
 if(not FatJet_rawmsoftdrop_isLoaded)
 {
   if(FatJet_rawmsoftdrop_branch != 0) FatJet_rawmsoftdrop_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_rawmsoftdrop_branch does not exist!\n");
exit(1);
   }
   FatJet_rawmsoftdrop_isLoaded = true;
 }
 return FatJet_rawmsoftdrop_;
}

const float * hhtree::FatJet_tau1() 
{
 if(not FatJet_tau1_isLoaded)
 {
   if(FatJet_tau1_branch != 0) FatJet_tau1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_tau1_branch does not exist!\n");
exit(1);
   }
   FatJet_tau1_isLoaded = true;
 }
 return FatJet_tau1_;
}

const float * hhtree::FatJet_tau2() 
{
 if(not FatJet_tau2_isLoaded)
 {
   if(FatJet_tau2_branch != 0) FatJet_tau2_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_tau2_branch does not exist!\n");
exit(1);
   }
   FatJet_tau2_isLoaded = true;
 }
 return FatJet_tau2_;
}

const float * hhtree::FatJet_tau3() 
{
 if(not FatJet_tau3_isLoaded)
 {
   if(FatJet_tau3_branch != 0) FatJet_tau3_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_tau3_branch does not exist!\n");
exit(1);
   }
   FatJet_tau3_isLoaded = true;
 }
 return FatJet_tau3_;
}

const float * hhtree::FatJet_tau4() 
{
 if(not FatJet_tau4_isLoaded)
 {
   if(FatJet_tau4_branch != 0) FatJet_tau4_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_tau4_branch does not exist!\n");
exit(1);
   }
   FatJet_tau4_isLoaded = true;
 }
 return FatJet_tau4_;
}

const int * hhtree::FatJet_electronIdx3SJ() 
{
 if(not FatJet_electronIdx3SJ_isLoaded)
 {
   if(FatJet_electronIdx3SJ_branch != 0) FatJet_electronIdx3SJ_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_electronIdx3SJ_branch does not exist!\n");
exit(1);
   }
   FatJet_electronIdx3SJ_isLoaded = true;
 }
 return FatJet_electronIdx3SJ_;
}

const int * hhtree::FatJet_idLep() 
{
 if(not FatJet_idLep_isLoaded)
 {
   if(FatJet_idLep_branch != 0) FatJet_idLep_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_idLep_branch does not exist!\n");
exit(1);
   }
   FatJet_idLep_isLoaded = true;
 }
 return FatJet_idLep_;
}

const int * hhtree::FatJet_jetId() 
{
 if(not FatJet_jetId_isLoaded)
 {
   if(FatJet_jetId_branch != 0) FatJet_jetId_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_jetId_branch does not exist!\n");
exit(1);
   }
   FatJet_jetId_isLoaded = true;
 }
 return FatJet_jetId_;
}

const int * hhtree::FatJet_muonIdx3SJ() 
{
 if(not FatJet_muonIdx3SJ_isLoaded)
 {
   if(FatJet_muonIdx3SJ_branch != 0) FatJet_muonIdx3SJ_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_muonIdx3SJ_branch does not exist!\n");
exit(1);
   }
   FatJet_muonIdx3SJ_isLoaded = true;
 }
 return FatJet_muonIdx3SJ_;
}

const int * hhtree::FatJet_nBHadrons() 
{
 if(not FatJet_nBHadrons_isLoaded)
 {
   if(FatJet_nBHadrons_branch != 0) FatJet_nBHadrons_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_nBHadrons_branch does not exist!\n");
exit(1);
   }
   FatJet_nBHadrons_isLoaded = true;
 }
 return FatJet_nBHadrons_;
}

const int * hhtree::FatJet_nCHadrons() 
{
 if(not FatJet_nCHadrons_isLoaded)
 {
   if(FatJet_nCHadrons_branch != 0) FatJet_nCHadrons_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_nCHadrons_branch does not exist!\n");
exit(1);
   }
   FatJet_nCHadrons_isLoaded = true;
 }
 return FatJet_nCHadrons_;
}

const int * hhtree::FatJet_nPFConstituents() 
{
 if(not FatJet_nPFConstituents_isLoaded)
 {
   if(FatJet_nPFConstituents_branch != 0) FatJet_nPFConstituents_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_nPFConstituents_branch does not exist!\n");
exit(1);
   }
   FatJet_nPFConstituents_isLoaded = true;
 }
 return FatJet_nPFConstituents_;
}

const int * hhtree::FatJet_subJetIdx1() 
{
 if(not FatJet_subJetIdx1_isLoaded)
 {
   if(FatJet_subJetIdx1_branch != 0) FatJet_subJetIdx1_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_subJetIdx1_branch does not exist!\n");
exit(1);
   }
   FatJet_subJetIdx1_isLoaded = true;
 }
 return FatJet_subJetIdx1_;
}

const int * hhtree::FatJet_subJetIdx2() 
{
 if(not FatJet_subJetIdx2_isLoaded)
 {
   if(FatJet_subJetIdx2_branch != 0) FatJet_subJetIdx2_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_subJetIdx2_branch does not exist!\n");
exit(1);
   }
   FatJet_subJetIdx2_isLoaded = true;
 }
 return FatJet_subJetIdx2_;
}

const bool * hhtree::FatJet_Hmatch() 
{
 if(not FatJet_Hmatch_isLoaded)
 {
   if(FatJet_Hmatch_branch != 0) FatJet_Hmatch_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_Hmatch_branch does not exist!\n");
exit(1);
   }
   FatJet_Hmatch_isLoaded = true;
 }
 return FatJet_Hmatch_;
}

const int * hhtree::FatJet_HgenIdx() 
{
 if(not FatJet_HgenIdx_isLoaded)
 {
   if(FatJet_HgenIdx_branch != 0) FatJet_HgenIdx_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_HgenIdx_branch does not exist!\n");
exit(1);
   }
   FatJet_HgenIdx_isLoaded = true;
 }
 return FatJet_HgenIdx_;
}

const float * hhtree::FatJet_HminDR() 
{
 if(not FatJet_HminDR_isLoaded)
 {
   if(FatJet_HminDR_branch != 0) FatJet_HminDR_branch->GetEntry(index);
   else
   {
     printf("branch FatJet_HminDR_branch does not exist!\n");
exit(1);
   }
   FatJet_HminDR_isLoaded = true;
 }
 return FatJet_HminDR_;
}

const bool &hhtree::HLT_PFHT1050() 
{
 if(not HLT_PFHT1050_isLoaded)
 {
   if(HLT_PFHT1050_branch != 0) HLT_PFHT1050_branch->GetEntry(index);
   else
   {
     printf("branch HLT_PFHT1050_branch does not exist!\n");
exit(1);
   }
   HLT_PFHT1050_isLoaded = true;
 }
 return HLT_PFHT1050_;
}

const bool &hhtree::HLT_AK8PFJet360_TrimMass30() 
{
 if(not HLT_AK8PFJet360_TrimMass30_isLoaded)
 {
   if(HLT_AK8PFJet360_TrimMass30_branch != 0) HLT_AK8PFJet360_TrimMass30_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet360_TrimMass30_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet360_TrimMass30_isLoaded = true;
 }
 return HLT_AK8PFJet360_TrimMass30_;
}

const bool &hhtree::HLT_AK8PFJet380_TrimMass30() 
{
 if(not HLT_AK8PFJet380_TrimMass30_isLoaded)
 {
   if(HLT_AK8PFJet380_TrimMass30_branch != 0) HLT_AK8PFJet380_TrimMass30_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet380_TrimMass30_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet380_TrimMass30_isLoaded = true;
 }
 return HLT_AK8PFJet380_TrimMass30_;
}

const bool &hhtree::HLT_AK8PFJet400_TrimMass30() 
{
 if(not HLT_AK8PFJet400_TrimMass30_isLoaded)
 {
   if(HLT_AK8PFJet400_TrimMass30_branch != 0) HLT_AK8PFJet400_TrimMass30_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet400_TrimMass30_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet400_TrimMass30_isLoaded = true;
 }
 return HLT_AK8PFJet400_TrimMass30_;
}

const bool &hhtree::HLT_AK8PFJet420_TrimMass30() 
{
 if(not HLT_AK8PFJet420_TrimMass30_isLoaded)
 {
   if(HLT_AK8PFJet420_TrimMass30_branch != 0) HLT_AK8PFJet420_TrimMass30_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet420_TrimMass30_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet420_TrimMass30_isLoaded = true;
 }
 return HLT_AK8PFJet420_TrimMass30_;
}

const bool &hhtree::HLT_AK8PFHT800_TrimMass50() 
{
 if(not HLT_AK8PFHT800_TrimMass50_isLoaded)
 {
   if(HLT_AK8PFHT800_TrimMass50_branch != 0) HLT_AK8PFHT800_TrimMass50_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFHT800_TrimMass50_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFHT800_TrimMass50_isLoaded = true;
 }
 return HLT_AK8PFHT800_TrimMass50_;
}

const bool &hhtree::HLT_PFJet500() 
{
 if(not HLT_PFJet500_isLoaded)
 {
   if(HLT_PFJet500_branch != 0) HLT_PFJet500_branch->GetEntry(index);
   else
   {
     printf("branch HLT_PFJet500_branch does not exist!\n");
exit(1);
   }
   HLT_PFJet500_isLoaded = true;
 }
 return HLT_PFJet500_;
}

const bool &hhtree::HLT_AK8PFJet500() 
{
 if(not HLT_AK8PFJet500_isLoaded)
 {
   if(HLT_AK8PFJet500_branch != 0) HLT_AK8PFJet500_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet500_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet500_isLoaded = true;
 }
 return HLT_AK8PFJet500_;
}

const bool &hhtree::HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17() 
{
 if(not HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_isLoaded)
 {
   if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch != 0) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_isLoaded = true;
 }
 return HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_;
}

const bool &hhtree::HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1() 
{
 if(not HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_isLoaded)
 {
   if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch != 0) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_isLoaded = true;
 }
 return HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_;
}

const bool &hhtree::HLT_AK8PFJet330_PFAK8BTagCSV_p17() 
{
 if(not HLT_AK8PFJet330_PFAK8BTagCSV_p17_isLoaded)
 {
   if(HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch != 0) HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_PFAK8BTagCSV_p17_isLoaded = true;
 }
 return HLT_AK8PFJet330_PFAK8BTagCSV_p17_;
}

const float &hhtree::hh_pt() 
{
 if(not hh_pt_isLoaded)
 {
   if(hh_pt_branch != 0) hh_pt_branch->GetEntry(index);
   else
   {
     printf("branch hh_pt_branch does not exist!\n");
exit(1);
   }
   hh_pt_isLoaded = true;
 }
 return hh_pt_;
}

const float &hhtree::hh_eta() 
{
 if(not hh_eta_isLoaded)
 {
   if(hh_eta_branch != 0) hh_eta_branch->GetEntry(index);
   else
   {
     printf("branch hh_eta_branch does not exist!\n");
exit(1);
   }
   hh_eta_isLoaded = true;
 }
 return hh_eta_;
}

const float &hhtree::hh_phi() 
{
 if(not hh_phi_isLoaded)
 {
   if(hh_phi_branch != 0) hh_phi_branch->GetEntry(index);
   else
   {
     printf("branch hh_phi_branch does not exist!\n");
exit(1);
   }
   hh_phi_isLoaded = true;
 }
 return hh_phi_;
}

const float &hhtree::hh_mass() 
{
 if(not hh_mass_isLoaded)
 {
   if(hh_mass_branch != 0) hh_mass_branch->GetEntry(index);
   else
   {
     printf("branch hh_mass_branch does not exist!\n");
exit(1);
   }
   hh_mass_isLoaded = true;
 }
 return hh_mass_;
}

const float &hhtree::hh_gen_pt() 
{
 if(not hh_gen_pt_isLoaded)
 {
   if(hh_gen_pt_branch != 0) hh_gen_pt_branch->GetEntry(index);
   else
   {
     printf("branch hh_gen_pt_branch does not exist!\n");
exit(1);
   }
   hh_gen_pt_isLoaded = true;
 }
 return hh_gen_pt_;
}

const float &hhtree::hh_gen_eta() 
{
 if(not hh_gen_eta_isLoaded)
 {
   if(hh_gen_eta_branch != 0) hh_gen_eta_branch->GetEntry(index);
   else
   {
     printf("branch hh_gen_eta_branch does not exist!\n");
exit(1);
   }
   hh_gen_eta_isLoaded = true;
 }
 return hh_gen_eta_;
}

const float &hhtree::hh_gen_phi() 
{
 if(not hh_gen_phi_isLoaded)
 {
   if(hh_gen_phi_branch != 0) hh_gen_phi_branch->GetEntry(index);
   else
   {
     printf("branch hh_gen_phi_branch does not exist!\n");
exit(1);
   }
   hh_gen_phi_isLoaded = true;
 }
 return hh_gen_phi_;
}

const float &hhtree::hh_gen_mass() 
{
 if(not hh_gen_mass_isLoaded)
 {
   if(hh_gen_mass_branch != 0) hh_gen_mass_branch->GetEntry(index);
   else
   {
     printf("branch hh_gen_mass_branch does not exist!\n");
exit(1);
   }
   hh_gen_mass_isLoaded = true;
 }
 return hh_gen_mass_;
}

const float &hhtree::weight() 
{
 if(not weight_isLoaded)
 {
   if(weight_branch != 0) weight_branch->GetEntry(index);
   else
   {
     printf("branch weight_branch does not exist!\n");
exit(1);
   }
   weight_isLoaded = true;
 }
 return weight_;
}

