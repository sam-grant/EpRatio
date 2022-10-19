// Fit the residual gain variation
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

TLine *Line(TH1D *hist, double binning, int start, int end) {

  TF1 *fit = hist->GetFunction("SlowGainFunc");

  TLine *line = new TLine(binning*start,fit->GetParameter(0),binning*end,fit->GetParameter(0));

  line->SetLineWidth(3);
  line->SetLineStyle(2);
  line->SetLineColor(kBlue);

  return line;
}

double SlowGainFunc(double *x, double *par) {

//  return par[0] + par[1] * exp(-x[0] / par[2]);
  return par[0] + par[1] * exp(-x[0] / 64.44);

}

void SlowGainFit(TH1D *hist, double binning, int start, double end) {

  TF1 *func = new TF1("SlowGainFunc", SlowGainFunc, binning*start/2, binning*end, 2);

  func->SetLineWidth(0);
  //func->FixParameter(2,64.44);
  hist->Fit(func,"RQ");

  cout<<"Offset:   \t"<<func->GetParameter(0)<<endl;
  cout<<"Amplitude:\t"<<func->GetParameter(1)<<"±"<<func->GetParError(1)<<endl;
  cout<<"===================================="<<endl;

  return;

}


void FancyDraw(TH1D *hist, int stn, string title, string name, string dataset, double binning, int start, int end) {

  TCanvas *c = new TCanvas("c","c",800,600);//"","",3000,2000);
  
  gStyle->SetStatFormat("6.3g");
  hist->Draw();
  gPad->Update();

  gStyle->SetOptStat(0);

  hist->SetLineWidth(3);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());

  hist->GetYaxis()->SetTitleOffset(1.3);
  hist->GetXaxis()->SetTitleOffset(0.9);
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);

  double min = hist->GetFunction("SlowGainFunc")->GetParameter(0) - 0.004;
  double max = hist->GetFunction("SlowGainFunc")->GetParameter(0) + 0.004;

  hist->GetYaxis()->SetRangeUser(min, max);
  hist->GetXaxis()->SetRangeUser(0.0, 210);
  hist->SetTitleSize(.75);
  hist->GetXaxis()->SetTitleSize(.05);
  hist->GetYaxis()->SetTitleSize(.05);
  c->SetLeftMargin(0.13);

  hist->Draw();

  c->SaveAs(("../images/"+dataset+"/S"+to_string(stn)+name+".C").c_str());
  c->SaveAs(("../images/"+dataset+"/S"+to_string(stn)+name+".pdf").c_str());

  delete c;

}

int main() {

  // Take command line input for dataset used
  string dataset;
  bool goodInput = false;
  cout << "Enter run-1 dataset: 60h 9d HK EG\n";
  cin >> dataset;
  if (dataset == "60h" || dataset == "9d" || dataset == "HK" || dataset == "EG") { 
     cout << "Starting\n" << endl;
  } else { 
    cout<<"Invalid dataset, stopping"<<endl;
  }

  string fitName;
  string fitMode;
  cout << "Select fit mode: '1' (SingleGaus) '2' (DoubleGaus) '3' (LanGaus)\n";
  cin >> fitName;
  if (fitName == "1") {
    fitMode = "SingleGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl; 
  } else if(fitName == "2") {
    fitMode = "DoubleGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl;
  } else if(fitName == "3") {
    fitMode = "LanGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl;
  } else {
    cout<<"Invalid fitmode, stopping"<<endl;
    exit(0);
  }

  string inputFname = "../plots/"+dataset+"/plotsEpTimeCalo_"+fitMode+"_"+dataset+".root";
  cout<<"Reading\t"<<inputFname<<endl;
  string outputFname = "../plots/"+dataset+"/slowGainFits_"+fitMode+"_"+dataset+".root";
  TFile *input = TFile::Open(inputFname.c_str());
  
  // cout<<"Reading... "<<inputFname<<endl;

  vector<TH1D*> hists12_, hists18_;

  int startPeriod = 0;
  int endPeriod = 50;
  double binWidth = 4.365;
  int fitStartPeriod;
  
  for (int stn(12); stn < 19; stn = stn + 6) {

    // string name = "GainCorr/S"+to_string(stn)+"/profiles/EoverPvsTimeCalo";
    // Change input if need be
    string name = "GainCorr/S"+to_string(stn)+"/profiles/EoverPvsTimeCalo";
    TH1D *h = (TH1D*)input->Get(name.c_str());
    h->GetXaxis()->SetLimits(startPeriod*binWidth,endPeriod*binWidth);

    //if(h==0) continue;

    // Fit a pol0 to normalise
   // TF1 *lineFit = LineFit(h); // , binning, start, end); // , binWidth, startPeriod, endPeriod);
   // h->Scale(1./lineFit->GetParameter(0));

    cout<<"Station:\t"<<stn<<endl;

    // Clone the histogram
    TH1D *h_1 = (TH1D*)h->Clone("h_1");
    TH1D *h_2 = (TH1D*)h->Clone("h_2");
    
    fitStartPeriod = 1;
    SlowGainFit(h_1, binWidth, fitStartPeriod, endPeriod);
    FancyDraw(h_1, stn, dataset+", station "+to_string(stn)+";In-fill time [#mus];E/p", "_EpVsTimeCalo_"+fitMode, dataset, binWidth, startPeriod, endPeriod);

    // fitStartPeriod = 7;
    // SlowGainFit(h_2, binWidth, fitStartPeriod, endPeriod);
    // FancyDraw(h_2, stn, dataset+", station "+to_string(stn)+";In-fill time [#mus];E/p", "_SlowGainFit_30us_"+fitMode, dataset, binWidth, startPeriod, endPeriod);

  }

  input->Close();

  return 0;

}
