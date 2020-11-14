#include "hhtree.hh"
hhtree hh; 

void hhtree::Init(TTree *tree) 
{

 weight_branch = tree->GetBranch("weight");
 if(weight_branch) weight_branch->SetAddress(&weight_);
 triggerEffWeight_branch = tree->GetBranch("triggerEffWeight");
 if(triggerEffWeight_branch) triggerEffWeight_branch->SetAddress(&triggerEffWeight_);
 pileupWeight_branch = tree->GetBranch("pileupWeight");
 if(pileupWeight_branch) pileupWeight_branch->SetAddress(&pileupWeight_);
 totalWeight_branch = tree->GetBranch("totalWeight");
 if(totalWeight_branch) totalWeight_branch->SetAddress(&totalWeight_);
 run_branch = tree->GetBranch("run");
 if(run_branch) run_branch->SetAddress(&run_);
 lumi_branch = tree->GetBranch("lumi");
 if(lumi_branch) lumi_branch->SetAddress(&lumi_);
 event_branch = tree->GetBranch("event");
 if(event_branch) event_branch->SetAddress(&event_);
 npu_branch = tree->GetBranch("npu");
 if(npu_branch) npu_branch->SetAddress(&npu_);
 rho_branch = tree->GetBranch("rho");
 if(rho_branch) rho_branch->SetAddress(&rho_);
 genHiggs1Pt_branch = tree->GetBranch("genHiggs1Pt");
 if(genHiggs1Pt_branch) genHiggs1Pt_branch->SetAddress(&genHiggs1Pt_);
 genHiggs1Eta_branch = tree->GetBranch("genHiggs1Eta");
 if(genHiggs1Eta_branch) genHiggs1Eta_branch->SetAddress(&genHiggs1Eta_);
 genHiggs1Phi_branch = tree->GetBranch("genHiggs1Phi");
 if(genHiggs1Phi_branch) genHiggs1Phi_branch->SetAddress(&genHiggs1Phi_);
 genHiggs2Pt_branch = tree->GetBranch("genHiggs2Pt");
 if(genHiggs2Pt_branch) genHiggs2Pt_branch->SetAddress(&genHiggs2Pt_);
 genHiggs2Eta_branch = tree->GetBranch("genHiggs2Eta");
 if(genHiggs2Eta_branch) genHiggs2Eta_branch->SetAddress(&genHiggs2Eta_);
 genHiggs2Phi_branch = tree->GetBranch("genHiggs2Phi");
 if(genHiggs2Phi_branch) genHiggs2Phi_branch->SetAddress(&genHiggs2Phi_);
 genHH_pt_branch = tree->GetBranch("genHH_pt");
 if(genHH_pt_branch) genHH_pt_branch->SetAddress(&genHH_pt_);
 genHH_eta_branch = tree->GetBranch("genHH_eta");
 if(genHH_eta_branch) genHH_eta_branch->SetAddress(&genHH_eta_);
 genHH_phi_branch = tree->GetBranch("genHH_phi");
 if(genHH_phi_branch) genHH_phi_branch->SetAddress(&genHH_phi_);
 genHH_mass_branch = tree->GetBranch("genHH_mass");
 if(genHH_mass_branch) genHH_mass_branch->SetAddress(&genHH_mass_);
 genLeptonId_branch = tree->GetBranch("genLeptonId");
 if(genLeptonId_branch) genLeptonId_branch->SetAddress(&genLeptonId_);
 genLeptonMotherId_branch = tree->GetBranch("genLeptonMotherId");
 if(genLeptonMotherId_branch) genLeptonMotherId_branch->SetAddress(&genLeptonMotherId_);
 genLeptonPt_branch = tree->GetBranch("genLeptonPt");
 if(genLeptonPt_branch) genLeptonPt_branch->SetAddress(&genLeptonPt_);
 genLeptonEta_branch = tree->GetBranch("genLeptonEta");
 if(genLeptonEta_branch) genLeptonEta_branch->SetAddress(&genLeptonEta_);
 genLeptonPhi_branch = tree->GetBranch("genLeptonPhi");
 if(genLeptonPhi_branch) genLeptonPhi_branch->SetAddress(&genLeptonPhi_);
 NJets_branch = tree->GetBranch("NJets");
 if(NJets_branch) NJets_branch->SetAddress(&NJets_);
 MET_branch = tree->GetBranch("MET");
 if(MET_branch) MET_branch->SetAddress(&MET_);
 fatJet1Pt_branch = tree->GetBranch("fatJet1Pt");
 if(fatJet1Pt_branch) fatJet1Pt_branch->SetAddress(&fatJet1Pt_);
 fatJet1Eta_branch = tree->GetBranch("fatJet1Eta");
 if(fatJet1Eta_branch) fatJet1Eta_branch->SetAddress(&fatJet1Eta_);
 fatJet1Phi_branch = tree->GetBranch("fatJet1Phi");
 if(fatJet1Phi_branch) fatJet1Phi_branch->SetAddress(&fatJet1Phi_);
 fatJet1Mass_branch = tree->GetBranch("fatJet1Mass");
 if(fatJet1Mass_branch) fatJet1Mass_branch->SetAddress(&fatJet1Mass_);
 fatJet1MassSD_branch = tree->GetBranch("fatJet1MassSD");
 if(fatJet1MassSD_branch) fatJet1MassSD_branch->SetAddress(&fatJet1MassSD_);
 fatJet1DDBTagger_branch = tree->GetBranch("fatJet1DDBTagger");
 if(fatJet1DDBTagger_branch) fatJet1DDBTagger_branch->SetAddress(&fatJet1DDBTagger_);
 fatJet1PNetXbb_branch = tree->GetBranch("fatJet1PNetXbb");
 if(fatJet1PNetXbb_branch) fatJet1PNetXbb_branch->SetAddress(&fatJet1PNetXbb_);
 fatJet1PNetQCDb_branch = tree->GetBranch("fatJet1PNetQCDb");
 if(fatJet1PNetQCDb_branch) fatJet1PNetQCDb_branch->SetAddress(&fatJet1PNetQCDb_);
 fatJet1PNetQCDbb_branch = tree->GetBranch("fatJet1PNetQCDbb");
 if(fatJet1PNetQCDbb_branch) fatJet1PNetQCDbb_branch->SetAddress(&fatJet1PNetQCDbb_);
 fatJet1PNetQCDc_branch = tree->GetBranch("fatJet1PNetQCDc");
 if(fatJet1PNetQCDc_branch) fatJet1PNetQCDc_branch->SetAddress(&fatJet1PNetQCDc_);
 fatJet1PNetQCDcc_branch = tree->GetBranch("fatJet1PNetQCDcc");
 if(fatJet1PNetQCDcc_branch) fatJet1PNetQCDcc_branch->SetAddress(&fatJet1PNetQCDcc_);
 fatJet1PNetQCDothers_branch = tree->GetBranch("fatJet1PNetQCDothers");
 if(fatJet1PNetQCDothers_branch) fatJet1PNetQCDothers_branch->SetAddress(&fatJet1PNetQCDothers_);
 fatJet1GenMatchIndex_branch = tree->GetBranch("fatJet1GenMatchIndex");
 if(fatJet1GenMatchIndex_branch) fatJet1GenMatchIndex_branch->SetAddress(&fatJet1GenMatchIndex_);
 fatJet1Tau3OverTau2_branch = tree->GetBranch("fatJet1Tau3OverTau2");
 if(fatJet1Tau3OverTau2_branch) fatJet1Tau3OverTau2_branch->SetAddress(&fatJet1Tau3OverTau2_);
 fatJet1HasMuon_branch = tree->GetBranch("fatJet1HasMuon");
 if(fatJet1HasMuon_branch) fatJet1HasMuon_branch->SetAddress(&fatJet1HasMuon_);
 fatJet1HasElectron_branch = tree->GetBranch("fatJet1HasElectron");
 if(fatJet1HasElectron_branch) fatJet1HasElectron_branch->SetAddress(&fatJet1HasElectron_);
 fatJet1HasBJetCSVLoose_branch = tree->GetBranch("fatJet1HasBJetCSVLoose");
 if(fatJet1HasBJetCSVLoose_branch) fatJet1HasBJetCSVLoose_branch->SetAddress(&fatJet1HasBJetCSVLoose_);
 fatJet1HasBJetCSVMedium_branch = tree->GetBranch("fatJet1HasBJetCSVMedium");
 if(fatJet1HasBJetCSVMedium_branch) fatJet1HasBJetCSVMedium_branch->SetAddress(&fatJet1HasBJetCSVMedium_);
 fatJet1HasBJetCSVTight_branch = tree->GetBranch("fatJet1HasBJetCSVTight");
 if(fatJet1HasBJetCSVTight_branch) fatJet1HasBJetCSVTight_branch->SetAddress(&fatJet1HasBJetCSVTight_);
 fatJet2Pt_branch = tree->GetBranch("fatJet2Pt");
 if(fatJet2Pt_branch) fatJet2Pt_branch->SetAddress(&fatJet2Pt_);
 fatJet2Eta_branch = tree->GetBranch("fatJet2Eta");
 if(fatJet2Eta_branch) fatJet2Eta_branch->SetAddress(&fatJet2Eta_);
 fatJet2Phi_branch = tree->GetBranch("fatJet2Phi");
 if(fatJet2Phi_branch) fatJet2Phi_branch->SetAddress(&fatJet2Phi_);
 fatJet2Mass_branch = tree->GetBranch("fatJet2Mass");
 if(fatJet2Mass_branch) fatJet2Mass_branch->SetAddress(&fatJet2Mass_);
 fatJet2MassSD_branch = tree->GetBranch("fatJet2MassSD");
 if(fatJet2MassSD_branch) fatJet2MassSD_branch->SetAddress(&fatJet2MassSD_);
 fatJet2DDBTagger_branch = tree->GetBranch("fatJet2DDBTagger");
 if(fatJet2DDBTagger_branch) fatJet2DDBTagger_branch->SetAddress(&fatJet2DDBTagger_);
 fatJet2PNetXbb_branch = tree->GetBranch("fatJet2PNetXbb");
 if(fatJet2PNetXbb_branch) fatJet2PNetXbb_branch->SetAddress(&fatJet2PNetXbb_);
 fatJet2PNetQCDb_branch = tree->GetBranch("fatJet2PNetQCDb");
 if(fatJet2PNetQCDb_branch) fatJet2PNetQCDb_branch->SetAddress(&fatJet2PNetQCDb_);
 fatJet2PNetQCDbb_branch = tree->GetBranch("fatJet2PNetQCDbb");
 if(fatJet2PNetQCDbb_branch) fatJet2PNetQCDbb_branch->SetAddress(&fatJet2PNetQCDbb_);
 fatJet2PNetQCDc_branch = tree->GetBranch("fatJet2PNetQCDc");
 if(fatJet2PNetQCDc_branch) fatJet2PNetQCDc_branch->SetAddress(&fatJet2PNetQCDc_);
 fatJet2PNetQCDcc_branch = tree->GetBranch("fatJet2PNetQCDcc");
 if(fatJet2PNetQCDcc_branch) fatJet2PNetQCDcc_branch->SetAddress(&fatJet2PNetQCDcc_);
 fatJet2PNetQCDothers_branch = tree->GetBranch("fatJet2PNetQCDothers");
 if(fatJet2PNetQCDothers_branch) fatJet2PNetQCDothers_branch->SetAddress(&fatJet2PNetQCDothers_);
 fatJet2GenMatchIndex_branch = tree->GetBranch("fatJet2GenMatchIndex");
 if(fatJet2GenMatchIndex_branch) fatJet2GenMatchIndex_branch->SetAddress(&fatJet2GenMatchIndex_);
 fatJet2Tau3OverTau2_branch = tree->GetBranch("fatJet2Tau3OverTau2");
 if(fatJet2Tau3OverTau2_branch) fatJet2Tau3OverTau2_branch->SetAddress(&fatJet2Tau3OverTau2_);
 fatJet2HasMuon_branch = tree->GetBranch("fatJet2HasMuon");
 if(fatJet2HasMuon_branch) fatJet2HasMuon_branch->SetAddress(&fatJet2HasMuon_);
 fatJet2HasElectron_branch = tree->GetBranch("fatJet2HasElectron");
 if(fatJet2HasElectron_branch) fatJet2HasElectron_branch->SetAddress(&fatJet2HasElectron_);
 fatJet2HasBJetCSVLoose_branch = tree->GetBranch("fatJet2HasBJetCSVLoose");
 if(fatJet2HasBJetCSVLoose_branch) fatJet2HasBJetCSVLoose_branch->SetAddress(&fatJet2HasBJetCSVLoose_);
 fatJet2HasBJetCSVMedium_branch = tree->GetBranch("fatJet2HasBJetCSVMedium");
 if(fatJet2HasBJetCSVMedium_branch) fatJet2HasBJetCSVMedium_branch->SetAddress(&fatJet2HasBJetCSVMedium_);
 fatJet2HasBJetCSVTight_branch = tree->GetBranch("fatJet2HasBJetCSVTight");
 if(fatJet2HasBJetCSVTight_branch) fatJet2HasBJetCSVTight_branch->SetAddress(&fatJet2HasBJetCSVTight_);
 fatJet3Pt_branch = tree->GetBranch("fatJet3Pt");
 if(fatJet3Pt_branch) fatJet3Pt_branch->SetAddress(&fatJet3Pt_);
 fatJet3Eta_branch = tree->GetBranch("fatJet3Eta");
 if(fatJet3Eta_branch) fatJet3Eta_branch->SetAddress(&fatJet3Eta_);
 fatJet3Phi_branch = tree->GetBranch("fatJet3Phi");
 if(fatJet3Phi_branch) fatJet3Phi_branch->SetAddress(&fatJet3Phi_);
 fatJet3Mass_branch = tree->GetBranch("fatJet3Mass");
 if(fatJet3Mass_branch) fatJet3Mass_branch->SetAddress(&fatJet3Mass_);
 fatJet3MassSD_branch = tree->GetBranch("fatJet3MassSD");
 if(fatJet3MassSD_branch) fatJet3MassSD_branch->SetAddress(&fatJet3MassSD_);
 fatJet3DDBTagger_branch = tree->GetBranch("fatJet3DDBTagger");
 if(fatJet3DDBTagger_branch) fatJet3DDBTagger_branch->SetAddress(&fatJet3DDBTagger_);
 fatJet3PNetXbb_branch = tree->GetBranch("fatJet3PNetXbb");
 if(fatJet3PNetXbb_branch) fatJet3PNetXbb_branch->SetAddress(&fatJet3PNetXbb_);
 fatJet3PNetQCDb_branch = tree->GetBranch("fatJet3PNetQCDb");
 if(fatJet3PNetQCDb_branch) fatJet3PNetQCDb_branch->SetAddress(&fatJet3PNetQCDb_);
 fatJet3PNetQCDbb_branch = tree->GetBranch("fatJet3PNetQCDbb");
 if(fatJet3PNetQCDbb_branch) fatJet3PNetQCDbb_branch->SetAddress(&fatJet3PNetQCDbb_);
 fatJet3PNetQCDc_branch = tree->GetBranch("fatJet3PNetQCDc");
 if(fatJet3PNetQCDc_branch) fatJet3PNetQCDc_branch->SetAddress(&fatJet3PNetQCDc_);
 fatJet3PNetQCDcc_branch = tree->GetBranch("fatJet3PNetQCDcc");
 if(fatJet3PNetQCDcc_branch) fatJet3PNetQCDcc_branch->SetAddress(&fatJet3PNetQCDcc_);
 fatJet3PNetQCDothers_branch = tree->GetBranch("fatJet3PNetQCDothers");
 if(fatJet3PNetQCDothers_branch) fatJet3PNetQCDothers_branch->SetAddress(&fatJet3PNetQCDothers_);
 fatJet3Tau3OverTau2_branch = tree->GetBranch("fatJet3Tau3OverTau2");
 if(fatJet3Tau3OverTau2_branch) fatJet3Tau3OverTau2_branch->SetAddress(&fatJet3Tau3OverTau2_);
 fatJet3HasMuon_branch = tree->GetBranch("fatJet3HasMuon");
 if(fatJet3HasMuon_branch) fatJet3HasMuon_branch->SetAddress(&fatJet3HasMuon_);
 fatJet3HasElectron_branch = tree->GetBranch("fatJet3HasElectron");
 if(fatJet3HasElectron_branch) fatJet3HasElectron_branch->SetAddress(&fatJet3HasElectron_);
 fatJet3HasBJetCSVLoose_branch = tree->GetBranch("fatJet3HasBJetCSVLoose");
 if(fatJet3HasBJetCSVLoose_branch) fatJet3HasBJetCSVLoose_branch->SetAddress(&fatJet3HasBJetCSVLoose_);
 fatJet3HasBJetCSVMedium_branch = tree->GetBranch("fatJet3HasBJetCSVMedium");
 if(fatJet3HasBJetCSVMedium_branch) fatJet3HasBJetCSVMedium_branch->SetAddress(&fatJet3HasBJetCSVMedium_);
 fatJet3HasBJetCSVTight_branch = tree->GetBranch("fatJet3HasBJetCSVTight");
 if(fatJet3HasBJetCSVTight_branch) fatJet3HasBJetCSVTight_branch->SetAddress(&fatJet3HasBJetCSVTight_);
 hh_pt_branch = tree->GetBranch("hh_pt");
 if(hh_pt_branch) hh_pt_branch->SetAddress(&hh_pt_);
 hh_eta_branch = tree->GetBranch("hh_eta");
 if(hh_eta_branch) hh_eta_branch->SetAddress(&hh_eta_);
 hh_phi_branch = tree->GetBranch("hh_phi");
 if(hh_phi_branch) hh_phi_branch->SetAddress(&hh_phi_);
 hh_mass_branch = tree->GetBranch("hh_mass");
 if(hh_mass_branch) hh_mass_branch->SetAddress(&hh_mass_);
 fatJet1PtOverMHH_branch = tree->GetBranch("fatJet1PtOverMHH");
 if(fatJet1PtOverMHH_branch) fatJet1PtOverMHH_branch->SetAddress(&fatJet1PtOverMHH_);
 fatJet1PtOverMSD_branch = tree->GetBranch("fatJet1PtOverMSD");
 if(fatJet1PtOverMSD_branch) fatJet1PtOverMSD_branch->SetAddress(&fatJet1PtOverMSD_);
 fatJet2PtOverMHH_branch = tree->GetBranch("fatJet2PtOverMHH");
 if(fatJet2PtOverMHH_branch) fatJet2PtOverMHH_branch->SetAddress(&fatJet2PtOverMHH_);
 fatJet2PtOverMSD_branch = tree->GetBranch("fatJet2PtOverMSD");
 if(fatJet2PtOverMSD_branch) fatJet2PtOverMSD_branch->SetAddress(&fatJet2PtOverMSD_);
 deltaEta_j1j2_branch = tree->GetBranch("deltaEta_j1j2");
 if(deltaEta_j1j2_branch) deltaEta_j1j2_branch->SetAddress(&deltaEta_j1j2_);
 deltaPhi_j1j2_branch = tree->GetBranch("deltaPhi_j1j2");
 if(deltaPhi_j1j2_branch) deltaPhi_j1j2_branch->SetAddress(&deltaPhi_j1j2_);
 deltaR_j1j2_branch = tree->GetBranch("deltaR_j1j2");
 if(deltaR_j1j2_branch) deltaR_j1j2_branch->SetAddress(&deltaR_j1j2_);
 ptj2_over_ptj1_branch = tree->GetBranch("ptj2_over_ptj1");
 if(ptj2_over_ptj1_branch) ptj2_over_ptj1_branch->SetAddress(&ptj2_over_ptj1_);
 mj2_over_mj1_branch = tree->GetBranch("mj2_over_mj1");
 if(mj2_over_mj1_branch) mj2_over_mj1_branch->SetAddress(&mj2_over_mj1_);
 lep1Pt_branch = tree->GetBranch("lep1Pt");
 if(lep1Pt_branch) lep1Pt_branch->SetAddress(&lep1Pt_);
 lep1Eta_branch = tree->GetBranch("lep1Eta");
 if(lep1Eta_branch) lep1Eta_branch->SetAddress(&lep1Eta_);
 lep1Phi_branch = tree->GetBranch("lep1Phi");
 if(lep1Phi_branch) lep1Phi_branch->SetAddress(&lep1Phi_);
 lep1Id_branch = tree->GetBranch("lep1Id");
 if(lep1Id_branch) lep1Id_branch->SetAddress(&lep1Id_);
 lep2Pt_branch = tree->GetBranch("lep2Pt");
 if(lep2Pt_branch) lep2Pt_branch->SetAddress(&lep2Pt_);
 lep2Eta_branch = tree->GetBranch("lep2Eta");
 if(lep2Eta_branch) lep2Eta_branch->SetAddress(&lep2Eta_);
 lep2Phi_branch = tree->GetBranch("lep2Phi");
 if(lep2Phi_branch) lep2Phi_branch->SetAddress(&lep2Phi_);
 lep2Id_branch = tree->GetBranch("lep2Id");
 if(lep2Id_branch) lep2Id_branch->SetAddress(&lep2Id_);
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
 HLT_AK8PFHT750_TrimMass50_branch = tree->GetBranch("HLT_AK8PFHT750_TrimMass50");
 if(HLT_AK8PFHT750_TrimMass50_branch) HLT_AK8PFHT750_TrimMass50_branch->SetAddress(&HLT_AK8PFHT750_TrimMass50_);
 HLT_AK8PFHT800_TrimMass50_branch = tree->GetBranch("HLT_AK8PFHT800_TrimMass50");
 if(HLT_AK8PFHT800_TrimMass50_branch) HLT_AK8PFHT800_TrimMass50_branch->SetAddress(&HLT_AK8PFHT800_TrimMass50_);
 HLT_AK8PFHT850_TrimMass50_branch = tree->GetBranch("HLT_AK8PFHT850_TrimMass50");
 if(HLT_AK8PFHT850_TrimMass50_branch) HLT_AK8PFHT850_TrimMass50_branch->SetAddress(&HLT_AK8PFHT850_TrimMass50_);
 HLT_AK8PFHT900_TrimMass50_branch = tree->GetBranch("HLT_AK8PFHT900_TrimMass50");
 if(HLT_AK8PFHT900_TrimMass50_branch) HLT_AK8PFHT900_TrimMass50_branch->SetAddress(&HLT_AK8PFHT900_TrimMass50_);
 HLT_PFJet450_branch = tree->GetBranch("HLT_PFJet450");
 if(HLT_PFJet450_branch) HLT_PFJet450_branch->SetAddress(&HLT_PFJet450_);
 HLT_PFJet500_branch = tree->GetBranch("HLT_PFJet500");
 if(HLT_PFJet500_branch) HLT_PFJet500_branch->SetAddress(&HLT_PFJet500_);
 HLT_PFJet550_branch = tree->GetBranch("HLT_PFJet550");
 if(HLT_PFJet550_branch) HLT_PFJet550_branch->SetAddress(&HLT_PFJet550_);
 HLT_AK8PFJet450_branch = tree->GetBranch("HLT_AK8PFJet450");
 if(HLT_AK8PFJet450_branch) HLT_AK8PFJet450_branch->SetAddress(&HLT_AK8PFJet450_);
 HLT_AK8PFJet500_branch = tree->GetBranch("HLT_AK8PFJet500");
 if(HLT_AK8PFJet500_branch) HLT_AK8PFJet500_branch->SetAddress(&HLT_AK8PFJet500_);
 HLT_AK8PFJet550_branch = tree->GetBranch("HLT_AK8PFJet550");
 if(HLT_AK8PFJet550_branch) HLT_AK8PFJet550_branch->SetAddress(&HLT_AK8PFJet550_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_);
 HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch = tree->GetBranch("HLT_AK8PFJet330_PFAK8BTagCSV_p17");
 if(HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch) HLT_AK8PFJet330_PFAK8BTagCSV_p17_branch->SetAddress(&HLT_AK8PFJet330_PFAK8BTagCSV_p17_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_);
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch = tree->GetBranch("HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4");
 if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch->SetAddress(&HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_);
 HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch = tree->GetBranch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20");
 if(HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch) HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch->SetAddress(&HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_);
 HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch = tree->GetBranch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087");
 if(HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch) HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch->SetAddress(&HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_);
 HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch = tree->GetBranch("HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087");
 if(HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch) HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch->SetAddress(&HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_);
 HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch = tree->GetBranch("HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20");
 if(HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch) HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch->SetAddress(&HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_);
 HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch = tree->GetBranch("HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20");
 if(HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch) HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch->SetAddress(&HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_);
 HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch = tree->GetBranch("HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20");
 if(HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch) HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch->SetAddress(&HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_);
 disc_qcd_and_ttbar_Run2_enhanced_v23_branch = tree->GetBranch("disc_qcd_and_ttbar_Run2_enhanced_v23");
 if(disc_qcd_and_ttbar_Run2_enhanced_v23_branch) disc_qcd_and_ttbar_Run2_enhanced_v23_branch->SetAddress(&disc_qcd_and_ttbar_Run2_enhanced_v23_);
 disc_qcd_and_ttbar_Run2_enhanced_v24_branch = tree->GetBranch("disc_qcd_and_ttbar_Run2_enhanced_v24");
 if(disc_qcd_and_ttbar_Run2_enhanced_v24_branch) disc_qcd_and_ttbar_Run2_enhanced_v24_branch->SetAddress(&disc_qcd_and_ttbar_Run2_enhanced_v24_);
}

