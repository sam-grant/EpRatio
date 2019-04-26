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
  
  string line_g;
  string line_m;
  ifstream gainFile("gain_means_norm_by_xtal22.csv");
  ifstream mipFile("mip_peaks_norm_by_xtal22.csv");

  if (!gainFile.is_open() || !mipFile.is_open()){// || !MIP.is_open()){
    cout << "Error, files not opened" << endl;
    gainFile.close();
    mipFile.close();
    return 0;
  }
  else {
    cout << "Both files open... starting\n" << endl;
  }

 vector<string> gain;
 vector<string> mip;
 char delim = ','; // Ddefine the delimiter to split by
 string tmp;
 if(gainFile.is_open()) {
   while (getline(gainFile, tmp, delim)) {
     gain.push_back(tmp);
   }
 }
  if(mipFile.is_open()) {
   while (getline(mipFile, tmp, delim)) {
     mip.push_back(tmp);
   }
 }

 
 // The strange way the csv file gets read means these loops are the only workaround
 double gain_value;
 double gain_error;
 double mip_value;
 double mip_error;
 TH1D *gain_h = new TH1D("E/p Means","E/p Means",54,-0.5,53.5);
 TH1D *mip_h = new TH1D("MIP Peaks","MIP Peaks",54,-0.5,53.5);
 //
 // gPad->Update();
  int j;
  //  for (int i = 1 ; i < 55 ; i++){
   for (int i = 55 ; i < 109 ; i++){

  //cout<<i+1<<" "<<gain[i+1]<<endl;
   // convert strings into doubles with atof
   j = i*2-1;
   gain_value = atof(gain[j].c_str());
   gain_error = atof(gain[j+1].c_str());
   mip_value = atof(mip[j].c_str());
   mip_error = atof(mip[j+1].c_str());
   //   cout<<gain_value<<endl;
   // cout<<i<<endl;
    gain_h->SetBinContent(i-54,gain_value);
    gain_h->SetBinError(i-54,gain_error);
    mip_h->SetBinContent(i-54,mip_value);
    mip_h->SetBinError(i-54,mip_error);
   /*gain_h->SetBinContent(i,gain_value);
    gain_h->SetBinError(i,gain_error);
    mip_h->SetBinContent(i,mip_value);
    mip_h->SetBinError(i,mip_error);*/
 }

   
  TCanvas *c1 = new TCanvas("c1", "c1", 2000, 1000);
  //Force the ranges to be sensible if ROOT's autoscale fails
  // int binmin = gain_h->FindFirstBinAbove(0,1);
  // int binmax = gain_h->FindLastBinAbove(0,1);
  // string fname = "test";


  // gStyle->SetOptStat(110010);
  gain_h->SetName("E/p Means");
  mip_h->SetName("MIP Peaks");
  mip_h->SetMarkerColor(kRed);
  mip_h->SetLineColor(kRed);
  gain_h->SetMarkerColor(kBlue);
  gain_h->SetLineColor(kBlue);
  mip_h->GetYaxis()->SetRangeUser(0.7,1.2);//xmin,xmax);
  // mip_h->GetXaxis()->SetNdivisions(-18);
  gPad->SetGrid();
  mip_h->SetStats(0);  
  mip_h->Draw();
  gain_h->Draw("same");
  c1->BuildLegend(0.69,0.79,0.89,0.89);
   mip_h->SetTitle("St 19 | MIP Peaks & Mean E/p per Crystal;Crystal Number;Normlised Units");
  c1->SaveAs("st19_mip_&_Ep_per_xtal.png");
   delete c1;
  delete gain_h;
  delete mip_h;

  gainFile.close();
  mipFile.close();
  return 0;
}
