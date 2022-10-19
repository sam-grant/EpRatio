///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Fit a single gaussain to E/p time slices, and plot the maximum versus time
// -----------------
// Sam Grant, March 2020 
// samuel.grant.18@ucl.ac.uk
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
// BEING MODIFIED TO USE A DOUBLE GAUSSIAN
//

#ifndef FitDoubleGausSlices_h
#define FitDoubleGausSlices_h

#include <iostream>
#include <math.h>

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

// More complicated that I thought

double UncertaintyAtMax(TF1 *fit) { 

  // First gaussian
  double a1 = fit->GetParameter(0);
  std::cout<<"a1\t"<<a1<<std::endl;
  double a1_e = fit->GetParError(0);
  std::cout<<"a1_e\t"<<a1_e<<std::endl;
  double b1 = fit->GetParameter(1);
  std::cout<<"b1\t"<<a1<<std::endl;
  double b1_e = fit->GetParError(1);
  std::cout<<"b1_e\t"<<a1_e<<std::endl;
  double c1 = fit->GetParameter(2);
  std::cout<<"c1\t"<<c1<<std::endl;
  double c1_e = fit->GetParError(2);
  std::cout<<"c1_e\t"<<c1_e<<std::endl;

  // Second gaussian
  double a2 = fit->GetParameter(3);
  std::cout<<"a2\t"<<a2<<std::endl;
  double a2_e = fit->GetParError(3);
  std::cout<<"a2_e\t"<<a2_e<<std::endl;
  double b2 = fit->GetParameter(4);
  std::cout<<"b2\t"<<b2<<std::endl;
  double b2_e = fit->GetParError(4);
  std::cout<<"b2_e\t"<<b2_e<<std::endl;
  double c2 = fit->GetParameter(5);
  std::cout<<"c2\t"<<c2<<std::endl;
  double c2_e = fit->GetParError(5);
  std::cout<<"c2_e\t"<<c2_e<<std::endl;

  // x value at function max 
  double xmax = fit->GetX(fit->GetMaximum());//fit->Eval(0, fit->GetMaximum(), 0);
  std::cout<<"xmax\t"<<xmax<<std::endl;
  std::cout<<"test\t"<<exp(-pow((-b1+xmax),2))<<std::endl;
  // Six terms, do them individually
  double t1 = exp(-pow((-b1+xmax),2)/pow(c1,2)) * pow(a1_e,2);
  std::cout<<"t1\t"<<t1<<std::endl;
  double t2 = exp(-pow((-b2+xmax),2)/pow(c2,2)) * pow(a2_e,2);
  std::cout<<"t2\t"<<t2<<std::endl;
  double t3 = pow(a1,2) * exp(-pow((-b1+xmax),2)/pow(c1,2)) * pow((-b1+xmax),2) * pow(b1_e, 2) * (1/pow(c1,4));
  std::cout<<"t3\t"<<t2<<std::endl;
  double t4 = pow(a2,2) * exp(-pow((-b2+xmax),2)/pow(c2,2)) * pow((-b2+xmax),2) * pow(b2_e, 2) * (1/pow(c2,4));
  std::cout<<"t4\t"<<t2<<std::endl;
  double t5 = pow(a1,2) * exp(-pow((-b1+xmax),2)/pow(c1,2)) * pow((-b1+xmax),4) * pow(c1_e, 2) * (1/pow(c1,6));
  std::cout<<"t5\t"<<t2<<std::endl;
  double t6 = pow(a2,2) * exp(-pow((-b2+xmax),2)/pow(c2,2)) * pow((-b2+xmax),4) * pow(c2_e, 2) * (1/pow(c2,6));
  std::cout<<"t6\t"<<t2<<std::endl;

  double y_err = sqrt(t1 + t2 + t3 + t4 + t5 + t6); // Gives the uncertainty on y at not xmax

  //double y_lo = fit->GetMaximum() - y_err;
  //double y_hi = fit->GetMaximum() + y_err;

  std::cout<<fit->GetMaximum()-y_err<<std::endl;


  // Does this make sense?
  double x_err = abs(xmax - fit->GetX(fit->GetMaximum()-y_err));
  //double x_err_hi = fit->GetX(y_hi);

  //if(x_err_lo != x_err_hi) std::cout<<"SOMETHING WEIRD"<<std::endl;
  std::cout<<x_err<<std::endl;
  return x_err;
}


