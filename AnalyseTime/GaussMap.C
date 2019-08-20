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

  TFile *input1 = TFile::Open("RootFiles/PlotsEpXtalFid.root");

  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {

    TCanvas *c1  = new TCanvas("c1","c1",6000,4000);    

    c1->Divide(9,6);

    for( int x = 0 ; x < 9 ; x++ ) {
      for( int y = 0 ; y < 6 ; y++) {

	int xtal = x+9*y;
	cout << xtal << endl;

	string name = "St"+to_string(stn)+"_gauss_Ep_vs_xtal_"+to_string(xtal);
	// Change input if need be
	TH1D *h1 = (TH1D*)input1->Get(name.c_str());
	if(h1==0) continue;
	h1->SetTitle(("Crystal "+to_string(xtal)+";E/p;").c_str());
	// Flip along central x-axis
	xtal = x + 9*(5-y);
	//	xtal = x + 7*(3-y);
	c1->cd(xtal+1);
	h1->SetStats(0);
       	h1->SetTitleSize(1.0f,"t");
	h1->SetTitleFont(32,"t");
	h1->Draw();
      }
    }

    string fname = "PlotsGoldList/St"+to_string(stn)+"_EpXtalGaussFid.png";
    c1->SaveAs(fname.c_str());
    delete c1;
  }

  return 0;
}
