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
double pull(double Ep_content,double laser_content, double Ep_error, double laser_error) {
  double sigma = sqrt(Ep_error*Ep_error + laser_error*laser_error);
  double result = (Ep_content - laser_content) / sigma;
  return result; 
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title) {
  TH1D *hist_clone = (TH1D*)hist->Clone("hist_clone");
  
  // Gauss fitter
  TF1 *g = new TF1("gauss","gaus");
 
  g->SetLineWidth(2);
  hist_clone->Fit(g);
   
  TCanvas *c = new TCanvas("c","c",1500,1000);
 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(11);
  gStyle->SetStatW(0.15);
  // Set width of stat-box (fraction of pad size)
  hist_clone->SetLineWidth(2);
  hist_clone->SetLineColor(kBlack);
  hist_clone->SetTitle(title.c_str());
  gPad->SetGridx();
  hist_clone->DrawCopy();
  c->SaveAs(name.c_str());
  hist_clone->SetDirectory(output);
  delete hist_clone;
  delete c;
  return;
}


int main() {
  // Get inputs
  bool full = true;//false;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  bool quality = true;//false;
  string input_Ep_name, input_laser_name, output_name, label;
  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_Q.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "stat_pull_1D_Q.root";
    label = all+"Q.png";
  }
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "stat_pull_1D_noQ.root";
    label = all+"noQ.png";
  }
  TFile *input_Ep = TFile::Open(input_Ep_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());
  // Set output
  TFile *output = new TFile(output_name.c_str(),"RECREATE");
  // Book historgrams
  int nBins = 24;
  TH1D *pull_tau13 = new TH1D("1D_tau_13","1D_tau_13",nBins,-3,3);//-4,2.6);//28
  TH1D *pull_tau19 = new TH1D("1D_tau_19","1D_tau_19",nBins,-3,3);//-4,2.6);//28
  TH1D *pull_amp13 = new TH1D("1D_amp_13","1D_amp_13",nBins,-3,3);//-4,2.6);//20
  TH1D *pull_amp19 = new TH1D("1D_amp_19","1D_amp_19",nBins,-3,3);//-4,2.6);//20
  // Hist name
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
  // }
 pull_tau13->SetName("#tau");

  pull_tau13->Add(pull_tau19);
   // pull_tau19->SetName("#tau");
    pull_amp13->SetName("A");
  pull_amp13->Add(pull_amp19);
  //  pull_amp19->SetName("A")
  pull_tau13->Add(pull_amp13);
    
  draw(pull_tau13,output,("pull_1D"+label).c_str(),"Calos 13 & 19 | Statistical Pull (All Parameters);Pull [#sigma];Entries");
  //  draw(pull_tau13,output,("stdev_tau13"+label).c_str(),"Calo 13 | Recovery Time Pull;Pull [#sigma];Entries");
  //draw(pull_tau19,output,("stdev_tau19"+label).c_str(),"Calo 19 | Recovery Time Pull;Pull [#sigma];Entries");
  //   draw(pull_amp13,output,("pull_amp_1D"+label).c_str(),"Calos 13 & 19 | Amplitude Pull;Pull [#sigma];Entries");
   //  draw(pull_amp13,output,("stdev_amp13"+label).c_str(),"Calo 13 | Amplitude Pull;Pull [#sigma];Entries");
   //  draw(pull_amp19,output,("stdev_amp19"+label).c_str(),"Calo 19 | Amplitude Pull;Pull [#sigma];Entries");
  
  ///////////////////////////////////////////////////////////////

  output->Write();
  output->Close();

  return 0;
}
