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
  return result;
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title, bool fit) {
  gStyle->SetOptStat(112211);
  if(fit) {
    // Define the gaussian function
    TF1 *gFunc = new TF1("gFunc", "gaus");//,-2,2);
    hist->Fit(gFunc);

    gStyle->SetOptFit(11);
  }
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist->SetName("Combined");
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGrid();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}

int main() {

 const int nBins = 20;
 const int xMin = -5;
 const int xMax = 5;

 bool quality = true;
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
  TH1D *pullHist = new TH1D("pullHist","pullHist",nBins,xMin,xMax);
  TH1D *fracHist = new TH1D("fracHist","fracHist",nBins,xMin,xMax);
  TH1D *pullHistTau = new TH1D("pullHistTau","pullHistTau",nBins,xMin,xMax);
  TH1D *fracHistTau = new TH1D("fracHistTau","fracHistTau",nBins,xMin,xMax);
  TH1D *pullHistAmp = new TH1D("pullHistAmp","pullHistAmp",nBins,xMin,xMax);
  TH1D *fracHistAmp = new TH1D("fracHistAmp","fracHistAmp",nBins,xMin,xMax);

  int counter = 0;

  // Start hist loop
  for (int iHist(0); iHist < 4; iHist++) {
    
    cout<<"hist : "<<h[iHist]<<endl;
    // Start xtal loop
    for (int xtal(0); xtal < 54; xtal++) {
      //      if (xtal==23) continue;      
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

      /* pullHistAmp->GetXaxis()->SetLimits(-300,300); */
      /* pullHistTau->GetXaxis()->SetLimits(-300,300); */
      /* fracHistAmp->GetXaxis()->SetLimits(-300,300); */
      /* fracHistAmp->GetXaxis()->SetLimits(-300,300); */
    }
    
  }
  //  fracHistTau->GetXaxis()->SetLimits(-500,500);
  //fracHistAmp->GetXaxis()->SetLimits(-500,500);
  //  fracHistTau->
  
  cout<<"xtals: "<<counter<<endl;
  counter = 0;
    draw(pullHist,output,("Plots/pull_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (Combined);Pull [#sigma];Entries",false);
  draw(fracHist,output,("Plots/frac_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (Combined);Laser - E/p / Laser;Entries",false);

  draw(pullHistTau,output,("Plots/pull_tau_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (#tau);Pull [#sigma];Entries",false);
  draw(fracHistTau,output,("Plots/frac_tau_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (#tau);Laser - E/p / Laser;Entries",false);
   draw(pullHistAmp,output,("Plots/pull_amp_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Pull (A);Pull [#sigma];Entries",false);
  draw(fracHistAmp,output,("Plots/frac_amp_1D"+suffix+".png").c_str(),"Calos 13 & 19 | Percentage Uncertainty (A);Laser - E/p / Laser;Entries",false);
  output->Write(); 

  cout<<outputFname<<" created"<<endl;
  return 0;
}
