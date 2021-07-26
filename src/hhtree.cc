#include "hhtree.hh"
hhtree hh; 

void hhtree::Init(TTree *tree) 
{

 runNumber_branch = tree->GetBranch("runNumber");
 if(runNumber_branch) runNumber_branch->SetAddress(&runNumber_);
 RunNumber_branch = tree->GetBranch("RunNumber");
 if(RunNumber_branch) RunNumber_branch->SetAddress(&RunNumber_);
 m_mcChannelNumber_branch = tree->GetBranch("m_mcChannelNumber");
 if(m_mcChannelNumber_branch) m_mcChannelNumber_branch->SetAddress(&m_mcChannelNumber_);
 eventNumber_branch = tree->GetBranch("eventNumber");
 if(eventNumber_branch) eventNumber_branch->SetAddress(&eventNumber_);
 mcweight_branch = tree->GetBranch("mcweight");
 if(mcweight_branch) mcweight_branch->SetAddress(&mcweight_);
 m_weight_branch = tree->GetBranch("m_weight");
 if(m_weight_branch) m_weight_branch->SetAddress(&m_weight_);
 n_ph_branch = tree->GetBranch("n_ph");
 if(n_ph_branch) n_ph_branch->SetAddress(&n_ph_);
 n_el_branch = tree->GetBranch("n_el");
 if(n_el_branch) n_el_branch->SetAddress(&n_el_);
 n_mu_branch = tree->GetBranch("n_mu");
 if(n_mu_branch) n_mu_branch->SetAddress(&n_mu_);
 n_tau_branch = tree->GetBranch("n_tau");
 if(n_tau_branch) n_tau_branch->SetAddress(&n_tau_);
 n_top_branch = tree->GetBranch("n_top");
 if(n_top_branch) n_top_branch->SetAddress(&n_top_);
 n_b_branch = tree->GetBranch("n_b");
 if(n_b_branch) n_b_branch->SetAddress(&n_b_);
 n_jet_branch = tree->GetBranch("n_jet");
 if(n_jet_branch) n_jet_branch->SetAddress(&n_jet_);
 n_bjet_branch = tree->GetBranch("n_bjet");
 if(n_bjet_branch) n_bjet_branch->SetAddress(&n_bjet_);
 m_mgg_branch = tree->GetBranch("m_mgg");
 if(m_mgg_branch) m_mgg_branch->SetAddress(&m_mgg_);
 tru_n_muel_branch = tree->GetBranch("tru_n_muel");
 if(tru_n_muel_branch) tru_n_muel_branch->SetAddress(&tru_n_muel_);
 n_lep_branch = tree->GetBranch("n_lep");
 if(n_lep_branch) n_lep_branch->SetAddress(&n_lep_);
 lep_q_1_branch = tree->GetBranch("lep_q_1");
 if(lep_q_1_branch) lep_q_1_branch->SetAddress(&lep_q_1_);
 lep_q_2_branch = tree->GetBranch("lep_q_2");
 if(lep_q_2_branch) lep_q_2_branch->SetAddress(&lep_q_2_);
 lep_E_1_branch = tree->GetBranch("lep_E_1");
 if(lep_E_1_branch) lep_E_1_branch->SetAddress(&lep_E_1_);
 lep_E_2_branch = tree->GetBranch("lep_E_2");
 if(lep_E_2_branch) lep_E_2_branch->SetAddress(&lep_E_2_);
 lep_pt_1_branch = tree->GetBranch("lep_pt_1");
 if(lep_pt_1_branch) lep_pt_1_branch->SetAddress(&lep_pt_1_);
 lep_pt_2_branch = tree->GetBranch("lep_pt_2");
 if(lep_pt_2_branch) lep_pt_2_branch->SetAddress(&lep_pt_2_);
 lep_pt_3_branch = tree->GetBranch("lep_pt_3");
 if(lep_pt_3_branch) lep_pt_3_branch->SetAddress(&lep_pt_3_);
 lep_eta_1_branch = tree->GetBranch("lep_eta_1");
 if(lep_eta_1_branch) lep_eta_1_branch->SetAddress(&lep_eta_1_);
 lep_eta_2_branch = tree->GetBranch("lep_eta_2");
 if(lep_eta_2_branch) lep_eta_2_branch->SetAddress(&lep_eta_2_);
 lep_phi_1_branch = tree->GetBranch("lep_phi_1");
 if(lep_phi_1_branch) lep_phi_1_branch->SetAddress(&lep_phi_1_);
 lep_phi_2_branch = tree->GetBranch("lep_phi_2");
 if(lep_phi_2_branch) lep_phi_2_branch->SetAddress(&lep_phi_2_);
 ph_pt1_branch = tree->GetBranch("ph_pt1");
 if(ph_pt1_branch) ph_pt1_branch->SetAddress(&ph_pt1_);
 ph_eta1_branch = tree->GetBranch("ph_eta1");
 if(ph_eta1_branch) ph_eta1_branch->SetAddress(&ph_eta1_);
 ph_phi1_branch = tree->GetBranch("ph_phi1");
 if(ph_phi1_branch) ph_phi1_branch->SetAddress(&ph_phi1_);
 ph_E1_branch = tree->GetBranch("ph_E1");
 if(ph_E1_branch) ph_E1_branch->SetAddress(&ph_E1_);
 ph_parent1_branch = tree->GetBranch("ph_parent1");
 if(ph_parent1_branch) ph_parent1_branch->SetAddress(&ph_parent1_);
 ph_pt2_branch = tree->GetBranch("ph_pt2");
 if(ph_pt2_branch) ph_pt2_branch->SetAddress(&ph_pt2_);
 ph_eta2_branch = tree->GetBranch("ph_eta2");
 if(ph_eta2_branch) ph_eta2_branch->SetAddress(&ph_eta2_);
 ph_phi2_branch = tree->GetBranch("ph_phi2");
 if(ph_phi2_branch) ph_phi2_branch->SetAddress(&ph_phi2_);
 ph_E2_branch = tree->GetBranch("ph_E2");
 if(ph_E2_branch) ph_E2_branch->SetAddress(&ph_E2_);
 ph_parent2_branch = tree->GetBranch("ph_parent2");
 if(ph_parent2_branch) ph_parent2_branch->SetAddress(&ph_parent2_);
 ph_pt3_branch = tree->GetBranch("ph_pt3");
 if(ph_pt3_branch) ph_pt3_branch->SetAddress(&ph_pt3_);
 ph_eta3_branch = tree->GetBranch("ph_eta3");
 if(ph_eta3_branch) ph_eta3_branch->SetAddress(&ph_eta3_);
 ph_phi3_branch = tree->GetBranch("ph_phi3");
 if(ph_phi3_branch) ph_phi3_branch->SetAddress(&ph_phi3_);
 ph_parent3_branch = tree->GetBranch("ph_parent3");
 if(ph_parent3_branch) ph_parent3_branch->SetAddress(&ph_parent3_);
 bjet_pt_1_branch = tree->GetBranch("bjet_pt_1");
 if(bjet_pt_1_branch) bjet_pt_1_branch->SetAddress(&bjet_pt_1_);
 bjet_pt_2_branch = tree->GetBranch("bjet_pt_2");
 if(bjet_pt_2_branch) bjet_pt_2_branch->SetAddress(&bjet_pt_2_);
 bjet_pt_3_branch = tree->GetBranch("bjet_pt_3");
 if(bjet_pt_3_branch) bjet_pt_3_branch->SetAddress(&bjet_pt_3_);
 jet0_pt_1_branch = tree->GetBranch("jet0_pt_1");
 if(jet0_pt_1_branch) jet0_pt_1_branch->SetAddress(&jet0_pt_1_);
 jet0_pt_2_branch = tree->GetBranch("jet0_pt_2");
 if(jet0_pt_2_branch) jet0_pt_2_branch->SetAddress(&jet0_pt_2_);
 jet0_pt_3_branch = tree->GetBranch("jet0_pt_3");
 if(jet0_pt_3_branch) jet0_pt_3_branch->SetAddress(&jet0_pt_3_);
 jet0_pt_4_branch = tree->GetBranch("jet0_pt_4");
 if(jet0_pt_4_branch) jet0_pt_4_branch->SetAddress(&jet0_pt_4_);
 jet0_pt_5_branch = tree->GetBranch("jet0_pt_5");
 if(jet0_pt_5_branch) jet0_pt_5_branch->SetAddress(&jet0_pt_5_);
 jet0_pt_6_branch = tree->GetBranch("jet0_pt_6");
 if(jet0_pt_6_branch) jet0_pt_6_branch->SetAddress(&jet0_pt_6_);
 jet0_pt_7_branch = tree->GetBranch("jet0_pt_7");
 if(jet0_pt_7_branch) jet0_pt_7_branch->SetAddress(&jet0_pt_7_);
 jet0_pt_8_branch = tree->GetBranch("jet0_pt_8");
 if(jet0_pt_8_branch) jet0_pt_8_branch->SetAddress(&jet0_pt_8_);
 jet0_eta_1_branch = tree->GetBranch("jet0_eta_1");
 if(jet0_eta_1_branch) jet0_eta_1_branch->SetAddress(&jet0_eta_1_);
 jet0_eta_2_branch = tree->GetBranch("jet0_eta_2");
 if(jet0_eta_2_branch) jet0_eta_2_branch->SetAddress(&jet0_eta_2_);
 jet0_eta_3_branch = tree->GetBranch("jet0_eta_3");
 if(jet0_eta_3_branch) jet0_eta_3_branch->SetAddress(&jet0_eta_3_);
 jet0_eta_4_branch = tree->GetBranch("jet0_eta_4");
 if(jet0_eta_4_branch) jet0_eta_4_branch->SetAddress(&jet0_eta_4_);
 jet0_eta_5_branch = tree->GetBranch("jet0_eta_5");
 if(jet0_eta_5_branch) jet0_eta_5_branch->SetAddress(&jet0_eta_5_);
 jet0_eta_6_branch = tree->GetBranch("jet0_eta_6");
 if(jet0_eta_6_branch) jet0_eta_6_branch->SetAddress(&jet0_eta_6_);
 jet0_eta_7_branch = tree->GetBranch("jet0_eta_7");
 if(jet0_eta_7_branch) jet0_eta_7_branch->SetAddress(&jet0_eta_7_);
 jet0_eta_8_branch = tree->GetBranch("jet0_eta_8");
 if(jet0_eta_8_branch) jet0_eta_8_branch->SetAddress(&jet0_eta_8_);
 jet0_phi_1_branch = tree->GetBranch("jet0_phi_1");
 if(jet0_phi_1_branch) jet0_phi_1_branch->SetAddress(&jet0_phi_1_);
 jet0_phi_2_branch = tree->GetBranch("jet0_phi_2");
 if(jet0_phi_2_branch) jet0_phi_2_branch->SetAddress(&jet0_phi_2_);
 jet0_phi_3_branch = tree->GetBranch("jet0_phi_3");
 if(jet0_phi_3_branch) jet0_phi_3_branch->SetAddress(&jet0_phi_3_);
 jet0_phi_4_branch = tree->GetBranch("jet0_phi_4");
 if(jet0_phi_4_branch) jet0_phi_4_branch->SetAddress(&jet0_phi_4_);
 jet0_phi_5_branch = tree->GetBranch("jet0_phi_5");
 if(jet0_phi_5_branch) jet0_phi_5_branch->SetAddress(&jet0_phi_5_);
 jet0_phi_6_branch = tree->GetBranch("jet0_phi_6");
 if(jet0_phi_6_branch) jet0_phi_6_branch->SetAddress(&jet0_phi_6_);
 jet0_phi_7_branch = tree->GetBranch("jet0_phi_7");
 if(jet0_phi_7_branch) jet0_phi_7_branch->SetAddress(&jet0_phi_7_);
 jet0_phi_8_branch = tree->GetBranch("jet0_phi_8");
 if(jet0_phi_8_branch) jet0_phi_8_branch->SetAddress(&jet0_phi_8_);
 b_pt1_branch = tree->GetBranch("b_pt1");
 if(b_pt1_branch) b_pt1_branch->SetAddress(&b_pt1_);
 b_eta1_branch = tree->GetBranch("b_eta1");
 if(b_eta1_branch) b_eta1_branch->SetAddress(&b_eta1_);
 b_phi1_branch = tree->GetBranch("b_phi1");
 if(b_phi1_branch) b_phi1_branch->SetAddress(&b_phi1_);
 b_pt2_branch = tree->GetBranch("b_pt2");
 if(b_pt2_branch) b_pt2_branch->SetAddress(&b_pt2_);
 b_eta2_branch = tree->GetBranch("b_eta2");
 if(b_eta2_branch) b_eta2_branch->SetAddress(&b_eta2_);
 b_phi2_branch = tree->GetBranch("b_phi2");
 if(b_phi2_branch) b_phi2_branch->SetAddress(&b_phi2_);
 b_pt3_branch = tree->GetBranch("b_pt3");
 if(b_pt3_branch) b_pt3_branch->SetAddress(&b_pt3_);
 b_eta3_branch = tree->GetBranch("b_eta3");
 if(b_eta3_branch) b_eta3_branch->SetAddress(&b_eta3_);
 b_phi3_branch = tree->GetBranch("b_phi3");
 if(b_phi3_branch) b_phi3_branch->SetAddress(&b_phi3_);
 ph_pt_branch = tree->GetBranch("ph_pt");
 if(ph_pt_branch) ph_pt_branch->SetAddress(&ph_pt_);
 ph_eta_branch = tree->GetBranch("ph_eta");
 if(ph_eta_branch) ph_eta_branch->SetAddress(&ph_eta_);
 ph_phi_branch = tree->GetBranch("ph_phi");
 if(ph_phi_branch) ph_phi_branch->SetAddress(&ph_phi_);
 ph_parent_id_branch = tree->GetBranch("ph_parent_id");
 if(ph_parent_id_branch) ph_parent_id_branch->SetAddress(&ph_parent_id_);
 m_el_pt_branch = tree->GetBranch("m_el_pt");
 if(m_el_pt_branch) m_el_pt_branch->SetAddress(&m_el_pt_);
 m_el_eta_branch = tree->GetBranch("m_el_eta");
 if(m_el_eta_branch) m_el_eta_branch->SetAddress(&m_el_eta_);
 m_el_phi_branch = tree->GetBranch("m_el_phi");
 if(m_el_phi_branch) m_el_phi_branch->SetAddress(&m_el_phi_);
 m_el_E_branch = tree->GetBranch("m_el_E");
 if(m_el_E_branch) m_el_E_branch->SetAddress(&m_el_E_);
 m_el_pdg_branch = tree->GetBranch("m_el_pdg");
 if(m_el_pdg_branch) m_el_pdg_branch->SetAddress(&m_el_pdg_);
 m_mu_pt_branch = tree->GetBranch("m_mu_pt");
 if(m_mu_pt_branch) m_mu_pt_branch->SetAddress(&m_mu_pt_);
 m_mu_eta_branch = tree->GetBranch("m_mu_eta");
 if(m_mu_eta_branch) m_mu_eta_branch->SetAddress(&m_mu_eta_);
 m_mu_phi_branch = tree->GetBranch("m_mu_phi");
 if(m_mu_phi_branch) m_mu_phi_branch->SetAddress(&m_mu_phi_);
 m_mu_E_branch = tree->GetBranch("m_mu_E");
 if(m_mu_E_branch) m_mu_E_branch->SetAddress(&m_mu_E_);
 m_mu_pdg_branch = tree->GetBranch("m_mu_pdg");
 if(m_mu_pdg_branch) m_mu_pdg_branch->SetAddress(&m_mu_pdg_);
 tau_pt_branch = tree->GetBranch("tau_pt");
 if(tau_pt_branch) tau_pt_branch->SetAddress(&tau_pt_);
 tau_eta_branch = tree->GetBranch("tau_eta");
 if(tau_eta_branch) tau_eta_branch->SetAddress(&tau_eta_);
 top_pt_branch = tree->GetBranch("top_pt");
 if(top_pt_branch) top_pt_branch->SetAddress(&top_pt_);
 top_eta_branch = tree->GetBranch("top_eta");
 if(top_eta_branch) top_eta_branch->SetAddress(&top_eta_);
 b_pt_branch = tree->GetBranch("b_pt");
 if(b_pt_branch) b_pt_branch->SetAddress(&b_pt_);
 b_eta_branch = tree->GetBranch("b_eta");
 if(b_eta_branch) b_eta_branch->SetAddress(&b_eta_);
 b_phi_branch = tree->GetBranch("b_phi");
 if(b_phi_branch) b_phi_branch->SetAddress(&b_phi_);
 m_jet_pt_branch = tree->GetBranch("m_jet_pt");
 if(m_jet_pt_branch) m_jet_pt_branch->SetAddress(&m_jet_pt_);
 m_jet_eta_branch = tree->GetBranch("m_jet_eta");
 if(m_jet_eta_branch) m_jet_eta_branch->SetAddress(&m_jet_eta_);
 m_jet_phi_branch = tree->GetBranch("m_jet_phi");
 if(m_jet_phi_branch) m_jet_phi_branch->SetAddress(&m_jet_phi_);
 m_jet_m_branch = tree->GetBranch("m_jet_m");
 if(m_jet_m_branch) m_jet_m_branch->SetAddress(&m_jet_m_);
 m_jet_btag70_branch = tree->GetBranch("m_jet_btag70");
 if(m_jet_btag70_branch) m_jet_btag70_branch->SetAddress(&m_jet_btag70_);
 m_jet_btag77_branch = tree->GetBranch("m_jet_btag77");
 if(m_jet_btag77_branch) m_jet_btag77_branch->SetAddress(&m_jet_btag77_);
 m_jet_btag60_branch = tree->GetBranch("m_jet_btag60");
 if(m_jet_btag60_branch) m_jet_btag60_branch->SetAddress(&m_jet_btag60_);
 m_jet_btag85_branch = tree->GetBranch("m_jet_btag85");
 if(m_jet_btag85_branch) m_jet_btag85_branch->SetAddress(&m_jet_btag85_);
 jet_AK4_b_tag_branch = tree->GetBranch("jet_AK4_b_tag");
 if(jet_AK4_b_tag_branch) jet_AK4_b_tag_branch->SetAddress(&jet_AK4_b_tag_);
 susy_m_branch = tree->GetBranch("susy_m");
 if(susy_m_branch) susy_m_branch->SetAddress(&susy_m_);
 susy_pt_branch = tree->GetBranch("susy_pt");
 if(susy_pt_branch) susy_pt_branch->SetAddress(&susy_pt_);
 susy_eta_branch = tree->GetBranch("susy_eta");
 if(susy_eta_branch) susy_eta_branch->SetAddress(&susy_eta_);
 susy_phi_branch = tree->GetBranch("susy_phi");
 if(susy_phi_branch) susy_phi_branch->SetAddress(&susy_phi_);
 susy_pdg_branch = tree->GetBranch("susy_pdg");
 if(susy_pdg_branch) susy_pdg_branch->SetAddress(&susy_pdg_);
 m_njet_branch = tree->GetBranch("m_njet");
 if(m_njet_branch) m_njet_branch->SetAddress(&m_njet_);
 N_j_central_branch = tree->GetBranch("N_j_central");
 if(N_j_central_branch) N_j_central_branch->SetAddress(&N_j_central_);
 m_HT_branch = tree->GetBranch("m_HT");
 if(m_HT_branch) m_HT_branch->SetAddress(&m_HT_);
 m_HT_central_branch = tree->GetBranch("m_HT_central");
 if(m_HT_central_branch) m_HT_central_branch->SetAddress(&m_HT_central_);
 m_mass_multijet_branch = tree->GetBranch("m_mass_multijet");
 if(m_mass_multijet_branch) m_mass_multijet_branch->SetAddress(&m_mass_multijet_);
 m_nbjet_fixed60_branch = tree->GetBranch("m_nbjet_fixed60");
 if(m_nbjet_fixed60_branch) m_nbjet_fixed60_branch->SetAddress(&m_nbjet_fixed60_);
 m_nbjet_fixed80_branch = tree->GetBranch("m_nbjet_fixed80");
 if(m_nbjet_fixed80_branch) m_nbjet_fixed80_branch->SetAddress(&m_nbjet_fixed80_);
 m_nbjet_fixed70_branch = tree->GetBranch("m_nbjet_fixed70");
 if(m_nbjet_fixed70_branch) m_nbjet_fixed70_branch->SetAddress(&m_nbjet_fixed70_);
 m_nbjet_fixed85_branch = tree->GetBranch("m_nbjet_fixed85");
 if(m_nbjet_fixed85_branch) m_nbjet_fixed85_branch->SetAddress(&m_nbjet_fixed85_);
 N_lep_branch = tree->GetBranch("N_lep");
 if(N_lep_branch) N_lep_branch->SetAddress(&N_lep_);
 lep_flav_1_branch = tree->GetBranch("lep_flav_1");
 if(lep_flav_1_branch) lep_flav_1_branch->SetAddress(&lep_flav_1_);
 lep_flav_2_branch = tree->GetBranch("lep_flav_2");
 if(lep_flav_2_branch) lep_flav_2_branch->SetAddress(&lep_flav_2_);
 m_mll_branch = tree->GetBranch("m_mll");
 if(m_mll_branch) m_mll_branch->SetAddress(&m_mll_);
 m_H_branch = tree->GetBranch("m_H");
 if(m_H_branch) m_H_branch->SetAddress(&m_H_);
 m_nph_branch = tree->GetBranch("m_nph");
 if(m_nph_branch) m_nph_branch->SetAddress(&m_nph_);
 m_tau_pt_branch = tree->GetBranch("m_tau_pt");
 if(m_tau_pt_branch) m_tau_pt_branch->SetAddress(&m_tau_pt_);
 m_ntau_medium_branch = tree->GetBranch("m_ntau_medium");
 if(m_ntau_medium_branch) m_ntau_medium_branch->SetAddress(&m_ntau_medium_);
 isPassed_branch = tree->GetBranch("isPassed");
 if(isPassed_branch) isPassed_branch->SetAddress(&isPassed_);
 flag_passedIso_branch = tree->GetBranch("flag_passedIso");
 if(flag_passedIso_branch) flag_passedIso_branch->SetAddress(&flag_passedIso_);
 flag_passedPID_branch = tree->GetBranch("flag_passedPID");
 if(flag_passedPID_branch) flag_passedPID_branch->SetAddress(&flag_passedPID_);
 ph_isTight1_branch = tree->GetBranch("ph_isTight1");
 if(ph_isTight1_branch) ph_isTight1_branch->SetAddress(&ph_isTight1_);
 ph_isTight2_branch = tree->GetBranch("ph_isTight2");
 if(ph_isTight2_branch) ph_isTight2_branch->SetAddress(&ph_isTight2_);
 ph_isTight3_branch = tree->GetBranch("ph_isTight3");
 if(ph_isTight3_branch) ph_isTight3_branch->SetAddress(&ph_isTight3_);
 ph_iso1_branch = tree->GetBranch("ph_iso1");
 if(ph_iso1_branch) ph_iso1_branch->SetAddress(&ph_iso1_);
 ph_iso2_branch = tree->GetBranch("ph_iso2");
 if(ph_iso2_branch) ph_iso2_branch->SetAddress(&ph_iso2_);
 ph_iso3_branch = tree->GetBranch("ph_iso3");
 if(ph_iso3_branch) ph_iso3_branch->SetAddress(&ph_iso3_);
 score_recotop1_branch = tree->GetBranch("score_recotop1");
 if(score_recotop1_branch) score_recotop1_branch->SetAddress(&score_recotop1_);
 isPassedTriggerMatch_branch = tree->GetBranch("isPassedTriggerMatch");
 if(isPassedTriggerMatch_branch) isPassedTriggerMatch_branch->SetAddress(&isPassedTriggerMatch_);
 m_mpx_branch = tree->GetBranch("m_mpx");
 if(m_mpx_branch) m_mpx_branch->SetAddress(&m_mpx_);
 m_mpy_branch = tree->GetBranch("m_mpy");
 if(m_mpy_branch) m_mpy_branch->SetAddress(&m_mpy_);
 m_sumet_branch = tree->GetBranch("m_sumet");
 if(m_sumet_branch) m_sumet_branch->SetAddress(&m_sumet_);
 m_met_branch = tree->GetBranch("m_met");
 if(m_met_branch) m_met_branch->SetAddress(&m_met_);
 gnn_score_branch = tree->GetBranch("gnn_score");
 if(gnn_score_branch) gnn_score_branch->SetAddress(&gnn_score_);
}

