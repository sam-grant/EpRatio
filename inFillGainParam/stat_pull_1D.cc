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
  TF1 *g = new TF1("gauss","gaus");
  g->SetNpx(10000);
  g->SetLineWidth(2);
  g->SetParLimits(1,-1,1);
  //g->SetPa
  //  hist->Fit(g,"M","",-2,2);
  TCanvas *c = new TCanvas();
  // hist->SetStats(0);
  // gStyle->SetOptStat(0);
  // gStyle->SetOptFit();
  // gStyle->SetStatX(0.49);
  //gStyle->SetStatY(0.89);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  // hist->SetLineFill(0);
  hist->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGridx();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}


int main() {

  const double factor = 10000;
  
  string input_sam_name = "inFillGainParams_sam_xtal_errors_Q.root";
  string input_laser_name = "inFillGainParams_laser_xtal_errors_Q.root";

  TFile *input_sam = TFile::Open(input_sam_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());

  // Set output
  TFile *output = new TFile("stat_1D_err_Q.root","RECREATE");

   // book historgrams 
  TH1D *pull_tau13 = new TH1D("1D_tau_13","1D_tau_13",50,-3.5,3.5);//-4,2.6);//28
  TH1D *pull_tau19 = new TH1D("1D_tau_19","1D_tau_19",50,-3.5,3.5);//-4,2.6);//28
  TH1D *pull_amp13 = new TH1D("1D_amp_13","1D_amp_13",50,-3.5,3.5);//-4,2.6);//20
  TH1D *pull_amp19 = new TH1D("1D_amp_19","1D_amp_19",50,-3.5,3.5);//-4,2.6);//20

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

       
      sam = (TH1D*)input_sam->Get(h[i].c_str());
      if (sam==0) continue;
      laser = (TH1D*)input_laser->Get(h[i].c_str());
      if (laser == 0) continue;

      if(i == 0) {
	
	
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0 || sam_content == 0) continue;

	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0 || laser_content == 0) continue;

	//   if(laser_error > factor*laser_content || sam_error >  factor*sam_content) continue;
	tau13_pull=pull(sam_content,laser_content,sam_error,laser_error);
	
	cout << tau13_pull << endl;
	
	pull_tau13->Fill(tau13_pull);
	
      }
      
      else if(i == 1) {
	
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0 || sam_content == 0) continue;
	
	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0 || laser_content == 0) continue;

	//    	if(laser_error >  factor*laser_content || sam_error >  factor*sam_content) continue;
	
	tau19_pull=pull(sam_content,laser_content,sam_error,laser_error);
	
	cout << xtal <<" "<<tau19_pull << endl;
	
	
	pull_tau19->Fill(tau19_pull);
      }
      else if(i == 2) {

	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0|| sam_content == 0) continue;

	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0 || laser_content == 0) continue;

	// 	if(laser_error >  factor*laser_content || sam_error >  factor*sam_content) continue;

	amp13_pull=pull(sam_content,laser_content,sam_error,laser_error);
	
	cout << amp13_pull << endl;
	
	pull_amp13->Fill(amp13_pull);
      }
      else if(i == 3) {
	sam_content = sam->GetBinContent(xtal+1);
	sam_error = sam->GetBinError(xtal+1);
	if (sam_error == 0 || sam_content == 0) continue;

	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0 || laser_content == 0) continue;


	//	if(laser_error >  factor*laser_content || sam_error >  factor*sam_content) continue;
	
	amp19_pull=pull(sam_content,laser_content,sam_error,laser_error);
	
	cout << amp19_pull << endl;
	
	pull_amp19->Fill(amp19_pull);
      }
 
    }  
  }

  // pull_tau13->Add(pull_tau19);
  pull_tau13->SetName("#tau");
   pull_tau19->SetName("#tau");
    pull_amp13->SetName("A");
  // pull_amp13->Add(pull_amp19);
  pull_amp19->SetName("A");
    
  draw(pull_tau13,output,"stdev_tau13.png","Calo 13 | Recovery Times Comparison;Pull [#sigma];Entries");
   draw(pull_tau19,output,"stdev_tau19.png","Calo 19 | Recovery Time Comparison;Standard Deviations;Entries");
  draw(pull_amp13,output,"stdev_amp13.png","Calo 13 | Amplitudes Comparison;Pull [#sigma];Entries");
  draw(pull_amp19,output,"stdev_amp19.png","Calo 19 | Amplitude Comparison;Pull [#sigma];Entries");


  ///////////////////////////////////////////////////////////////

  output->Write();
  output->Close();

  return 0;
}
