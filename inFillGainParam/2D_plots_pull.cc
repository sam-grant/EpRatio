// Generate 2D plots

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


void xtalIndex(TFile *file, TH2D *hist, string name, string title, string fname) {

  double weight;
  TH1D *h = (TH1D*)file->Get(name.c_str());
  for( int x = 0 ; x < 9 ; x++ ) {
    for( int y = 0 ; y < 6 ; y++) {
      int xtal = x+9*y;
      //cout << xtal <<" " <<x<<" "<<y<<endl;
      weight=h->GetBinContent(xtal+1);
      hist->Fill(x,y,weight);
    }
  }

  TCanvas *c1 = new TCanvas();
  // gStyle->SetPalette(55);//
  hist->SetStats(0);
  hist->SetTitle(title.c_str());
  hist->Draw("COLZ");
  // hist->Draw("text same");
  c1->SaveAs(fname.c_str());
  delete c1;
  return;

}

int main() {

  //All inputs
  TFile *pull = TFile::Open("stat_pull.root");
 
  TFile *output = new TFile("2D_pull.root","RECREATE");

  TH2D *tau13 = new TH2D("tau_13","",9,0,9,6,0,6);
  TH2D *tau19 = new TH2D("tau_19","",9,0,9,6,0,6);
  TH2D *amp13 = new TH2D("amp_13","",9,0,9,6,0,6);
  TH2D *amp19 = new TH2D("amp_19","",9,0,9,6,0,6);

  xtalIndex(pull,tau13,"pull_tau_13","Calo 13 | Recovery Time Comparison;Crystal Index X;Crystal Index Y","St13_tau_pull_2d.png");
  xtalIndex(pull,tau19,"pull_tau_19","Calo 19 | Recovery Time Comparison;Crystal Index X;Crystal Index Y","St19_tau_pull_2d.png");
  xtalIndex(pull,amp13,"pull_amp_13","Calo 13 | Amplitude Comparison;Crystal Index X;Crystal Index Y","St13_amp_pull_2d.png");
  xtalIndex(pull,amp19,"pull_amp_19","Calo 19 | Amplitude Comparison;Crystal Index X;Crystal Index Y","St19_amp_pull_2d.png");
  

  return 0;
}
