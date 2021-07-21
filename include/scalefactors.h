#ifndef scalefactors_h
#define scalefactors_h

class PNetHbbScaleFactors
{
    public: 
        TFile *file_sf;       
        TH2D *PNetXBBSF;
        
        PNetHbbScaleFactors(string year)
        {
            file_sf = new  TFile("data/scale_factor/PNetXBB_SF_v2.root");
            PNetXBBSF =   (TH2D*)file_sf->Get(("PNetXBBSF_"+year).data());  
            PNetXBBSF->SetDirectory(0);           
            file_sf->Close();               
        }
        ~PNetHbbScaleFactors()
        {
            delete PNetXBBSF;
        }
        //get the trigger eff per AK8 jet
        float getPNetHbbScaleFactors(float pt, float PNetXbb, int ibinx, int ibiny, int variation) 
        {
            if( pt > PNetXBBSF->GetXaxis()->GetXmax() * 0.999 ) {
                    pt = PNetXBBSF->GetXaxis()->GetXmax() * 0.999;
            }
           
            float result = 1.0;

            int bin_index_x = PNetXBBSF->GetXaxis()->FindFixBin(pt);
            int bin_index_y = PNetXBBSF->GetYaxis()->FindFixBin(PNetXbb);
            
            int nbin_x = PNetXBBSF->GetNbinsX();
            int nbin_y = PNetXBBSF->GetNbinsY();
            
            if ( (bin_index_x>0) && (bin_index_y>0) && (bin_index_x<=nbin_x) && (bin_index_y<=nbin_y) ){
                if( (variation==1) && (ibinx == bin_index_x) && (ibiny == bin_index_y) ){
                    result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y) + PNetXBBSF->GetBinError(bin_index_x, bin_index_y);
                }
                else if( (variation==-1) && (ibinx == bin_index_x) && (ibiny == bin_index_y) ){
                    result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y) - PNetXBBSF->GetBinError(bin_index_x, bin_index_y);
                }
                else result = PNetXBBSF->GetBinContent(bin_index_x, bin_index_y);
            }   
 
            return result;
        }
};

class TrigEffScaleFactors
{
    public: 
        TFile *file_sf;
        
        TH2F *hist_sf_Xbb0p0To0p9;
        TH2F *hist_sf_Xbb0p9To0p95;
        TH2F *hist_sf_Xbb0p95To0p98;
        TH2F *hist_sf_Xbb0p98To1p0;
        
        int Nbin_Xbb0p0To0p9 = 0;
        int Nbin_Xbb0p9To0p95 = 0;
        int Nbin_Xbb0p95To0p98 = 0;
        int Nbin_Xbb0p98To1p0 = 0;
        
        int nbin_x_Xbb0p0To0p9 = 0;
        int nbin_y_Xbb0p0To0p9 = 0;
        
        int nbin_x_Xbb0p9To0p95 = 0;
        int nbin_y_Xbb0p9To0p95 = 0;
        
        int nbin_x_Xbb0p95To0p98 = 0;
        int nbin_y_Xbb0p95To0p98 = 0;
        
