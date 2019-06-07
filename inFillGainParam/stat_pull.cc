// Get the abs statisical pull betwen laser and E/p
// Some of the messiest code ever written

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"

using namespace std;

double pull(double sam_content,double laser_content, double sam_error, double laser_error) {
  double sigma = sqrt(sam_error*sam_error + laser_error*laser_error);
  double result = (sam_content - laser_content)/sigma;
  // result = sqrt(result*result);
  return result; 
}

void draw(TH1D *hist, TFile *output, string name, string title) {
  TCanvas *c = new TCanvas();
  hist->SetStats(0);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  // hist->SetLineFill(0);
  hist->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGrid();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}


int main() {
  
  string input_sam_name = "inFillGainParams_sam_xtal_errors_Q.root";
  string input_laser_name = "inFillGainParams_laser_xtal_errors_Q.root";

  TFile *input_sam = TFile::Open(input_sam_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());

  // Set output
  TFile *output = new TFile("stat_pull.root","RECREATE");

   // book historgrams 
  TH1D *pull_tau13 = new TH1D("pull_tau_13","pull_tau_13",54,-0.5,53.5);
  TH1D *pull_tau19 = new TH1D("pull_tau_19","pull_tau_19",54,-0.5,53.5);
  TH1D *pull_amp13 = new TH1D("pull_amp_13","pull_amp_13",54,-0.5,53.5);
  TH1D *pull_amp19 = new TH1D("pull_amp_19","pull_amp_19",54,-0.5,53.5);
  pull_tau13->GetXaxis()->SetNdivisions(27);
  pull_tau19->GetXaxis()->SetNdivisions(27);
  pull_amp13->GetXaxis()->SetNdivisions(27);
  pull_amp19->GetXaxis()->SetNdivisions(27);

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};

  TH1D *sam;
  TH1D *laser;

  double tau13_pull;
  double amp13_pull;
  double tau19_pull;
  double amp19_pull;
  double sam_content;
  double sam_error;
  double laser_content;
  double laser_error;
  
  for (int i = 0; i < 4; i++) {
    	cout << h[i] << endl;
	
    for(int xtal = 0; xtal < 54; xtal++) {

      
      // xtal 15 is bad for station 19, get rid of it
      if((i == 1 && xtal == 15) || (i == 3 && xtal == 15)) continue;
      // xtal 51 is bad for station 13, get rid of it
      if((i == 0 && xtal == 51) || (i == 2 && xtal == 51)) continue;
      // xtal 35 is bad for station 13, get rid of it
       if((i == 0 && xtal == 35) || (i == 2 && xtal == 35)) continue;
      
      sam = (TH1D*)input_sam->Get(h[i].c_str());
      if (sam==0) continue;
      laser = (TH1D*)input_laser->Get(h[i].c_str());
      if (laser == 0) continue;

      if(i == 0) {
	
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0) continue;
     
	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0) continue;

	tau13_pull=pull(sam_content,laser_content,sam_error,laser_error);
	
	cout << tau13_pull << endl;
	
	pull_tau13->SetBinContent(xtal+1,tau13_pull);
	
      }
      
      else if(i == 1) {
	
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0) continue;
	
	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0) continue;
	
	tau19_pull=pull(sam_content,laser_content,sam_error,laser_error);
	cout << tau19_pull << endl;
	pull_tau19->SetBinContent(xtal+1,tau19_pull);
	
      }
      else if(i == 2) {

	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0) continue;
	
	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0) continue;

	amp13_pull=pull(sam_content,laser_content,sam_error,laser_error);
	cout << amp13_pull << endl;
	pull_amp13->SetBinContent(xtal+1,amp13_pull);
	
      }
      else if(i == 3) {
	
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0) continue;
	
	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0) continue;

	amp19_pull=pull(sam_content,laser_content,sam_error,laser_error);
	cout << amp19_pull << endl;
	pull_amp19->SetBinContent(xtal+1,amp19_pull);
      }
 
    }  
  }

 
    
  draw(pull_tau13,output,"pull_tau13_err.png","Calo 13 | Recovery Time Pull;Crystal Number;Pull [#sigma]");
  draw(pull_tau19,output,"pull_tau19_err.png","Calo 19 | Recovery Time Pull ;Crystal Number;Pull [#sigma]");
  draw(pull_amp13,output,"pull_amp13_err.png","Calo 13 | Amplitude Pull;Crystal Number;Pull [#sigma]");
  draw(pull_amp19,output,"pull_amp19_err.png","Calo 19 | Amplitude Pull;Crystal Number;Pull [#sigma]");


  ///////////////////////////////////////////////////////////////

  output->Write();
  output->Close();

  return 0;
}
