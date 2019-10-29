// Read csv/txt laser parameters and put them in a ROOT file
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
#include "TDirectory.h"

using namespace std;

int main() {

  string path = "~/Documents/gm2/EpRatio/Analyse/60hr/";
  string outputName = path+"RootFiles/LaserParameters_60hr.root";
  TFile *output = new TFile(outputName.c_str(), "recreate");
  
  ifstream laserFileTau("../csvFiles/laser_tau_errors_full.csv");
  ifstream laserFileA("../csvFiles/laser_A_errors_full.csv");
  
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
  char delim = ','; // Define the delimiter to split by
  string tmp;
  if(laserFileTau.is_open()) {
    while (getline(laserFileTau, tmp, delim)) {
      laserTau.push_back(tmp);
      //  cout << tmp << endl;
    }
  }
  vector<string> laserA;
  // char delim = ','; // Define the delimiter to split by
  //string tmp;
  if(laserFileA.is_open()) {
    while (getline(laserFileA, tmp, delim)) {
      laserA.push_back(tmp);
    }
  }
 
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
    // Convert to clock ticks
    tau = tau * 1.25;

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
    // Convert to clock ticks
    tau = tau * 1.25;
 
    amp19->SetBinContent(i-54,amp);
    amp19->SetBinError(i-54,damp);
    tau19->SetBinContent(i-54,tau);
    tau19->SetBinError(i-54,dtau);
  }

  amp13->Draw();
  tau13->Draw();
  amp19->Draw();
  tau19->Draw();
  
  output->Write();
  output->Close();
  
  laserFileA.close();
  laserFileTau.close();

  cout<<"Created "<<outputName<<" "<<output<<endl;
 
  return 0;
}
