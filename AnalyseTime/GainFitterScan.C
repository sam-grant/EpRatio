// Scan over fit ranges and find plot the uncertainties on fit parameters
// Sam Grant April-June 2019
// samuel.grant.18@ucl.ac.uk
// April-June 2019

#include <iostream>
//#include <vector>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TAttMarker.h"
#include "TLine.h"

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

void draw(vector<TH1D *> hist_, string fname, int stn, int par, int err, bool save) {

  string calo, para, axes;
  string us = "";

  if(stn == 13) calo = "Stn 12";
  else calo = "Stn 18";
  if(par == 0 && err == 0) {
    para = " #alpha";
  }
  else if(par == 0 && err == 1) {
    para = " #delta#alpha";
     }
  else if(par == 1 && err == 0) {
    para = " #tau_{r}";
    us  = " [#mus]";
  }
  else if(par == 1 && err == 1) {
    para = " #delta#tau_{r}";
    us  = " [#mus]";
  }
  axes = ";Fit End Time [#mus];"+para+us;
  gStyle->SetPalette(kRainBow);
  int nColors = gStyle->GetNumberOfColors();
  int nHistos = hist_.size();;
  //cout<<hist_.size()<<endl;
  TCanvas *c = new TCanvas("c","c",3000,2000);
  TLegend *leg = new TLegend(0.92,0.11,0.98,0.89);
  leg->SetBorderSize(0);
  double x1, x2, y1, y2;
  x1 = 4.2*23;
  x2 = x1;

  for(int i(0); i<hist_.size(); i++) {

    if (hist_.at(i) -> GetEntries() == 0) continue;
    if(par == 0 && err == 0 && stn == 13) {
      y1 = 0.0;
      y2 = 0.04;
    }
    if(par == 0 && err == 1 && stn == 13) {
           y1 = 0.0;
       y2 = 0.018;
    }
    if(par == 1 && err == 0 && stn == 13) {
          y1 = 4.0;
       y2 = 13.0;
    }
    if(par == 1 && err == 1 && stn == 13) {
           y1 = 0.0;
       y2 = 13.0;
    }
    if(par == 0 && err == 0 && stn == 19) {
          y1 = 0.004;
       y2 = 0.015;
    }
    if(par == 0 && err == 1 && stn == 19) {
       y1 = 0.0;
       y2 = 0.008;
    }
    if(par == 1 && err == 0 && stn == 19) {
       y1 = 4.0;
       y2 = 15.0;
    }
    if(par == 1 && err == 1 && stn == 19) {
       y1 = 1.5;
       y2 = 8.0;
    }

    //    TLine l(4.2*23,y1,4.2*23,y2);
    double range = 4.2*23;
    TLine *l = new TLine(range,y1,range,y2);//80, 0, 80, 100);
    hist_.at(i)->GetYaxis()->SetRangeUser(y1,y2);
    hist_.at(i)->SetStats(0);
    hist_.at(i)->SetLineWidth(0);
    hist_.at(i)->SetMarkerSize(5);
    hist_.at(i)->SetMarkerStyle(20);//kStar);
    int histoColor = (float)nColors / hist_.size() * i;
    hist_.at(i)->SetMarkerColor(gStyle->GetColorPalette(histoColor));
    if(i==0) hist_.at(i)->Draw("P");
    hist_.at(i)->Draw("P SAME");
    l->SetLineWidth(5);
    l->SetLineStyle(2);
    l->Draw("same");
    leg->AddEntry(hist_.at(i));
    hist_.at(i)->SetTitle((calo+axes).c_str());
   }
  c->Draw();
  leg->Draw();
  if(save) c->SaveAs(("Plots/"+fname+".png").c_str());
  
  delete c;
  delete leg;
  return;
}
  
