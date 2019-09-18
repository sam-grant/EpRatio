// Read 9 day ifg parameters from text file and put them in ROOT file
// Sam Grant 
// Sept 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdlib.h> 
#include "TFile.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "TCanvas.h"
#include "TStyle.h"

using namespace std;

void draw(TH1D *hist, TFile *output) {
  TCanvas *c = new TCanvas("c","c",3000,2000);
  hist->SetStats(0);
  hist->SetLineColor(kBlack);
  hist->SetLineWidth(3);
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);
  hist->SetTitleSize(.075);
  hist->GetXaxis()->SetTitleSize(.075);
  hist->GetYaxis()->SetTitleSize(.075);
  hist->GetYaxis()->SetTitleOffset(0.25);
  hist->GetXaxis()->SetTitleOffset(0.25);
  hist->Draw();
  hist->SetDirectory(output);
  delete c;
  return;
}

int main() {
  // Book output
  string outputFname = "RootFiles/ifg_9day.root";
  TFile *output = new TFile(outputFname.c_str(), "recreate");
  // Take input
  ifstream file_("/home/daq/omegaEU/msorbara/gm2DevEuropa_v9_20_00/srcs/gm2analyses/europa/procedures/pileup-correction/01-build-apc-ds/ifg_corr_9d.txt");
  
  // Check that it opened
  if (!file_.is_open()) {
    cout << "\nError, file not opened" << endl;
    file_.close();
    return 0;
  }
  else {
    cout << "\nFile open... starting\n" << endl;
  }

  // Read entries and put them in a single vector
  // (It has to be strings, don't ask why)
  vector<string> allValues_;
  // Define the delimiter to split by
  char delim = ' ';
  // Temp string to hold entries
  string tmp;
  // Fill vector
  if(file_.is_open()) {
    while (getline(file_, tmp)) {
       allValues_.push_back(tmp);
    }
  }
  cout<<"Finished reading, closing file\n"<<endl;
  file_.close();
  
// 54 xtals per calo -> 1296 crystals 
  // Calo 13: 649 to 702
  // Calo 19: 973 to 1026
  vector<double> amp13_, amp19_, tau13_, tau19_;
  // Parse each line and pick out amps and taus
  // Put this in a function SAM
  for(int i(0); i<allValues_.size(); i++) {
    // Calo 13
    if(i>=649 && i<= 702) {
      stringstream ss(allValues_.at(i));
      int counter13 = 0;
      while(getline(ss,tmp,delim)){
	// atof nicely converts string to doubles
	double token = atof((tmp).c_str());
	counter13++;
	if(counter13==2) amp13_.push_back(token);
	else if(counter13==3) tau13_.push_back(token*1.25); // Convert from clock ticks
      }
    }
    // Calo 19
    if(i>=973 && i<= 1026) {
      stringstream ss(allValues_.at(i));
      int counter19 = 0;
      while(getline(ss,tmp,delim)){
        double token = atof((tmp).c_str());
        counter19++;
        if(counter19==2) amp19_.push_back(token);
        else if(counter19==3) tau19_.push_back(token*1.25);
      }
    }
  }

  TH1D *tau13 = new TH1D("tau_13","Calo 13;Xtal;#tau [#mus]",54,-0.5,53.5);
  TH1D *tau19 = new TH1D("tau_19","Calo 19;Xtal;#tau [#mus]",54,-0.5,53.5);
  TH1D *amp13 = new TH1D("amp_13","Calo 13;Xtal;#alpha",54,-0.5,53.5);
  TH1D *amp19 = new TH1D("amp_19","Calo 19;Xtal;#alpha",54,-0.5,53.5);

  for (int i(0); i<54; i++) {
    tau13->SetBinContent(i+1,tau13_.at(i));
    tau19->SetBinContent(i+1,tau19_.at(i));
    amp13->SetBinContent(i+1,amp13_.at(i));
    amp19->SetBinContent(i+1,amp19_.at(i));
  }

  draw(tau13,output);
  draw(tau19,output);
  draw(amp13,output);
  draw(amp19,output);
  
  output->Write();
  output->Close();

  cout<<"Output written to "<<outputFname<<" *** "<<output<<"\n"<<endl;
 
  return 0;
}
