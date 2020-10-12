#ifndef scalefactors_h
#define scalefactors_h

class TopTagScaleFactors
{
    public: 
        TFile *file_sf_2016_bin1;//pt<300
        TFile *file_sf_2016_bin2;//pt>300
        TFile *file_sf_2017_bin1;
        TFile *file_sf_2017_bin2;
        TFile *file_sf_2018_bin1;
        TFile *file_sf_2018_bin2;
        TH1F *hist_sf_2016_bin1;//pt<300
        TH1F *hist_sf_2016_bin2;//pt>300
        TH1F *hist_sf_2017_bin1;
        TH1F *hist_sf_2017_bin2;
        TH1F *hist_sf_2018_bin1;
        TH1F *hist_sf_2018_bin2;
        TopTagScaleFactors()
        {
            file_sf_2016_bin1 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2016_bin1.root");
            file_sf_2016_bin2 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2016_bin2.root");
            file_sf_2017_bin1 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2017_bin1.root");
            file_sf_2017_bin2 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2017_bin2.root");
            file_sf_2018_bin1 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2018_bin1.root");
            file_sf_2018_bin2 = new  TFile("data/scale_factor/TTBarCR_hh_pt_2018_bin2.root");

            hist_sf_2016_bin1 =   (TH1F*)file_sf_2016_bin1->Get("ratio");
            hist_sf_2016_bin2 =   (TH1F*)file_sf_2016_bin1->Get("ratio");
            hist_sf_2017_bin1 =   (TH1F*)file_sf_2017_bin1->Get("ratio");
            hist_sf_2017_bin2 =   (TH1F*)file_sf_2017_bin1->Get("ratio");
            hist_sf_2018_bin1 =   (TH1F*)file_sf_2018_bin1->Get("ratio");
            hist_sf_2018_bin2 =   (TH1F*)file_sf_2018_bin1->Get("ratio");
        }
        ~TopTagScaleFactors()
        {
            file_sf_2016_bin1->Close();
            file_sf_2016_bin2->Close();
            file_sf_2017_bin1->Close();
            file_sf_2017_bin2->Close();
            file_sf_2018_bin1->Close();
            file_sf_2018_bin2->Close();

            delete hist_sf_2016_bin1;
            delete hist_sf_2016_bin2;
            delete hist_sf_2017_bin1;
            delete hist_sf_2017_bin2;
            delete hist_sf_2018_bin1;
            delete hist_sf_2018_bin2;
        }
        float getScaleFactors(string year, float pt)
        {
            float result = 1.0;
            if (pt<0.1)  pt= 0.1;
            if(pt>999.9) pt =999.9;
            if(year ==  "2016")
            {
                if(pt > 300.0 ) result = hist_sf_2016_bin2->GetBinContent(hist_sf_2016_bin2->GetXaxis()->FindFixBin(pt));
                if(pt <= 300.0 ) result  = hist_sf_2016_bin1->GetBinContent(hist_sf_2016_bin1->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2017")
            {
                if(pt > 300.0 ) result = hist_sf_2017_bin2->GetBinContent(hist_sf_2017_bin2->GetXaxis()->FindFixBin(pt));
                if(pt <= 300.0 ) result  = hist_sf_2017_bin1->GetBinContent(hist_sf_2017_bin1->GetXaxis()->FindFixBin(pt));
            }
            if(year ==  "2018")
            {
                if(pt > 300.0 ) result = hist_sf_2018_bin2->GetBinContent(hist_sf_2018_bin2->GetXaxis()->FindFixBin(pt));
                if(pt <= 300.0 ) result  = hist_sf_2018_bin1->GetBinContent(hist_sf_2018_bin1->GetXaxis()->FindFixBin(pt));
            }
            if(result <0.01) result = 1.0;
            if(result >3.0) result = 1.0;
            return result;
        }

};

double TopTagSF( string workingPoint, string year, double pt ) {
  double result = 1.0;
  if (workingPoint == "0.46") {
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
//extern TopTagScaleFactors toptag_sf; 
//#endif

#endif
