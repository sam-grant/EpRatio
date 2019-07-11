// Sam Grant - April 2019
// samuel.grant.18@ucl.ac.uk
// WORK IN PROGRESS

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

void draw(TH1D *hist, string fname, string title, bool log) {
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist->SetStats(0);
  hist->SetMarkerColor(kBlack);
  hist->SetLineWidth(2);
  hist->SetMarkerStyle(kStar);
  hist->SetMarkerSize(3);
  hist->SetTitle(title.c_str());
  hist->Draw("P");
  //  c->BuildLegend(0.79,0.79,0.89,0.89);
  //  if(log) c->SetLogy();
  gPad->SetGrid();
  c->SaveAs(fname.c_str());
  delete c;
  return;
}


int main() {

  string xParName[2] = {"#chi^{2} / NDF","Entries / Crystal"};//
  string xPar[2] = {"chi","N"};
  string yParName[2] = {"Pull [#sigma]","Fractional Shift"};
  string yPar[2] = {"stat_pull","frac_shift"};
  string par[2] = {"tau","amp"};
  string histName, fileName;
  string name[2];
  double NVal, shiftVal;//, NVal, chiVal;
  int nBins, xLow, xHigh;
  bool log = false;
  TH1D *result1 = new TH1D("result1","result1",40,0,4);//nBins,xLow,xHigh);
  TH1D *result2 = new TH1D("result2","result2",250,0,250000);
  
  for(int iyPar(0); iyPar < 2; iyPar++){

    TFile *shiftFile = TFile::Open((yPar[iyPar]+"_full_veryEarly_noQ.root").c_str());
    TFile *entryFile = TFile::Open("inFillGainParams_Ep_xtal_errors_veryEarly_noQ.root");

    for (int stn(13); stn < 20; stn = stn + 6){

      for(int ipar(0); ipar < 2; ipar++){

	histName = par[ipar]+"_"+to_string(stn);
	TH1D *hist1 = (TH1D*)shiftFile->Get(histName.c_str());

	for(int ixPar(0); ixPar < 2; ixPar++){
	  //	  if(ixPar == 0) log=true;//{ // chi
	  //	  if(ixPar == 1) log=false;

	  histName = xPar[ixPar]+"_"+to_string(stn);

	  TH1D *hist2 = (TH1D*)entryFile->Get(histName.c_str());
	 
	  for (int xtal(0); xtal < 54; xtal++) {
	    shiftVal = fabs(hist1->GetBinContent(xtal+1));
	    	    if(shiftVal > 10) continue;
	    NVal = fabs(hist2->GetBinContent(xtal+1));
	    // if (NVal > 1.5 && ) cout << NVal << endl;
	    if(ixPar==0) result1->SetBinContent(NVal,shiftVal);
	    if(ixPar==1) result2->SetBinContent(NVal,shiftVal);
	  }

	  string fname = "St"+to_string(stn)+"_"+yPar[iyPar]+"_versus_"+xPar[ixPar]+".png";
	  string title = "Calo "+to_string(stn)+" | "+yParName[iyPar]+" vs. "+xParName[ixPar]+";"+xParName[ixPar]+";"+yParName[iyPar];
	  
	  if(ixPar==0) draw(result1,fname,title,log);
	  if(ixPar==1) draw(result2,fname,title,log);
	  // Delete to stop leaking memory, VErY iMpOrtAnt SAM!
	  //delete result;
	}
      }
    }
  }
  return 0;
}
