

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


void draw(TH1D *hist1, TH1D *hist2, string title, string fname) {

  TCanvas *c = new TCanvas();
  hist1->SetStats(0);
  hist1->SetMinimum(0);
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kGreen-3);
  hist1->SetLineWidth(2);
  hist2->SetLineWidth(2);
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
  
  TFile *laser = TFile::Open("inFillGainParams_laser_xtal_errors_Q.root");
  TFile *sam = TFile::Open("inFillGainParams_sam_xtal2_Q.root");

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  string title[4] = {"Calo 13 | Recovery Times;Crystal Number;#tau [#mus]","Calo 19 | Recovery Times;Crystal Number;#tau [#mus]","Calo 13 | Amplitudes;Crystal Number;A","Calo 19 | Amplitudes;Crystal Number;A"};
  string fname[4] = {"tau13_scat_hiQ.png","tau19_scat_hiQ.png","amp13_scat_hiQ.png","amp19_scat_hiQ.png"};

  // TH1D *laser_hist;
  //TH1D *sam_hist;
   cout << "test" << endl;
   // laser_hist->SetName("Laser");
   //sam_hist->SetName("E/p Ratio");

   const double factor = 100000;

  // Loop over hists
   double value;
   double error;
   
  for (int i = 0; i < 4; i++) {
    TH1D *laser_hist = (TH1D*)laser->Get(h[i].c_str());
    TH1D *sam_hist = (TH1D*)sam->Get(h[i].c_str());
    for(int xtal = 0; xtal < 54; xtal++) {
      value = laser_hist->GetBinContent(xtal+1);
      error= laser_hist->GetBinError(xtal+1);
      /* if(error>factor*value) {
	laser_hist->SetBinContent(xtal+1,-1000);
       	laser_hist->SetBinError(xtal+1,0);
	}*/
      }
        for(int xtal = 0; xtal < 54; xtal++) {
      value = sam_hist->GetBinContent(xtal+1);
      error= sam_hist->GetBinError(xtal+1);
      /* if(error>factor*value) {
	sam_hist->SetBinContent(xtal+1,-1000);
	 sam_hist->SetBinError(xtal+1,0);
	 }*/
      }
	
      
    laser_hist->SetTitle("Laser");
    sam_hist->SetTitle("E/p Ratio");
    draw(laser_hist,sam_hist,title[i],fname[i]);	       
  }

  


  return 0;

}
