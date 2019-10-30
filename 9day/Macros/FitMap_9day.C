// Sam Grant - August 2019
// samuel.grant.18@ucl.ac.uk
// Draw all my gauss fits in corresponding crystal position.
// Y axis needed reversing 

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

int main() {
  string inputFname = "../ROOT/FitsTimeXtalFid_9day.root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout<<"Reading... "<<inputFname<<endl;

  int place = 0;
  
  TCanvas *c1  = new TCanvas("","",600,600);    
  c1->Divide(5,5);

  for (int stn(13) ; stn < 20 ; stn = stn + 6 ) {

    // 33 xtals, so draw a 5 by 7 grid
    for(int xtal(0); xtal<54; xtal++) {

      string name = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      // Change input if need be
      TH1D *h = (TH1D*)input->Get(name.c_str());
      if(h==0) continue;

      // Some formatting
      h->SetTitle(("Station "+to_string(stn-1)+", Crystal "+to_string(xtal)+";In fill time [#mus];E/p").c_str());
      h->GetYaxis()->SetTitleOffset(1.25);
      h->GetXaxis()->SetRange(0,23);
      c1->cd(place+1);
      place++;
      cout<<place<<endl;
      h->SetStats(0);
      /* gStyle->SetOptStat(10); */
      /* gStyle->SetOptFit(111); */
      h->Draw();

    }

  }
    string fname = "../TestPlots/FitXtalMap_9day.pdf";
    c1->SaveAs(fname.c_str());
    delete c1;

  return 0;
}
