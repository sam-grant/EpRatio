// Very very simple code just to see how the gain sag function works
// Sam Grant - April 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TCanvas.h"
#include "TAxis.h"

using namespace std;

double gain_sag(double *x, double *par) {
  
  double time = x[0];
  double N0 = 1; // Overall normalisation
  double p0 = 0.5; // Amplitude of the sag;
  double tau_mu = 12; // Time constant of the rising exponential
  double tau_r = 10; // Time constant for the fall exponetial

  double N  = N0 * ( 1 - p0 * ( exp( - time / tau_mu ) - exp( - time / tau_r ) ) );
  return N;
  
}

double falling(double *x, double *par) {
  
  double time = x[0];
  double N0 = 1; // Overall normalisation
  double p0 = 0.5; // Amplitude of the sag;
  double tau_mu = 12; // Time constant of the rising exponential
  double tau_r = 10; // Time constant for the fall exponetial

  double N  = N0 * ( 1 - p0 * (  - exp( - time / tau_r ) ) );
  return N;
  
}

double rising(double *x, double *par) {
  
  double time = x[0];
  double N0 = 1; // Overall normalisation
  double p0 = 0.5; // Amplitude of the sag;
  double tau_mu = 12; // Time constant of the rising exponential
  double tau_r = 10; // Time constant for the fall exponetial

  double N  = N0 * ( 1 - p0 * ( exp( - time / tau_mu ) ) );
  return N;
  
}

int main() {

  // Book function over 50 g-2 cycles
  int earlyTime = 210; 
  TF1 *f1 = new TF1("f1", gain_sag, 0, earlyTime);
   TF1 *f2 = new TF1("f1", falling, 0, earlyTime);
    TF1 *f3 = new TF1("f1", rising, 0, earlyTime);
  f1 -> SetNpx(5000);
  f2->SetNpx(5000);
  f3->SetNpx(5000);
  // Draw it and save
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
    f1->SetTitle("Gain Sag Function;Absolute Time [#mus];E/p");
    f1->GetYaxis()->SetRangeUser(0.4,1.6);
    f2->SetLineColor(kBlue);
    f3->SetLineColor(kGreen);
  f1->Draw();
  f2->Draw("same");
  f3->Draw("same");

  c1->SaveAs("gain_sag.png");

  delete c1;
  delete f1;
  return 0;
  
}
  
