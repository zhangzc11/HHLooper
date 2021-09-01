#ifndef scalefactors_h
#define scalefactors_h

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
        }
        ~TTJetsScaleFactors()
        {
            file_sf_2016->Close();
            file_sf_2017->Close();
            file_sf_2018->Close();

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
            if(year ==  "2016")
            {
                float p0 = 0.9183, p1=0.0008758, y1=1.179;
                if (type==1 || type==-1) p1 += 0.0004871*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(year ==  "2017")
            {
                float p0 = 0.7434, p1=0.003026, y1=1.475;
                if (type==1 || type==-1) p1 += 0.000367*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(year ==  "2018")
            {
                float p0 = 0.7114, p1=0.001274, y1=1.063;
                if (type==1 || type==-1) p1 += 0.000234*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(result <0.01) result = 1.0;
            if(result >3.0) result = 1.0;
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
               float sf[5] = {0.825, 0.787, 0.818, 0.673, 0.698};
               float esf[5] = {0.011, 0.059, 0.041, 0.069, 0.062};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2017")
            {
               float sf[5] = {0.932, 0.898, 0.901, 0.876, 0.926};
               float esf[5] = {0.013, 0.066, 0.045, 0.065, 0.071};
               return sf[idx_xbb] + type*esf[idx_xbb];
            }
            if (year == "2018")
            {
               float sf[5] = {0.981, 1.013, 0.922, 0.871, 0.781};
               float esf[5] = {0.011, 0.058, 0.038, 0.053, 0.054};
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