void FitDoubleGausSlices(TH2D *hist, string profileName, string gaussName, string dir1, string dir2, TFile *output) {
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
  TF1 *gFunc = new TF1("gFunc", "gaus"); // Placeholder, the way I was originally fitting
  TF1 *gFuncA = new TF1("gFuncA", "gaus"); // So that I can draw the first gaussian
  TF1 *gFuncB = new TF1("gFuncB", "gaus"); // So that I can draw the second gaussian 
  TF1* gFunc1 = new TF1("gFunc1", "[0] * exp( -1 * ((x - [1])^2 / (2*[2]^2)) )"); // First gaussian
  TF1* gFunc2 = new TF1("gFunc2", "[0] * exp( -1 * ((x - [1])^2 / (2*[2]^2)) ) + [3] * exp( -1 * ((x - [4])^2 / (2*[5]^2)) )"); // Convoluted gaussian

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
    //good initial guesses for EG
    gFunc1->SetParameter(0, projY->GetMaximum());
    gFunc1->SetParameter(1, 0.96);  
    gFunc1->SetParameter(2, 0.05);

    // Get half decent intial parameters from single gaussian
    projY -> Fit(gFunc1,"QRM","",fitMin,fitMax);
    //std::cout << "fitted initial gaussian...\n\n";

    // starting from single gaussian, add another
    gFunc2->SetParameter(0, gFunc1->GetParameter(0) / 2.0);
    gFunc2->SetParameter(1, gFunc1->GetParameter(1) * 0.9);  
    gFunc2->SetParameter(2, gFunc1->GetParameter(2));
    gFunc2->SetParameter(3, gFunc1->GetParameter(0) / 2.0);
    gFunc2->SetParameter(4, gFunc1->GetParameter(1) * 1.1); 
    gFunc2->SetParameter(5, 0.02);

    // TESTING NEW PARAMS
    //gFunc2->SetParameter(3, gFunc1->GetParameter(0) / 2.0);
    //gFunc2->SetParameter(4, gFunc1->GetParameter(1) * 1.1); 
    //gFunc2->SetParameter(5, 0.05);
    
    gFunc2->SetParLimits(5, 0, 10.0);

    // Fit the double gaussian
    projY -> Fit(gFunc2,"QRM","",fitMin,fitMax);

    //updated to use double gaussian
    //To do - work out mean from 2 gaussians, and error
    projX -> SetBinContent(i+1, gFunc2->GetX(gFunc2->GetMaximum()));

    // Set a placeholder error of 1%
    projX -> SetBinError(i+1, UncertaintyAtMax(gFunc2));

    // Draw with the gaussians
    projY->Draw();

    bool plotFit = false;

    if (plotFit) {

      // original single gaussian fit
      gFunc1->SetLineColor(3);
      gFunc1->SetRange(fitMin, fitMax);
      gFunc1->Draw("SAME");

      //one of the gaussians
      gFuncA->FixParameter(0, gFunc2->GetParameter(0));
      gFuncA->FixParameter(1, gFunc2->GetParameter(1));  
      gFuncA->FixParameter(2, gFunc2->GetParameter(2));
      gFuncA->SetRange(fitMin, fitMax);
      gFuncA->SetLineColor(4);
      gFuncA->Draw("SAME");
      
      //the other gaussian
      gFuncB->FixParameter(0, gFunc2->GetParameter(3));
      gFuncB->FixParameter(1, gFunc2->GetParameter(4));  
      gFuncB->FixParameter(2, gFunc2->GetParameter(5));
      gFuncB->SetRange(fitMin, fitMax);
      gFuncB->SetLineColor(6);
      gFuncB->Draw("SAME");
      
      c1->SaveAs("../../images/tmp.C");

      std::cout << "max in range: " <<  gFunc2->GetMaximum(fitMin, fitMax) << " " << projX->GetBinContent(i+1) << "\n";

      if (true) exit(0);
    }
    projY->GetXaxis()->SetRangeUser(0.5,1.5);
    projY->SetName((gaussName+"_"+to_string(i)).c_str());
    output->cd(dir1.c_str());
    projY->SetDirectory(gDirectory);
    // gFunc1->SetDirectory(gDirectory);
    // gFuncA->SetDirectory(gDirectory);
    // gFuncB->SetDirectory(gDirectory);

    delete c1;
    
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