int main() {
  //  string suffix = "_skip18";
  string suffix = "";
  // Define number of g-2 cycles to use 
  int cycles = 50;
  // To save plots to png then save = true  
  bool save = true;
  // Open input ROOT file
  string input_fname = "RootFiles/plots_timeXtalLong"+suffix+".root";
  TFile *input = TFile::Open(input_fname.c_str());
  cout << "Reading ... " << input_fname << endl;

  for(int iErr(0); iErr<2; iErr++) {    
  //  // Book output ROOT file
     // Station loop
    for (int stn(13); stn < 20; stn = stn + 6) {
      vector<TH1D *> scanVecA_;
      vector<TH1D *> scanVecTau_;	   
      string nameA, nameTau;
      // Crystal loop
       for (int xtal(0); xtal < 54; xtal++) {
	nameA = "Crystal "+to_string(xtal);
	nameTau = nameA;
	// Start at 2x 4.2
	TH1D *scanA = new TH1D("",nameA.c_str(),48,1.5*4.2,49.5*4.2);
	TH1D *scanTau = new TH1D("",nameTau.c_str(),48,1.5*4.2,49.5*4.2);
	// Get 
	string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
	TH1D *hist = (TH1D*)input->Get(h.c_str());
	// Skip empty ones
	if(hist == 0) continue;
	// Start at twice the starting value and finish at the max
	for(int tscan(2); tscan<hist->GetNbinsX(); tscan++) {
	  // Book output histogram
     	  // Book the gain sag function
	  TF1 *f1 = new TF1("f1", GainSag, 4.2, 4.2*tscan, 3);
  	  // Set a starting time constant, expectation from laser is ~5 us
	  f1->SetParameter(2,5);
	  f1->SetParName(0,"G_{0}");
	  f1->SetParName(1,"A");
	  f1->SetParName(2,"#tau_{r}");
	  // Perform fit, over range "R", suppress output "Q", use minuit "M"
	  hist->Fit(f1,"QMR");
	  // Get fit constants 
	  double N = hist->GetEntries();
	  double chiSqrNDF = f1->GetChisquare() / f1->GetNDF();
	  double A = f1->GetParameter(1);
	  double A_err = f1->GetParError(1);
	  double tau = f1->GetParameter(2);
	  double tau_err = f1->GetParError(2);
	  // Avoid low stats
	  if (N < 100000) continue;
	  // Require a reasonable reduced chi square
	  if( chiSqrNDF < 0.25 || chiSqrNDF > 4) continue;
	  // Require low error
	  if( tau_err > 0.5*tau || A_err > 0.5*A) continue;
	  if( isnan(tau_err) || isnan(A_err) ) continue;
	  // factor of 100 greater than they should be
	  if(tau > 100 || A > 1) continue;
	  if (iErr == 0) {
	    scanA->SetBinContent(tscan, A);//f1->GetParameter(par));
	    scanTau->SetBinContent(tscan, tau);//f1->GetParameter(par));
	  }
	  else if(iErr == 1) {
      	    scanA->SetBinContent(tscan, A_err);//f1->GetParameter(par));
	    scanTau->SetBinContent(tscan, tau_err);//f1->GetParameter(par));
	  }
     	  scanA->SetBinError(tscan, 0);//A_err);//f1->GetParError(par));
	  scanTau->SetBinError(tscan, 0);//tau_err);//f1->GetParError(par));
     	  scanA->SetName(("Xtal "+to_string(xtal)).c_str());
	  scanTau->SetName(("Xtal "+to_string(xtal)).c_str()); 
	} // fill loop
	scanVecA_.push_back(scanA);
	scanVecTau_.push_back(scanTau);

      } // xtal loop
       string unc;
       if(iErr == 1) unc = "Err";
       else unc = "";
      string fnameA = "St"+to_string(stn)+"AlphaFitEndPointScan"+unc;
      string fnameTau = "St"+to_string(stn)+"TauFitEndPointScan"+unc;
      draw(scanVecA_, fnameA, stn, 0, iErr, save);
      draw(scanVecTau_, fnameTau, stn, 1, iErr, save);
    }
  }
     input->Close();
    return 0; 
}



