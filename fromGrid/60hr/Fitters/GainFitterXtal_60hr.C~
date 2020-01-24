// Fitting code for gain functions per xtal
// Sam Grant April-June 2019
// samuel.grant.18@ucl.ac.uk
// April-June 2019

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TPaveStats.h"

using namespace std;

// Define gain sag function, a simple exponetial 
double GainSag(double *x, double *par) {
  double time = x[0];
  double N0 = par[0]; // Overall normalisation
  double A = par[1]; // Amplitude 
  double tau = par[2]; // Recovery time  
  double N  = N0 * ( 1 - A * ( exp( - time / tau ) ) );
  return N; 
}

int main() {
  
  bool quality = true;
  bool save = false;
  // Number of g-2 cycles
  int cycles = 23;
  // Fit range
  int range = 23;
  string suffix;
  // Counter for crystals 
  int counter = 0;
  double tau_err_tot = 0.0;
  double amp_err_tot = 0.0;
  double chi_tot = 0.0;
 
  // Open input ROOT file
  // string inputFname = "RootFiles/plots_TimeXtalLong"+suffix+".root";
  string inputFname = "RootFiles/PlotsTimeXtalFid_60hr.root";
 
  TFile *input = TFile::Open(inputFname.c_str());
  cout << "Reading ... " << inputFname << endl;

  if(quality) suffix = "_Q";
  else if(!quality) suffix = "_noQ";

  // Book output ROOT file
  string outputFname = "RootFiles/FitsTimeXtal_60hr"+suffix+".root";
  TFile *output = new TFile(outputFname.c_str(), "recreate");
  
  // Define time limit
  const int maxTime = 4.2*cycles;

  cout<<"Xtal,N,ChiSqrNdf,Tau,dTau,Alpha,dAlpha"<<endl;
  //cout<<"dTau,dAlpha"<<endl;
  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {

    // Crystal loop
    for (int xtal(0); xtal < 54; xtal++) {

      // Book histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      TH1D *hist = (TH1D*)input->Get(h.c_str());

      // Skip empty ones
      if(hist == 0) continue;

      // Book the gain sag function
      TF1 *f1 = new TF1("f1", GainSag, 4.2, 4.2*range, 3);
      f1->SetNpx(10000);
      f1->SetLineWidth(3);
      f1->SetParameter(2,5);
      f1->SetParName(0,"G_{0}");
      f1->SetParName(1,"#alpha");
      f1->SetParName(2,"#tau_{r} [#mus]");

      // If the gain is unphysical then set error = value, to stop inflation of the chi squared
      /* for (int ibin(0); ibin < hist->GetXaxis()->GetNbins(); ibin++) { */
      /*   double binValue = hist->GetBinContent(ibin); */
      /*   if (binValue > 25.0) hist->SetBinError(ibin,binValue); */
      /* } */
      
      // Perform fit, over range "R", suppress output "Q", use minuit "M"
      hist->Fit(f1,"QMR");

      // Get fit constants 
      double N = hist->GetEntries();
      double chiSqrNDF = f1->GetChisquare() / f1->GetNDF();
      double A = f1->GetParameter(1);
      double A_err = f1->GetParError(1);
      double tau = f1->GetParameter(2);
      double tau_err = f1->GetParError(2);

      /////////////////////////////////////////////////////
      //QUALITY CUTS
      /////////////////////////////////////////////////////
       if (quality) {
        // Avoid low stats
        if (N < 100000) continue;
        // Require a reasonable reduced chi square
        if( chiSqrNDF < 0.25 || chiSqrNDF > 4) continue;
        // Require low relative error
        if( tau_err > 0.5*tau || A_err > 0.5*A) continue;
      }

      // Add up surviving crystals
      counter++;

      hist->SetStats(1);
      hist->Draw();
      gStyle->SetStatFormat("6.3g"); 
      gStyle->SetOptStat(10);
      gStyle->SetOptFit(111);
      //Collect stats of the first histogram
      gPad->Update();

      TPaveStats *tps1 = (TPaveStats*)hist -> FindObject("stats");
      tps1->SetLineWidth(0);
      tps1->SetX1NDC(0.49);
      tps1->SetX2NDC(0.89);
      tps1->SetY1NDC(0.65);
      tps1->SetY2NDC(0.89);

      // Book canvas, make it high def
      TCanvas *c1 = new TCanvas("c","",800,600);
      hist->SetLineWidth(3);
      hist->GetXaxis()->SetTitle("In Fill Time [#mus]");
      hist->GetYaxis()->SetTitle("E/p");
      hist->GetXaxis()->CenterTitle(true);
      hist->GetYaxis()->CenterTitle(true);
      hist->SetTitleSize(.75);
      hist->GetXaxis()->SetTitleSize(.04);
      hist->GetYaxis()->SetTitleSize(.04);
      hist->GetYaxis()->SetTitleOffset(1.1);
      hist->GetXaxis()->SetTitleOffset(1.1);      
      hist->GetYaxis()->SetRangeUser(0.99,1.01);
      hist->GetXaxis()->SetRangeUser(0,4.2*cycles);
      //hist->SetStats(0);
      hist->Draw();
      tps1->Draw("same");
      hist->SetDirectory(output);

      if (save) {
		c1->SaveAs(("PlotsGoldList/"+h+".pdf").c_str());
      }
      // Make some print outs
      cout<<xtal<<","<<N<<","<<chiSqrNDF<<","<<tau<<","<<tau_err<<","<<A<<","<<A_err<<endl;
      //cout<<tau_err<<","<<A_err<<endl;
      tau_err_tot = tau_err_tot + tau_err;
      amp_err_tot = amp_err_tot + A_err;
      chi_tot = chi_tot + chiSqrNDF;
      // Delete the canvas
      delete c1;
    }
  }
  // Print out the number of xtals that pass quality cuts
  cout << "\nSurviving xtals: " << counter << endl;
  cout << "Mean tau_err = " << tau_err_tot / counter << endl;
  cout << "Mean amp_err = " << amp_err_tot / counter << endl;
  cout << "Mean chiSqrNDF = " << chi_tot / counter << endl;
  // Write and close input/output
  output->Write();
  output->Close();
  input->Close();

  cout << "Created: " << outputFname << endl;
  return 0; 
}



