///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit a Landau convoluted with a gaussian to E/p time slices, and plot the maximum versus time

#ifndef FitLanGausSlices_h
#define FitLanGausSlices_h

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
#include "TMath.h"

using namespace std;

// This bit is not my code, convolution of landau and a gaussian
double langaufun(double *x, double *par) {

  //Fit parameters:
  //par[0]=Width (scale) parameter of Landau density
  //par[1]=Most Probable (MP, location) parameter of Landau density
  //par[2]=Total area (integral -inf to inf, normalization constant)
  //par[3]=Width (sigma) of convoluted Gaussian function
  //
  //In the Landau distribution (represented by the CERNLIB approximation),
  //the maximum is located at x=-0.22278298 with the location parameter=0.
  //This shift is corrected within this function, so that the actual
  //maximum is identical to the MP parameter.

  // Numeric constants
  double invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  double mpshift  = -0.22278298;       // Landau maximum location

  // Control constants
  double np = 1000.0;      // number of convolution steps
  double sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

  // Variables
  double xx;
  double mpc;
  double fland;
  double sum = 0.0;
  double xlow,xupp;
  double step;
  double i;

  // MP shift correction
  mpc = par[1] - mpshift * par[0];

  // Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];

  step = (xupp-xlow) / np;

  // Convolution integral of Landau and Gaussian by sum
  for(i=1.0; i<=np/2; i++) {
    xx = xlow + (i-.5) * step;
    fland = TMath::Landau(-xx,-mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);

    xx = xupp - (i-.5) * step;
    fland = TMath::Landau(-xx,-mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
  }

  return (par[2] * step * sum * invsq2pi / par[3]);
}




void FitLanGausSlices(TH2D *hist, string profileName, string langausName, string dir1, string dir2, TFile *output) {


  //Clone input to be safe 
  TH2D *hist_clone = (TH2D*)hist->Clone("hist_clone");
  //Get number of bins
  int nBins = hist_clone->GetNbinsX();
   // Set number of slices. You can hardcode this to change the number of slices
  int nSlices = nBins;
  // Get the length of the slice in x
  int length = nBins / nSlices;
  hist_clone -> RebinX(length);
  // Declare step edges
  int loStep;
  int hiStep;
  // Book a 1D hist for the Y projection slices
  // TH1D *projY;
  // Book a 1D hist to take the results of each fit on it's X axis
  TH1D *projX = hist_clone -> ProjectionX("prX");
  // Threshold (minimum number of bins), to define the fit range
  double threshold;
  double fitMin;
  double fitMax;
  double binCentre;
  double centre;

  // Slice loop
  for(int i = 0 ; i < nSlices; i++) {

    // Do we need a TCanvas?    
    TCanvas *c1 = new TCanvas();
    // Define steps
    loStep = i+1;
    hiStep = i+1;
    // Perform projection
    TH1D *projY = hist_clone->ProjectionY("prY",loStep,hiStep);
    // Clean up low bins 
    if (projY->GetEntries() < 1) continue;
    //Define the threshold at half maximum to avoid those tails.
    double maximum =  (projY -> GetBinContent(projY->GetMaximumBin()));// * (2/3);
    // = threshold*0.33;
    // Define a tight fit range to avoid poorly defined tails
    fitMin = projY -> GetBinCenter(projY -> FindFirstBinAbove(maximum*.50,1));
    fitMax = projY -> GetBinCenter(projY -> FindLastBinAbove(maximum*.50,1));
    
    // "Q" : supress printing "M" use minuit to improve fit result, "R" fit over range
    TF1 *lgFunc = new TF1("lgFunc",langaufun, fitMin, fitMax, 4);
   
    // Set starting params
    lgFunc->SetParameters(0.01, 0.975, projY->Integral()/5e6, 0.05);
    // Some empirical limits
    // limits on width
    lgFunc->SetParLimits(0, 0.001, 0.1);
    // limits on MP
    lgFunc->SetParLimits(1, 0.95, 1.0);
    // limits on GSigma
    lgFunc->SetParLimits(3, 0.03, 0.05); 

    lgFunc->SetParNames("Width","MP","Area","GSigma");

    // Global style settings
    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);

    // Get half decent intial parameters from single gaussian
    projY->Fit(lgFunc,"QMR");// ,"",fitMin,fitMax);

    if(i==0) {
      projX -> SetBinContent(i+1, 0);
      projX -> SetBinError(i+1, 0);

    } else {
      projX -> SetBinContent(i+1, lgFunc->GetParameter(1));
      projX -> SetBinError(i+1, lgFunc->GetParError(1));
  
      // std::cout<<lgFunc->GetParameter(1)<<" +/- "<<lgFunc->GetParError(1)<<std::endl;
      // std::cout<<lgFunc->GetChisquare() / lgFunc->GetNDF()<<std::endl;

      // std::cout<<projY->Integral()<<std::endl;
      // std::cout<<lgFunc->GetParameter(3)<<std::endl;
      // std::cout<<projY->Integral()/lgFunc->GetParameter(3)<<std::endl;
    }

    // Draw with the gaussians
    projY->Draw();
    lgFunc->Draw("lsame");

    bool plotFit = false;

    projY->GetXaxis()->SetRangeUser(0.5,1.5);
    projY->SetName((langausName+"_"+to_string(i)).c_str());
    output->cd(dir1.c_str());
    projY->SetDirectory(gDirectory);
    // gFunc1->SetDirectory(gDirectory);
    // gFuncA->SetDirectory(gDirectory);
    // gFuncB->SetDirectory(gDirectory);
    //c1->SaveAs("../../images/lgfunc.png");

    delete c1;
    //delete lgFunc;
    
  } // End slice loop

  delete hist_clone;
  //Force the ranges to be sensible if ROOT's autoscale fails
  int binmin = projX->FindFirstBinAbove(0,1);
  int binmax = projX->FindLastBinAbove(0,1);
  // Set name...
  projX->SetName(profileName.c_str());
  // Plot means 
  TCanvas *c2 = new TCanvas();//"c2", "c2", 3000, 2000);

  // Draw and save
  projX->DrawCopy();
  output->cd(dir2.c_str());
  projX->SetDirectory(gDirectory);

  delete c2;
  return;
}

#endif
