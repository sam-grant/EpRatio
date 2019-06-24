// Sam Grant - April 2019
// samuel.grant.18@ucl.ac.uk
// Draw pulls per xtal on a map of the calo face
// Y axis needed reversing 

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

int main() {
  
  string input_fname;
  string fname;
  string name;
  bool quality = true;//false;
  bool full = true;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";

  string cut[4] = {"Q","statCut","errCut","chiCut"};
  string par[2] = {"tau","amp"};
  string parName[2] = {"Recovery Time","Amplitude"};
  string statName[2] = {" Pull"," Fractional Uncertainty"};
  double value;
  TH2D *map = new TH2D("","",9,0,9,6,0,6);      
  string stat[2] = {"pull_shift","frac_shift"};  	
  for(int istat(0); istat < 2; istat++){
    
    for (int icut(0); icut < 4; icut++) {
      //      if(icut!=1)continue;
      for (int stn(13); stn < 20; stn = stn + 6) {
    
	for (int ipar(0); ipar < 2; ipar++) {

	  int counter = 0;

	  if(quality) {
	    input_fname = stat[istat]+all+cut[icut]+".root";
	    fname = "St"+to_string(stn)+"_"+par[ipar]+"_map_"+stat[istat]+all+cut[icut]+".png";
	  }
	  else if (!quality) {
	    input_fname = stat[istat]+all+"noQ.root";
	    fname = "St"+to_string(stn)+"_"+par[ipar]+"_map_"+stat[istat]+all+"noQ.png";
	  }
	  cout << input_fname << endl;
	  TFile *input = TFile::Open(input_fname.c_str());

	  name = par[ipar]+"_"+to_string(stn);
	  cout<<name<<endl;
	  // Change input if need be
	  TH1D *hist = (TH1D*)input->Get(name.c_str());
	  //	  if(hist==0) continue;

	  TCanvas *c1  = new TCanvas("c1","c1",1500,1000);    

	  for( int x = 0 ; x < 9 ; x++ ) {
	    for( int y = 0 ; y < 6 ; y++) {
	      int xtal = x+9*y;
	      //	c1->cd(xtal+1);
	      //cout << xtal << endl;
	      value = fabs(hist->GetBinContent(xtal+1));
	      //	      if(value>100)continue;
	      //	      cout<<stn<<" "<<par[ipar]<<" "<<value<<endl;
	      map->SetBinContent(x+1,y+1,value);

	      if(value!=0)counter++;
	    }
	  }
	  cout<<"Number of xtals "<<counter<<endl;
	  counter=0;
	  //      gPad->SetLogz();
	  gStyle->SetPalette(55);
	  map->SetTitle(("Calo "+to_string(stn)+" | "+parName[ipar]+statName[istat]+";Crystal Index X;Crystal Index Y").c_str());
	  map->SetStats(0);
	  map->Draw("COLZ");
	  map->Draw("text same");      

	  c1->SaveAs(fname.c_str());
	  delete c1;
	  delete hist;
	}
      }
    }
  }

  return 0;
}