void hhtree::GetEntry(unsigned int idx)
{

 index = idx;
 runNumber_isLoaded = false;
 RunNumber_isLoaded = false;
 m_mcChannelNumber_isLoaded = false;
 eventNumber_isLoaded = false;
 mcweight_isLoaded = false;
 m_weight_isLoaded = false;
 n_ph_isLoaded = false;
 n_el_isLoaded = false;
 n_mu_isLoaded = false;
 n_tau_isLoaded = false;
 n_top_isLoaded = false;
 n_b_isLoaded = false;
 n_jet_isLoaded = false;
 n_bjet_isLoaded = false;
 m_mgg_isLoaded = false;
 tru_n_muel_isLoaded = false;
 n_lep_isLoaded = false;
 lep_q_1_isLoaded = false;
 lep_q_2_isLoaded = false;
 lep_E_1_isLoaded = false;
 lep_E_2_isLoaded = false;
 lep_pt_1_isLoaded = false;
 lep_pt_2_isLoaded = false;
 lep_pt_3_isLoaded = false;
 lep_eta_1_isLoaded = false;
 lep_eta_2_isLoaded = false;
 lep_phi_1_isLoaded = false;
 lep_phi_2_isLoaded = false;
 ph_pt1_isLoaded = false;
 ph_eta1_isLoaded = false;
 ph_phi1_isLoaded = false;
 ph_E1_isLoaded = false;
 ph_parent1_isLoaded = false;
 ph_pt2_isLoaded = false;
 ph_eta2_isLoaded = false;
 ph_phi2_isLoaded = false;
 ph_E2_isLoaded = false;
 ph_parent2_isLoaded = false;
 ph_pt3_isLoaded = false;
 ph_eta3_isLoaded = false;
 ph_phi3_isLoaded = false;
 ph_parent3_isLoaded = false;
 bjet_pt_1_isLoaded = false;
 bjet_pt_2_isLoaded = false;
 bjet_pt_3_isLoaded = false;
 jet0_pt_1_isLoaded = false;
 jet0_pt_2_isLoaded = false;
 jet0_pt_3_isLoaded = false;
 jet0_pt_4_isLoaded = false;
 jet0_pt_5_isLoaded = false;
 jet0_pt_6_isLoaded = false;
 jet0_pt_7_isLoaded = false;
 jet0_pt_8_isLoaded = false;
 jet0_eta_1_isLoaded = false;
 jet0_eta_2_isLoaded = false;
 jet0_eta_3_isLoaded = false;
 jet0_eta_4_isLoaded = false;
 jet0_eta_5_isLoaded = false;
 jet0_eta_6_isLoaded = false;
 jet0_eta_7_isLoaded = false;
 jet0_eta_8_isLoaded = false;
 jet0_phi_1_isLoaded = false;
 jet0_phi_2_isLoaded = false;
 jet0_phi_3_isLoaded = false;
 jet0_phi_4_isLoaded = false;
 jet0_phi_5_isLoaded = false;
 jet0_phi_6_isLoaded = false;
 jet0_phi_7_isLoaded = false;
 jet0_phi_8_isLoaded = false;
 b_pt1_isLoaded = false;
 b_eta1_isLoaded = false;
 b_phi1_isLoaded = false;
 b_pt2_isLoaded = false;
 b_eta2_isLoaded = false;
 b_phi2_isLoaded = false;
 b_pt3_isLoaded = false;
 b_eta3_isLoaded = false;
 b_phi3_isLoaded = false;
 ph_pt_isLoaded = false;
 ph_eta_isLoaded = false;
 ph_phi_isLoaded = false;
 ph_parent_id_isLoaded = false;
 m_el_pt_isLoaded = false;
 m_el_eta_isLoaded = false;
 m_el_phi_isLoaded = false;
 m_el_E_isLoaded = false;
 m_el_pdg_isLoaded = false;
 m_mu_pt_isLoaded = false;
 m_mu_eta_isLoaded = false;
 m_mu_phi_isLoaded = false;
 m_mu_E_isLoaded = false;
 m_mu_pdg_isLoaded = false;
 tau_pt_isLoaded = false;
 tau_eta_isLoaded = false;
 top_pt_isLoaded = false;
 top_eta_isLoaded = false;
 b_pt_isLoaded = false;
 b_eta_isLoaded = false;
 b_phi_isLoaded = false;
 m_jet_pt_isLoaded = false;
 m_jet_eta_isLoaded = false;
 m_jet_phi_isLoaded = false;
 m_jet_m_isLoaded = false;
 m_jet_btag70_isLoaded = false;
 m_jet_btag77_isLoaded = false;
 m_jet_btag60_isLoaded = false;
 m_jet_btag85_isLoaded = false;
 jet_AK4_b_tag_isLoaded = false;
 susy_m_isLoaded = false;
 susy_pt_isLoaded = false;
 susy_eta_isLoaded = false;
 susy_phi_isLoaded = false;
 susy_pdg_isLoaded = false;
 m_njet_isLoaded = false;
 N_j_central_isLoaded = false;
 m_HT_isLoaded = false;
 m_HT_central_isLoaded = false;
 m_mass_multijet_isLoaded = false;
 m_nbjet_fixed60_isLoaded = false;
 m_nbjet_fixed80_isLoaded = false;
 m_nbjet_fixed70_isLoaded = false;
 m_nbjet_fixed85_isLoaded = false;
 N_lep_isLoaded = false;
 lep_flav_1_isLoaded = false;
 lep_flav_2_isLoaded = false;
 m_mll_isLoaded = false;
 m_H_isLoaded = false;
 m_nph_isLoaded = false;
 m_tau_pt_isLoaded = false;
 m_ntau_medium_isLoaded = false;
 isPassed_isLoaded = false;
 flag_passedIso_isLoaded = false;
 flag_passedPID_isLoaded = false;
 ph_isTight1_isLoaded = false;
 ph_isTight2_isLoaded = false;
 ph_isTight3_isLoaded = false;
 ph_iso1_isLoaded = false;
 ph_iso2_isLoaded = false;
 ph_iso3_isLoaded = false;
 score_recotop1_isLoaded = false;
 isPassedTriggerMatch_isLoaded = false;
 m_mpx_isLoaded = false;
 m_mpy_isLoaded = false;
 m_sumet_isLoaded = false;
 m_met_isLoaded = false;
 gnn_score_isLoaded = false;
}