void hhtree::GetEntry(unsigned int idx)
{

 index = idx;
 weight_isLoaded = false;
 triggerEffWeight_isLoaded = false;
 pileupWeight_isLoaded = false;
 totalWeight_isLoaded = false;
 run_isLoaded = false;
 lumi_isLoaded = false;
 event_isLoaded = false;
 npu_isLoaded = false;
 rho_isLoaded = false;
 genHiggs1Pt_isLoaded = false;
 genHiggs1Eta_isLoaded = false;
 genHiggs1Phi_isLoaded = false;
 genHiggs2Pt_isLoaded = false;
 genHiggs2Eta_isLoaded = false;
 genHiggs2Phi_isLoaded = false;
 genHH_pt_isLoaded = false;
 genHH_eta_isLoaded = false;
 genHH_phi_isLoaded = false;
 genHH_mass_isLoaded = false;
 genLeptonId_isLoaded = false;
 genLeptonMotherId_isLoaded = false;
 genLeptonPt_isLoaded = false;
 genLeptonEta_isLoaded = false;
 genLeptonPhi_isLoaded = false;
 NJets_isLoaded = false;
 MET_isLoaded = false;
 fatJet1Pt_isLoaded = false;
 fatJet1Eta_isLoaded = false;
 fatJet1Phi_isLoaded = false;
 fatJet1Mass_isLoaded = false;
 fatJet1MassSD_isLoaded = false;
 fatJet1DDBTagger_isLoaded = false;
 fatJet1PNetXbb_isLoaded = false;
 fatJet1PNetQCDb_isLoaded = false;
 fatJet1PNetQCDbb_isLoaded = false;
 fatJet1PNetQCDc_isLoaded = false;
 fatJet1PNetQCDcc_isLoaded = false;
 fatJet1PNetQCDothers_isLoaded = false;
 fatJet1GenMatchIndex_isLoaded = false;
 fatJet1Tau3OverTau2_isLoaded = false;
 fatJet1HasMuon_isLoaded = false;
 fatJet1HasElectron_isLoaded = false;
 fatJet1HasBJetCSVLoose_isLoaded = false;
 fatJet1HasBJetCSVMedium_isLoaded = false;
 fatJet1HasBJetCSVTight_isLoaded = false;
 fatJet2Pt_isLoaded = false;
 fatJet2Eta_isLoaded = false;
 fatJet2Phi_isLoaded = false;
 fatJet2Mass_isLoaded = false;
 fatJet2MassSD_isLoaded = false;
 fatJet2DDBTagger_isLoaded = false;
 fatJet2PNetXbb_isLoaded = false;
 fatJet2PNetQCDb_isLoaded = false;
 fatJet2PNetQCDbb_isLoaded = false;
 fatJet2PNetQCDc_isLoaded = false;
 fatJet2PNetQCDcc_isLoaded = false;
 fatJet2PNetQCDothers_isLoaded = false;
 fatJet2GenMatchIndex_isLoaded = false;
 fatJet2Tau3OverTau2_isLoaded = false;
 fatJet2HasMuon_isLoaded = false;
 fatJet2HasElectron_isLoaded = false;
 fatJet2HasBJetCSVLoose_isLoaded = false;
 fatJet2HasBJetCSVMedium_isLoaded = false;
 fatJet2HasBJetCSVTight_isLoaded = false;
 fatJet3Pt_isLoaded = false;
 fatJet3Eta_isLoaded = false;
 fatJet3Phi_isLoaded = false;
 fatJet3Mass_isLoaded = false;
 fatJet3MassSD_isLoaded = false;
 fatJet3DDBTagger_isLoaded = false;
 fatJet3PNetXbb_isLoaded = false;
 fatJet3PNetQCDb_isLoaded = false;
 fatJet3PNetQCDbb_isLoaded = false;
 fatJet3PNetQCDc_isLoaded = false;
 fatJet3PNetQCDcc_isLoaded = false;
 fatJet3PNetQCDothers_isLoaded = false;
 fatJet3Tau3OverTau2_isLoaded = false;
 fatJet3HasMuon_isLoaded = false;
 fatJet3HasElectron_isLoaded = false;
 fatJet3HasBJetCSVLoose_isLoaded = false;
 fatJet3HasBJetCSVMedium_isLoaded = false;
 fatJet3HasBJetCSVTight_isLoaded = false;
 hh_pt_isLoaded = false;
 hh_eta_isLoaded = false;
 hh_phi_isLoaded = false;
 hh_mass_isLoaded = false;
 fatJet1PtOverMHH_isLoaded = false;
 fatJet1PtOverMSD_isLoaded = false;
 fatJet2PtOverMHH_isLoaded = false;
 fatJet2PtOverMSD_isLoaded = false;
 deltaEta_j1j2_isLoaded = false;
 deltaPhi_j1j2_isLoaded = false;
 deltaR_j1j2_isLoaded = false;
 ptj2_over_ptj1_isLoaded = false;
 mj2_over_mj1_isLoaded = false;
 lep1Pt_isLoaded = false;
 lep1Eta_isLoaded = false;
 lep1Phi_isLoaded = false;
 lep1Id_isLoaded = false;
 lep2Pt_isLoaded = false;
 lep2Eta_isLoaded = false;
 lep2Phi_isLoaded = false;
 lep2Id_isLoaded = false;
 HLT_PFHT1050_isLoaded = false;
 HLT_AK8PFJet360_TrimMass30_isLoaded = false;
 HLT_AK8PFJet380_TrimMass30_isLoaded = false;
 HLT_AK8PFJet400_TrimMass30_isLoaded = false;
 HLT_AK8PFJet420_TrimMass30_isLoaded = false;
 HLT_AK8PFHT750_TrimMass50_isLoaded = false;
 HLT_AK8PFHT800_TrimMass50_isLoaded = false;
 HLT_AK8PFHT850_TrimMass50_isLoaded = false;
 HLT_AK8PFHT900_TrimMass50_isLoaded = false;
 HLT_PFJet450_isLoaded = false;
 HLT_PFJet500_isLoaded = false;
 HLT_PFJet550_isLoaded = false;
 HLT_AK8PFJet450_isLoaded = false;
 HLT_AK8PFJet500_isLoaded = false;
 HLT_AK8PFJet550_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p17_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BTagDeepCSV_p1_isLoaded = false;
 HLT_AK8PFJet330_PFAK8BTagCSV_p17_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_isLoaded = false;
 HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_isLoaded = false;
 HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_isLoaded = false;
 HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_isLoaded = false;
 HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_isLoaded = false;
 HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_isLoaded = false;
 HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_isLoaded = false;
 HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_isLoaded = false;
 disc_qcd_and_ttbar_Run2_enhanced_v23_isLoaded = false;
 disc_qcd_and_ttbar_Run2_enhanced_v24_isLoaded = false;
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

const float &hhtree::triggerEffWeight() 
{
 if(not triggerEffWeight_isLoaded)
 {
   if(triggerEffWeight_branch != 0) triggerEffWeight_branch->GetEntry(index);
   else
   {
     printf("branch triggerEffWeight_branch does not exist!\n");
exit(1);
   }
   triggerEffWeight_isLoaded = true;
 }
 return triggerEffWeight_;
}

const float &hhtree::pileupWeight() 
{
 if(not pileupWeight_isLoaded)
 {
   if(pileupWeight_branch != 0) pileupWeight_branch->GetEntry(index);
   else
   {
     printf("branch pileupWeight_branch does not exist!\n");
exit(1);
   }
   pileupWeight_isLoaded = true;
 }
 return pileupWeight_;
}

const float &hhtree::totalWeight() 
{
 if(not totalWeight_isLoaded)
 {
   if(totalWeight_branch != 0) totalWeight_branch->GetEntry(index);
   else
   {
     printf("branch totalWeight_branch does not exist!\n");
exit(1);
   }
   totalWeight_isLoaded = true;
 }
 return totalWeight_;
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

const unsigned int &hhtree::lumi() 
{
 if(not lumi_isLoaded)
 {
   if(lumi_branch != 0) lumi_branch->GetEntry(index);
   else
   {
     printf("branch lumi_branch does not exist!\n");
exit(1);
   }
   lumi_isLoaded = true;
 }
 return lumi_;
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

const float &hhtree::npu() 
{
 if(not npu_isLoaded)
 {
   if(npu_branch != 0) npu_branch->GetEntry(index);
   else
   {
     printf("branch npu_branch does not exist!\n");
exit(1);
   }
   npu_isLoaded = true;
 }
 return npu_;
}

const float &hhtree::rho() 
{
 if(not rho_isLoaded)
 {
   if(rho_branch != 0) rho_branch->GetEntry(index);
   else
   {
     printf("branch rho_branch does not exist!\n");
exit(1);
   }
   rho_isLoaded = true;
 }
 return rho_;
}

const float &hhtree::genHiggs1Pt() 
{
 if(not genHiggs1Pt_isLoaded)
 {
   if(genHiggs1Pt_branch != 0) genHiggs1Pt_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs1Pt_branch does not exist!\n");
exit(1);
   }
   genHiggs1Pt_isLoaded = true;
 }
 return genHiggs1Pt_;
}

const float &hhtree::genHiggs1Eta() 
{
 if(not genHiggs1Eta_isLoaded)
 {
   if(genHiggs1Eta_branch != 0) genHiggs1Eta_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs1Eta_branch does not exist!\n");
exit(1);
   }
   genHiggs1Eta_isLoaded = true;
 }
 return genHiggs1Eta_;
}

const float &hhtree::genHiggs1Phi() 
{
 if(not genHiggs1Phi_isLoaded)
 {
   if(genHiggs1Phi_branch != 0) genHiggs1Phi_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs1Phi_branch does not exist!\n");
exit(1);
   }
   genHiggs1Phi_isLoaded = true;
 }
 return genHiggs1Phi_;
}

