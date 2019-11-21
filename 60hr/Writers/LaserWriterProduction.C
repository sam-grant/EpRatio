// Read laser parameter fcl file, pull in-fill gain parameters for calos 13 & 19
// Sam Grant 
// October 2019
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

  // Book output file
  string outputName = "../ROOT/LaserParametersProduction_60hr.root";
  TFile *output = new TFile(outputName.c_str(), "recreate");

  // Book some holder histograms
  TH1D *tau13 = new TH1D("tau_13","Calo 13",54,-0.5,53.5);
  TH1D *tau19 = new TH1D("tau_19","Calo 19",54,-0.5,53.5);
  TH1D *amp13 = new TH1D("amp_13","Calo 13",54,-0.5,53.5);
  TH1D *amp19 = new TH1D("amp_19","Calo 19",54,-0.5,53.5);

  // Open input
  ifstream file("../Txt/inFillGainParams_withexpstdp.fcl");
  //ifstream fclFile("../Txt/laser_A_errors_full.csv");

  // Dump all the lines into a string
  vector<string> lines_;
  char delim = ','; // Define the delimiter to split by
  string tmp;
  if(file.is_open()) {
    cout << "File open... starting\n" << endl;

    while (getline(file, tmp)) {
    //  cout << tmp << endl;
      lines_.push_back(tmp);
    }
  }
  else {
    cout << "Error, file not opened\n" << endl;
  }

  // We have three datasets in logical order, 60hr, 9d, EndGame
//  vector<string> datasets_;
//  datasets_.push_back("ifgf_withstdp_60h: {");
//  datasets_.push_back("ifgf_withstdp_9d: {");
//  datasets_.push_back("ifgf_withstdp_EndGame: {");
/*
     getline(inFile,line); // get line from file
      pos=line.find(search); // search
      if(pos!=string::npos) // string::npos is returned if string is not found
        {
            cout <<"Found!";
            break;
        }
  }*/
  size_t pos;
  for (int i(0); i<lines_.size(); i++) {
   // cout<<"line "+to_string(i)+" * "+lines_.at(i)<<endl;
    //if (lines_.at(i)=="    calo13: {") {

    pos=lines_.find("60h");

            if(pos!=string::npos) // string::npos is returned if string is not found
            {
              cout <<"Found!";
              break;
            }
          }
          
/*    if (lines_.at(i)==datasets_.at(0)) {
      cout<<lines_.at(i)<<endl;
    }
  }*/
/*
  vector<string> amp, vector<string> tau;
 


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

  cout<<"Created "<<outputName<<" "<<output<<endl;*/
 
  return 0;
}
