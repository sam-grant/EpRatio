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

  //hist->GetYaxis()->SetRangeUser(0.99,1.001);

  hist->SetLineWidth(3);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());

  //hist->SetStats(0);
  hist->GetYaxis()->SetTitleOffset(1.0);
  hist->GetXaxis()->SetTitleOffset(0.9);
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

  return lineFit;

}

double SlowGainFunc(double *x, double *par) {

  // return par[0] + par[1] * exp(-x[0] / 64.44) * ( 1 + 0.2 * cos(par[3] * x[0] - par[4]));
  return par[0] + par[1] * exp(-x[0] / 64.44);
}

void SlowGainFit(TH1D *hist) {

  TF1 *func = new TF1("func", SlowGainFunc, 4.2, 4.2*50, 2);

  // func->FixParameter(1,64.44);
  func->SetLineWidth(3);
  func->SetParName(0,"Offset");
  func->SetParName(1,"Amplitude");

  hist->Fit(func);

  return;
}

int main() {

  string inputFname = "../ROOT/PlotsTimeCalo_9day.root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout<<"Reading... "<<inputFname<<endl;

  vector<TH1D*> hists12_, hists18_;
  
  for (int stn(13); stn < 20; stn = stn + 6) {

    string name = "St"+to_string(stn)+"_Ep_vs_t";
    // Change input if need be
    
    TH1D *h = (TH1D*)input->Get(name.c_str());
    if(h==0) continue;

    // Fit a pol0 to normalise
    TF1 *lineFit = LineFit(h);
    // double norm = lineFit->GetParameter(0);
    h->Scale(1./lineFit->GetParameter(0));

    SlowGainFit(h);
    FancyDraw(h, stn-1, "Station "+to_string(stn-1)+";In fill time [#mus];E/p", "SlowGainFit");

  }

  return 0;
}
