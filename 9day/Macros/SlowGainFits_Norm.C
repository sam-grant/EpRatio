#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include <vector>

using namespace std;


void FancyDraw(TH1D *hist, int stn, string title, string name) {

  TCanvas *c = new TCanvas("c","c",800,600);//"","",3000,2000);
  
  gStyle->SetStatFormat("6.3g");
  hist->Draw();
  gPad->Update();

// Typical ROOT nonsense!
   gStyle->SetOptStat(0);
   gStyle->SetOptFit(111);
   gStyle->SetOptStat(10);

  TPaveStats *statBox = (TPaveStats*) hist->FindObject("stats");

  statBox->SetBorderSize();

  statBox->SetBorderSize(0);
  statBox->SetX1NDC(0.49);
  statBox->SetX2NDC(0.89);
  statBox->SetY1NDC(0.65);
  statBox->SetY2NDC(0.88);

  // hist->GetYaxis()->SetRangeUser(-0.1,1.1);

  hist->SetLineWidth(3);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());

  //hist->SetStats(0);
  hist->GetYaxis()->SetTitleOffset(1.0);
  hist->GetXaxis()->SetTitleOffset(0.8);
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);
  hist->SetTitleSize(.75);
  hist->GetXaxis()->SetTitleSize(.05);
  hist->GetYaxis()->SetTitleSize(.05);

  hist->Draw();
  // statBox->Draw("same");
  c->SaveAs(("../TestPlots/"+name+(to_string(stn))+".png").c_str());
  c->SaveAs(("../TestPlots/"+name+(to_string(stn))+".pdf").c_str());

}

TF1* LineFit(TH1D *hist) {

  // Fit a pol0 to normalise
  TF1 *lineFit = new TF1("lineFit", "pol 0");
  lineFit->SetLineWidth(0);

  hist->Fit(lineFit,"Q");
  // lineFit->SetLineColor(kRed);


  return lineFit;

}

TH1D* Combine( vector<TH1D*> h_ ) {

  // Add all the xtal hists together

  int entries = h_.at(0)->GetEntries();

  for (int i = 1; i < h_.size(); i++) {
    // cout<<"i : "<<i<<endl;
    h_.at(0)->Add(h_.at(i));

    entries = entries + h_.at(i)->GetEntries();
  }

  cout<<"***DEBUG***\t ENTRIES IN ALL HISTS ADDED: "<<entries<<endl;

  // Fit a pol0 to normalise
  TF1 *lineFit = LineFit(h_.at(0));
  double norm = lineFit->GetParameter(0);
  h_.at(0)->Scale(1./norm);
  TF1 *lineFitNorm = LineFit(h_.at(0));

  return  h_.at(0);

}

double SlowGainFunc(double *x, double *par) {

  return par[0] * exp(-x[0]/par[1]);
}

void SlowGainFit(TH1D *hist) {

  TF1 *func = new TF1("func", SlowGainFunc, 4.2, 4.2*50, 2);

  //func->FixParameter(0,1);
  func->FixParameter(1,64.44);

  hist->Fit(func);

  return;
}


/*TH1D* Residual(TH1D *hist) { 

  // Fit hist with a flat line and get the fit residual
  // Put residual in new hist

  TH1D *histRes = (TH1D*)hist->Clone("histRes");
  cout<<"***DEBUG***\t BIN CONTENT BEFORE RESET: "<<histRes->GetBinContent(5)<<endl;
  histRes->Reset();
  cout<<"***DEBUG***\t BIN CONTENT AFTER RESET: "<<histRes->GetBinContent(5)<<endl;

  int nBins = hist->GetNbinsX();

  // Fit a pol0 to normalise
  TF1 *lineFit = LineFit(hist);
  double norm = lineFit->GetParameter(0);
  hist->Scale(1./norm);
  TF1 *lineFitNorm = LineFit(hist);

  double time, measured, fitted;

    //Get the residual
  for (int i = 0; i < nBins; i++){

      time = hist -> GetBinCenter(i+1);
      measured = hist -> GetBinContent(i+1);
      fitted = lineFitNorm -> Eval(time);
      
      histRes -> SetBinContent(i, measured-fitted); //residual SG
      
  }

return histRes;

}*/

int main() {

  string inputFname = "../ROOT/PlotsTimeXtalFidCorr_9day.root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout<<"Reading... "<<inputFname<<endl;

  vector<TH1D*> hists12_, hists18_;
  
  for (int stn(13) ; stn < 20 ; stn = stn + 6 ) {

    // 33 xtals, so draw a 5 by 7 grid
    for(int xtal(0); xtal<54; xtal++) {

      string name = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal);
      // Change input if need be
      TH1D *h = (TH1D*)input->Get(name.c_str());
      if(h==0) continue;

      // Fit a pol0 to normalise
      TF1 *lineFit = LineFit(h);
      double norm = lineFit->GetParameter(0);
      h->Scale(1./norm);

      if( stn == 13) hists12_.push_back(h);
      else if( stn == 19) hists18_.push_back(h);

    }

  }

  TH1D *combinedHist = Combine(hists12_);
  // Fit
  SlowGainFit(combinedHist);
 
  cout<<"***DEBUG***\t ENTRIES IN ADDED HISTS: "<<combinedHist->GetEntries()<<endl;
 
  // TH1D *residualHist = Residual(combinedHist);

  FancyDraw(combinedHist, 12, "Station 12;In fill time [#mus];E/p", "combinedHist");

  // FancyDraw(residualHist, 12, "Station 12;In fill time [#mus];Fit residual", "residualHist");

  return 0;
}
