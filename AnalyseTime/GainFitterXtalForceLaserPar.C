// Fitting code for gain functions per xtal
// Force them to take the laser parameters
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
  bool save = true;
  // Number of g-2 cycles
  int cycles = 50;
  // Fit range
  int range = 23;
  string suffix;
  // Counter for crystals 
  int counter = 0;
 
  // Open input ROOT file
  // string inputFname = "RootFiles/plots_TimeXtalLong"+suffix+".root";
  string inputFname1 = "RootFiles/PlotsTimeXtal.root";//Long"+suffix+".root";
  string inputFname2 = "RootFiles/LaserParameters.root";
  TFile *input1 = TFile::Open(inputFname1.c_str());
  TFile *input2 = TFile::Open(inputFname2.c_str());

  cout << "Reading ... " << inputFname1 << ", " << inputFname2 << endl;

  if(quality) suffix = "_Q";
  else if(!quality) suffix = "_noQ";

  // Book output ROOT file
  string outputFname = "RootFiles/FitsTimeXtalFixLaser"+suffix+".root";
  TFile *output = new TFile(outputFname.c_str(), "recreate");
  
  // Define time limit
  const int maxTime = 4.2*cycles;

  cout<<"Xtal,N,ChiSqrNdf,Tau,dTau,Alpha,dAlpha"<<endl;
  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {

    // Crystal loop
    for (int xtal(0); xtal < 54; xtal++) {

      // Book histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      TH1D *hist = (TH1D*)input1->Get(h.c_str());

      // Skip empty ones
      if(hist == 0) continue;

      // Book the gain sag function
      TF1 *f1 = new TF1("f1", GainSag, 4.2, 4.2*range, 3);
      f1->SetNpx(10000);
      f1->SetLineWidth(5);
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

       // Now fix parameters to laser
       TF1 *f2 = new TF1("f2", GainSag, 4.2, 4.2*range, 3);
       f2->SetLineColor(kGreen+2);
       f2->SetLineWidth(5);
       string tauName = "tau_"+to_string(stn);
       string ampName = "amp_"+to_string(stn);
       TH1D *hTau = (TH1D*)input2->Get(tauName.c_str());
       TH1D *hAmp = (TH1D*)input2->Get(ampName.c_str());
       double ALaser = hAmp->GetBinContent(xtal+1);
       double tauLaser = hTau->GetBinContent(xtal+1);
       f2->FixParameter(1,ALaser);
       f2->FixParameter(2,tauLaser);
       hist->Fit(f2,"QMR");
       chiSqrNDF = f2->GetChisquare() / f2->GetNDF();
       if( chiSqrNDF < 0.25 || chiSqrNDF > 4) continue;

             // Add up surviving crystals
      counter++;
     
      // Book canvas, make it high def
      TCanvas *c1 = new TCanvas("","",3000,2000);
 
      // Draw, format, and save
      hist->SetStats(1);
      gStyle->SetOptStat(10);
      gStyle->SetOptFit(111);
      gStyle->SetStatH(0.13);
      hist->SetLineWidth(5);
      f1->SetLineColor(kGreen-3);
      hist->SetTitle(("Stn "+to_string(stn-1)+", Crystal "+to_string(xtal)+", Fixed Parameters;In Fill Time [#mus];Cluster Energy, E / Track Momentum, p").c_str());
      hist->GetYaxis()->SetRangeUser(0.99,1.01);
      hist->GetXaxis()->SetRangeUser(0,4.2*cycles);

      hist->Draw();
      hist->SetDirectory(output);

      if (save) {
		c1->SaveAs(("PlotsGoldList/"+h+"_FixLaser.png").c_str());
      }
      // Make some print outs
      cout<<xtal<<","<<N<<","<<chiSqrNDF<<","<<tau<<","<<tau_err<<","<<A<<","<<A_err<<endl;
      // Delete the canvas
      delete c1;
    }
  }
  // Print out the number of xtals that pass quality cuts
  cout << "\nSurviving xtals: " << counter << endl;

  // Write and close input/output
  output->Write();
  output->Close();
  input1->Close();
  input2->Close();

  cout << "Created: " << outputFname << endl;
  return 0; 
}



