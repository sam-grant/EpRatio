// Plotting code for gain par per xtal scatter plots 
// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

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
// Function for drawing the plots
void draw(vector<double> true_, vector<double> fix_,  string title, string fname) {
  //void draw(TH1D *hist1, string title, string fname) {
  TH1D *hist1 = new TH1D("","",18,0.5,18.5); 
  TH1D *hist2 = new TH1D("","",18,0.5,18.5); 
  double chi1Sum = 0;
  double chi2Sum = 0;
  for(int i(0); i<true_.size(); i++) {
    hist1->SetBinContent(i+1,true_.at(i));
    hist1->SetBinError(i+1,0);
    hist2->SetBinContent(i+1,fix_.at(i));
    hist2->SetBinError(i+1,0);
    chi1Sum=chi1Sum+true_.at(i);
    chi2Sum=chi2Sum+fix_.at(i);
  }
  cout<<"Mean True ChiSqrNdf: "<<chi1Sum/18<<endl;
  cout<<"Mean Fixed ChiSqrNdf: "<<chi2Sum/18<<endl;
    
  TCanvas *c = new TCanvas("","",3000,2000);
  TLegend *leg = new TLegend(0.69,0.69,0.89,0.89);
  leg->SetBorderSize(0);
  hist1->SetStats(0);
  hist2->SetStats(0);
  hist1->SetMarkerColor(kGreen+2);
  hist2->SetMarkerColor(kRed);
  hist1->SetLineWidth(0);
  hist1->SetMarkerSize(5);
  hist2->SetLineWidth(0);
  hist2->SetMarkerSize(5);
  for(int xtal(0); xtal<54; xtal++) {
    if(hist1->GetBinContent(xtal+1) == 0) hist1->SetBinContent(xtal+1,-1000);
    if(hist2->GetBinContent(xtal+1) == 0) hist2->SetBinContent(xtal+1,-1000);
  }
  hist1->SetMarkerStyle(20);
  hist2->SetMarkerStyle(20);
  hist1->SetTitle("True Fits");
  hist2->SetTitle("Fixed Fits");
  leg->AddEntry(hist1);
  leg->AddEntry(hist2);
  hist1->GetYaxis()->SetRangeUser(0,2.5);
  hist1->Draw("P");
  hist2->Draw("P same");
  leg->Draw("same"); 
  hist1->SetTitle(title.c_str());
  gPad->SetGridx();
  c->SaveAs(fname.c_str());
  delete c;

  return;
}

int main() {
  
  string inputFname1 = "RootFiles/FitsTimeXtal_Q.root";
  string inputFname2 = "RootFiles/FitsTimeXtalFixLaser_Q.root";

  TFile *input1 = TFile::Open(inputFname1.c_str());
  TFile *input2 = TFile::Open(inputFname2.c_str());
  cout<<"Reading... "<<inputFname1<<", "<<inputFname2<<endl;
  /* string fname[2] = {"Plots/St13ChiSqr.png","Plots/St19ChiSqr.png"}; */
  /* string title[2] = {"Stn 12;Crystal Number;#chi^{2}/NDF","Stn 18;Crystal Number;#chi^{2}/NDF"};x */

  string fname = "Plots/ChiSqrCompare.png"; 
  string title = ";Fit Number;#chi^{2}/NDF"; 
  vector<double> chi1_;
  vector<double> chi2_;
  
  int icount = 0;

  for(int stn(13); stn<20; stn = stn+6) {
    double chi1Sum = 0;
    double chi2Sum = 0;
    
    for (int xtal(0); xtal<54; xtal++) {

      TH1D *h1 = (TH1D*)input1->Get(("St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal)).c_str());
      TH1D *h2 = (TH1D*)input2->Get(("St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal)).c_str());

      if(h1==0 || h2==0) continue;

      // Get Fit
      TF1 *fit1 = (TF1*)h1->GetFunction("f1");
      TF1 *fit2 = (TF1*)h2->GetFunction("f2");
      
      double chi1 = fit1->GetChisquare()/fit1->GetNDF();
      double chi2 = fit2->GetChisquare()/fit2->GetNDF();

      chi1_.push_back(chi1);
      chi2_.push_back(chi2);
      
      chi1Sum = chi1Sum + chi1;
      chi2Sum = chi2Sum + chi2;

      /* chiHist1->SetBinContent(xtal+1,chi1); */
      /* chiHist1->SetBinError(xtal+1,0); */
      /* chiHist2->SetBinContent(xtal+1,chi2); */
      /* chiHist2->SetBinError(xtal+1,0); */
      /* cout<<"stn : "<<stn-1<<" xtal : "<<xtal<<" chi1 : "<<fit1->GetChisquare()<<"/"<<fit1->GetNDF()<<" chi2 : "<<fit2->GetChisquare()<<"/"<<fit2->GetNDF()<<" dchi : "<<endl; */
      /* cout<<"stn : "<<stn-1<<" xtal : "<<xtal<<" chi1 : "<<chi1<<" chi2 : "<<chi2<<endl; */
    }
    /* double chi1Mean = chi1Sum/18; */
    /* double chi2Mean = chi2Sum/18; */
    /* cout<<"Stn "<<stn-1<<", chi1 Mean: "<<chi1Mean<<", chi2 Mean: "<<chi2Mean<<endl; */
  }
  draw(chi1_,chi2_,title,fname);
  cout<<"\nClosing"<<endl;
  input1->Close();
  input2->Close();
  return 0;
  
}
