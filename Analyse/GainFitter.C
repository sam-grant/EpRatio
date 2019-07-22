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
  //  string suffix = "_skip18";
  string suffix = "";
  // Define number of g-2 cycles to use 
  int cycles = 50;
  int range = 50;

  // Counter for crystals 
  int counter = 0;
  
  // To save plots to png then save = true  
  bool save = false;
 
  // Open input ROOT file
  string input_fname = "RootFiles/plots_timeXtalLong"+suffix+".root";
  TFile *input = TFile::Open(input_fname.c_str());
  cout << "Reading ... " << input_fname << endl;

  if(quality) suffix = suffix+"_Q";
  else if(!quality) suffix = suffix+"_noQ";

  // Book output ROOT file
  string output_fname = "RootFiles/fits_timeXtalLong"+suffix+".root";
  TFile *output = new TFile(output_fname.c_str(), "recreate");

  
  // Define time limit
  const int maxTime = 4.2*cycles;

  // Book canvas, make it high def
  TCanvas *c1 = new TCanvas("c1","c1",1500,1000);
  
  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {

    // Crystal loop
    for (int xtal(0); xtal < 54; xtal++) {

      // Book histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      TH1D *hist = (TH1D*)input->Get(h.c_str());

      // Skip empty ones
      if(hist == 0) continue;

        // Set a starting time constant, expectation from laser is ~5 us  
      // Book the gain sag function
      TF1 *f1 = new TF1("f1", GainSag, 4.2, 4.2*range/4, 3);
      f1->SetNpx(10000);

                f1->SetParameter(2,5);
	  //  f1->SetParameter(1,0.01);
      f1->SetParName(0,"G_{0}");
      f1->SetParName(1,"A");
      f1->SetParName(2,"#tau_{r}");

      // If the gain is unphysical then set error = value, to stop inflation of the chi squared
      /* for (int ibin(0); ibin < hist->GetXaxis()->GetNbins(); ibin++) { */
      /*   double binValue = hist->GetBinContent(ibin); */
      /*   if (binValue > 25.0) hist->SetBinError(ibin,binValue); */
      /* } */
      
      // Perform fit, over range "R", suppress output "Q", use minuit "M"
      hist->Fit(f1,"QMR");
      // Normalise
      //      hist->Scale(1/f1->GetParameter(0));
      //hist->Fit(f1,"QMR");

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
        // Get rid of infinite errors please!
        if( isnan(tau_err) == true || isnan(A_err) == true ) continue;
        // Chop anything a factor of 100 greater than the expectation
        if(tau > 100 || A > 1) continue;
      }

      // Add up surviving crystals
      counter++;
    
      // Draw, format, and save
      hist->SetStats(1);
      gStyle->SetOptFit(11111);
      hist->SetLineWidth(3);
      f1->SetLineWidth(3);
      //      gStyle->SetStatX(0.49);
      //  gStyle->SetStatY(0.89);
      hist->GetXaxis()->SetTitle("In Fill Time [#mus]");
      hist->GetYaxis()->SetRangeUser(0.99,1.01);
      hist->GetXaxis()->SetRangeUser(0,4.2*cycles);
      hist->Draw();
      hist->SetDirectory(output);
      if (save){
		c1->SaveAs(("Plots/"+h+".png").c_str());
      }
      // Make some print outs
      cout<<xtal<<", "<<N<<", "<<chiSqrNDF<<", "<<tau<<"+-"<<tau_err<<", "<<A<<"+-"<<A_err<<endl;
    }
  }
  // Print out the number of xtals that pass quality cuts
  cout << "\nSurviving xtals: " << counter << endl;
  // Delete the canvas
  delete c1;

  // Write and close input/output
  output->Write();
  output->Close();
  input->Close();

  cout << "Created : " << output_fname << endl;
  return 0; 
}



