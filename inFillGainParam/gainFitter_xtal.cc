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
double gain_sag(double *x, double *par) {
  double time = x[0];
  double N0 = par[0]; // Overall normalisation
  double A = par[1]; // Amplitude 
  double tau = par[2]; // Recovery time  
  double N  = N0 * ( 1 - A * ( exp( - time / tau ) ) );
  return N; 
}

int main() {
  // Define number of g-2 cycles to use 
  const int cycles = 50;
  // Counter for crystals 
  int counter = 0;
  // To save plots to png then save = true  
  bool save = false;//true;//false;//true;
  // Apply quality cuts
  bool quality = true;
  // Open input ROOT file
  string input_fname = "../makePlots2/fits_time_normalised_xtal.root";
  TFile *input = TFile::Open(input_fname.c_str());
  cout << "Reading ... " << input_fname << endl;
  // Book output ROOT file
  string output_fname;
  if(quality) {
    output_fname = "taus_time_normalised_xtal_statCut.root";
  }
  else if(!quality) {
    output_fname = "taus_time_normalised_xtal_noQ.root";
  }
  TFile *output = new TFile(output_fname.c_str(), "recreate");
  // Book canvas, make it high def
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  
  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {
    // if (stn == 13) continue;
    cout<<"Station "<<stn<<endl;
    cout<<"xtal, Entries, chiSqr/NDF, tau, A "<<endl;
    
    // Crystal loop
    for (int xtal(0); xtal < 54; xtal++) {
      //  if (xtal != 22) continue;
      // Define time limit
      const int maxTime = 4.2*cycles;
      // Book histogram
      string h = "St"+to_string(stn)+"_fit_Ep_vs_t_early_"+to_string(xtal);
      TH1D *t_early = (TH1D*)input->Get(h.c_str());
      // Skip empty ones
      if(t_early == 0) continue;
      // If the gain is unphysical then set error = value, to stop inflation of the chi squared
      for (int ibin(0); ibin < t_early->GetXaxis()->GetNbins(); ibin++) {
      	double binValue = t_early->GetBinContent(ibin);
      	if (binValue > 25.0) t_early->SetBinError(ibin,binValue);
      }
      // Book the gain sag function
      TF1 *f1 = new TF1("f1", gain_sag, 0, maxTime, 3);
      f1->SetNpx(10000);
      // Set a starting time constant, expectation from laser is ~5 us  
      f1->SetParameter(2,5);
      f1->SetParName(0,"G_{0}");
      f1->SetParName(1,"A");
      f1->SetParName(2,"#tau_{r}");
      // Perform fit, over range "R", suppress output "Q", use minuit "M"
      t_early->Fit(f1,"QMR");

      // // Calculate your own chi squared as a cross check
      // double chi = 0.0;
      // for (int ibin(0); ibin < t_early->GetXaxis()->GetNbins(); ibin++){
      // 	double value = f1->Eval(t_early->GetBinCenter(ibin));
      // 	double cont = t_early->GetBinContent(ibin);
      // 	double err = t_early->GetBinError(ibin);
      // 	if (err > 0 && cont < 10000.5)
      // 	  chi += pow(fabs(cont - value),2) / pow(err,2);
      // 	// cout << "xtal "<< xtal << "chi user "<< chi_user << " chi_ROOT " << chi_root << endl;// << " fit: " << value << " chi: " << chi <<"\n";
      // }
      //  cout << "xtal "<< xtal << " chi user "<< chi_user << " chi ROOT " << chi_root << endl;
      
      // Get parameters
      const double N = t_early->GetEntries();
      const double chiSqrNDF = f1->GetChisquare() / f1->GetNDF();
      const double A = f1->GetParameter(1);
      const double A_err = f1->GetParError(1);
      const double tau = f1->GetParameter(2);
      const double tau_err = f1->GetParError(2);

      /////////////////////////////////////////////////////
      //QUALITY CUTS
      /////////////////////////////////////////////////////
      if (quality) {
	// Avoid low stats
	if (N < 50000) continue;
	// Require a reasonable reduced chi square
	//	if( chiSqrNDF < 0.25 || chiSqrNDF > 4) continue;
	// Require low error
	//if( tau_err > 0.5*tau || A_err > 0.5*A) continue;
      }
      cout << N << endl;
      ////////////////////////////////////////////////////
      // Add up surviving crystals
      counter++;
      cout<<counter<<endl;
      // Draw, format, and save
      t_early->SetStats(1);
      gStyle->SetOptStat(11);
      gStyle->SetOptFit();
      t_early->SetLineWidth(2);
      gStyle->SetStatX(0.49);
      gStyle->SetStatY(0.89);
      t_early->GetXaxis()->SetTitle("In Fill Time [#mus]");
      t_early->GetYaxis()->SetRangeUser(0.99,1.01);
      t_early->GetXaxis()->SetRangeUser(0,maxTime);
      t_early->Draw();
      t_early->SetDirectory(output);
      if (save){
		c1->SaveAs((h+".png").c_str());
      }
      // Make some print outs
      cout<<xtal<<", "<<N<<", "<<chiSqrNDF<<", "<<tau<<"+-"<<tau_err<<", "<<A<<"+-"<<A_err<<endl;
    }
    //      cout << "\nSurviving xtals: " << counter << endl;
      //      counter = 0;
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