const int &hhtree::runNumber() 
{
 if(not runNumber_isLoaded)
 {
   if(runNumber_branch != 0) runNumber_branch->GetEntry(index);
   else
   {
     printf("branch runNumber_branch does not exist!\n");
exit(1);
   }
   runNumber_isLoaded = true;
 }
 return runNumber_;
}

const int &hhtree::RunNumber() 
{
 if(not RunNumber_isLoaded)
 {
   if(RunNumber_branch != 0) RunNumber_branch->GetEntry(index);
   else
   {
     printf("branch RunNumber_branch does not exist!\n");
exit(1);
   }
   RunNumber_isLoaded = true;
 }
 return RunNumber_;
}

const int &hhtree::m_mcChannelNumber() 
{
 if(not m_mcChannelNumber_isLoaded)
 {
   if(m_mcChannelNumber_branch != 0) m_mcChannelNumber_branch->GetEntry(index);
   else
   {
     printf("branch m_mcChannelNumber_branch does not exist!\n");
exit(1);
   }
   m_mcChannelNumber_isLoaded = true;
 }
 return m_mcChannelNumber_;
}

const int &hhtree::eventNumber() 
{
 if(not eventNumber_isLoaded)
 {
   if(eventNumber_branch != 0) eventNumber_branch->GetEntry(index);
   else
   {
     printf("branch eventNumber_branch does not exist!\n");
exit(1);
   }
   eventNumber_isLoaded = true;
 }
 return eventNumber_;
}

