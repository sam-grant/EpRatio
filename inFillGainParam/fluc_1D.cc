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


void drawNfit(TH1D *hist, string name) {
  TH1D *hist_clone = (TH1D*)hist->Clone("hist_clone");
   // Define the gaussian function                                                                                                                                                                        
  TF1 *gFunc = new TF1("gFunc", "gaus");
    // "Q" : supress printing "M" use minuit to improve fit result, "R" fit over range                                                                                                                      
  hist_clone->Fit(gFunc);//,"",fitMin,fitMax);
  TCanvas *c = new TCanvas();
  //  hist_clone->SetStats(0);

  hist_clone->SetStats(0);
  gStyle->SetOptStat(110010);
  //  gStyle->SetOptFit(11111);
  hist_clone->SetLineWidth(2);
  hist_clone->SetLineColor(kBlack);
  hist_clone->Draw();
  gPad->SetGridx();
  c->SaveAs(name.c_str());
  delete c;
}

int main() {

  TFile *laser_input = TFile::Open("inFillGainParams_laser_xtal_errors_Q.root");
  TFile *Ep_input = TFile::Open("inFillGainParams_Ep_xtal_errors_Q.root");
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  string name[2] = {"fluc_tau_1D_Q.png","fluc_amp_1D_Q.png"};//{"fluc_tau1D_13.png","fluc_tau1D_19.png","fluc_amp1D_13.png","fluc_amp1D_19.png"};
  string title[2] = {"Calos 13 & 19 | Recovery Time: Fractional Shift;Fractional Shift;Entries","Calos 13 & 19 | Amplitude: Fractional Shift;Fractional Shift;Entries"};
  // book historgrams
  TH1D *tau_fluc = new TH1D("tau_fluc","tau_fluc",12,-1.5,1.5);//54,-0.5,53.5);
  TH1D *amp_fluc = new TH1D("amp_fluc","amp_fluc",12,-1.5,1.5);//54,-0.5,53.5);

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
      // Get values
      value = fluc_val(laser_hist,Ep_hist,xtal);
      if (value == 1) continue; // AKA, the Ep value is zero
      if( fabs(error) > 2.0 ) continue;
      if(i==0 && xtal==23) continue;
      cout << xtal << " " << value << "+/-" << error << " " << (error/value) * 100 <<endl;
      if(i<2) {
	if(i==1 && xtal == 23) continue;
	tau_fluc->Fill(value);
      	tau_fluc->SetTitle(title[0].c_str());
      }
      else if(i>1) {
	amp_fluc->Fill(value);
	amp_fluc->SetTitle(title[1].c_str());
      }
    }
  }	  

  drawNfit(tau_fluc,"tau13_fluc_1D_Q.png");
  drawNfit(amp_fluc,"amp13_fluc_1D_Q.png");

  laser_input->Close();
  Ep_input->Close();

return 0;

}

