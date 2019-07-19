// Plotting code for gain par per xtal scatter plots 
// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAttMarker.h"

using namespace std;

// Function for drawing the plots
void draw(TH1D *hist1, TH1D *hist2, string title, string fname) {

  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist1->SetStats(0);
  hist1->SetMinimum(0);
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kGreen+2);
  hist1->SetLineWidth(3);
  hist2->SetLineWidth(3);
  hist1->Draw();
  hist2->Draw("same");
  c->BuildLegend(0.79,0.79,0.89,0.89);
  hist1->SetTitle(title.c_str());
  gPad->SetGridx();
  c->SaveAs(fname.c_str());
  delete c;

  return;
}

int main() {

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  string title[4] = {"Calo 13 | Recovery Times;Crystal Number;#tau [#mus]","Calo 19 | Recovery Times;Crystal Number;#tau [#mus]","Calo 13 | Amplitudes;Crystal Number;A","Calo 19 | Amplitudes;Crystal Number;A"};

  string laser_input = "RootFiles/LaserParameters.root";
  string Ep_input = "RootFiles/EpParameters_skip18_Q.root";
 
  
  string fname[4] = {"Plots/tau13_scat.png","Plots/tau19_scat.png","Plots/amp13_scat.png","Plots/amp19_scat.png"};
  TFile *laser = TFile::Open(laser_input.c_str());
  TFile *Ep = TFile::Open(Ep_input.c_str());
  // Get parameters 
  for (int ihist(0); ihist < 4; ihist++) {
    TH1D *laser_hist = (TH1D*)laser->Get(h[ihist].c_str());
    TH1D *Ep_hist = (TH1D*)Ep->Get(h[ihist].c_str());
    laser_hist->SetTitle("Laser");
    Ep_hist->SetTitle("E/p Ratio");
    draw(laser_hist,Ep_hist,title[ihist],fname[ihist]);
  }
  return 0;
}