const float &hhtree::mcweight() 
{
 if(not mcweight_isLoaded)
 {
   if(mcweight_branch != 0) mcweight_branch->GetEntry(index);
   else
   {
     printf("branch mcweight_branch does not exist!\n");
exit(1);
   }
   mcweight_isLoaded = true;
 }
 return mcweight_;
}

const double &hhtree::m_weight() 
{
 if(not m_weight_isLoaded)
 {
   if(m_weight_branch != 0) m_weight_branch->GetEntry(index);
   else
   {
     printf("branch m_weight_branch does not exist!\n");
exit(1);
   }
   m_weight_isLoaded = true;
 }
 return m_weight_;
}

const int &hhtree::n_ph() 
{
 if(not n_ph_isLoaded)
 {
   if(n_ph_branch != 0) n_ph_branch->GetEntry(index);
   else
   {
     printf("branch n_ph_branch does not exist!\n");
exit(1);
   }
   n_ph_isLoaded = true;
 }
 return n_ph_;
}

const int &hhtree::n_el() 
{
 if(not n_el_isLoaded)
 {
   if(n_el_branch != 0) n_el_branch->GetEntry(index);
   else
   {
     printf("branch n_el_branch does not exist!\n");
exit(1);
   }
   n_el_isLoaded = true;
 }
 return n_el_;
}

const int &hhtree::n_mu() 
{
 if(not n_mu_isLoaded)
 {
   if(n_mu_branch != 0) n_mu_branch->GetEntry(index);
   else
   {
     printf("branch n_mu_branch does not exist!\n");
exit(1);
   }
   n_mu_isLoaded = true;
 }
 return n_mu_;
}

const int &hhtree::n_tau() 
{
 if(not n_tau_isLoaded)
 {
   if(n_tau_branch != 0) n_tau_branch->GetEntry(index);
   else
   {
     printf("branch n_tau_branch does not exist!\n");
exit(1);
   }
   n_tau_isLoaded = true;
 }
 return n_tau_;
}

const int &hhtree::n_top() 
{
 if(not n_top_isLoaded)
 {
   if(n_top_branch != 0) n_top_branch->GetEntry(index);
   else
   {
     printf("branch n_top_branch does not exist!\n");
exit(1);
   }
   n_top_isLoaded = true;
 }
 return n_top_;
}

const int &hhtree::n_b() 
{
 if(not n_b_isLoaded)
 {
   if(n_b_branch != 0) n_b_branch->GetEntry(index);
   else
   {
     printf("branch n_b_branch does not exist!\n");
exit(1);
   }
   n_b_isLoaded = true;
 }
 return n_b_;
}

const int &hhtree::n_jet() 
{
 if(not n_jet_isLoaded)
 {
   if(n_jet_branch != 0) n_jet_branch->GetEntry(index);
   else
   {
     printf("branch n_jet_branch does not exist!\n");
exit(1);
   }
   n_jet_isLoaded = true;
 }
 return n_jet_;
}

const int &hhtree::n_bjet() 
{
 if(not n_bjet_isLoaded)
 {
   if(n_bjet_branch != 0) n_bjet_branch->GetEntry(index);
   else
   {
     printf("branch n_bjet_branch does not exist!\n");
exit(1);
   }
   n_bjet_isLoaded = true;
 }
 return n_bjet_;
}

const float &hhtree::m_mgg() 
{
 if(not m_mgg_isLoaded)
 {
   if(m_mgg_branch != 0) m_mgg_branch->GetEntry(index);
   else
   {
     printf("branch m_mgg_branch does not exist!\n");
exit(1);
   }
   m_mgg_isLoaded = true;
 }
 return m_mgg_;
}

const int &hhtree::tru_n_muel() 
{
 if(not tru_n_muel_isLoaded)
 {
   if(tru_n_muel_branch != 0) tru_n_muel_branch->GetEntry(index);
   else
   {
     printf("branch tru_n_muel_branch does not exist!\n");
exit(1);
   }
   tru_n_muel_isLoaded = true;
 }
 return tru_n_muel_;
}

const int &hhtree::n_lep() 
{
 if(not n_lep_isLoaded)
 {
   if(n_lep_branch != 0) n_lep_branch->GetEntry(index);
   else
   {
     printf("branch n_lep_branch does not exist!\n");
exit(1);
   }
   n_lep_isLoaded = true;
 }
 return n_lep_;
}

const int &hhtree::lep_q_1() 
{
 if(not lep_q_1_isLoaded)
 {
   if(lep_q_1_branch != 0) lep_q_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_q_1_branch does not exist!\n");
exit(1);
   }
   lep_q_1_isLoaded = true;
 }
 return lep_q_1_;
}

const int &hhtree::lep_q_2() 
{
 if(not lep_q_2_isLoaded)
 {
   if(lep_q_2_branch != 0) lep_q_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_q_2_branch does not exist!\n");
exit(1);
   }
   lep_q_2_isLoaded = true;
 }
 return lep_q_2_;
}

const float &hhtree::lep_E_1() 
{
 if(not lep_E_1_isLoaded)
 {
   if(lep_E_1_branch != 0) lep_E_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_E_1_branch does not exist!\n");
exit(1);
   }
   lep_E_1_isLoaded = true;
 }
 return lep_E_1_;
}

const float &hhtree::lep_E_2() 
{
 if(not lep_E_2_isLoaded)
 {
   if(lep_E_2_branch != 0) lep_E_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_E_2_branch does not exist!\n");
exit(1);
   }
   lep_E_2_isLoaded = true;
 }
 return lep_E_2_;
}

const float &hhtree::lep_pt_1() 
{
 if(not lep_pt_1_isLoaded)
 {
   if(lep_pt_1_branch != 0) lep_pt_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_pt_1_branch does not exist!\n");
exit(1);
   }
   lep_pt_1_isLoaded = true;
 }
 return lep_pt_1_;
}

const float &hhtree::lep_pt_2() 
{
 if(not lep_pt_2_isLoaded)
 {
   if(lep_pt_2_branch != 0) lep_pt_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_pt_2_branch does not exist!\n");
exit(1);
   }
   lep_pt_2_isLoaded = true;
 }
 return lep_pt_2_;
}

const float &hhtree::lep_pt_3() 
{
 if(not lep_pt_3_isLoaded)
 {
   if(lep_pt_3_branch != 0) lep_pt_3_branch->GetEntry(index);
   else
   {
     printf("branch lep_pt_3_branch does not exist!\n");
exit(1);
   }
   lep_pt_3_isLoaded = true;
 }
 return lep_pt_3_;
}

const float &hhtree::lep_eta_1() 
{
 if(not lep_eta_1_isLoaded)
 {
   if(lep_eta_1_branch != 0) lep_eta_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_eta_1_branch does not exist!\n");
exit(1);
   }
   lep_eta_1_isLoaded = true;
 }
 return lep_eta_1_;
}

const float &hhtree::lep_eta_2() 
{
 if(not lep_eta_2_isLoaded)
 {
   if(lep_eta_2_branch != 0) lep_eta_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_eta_2_branch does not exist!\n");
exit(1);
   }
   lep_eta_2_isLoaded = true;
 }
 return lep_eta_2_;
}

const float &hhtree::lep_phi_1() 
{
 if(not lep_phi_1_isLoaded)
 {
   if(lep_phi_1_branch != 0) lep_phi_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_phi_1_branch does not exist!\n");
exit(1);
   }
   lep_phi_1_isLoaded = true;
 }
 return lep_phi_1_;
}

const float &hhtree::lep_phi_2() 
{
 if(not lep_phi_2_isLoaded)
 {
   if(lep_phi_2_branch != 0) lep_phi_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_phi_2_branch does not exist!\n");
exit(1);
   }
   lep_phi_2_isLoaded = true;
 }
 return lep_phi_2_;
}

const float &hhtree::ph_pt1() 
{
 if(not ph_pt1_isLoaded)
 {
   if(ph_pt1_branch != 0) ph_pt1_branch->GetEntry(index);
   else
   {
     printf("branch ph_pt1_branch does not exist!\n");
exit(1);
   }
   ph_pt1_isLoaded = true;
 }
 return ph_pt1_;
}

const float &hhtree::ph_eta1() 
{
 if(not ph_eta1_isLoaded)
 {
   if(ph_eta1_branch != 0) ph_eta1_branch->GetEntry(index);
   else
   {
     printf("branch ph_eta1_branch does not exist!\n");
exit(1);
   }
   ph_eta1_isLoaded = true;
 }
 return ph_eta1_;
}

const float &hhtree::ph_phi1() 
{
 if(not ph_phi1_isLoaded)
 {
   if(ph_phi1_branch != 0) ph_phi1_branch->GetEntry(index);
   else
   {
     printf("branch ph_phi1_branch does not exist!\n");
exit(1);
   }
   ph_phi1_isLoaded = true;
 }
 return ph_phi1_;
}

