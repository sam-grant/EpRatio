// Sam Grant - April 2019
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

void draw(TH2D *hist, string title, string fname) {

  TCanvas *c = new TCanvas();
  ///  hist->SetStats(0);
  hist->SetLineColor(kBlack);
  hist->SetLineWidth(2);
  hist->Draw("COLZ");
  //  c->BuildLegend(0.79,0.79,0.89,0.89);
  hist->SetTitle(title.c_str());
  // gPad->SetGridx();
  c->SaveAs(fname.c_str());
  delete c;

  return;
}


int main() {

  bool quality = false;
  bool full = true;
  
  string input_fname1, input_fname2;
  string fname;
  string name1, name2;
  string all;
  string title;
  string cut[4] = {"Q","statCut","errCut","chiCut"};
  string par1[2] = {"chi","N"};
  string par2[2] = {"tau","amp"};

  string parName[2] = {"#chi^{2} / NDF","Entries"};
  string statName[2] = {" Pull"," Fractional Shift"};
  string stat[2] = {"pull_shift","frac_shift"};
  double shiftVal, otherVal;//, NVal, chiVal;

  TH2D *result = new TH2D("","",50,0,50,50,0,50);
  //  TH2D *N = new TH2D("","",500,0,100,250,0,250e+3);

  if(full) all = "_full_";
  else if(!full) all = "_";

  for(int istat(0); istat < 2; istat++){
    
    //    for (int icut(0); icut < 4; icut++) {

      //      cout << stat[istat] << endl;
    
      int counter = 0;

      if(quality) {
	//1: stat root fill, 2: par root file
	//	input_fname1 = stat[istat]+all+cut[icut]+".root";
	input_fname2 = "inFillGainParams_Ep_xtal_errors_"+stat[istat]+".root";
      }
      else if (!quality) {
	input_fname1 = stat[istat]+all+"noQ.root";
    	input_fname2 = "inFillGainParams_Ep_xtal_errors_noQ.root";
      }

      TFile *input1 = TFile::Open(input_fname1.c_str());
      TFile *input2 = TFile::Open(input_fname2.c_str());
       cout << "input1 " <<input_fname1<<endl;
      // cout << "input2 " <<input_fname2<<endl;
  
      for (int stn(13); stn < 20; stn = stn + 6) {
    
	for (int ipar(0); ipar < 2; ipar++) {
	  // FIX THIS SAM
	  name2 = par1[ipar]+"_"+to_string(stn);
	  name1 = par2[ipar]+"_"+to_string(stn);
	  
	  cout << name1 << endl;
	  // cout << name2 << endl;
	  TH1D *hist1 = (TH1D*)input1->Get(name1.c_str());
     	  if(hist1!=0) cout << "success" << endl;
	    //continue;
	  TH1D *hist2 = (TH1D*)input2->Get(name2.c_str());
	  if(hist2!=0) cout << "success" << endl;//continue;

	  for (int xtal(0); xtal < 54; xtal++) {
	    // From shift root file  

	    shiftVal = fabs(hist1->GetBinContent(xtal+1));
	  // from inFill root file

	  otherVal = fabs(hist2->GetBinContent(xtal+1));


	  result->Fill(otherVal,shiftVal);
	  //	  chi->Fill(chiVal,shiftVal);

	  if(shiftVal != 0) counter++;

	  }
	  cout<<"Number of xtals "<<counter<<endl;
	  counter=0;

	  //	  map->SetTitle(("Calo "+to_string(stn)+" | "+parName[ipar]+statName[istat]+";Crystal Index X;Crystal Index Y").c_str());
	  //map->SetStats(0);
	 
	  // map->Draw("text same");
	  title = "St"+to_string(stn)+"_"+par1[ipar]+"_vs_"+par2[ipar];
	  fname = "St"+to_string(stn)+"_"+par1[ipar]+"_vs_"+par2[ipar]+"_"+stat[istat]+all+".png";
	  //	  fname = "St"+to_string(stn)+"_"+par1[ipar]+"_vs_"+par2[ipar]+stat[istat]+all+cut[icut]+".png";
	  draw(result,title,fname);//"COLZ");
	  //	  draw(N,titleN,fnameN);
	  //x delete hist1;
	  //	  delete hist2;
	  //	}
      }
    }
  }

  return 0;
}
