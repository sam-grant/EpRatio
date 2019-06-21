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

void draw(TH1D *hist, string fname, string title) {

  TCanvas *c = new TCanvas("c","c",1500,1000);
  ///  hist->SetStats(0);
  hist->SetLineColor(kBlack);
  hist->SetLineWidth(2);
  hist->SetMarkerStyle(kStar);
  hist->SetTitle(title.c_str());
  hist->Draw("P");
  //  c->BuildLegend(0.79,0.79,0.89,0.89);
  //
  c->SetLogy();
  gPad->SetGrid();
  c->SaveAs(fname.c_str());
  delete c;

  return;
}


int main() {

  string xParName = "#chi^{2} / NDF";//
  string xPar = "chi";
  string statName[2] = {"Pull [#sigma]","Fractional Shift"};
  string stat[2] = {"pull_shift","frac_shift"};
  string par[2] = {"tau","amp"};
  string histName, fileName;
  string name[2];
  double NVal, shiftVal;//, NVal, chiVal;
  
  TH1D *result = new TH1D("result","result",100,0,4);

  for(int istat(0); istat < 2; istat++){

    TFile *shiftFile = TFile::Open((stat[istat]+"_full_noQ.root").c_str());
    TFile *entryFile = TFile::Open("inFillGainParams_Ep_xtal_errors_noQ.root");

    for (int stn(13); stn < 20; stn = stn + 6) {
      for(int ipar(0); ipar < 2; ipar++) {

	histName = par[ipar]+"_"+to_string(stn);
	cout << histName << endl;
	TH1D *hist1 = (TH1D*)shiftFile->Get(histName.c_str());//(stat[istat]+"_"+to_string(stn)).c_str());

	histName = xPar+"_"+to_string(stn);
	cout << histName << endl;
	TH1D *hist2 = (TH1D*)entryFile->Get(histName.c_str());

	for (int xtal(0); xtal < 54; xtal++) {

	  shiftVal = fabs(hist1->GetBinContent(xtal+1));
	  NVal = fabs(hist2->GetBinContent(xtal+1));

	  cout <<shiftVal<<endl;
	  result->SetBinContent(NVal,shiftVal);

	  string fname = "St"+to_string(stn)+"_"+stat[istat]+"_versus_"+xPar+".png";
	  string title = "Calo "+to_string(stn)+" | "+statName[istat]+" vs. "+xParName+";"+xParName+" per fit;"+statName[istat];
	  draw(result,fname,title);

	}
      }
    }

    return 0;
  }
