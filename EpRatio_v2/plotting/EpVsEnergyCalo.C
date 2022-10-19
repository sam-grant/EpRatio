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


void FancyDraw(TH1D *hist, int stn, string title, string name, string dataset) { //, double binning, int start, int end) {

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

  // hist->GetXaxis()->SetRangeUser(0.0, 210);
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

  string inputName = "../plots/"+dataset+"/plotsEpEnergyCalo_"+fitMode+"_"+dataset+".root";
  TFile *input = TFile::Open(inputName.c_str());
  cout<<"Reading\t"<<inputName<<"\t"<<input<<endl;

  for (int stn(12); stn < 19; stn = stn + 6) {

    // Change input if need be
    string name = "GainCorr/S"+to_string(stn)+"/profiles/EoverPvsEnergyCalo";
    TH1D *h = (TH1D*)input->Get(name.c_str());
    // h->GetXaxis()->SetRangeUser(1000,3000);

    cout<<"Station:\t"<<stn<<endl;

    // Clone the histogram
 //   TH1D *h_1 = (TH1D*)h->Clone("h_1");

    
    FancyDraw(h, stn, dataset+", station "+to_string(stn)+";Cluster energy [MeV];E/p", "_EpVsEnergyCalo_"+fitMode, dataset); // , binWidth, startPeriod, endPeriod);
    h->GetXaxis()->SetRangeUser(1000,3000);
    FancyDraw(h, stn, dataset+", station "+to_string(stn)+";Cluster energy [MeV];E/p", "_EpVsEnergyCaloTightRange_"+fitMode, dataset); // , binWidth, startPeriod, endPeriod);

  }

  input->Close();

  return 0;

}
