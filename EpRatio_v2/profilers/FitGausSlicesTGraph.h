///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit a single gaussain to E/p time slices, and plot the maximum versus time
// -----------------
// Sam Grant, April 2019 
// samuel.grant.18@ucl.ac.uk
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// TODO: USE TGRAPH ERRORS INSTEAD OF TH1D
//

#ifndef FitGausSlicesTGraphs_h
#define FitGausSlicesTGraph_h

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
#include "TGraphErrors.h"

using namespace std;

void FitGausSlicesTGraph(TH2D *hist, string profileName, string gaussName, string dir1, string dir2, TFile *output) {
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
  // Containers for TGraph
/*  std::vector<double> x;
  std::vector<double> ex;
  std::vector<double> y;
  std::vector<double> ey;*/
  double x[nSlices];
  double ex[nSlices];
  double y[nSlices];
  double ey[nSlices];
  /*  TGraphErrors *tgr; */
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
    // Do we need a TCanvas?    
    TCanvas *c1 = new TCanvas();
    // Define steps
    loStep = i+1;
    hiStep = i+1;
    // Perform projection
    projY = hist_clone->ProjectionY("prY",loStep,hiStep);
    // Clean up low bins 
    if (projY->GetEntries() < 1) continue;
    //Define the threshold at half maximum to avoid those tails.
    double maximum =  (projY -> GetBinContent(projY->GetMaximumBin()));// * (2/3);
    maximum = maximum * 0.5;
    // Define the fit range
    fitMin = projY -> GetBinCenter(projY -> FindFirstBinAbove(maximum,1));
    fitMax = projY -> GetBinCenter(projY -> FindLastBinAbove(maximum,1));
    // "Q" : supress printing "M" use minuit to improve fit result, "R" fit over range

    //projY -> Fit(gFunc,"RM","",fitMin,fitMax);
    //good initial guesses
/*    gFunc->SetParameter(0, projY->GetMaximum());
    gFunc->SetParameter(1, 0.96);  
    gFunc->SetParameter(2, 0.05);*/

    // Get half decent intial parameters from single gaussian
    projY -> Fit(gFunc,"QRM","",fitMin,fitMax);
    //std::cout << "fitted initial gaussian...\n\n";
    ex[i] = 0; 
    x[i] = projX->GetBinCenter(i+1);//push_back(projX->GetBinCenter(i+1));
    if(i==0) {
/*      y.push_back(0);
      ey.push_back(0);*/
      y[i] = 0;
      ey[i] = 0;
/*      projX -> SetBinContent(i+1, 0);
      projX -> SetBinError(i+1, 0);
*/
    } else {
      y[i] = gFunc->GetParameter(1);
      ey[i] = gFunc->GetParError(1);
/*      y.push_backgFunc->GetParameter(1)(gFunc->GetParameter(1));
      ey.push_back(gFunc->GetParError(1));*/

/*      projX -> SetBinContent(i+1, gFunc->GetParameter(1));
      projX -> SetBinError(i+1, gFunc->GetParError(1));*/
    }

    // std::cout<<gFunc->GetParameter(1)<<std::endl;

    // Draw and save
    projY->Draw();
    projY->GetXaxis()->SetRangeUser(0.5,1.5);
    projY->SetName((gaussName+"_"+to_string(i)).c_str());
    output->cd(dir1.c_str());
    projY->SetDirectory(gDirectory);

    delete c1;
    
  } // End slice loop

  delete hist_clone;
  //Force the ranges to be sensible if ROOT's autoscale fails

/*  auto*/
  TGraphErrors *gr = new TGraphErrors(nSlices,x,y,ex,ey);
/*  nt binmin = projX->FindFirstBinAbove(0,1);
  int binmax = projX->FindLastBinAbove(0,1);*/
  // Set name...
  gr->SetName(profileName.c_str());
  // Plot means 
  TCanvas *c2 = new TCanvas();//"c2", "c2", 3000, 2000);

  // Draw and save
  gr->Draw("AP");
  output->cd(dir2.c_str());
  gr->Write();
  /*gr->SetDirectory(gDirectory);*/
  delete c2;
  return;
}

#endif
