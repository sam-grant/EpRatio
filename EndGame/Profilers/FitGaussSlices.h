////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// fitSlicesGauss.h
// -----------------
// Function to slice a 2D histogram along the x-axis bin by bin, project those slices in y, fit gaussians to each projection
// Output a 1D histogram of the gaussian means centred on the x bin centres of the original histogram. 
// Sam Grant, April 2019 
// samuel.grant.18@ucl.ac.uk
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FitGaussSlices_h
#define FitGaussSlices_h

#include <iostream>
#include "TH2D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TF1.h"
#include "TDirectory.h"

using namespace std;

void FitGaussSlices(TH2D *hist, string axes, TFile *output) {
  //Clone input to be safe 
  TH2D *hist_clone = (TH2D*)hist->Clone("hist_clone");
  //Get number of bins
  int nBins = hist_clone->GetNbinsX();
   // Set number of slices. You can hardcode this to change the number of slices
  int nSlices = nBins;
  // Get the length of the slice in x
  int length = nBins / nSlices;
  hist_clone -> RebinX(length);
  // Define the gaussian function
  TF1 *gFunc = new TF1("gFunc", "gaus");
  //  gFunc->SetLineWidth(5);
  // Declare step edges
  int loStep;
  int hiStep;
  // Book a 1D hist for the Y projection slices
  TH1D *projY;
  // Book a 1D hist to take the results of each fit on it's X axis
  TH1D *projX = hist_clone -> ProjectionX("prX");
  // Threshold (minimum number of bins), to define the fit range
  double threshold;
  double fitMin;
  double fitMax;
  double binCentre;
  double centre;
  // Slice loop
  //  cout<<"calo,xtal,Ep,dEp,dEp/Ep"<<endl;
  for(int i = 0 ; i < nSlices; i++) {
    // Fiducial region
    
    TCanvas *c1 = new TCanvas();//"c1","c1",3000,2000);
    // Define steps
    loStep = i+1;
    hiStep = i+1;
    // Perform projection
    projY = hist_clone->ProjectionY("prY",loStep,hiStep);
    // Clean up low bins 
    if (projY->GetEntries() < 1) continue;
    //Define the threshold at half maximum to avoid those tails.
    threshold =  (projY -> GetBinContent(projY->GetMaximumBin()));// * (2/3);
    threshold = threshold * 0.5;
    // Define the fit range
    fitMin = projY -> GetBinCenter(projY -> FindFirstBinAbove(threshold,1));
    fitMax = projY -> GetBinCenter(projY -> FindLastBinAbove(threshold,1));
    // "Q" : supress printing "M" use minuit to improve fit result, "R" fit over range
    projY -> Fit(gFunc,"RMQ","",fitMin,fitMax);
    // Fill a histogram with the fit results
    double value = gFunc->GetParameter(1);
    double error = gFunc->GetParError(1);
    //    if(error/value<0.05) {
      projX -> SetBinContent(i+1, value);
      projX -> SetBinError(i+1, error);
    // }
    // else {
    //   projX -> SetBinContent(i+1, 0);
    //   projX -> SetBinError(i+1, 0);
    // }
    gStyle->SetOptStat(2210);
    gStyle->SetOptFit(111);
    projY->SetTitle((";E/p;Entries").c_str());
    projY->SetMarkerColor(kBlack);
    projY->SetLineColor(kBlack);
    projY->Draw();
    projY->SetName((g_fname+"_"+to_string(i)).c_str());
    // projY->SetDirectory(output);
    //if (save) {
      //         c1->SaveAs(("Plots/"+g_fname+"_"+to_string(i)+".png").c_str());
    //}
    delete c1;
    //cout << i << " " <<  gFunc->GetParameter(1) << endl;
  } // End slice loop
  delete hist_clone;
  //Force the ranges to be sensible if ROOT's autoscale fails
  int binmin = projX->FindFirstBinAbove(0,1);
  int binmax = projX->FindLastBinAbove(0,1);
  // Set name...
  projX->SetName(fname.c_str());
  // Plot means 
  TCanvas *c2 = new TCanvas();//"c2", "c2", 3000, 2000);
  //  projX->SetStats(0);
  gStyle->SetOptStat(2210);
  //  projX->GetYaxis()->SetRangeUser(0.94,0.98);
  projX->SetTitle(axes.c_str());
  projX->SetMarkerColor(kBlack);
  projX->SetLineColor(kBlack);
  projX->GetXaxis()->CenterTitle(true);
  projX->GetYaxis()->CenterTitle(true);
  projX->SetTitleSize(.75);
  projX->GetXaxis()->SetTitleSize(.05);
  projX->GetYaxis()->SetTitleSize(.05);
  projX->GetYaxis()->SetTitleOffset(0.65);
  projX->GetXaxis()->SetTitleOffset(0.5);
  //  projX->SetLineWidth(5);
  projX->GetXaxis()->SetRange(binmin,binmax);
  //  projX->GetYaxis()->SetRangeUser(.75,1.05);
  //  gPad->SetGridy();
  projX->DrawCopy();
  //if (save) {
  //  c2->SaveAs(("Plots/"+fname+".png").c_str());
  // }
  // Save to ROOT file
  projX->SetDirectory(output);
  delete c2;

  output->Write();
  return;
}

#endif