const float &hhtree::genHiggs2Pt() 
{
 if(not genHiggs2Pt_isLoaded)
 {
   if(genHiggs2Pt_branch != 0) genHiggs2Pt_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs2Pt_branch does not exist!\n");
exit(1);
   }
   genHiggs2Pt_isLoaded = true;
 }
 return genHiggs2Pt_;
}

const float &hhtree::genHiggs2Eta() 
{
 if(not genHiggs2Eta_isLoaded)
 {
   if(genHiggs2Eta_branch != 0) genHiggs2Eta_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs2Eta_branch does not exist!\n");
exit(1);
   }
   genHiggs2Eta_isLoaded = true;
 }
 return genHiggs2Eta_;
}

const float &hhtree::genHiggs2Phi() 
{
 if(not genHiggs2Phi_isLoaded)
 {
   if(genHiggs2Phi_branch != 0) genHiggs2Phi_branch->GetEntry(index);
   else
   {
     printf("branch genHiggs2Phi_branch does not exist!\n");
exit(1);
   }
   genHiggs2Phi_isLoaded = true;
 }
 return genHiggs2Phi_;
}

const float &hhtree::genHH_pt() 
{
 if(not genHH_pt_isLoaded)
 {
   if(genHH_pt_branch != 0) genHH_pt_branch->GetEntry(index);
   else
   {
     printf("branch genHH_pt_branch does not exist!\n");
exit(1);
   }
   genHH_pt_isLoaded = true;
 }
 return genHH_pt_;
}

