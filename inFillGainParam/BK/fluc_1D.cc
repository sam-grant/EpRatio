// Make plots of the fluctuation, combined between both stations
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
#include "TGraphErrors.h"

using namespace std;

// Fluctation is basically the fractional error
double fluc_val(TH1D *laser_hist, TH1D *ep_hist, int iter) {
    double laser_value = laser_hist->GetBinContent(iter+1);
    double ep_value = ep_hist->GetBinContent(iter+1);
    double laser_error = laser_hist->GetBinError(iter+1);
    double ep_error = ep_hist->GetBinError(iter+1);
    // Fractional shift
    double result = (laser_value - ep_value) / laser_value;
    return result;
}

double fluc_err(TH1D *laser_hist, TH1D *ep_hist, int iter) {
  double laser_value = laser_hist->GetBinContent(iter+1);
  double ep_value = ep_hist->GetBinContent(iter+1);
  // Fractional shift
  double result = (laser_value - ep_value) / laser_value;
  double laser_error = laser_hist->GetBinError(iter+1);
  double ep_error = ep_hist->GetBinError(iter+1);
  // Calcuate the uncertainty
  double term1 = (sqrt(laser_error*laser_error+ep_error*ep_error))/(laser_value-ep_value); // Checked
  double term2 = (laser_error/laser_value); // Checked
  double result_error = result * sqrt(term1*term1+term2*term2); // Checked
  return result_error; 
}

// double shift(TH1D *laser_hist, TH1D *ep_hist, int iter) {
//   double laser_value = laser_hist->GetBinContent(iter+1);
//   double ep_value = ep_hist->GetBinContent(iter+1);
//   // Fractional shift
//   double diff = (laser_value - ep_value);
//   if(diff == laser_value) return 1000;
//   double laser_error = laser_hist->GetBinError(iter+1);
//   double ep_error = ep_hist->GetBinError(iter+1);
//   // Calcuate the uncertainty
//   double diff_err = sqrt(laser_error*laser_error+ep_error*ep_error);
//   double result = diff / fabs(diff_err);
//   return result;
// }


void drawNfit(TH1D *hist, string name, string title) {
  TH1D *hist_clone = (TH1D*)hist->Clone("hist_clone");
  // Define the gaussian function                                                                                                                                                                        
  TF1 *gFunc = new TF1("gFunc", "gaus");
  gFunc->SetLineWidth(2);
  //  hist_clone->Fit(gFunc);

  TCanvas *c = new TCanvas("c","c",1500,1000);
  // gStyle->SetOptFit(11);
  // Set x-position (fraction of pad size)
  gStyle->SetStatW(0.15);                
  // Set width of stat-box (fraction of pad size)
  //gStyle->SetStatH(0.2); 
  //gStyle->SetStatX(0.40);
  // gStyle->SetStatY(0.89);
  hist_clone->SetName("Fractional Uncertainty");
  hist_clone->SetTitle(title.c_str());
  hist_clone->SetLineWidth(2);
  hist_clone->SetLineColor(kBlack);
  hist_clone->Draw();
  gPad->SetGridx();
  c->SaveAs(name.c_str());
  delete c;
}

int main() {
  // Get input                                                                                                                                               
  bool full = true;//xtrue;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  bool quality = true;//false;
  string input_Ep_name, input_laser_name, output_name, label;

  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_Q.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "shift_1D"+all+"Q.png";//root";
    label = all+"Q.png";
  }
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "shift_1D"+all+"noQ.png";//root";
    label = all+"noQ.png";
  }
  
  TFile *laser_input = TFile::Open(input_laser_name.c_str());
  TFile *Ep_input = TFile::Open(input_Ep_name.c_str());
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  //  string name[2] = {"fluc_tau_1D_Q.png","fluc_amp_1D_Q.png"};//{"fluc_tau1D_13.png","fluc_tau1D_19.png","fluc_amp1D_13.png","fluc_amp1D_19.png"};
  //  string title[2] = {"Calos 13 & 19 | Recovery Time: Fractional Shift;Fractional Shift;Entries","Calos 13 & 19 | Amplitude: Fractional Shift;Fractional Shift;Entries"};
  // book historgrams
  
  int Nbins = 24;
  TH1D *tau_fluc = new TH1D("tau_fluc","tau_fluc",Nbins,-3,3);//54,-0.5,53.5);
  TH1D *amp_fluc = new TH1D("amp_fluc","amp_fluc",Nbins,-3,3);//54,-0.5,53.5);

  TH1D *laser_hist;
  TH1D *Ep_hist;
  double value;
  double error;

  for(int i(0); i<4; i++) {
    // Get histograms
    laser_hist = (TH1D*)laser_input->Get(h[i].c_str());
    Ep_hist = (TH1D*)Ep_input->Get(h[i].c_str());
    // Start crystal loop
    for (int xtal(0); xtal<54; xtal++) {
      // Get values and errors
      //      if(xtal==23
      value = fluc_val(laser_hist,Ep_hist,xtal);
      error = fluc_err(laser_hist,Ep_hist,xtal);
      if (value == 1) continue; // AKA, the Ep value is zero
	cout << i << " "  <<xtal << " " << value << "+/-" << error << " " << (error/value) * 100 <<endl;
	tau_fluc->Fill(value);
    }
  }	  

  drawNfit(tau_fluc,output_name,"Calos 13 & 19 | Fractional Uncertainty (All Parameters);Fractional Uncertainty;Entries");
  //  drawNfit(amp_fluc,("amp_fluc_1D"+label).c_str());

  laser_input->Close();
  Ep_input->Close();

return 0;

}

