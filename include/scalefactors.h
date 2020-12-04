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
                float p0 = 0.6528, p1=0.0006043, y1=0.783;
                if (type==1 || type==-1) p1 += 0.0002218*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(year ==  "2017")
            {
                float p0 = 0.6648, p1=0.002605, y1=1.299;
                if (type==1 || type==-1) p1 += 0.000297*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(year ==  "2018")
            {
                float p0 = 0.6778, p1=0.001174, y1=1.029;
                if (type==1 || type==-1) p1 += 0.000207*type;
                float x1=(y1-p0)/p1;
                if(pt>x1) result = y1;
                else  result = p0+p1*pt;
            }
            if(result <0.01) result = 1.0;
            if(result >3.0) result = 1.0;
            return result;
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