const float &hhtree::ph_E1() 
{
 if(not ph_E1_isLoaded)
 {
   if(ph_E1_branch != 0) ph_E1_branch->GetEntry(index);
   else
   {
     printf("branch ph_E1_branch does not exist!\n");
exit(1);
   }
   ph_E1_isLoaded = true;
 }
 return ph_E1_;
}

const float &hhtree::ph_parent1() 
{
 if(not ph_parent1_isLoaded)
 {
   if(ph_parent1_branch != 0) ph_parent1_branch->GetEntry(index);
   else
   {
     printf("branch ph_parent1_branch does not exist!\n");
exit(1);
   }
   ph_parent1_isLoaded = true;
 }
 return ph_parent1_;
}

const float &hhtree::ph_pt2() 
{
 if(not ph_pt2_isLoaded)
 {
   if(ph_pt2_branch != 0) ph_pt2_branch->GetEntry(index);
   else
   {
     printf("branch ph_pt2_branch does not exist!\n");
exit(1);
   }
   ph_pt2_isLoaded = true;
 }
 return ph_pt2_;
}

const float &hhtree::ph_eta2() 
{
 if(not ph_eta2_isLoaded)
 {
   if(ph_eta2_branch != 0) ph_eta2_branch->GetEntry(index);
   else
   {
     printf("branch ph_eta2_branch does not exist!\n");
exit(1);
   }
   ph_eta2_isLoaded = true;
 }
 return ph_eta2_;
}

const float &hhtree::ph_phi2() 
{
 if(not ph_phi2_isLoaded)
 {
   if(ph_phi2_branch != 0) ph_phi2_branch->GetEntry(index);
   else
   {
     printf("branch ph_phi2_branch does not exist!\n");
exit(1);
   }
   ph_phi2_isLoaded = true;
 }
 return ph_phi2_;
}

const float &hhtree::ph_E2() 
{
 if(not ph_E2_isLoaded)
 {
   if(ph_E2_branch != 0) ph_E2_branch->GetEntry(index);
   else
   {
     printf("branch ph_E2_branch does not exist!\n");
exit(1);
   }
   ph_E2_isLoaded = true;
 }
 return ph_E2_;
}

const float &hhtree::ph_parent2() 
{
 if(not ph_parent2_isLoaded)
 {
   if(ph_parent2_branch != 0) ph_parent2_branch->GetEntry(index);
   else
   {
     printf("branch ph_parent2_branch does not exist!\n");
exit(1);
   }
   ph_parent2_isLoaded = true;
 }
 return ph_parent2_;
}

const float &hhtree::ph_pt3() 
{
 if(not ph_pt3_isLoaded)
 {
   if(ph_pt3_branch != 0) ph_pt3_branch->GetEntry(index);
   else
   {
     printf("branch ph_pt3_branch does not exist!\n");
exit(1);
   }
   ph_pt3_isLoaded = true;
 }
 return ph_pt3_;
}

const float &hhtree::ph_eta3() 
{
 if(not ph_eta3_isLoaded)
 {
   if(ph_eta3_branch != 0) ph_eta3_branch->GetEntry(index);
   else
   {
     printf("branch ph_eta3_branch does not exist!\n");
exit(1);
   }
   ph_eta3_isLoaded = true;
 }
 return ph_eta3_;
}

const float &hhtree::ph_phi3() 
{
 if(not ph_phi3_isLoaded)
 {
   if(ph_phi3_branch != 0) ph_phi3_branch->GetEntry(index);
   else
   {
     printf("branch ph_phi3_branch does not exist!\n");
exit(1);
   }
   ph_phi3_isLoaded = true;
 }
 return ph_phi3_;
}

const float &hhtree::ph_parent3() 
{
 if(not ph_parent3_isLoaded)
 {
   if(ph_parent3_branch != 0) ph_parent3_branch->GetEntry(index);
   else
   {
     printf("branch ph_parent3_branch does not exist!\n");
exit(1);
   }
   ph_parent3_isLoaded = true;
 }
 return ph_parent3_;
}

const float &hhtree::bjet_pt_1() 
{
 if(not bjet_pt_1_isLoaded)
 {
   if(bjet_pt_1_branch != 0) bjet_pt_1_branch->GetEntry(index);
   else
   {
     printf("branch bjet_pt_1_branch does not exist!\n");
exit(1);
   }
   bjet_pt_1_isLoaded = true;
 }
 return bjet_pt_1_;
}

const float &hhtree::bjet_pt_2() 
{
 if(not bjet_pt_2_isLoaded)
 {
   if(bjet_pt_2_branch != 0) bjet_pt_2_branch->GetEntry(index);
   else
   {
     printf("branch bjet_pt_2_branch does not exist!\n");
exit(1);
   }
   bjet_pt_2_isLoaded = true;
 }
 return bjet_pt_2_;
}

const float &hhtree::bjet_pt_3() 
{
 if(not bjet_pt_3_isLoaded)
 {
   if(bjet_pt_3_branch != 0) bjet_pt_3_branch->GetEntry(index);
   else
   {
     printf("branch bjet_pt_3_branch does not exist!\n");
exit(1);
   }
   bjet_pt_3_isLoaded = true;
 }
 return bjet_pt_3_;
}

const float &hhtree::jet0_pt_1() 
{
 if(not jet0_pt_1_isLoaded)
 {
   if(jet0_pt_1_branch != 0) jet0_pt_1_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_1_branch does not exist!\n");
exit(1);
   }
   jet0_pt_1_isLoaded = true;
 }
 return jet0_pt_1_;
}

const float &hhtree::jet0_pt_2() 
{
 if(not jet0_pt_2_isLoaded)
 {
   if(jet0_pt_2_branch != 0) jet0_pt_2_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_2_branch does not exist!\n");
exit(1);
   }
   jet0_pt_2_isLoaded = true;
 }
 return jet0_pt_2_;
}

const float &hhtree::jet0_pt_3() 
{
 if(not jet0_pt_3_isLoaded)
 {
   if(jet0_pt_3_branch != 0) jet0_pt_3_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_3_branch does not exist!\n");
exit(1);
   }
   jet0_pt_3_isLoaded = true;
 }
 return jet0_pt_3_;
}

const float &hhtree::jet0_pt_4() 
{
 if(not jet0_pt_4_isLoaded)
 {
   if(jet0_pt_4_branch != 0) jet0_pt_4_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_4_branch does not exist!\n");
exit(1);
   }
   jet0_pt_4_isLoaded = true;
 }
 return jet0_pt_4_;
}

const float &hhtree::jet0_pt_5() 
{
 if(not jet0_pt_5_isLoaded)
 {
   if(jet0_pt_5_branch != 0) jet0_pt_5_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_5_branch does not exist!\n");
exit(1);
   }
   jet0_pt_5_isLoaded = true;
 }
 return jet0_pt_5_;
}

const float &hhtree::jet0_pt_6() 
{
 if(not jet0_pt_6_isLoaded)
 {
   if(jet0_pt_6_branch != 0) jet0_pt_6_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_6_branch does not exist!\n");
exit(1);
   }
   jet0_pt_6_isLoaded = true;
 }
 return jet0_pt_6_;
}

const float &hhtree::jet0_pt_7() 
{
 if(not jet0_pt_7_isLoaded)
 {
   if(jet0_pt_7_branch != 0) jet0_pt_7_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_7_branch does not exist!\n");
exit(1);
   }
   jet0_pt_7_isLoaded = true;
 }
 return jet0_pt_7_;
}

const float &hhtree::jet0_pt_8() 
{
 if(not jet0_pt_8_isLoaded)
 {
   if(jet0_pt_8_branch != 0) jet0_pt_8_branch->GetEntry(index);
   else
   {
     printf("branch jet0_pt_8_branch does not exist!\n");
exit(1);
   }
   jet0_pt_8_isLoaded = true;
 }
 return jet0_pt_8_;
}

const float &hhtree::jet0_eta_1() 
{
 if(not jet0_eta_1_isLoaded)
 {
   if(jet0_eta_1_branch != 0) jet0_eta_1_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_1_branch does not exist!\n");
exit(1);
   }
   jet0_eta_1_isLoaded = true;
 }
 return jet0_eta_1_;
}

const float &hhtree::jet0_eta_2() 
{
 if(not jet0_eta_2_isLoaded)
 {
   if(jet0_eta_2_branch != 0) jet0_eta_2_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_2_branch does not exist!\n");
exit(1);
   }
   jet0_eta_2_isLoaded = true;
 }
 return jet0_eta_2_;
}

const float &hhtree::jet0_eta_3() 
{
 if(not jet0_eta_3_isLoaded)
 {
   if(jet0_eta_3_branch != 0) jet0_eta_3_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_3_branch does not exist!\n");
exit(1);
   }
   jet0_eta_3_isLoaded = true;
 }
 return jet0_eta_3_;
}

const float &hhtree::jet0_eta_4() 
{
 if(not jet0_eta_4_isLoaded)
 {
   if(jet0_eta_4_branch != 0) jet0_eta_4_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_4_branch does not exist!\n");
exit(1);
   }
   jet0_eta_4_isLoaded = true;
 }
 return jet0_eta_4_;
}

const float &hhtree::jet0_eta_5() 
{
 if(not jet0_eta_5_isLoaded)
 {
   if(jet0_eta_5_branch != 0) jet0_eta_5_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_5_branch does not exist!\n");
exit(1);
   }
   jet0_eta_5_isLoaded = true;
 }
 return jet0_eta_5_;
}

const float &hhtree::jet0_eta_6() 
{
 if(not jet0_eta_6_isLoaded)
 {
   if(jet0_eta_6_branch != 0) jet0_eta_6_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_6_branch does not exist!\n");
exit(1);
   }
   jet0_eta_6_isLoaded = true;
 }
 return jet0_eta_6_;
}

const float &hhtree::jet0_eta_7() 
{
 if(not jet0_eta_7_isLoaded)
 {
   if(jet0_eta_7_branch != 0) jet0_eta_7_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_7_branch does not exist!\n");
exit(1);
   }
   jet0_eta_7_isLoaded = true;
 }
 return jet0_eta_7_;
}

