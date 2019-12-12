// Fit Aaron's slow gain function to E/p
// See DocDB 17962
// Sam Grant - Dec 2019

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "TLine.h"
#include <vector>

using namespace std;

TLine *Line(TH1D *hist) {

  TF1 *fit = hist->GetFunction("SlowGainFunc");

  TLine *line = new TLine(4.2,fit->GetParameter(0),4.2*50,fit->GetParameter(0));

  line->SetLineWidth(3);
  line->SetLineStyle(2);
  line->SetLineColor(kBlue);

  return line;
}

TF1 *LineFit(TH1D *hist) {

  // Fit p0 to normalise
  TF1 *lineFit = new TF1("lineFit", "pol0");
 
  hist->Fit(lineFit,"Q");

  return lineFit;

}

double SlowGainFunc(double *x, double *par) {

  return par[0] + par[1] * exp(-x[0] / 64.44);

}

void SlowGainFit(TH1D *hist) {

  TF1 *func = new TF1("SlowGainFunc", SlowGainFunc, 4.2, 4.2*50, 2);

  func->SetLineWidth(3);

  hist->Fit(func,"Q");

  cout<<"Offset:   \t"<<func->GetParameter(0)<<endl;
  cout<<"Amplitude:\t"<<func->GetParameter(1)<<endl;
  cout<<"===================================="<<endl;

  return;

}

void FancyDraw(TH1D *hist, int stn, string title, string name) {

  TCanvas *c = new TCanvas("c","c",800,600);//"","",3000,2000);
  
  gStyle->SetStatFormat("6.3g");
  hist->Draw();
  gPad->Update();

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

  hist->SetLineWidth(3);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());

  hist->GetYaxis()->SetTitleOffset(1.3);
  hist->GetXaxis()->SetTitleOffset(1.0);
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);
  hist->SetTitleSize(.75);
  hist->GetXaxis()->SetTitleSize(.05);
  hist->GetYaxis()->SetTitleSize(.05);
  c->SetLeftMargin(0.13);

  hist->Draw();

  Line(hist)->Draw("same");
  c->SaveAs(("../TestPlots/"+name+(to_string(stn))+".png").c_str());
  c->SaveAs(("../ThesisPlots/"+name+(to_string(stn))+".pdf").c_str());

  delete c;

}

int main() {

  string inputFname = "../ROOT/PlotsTimeCalo_9day.root";
  TFile *input = TFile::Open(inputFname.c_str());
  
  // cout<<"Reading... "<<inputFname<<endl;

  vector<TH1D*> hists12_, hists18_;
  
  for (int stn(13); stn < 20; stn = stn + 6) {

    string name = "St"+to_string(stn)+"_Ep_vs_t";
    // Change input if need be
    
    TH1D *h = (TH1D*)input->Get(name.c_str());
    if(h==0) continue;

    // Fit a pol0 to normalise
    TF1 *lineFit = LineFit(h);
    h->Scale(1./lineFit->GetParameter(0));

    cout<<"Station:\t"<<stn-1<<endl;

    SlowGainFit(h);
    FancyDraw(h, stn-1, "Station "+to_string(stn-1)+";In fill time [#mus];E/p", "SlowGainFit");

  }

  return 0;

}
