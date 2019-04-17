// Code to compare the mean gain with the MIP peaks
// Sam Grant 
// April 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TProfile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TObject.h"
#include "TGraph.h"
#include "TLegend.h"
#include "TPaveStats.h"


using namespace std;

int main() {
  
  string line;
  ifstream gainFile("gain_means_norm_by_xtal22.csv");
  // ifstream MIP;
  
  //  means.open("gain_means_norm_by_xtal22.csv");
  //  MIP.open("mip_peaks_norm_by_xtal22.csv");
  
  if (!gainFile.is_open()){// || !MIP.is_open()){
    cout << "Error, files not opened" << endl;
    gainFile.close();
    // MIP.close();
    return 0;
  }
  else {
    cout << "Both files open... starting\n" << endl;
  }

 vector<string> gain;
 char delim = ','; // Ddefine the delimiter to split by
 string tmp;
 if(gain.is_open()) {
   while (getline(gain, tmp, delim)) {
      // Provide proper checks here for tmp like if empty
      // Also strip down symbols like !, ., ?, etc.
      // Finally push it.]]=
     // cout << tmp << endl;
     gain.push_back(tmp);
   }
 }

 TH1D *gain_h = new TH1D("gain_h","gain_h",54,-0.5,53.5);
 gain_h->

 

 
  gainFile.close();
  //  MIP.close();
  return 0;
}