const float &hhtree::jet0_eta_8() 
{
 if(not jet0_eta_8_isLoaded)
 {
   if(jet0_eta_8_branch != 0) jet0_eta_8_branch->GetEntry(index);
   else
   {
     printf("branch jet0_eta_8_branch does not exist!\n");
exit(1);
   }
   jet0_eta_8_isLoaded = true;
 }
 return jet0_eta_8_;
}

const float &hhtree::jet0_phi_1() 
{
 if(not jet0_phi_1_isLoaded)
 {
   if(jet0_phi_1_branch != 0) jet0_phi_1_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_1_branch does not exist!\n");
exit(1);
   }
   jet0_phi_1_isLoaded = true;
 }
 return jet0_phi_1_;
}

const float &hhtree::jet0_phi_2() 
{
 if(not jet0_phi_2_isLoaded)
 {
   if(jet0_phi_2_branch != 0) jet0_phi_2_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_2_branch does not exist!\n");
exit(1);
   }
   jet0_phi_2_isLoaded = true;
 }
 return jet0_phi_2_;
}

const float &hhtree::jet0_phi_3() 
{
 if(not jet0_phi_3_isLoaded)
 {
   if(jet0_phi_3_branch != 0) jet0_phi_3_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_3_branch does not exist!\n");
exit(1);
   }
   jet0_phi_3_isLoaded = true;
 }
 return jet0_phi_3_;
}

const float &hhtree::jet0_phi_4() 
{
 if(not jet0_phi_4_isLoaded)
 {
   if(jet0_phi_4_branch != 0) jet0_phi_4_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_4_branch does not exist!\n");
exit(1);
   }
   jet0_phi_4_isLoaded = true;
 }
 return jet0_phi_4_;
}

const float &hhtree::jet0_phi_5() 
{
 if(not jet0_phi_5_isLoaded)
 {
   if(jet0_phi_5_branch != 0) jet0_phi_5_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_5_branch does not exist!\n");
exit(1);
   }
   jet0_phi_5_isLoaded = true;
 }
 return jet0_phi_5_;
}

const float &hhtree::jet0_phi_6() 
{
 if(not jet0_phi_6_isLoaded)
 {
   if(jet0_phi_6_branch != 0) jet0_phi_6_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_6_branch does not exist!\n");
exit(1);
   }
   jet0_phi_6_isLoaded = true;
 }
 return jet0_phi_6_;
}

const float &hhtree::jet0_phi_7() 
{
 if(not jet0_phi_7_isLoaded)
 {
   if(jet0_phi_7_branch != 0) jet0_phi_7_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_7_branch does not exist!\n");
exit(1);
   }
   jet0_phi_7_isLoaded = true;
 }
 return jet0_phi_7_;
}

const float &hhtree::jet0_phi_8() 
{
 if(not jet0_phi_8_isLoaded)
 {
   if(jet0_phi_8_branch != 0) jet0_phi_8_branch->GetEntry(index);
   else
   {
     printf("branch jet0_phi_8_branch does not exist!\n");
exit(1);
   }
   jet0_phi_8_isLoaded = true;
 }
 return jet0_phi_8_;
}

const float &hhtree::b_pt1() 
{
 if(not b_pt1_isLoaded)
 {
   if(b_pt1_branch != 0) b_pt1_branch->GetEntry(index);
   else
   {
     printf("branch b_pt1_branch does not exist!\n");
exit(1);
   }
   b_pt1_isLoaded = true;
 }
 return b_pt1_;
}

const float &hhtree::b_eta1() 
{
 if(not b_eta1_isLoaded)
 {
   if(b_eta1_branch != 0) b_eta1_branch->GetEntry(index);
   else
   {
     printf("branch b_eta1_branch does not exist!\n");
exit(1);
   }
   b_eta1_isLoaded = true;
 }
 return b_eta1_;
}

const float &hhtree::b_phi1() 
{
 if(not b_phi1_isLoaded)
 {
   if(b_phi1_branch != 0) b_phi1_branch->GetEntry(index);
   else
   {
     printf("branch b_phi1_branch does not exist!\n");
exit(1);
   }
   b_phi1_isLoaded = true;
 }
 return b_phi1_;
}

const float &hhtree::b_pt2() 
{
 if(not b_pt2_isLoaded)
 {
   if(b_pt2_branch != 0) b_pt2_branch->GetEntry(index);
   else
   {
     printf("branch b_pt2_branch does not exist!\n");
exit(1);
   }
   b_pt2_isLoaded = true;
 }
 return b_pt2_;
}

const float &hhtree::b_eta2() 
{
 if(not b_eta2_isLoaded)
 {
   if(b_eta2_branch != 0) b_eta2_branch->GetEntry(index);
   else
   {
     printf("branch b_eta2_branch does not exist!\n");
exit(1);
   }
   b_eta2_isLoaded = true;
 }
 return b_eta2_;
}

const float &hhtree::b_phi2() 
{
 if(not b_phi2_isLoaded)
 {
   if(b_phi2_branch != 0) b_phi2_branch->GetEntry(index);
   else
   {
     printf("branch b_phi2_branch does not exist!\n");
exit(1);
   }
   b_phi2_isLoaded = true;
 }
 return b_phi2_;
}

const float &hhtree::b_pt3() 
{
 if(not b_pt3_isLoaded)
 {
   if(b_pt3_branch != 0) b_pt3_branch->GetEntry(index);
   else
   {
     printf("branch b_pt3_branch does not exist!\n");
exit(1);
   }
   b_pt3_isLoaded = true;
 }
 return b_pt3_;
}

const float &hhtree::b_eta3() 
{
 if(not b_eta3_isLoaded)
 {
   if(b_eta3_branch != 0) b_eta3_branch->GetEntry(index);
   else
   {
     printf("branch b_eta3_branch does not exist!\n");
exit(1);
   }
   b_eta3_isLoaded = true;
 }
 return b_eta3_;
}

const float &hhtree::b_phi3() 
{
 if(not b_phi3_isLoaded)
 {
   if(b_phi3_branch != 0) b_phi3_branch->GetEntry(index);
   else
   {
     printf("branch b_phi3_branch does not exist!\n");
exit(1);
   }
   b_phi3_isLoaded = true;
 }
 return b_phi3_;
}

const vector<float> &hhtree::ph_pt() 
{
 if(not ph_pt_isLoaded)
 {
   if(ph_pt_branch != 0) ph_pt_branch->GetEntry(index);
   else
   {
     printf("branch ph_pt_branch does not exist!\n");
exit(1);
   }
   ph_pt_isLoaded = true;
 }
 return *ph_pt_;
}

const vector<float> &hhtree::ph_eta() 
{
 if(not ph_eta_isLoaded)
 {
   if(ph_eta_branch != 0) ph_eta_branch->GetEntry(index);
   else
   {
     printf("branch ph_eta_branch does not exist!\n");
exit(1);
   }
   ph_eta_isLoaded = true;
 }
 return *ph_eta_;
}

const vector<float> &hhtree::ph_phi() 
{
 if(not ph_phi_isLoaded)
 {
   if(ph_phi_branch != 0) ph_phi_branch->GetEntry(index);
   else
   {
     printf("branch ph_phi_branch does not exist!\n");
exit(1);
   }
   ph_phi_isLoaded = true;
 }
 return *ph_phi_;
}

const vector<float> &hhtree::ph_parent_id() 
{
 if(not ph_parent_id_isLoaded)
 {
   if(ph_parent_id_branch != 0) ph_parent_id_branch->GetEntry(index);
   else
   {
     printf("branch ph_parent_id_branch does not exist!\n");
exit(1);
   }
   ph_parent_id_isLoaded = true;
 }
 return *ph_parent_id_;
}

const vector<float> &hhtree::m_el_pt() 
{
 if(not m_el_pt_isLoaded)
 {
   if(m_el_pt_branch != 0) m_el_pt_branch->GetEntry(index);
   else
   {
     printf("branch m_el_pt_branch does not exist!\n");
exit(1);
   }
   m_el_pt_isLoaded = true;
 }
 return *m_el_pt_;
}

const vector<float> &hhtree::m_el_eta() 
{
 if(not m_el_eta_isLoaded)
 {
   if(m_el_eta_branch != 0) m_el_eta_branch->GetEntry(index);
   else
   {
     printf("branch m_el_eta_branch does not exist!\n");
exit(1);
   }
   m_el_eta_isLoaded = true;
 }
 return *m_el_eta_;
}

const vector<float> &hhtree::m_el_phi() 
{
 if(not m_el_phi_isLoaded)
 {
   if(m_el_phi_branch != 0) m_el_phi_branch->GetEntry(index);
   else
   {
     printf("branch m_el_phi_branch does not exist!\n");
exit(1);
   }
   m_el_phi_isLoaded = true;
 }
 return *m_el_phi_;
}

const vector<float> &hhtree::m_el_E() 
{
 if(not m_el_E_isLoaded)
 {
   if(m_el_E_branch != 0) m_el_E_branch->GetEntry(index);
   else
   {
     printf("branch m_el_E_branch does not exist!\n");
exit(1);
   }
   m_el_E_isLoaded = true;
 }
 return *m_el_E_;
}

const vector<float> &hhtree::m_el_pdg() 
{
 if(not m_el_pdg_isLoaded)
 {
   if(m_el_pdg_branch != 0) m_el_pdg_branch->GetEntry(index);
   else
   {
     printf("branch m_el_pdg_branch does not exist!\n");
exit(1);
   }
   m_el_pdg_isLoaded = true;
 }
 return *m_el_pdg_;
}

const vector<float> &hhtree::m_mu_pt() 
{
 if(not m_mu_pt_isLoaded)
 {
   if(m_mu_pt_branch != 0) m_mu_pt_branch->GetEntry(index);
   else
   {
     printf("branch m_mu_pt_branch does not exist!\n");
exit(1);
   }
   m_mu_pt_isLoaded = true;
 }
 return *m_mu_pt_;
}

const vector<float> &hhtree::m_mu_eta() 
{
 if(not m_mu_eta_isLoaded)
 {
   if(m_mu_eta_branch != 0) m_mu_eta_branch->GetEntry(index);
   else
   {
     printf("branch m_mu_eta_branch does not exist!\n");
exit(1);
   }
   m_mu_eta_isLoaded = true;
 }
 return *m_mu_eta_;
}

