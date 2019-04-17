// Code to compare the mean gain with the MIP peaks
// Sam Grant 
// April 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <stdio.h>     
#include <stdlib.h> 
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
//#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
//#include "TProfile.h"
//#include "TF1.h"
#include "TDirectory.h"
//#include "TObject.h"
//#include "TGraph.h"
#include "TLegend.h"
//#include "TPaveStats.h"


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
 if(gainFile.is_open()) {
   while (getline(gainFile, tmp, delim)) {
      // Provide proper checks here for tmp like if empty
      // Also strip down symbols like !, ., ?, etc.
      // Finally push it.]]=
     // cout << tmp << endl;
     gain.push_back(tmp);
   }
 }

 
 // The strange way the csv file gets read means these loops are the only workaround
 double value;
 double error;
  TH1D *gain_h = new TH1D("gain_h","gain_h",54,-0.5,53.5);
  int j;
 for (int i = 1 ; i < 55 ; i++){
   //cout<<i+1<<" "<<gain[i+1]<<endl;
   // convert strings into doubles with atof
   j = i*2-1;
   value = atof(gain[j].c_str());
   error = atof(gain[j+1].c_str());
   // cout<<i<<endl;
     cout<<value<<endl;
    gain_h->SetBinContent(i,value);
   gain_h->SetBinError(i,error);
 }

  TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
  //Force the ranges to be sensible if ROOT's autoscale fails
  // int binmin = gain_h->FindFirstBinAbove(0,1);
  // int binmax = gain_h->FindLastBinAbove(0,1);
  string fname = "test";
  string title = "title";
  gain_h->SetName(fname.c_str());
  // gStyle->SetOptStat(110010);
  gain_h->SetTitle(title.c_str());
  gain_h->SetMarkerColor(kBlack);
  gain_h->SetLineColor(kBlack);
  gain_h->GetYaxis()->SetRangeUser(0.9,1.1);//xmin,xmax);
  gPad->SetGrid();
  gain_h->DrawCopy();
  // if (save) {
    c1->SaveAs((fname+".png").c_str());
    // } 
    // gain_h->SetDirectory(output);
  delete c1;
 /*
 cout << gain[9] << endl;
 cout << gain[11] << endl;
 cout << gain[13] << endl;
 cout << gain[15] << endl;
 cout << gain[17] << endl;
 */

  // int it;
 /*for (int i = 0 ; i < 54 ; i++) {
   
   if (i == 0 ) {
     it = 1;
   }
   else {
     it = 3;
   }
   cout << (i+1)*it << endl;
   cout<<gain[(i+1)*it]<<endl;
   // cout<<gain[(i+2)*it]<<endl;

   //
   // 
			 
   }*/
 //TH1D *gain_h = new TH1D("gain_h","gain_h",54,-0.5,53.5);
 // gain_h->

 

 
  gainFile.close();
  //  MIP.close();
  return 0;
}
