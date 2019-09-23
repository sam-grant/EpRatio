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

using namespace std;
// Function for drawing the plots
void draw(TH1D *hist1, TH1D *hist2, string title, string fname) {
  
  TCanvas *c = new TCanvas();//"","",3000,2000);
  TLegend *leg = new TLegend(0.76,0.76,0.89,0.89);
  leg->SetBorderSize(0);
  hist1->SetStats(0);
  hist2->SetStats(0);
  hist1->SetLineColor(kGreen-3);
  hist2->SetLineColor(kRed);
  hist1->SetLineWidth(5);
  hist2->SetLineWidth(5);
  hist1->GetXaxis()->CenterTitle(true);
  hist1->GetYaxis()->CenterTitle(true);
  hist1->SetTitleSize(.75);
  hist1->GetXaxis()->SetTitleSize(.05);
  hist1->GetYaxis()->SetTitleSize(.05);
  hist1->GetYaxis()->SetTitleOffset(1.0);
  hist1->GetXaxis()->SetTitleOffset(0.8);
  
  leg->AddEntry(hist1);
  leg->AddEntry(hist2);
  hist1->Draw();
  hist2->Draw("same");
  leg->Draw("same");
  // c->BuildLegend(0.79,0.79,0.89,0.89);
  hist1->SetTitle(title.c_str());
  gPad->SetGridx();
  c->SaveAs(fname.c_str());
  delete c;

  return;
}

int main() {
  
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  //  string title[4] = {"St 12 | Recovery Times;Crystal Number;#tau_{r} [#mus]","St 18 | Recovery Times;Crystal Number;#tau_{r} [#mus]","St 12 | Amplitudes;Crystal Number;#alpha","St 18 | Amplitudes;Crystal Number;#alpha"};
  string title[4] = {"Station 12;Crystal;#tau_{r} [#mus]","Station 18;Crystal;#tau_{r} [#mus]","Station 12;Crystal;#alpha","Station 18;Crystal;#alpha"};
  string laser_input = "../ReadNTuples/RootFiles/ifg_9day.root";
  string Ep_input = "RootFiles/EpParameters_9day_Q.root";
  string fname[4] = {"Plots_9day/St13ScatterTau.pdf","Plots_9day/St19ScatterTau.pdf","Plots_9day/St13ScatterAmp.pdf","Plots_9day/St19ScatterAmp.pdf"};
  TFile *laser = TFile::Open(laser_input.c_str());
  TFile *Ep = TFile::Open(Ep_input.c_str());
  // Get parameters 
  for (int ihist(0); ihist < 4; ihist++) {
    TH1D *laser_hist = (TH1D*)laser->Get(h[ihist].c_str());
    TH1D *Ep_hist = (TH1D*)Ep->Get(h[ihist].c_str());
    laser_hist->SetTitle("Laser");
    Ep_hist->SetTitle("E/p");
    if(ihist==0) laser_hist->GetYaxis()->SetRangeUser(2,13);
    if(ihist==1) laser_hist->GetYaxis()->SetRangeUser(2,13);
    if(ihist==2) laser_hist->GetYaxis()->SetRangeUser(0,0.08);
    if(ihist==3) laser_hist->GetYaxis()->SetRangeUser(0,0.03);
    draw(laser_hist,Ep_hist,title[ihist],fname[ihist]);
  }
  
  return 0;
  
}