const float &hhtree::genHH_eta() 
{
 if(not genHH_eta_isLoaded)
 {
   if(genHH_eta_branch != 0) genHH_eta_branch->GetEntry(index);
   else
   {
     printf("branch genHH_eta_branch does not exist!\n");
exit(1);
   }
   genHH_eta_isLoaded = true;
 }
 return genHH_eta_;
}

const float &hhtree::genHH_phi() 
{
 if(not genHH_phi_isLoaded)
 {
   if(genHH_phi_branch != 0) genHH_phi_branch->GetEntry(index);
   else
   {
     printf("branch genHH_phi_branch does not exist!\n");
exit(1);
   }
   genHH_phi_isLoaded = true;
 }
 return genHH_phi_;
}

const float &hhtree::genHH_mass() 
{
 if(not genHH_mass_isLoaded)
 {
   if(genHH_mass_branch != 0) genHH_mass_branch->GetEntry(index);
   else
   {
     printf("branch genHH_mass_branch does not exist!\n");
exit(1);
   }
   genHH_mass_isLoaded = true;
 }
 return genHH_mass_;
}

const int &hhtree::genLeptonId() 
{
 if(not genLeptonId_isLoaded)
 {
   if(genLeptonId_branch != 0) genLeptonId_branch->GetEntry(index);
   else
   {
     printf("branch genLeptonId_branch does not exist!\n");
exit(1);
   }
   genLeptonId_isLoaded = true;
 }
 return genLeptonId_;
}

