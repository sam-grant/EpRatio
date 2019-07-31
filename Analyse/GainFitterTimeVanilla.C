// Sam Grant April-June 2019
// samuel.grant.18@ucl.ac.uk
// April-June 2019

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TDirectory.h"

using namespace std;

double PseudoWiggle(double *x, double *par) {
  return par[0]*(1+par[1]*cos(par[2]*x[0]+par[3]));
}

int main() {
    bool save = true;
  // Define number of g-2 cycles to use 
  int cycles = 25;
  int range = 15;
 
  // Open input ROOT file
  string inputFname = "RootFiles/PlotsTimeCorrected.root";
  TFile *input = TFile::Open(inputFname.c_str());
  
  // Book output ROOT file
  string outputFname = "RootFiles/FitsTimeCorrected.root";
  TFile *output = new TFile(outputFname.c_str(), "recreate");
  
  // Define time limitOA
  const int maxTime = 4.2*cycles;

  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {
   
    // Fid loop
    for (int fid(0); fid < 2; fid++) {
      if(fid==1) continue;
      // Book histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(fid);
      TH1D *hist = (TH1D*)input->Get(h.c_str());
      // Skip empty ones
      if(hist == 0) continue;
      // Book the gain sag function
      TF1 *f1 = new TF1("f1", PseudoWiggle, 4.2, 4.2*range, 4);
      f1->SetNpx(100000);
      f1->SetParameter(1,0.001);
      f1->SetParameter(2,1.5);
      f1->SetParName(0,"G_{0}");
      f1->SetParName(1,"A");
      f1->SetParName(2,"#omega");
      f1->SetParName(3,"#phi");
      hist->Fit(f1,"R");

      // Get fit constants 
      double N = hist->GetEntries();
      double chiSqrNDF = f1->GetChisquare() / f1->GetNDF();
      double N0 = f1->GetParameter(0);
      double A = f1->GetParError(1);
      double omega = f1->GetParameter(2);
      double phi = f1->GetParameter(3);
      
      // Book canvas
      TCanvas *c1 = new TCanvas("c1","c1",3000,2000);

      // Draw, format, and save
      hist->SetStats(1);
      gStyle->SetOptStat(10);
      gStyle->SetOptFit(111);
      //      gStyle->SetStatH(0.13);
      hist->SetLineWidth(2);
      f1->SetLineWidth(5);

      hist->GetXaxis()->SetTitle("In Fill Time [#mus]");
      if(stn==13) hist->GetYaxis()->SetRangeUser(0.952,0.966);
      if(stn==19) hist->GetYaxis()->SetRangeUser(0.958,0.967);
		
      hist->GetXaxis()->SetRangeUser(0,4.2*cycles);
      hist->Draw();
      f1->Draw("same");
      hist->SetDirectory(output);
      if (save){
		c1->SaveAs(("Plots/"+h+"_corr_fits.png").c_str());
      }
      delete c1;
    }
  }
  // Write and close input/output
  output->Write();
  output->Close();
  input->Close();

  cout << "Created: " << outputFname << endl;
  return 0; 
}



