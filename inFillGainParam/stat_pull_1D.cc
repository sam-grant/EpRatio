// Get statisical pull between laser and E/p parameters in 1D
// Sam Grant
// samuel.grant.18@ucl.ac.uk
// May-June 2019

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"

using namespace std;

// Define pull 
double pull(double sam_content,double laser_content, double sam_error, double laser_error) {
  double sigma = sqrt(sam_error*sam_error + laser_error*laser_error);
  double result = (sam_content - laser_content) / sigma;
  return result; 
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title) {
  // Gauss fitter
  // TF1 *g = new TF1("gauss","gaus");
  // g->SetNpx(10000);
  // g->SetLineWidth(2);
  // g->SetParLimits(1,-1,1);
  // hist->Fit(g,"M","",-2,2);
  TCanvas *c = new TCanvas();
  // hist->SetStats(0);
  gStyle->SetOptStat(111111);
  // gStyle->SetOptFit();
  // gStyle->SetStatX(0.49);
  //gStyle->SetStatY(0.89);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGridx();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}


int main() {
  // Get inputs
  string input_Ep_name = "inFillGainParams_sam_xtal_errors_Q.root";
  string input_laser_name = "inFillGainParams_laser_xtal_errors_Q.root";
  TFile *input_Ep = TFile::Open(input_Ep_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());
  // Set output
  TFile *output = new TFile("stat_1D_err_Q.root","RECREATE");
  // Book historgrams 
  TH1D *pull_tau13 = new TH1D("1D_tau_13","1D_tau_13",50,-3.5,3.5);//-4,2.6);//28
  TH1D *pull_tau19 = new TH1D("1D_tau_19","1D_tau_19",50,-3.5,3.5);//-4,2.6);//28
  TH1D *pull_amp13 = new TH1D("1D_amp_13","1D_amp_13",50,-3.5,3.5);//-4,2.6);//20
  TH1D *pull_amp19 = new TH1D("1D_amp_19","1D_amp_19",50,-3.5,3.5);//-4,2.6);//20
  // Hist names
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  // Book output hists
  TH1D *Ep;
  TH1D *laser;
  double pull_value;
  double Ep_content;
  double Ep_error;
  double laser_content;
  double laser_error;
  
  for (int ihist(0); ihist < 4; ihist++) {
    cout<<"hist : "<<h[ihist]<<endl;
    for(int xtal(0); xtal < 54; xtal++) {
       
      Ep = (TH1D*)input_Ep->Get(h[ihist].c_str());
      laser = (TH1D*)input_laser->Get(h[ihist].c_str());

      Ep_content = Ep->GetBinContent(xtal+1);
	Ep_error = Ep->GetBinError(xtal+1);
	if (Ep_error == 0 || Ep_content == 0) continue;

	laser_content = laser->GetBinContent(xtal+1);
	laser_error = laser->GetBinError(xtal+1);
	if(laser_error == 0 || laser_content == 0) continue;

	
	//   if(laser_error > factor*laser_content || Ep_error >  factor*Ep_content) continue;
	pull_value=pull(Ep_content,laser_content,Ep_error,laser_error);
	
	cout<<"xtal: "<<xtal<<"; pull: "<<pull_value<<endl;
	if(ihist==0) pull_tau13->Fill(pull_value);
	if(ihist==1) pull_tau19->Fill(pull_value);
	if(ihist==2) pull_amp13->Fill(pull_value);
	if(ihist==3) pull_amp19->Fill(pull_value);	  //      }
    }
  }
  // 	  //      else if(ihist == 1) {
	
  // 	Ep_content = Ep->GetBinContent(xtal+1);
  // 	Ep_error = Ep->GetBinError(xtal+1);
  // 	if (Ep_error == 0 || Ep_content == 0) continue;
	
  // 	laser_content = laser->GetBinContent(xtal+1);
  // 	laser_error = laser->GetBinError(xtal+1);
  // 	if(laser_error == 0 || laser_content == 0) continue;

  // 	//    	if(laser_error >  factor*laser_content || Ep_error >  factor*Ep_content) continue;
	
  // 	tau19_pull=pull(Ep_content,laser_content,Ep_error,laser_error);
	
  // 	cout << xtal <<" "<<tau19_pull << endl;
	
	
  // 	pull_tau19->Fill(tau19_pull);
  //     }
  //     else if(ihist == 2) {

  // 	Ep_content = Ep->GetBinContent(xtal+1);
  // 	Ep_error = Ep->GetBinError(xtal+1);
  // 	if (Ep_error == 0|| Ep_content == 0) continue;

  // 	laser_content = laser->GetBinContent(xtal+1);
  // 	laser_error = laser->GetBinError(xtal+1);
  // 	if(laser_error == 0 || laser_content == 0) continue;

  // 	// 	if(laser_error >  factor*laser_content || Ep_error >  factor*Ep_content) continue;

  // 	amp13_pull=pull(Ep_content,laser_content,Ep_error,laser_error);
	
  // 	cout << amp13_pull << endl;
	
  // 	pull_amp13->Fill(amp13_pull);
  //     }
  //     else if(ihist == 3) {
  // 	Ep_content = Ep->GetBinContent(xtal+1);
  // 	Ep_error = Ep->GetBinError(xtal+1);
  // 	if (Ep_error == 0 || Ep_content == 0) continue;

  // 	laser_content = laser->GetBinContent(xtal+1);
  // 	laser_error = laser->GetBinError(xtal+1);
  // 	if(laser_error == 0 || laser_content == 0) continue;


  // 	//	if(laser_error >  factor*laser_content || Ep_error >  factor*Ep_content) continue;
	
  // 	amp19_pull=pull(Ep_content,laser_content,Ep_error,laser_error);
	
  // 	cout << amp19_pull << endl;
	
  // 	pull_amp19->Fill(amp19_pull);
  //     }
 
  //   }  
  // }

  // pull_tau13->Add(pull_tau19);
  pull_tau13->SetName("#tau");
   pull_tau19->SetName("#tau");
    pull_amp13->SetName("A");
  // pull_amp13->Add(pull_amp19);
  pull_amp19->SetName("A");
    
  draw(pull_tau13,output,"stdev_tau13.png","Calo 13 | Recovery Time Pull;Pull [#sigma];Entries");
   draw(pull_tau19,output,"stdev_tau19.png","Calo 19 | Recovery Time Pull;Standard Deviations;Entries");
  draw(pull_amp13,output,"stdev_amp13.png","Calo 13 | Amplitude Pull;Pull [#sigma];Entries");
  draw(pull_amp19,output,"stdev_amp19.png","Calo 19 | Amplitude Pull;Pull [#sigma];Entries");


  ///////////////////////////////////////////////////////////////

  output->Write();
  output->Close();

  return 0;
}
