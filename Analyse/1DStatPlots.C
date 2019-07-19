// Plot the combined 1D distributons (pull and frac. unc.)
// Sam Grant
// samuel.grant.18@ucl.ac.uk
// May-June 2019

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
// Define pull
double pull(double Ep_content,double laser_content, double Ep_error, double laser_error) {
  double sigma = sqrt(Ep_error*Ep_error + laser_error*laser_error);
  double result = (Ep_content - laser_content) / sigma;
  return result;
}
// Define fractional shift
double frac(double laser_value, double Ep_value) {
  // Fractional shift
  double result = (laser_value - Ep_value) / laser_value;
  result = result * 100;
  return result;
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title, bool fit) {
  gStyle->SetOptStat(2210);
  if(fit) {
    // Define the gaussian function
    TF1 *gFunc = new TF1("gFunc", "gaus");//,-2,2);
    hist->Fit(gFunc);
    gStyle->SetOptFit(11);
  }
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist->SetName(name.c_str());
  hist->SetLineWidth(3);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());
  hist->Draw();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}

// Drawing function
void draw2(TH1D *hist1, TH1D *hist2, TFile *output, string name, string title, bool fit) {
  gStyle->SetOptStat(2211);
  if(fit) {
    // Define the gaussian function
    TF1 *gFunc = new TF1("gFunc", "gaus");//,-2,2);
    hist1->Fit(gFunc);
    gStyle->SetOptFit(11);
  }
  hist1->SetName("A");
  hist2->SetName("#tau_{r}");
  hist1->Draw();
  gPad->Update();
  // Collect stats of the first histogram
  TPaveStats *tps1 = (TPaveStats*) hist1 -> FindObject("stats");

  tps1->SetTextColor(kBlue);
  tps1->SetLineColor(kBlue);

  tps1->SetX1NDC(0.70);
  tps1->SetX2NDC(0.89);
  tps1->SetY1NDC(0.69);
  tps1->SetY2NDC(0.89);

  double X1 = tps1->GetX1NDC();
  double Y1 = tps1->GetY1NDC();
  double X2 = tps1->GetX2NDC();
  double Y2 = tps1->GetY2NDC();
  cout<<X1<<" "<<X2<<" "<<Y1<<" "<<Y2<<endl;

  hist2->Draw();
  gPad->Update();
    
  TPaveStats *tps2 = (TPaveStats*) hist2 -> FindObject("stats");

  tps2->SetTextColor(kRed);
  tps2->SetLineColor(kRed);

  // Put stat box beneath the first
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC((Y1-0.025)-(Y2-Y1));
  tps2->SetY2NDC(Y1-0.025);
    
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist1->SetLineWidth(2);
  hist1->SetLineColor(kBlue);
  hist2->SetLineColor(kRed);
  hist1->SetLineWidth(3);
  hist2->SetLineWidth(3);
  hist1->SetTitle(title.c_str());
  hist1->Draw();
  hist2->Draw("same");
  tps1->Draw("same");
  tps2->Draw("same");
  c->SaveAs(name.c_str());
  //  hist1->SetDirectory(output);
  delete c;
  return;
}

int main() {

 /* const int nBins = 30; */
 /* const int xMin = -5; */
 /* const int xMax = 5; */

  bool quality = false;//true;
 bool skip = true;
  // Set input and output
  string suffix;
  if(quality && skip) suffix = "_skip18_Q";
  else if(!quality && skip) suffix = "_skip18_noQ";
  else if(quality && !skip) suffix = "_Q";
  else if(!quality && !skip) suffix = "_noQ";
 //  string suffix = "";
  string inputFnameEp = "RootFiles/EpParameters"+suffix+".root";
  string inputFnameLaser = "RootFiles/LaserParameters.root";
  
  string outputFname = "RootFiles/1DStatPlots"+suffix+".root";
    
  // Set input
  TH1D *Ep, *laser;
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  TFile *inputEp = TFile::Open(inputFnameEp.c_str());
  TFile *inputLaser = TFile::Open(inputFnameLaser.c_str());
 
  // Set output
  TFile *output = new TFile(outputFname.c_str(),"RECREATE");


  // string input_Ep_name, input_laser_name, output_name, label;
  double pullValue, fracValue, EpValue, laserValue, EpError, laserError;

  // Book histograms
  TH1D *pullHist = new TH1D("pullHist","pullHist",20,-5,5);
  TH1D *fracHist = new TH1D("fracHist","fracHist",16,-200,200);
  TH1D *pullHistTau = new TH1D("pullHistTau","pullHistTau",20,-5,5);
  TH1D *fracHistTau = new TH1D("fracHistTau","fracHistTau",16,-200,200);
  TH1D *pullHistAmp = new TH1D("pullHistAmp","pullHistAmp",20,-5,5);
  TH1D *fracHistAmp = new TH1D("fracHistAmp","fracHistAmp",16,-200,200);

  int counter = 0;

  // Start hist loop
  for (int iHist(0); iHist < 4; iHist++) {
    
    cout<<"hist : "<<h[iHist]<<endl;
    // Start xtal loop
    for (int xtal(0); xtal < 54; xtal++) {
      //         if (xtal==32) continue;      
      // Get histograms
      Ep = (TH1D*)inputEp->Get(h[iHist].c_str());
      laser = (TH1D*)inputLaser->Get(h[iHist].c_str());
      
      // Get pullValues and errors
      EpValue = Ep->GetBinContent(xtal+1);
      EpError = Ep->GetBinError(xtal+1);
      if (EpValue == 0) continue;
      laserValue = laser->GetBinContent(xtal+1);
      laserError = laser->GetBinError(xtal+1);
      if (laserValue == 0) continue;
      
      // Calculate pull
      pullValue=pull(EpValue,laserValue,EpError,laserError);
      fracValue=frac(laserValue,EpValue);

      // Print
      cout<<"xtal: "<<xtal<<"; pull: "<<pullValue<<"; frac unc: "<<fracValue<<endl;
      pullHist->Fill(pullValue);
      fracHist->Fill(fracValue);
      // Fill
      if(iHist < 2) {
      pullHistTau->Fill(pullValue);
      fracHistTau->Fill(fracValue);
      }
      else if(iHist >= 2) {
      pullHistAmp->Fill(pullValue);
      fracHistAmp->Fill(fracValue);
      }
      counter++;

    }
    
  }
  cout<<"xtals: "<<counter<<endl;
  counter = 0;

  draw(pullHist,output,("Plots/pull_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (Combined);Pull [#sigma];Entries",false);
  draw(fracHist,output,("Plots/frac_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (Combined);(Laser - E/p) / Laser [%];Entries",false);

  draw2(fracHistAmp,fracHistTau,output,("Plots/frac_overlay_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty;(Laser - E/p) / Laser [%];Entries",false);

   draw2(pullHistAmp,pullHistTau,output,("Plots/pull_overlay_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull;Pull [#sigma];Entries",false);
    
  draw(pullHistTau,output,("Plots/pull_tau_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (#tau);Pull [#sigma];Entries",false);
  draw(fracHistTau,output,("Plots/frac_tau_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (#tau);(Laser - E/p) / Laser [%];Entries",false);
   draw(pullHistAmp,output,("Plots/pull_amp_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (A);Pull [#sigma];Entries",false);
  draw(fracHistAmp,output,("Plots/frac_amp_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (A);(Laser - E/p) / Laser [%];Entries",false);
  output->Write(); 

  cout<<outputFname<<" created"<<endl;
  return 0;
}
