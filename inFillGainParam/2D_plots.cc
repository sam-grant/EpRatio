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


void xtalIndex(TFile *file, TH2D *hist, string name, string title, string fname, bool tau) {

  double weight;
  TH1D *h = (TH1D*)file->Get(name.c_str());
  for( int x = 0 ; x < 9 ; x++ ) {
    for( int y = 0 ; y < 6 ; y++) {
      int xtal = x+9*y;
      //cout << xtal <<" " <<x<<" "<<y<<endl;
      //  if(weight < 0 || weight > ) continue;
      weight=h->GetBinContent(xtal+1);

      if(tau && (weight < 0 || weight > 16)) continue;
      if(!tau && (weight < 0 || weight > 0.05)) continue;

      hist->Fill(x,y,weight);
    }
  }

  TCanvas *c = new TCanvas("c", "c", 2000, 1000);
  // gStyle->SetPalette(55);//
  // hist->Get
  hist->SetStats(0);
  hist->SetTitle(title.c_str());
  hist->Draw("COLZ");
  // hist->Draw("text same");
  c->SaveAs(fname.c_str());
  delete c;
  return;

}

int main() {

  //All inputs
  TFile *laser_xtal = TFile::Open("inFillGainParams_laser_xtal.root");
  TFile *sam_xtal = TFile::Open("inFillGainParams_sam_xtal2.root");
  TFile *output = new TFile("2D.root","RECREATE");

  TH2D *tau13_laser = new TH2D("tau13_laser","",9,0,9,6,0,6);
  TH2D *tau19_laser = new TH2D("tau19_laser","",9,0,9,6,0,6);
  TH2D *amp13_laser = new TH2D("amp13_laser","",9,0,9,6,0,6);
  TH2D *amp19_laser = new TH2D("amp19_laser","",9,0,9,6,0,6);

  TH2D *tau13_sam = new TH2D("tau13_sam","",9,0,9,6,0,6);
  TH2D *tau19_sam = new TH2D("tau19_sam","",9,0,9,6,0,6);
  TH2D *amp13_sam = new TH2D("amp13_sam","",9,0,9,6,0,6);
  TH2D *amp19_sam = new TH2D("amp19_sam","",9,0,9,6,0,6);

  xtalIndex(laser_xtal,tau13_laser,"tau_13","Calo 13 | Recovery Times (Laser);Crystal Index X;Crystal Index Y;#tau","St13_tau_laser_2d.png",true);
  xtalIndex(sam_xtal,tau13_sam,"tau_13","Calo 13 | Recovery Times (E/p Ratio);Crystal Index X;Crystal Index Y;#tau","St13_tau_sam_2d.png",true);
  xtalIndex(laser_xtal,tau19_laser,"tau_19","Calo 19 | Recovery Times (Laser);Crystal Index X;Crystal Index Y;#tau","St19_tau_laser_2d.png",true);
  xtalIndex(sam_xtal,tau13_sam,"tau_19","Calo 19 | Recovery Times (E/p Ratio);Crystal Index X;Crystal Index Y;#tau","St19_tau_sam_2d.png",true);
  
  xtalIndex(laser_xtal, amp13_laser,"amp_13","Calo 13 | Amplitudes (Laser);Crystal Index X;Crystal Index Y;Amplitude","St13_amp_laser_2d.png",false);
  xtalIndex(sam_xtal,amp13_sam,"amp_13","Calo 13 | Amplitudes (E/p Ratio);Crystal Index X;Crystal Index Y;Ampltitude","St13_amp_sam_2d.png",false);
  xtalIndex(laser_xtal,amp19_laser,"amp_19","Calo 19 | Amplitudes (Laser);Crystal Index X;Crystal Index Y;Amplitude","St19_amp_laser_2d.png",false);
  xtalIndex(sam_xtal,amp19_sam,"amp_19","Calo 19 | Amplitudes (E/p Ratio);Crystal Index X;Crystal Index Y;Amplitude","St19_amp_sam_2d.png",false);

  return 0;
}
