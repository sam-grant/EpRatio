// Sam Grant - April 2019
// samuel.grant.18@ucl.ac.uk
// Draw remaining xtals
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
  
  string inputFname = "RootFiles/EpParameters_Q.root";
  string outputFname = "RootFiles/XtalMap_Q.root";
  TFile *input = TFile::Open(inputFname.c_str());
  TFile *output = new TFile(outputFname.c_str(),"recreate");
  cout<<"Reading... "<<inputFname<<endl;
  
  TH2D *map = new TH2D("","",9,-0.5,8.5,6,-0.5,5.5);      

  for (int stn(13); stn < 20; stn = stn + 6) {
    
	  int counter = 0;
	  string histName = "N_"+to_string(stn);
	  TH1D *hist = (TH1D*)input->Get(histName.c_str());

	  TCanvas *c1  = new TCanvas("","",800,600);    

	  for( int x = 0 ; x < 9 ; x++ ) {
	    for( int y = 0 ; y < 6 ; y++) {
	      int xtal = x+9*y;
	      double value = fabs(hist->GetBinContent(xtal+1));
	      map->SetBinContent(x+1,y+1,value);
	      if(value!=0)counter++;
	    }
	  }
	  cout<<"Stn: "<<stn<<", Number of xtals "<<counter<<endl;
	  counter=0;
	  gStyle->SetPalette(55);
	  map->SetTitle(("Stn "+to_string(stn-1)+";Crystal Index X;Crystal Index Y").c_str());
	  map->SetStats(0);
	  //map->GetXaxis()->CenterTitle(1);
	  //map->GetYaxis()->CenterTitle(1);
	  map->Draw("COLZ");
	  c1->SaveAs(("PlotsGoldList/St"+to_string(stn)+"SurivingXtals.pdf").c_str());

  }

  return 0;
}