const int &hhtree::genLeptonMotherId() 
{
 if(not genLeptonMotherId_isLoaded)
 {
   if(genLeptonMotherId_branch != 0) genLeptonMotherId_branch->GetEntry(index);
   else
   {
     printf("branch genLeptonMotherId_branch does not exist!\n");
exit(1);
   }
   genLeptonMotherId_isLoaded = true;
 }
 return genLeptonMotherId_;
}

const float &hhtree::genLeptonPt() 
{
 if(not genLeptonPt_isLoaded)
 {
   if(genLeptonPt_branch != 0) genLeptonPt_branch->GetEntry(index);
   else
   {
     printf("branch genLeptonPt_branch does not exist!\n");
exit(1);
   }
   genLeptonPt_isLoaded = true;
 }
 return genLeptonPt_;
}

const float &hhtree::genLeptonEta() 
{
 if(not genLeptonEta_isLoaded)
 {
   if(genLeptonEta_branch != 0) genLeptonEta_branch->GetEntry(index);
   else
   {
     printf("branch genLeptonEta_branch does not exist!\n");
exit(1);
   }
   genLeptonEta_isLoaded = true;
 }
 return genLeptonEta_;
}

const float &hhtree::genLeptonPhi() 
{
 if(not genLeptonPhi_isLoaded)
 {
   if(genLeptonPhi_branch != 0) genLeptonPhi_branch->GetEntry(index);
   else
   {
     printf("branch genLeptonPhi_branch does not exist!\n");
exit(1);
   }
   genLeptonPhi_isLoaded = true;
 }
 return genLeptonPhi_;
}

const int &hhtree::NJets() 
{
 if(not NJets_isLoaded)
 {
   if(NJets_branch != 0) NJets_branch->GetEntry(index);
   else
   {
     printf("branch NJets_branch does not exist!\n");
exit(1);
   }
   NJets_isLoaded = true;
 }
 return NJets_;
}

const float &hhtree::MET() 
{
 if(not MET_isLoaded)
 {
   if(MET_branch != 0) MET_branch->GetEntry(index);
   else
   {
     printf("branch MET_branch does not exist!\n");
exit(1);
   }
   MET_isLoaded = true;
 }
 return MET_;
}

const float &hhtree::fatJet1Pt() 
{
 if(not fatJet1Pt_isLoaded)
 {
   if(fatJet1Pt_branch != 0) fatJet1Pt_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1Pt_branch does not exist!\n");
exit(1);
   }
   fatJet1Pt_isLoaded = true;
 }
 return fatJet1Pt_;
}

const float &hhtree::fatJet1Eta() 
{
 if(not fatJet1Eta_isLoaded)
 {
   if(fatJet1Eta_branch != 0) fatJet1Eta_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1Eta_branch does not exist!\n");
exit(1);
   }
   fatJet1Eta_isLoaded = true;
 }
 return fatJet1Eta_;
}

const float &hhtree::fatJet1Phi() 
{
 if(not fatJet1Phi_isLoaded)
 {
   if(fatJet1Phi_branch != 0) fatJet1Phi_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1Phi_branch does not exist!\n");
exit(1);
   }
   fatJet1Phi_isLoaded = true;
 }
 return fatJet1Phi_;
}

const float &hhtree::fatJet1Mass() 
{
 if(not fatJet1Mass_isLoaded)
 {
   if(fatJet1Mass_branch != 0) fatJet1Mass_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1Mass_branch does not exist!\n");
exit(1);
   }
   fatJet1Mass_isLoaded = true;
 }
 return fatJet1Mass_;
}

const float &hhtree::fatJet1MassSD() 
{
 if(not fatJet1MassSD_isLoaded)
 {
   if(fatJet1MassSD_branch != 0) fatJet1MassSD_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1MassSD_branch does not exist!\n");
exit(1);
   }
   fatJet1MassSD_isLoaded = true;
 }
 return fatJet1MassSD_;
}

const float &hhtree::fatJet1DDBTagger() 
{
 if(not fatJet1DDBTagger_isLoaded)
 {
   if(fatJet1DDBTagger_branch != 0) fatJet1DDBTagger_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1DDBTagger_branch does not exist!\n");
exit(1);
   }
   fatJet1DDBTagger_isLoaded = true;
 }
 return fatJet1DDBTagger_;
}

const float &hhtree::fatJet1PNetXbb() 
{
 if(not fatJet1PNetXbb_isLoaded)
 {
   if(fatJet1PNetXbb_branch != 0) fatJet1PNetXbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetXbb_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetXbb_isLoaded = true;
 }
 return fatJet1PNetXbb_;
}

const float &hhtree::fatJet1PNetQCDb() 
{
 if(not fatJet1PNetQCDb_isLoaded)
 {
   if(fatJet1PNetQCDb_branch != 0) fatJet1PNetQCDb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetQCDb_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetQCDb_isLoaded = true;
 }
 return fatJet1PNetQCDb_;
}

const float &hhtree::fatJet1PNetQCDbb() 
{
 if(not fatJet1PNetQCDbb_isLoaded)
 {
   if(fatJet1PNetQCDbb_branch != 0) fatJet1PNetQCDbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetQCDbb_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetQCDbb_isLoaded = true;
 }
 return fatJet1PNetQCDbb_;
}

const float &hhtree::fatJet1PNetQCDc() 
{
 if(not fatJet1PNetQCDc_isLoaded)
 {
   if(fatJet1PNetQCDc_branch != 0) fatJet1PNetQCDc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetQCDc_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetQCDc_isLoaded = true;
 }
 return fatJet1PNetQCDc_;
}

const float &hhtree::fatJet1PNetQCDcc() 
{
 if(not fatJet1PNetQCDcc_isLoaded)
 {
   if(fatJet1PNetQCDcc_branch != 0) fatJet1PNetQCDcc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetQCDcc_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetQCDcc_isLoaded = true;
 }
 return fatJet1PNetQCDcc_;
}

const float &hhtree::fatJet1PNetQCDothers() 
{
 if(not fatJet1PNetQCDothers_isLoaded)
 {
   if(fatJet1PNetQCDothers_branch != 0) fatJet1PNetQCDothers_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PNetQCDothers_branch does not exist!\n");
exit(1);
   }
   fatJet1PNetQCDothers_isLoaded = true;
 }
 return fatJet1PNetQCDothers_;
}

const int &hhtree::fatJet1GenMatchIndex() 
{
 if(not fatJet1GenMatchIndex_isLoaded)
 {
   if(fatJet1GenMatchIndex_branch != 0) fatJet1GenMatchIndex_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1GenMatchIndex_branch does not exist!\n");
exit(1);
   }
   fatJet1GenMatchIndex_isLoaded = true;
 }
 return fatJet1GenMatchIndex_;
}

const float &hhtree::fatJet1Tau3OverTau2() 
{
 if(not fatJet1Tau3OverTau2_isLoaded)
 {
   if(fatJet1Tau3OverTau2_branch != 0) fatJet1Tau3OverTau2_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1Tau3OverTau2_branch does not exist!\n");
exit(1);
   }
   fatJet1Tau3OverTau2_isLoaded = true;
 }
 return fatJet1Tau3OverTau2_;
}

const bool &hhtree::fatJet1HasMuon() 
{
 if(not fatJet1HasMuon_isLoaded)
 {
   if(fatJet1HasMuon_branch != 0) fatJet1HasMuon_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1HasMuon_branch does not exist!\n");
exit(1);
   }
   fatJet1HasMuon_isLoaded = true;
 }
 return fatJet1HasMuon_;
}

const bool &hhtree::fatJet1HasElectron() 
{
 if(not fatJet1HasElectron_isLoaded)
 {
   if(fatJet1HasElectron_branch != 0) fatJet1HasElectron_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1HasElectron_branch does not exist!\n");
exit(1);
   }
   fatJet1HasElectron_isLoaded = true;
 }
 return fatJet1HasElectron_;
}

const bool &hhtree::fatJet1HasBJetCSVLoose() 
{
 if(not fatJet1HasBJetCSVLoose_isLoaded)
 {
   if(fatJet1HasBJetCSVLoose_branch != 0) fatJet1HasBJetCSVLoose_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1HasBJetCSVLoose_branch does not exist!\n");
exit(1);
   }
   fatJet1HasBJetCSVLoose_isLoaded = true;
 }
 return fatJet1HasBJetCSVLoose_;
}