const vector<float> &hhtree::m_mu_phi() 
{
 if(not m_mu_phi_isLoaded)
 {
   if(m_mu_phi_branch != 0) m_mu_phi_branch->GetEntry(index);
   else
   {
     printf("branch m_mu_phi_branch does not exist!\n");
exit(1);
   }
   m_mu_phi_isLoaded = true;
 }
 return *m_mu_phi_;
}

const vector<float> &hhtree::m_mu_E() 
{
 if(not m_mu_E_isLoaded)
 {
   if(m_mu_E_branch != 0) m_mu_E_branch->GetEntry(index);
   else
   {
     printf("branch m_mu_E_branch does not exist!\n");
exit(1);
   }
   m_mu_E_isLoaded = true;
 }
 return *m_mu_E_;
}

const vector<float> &hhtree::m_mu_pdg() 
{
 if(not m_mu_pdg_isLoaded)
 {
   if(m_mu_pdg_branch != 0) m_mu_pdg_branch->GetEntry(index);
   else
   {
     printf("branch m_mu_pdg_branch does not exist!\n");
exit(1);
   }
   m_mu_pdg_isLoaded = true;
 }
 return *m_mu_pdg_;
}

const vector<float> &hhtree::tau_pt() 
{
 if(not tau_pt_isLoaded)
 {
   if(tau_pt_branch != 0) tau_pt_branch->GetEntry(index);
   else
   {
     printf("branch tau_pt_branch does not exist!\n");
exit(1);
   }
   tau_pt_isLoaded = true;
 }
 return *tau_pt_;
}

const vector<float> &hhtree::tau_eta() 
{
 if(not tau_eta_isLoaded)
 {
   if(tau_eta_branch != 0) tau_eta_branch->GetEntry(index);
   else
   {
     printf("branch tau_eta_branch does not exist!\n");
exit(1);
   }
   tau_eta_isLoaded = true;
 }
 return *tau_eta_;
}

const vector<float> &hhtree::top_pt() 
{
 if(not top_pt_isLoaded)
 {
   if(top_pt_branch != 0) top_pt_branch->GetEntry(index);
   else
   {
     printf("branch top_pt_branch does not exist!\n");
exit(1);
   }
   top_pt_isLoaded = true;
 }
 return *top_pt_;
}

const vector<float> &hhtree::top_eta() 
{
 if(not top_eta_isLoaded)
 {
   if(top_eta_branch != 0) top_eta_branch->GetEntry(index);
   else
   {
     printf("branch top_eta_branch does not exist!\n");
exit(1);
   }
   top_eta_isLoaded = true;
 }
 return *top_eta_;
}

const vector<float> &hhtree::b_pt() 
{
 if(not b_pt_isLoaded)
 {
   if(b_pt_branch != 0) b_pt_branch->GetEntry(index);
   else
   {
     printf("branch b_pt_branch does not exist!\n");
exit(1);
   }
   b_pt_isLoaded = true;
 }
 return *b_pt_;
}

const vector<float> &hhtree::b_eta() 
{
 if(not b_eta_isLoaded)
 {
   if(b_eta_branch != 0) b_eta_branch->GetEntry(index);
   else
   {
     printf("branch b_eta_branch does not exist!\n");
exit(1);
   }
   b_eta_isLoaded = true;
 }
 return *b_eta_;
}

const vector<float> &hhtree::b_phi() 
{
 if(not b_phi_isLoaded)
 {
   if(b_phi_branch != 0) b_phi_branch->GetEntry(index);
   else
   {
     printf("branch b_phi_branch does not exist!\n");
exit(1);
   }
   b_phi_isLoaded = true;
 }
 return *b_phi_;
}

const vector<float> &hhtree::m_jet_pt() 
{
 if(not m_jet_pt_isLoaded)
 {
   if(m_jet_pt_branch != 0) m_jet_pt_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_pt_branch does not exist!\n");
exit(1);
   }
   m_jet_pt_isLoaded = true;
 }
 return *m_jet_pt_;
}

const vector<float> &hhtree::m_jet_eta() 
{
 if(not m_jet_eta_isLoaded)
 {
   if(m_jet_eta_branch != 0) m_jet_eta_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_eta_branch does not exist!\n");
exit(1);
   }
   m_jet_eta_isLoaded = true;
 }
 return *m_jet_eta_;
}

const vector<float> &hhtree::m_jet_phi() 
{
 if(not m_jet_phi_isLoaded)
 {
   if(m_jet_phi_branch != 0) m_jet_phi_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_phi_branch does not exist!\n");
exit(1);
   }
   m_jet_phi_isLoaded = true;
 }
 return *m_jet_phi_;
}

const vector<float> &hhtree::m_jet_m() 
{
 if(not m_jet_m_isLoaded)
 {
   if(m_jet_m_branch != 0) m_jet_m_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_m_branch does not exist!\n");
exit(1);
   }
   m_jet_m_isLoaded = true;
 }
 return *m_jet_m_;
}

const vector<float> &hhtree::m_jet_btag70() 
{
 if(not m_jet_btag70_isLoaded)
 {
   if(m_jet_btag70_branch != 0) m_jet_btag70_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_btag70_branch does not exist!\n");
exit(1);
   }
   m_jet_btag70_isLoaded = true;
 }
 return *m_jet_btag70_;
}

const vector<float> &hhtree::m_jet_btag77() 
{
 if(not m_jet_btag77_isLoaded)
 {
   if(m_jet_btag77_branch != 0) m_jet_btag77_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_btag77_branch does not exist!\n");
exit(1);
   }
   m_jet_btag77_isLoaded = true;
 }
 return *m_jet_btag77_;
}

const vector<float> &hhtree::m_jet_btag60() 
{
 if(not m_jet_btag60_isLoaded)
 {
   if(m_jet_btag60_branch != 0) m_jet_btag60_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_btag60_branch does not exist!\n");
exit(1);
   }
   m_jet_btag60_isLoaded = true;
 }
 return *m_jet_btag60_;
}

const vector<float> &hhtree::m_jet_btag85() 
{
 if(not m_jet_btag85_isLoaded)
 {
   if(m_jet_btag85_branch != 0) m_jet_btag85_branch->GetEntry(index);
   else
   {
     printf("branch m_jet_btag85_branch does not exist!\n");
exit(1);
   }
   m_jet_btag85_isLoaded = true;
 }
 return *m_jet_btag85_;
}

const vector<float> &hhtree::jet_AK4_b_tag() 
{
 if(not jet_AK4_b_tag_isLoaded)
 {
   if(jet_AK4_b_tag_branch != 0) jet_AK4_b_tag_branch->GetEntry(index);
   else
   {
     printf("branch jet_AK4_b_tag_branch does not exist!\n");
exit(1);
   }
   jet_AK4_b_tag_isLoaded = true;
 }
 return *jet_AK4_b_tag_;
}

const vector<float> &hhtree::susy_m() 
{
 if(not susy_m_isLoaded)
 {
   if(susy_m_branch != 0) susy_m_branch->GetEntry(index);
   else
   {
     printf("branch susy_m_branch does not exist!\n");
exit(1);
   }
   susy_m_isLoaded = true;
 }
 return *susy_m_;
}

const vector<float> &hhtree::susy_pt() 
{
 if(not susy_pt_isLoaded)
 {
   if(susy_pt_branch != 0) susy_pt_branch->GetEntry(index);
   else
   {
     printf("branch susy_pt_branch does not exist!\n");
exit(1);
   }
   susy_pt_isLoaded = true;
 }
 return *susy_pt_;
}

const vector<float> &hhtree::susy_eta() 
{
 if(not susy_eta_isLoaded)
 {
   if(susy_eta_branch != 0) susy_eta_branch->GetEntry(index);
   else
   {
     printf("branch susy_eta_branch does not exist!\n");
exit(1);
   }
   susy_eta_isLoaded = true;
 }
 return *susy_eta_;
}

const vector<float> &hhtree::susy_phi() 
{
 if(not susy_phi_isLoaded)
 {
   if(susy_phi_branch != 0) susy_phi_branch->GetEntry(index);
   else
   {
     printf("branch susy_phi_branch does not exist!\n");
exit(1);
   }
   susy_phi_isLoaded = true;
 }
 return *susy_phi_;
}

const vector<float> &hhtree::susy_pdg() 
{
 if(not susy_pdg_isLoaded)
 {
   if(susy_pdg_branch != 0) susy_pdg_branch->GetEntry(index);
   else
   {
     printf("branch susy_pdg_branch does not exist!\n");
exit(1);
   }
   susy_pdg_isLoaded = true;
 }
 return *susy_pdg_;
}

const int &hhtree::m_njet() 
{
 if(not m_njet_isLoaded)
 {
   if(m_njet_branch != 0) m_njet_branch->GetEntry(index);
   else
   {
     printf("branch m_njet_branch does not exist!\n");
exit(1);
   }
   m_njet_isLoaded = true;
 }
 return m_njet_;
}

const int &hhtree::N_j_central() 
{
 if(not N_j_central_isLoaded)
 {
   if(N_j_central_branch != 0) N_j_central_branch->GetEntry(index);
   else
   {
     printf("branch N_j_central_branch does not exist!\n");
exit(1);
   }
   N_j_central_isLoaded = true;
 }
 return N_j_central_;
}

const double &hhtree::m_HT() 
{
 if(not m_HT_isLoaded)
 {
   if(m_HT_branch != 0) m_HT_branch->GetEntry(index);
   else
   {
     printf("branch m_HT_branch does not exist!\n");
exit(1);
   }
   m_HT_isLoaded = true;
 }
 return m_HT_;
}

const double &hhtree::m_HT_central() 
{
 if(not m_HT_central_isLoaded)
 {
   if(m_HT_central_branch != 0) m_HT_central_branch->GetEntry(index);
   else
   {
     printf("branch m_HT_central_branch does not exist!\n");
exit(1);
   }
   m_HT_central_isLoaded = true;
 }
 return m_HT_central_;
}

const double &hhtree::m_mass_multijet() 
{
 if(not m_mass_multijet_isLoaded)
 {
   if(m_mass_multijet_branch != 0) m_mass_multijet_branch->GetEntry(index);
   else
   {
     printf("branch m_mass_multijet_branch does not exist!\n");
exit(1);
   }
   m_mass_multijet_isLoaded = true;
 }
 return m_mass_multijet_;
}

