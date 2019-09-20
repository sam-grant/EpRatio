// Code to read fit parameters per xtal and put them in a ROOT file
// May 2019
// Sam Grant
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

int main() {
  /* bool quality = true; */
  /* bool skip = true; */
  /* // Set input and output */
  /* string suffix; */
  /* if(quality && skip) suffix = "";//"_skip18_Q"; */
  /* else if(!quality && skip) suffix = "_skip18_noQ"; */
  /* else if(quality && !skip) suffix = "_Q"; */
  /* else if(!quality && !skip) suffix = "_noQ"; */

  //  string suffix = "";
  string input_name = "RootFiles/FitsTimeXtal_9day_Q.root";//"+suffix+".root";
  string output_name = "RootFiles/EpParameters_9day_Q.root";//+suffix+".root";
      
  TFile *input = TFile::Open(input_name.c_str());
  TFile *output = new TFile(output_name.c_str(),"RECREATE");

  // Book historgrams 
  TH1D *tau13 = new TH1D("tau_13","tau_13",54,-0.5,53.5);
  tau13->SetTitle("Calo 13 | Recovery Times;xtal;#tau");
  TH1D *tau19 = new TH1D("tau_19","tau_19",54,-0.5,53.5);
  tau19->SetTitle("Calo 19 | Recovery Times;xtal;#tau");
  TH1D *amp13 = new TH1D("amp_13","amp_13",54,-0.5,53.5);
  amp13->SetTitle("Calo 13 | Amplitudes;xtal;A");
  TH1D *amp19 = new TH1D("amp_19","amp_19",54,-0.5,53.5);
  amp19->SetTitle("Calo 19 | Amplitudes;xtal;A");
  // Chi squared
  TH1D *chi13 = new TH1D("chi_13","chi_13",54,-0.5,53.5);
  chi13->SetTitle("St 13 |  #chi^{2} / NDF;xtal; #chi^{2} / NDF");
  TH1D *chi19 = new TH1D("chi_19","chi_19",54,-0.5,53.5);
  chi19->SetTitle("St 19 | #chi^{2} / NDF;xtal;#chi^{2} / NDF");
  // Entries
  TH1D *N13 = new TH1D("N_13","N_13",54,-0.5,53.5);
  N13->SetTitle("St 13 |  Entries;xtal; Entries");
  TH1D *N19 = new TH1D("N_19","N_19",54,-0.5,53.5);
  N19->SetTitle("St 19 | Entries;xtal;Entries");

  // Book params
  double amp, amp_err, tau, tau_err, chiSq, N;

  // Station loop
  for (int stn = 13; stn < 20; stn = stn + 6) {
    for (int xtal = 0; xtal < 54; xtal++ ) {
      // Get input histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      TH1D *hist = (TH1D*)input->Get(h.c_str());
      // Chuck empty ones
      if (hist == 0) continue;
      // Get fit
      TF1 *fit = (TF1*)hist->GetFunction("f1");
      // Get parameters
      amp = fit->GetParameter(1);
      amp_err = fit->GetParError(1);
      tau = fit->GetParameter(2);
      tau_err = fit->GetParError(2);
      chiSq = fit -> GetChisquare() / fit->GetNDF();
      N = hist->GetEntries();

      //Fill histograms
      if (stn == 13) {
	if(xtal==17) continue;
	tau13->SetBinContent(xtal+1,tau);
	tau13->SetBinError(xtal+1,tau_err);
	amp13->SetBinContent(xtal+1,amp);
	amp13->SetBinError(xtal+1,amp_err);
	chi13->SetBinContent(xtal+1,chiSq);
	N13->SetBinContent(xtal+1,N);
      }
      else if (stn == 19) {
	tau19->SetBinContent(xtal+1,tau);
	tau19->SetBinError(xtal+1,tau_err);
	amp19->SetBinContent(xtal+1,amp);
	amp19->SetBinError(xtal+1,amp_err);
	chi19->SetBinContent(xtal+1,chiSq);
	N19->SetBinContent(xtal+1,N);
      }
    }
  }
  amp13->Draw();
  tau13->Draw();
  amp19->Draw();
  tau19->Draw();
  chi13->Draw();
  chi19->Draw();
  N13->Draw();
  N19->Draw();
  amp13->SetDirectory(output);
  tau13->SetDirectory(output);
  amp19->SetDirectory(output);
  tau19->SetDirectory(output);
  chi13->SetDirectory(output);
  chi19->SetDirectory(output);
  N13->SetDirectory(output);
  N19->SetDirectory(output);
  output->Write();
  output->Close();
 
  cout<<"\nCreated "<<output_name<<endl;
 
  return 0;
}