        int nbin_x_Xbb0p98To1p0 = 0;
        int nbin_y_Xbb0p98To1p0 = 0;

        
        TrigEffScaleFactors(string year)
        {
            if(year == "2016") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2016.root");
            else if(year == "2017") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2017.root");
            else if(year == "2018") file_sf = new TFile("data/scale_factor/trigger/JetHTTriggerEfficiency_2018.root");

            hist_sf_Xbb0p0To0p9 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p0To0p9");
            hist_sf_Xbb0p9To0p95 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p9To0p95");
            hist_sf_Xbb0p95To0p98 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p95To0p98");
            hist_sf_Xbb0p98To1p0 = (TH2F*)file_sf->Get("efficiency_ptmass_Xbb0p98To1p0");   
            
            hist_sf_Xbb0p0To0p9->SetDirectory(0);
            hist_sf_Xbb0p9To0p95->SetDirectory(0);
            hist_sf_Xbb0p95To0p98->SetDirectory(0);
            hist_sf_Xbb0p98To1p0->SetDirectory(0);
            
            file_sf->Close();
            
            Nbin_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetYaxis()->GetNbins()*hist_sf_Xbb0p0To0p9->GetXaxis()->GetNbins();
            Nbin_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetYaxis()->GetNbins()*hist_sf_Xbb0p9To0p95->GetXaxis()->GetNbins();
            Nbin_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetYaxis()->GetNbins()*hist_sf_Xbb0p95To0p98->GetXaxis()->GetNbins();
            Nbin_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetYaxis()->GetNbins()*hist_sf_Xbb0p98To1p0->GetXaxis()->GetNbins();  
            
            nbin_x_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetXaxis()->GetNbins();
            nbin_y_Xbb0p0To0p9 = hist_sf_Xbb0p0To0p9->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetXaxis()->GetNbins();
            nbin_y_Xbb0p9To0p95 = hist_sf_Xbb0p9To0p95->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetXaxis()->GetNbins();
            nbin_y_Xbb0p95To0p98 = hist_sf_Xbb0p95To0p98->GetYaxis()->GetNbins();
        
            nbin_x_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetXaxis()->GetNbins();
            nbin_y_Xbb0p98To1p0 = hist_sf_Xbb0p98To1p0->GetYaxis()->GetNbins();
                
        }
        ~TrigEffScaleFactors()
        {
            delete hist_sf_Xbb0p0To0p9;
            delete hist_sf_Xbb0p9To0p95;
            delete hist_sf_Xbb0p95To0p98;
            delete hist_sf_Xbb0p98To1p0;
        }
        //get the trigger eff per AK8 jet
        float getTriggerEff3D(float pt, float mass, float PNetXbb, int variation, int ibin) 
        {
            //cout <<"ibin in getTriggerEff3D: "<<ibin<<endl;
            float result = 0.0;
            float tmpMass = 0;
            float tmpPt = 0;
            TH2F* trigEffHist = 0;
            
            int ibin_start = 0; //0
            int nbin_x = 0;
            
            if (PNetXbb < 0.9){
                trigEffHist = hist_sf_Xbb0p0To0p9;
                nbin_x = nbin_x_Xbb0p0To0p9;
            }
            else if (PNetXbb < 0.95){ 
                trigEffHist = hist_sf_Xbb0p9To0p95; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9;
                nbin_x = nbin_x_Xbb0p9To0p95;
            }
            else if (PNetXbb < 0.98){ 
                trigEffHist = hist_sf_Xbb0p95To0p98; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95; 
                nbin_x = nbin_x_Xbb0p95To0p98;
            }  
            else{ 
                trigEffHist = hist_sf_Xbb0p98To1p0; 
                ibin_start = ibin_start + Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95 + Nbin_Xbb0p95To0p98; 
                nbin_x = nbin_x_Xbb0p98To1p0;
            }    
            
            if (trigEffHist) {
                // constrain to histogram bounds for mass and pT of Jet
                if( mass > trigEffHist->GetXaxis()->GetXmax() * 0.999 ) {
                    tmpMass = trigEffHist->GetXaxis()->GetXmax() * 0.999;
                } 
                else if ( mass < 0 ) {
                    tmpMass = 0.001;
                } 
                else {
                    tmpMass = mass;
                }
    
                if( pt > trigEffHist->GetYaxis()->GetXmax() * 0.999 ) {
                    tmpPt = trigEffHist->GetYaxis()->GetXmax() * 0.999;
                } 
                else if (pt < 0) {
                    tmpPt = 0.001;
                    //cout << "Warning: pt=" << pt << " is negative and unphysical\n";
                } 
                else {
                   tmpPt = pt;
                }
                int bin_index_x = trigEffHist->GetXaxis()->FindFixBin(tmpMass);
                int bin_index_y = trigEffHist->GetYaxis()->FindFixBin(tmpPt);
                //cout <<"variation PNetXbb tmpMasss tmpPt "<<variation<<" "<< PNetXbb<<" "<<tmpMass<<" "<<tmpPt<<endl;
                //cout <<"bin_index_x, bin_index_y"<<bin_index_x<<" "<<bin_index_y<<endl;
                //cout <<"ibin ibin_start + (bin_index_y-1)*nbin_x + bin_index_x "<<ibin<<" "<< ibin_start + (bin_index_y-1)*nbin_x + bin_index_x <<endl;

                if( variation==0 ) result = trigEffHist->GetBinContent(bin_index_x, bin_index_y); 
                else if( ibin == (ibin_start + (bin_index_y-1)*nbin_x + bin_index_x) ){
                    if( variation==1 ){
                        result = trigEffHist->GetBinContent(bin_index_x, bin_index_y) + trigEffHist->GetBinError(bin_index_x, bin_index_y);
                        //cout <<"trig unc up "<<endl;
                    }
                    else if( variation==-1 ){
                        result = trigEffHist->GetBinContent(bin_index_x, bin_index_y) - trigEffHist->GetBinError(bin_index_x, bin_index_y);
                        //cout <<"trig unc down"<<endl;
                    }
                }
                else result = trigEffHist->GetBinContent(bin_index_x, bin_index_y);  
            } 
            else {
                //std::cout << "Error: expected a histogram, got a null pointer" << std::endl;
                return 0;
            }
            //cout <<"eff per jet"<<endl;
            return result;
        }
        //get the trigger eff per event
        float getTrigEffEvt(float pt1, float mass1, float PNetXbb1, float pt2, float mass2, float PNetXbb2, int variation, int ibin){
            //cout <<"ibin in getTrigEffEvt: "<<ibin<<endl;
            float eff = 1.0 - (1.0 - getTriggerEff3D(pt1, mass1, PNetXbb1, variation, ibin))*(1.0 - getTriggerEff3D(pt2, mass2, PNetXbb2, variation, ibin));
            return eff;
        }
        //get the number of systematic uncertainties sources (number of bins in trigger map)
        int getNbins(){
            int Nbins = Nbin_Xbb0p0To0p9 + Nbin_Xbb0p9To0p95 + Nbin_Xbb0p95To0p98 + Nbin_Xbb0p98To1p0;
            return Nbins;
        }
        //get the SF ratio of variation/nominal 
        float get_unc_ratio(float pt1, float mass1, float PNetXbb1, float pt2, float mass2, float PNetXbb2, int variation, int itrig_unc){           
            float tmp = 0;
            //cout <<"ibin in get_unc_ratio: "<<itrig_unc<<endl;           
            float nominal = getTrigEffEvt(pt1, mass1, PNetXbb1, pt2, mass2, PNetXbb2, 0, 0);     
            if( nominal!=0 ){
                tmp = getTrigEffEvt(pt1, mass1, PNetXbb1, pt2, mass2, PNetXbb2, variation, itrig_unc)/nominal;   
                //if (tmp!=1) cout <<" ratio for itrig_unc: "<< itrig_unc<<" "<<tmp<< endl;
            } 
            return tmp;
        }
};

