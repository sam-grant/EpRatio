#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

int main() {
  // The "2" means 1 crystal hit per cluster 
  string input_name = "taus_time_normalised_xtal2.root";
  string output_name = "inFillGainParams_sam_xtal2_Q.root";
  
  TFile *input = TFile::Open(input_name.c_str());
  TFile *output = new TFile(output_name.c_str(),"RECREATE");
 
  // book historgrams 
  TH1D *tau13 = new TH1D("tau_13","tau_13",54,-0.5,53.5);
  TH1D *tau19 = new TH1D("tau_19","tau_19",54,-0.5,53.5);
  TH1D *amp13 = new TH1D("amp_13","amp_13",54,-0.5,53.5);
  TH1D *amp19 = new TH1D("amp_19","amp_19",54,-0.5,53.5);

  double amp;
  double amp_err;
  double tau;
  double tau_err;
    // Station loop
  for (int stn = 13; stn < 20; stn = stn + 6) {
    cout <<"Station " << stn << endl;
    for (int xtal = 0; xtal < 54; xtal++ ) {
      
    
      string h = "St"+to_string(stn)+"_fit_Ep_vs_t_early_"+to_string(xtal);
      TH1D *hist = (TH1D*)input->Get(h.c_str());
       if (hist == 0) continue;
 

      TF1 *fit = (TF1*)hist->GetFunction("f1");
     
      
      amp = fit->GetParameter(1);
      amp_err = fit->GetParError(1);
      tau = fit->GetParameter(2);
      tau_err = fit->GetParError(2);
      if(amp <= 0 || tau <=0) continue;
      if(amp > 0.1 || tau > 16) continue;
      
      cout<<xtal<<" | amp: "<<amp<<"+/-"<<amp_err<<"  | tau: "<<tau<<"+/-"<<tau_err<<endl;
      
      //Fill histograms
      if (stn == 13) {
	tau13->SetBinContent(xtal+1,tau);
	tau13->SetBinError(xtal+1,tau_err);
	amp13->SetBinContent(xtal+1,amp);
	amp13->SetBinError(xtal+1,amp_err);
      }
      else if (stn == 19) {
	tau19->SetBinContent(xtal+1,tau);
	tau19->SetBinError(xtal+1,tau_err);
	amp19->SetBinContent(xtal+1,amp);
	amp19->SetBinError(xtal+1,amp_err);
      }
      
      
    }
  }
 
  // Draw

  amp13->Draw();
  tau13->Draw();
  amp19->Draw();
  tau19->Draw();
  amp13->SetDirectory(output);
  tau13->SetDirectory(output);
  amp19->SetDirectory(output);
  tau19->SetDirectory(output);

  output->Write();
  output->Close();
     
  return 0;
}
