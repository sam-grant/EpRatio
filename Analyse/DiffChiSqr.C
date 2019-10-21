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
void draw(TH1D *hist1, TH1D *hist2, string title, string fname) {
//void draw(TH1D *hist1, string title, string fname) {
  
  TCanvas *c = new TCanvas("","",3000,2000);
  TLegend *leg = new TLegend(0.79,0.79,0.89,0.89);
  leg->SetBorderSize(0);
  hist1->SetStats(0);
  hist2->SetStats(0);
  hist1->SetMarkerColor(kRed);
  hist2->SetMarkerColor(kBlue);
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
  hist1->SetTitle("Stn 12");
  hist2->SetTitle("Stn 18");
  leg->AddEntry(hist1);
  leg->AddEntry(hist2);
  hist1->GetYaxis()->SetRangeUser(0,2.0);
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

  /* string fname[2] = {"Plots/St13ChiSqrDiff.png","Plots/St19ChiSqrDiff.png"}; */
  /* string title[4] = {"Stn 12;Crystal Number;#chi^{2}/NDF","Stn 18;Crystal Number;#chi^{2}/NDF"}; */

  string fname = "Plots/ChiSqrDiff.png";
  string title = ";Crystal Number;#Delta#chi^{2}/NDF";

  TH1D *chiHist13 = new TH1D("","",54,-0.5,53.5);
  TH1D *chiHist19 = new TH1D("","",54,-0.5,53.5);
  
  int icount = 0;
  for(int stn(13); stn<20; stn = stn+6) {
    for (int xtal(0); xtal<54; xtal++) {

      TH1D *h1 = (TH1D*)input1->Get(("St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal)).c_str());         TH1D *h2 = (TH1D*)input2->Get(("St"+to_string(stn)+"_Ep_vs_t_"+to_string(xtal)).c_str());
      if(h1==0 || h2==0) continue;

      // Get Fit
      TF1 *fit1 = (TF1*)h1->GetFunction("f1");
      TF1 *fit2 = (TF1*)h2->GetFunction("f2");
      
      double chi1 = fit1->GetChisquare()/fit1->GetNDF();
      double chi2 = fit2->GetChisquare()/fit2->GetNDF();
      double dchi = chi2-chi1;
      
      if(stn==13) {
 	chiHist13->SetBinContent(xtal+1,dchi);
	chiHist13->SetBinError(xtal+1,0);
      }
      else if(stn==19) {
	chiHist19->SetBinContent(xtal+1,dchi);
	chiHist19->SetBinError(xtal+1,0);
      }
      cout<<"stn : "<<stn-1<<" xtal : "<<xtal<<" chi1 : "<<fit1->GetChisquare()<<"/"<<fit1->GetNDF()<<" chi2 : "<<fit2->GetChisquare()<<"/"<<fit2->GetNDF()<<" dchi : "<<dchi<<endl;      
    }

  icount++;
  }

  draw(chiHist13,chiHist19,title,fname);

  return 0;
  
}