const bool &hhtree::fatJet1HasBJetCSVMedium() 
{
 if(not fatJet1HasBJetCSVMedium_isLoaded)
 {
   if(fatJet1HasBJetCSVMedium_branch != 0) fatJet1HasBJetCSVMedium_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1HasBJetCSVMedium_branch does not exist!\n");
exit(1);
   }
   fatJet1HasBJetCSVMedium_isLoaded = true;
 }
 return fatJet1HasBJetCSVMedium_;
}

const bool &hhtree::fatJet1HasBJetCSVTight() 
{
 if(not fatJet1HasBJetCSVTight_isLoaded)
 {
   if(fatJet1HasBJetCSVTight_branch != 0) fatJet1HasBJetCSVTight_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1HasBJetCSVTight_branch does not exist!\n");
exit(1);
   }
   fatJet1HasBJetCSVTight_isLoaded = true;
 }
 return fatJet1HasBJetCSVTight_;
}

const float &hhtree::fatJet2Pt() 
{
 if(not fatJet2Pt_isLoaded)
 {
   if(fatJet2Pt_branch != 0) fatJet2Pt_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2Pt_branch does not exist!\n");
exit(1);
   }
   fatJet2Pt_isLoaded = true;
 }
 return fatJet2Pt_;
}

const float &hhtree::fatJet2Eta() 
{
 if(not fatJet2Eta_isLoaded)
 {
   if(fatJet2Eta_branch != 0) fatJet2Eta_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2Eta_branch does not exist!\n");
exit(1);
   }
   fatJet2Eta_isLoaded = true;
 }
 return fatJet2Eta_;
}

const float &hhtree::fatJet2Phi() 
{
 if(not fatJet2Phi_isLoaded)
 {
   if(fatJet2Phi_branch != 0) fatJet2Phi_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2Phi_branch does not exist!\n");
exit(1);
   }
   fatJet2Phi_isLoaded = true;
 }
 return fatJet2Phi_;
}

const float &hhtree::fatJet2Mass() 
{
 if(not fatJet2Mass_isLoaded)
 {
   if(fatJet2Mass_branch != 0) fatJet2Mass_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2Mass_branch does not exist!\n");
exit(1);
   }
   fatJet2Mass_isLoaded = true;
 }
 return fatJet2Mass_;
}

const float &hhtree::fatJet2MassSD() 
{
 if(not fatJet2MassSD_isLoaded)
 {
   if(fatJet2MassSD_branch != 0) fatJet2MassSD_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2MassSD_branch does not exist!\n");
exit(1);
   }
   fatJet2MassSD_isLoaded = true;
 }
 return fatJet2MassSD_;
}

const float &hhtree::fatJet2DDBTagger() 
{
 if(not fatJet2DDBTagger_isLoaded)
 {
   if(fatJet2DDBTagger_branch != 0) fatJet2DDBTagger_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2DDBTagger_branch does not exist!\n");
exit(1);
   }
   fatJet2DDBTagger_isLoaded = true;
 }
 return fatJet2DDBTagger_;
}

const float &hhtree::fatJet2PNetXbb() 
{
 if(not fatJet2PNetXbb_isLoaded)
 {
   if(fatJet2PNetXbb_branch != 0) fatJet2PNetXbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetXbb_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetXbb_isLoaded = true;
 }
 return fatJet2PNetXbb_;
}

const float &hhtree::fatJet2PNetQCDb() 
{
 if(not fatJet2PNetQCDb_isLoaded)
 {
   if(fatJet2PNetQCDb_branch != 0) fatJet2PNetQCDb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetQCDb_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetQCDb_isLoaded = true;
 }
 return fatJet2PNetQCDb_;
}

const float &hhtree::fatJet2PNetQCDbb() 
{
 if(not fatJet2PNetQCDbb_isLoaded)
 {
   if(fatJet2PNetQCDbb_branch != 0) fatJet2PNetQCDbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetQCDbb_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetQCDbb_isLoaded = true;
 }
 return fatJet2PNetQCDbb_;
}

const float &hhtree::fatJet2PNetQCDc() 
{
 if(not fatJet2PNetQCDc_isLoaded)
 {
   if(fatJet2PNetQCDc_branch != 0) fatJet2PNetQCDc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetQCDc_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetQCDc_isLoaded = true;
 }
 return fatJet2PNetQCDc_;
}

const float &hhtree::fatJet2PNetQCDcc() 
{
 if(not fatJet2PNetQCDcc_isLoaded)
 {
   if(fatJet2PNetQCDcc_branch != 0) fatJet2PNetQCDcc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetQCDcc_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetQCDcc_isLoaded = true;
 }
 return fatJet2PNetQCDcc_;
}

const float &hhtree::fatJet2PNetQCDothers() 
{
 if(not fatJet2PNetQCDothers_isLoaded)
 {
   if(fatJet2PNetQCDothers_branch != 0) fatJet2PNetQCDothers_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PNetQCDothers_branch does not exist!\n");
exit(1);
   }
   fatJet2PNetQCDothers_isLoaded = true;
 }
 return fatJet2PNetQCDothers_;
}

const int &hhtree::fatJet2GenMatchIndex() 
{
 if(not fatJet2GenMatchIndex_isLoaded)
 {
   if(fatJet2GenMatchIndex_branch != 0) fatJet2GenMatchIndex_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2GenMatchIndex_branch does not exist!\n");
exit(1);
   }
   fatJet2GenMatchIndex_isLoaded = true;
 }
 return fatJet2GenMatchIndex_;
}

const float &hhtree::fatJet2Tau3OverTau2() 
{
 if(not fatJet2Tau3OverTau2_isLoaded)
 {
   if(fatJet2Tau3OverTau2_branch != 0) fatJet2Tau3OverTau2_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2Tau3OverTau2_branch does not exist!\n");
exit(1);
   }
   fatJet2Tau3OverTau2_isLoaded = true;
 }
 return fatJet2Tau3OverTau2_;
}

const bool &hhtree::fatJet2HasMuon() 
{
 if(not fatJet2HasMuon_isLoaded)
 {
   if(fatJet2HasMuon_branch != 0) fatJet2HasMuon_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2HasMuon_branch does not exist!\n");
exit(1);
   }
   fatJet2HasMuon_isLoaded = true;
 }
 return fatJet2HasMuon_;
}

const bool &hhtree::fatJet2HasElectron() 
{
 if(not fatJet2HasElectron_isLoaded)
 {
   if(fatJet2HasElectron_branch != 0) fatJet2HasElectron_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2HasElectron_branch does not exist!\n");
exit(1);
   }
   fatJet2HasElectron_isLoaded = true;
 }
 return fatJet2HasElectron_;
}

const bool &hhtree::fatJet2HasBJetCSVLoose() 
{
 if(not fatJet2HasBJetCSVLoose_isLoaded)
 {
   if(fatJet2HasBJetCSVLoose_branch != 0) fatJet2HasBJetCSVLoose_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2HasBJetCSVLoose_branch does not exist!\n");
exit(1);
   }
   fatJet2HasBJetCSVLoose_isLoaded = true;
 }
 return fatJet2HasBJetCSVLoose_;
}

const bool &hhtree::fatJet2HasBJetCSVMedium() 
{
 if(not fatJet2HasBJetCSVMedium_isLoaded)
 {
   if(fatJet2HasBJetCSVMedium_branch != 0) fatJet2HasBJetCSVMedium_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2HasBJetCSVMedium_branch does not exist!\n");
exit(1);
   }
   fatJet2HasBJetCSVMedium_isLoaded = true;
 }
 return fatJet2HasBJetCSVMedium_;
}

const bool &hhtree::fatJet2HasBJetCSVTight() 
{
 if(not fatJet2HasBJetCSVTight_isLoaded)
 {
   if(fatJet2HasBJetCSVTight_branch != 0) fatJet2HasBJetCSVTight_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2HasBJetCSVTight_branch does not exist!\n");
exit(1);
   }
   fatJet2HasBJetCSVTight_isLoaded = true;
 }
 return fatJet2HasBJetCSVTight_;
}

const float &hhtree::fatJet3Pt() 
{
 if(not fatJet3Pt_isLoaded)
 {
   if(fatJet3Pt_branch != 0) fatJet3Pt_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3Pt_branch does not exist!\n");
exit(1);
   }
   fatJet3Pt_isLoaded = true;
 }
 return fatJet3Pt_;
}

const float &hhtree::fatJet3Eta() 
{
 if(not fatJet3Eta_isLoaded)
 {
   if(fatJet3Eta_branch != 0) fatJet3Eta_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3Eta_branch does not exist!\n");
exit(1);
   }
   fatJet3Eta_isLoaded = true;
 }
 return fatJet3Eta_;
}

const float &hhtree::fatJet3Phi() 
{
 if(not fatJet3Phi_isLoaded)
 {
   if(fatJet3Phi_branch != 0) fatJet3Phi_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3Phi_branch does not exist!\n");
exit(1);
   }
   fatJet3Phi_isLoaded = true;
 }
 return fatJet3Phi_;
}

const float &hhtree::fatJet3Mass() 
{
 if(not fatJet3Mass_isLoaded)
 {
   if(fatJet3Mass_branch != 0) fatJet3Mass_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3Mass_branch does not exist!\n");
exit(1);
   }
   fatJet3Mass_isLoaded = true;
 }
 return fatJet3Mass_;
}

