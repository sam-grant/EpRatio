// Convert csv to ROOT
// Sam Grant 
// April 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> 
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TDirectory.h"
#include "TLegend.h"
#include "TAttMarker.h"

using namespace std;

int main() {
 
  string output_fname = "inFillGainParams_laser_xtal_errors_Q.root";
  TFile *output = new TFile(output_fname.c_str(), "recreate");
  
  // string line_t;
  // string line_a;
  ifstream laserFileTau("laser_tau_with_errors.csv");
  ifstream laserFileA("laser_A_with_errors.csv");

  
  if (!laserFileTau.is_open() || !laserFileA.is_open()){
    cout << "Error, files not opened" << endl;
    laserFileTau.close();
    laserFileA.close();
    return 0;
  }
  else {
    cout << "File open... starting\n" << endl;
  }

  vector<string> laserTau;
  char delim = ','; // Ddefine the delimiter to split by
  string tmp;
  if(laserFileTau.is_open()) {
    while (getline(laserFileTau, tmp, delim)) {
      laserTau.push_back(tmp);
      //  cout << tmp << endl;
    }
  }
  vector<string> laserA;
  // char delim = ','; // Ddefine the delimiter to split by
  //string tmp;
  if(laserFileA.is_open()) {
    while (getline(laserFileA, tmp, delim)) {
      laserA.push_back(tmp);
    }
  }

  //  cout << laserTau << endl;
 
  TH1D *tau13 = new TH1D("tau_13","Calo 13",54,-0.5,53.5);//,64,0,16);//-0.2,16.2);
  TH1D *tau19 = new TH1D("tau_19","Calo 19",54,-0.5,53.5);//,64,0,16);//-0.2,16.2);
  TH1D *amp13 = new TH1D("amp_13","Calo 13",54,-0.5,53.5);//,50,0,0.05);//0-0.002,0.052);
  TH1D *amp19 = new TH1D("amp_19","Calo 19",54,-0.5,53.5);//,50,0,0.05);//-0.002,0.052);



  int j;
  for (int i = 1 ; i < 55 ; i++){
    // convert strings into doubles with atof
    j = i*2-1;
    double amp = atof(laserA[j].c_str());
    double tau = atof(laserTau[j].c_str());
    double damp = atof(laserA[j+1].c_str());
    double dtau = atof(laserTau[j+1].c_str());
    cout<<i-55<<" "<<amp<<" "<<damp<<" "<<tau<<" "<<dtau<<endl;
    tau = tau * 1.25;
    //    if(amp <= 0 || tau <=0) continue;
    //    if(amp > 0.1 || tau > 16) continue;

    amp13->SetBinContent(i,amp);
    amp13->SetBinError(i,damp);
    tau13->SetBinContent(i,tau);
    tau13->SetBinError(i,dtau);
  }

  for (int i = 55 ; i < 109 ; i++){
    j = i*2-1;
    double amp = atof(laserA[j].c_str());
    double tau = atof(laserTau[j].c_str());
    double damp = atof(laserA[j+1].c_str());
    double dtau = atof(laserTau[j+1].c_str());
    cout<<i-55<<" "<<amp<<" "<<damp<<" "<<tau<<" "<<dtau<<endl;
    tau = tau * 1.25;
    //   if(amp <= 0 || tau <=0) continue;
    // if(amp > 0.1 || tau > 16) continue;
 
    amp19->SetBinContent(i-54,amp);
    amp19->SetBinError(i-54,damp);
    tau19->SetBinContent(i-54,tau);
    tau19->SetBinError(i-54,dtau);
  }


    // Draw

  amp13->Draw();
  tau13->Draw();
  amp19->Draw();
  tau19->Draw();

  
  output->Write();
  output->Close();
  
  laserFileA.close();
  laserFileTau.close();
 
  return 0;

  /*
  TCanvas *c2 = new TCanvas();//"c2","c2",2000,1000);
  tau13->SetStats(0);
  tau13->SetMarkerColor(kOrange+2);
  tau19->SetMarkerColor(kBlue+2);
  tau13->SetLineWidth(0);
  tau19->SetLineWidth(0);
  tau13->SetMarkerStyle(kStar);
  tau19->SetMarkerStyle(kStar); 
  tau13->Draw();//"P");
  tau19->Draw();//"P same"); 
  //  tau13->Draw();
  //tau19->Draw();
  c2->BuildLegend(0.78,0.79,0.89,0.89);
  //  tau13->SetTitle("Recovery times;In Fill Time [#mus];N");
  tau13->SetTitle("Recovery times;Crystal Number;Recovery time [#mus]");
  tau13->SetDirectory(output);
  tau19->SetDirectory(output);
  // c2->SaveAs("tau_sam_xtal.png");
  // c2->SaveAs("tau_laser_xtal.png");
  delete c2;

  TCanvas *c3 = new TCanvas();//"c3","c3",2000,1000);
  amp13->SetStats(0);
  amp13->SetMarkerColor(kOrange+2);
  amp19->SetMarkerColor(kBlue+2);
  amp13->SetLineWidth(0);
  amp19->SetLineWidth(0);
  amp13->SetMarkerStyle(kStar);
  amp19->SetMarkerStyle(kStar);
  amp13->Draw();//"P");
  amp19->Draw();//"P same");
  //  amp13->Draw();
  // amp19->Draw("same");


  c3->BuildLegend(0.78,0.79,0.89,0.89);
  // amp13->SetTitle("Amplitudes;Amplitude;N");
   amp13->SetTitle("Amplitudes;Crytal Number;Amplitude");
  amp13->SetDirectory(output);
  amp19->SetDirectory(output);
 
  // c3->SaveAs("amp_sam_xtal.png");
  //  c3->SaveAs("amp_laser_xtal.png");
  delete c3;
*/

}
