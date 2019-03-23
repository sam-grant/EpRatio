//#include "MyRootStuff.h"
//using namespace MyRootStuff;
#include <iostream>
#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TList.h"
//#include "TMath.h"

using std::cout;
using std::endl;

int reBin = 2;



//Function must have two parameters
//1. Double_t *v: a pointer to the variables array. This array must be a 1-dim array with v[0] = x in case of a 1-dim histogram, v[0] =x, v[1] = y for a 2-dim histogram, etc. 
//2. Double_t *par: a pointer to the parameters array. par will contain the current values of parameters when it is called by the FCN function. 
//Condition for exclusion of fit


//Global variable for number of parameters in fit

 int N_par = 5;
 Bool_t reject;

Double_t fline(Double_t *v, Double_t *par) {
  //     if (reject && v[0] > -2.5 && v[0] < 2.5) {
  if (reject &&  v[0] < 0.5) {
    TF1::RejectPoint();
    return 0;
  }
  return par[0]*TMath::Exp(v[0]*par[1]) * (1+par[2]*TMath::Sin(par[3]*v[0]+par[4]));
 }


void fit(TString plotname) {

  bool toy = false;
  
  TH1 *plot;
  if(toy) {
    //read toy:
    TFile *out = new TFile("toy_plots.root", "READ");
    plot = (TH1*)out->Get("toy");
    plot->SetDirectory(0);
    out->Close();
  }
  else {
    //read data:
    TFile *out = new TFile("plots.root", "READ");
    // plot = (TH1*)out->Get("time_diff_55_55_p01");
    plot = (TH1*)out->Get(plotname);
    plot->SetDirectory(0);
    out->Close();
  }
  
  
  //normalise the plot:
  plot->Scale( 1./plot->Integral() );
  plot->SetStats(0);
  //Excluded fit
  //  TF1 *fit1 = new TF1("fit1",fline,-10,20,N_par);
  TF1 *fit1 = new TF1("fit1",fline,0,20,N_par);

  if(toy) {
    //With these parameters you can get quite close
    fit1->SetParLimits(0, 0.0002, 0.1);
    fit1->SetParLimits(1, -0.01, -0.001);
    fit1->SetParLimits(2, 0.002, 0.1); //expect ~ 0.003
    fit1->SetParLimits(3, 1.2, 1.8); //expect ~1.44

  }
  
  else { 
    //With these parameters you can get quite close
    fit1->SetParLimits(0, 0.0002, 0.0005);
    fit1->SetParLimits(1,  -0.02, -0.01);
    fit1->SetParLimits(2, 0.002, 0.1); //expect ~ 0.003
    fit1->SetParLimits(3, 1.2, 1.8); //expect ~1.44
    //    fit1->SetParLimits(4, 1, 1.5); //expect ~1.15
  }
  
  reject = kTRUE;
  //do not plot result of fit
  plot->Fit(fit1,"RN");//,"0");

  
  //plot result of fit
  reject = kFALSE; 
  fit1->SetLineColor(kBlue);
  fit1->SetLineWidth(2);

  
  // Create a canvas, divide into three windows, 
  TCanvas *c1 = new TCanvas("c1", "Canvas 1");
  gPad->SetGrid();
  // Plot
  // c1->cd(1);
  //  plot->SetTitle("Excluded Wiggle Fit Between -1.0<x<1.0    #mus;Track Time i - Track Time j (#mus);Normalised Frequency");
  // plot->DrawCopy();
  //fit1->Draw("SAME");

  plot->SetAxisRange(0, 20, "X");
  plot->SetTitle(";Track Time i - Track Time j [#mus]; unit normalised");
  plot->DrawCopy();
  c1->Print("figures/fit_data_"+plotname+".pdf");
  
  fit1->Draw("SAME");
  if(toy) c1->Print("figures/fit_exclude.pdf");
  else c1->Print("figures/fit_"+plotname+".pdf");
 
  plot->SetAxisRange(0, 2, "X");
  // if(!toy) plot->SetAxisRange(0.0002*reBin, 0.000212*reBin, "Y");
  plot->SetTitle(";Track Time i - Track Time j [#mus] ; unit normalised");
  plot->SetTitleOffset(1.5,"Y");

  
  plot->DrawCopy();
  c1->Print("figures/fit_data_zoom_"+plotname+".pdf");
  fit1->Draw("SAME");

  if(toy) c1->Print("figures/fit_exclude_zoom_toy.pdf");
  else c1->Print("figures/fit_zoom_"+plotname+".pdf");


  return;
}




int main() {

  fit("time_diff_55_55_p01");
  fit("time_diff_60_60_p01");

  fit("time_diff_55_55_p1");
  fit("time_diff_60_60_p1");

  return 1;
}
