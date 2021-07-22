#ifndef scalefactors_h
#define scalefactors_h

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