const float &hhtree::fatJet3MassSD() 
{
 if(not fatJet3MassSD_isLoaded)
 {
   if(fatJet3MassSD_branch != 0) fatJet3MassSD_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3MassSD_branch does not exist!\n");
exit(1);
   }
   fatJet3MassSD_isLoaded = true;
 }
 return fatJet3MassSD_;
}

const float &hhtree::fatJet3DDBTagger() 
{
 if(not fatJet3DDBTagger_isLoaded)
 {
   if(fatJet3DDBTagger_branch != 0) fatJet3DDBTagger_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3DDBTagger_branch does not exist!\n");
exit(1);
   }
   fatJet3DDBTagger_isLoaded = true;
 }
 return fatJet3DDBTagger_;
}

const float &hhtree::fatJet3PNetXbb() 
{
 if(not fatJet3PNetXbb_isLoaded)
 {
   if(fatJet3PNetXbb_branch != 0) fatJet3PNetXbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetXbb_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetXbb_isLoaded = true;
 }
 return fatJet3PNetXbb_;
}

const float &hhtree::fatJet3PNetQCDb() 
{
 if(not fatJet3PNetQCDb_isLoaded)
 {
   if(fatJet3PNetQCDb_branch != 0) fatJet3PNetQCDb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetQCDb_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetQCDb_isLoaded = true;
 }
 return fatJet3PNetQCDb_;
}

const float &hhtree::fatJet3PNetQCDbb() 
{
 if(not fatJet3PNetQCDbb_isLoaded)
 {
   if(fatJet3PNetQCDbb_branch != 0) fatJet3PNetQCDbb_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetQCDbb_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetQCDbb_isLoaded = true;
 }
 return fatJet3PNetQCDbb_;
}

const float &hhtree::fatJet3PNetQCDc() 
{
 if(not fatJet3PNetQCDc_isLoaded)
 {
   if(fatJet3PNetQCDc_branch != 0) fatJet3PNetQCDc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetQCDc_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetQCDc_isLoaded = true;
 }
 return fatJet3PNetQCDc_;
}

const float &hhtree::fatJet3PNetQCDcc() 
{
 if(not fatJet3PNetQCDcc_isLoaded)
 {
   if(fatJet3PNetQCDcc_branch != 0) fatJet3PNetQCDcc_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetQCDcc_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetQCDcc_isLoaded = true;
 }
 return fatJet3PNetQCDcc_;
}

const float &hhtree::fatJet3PNetQCDothers() 
{
 if(not fatJet3PNetQCDothers_isLoaded)
 {
   if(fatJet3PNetQCDothers_branch != 0) fatJet3PNetQCDothers_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3PNetQCDothers_branch does not exist!\n");
exit(1);
   }
   fatJet3PNetQCDothers_isLoaded = true;
 }
 return fatJet3PNetQCDothers_;
}

const float &hhtree::fatJet3Tau3OverTau2() 
{
 if(not fatJet3Tau3OverTau2_isLoaded)
 {
   if(fatJet3Tau3OverTau2_branch != 0) fatJet3Tau3OverTau2_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3Tau3OverTau2_branch does not exist!\n");
exit(1);
   }
   fatJet3Tau3OverTau2_isLoaded = true;
 }
 return fatJet3Tau3OverTau2_;
}

const bool &hhtree::fatJet3HasMuon() 
{
 if(not fatJet3HasMuon_isLoaded)
 {
   if(fatJet3HasMuon_branch != 0) fatJet3HasMuon_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3HasMuon_branch does not exist!\n");
exit(1);
   }
   fatJet3HasMuon_isLoaded = true;
 }
 return fatJet3HasMuon_;
}

const bool &hhtree::fatJet3HasElectron() 
{
 if(not fatJet3HasElectron_isLoaded)
 {
   if(fatJet3HasElectron_branch != 0) fatJet3HasElectron_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3HasElectron_branch does not exist!\n");
exit(1);
   }
   fatJet3HasElectron_isLoaded = true;
 }
 return fatJet3HasElectron_;
}

const bool &hhtree::fatJet3HasBJetCSVLoose() 
{
 if(not fatJet3HasBJetCSVLoose_isLoaded)
 {
   if(fatJet3HasBJetCSVLoose_branch != 0) fatJet3HasBJetCSVLoose_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3HasBJetCSVLoose_branch does not exist!\n");
exit(1);
   }
   fatJet3HasBJetCSVLoose_isLoaded = true;
 }
 return fatJet3HasBJetCSVLoose_;
}

const bool &hhtree::fatJet3HasBJetCSVMedium() 
{
 if(not fatJet3HasBJetCSVMedium_isLoaded)
 {
   if(fatJet3HasBJetCSVMedium_branch != 0) fatJet3HasBJetCSVMedium_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3HasBJetCSVMedium_branch does not exist!\n");
exit(1);
   }
   fatJet3HasBJetCSVMedium_isLoaded = true;
 }
 return fatJet3HasBJetCSVMedium_;
}

const bool &hhtree::fatJet3HasBJetCSVTight() 
{
 if(not fatJet3HasBJetCSVTight_isLoaded)
 {
   if(fatJet3HasBJetCSVTight_branch != 0) fatJet3HasBJetCSVTight_branch->GetEntry(index);
   else
   {
     printf("branch fatJet3HasBJetCSVTight_branch does not exist!\n");
exit(1);
   }
   fatJet3HasBJetCSVTight_isLoaded = true;
 }
 return fatJet3HasBJetCSVTight_;
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

const float &hhtree::fatJet1PtOverMHH() 
{
 if(not fatJet1PtOverMHH_isLoaded)
 {
   if(fatJet1PtOverMHH_branch != 0) fatJet1PtOverMHH_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PtOverMHH_branch does not exist!\n");
exit(1);
   }
   fatJet1PtOverMHH_isLoaded = true;
 }
 return fatJet1PtOverMHH_;
}

const float &hhtree::fatJet1PtOverMSD() 
{
 if(not fatJet1PtOverMSD_isLoaded)
 {
   if(fatJet1PtOverMSD_branch != 0) fatJet1PtOverMSD_branch->GetEntry(index);
   else
   {
     printf("branch fatJet1PtOverMSD_branch does not exist!\n");
exit(1);
   }
   fatJet1PtOverMSD_isLoaded = true;
 }
 return fatJet1PtOverMSD_;
}

const float &hhtree::fatJet2PtOverMHH() 
{
 if(not fatJet2PtOverMHH_isLoaded)
 {
   if(fatJet2PtOverMHH_branch != 0) fatJet2PtOverMHH_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PtOverMHH_branch does not exist!\n");
exit(1);
   }
   fatJet2PtOverMHH_isLoaded = true;
 }
 return fatJet2PtOverMHH_;
}

const float &hhtree::fatJet2PtOverMSD() 
{
 if(not fatJet2PtOverMSD_isLoaded)
 {
   if(fatJet2PtOverMSD_branch != 0) fatJet2PtOverMSD_branch->GetEntry(index);
   else
   {
     printf("branch fatJet2PtOverMSD_branch does not exist!\n");
exit(1);
   }
   fatJet2PtOverMSD_isLoaded = true;
 }
 return fatJet2PtOverMSD_;
}

const float &hhtree::deltaEta_j1j2() 
{
 if(not deltaEta_j1j2_isLoaded)
 {
   if(deltaEta_j1j2_branch != 0) deltaEta_j1j2_branch->GetEntry(index);
   else
   {
     printf("branch deltaEta_j1j2_branch does not exist!\n");
exit(1);
   }
   deltaEta_j1j2_isLoaded = true;
 }
 return deltaEta_j1j2_;
}

const float &hhtree::deltaPhi_j1j2() 
{
 if(not deltaPhi_j1j2_isLoaded)
 {
   if(deltaPhi_j1j2_branch != 0) deltaPhi_j1j2_branch->GetEntry(index);
   else
   {
     printf("branch deltaPhi_j1j2_branch does not exist!\n");
exit(1);
   }
   deltaPhi_j1j2_isLoaded = true;
 }
 return deltaPhi_j1j2_;
}

const float &hhtree::deltaR_j1j2() 
{
 if(not deltaR_j1j2_isLoaded)
 {
   if(deltaR_j1j2_branch != 0) deltaR_j1j2_branch->GetEntry(index);
   else
   {
     printf("branch deltaR_j1j2_branch does not exist!\n");
exit(1);
   }
   deltaR_j1j2_isLoaded = true;
 }
 return deltaR_j1j2_;
}

const float &hhtree::ptj2_over_ptj1() 
{
 if(not ptj2_over_ptj1_isLoaded)
 {
   if(ptj2_over_ptj1_branch != 0) ptj2_over_ptj1_branch->GetEntry(index);
   else
   {
     printf("branch ptj2_over_ptj1_branch does not exist!\n");
exit(1);
   }
   ptj2_over_ptj1_isLoaded = true;
 }
 return ptj2_over_ptj1_;
}

const float &hhtree::mj2_over_mj1() 
{
 if(not mj2_over_mj1_isLoaded)
 {
   if(mj2_over_mj1_branch != 0) mj2_over_mj1_branch->GetEntry(index);
   else
   {
     printf("branch mj2_over_mj1_branch does not exist!\n");
exit(1);
   }
   mj2_over_mj1_isLoaded = true;
 }
 return mj2_over_mj1_;
}