const int &hhtree::m_nbjet_fixed60() 
{
 if(not m_nbjet_fixed60_isLoaded)
 {
   if(m_nbjet_fixed60_branch != 0) m_nbjet_fixed60_branch->GetEntry(index);
   else
   {
     printf("branch m_nbjet_fixed60_branch does not exist!\n");
exit(1);
   }
   m_nbjet_fixed60_isLoaded = true;
 }
 return m_nbjet_fixed60_;
}

const int &hhtree::m_nbjet_fixed80() 
{
 if(not m_nbjet_fixed80_isLoaded)
 {
   if(m_nbjet_fixed80_branch != 0) m_nbjet_fixed80_branch->GetEntry(index);
   else
   {
     printf("branch m_nbjet_fixed80_branch does not exist!\n");
exit(1);
   }
   m_nbjet_fixed80_isLoaded = true;
 }
 return m_nbjet_fixed80_;
}

const int &hhtree::m_nbjet_fixed70() 
{
 if(not m_nbjet_fixed70_isLoaded)
 {
   if(m_nbjet_fixed70_branch != 0) m_nbjet_fixed70_branch->GetEntry(index);
   else
   {
     printf("branch m_nbjet_fixed70_branch does not exist!\n");
exit(1);
   }
   m_nbjet_fixed70_isLoaded = true;
 }
 return m_nbjet_fixed70_;
}

const int &hhtree::m_nbjet_fixed85() 
{
 if(not m_nbjet_fixed85_isLoaded)
 {
   if(m_nbjet_fixed85_branch != 0) m_nbjet_fixed85_branch->GetEntry(index);
   else
   {
     printf("branch m_nbjet_fixed85_branch does not exist!\n");
exit(1);
   }
   m_nbjet_fixed85_isLoaded = true;
 }
 return m_nbjet_fixed85_;
}

const int &hhtree::N_lep() 
{
 if(not N_lep_isLoaded)
 {
   if(N_lep_branch != 0) N_lep_branch->GetEntry(index);
   else
   {
     printf("branch N_lep_branch does not exist!\n");
exit(1);
   }
   N_lep_isLoaded = true;
 }
 return N_lep_;
}

const int &hhtree::lep_flav_1() 
{
 if(not lep_flav_1_isLoaded)
 {
   if(lep_flav_1_branch != 0) lep_flav_1_branch->GetEntry(index);
   else
   {
     printf("branch lep_flav_1_branch does not exist!\n");
exit(1);
   }
   lep_flav_1_isLoaded = true;
 }
 return lep_flav_1_;
}

const int &hhtree::lep_flav_2() 
{
 if(not lep_flav_2_isLoaded)
 {
   if(lep_flav_2_branch != 0) lep_flav_2_branch->GetEntry(index);
   else
   {
     printf("branch lep_flav_2_branch does not exist!\n");
exit(1);
   }
   lep_flav_2_isLoaded = true;
 }
 return lep_flav_2_;
}

const double &hhtree::m_mll() 
{
 if(not m_mll_isLoaded)
 {
   if(m_mll_branch != 0) m_mll_branch->GetEntry(index);
   else
   {
     printf("branch m_mll_branch does not exist!\n");
exit(1);
   }
   m_mll_isLoaded = true;
 }
 return m_mll_;
}

const float &hhtree::m_H() 
{
 if(not m_H_isLoaded)
 {
   if(m_H_branch != 0) m_H_branch->GetEntry(index);
   else
   {
     printf("branch m_H_branch does not exist!\n");
exit(1);
   }
   m_H_isLoaded = true;
 }
 return m_H_;
}

const int &hhtree::m_nph() 
{
 if(not m_nph_isLoaded)
 {
   if(m_nph_branch != 0) m_nph_branch->GetEntry(index);
   else
   {
     printf("branch m_nph_branch does not exist!\n");
exit(1);
   }
   m_nph_isLoaded = true;
 }
 return m_nph_;
}

const vector<float> &hhtree::m_tau_pt() 
{
 if(not m_tau_pt_isLoaded)
 {
   if(m_tau_pt_branch != 0) m_tau_pt_branch->GetEntry(index);
   else
   {
     printf("branch m_tau_pt_branch does not exist!\n");
exit(1);
   }
   m_tau_pt_isLoaded = true;
 }
 return *m_tau_pt_;
}

const int &hhtree::m_ntau_medium() 
{
 if(not m_ntau_medium_isLoaded)
 {
   if(m_ntau_medium_branch != 0) m_ntau_medium_branch->GetEntry(index);
   else
   {
     printf("branch m_ntau_medium_branch does not exist!\n");
exit(1);
   }
   m_ntau_medium_isLoaded = true;
 }
 return m_ntau_medium_;
}

const bool &hhtree::isPassed() 
{
 if(not isPassed_isLoaded)
 {
   if(isPassed_branch != 0) isPassed_branch->GetEntry(index);
   else
   {
     printf("branch isPassed_branch does not exist!\n");
exit(1);
   }
   isPassed_isLoaded = true;
 }
 return isPassed_;
}

const bool &hhtree::flag_passedIso() 
{
 if(not flag_passedIso_isLoaded)
 {
   if(flag_passedIso_branch != 0) flag_passedIso_branch->GetEntry(index);
   else
   {
     printf("branch flag_passedIso_branch does not exist!\n");
exit(1);
   }
   flag_passedIso_isLoaded = true;
 }
 return flag_passedIso_;
}

const bool &hhtree::flag_passedPID() 
{
 if(not flag_passedPID_isLoaded)
 {
   if(flag_passedPID_branch != 0) flag_passedPID_branch->GetEntry(index);
   else
   {
     printf("branch flag_passedPID_branch does not exist!\n");
exit(1);
   }
   flag_passedPID_isLoaded = true;
 }
 return flag_passedPID_;
}

const bool &hhtree::ph_isTight1() 
{
 if(not ph_isTight1_isLoaded)
 {
   if(ph_isTight1_branch != 0) ph_isTight1_branch->GetEntry(index);
   else
   {
     printf("branch ph_isTight1_branch does not exist!\n");
exit(1);
   }
   ph_isTight1_isLoaded = true;
 }
 return ph_isTight1_;
}

const bool &hhtree::ph_isTight2() 
{
 if(not ph_isTight2_isLoaded)
 {
   if(ph_isTight2_branch != 0) ph_isTight2_branch->GetEntry(index);
   else
   {
     printf("branch ph_isTight2_branch does not exist!\n");
exit(1);
   }
   ph_isTight2_isLoaded = true;
 }
 return ph_isTight2_;
}

const bool &hhtree::ph_isTight3() 
{
 if(not ph_isTight3_isLoaded)
 {
   if(ph_isTight3_branch != 0) ph_isTight3_branch->GetEntry(index);
   else
   {
     printf("branch ph_isTight3_branch does not exist!\n");
exit(1);
   }
   ph_isTight3_isLoaded = true;
 }
 return ph_isTight3_;
}

const bool &hhtree::ph_iso1() 
{
 if(not ph_iso1_isLoaded)
 {
   if(ph_iso1_branch != 0) ph_iso1_branch->GetEntry(index);
   else
   {
     printf("branch ph_iso1_branch does not exist!\n");
exit(1);
   }
   ph_iso1_isLoaded = true;
 }
 return ph_iso1_;
}

const bool &hhtree::ph_iso2() 
{
 if(not ph_iso2_isLoaded)
 {
   if(ph_iso2_branch != 0) ph_iso2_branch->GetEntry(index);
   else
   {
     printf("branch ph_iso2_branch does not exist!\n");
exit(1);
   }
   ph_iso2_isLoaded = true;
 }
 return ph_iso2_;
}

const bool &hhtree::ph_iso3() 
{
 if(not ph_iso3_isLoaded)
 {
   if(ph_iso3_branch != 0) ph_iso3_branch->GetEntry(index);
   else
   {
     printf("branch ph_iso3_branch does not exist!\n");
exit(1);
   }
   ph_iso3_isLoaded = true;
 }
 return ph_iso3_;
}

const double &hhtree::score_recotop1() 
{
 if(not score_recotop1_isLoaded)
 {
   if(score_recotop1_branch != 0) score_recotop1_branch->GetEntry(index);
   else
   {
     printf("branch score_recotop1_branch does not exist!\n");
exit(1);
   }
   score_recotop1_isLoaded = true;
 }
 return score_recotop1_;
}

const bool &hhtree::isPassedTriggerMatch() 
{
 if(not isPassedTriggerMatch_isLoaded)
 {
   if(isPassedTriggerMatch_branch != 0) isPassedTriggerMatch_branch->GetEntry(index);
   else
   {
     printf("branch isPassedTriggerMatch_branch does not exist!\n");
exit(1);
   }
   isPassedTriggerMatch_isLoaded = true;
 }
 return isPassedTriggerMatch_;
}

const float &hhtree::m_mpx() 
{
 if(not m_mpx_isLoaded)
 {
   if(m_mpx_branch != 0) m_mpx_branch->GetEntry(index);
   else
   {
     printf("branch m_mpx_branch does not exist!\n");
exit(1);
   }
   m_mpx_isLoaded = true;
 }
 return m_mpx_;
}

const float &hhtree::m_mpy() 
{
 if(not m_mpy_isLoaded)
 {
   if(m_mpy_branch != 0) m_mpy_branch->GetEntry(index);
   else
   {
     printf("branch m_mpy_branch does not exist!\n");
exit(1);
   }
   m_mpy_isLoaded = true;
 }
 return m_mpy_;
}

const float &hhtree::m_sumet() 
{
 if(not m_sumet_isLoaded)
 {
   if(m_sumet_branch != 0) m_sumet_branch->GetEntry(index);
   else
   {
     printf("branch m_sumet_branch does not exist!\n");
exit(1);
   }
   m_sumet_isLoaded = true;
 }
 return m_sumet_;
}

const float &hhtree::m_met() 
{
 if(not m_met_isLoaded)
 {
   if(m_met_branch != 0) m_met_branch->GetEntry(index);
   else
   {
     printf("branch m_met_branch does not exist!\n");
exit(1);
   }
   m_met_isLoaded = true;
 }
 return m_met_;
}

const float &hhtree::gnn_score() 
{
 if(not gnn_score_isLoaded)
 {
   if(gnn_score_branch != 0) gnn_score_branch->GetEntry(index);
   else
   {
     printf("branch gnn_score_branch does not exist!\n");
exit(1);
   }
   gnn_score_isLoaded = true;
 }
 return gnn_score_;
}