class TTJetsScaleFactors
{
    public: 
        TFile *file_sf_2016;
        TFile *file_sf_2017;
        TFile *file_sf_2018;
        TH1F *hist_sf_2016;
        TH1F *hist_sf_2017;
        TH1F *hist_sf_2018;
        TTJetsScaleFactors()
        {
            file_sf_2016 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2016.root");
            file_sf_2017 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2017.root");
            file_sf_2018 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2018.root");

            hist_sf_2016 =   (TH1F*)file_sf_2016->Get("ratio_data_over_mc");
            hist_sf_2017 =   (TH1F*)file_sf_2017->Get("ratio_data_over_mc");
            hist_sf_2018 =   (TH1F*)file_sf_2018->Get("ratio_data_over_mc");
            
            hist_sf_2016->SetDirectory(0);
            hist_sf_2017->SetDirectory(0);
            hist_sf_2018->SetDirectory(0);
            
            file_sf_2016->Close();
            file_sf_2017->Close();
            file_sf_2018->Close();
        }
        ~TTJetsScaleFactors()
        {
            //file_sf_2016->Close();
            //file_sf_2017->Close();
            //file_sf_2018->Close();

            delete hist_sf_2016;
            delete hist_sf_2017;
            delete hist_sf_2018;
        }
        float getScaleFactors(string year, float pt)
        {
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            if(year ==  "2016")
            {
                result  = hist_sf_2016->GetBinContent(hist_sf_2016->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2017")
            {
                result  = hist_sf_2017->GetBinContent(hist_sf_2017->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2018")
            {
                result  = hist_sf_2018->GetBinContent(hist_sf_2018->GetXaxis()->FindFixBin(pt));
            }
            if(result <0.01) result = 1.0;
            if(result >3.0) result = 1.0;
            return result;
        }
        float getScaleFactorsFit(string year, float pt, int type=0)
        {
            //type: 0, 1, -1 for norminal Up, Down
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            if(year == "2016")
            {
                //float slope = 3.39715e-04, slope_err = 2.72340e-04, constant = 1.06357e+00, constant_err = 5.52116e-02;
                //float slope = 1.86172e-04, slope_err = 2.75413e-04, constant = 1.07197e+00, constant_err = 5.54311e-02;
                float slope = 0.000291232, slope_err = 0.000328419, constant = 1.10197, constant_err = 0.065916;
                if(pt<300) result = (slope + type*slope_err)*(pt-300.) + constant + type*constant_err;
                else result = constant + type*constant_err;
            }
            if(year == "2017")
            {
                //float slope = 1.52909e-03, slope_err = 2.36132e-04, constant = 1.20558e+00, constant_err = 5.00417e-02;
                //float slope = 1.60289e-03, slope_err = 2.51147e-04, constant = 1.28418e+00, constant_err = 5.31669e-02;
                float slope = 0.00177981, slope_err = 0.000283582, constant = 1.31793, constant_err = 0.0582431;
                if(pt<300) result = (slope + type*slope_err)*(pt-300.) + constant + type*constant_err;
                else result = constant + type*constant_err;
            }
            if(year == "2018")
            {
                //float slope = 1.33382e-03, slope_err = 1.92282e-04, constant = 1.10805e+00, constant_err = 4.01827e-02;
                //float slope = 1.36880e-03, slope_err = 1.91672e-04, constant = 1.11018e+00, constant_err = 4.01700e-02;
                float slope = 0.00148792, slope_err = 0.000222207, constant = 1.12203, constant_err = 0.045051;
                if(pt<300) result = (slope + type*slope_err)*(pt-300.) + constant + type*constant_err;
                else result = constant + type*constant_err;
            }
            //if(result <0.01) result = 1.0;
            //if(result >3.0) result = 1.0;
            return result;
        }
        float getPNetXbbShapeScaleFactors(string year, float xbb, int type=0)
        {
            //type: 0, 1, -1 for nominal Up Down
            int idx_xbb  = 0;
            if(xbb < 0.945) idx_xbb  = 0;
            else if (xbb  < 0.955) idx_xbb =1;
            else if (xbb  < 0.975) idx_xbb =2;
            else if (xbb < 0.985) idx_xbb =3;
            else idx_xbb = 4;
            if (year == "2016")
            {
               float sf[5] = {0.821, 0.789, 0.824, 0.701, 0.741};
               float esf[5] = {0.012, 0.066, 0.044, 0.084, 0.069};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2017")
            {
               float sf[5] = {0.901, 0.880, 0.876, 0.860, 0.916};
               float esf[5] = {0.014, 0.067, 0.045, 0.064, 0.071};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2018")
            {
               float sf[5] = {0.975, 1.024, 0.935, 0.890, 0.798};
               float esf[5] = {0.016, 0.059, 0.039, 0.055, 0.056};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            return 1.0;
        }

};

double TopTagSF( string workingPoint, string year, double pt ) {
  double result = 1.0;
  if (workingPoint == "0.40") {
    if (year == "2016") {
      if (pt > 600) {
	result = 0.930;
      } else if (pt > 480) {
	result = 1.013;
      } else if (pt > 400) {
	result = 1.041;
      } else if (pt > 300) {
	result = 0.926;
      } else {
	result = 0.926; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else if (year == "2017") {
      if (pt > 600) {
	result = 0.760;
      } else if (pt > 480) {
	result = 0.851;
      } else if (pt > 400) {
	result = 0.856;
      } else if (pt > 300) {
	result = 0.879;
      } else {
	result = 0.879; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else if (year == "2018") {
      if (pt > 600) {
	result = 0.787;
      } else if (pt > 480) {
	result = 0.911;
      } else if (pt > 400) {
	result = 0.923;
      } else if (pt > 300) {
	result = 0.888;
      } else {
	result = 0.888; //this isn't measured, so we take the value of the last bin measured.
      }
    }
    else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }
  else if (workingPoint == "0.46") {
    if (year == "2016") {
      if (pt > 600) {
    result = 1.00;
      } else if (pt > 480) {
    result = 0.988;
      } else if (pt > 400) {
    result = 0.976;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
    else if (year == "2017") {
      if (pt > 600) {
    result = 0.87;
      } else if (pt > 480) {
    result = 0.89;
      } else if (pt > 400) {
    result = 0.95;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
    else if (year == "2018") {
      if (pt > 600) {
    result = 0.847;
      } else if (pt > 480) {
    result = 0.93;
      } else if (pt > 400) {
    result = 0.976;
      } else if (pt > 300) {
    result = 0.93;
      } else {
    result = 0.93; //this isn't measured, so we take the value of the last bin measured. 
      }
    }
   else {
      cout << "[TopTagSF] Warning: year=" << year << " is not supported\n";
    }
  }  else {
    cout << "[TopTagSF] Warning: workingPoint=" << workingPoint << " is not supported\n";
  }
  return result;
};

//#ifndef __CINT__
//// Scale factors tools
//extern TTJetsScaleFactors toptag_sf; 
//#endif

#endif