const float &hhtree::lep1Pt()
{
 if(not lep1Pt_isLoaded)
 {
   if(lep1Pt_branch != 0) lep1Pt_branch->GetEntry(index);
   else
   {
     printf("branch lep1Pt_branch does not exist!\n");
exit(1);
   }
   lep1Pt_isLoaded = true;
 }
 return lep1Pt_;
}

const float &hhtree::lep1Eta()
{
 if(not lep1Eta_isLoaded)
 {
   if(lep1Eta_branch != 0) lep1Eta_branch->GetEntry(index);
   else
   {
     printf("branch lep1Eta_branch does not exist!\n");
exit(1);
   }
   lep1Eta_isLoaded = true;
 }
 return lep1Eta_;
}

const float &hhtree::lep1Phi()
{
 if(not lep1Phi_isLoaded)
 {
   if(lep1Phi_branch != 0) lep1Phi_branch->GetEntry(index);
   else
   {
     printf("branch lep1Phi_branch does not exist!\n");
exit(1);
   }
   lep1Phi_isLoaded = true;
 }
 return lep1Phi_;
}

const int &hhtree::lep1Id()
{
 if(not lep1Id_isLoaded)
 {
   if(lep1Id_branch != 0) lep1Id_branch->GetEntry(index);
   else
   {
     printf("branch lep1Id_branch does not exist!\n");
exit(1);
   }
   lep1Id_isLoaded = true;
 }
 return lep1Id_;
}

const float &hhtree::lep2Pt()
{
 if(not lep2Pt_isLoaded)
 {
   if(lep2Pt_branch != 0) lep2Pt_branch->GetEntry(index);
   else
   {
     printf("branch lep2Pt_branch does not exist!\n");
exit(1);
   }
   lep2Pt_isLoaded = true;
 }
 return lep2Pt_;
}

const float &hhtree::lep2Eta()
{
 if(not lep2Eta_isLoaded)
 {
   if(lep2Eta_branch != 0) lep2Eta_branch->GetEntry(index);
   else
   {
     printf("branch lep2Eta_branch does not exist!\n");
exit(1);
   }
   lep2Eta_isLoaded = true;
 }
 return lep2Eta_;
}
const float &hhtree::lep2Phi()
{
 if(not lep2Phi_isLoaded)
 {
   if(lep2Phi_branch != 0) lep2Phi_branch->GetEntry(index);
   else
   {
     printf("branch lep2Phi_branch does not exist!\n");
exit(1);
   }
   lep2Phi_isLoaded = true;
 }
 return lep2Phi_;
}

const int &hhtree::lep2Id()
{
 if(not lep2Id_isLoaded)
 {
   if(lep2Id_branch != 0) lep2Id_branch->GetEntry(index);
   else
   {
     printf("branch lep2Id_branch does not exist!\n");
exit(1);
   }
   lep2Id_isLoaded = true;
 }
 return lep2Id_;
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

const bool &hhtree::HLT_AK8PFHT750_TrimMass50() 
{
 if(not HLT_AK8PFHT750_TrimMass50_isLoaded)
 {
   if(HLT_AK8PFHT750_TrimMass50_branch != 0) HLT_AK8PFHT750_TrimMass50_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFHT750_TrimMass50_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFHT750_TrimMass50_isLoaded = true;
 }
 return HLT_AK8PFHT750_TrimMass50_;
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

const bool &hhtree::HLT_AK8PFHT850_TrimMass50() 
{
 if(not HLT_AK8PFHT850_TrimMass50_isLoaded)
 {
   if(HLT_AK8PFHT850_TrimMass50_branch != 0) HLT_AK8PFHT850_TrimMass50_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFHT850_TrimMass50_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFHT850_TrimMass50_isLoaded = true;
 }
 return HLT_AK8PFHT850_TrimMass50_;
}

const bool &hhtree::HLT_AK8PFHT900_TrimMass50() 
{
 if(not HLT_AK8PFHT900_TrimMass50_isLoaded)
 {
   if(HLT_AK8PFHT900_TrimMass50_branch != 0) HLT_AK8PFHT900_TrimMass50_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFHT900_TrimMass50_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFHT900_TrimMass50_isLoaded = true;
 }
 return HLT_AK8PFHT900_TrimMass50_;
}

const bool &hhtree::HLT_PFJet450() 
{
 if(not HLT_PFJet450_isLoaded)
 {
   if(HLT_PFJet450_branch != 0) HLT_PFJet450_branch->GetEntry(index);
   else
   {
     printf("branch HLT_PFJet450_branch does not exist!\n");
exit(1);
   }
   HLT_PFJet450_isLoaded = true;
 }
 return HLT_PFJet450_;
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

const bool &hhtree::HLT_PFJet550() 
{
 if(not HLT_PFJet550_isLoaded)
 {
   if(HLT_PFJet550_branch != 0) HLT_PFJet550_branch->GetEntry(index);
   else
   {
     printf("branch HLT_PFJet550_branch does not exist!\n");
exit(1);
   }
   HLT_PFJet550_isLoaded = true;
 }
 return HLT_PFJet550_;
}

const bool &hhtree::HLT_AK8PFJet450() 
{
 if(not HLT_AK8PFJet450_isLoaded)
 {
   if(HLT_AK8PFJet450_branch != 0) HLT_AK8PFJet450_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet450_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet450_isLoaded = true;
 }
 return HLT_AK8PFJet450_;
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

const bool &hhtree::HLT_AK8PFJet550() 
{
 if(not HLT_AK8PFJet550_isLoaded)
 {
   if(HLT_AK8PFJet550_branch != 0) HLT_AK8PFJet550_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet550_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet550_isLoaded = true;
 }
 return HLT_AK8PFJet550_;
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

const bool &hhtree::HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02() 
{
 if(not HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_isLoaded)
 {
   if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch != 0) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_isLoaded = true;
 }
 return HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_p02_;
}

const bool &hhtree::HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2() 
{
 if(not HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_isLoaded)
 {
   if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch != 0) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_isLoaded = true;
 }
 return HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np2_;
}

const bool &hhtree::HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4() 
{
 if(not HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_isLoaded)
 {
   if(HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch != 0) HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_isLoaded = true;
 }
 return HLT_AK8PFJet330_TrimMass30_PFAK8BoostedDoubleB_np4_;
}

const bool &hhtree::HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20() 
{
 if(not HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_isLoaded)
 {
   if(HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch != 0) HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_branch does not exist!\n");
exit(1);
   }
   HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_isLoaded = true;
 }
 return HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p20_;
}

const bool &hhtree::HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087() 
{
 if(not HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_isLoaded)
 {
   if(HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch != 0) HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_branch does not exist!\n");
exit(1);
   }
   HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_isLoaded = true;
 }
 return HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p087_;
}

const bool &hhtree::HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087() 
{
 if(not HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_isLoaded)
 {
   if(HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch != 0) HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_branch does not exist!\n");
exit(1);
   }
   HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_isLoaded = true;
 }
 return HLT_AK8DiPFJet300_200_TrimMass30_BTagCSV_p087_;
}

const bool &hhtree::HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20() 
{
 if(not HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_isLoaded)
 {
   if(HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch != 0) HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_branch does not exist!\n");
exit(1);
   }
   HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_isLoaded = true;
 }
 return HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV_p20_;
}

const bool &hhtree::HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20() 
{
 if(not HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_isLoaded)
 {
   if(HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch != 0) HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_branch does not exist!\n");
exit(1);
   }
   HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_isLoaded = true;
 }
 return HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV_p20_;
}

const bool &hhtree::HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20() 
{
 if(not HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_isLoaded)
 {
   if(HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch != 0) HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch->GetEntry(index);
   else
   {
     printf("branch HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_branch does not exist!\n");
exit(1);
   }
   HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_isLoaded = true;
 }
 return HLT_AK8DiPFJet250_200_TrimMass30_BTagCSV_p20_;
}

const float &hhtree::disc_qcd_and_ttbar_Run2_enhanced_v23() 
{
 if(not disc_qcd_and_ttbar_Run2_enhanced_v23_isLoaded)
 {
   if(disc_qcd_and_ttbar_Run2_enhanced_v23_branch != 0) disc_qcd_and_ttbar_Run2_enhanced_v23_branch->GetEntry(index);
   else
   {
     printf("branch disc_qcd_and_ttbar_Run2_enhanced_v23_branch does not exist!\n");
exit(1);
   }
   disc_qcd_and_ttbar_Run2_enhanced_v23_isLoaded = true;
 }
 return disc_qcd_and_ttbar_Run2_enhanced_v23_;
}

const float &hhtree::disc_qcd_and_ttbar_Run2_enhanced_v24() 
{
 if(not disc_qcd_and_ttbar_Run2_enhanced_v24_isLoaded)
 {
   if(disc_qcd_and_ttbar_Run2_enhanced_v24_branch != 0) disc_qcd_and_ttbar_Run2_enhanced_v24_branch->GetEntry(index);
   else
   {
     printf("branch disc_qcd_and_ttbar_Run2_enhanced_v24_branch does not exist!\n");
exit(1);
   }
   disc_qcd_and_ttbar_Run2_enhanced_v24_isLoaded = true;
 }
 return disc_qcd_and_ttbar_Run2_enhanced_v24_;
}

