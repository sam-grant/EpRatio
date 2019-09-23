// Plot and fit the uncertainties for the surviving xtals
// Sam Grant
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TAttMarker.h"
#include "TPaveStats.h"

using namespace std;

// Define percentage uncertainty 
double Value(double laserValue, double EpValue) {
  // Fractional shift
  double result = (laserValue - EpValue) / laserValue;
  return result;//sqrt(pow(result,2));
}
// Define percentage uncertainty uncertainty
double Error(double laserValue, double laserError, double EpValue, double EpError) {
  double term1 = (EpValue*laserError) / pow(laserValue,2);
  double term2 = EpError / laserValue;
  return sqrt(pow(term1,2) + pow(term2,2));
}
// Drawing function
void DrawNFit(TH1D *hist, TFile *output, string fname, string title) {
  TCanvas *c = new TCanvas("c","c",3000,2000);
  TF1 *lineFit = new TF1("lineFit", "pol 0");

  gStyle->SetStatFormat("6.3g");

      /* hist->Draw(); */
      /* gStyle->SetStatFormat("6.3g"); */
      gStyle->SetOptStat(10); 
      gStyle->SetOptFit(110);
      /* //Collect stats of the first histogram */
      /* gPad->Update(); */
      hist->Draw();
      gPad->Update();
      TPaveStats *tps1 = (TPaveStats*)hist -> FindObject("stats"); 
      tps1->SetLineWidth(0);

      tps1->SetX1NDC(0.49);
      tps1->SetX2NDC(0.89);
      tps1->SetY1NDC(0.11);
      tps1->SetY2NDC(0.31);
  /* Hist->SetStats(1); */
  /* hist->Draw(); */
  /* gStyle->SetOptStat(0); */
  /* gStyle->SetOptFit(111); */
  /* gPad->Update(); */

  /* //Collect stats of the first histogram */
  /* TPaveStats *tps1 = (TPaveStats*)hist->FindObject("stats"); */

  /* //  tps1->SetTextColor(kBlue); */
  /* // tps1->SetLineColor(kBlue); */

  /* tps1->SetX1NDC(0.65); */
  /* tps1->SetX2NDC(0.89); */
  /* tps1->SetY1NDC(0.15); */
  /* tps1->SetY2NDC(0.25); */
  
  lineFit->SetLineWidth(5);
  
  hist->Fit(lineFit);

  hist->SetLineColor(kBlack);
  hist->SetLineWidth(5);
  hist->SetTitle(title.c_str());
  hist->GetXaxis()->CenterTitle(true);
  hist->GetYaxis()->CenterTitle(true);
  hist->SetTitleSize(.75);
  hist->GetXaxis()->SetTitleSize(.05);
  hist->GetYaxis()->SetTitleSize(.05);
  hist->GetYaxis()->SetTitleOffset(0.9);
  hist->GetXaxis()->SetTitleOffset(0.75);
  hist->Draw();
  tps1->Draw("same");
  c->SaveAs(fname.c_str());
  hist->SetDirectory(output);
  delete c;
  delete lineFit;
  return;
}

TH1D *Fill(vector<double> values_, vector<double> errors_) {

  if(values_.size() != errors_.size()) {
    cout<<"Error: value and eror vectors not equally sized"<<endl;
    return 0;
  }
  
  TH1D *hist = new TH1D("hist","hist title",values_.size(),0.5,values_.size()+0.5);

  for(int i(0); i<values_.size(); i++) {
    hist->SetBinContent(i+1,values_.at(i));
    cout<<"Bin: "<<i+1<<", Value: "<<values_.at(i)<<", Error: "<<errors_.at(i)<<endl;
    hist->SetBinError(i+1,errors_.at(i));
  }
  
  return hist;
  //  delete hist;
}

int main() {
  
  string EpInputName = "RootFiles/EpParameters_Q.root";
  string laserInputName = "RootFiles/LaserParameters.root";
  string outputName = "RootFiles/PercentageUncertainty.root";

  // Set inputs
  TFile *EpInput = TFile::Open(EpInputName.c_str());
  TFile *laserInput = TFile::Open(laserInputName.c_str());

  // Set output
  TFile *output = new TFile(outputName.c_str(),"RECREATE");
  
  cout<<"Reading... "<<EpInputName<<endl;
  cout<<"Reading... "<<laserInputName<<endl;
    
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
 
  vector<double> tauValues_;
  vector<double> alphaValues_;
  vector<double> tauErrors_;
  vector<double> alphaErrors_;

  // Start hist loop
  cout<<"Starting histogram loop\n"<<endl;
  for (int ihist(0); ihist < 4; ihist++) {
    
    cout<<"histogram : "<<h[ihist]<<"\n"<<endl;
    
    TH1D *Ep = (TH1D*)EpInput->Get(h[ihist].c_str());
    TH1D *laser = (TH1D*)laserInput->Get(h[ihist].c_str());
    
    int counter = 0;

    // Start xtal loop
    
    for (int xtal(0); xtal < 54; xtal++) {
      
      if(Ep->GetBinContent(xtal+1) == 0) continue;
      
      double val = Value(laser->GetBinContent(xtal+1),Ep->GetBinContent(xtal+1));
      double err = Error(laser->GetBinContent(xtal+1),laser->GetBinError(xtal+1),Ep->GetBinContent(xtal+1),Ep->GetBinError(xtal+1));

      // Fill vectors
      if(ihist < 2) {
	//	if(xtal==21)continue;
	tauValues_.push_back(val);
	tauErrors_.push_back(err);
      }
      else if(ihist >= 2) {
	alphaValues_.push_back(val);
	alphaErrors_.push_back(err);
      }
      else {
	cout<<"Error"<<endl;
      }

      // Print out results
      if(val != 100) {
	cout<<"xtal: "<<xtal<<", "<<val<<"+/-"<<err<<"%"<<endl;
	counter++;
      }

    } // End xtal loop
      cout<<"\nSurviving xtals: "<<counter<<endl;
  } // End hist loop

  TH1D *tauHist = Fill(tauValues_,tauErrors_);
  DrawNFit(tauHist,output,"Plots/UncertaintyFitTau.pdf",";Fit Number;#Delta#tau_{r}/#tau_{r}");

  TH1D *alphaHist = Fill(alphaValues_,alphaErrors_);
  DrawNFit(alphaHist,output,"Plots/UncertaintyFitAlpha.pdf",";Fit Number;#Delta#alpha/#alpha");
    
  output->Write(); 

  cout<<outputName<<" created"<<endl;
  
  return 0;
}
