// Sam Grant
// Read in-fill gain parameters and output 1D "pull" distribution
// samuel.grant.18@ucl.ac.uk
// May 2019

#include <iostream>
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TDirectory.h"
#include "TPaveStats.h"

using namespace std;

// Define pull
double pull(double EpValue,double laserValue, double EpError, double laserError) {
  double sigma = sqrt(EpError*EpError + laserError*laserError);
  return (laserValue - EpValue) / sigma;
}

// Drawing function
void draw(TH1D *hist1, TH1D *hist2, TFile *output, string name, string title) {

  //  gStyle->SetStatFormat("g");
  
  // Arrange the stat boxes...
  hist1->Draw();
  gPad->Update();

  //Collect stats of the first histogram
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

  hist2->Draw();
  gPad->Update();
  
  //Collect stats of the first histogram
  TPaveStats *tps2 = (TPaveStats*) hist2 -> FindObject("stats");

  tps2->SetTextColor(kRed);
  tps2->SetLineColor(kRed);

  // Put stat box beneath the first
  tps2->SetX1NDC(X1);
  tps2->SetX2NDC(X2);
  tps2->SetY1NDC((Y1-0.025)-(Y2-Y1));
  tps2->SetY2NDC(Y1-0.025);

  // Draw it
  TCanvas *c = new TCanvas("c","c",3000,2000);
  gStyle->SetOptStat(22);
  gPad->Update();

  hist1->SetLineColor(kBlue);
  hist2->SetLineColor(kRed);
  hist1->SetLineWidth(5);
  hist2->SetLineWidth(5);
  hist1->SetTitle(title.c_str());

  hist1->Draw();
  hist2->Draw("same");
  tps1->Draw("same");
  tps2->Draw("same");

  // Save as png
  c->SaveAs(name.c_str());
  
  delete c;

  // Write to ROOT file because why not
  hist1->SetDirectory(output);
  hist2->SetDirectory(output);
  
  return;
}

int main() {

  string inputFnameEp = "RootFiles/EpParameters_Q.root";
  string inputFnameLaser = "RootFiles/LaserParameters.root";
  string outputFname = "RootFiles/Pulls.root";
    
  // Read input
  TH1D *Ep, *laser;
  
  // Names of the histograms being read in
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};

  TFile *inputEp = TFile::Open(inputFnameEp.c_str());
  TFile *inputLaser = TFile::Open(inputFnameLaser.c_str());

  cout<<"Reading... "<<inputFnameEp<<", "<<inputEp<<endl;
  cout<<"Reading... "<<inputFnameLaser<<", "<<inputLaser<<endl;

  // Set output
  TFile *output = new TFile(outputFname.c_str(),"RECREATE");

  double pullValue, EpValue, laserValue, EpError, laserError;
  
  // Book pull histograms
  TH1D *pullHistAmp = new TH1D("#alpha","pullHistAmp",20,-5,5);
  TH1D *pullHistTau = new TH1D("#tau_{r}","pullHistTau",20,-5,5);

  // Start hist loop
  for (int ihist(0); ihist < 4; ihist++) {
    
    // Start xtal loop
    for (int xtal(0); xtal < 54; xtal++) {

      Ep = (TH1D*)inputEp->Get(h[ihist].c_str());
      laser = (TH1D*)inputLaser->Get(h[ihist].c_str());
      
      // Get pullValues and errors
      EpValue = Ep->GetBinContent(xtal+1);
      EpError = Ep->GetBinError(xtal+1);

      if (EpValue == 0) continue;

      laserValue = laser->GetBinContent(xtal+1);
      laserError = laser->GetBinError(xtal+1);

      if (laserValue == 0) continue;
      
      // Calculate pull
      pullValue= pull(EpValue,laserValue,EpError,laserError);
     
      // Print
      cout<<"xtal: "<<xtal<<"; pull: "<<pullValue<<endl;

      if(ihist < 2) {
      pullHistTau->Fill(pullValue);
      }
      else if(ihist >= 2) {
      pullHistAmp->Fill(pullValue);
      }
      else {
	cout<<"**Something strange is happening**"<<endl;
      }

    }
    
  }

  draw(pullHistTau,pullHistAmp,output,"Plots/PullOverlay1D.png","Stn 12 & 18;Pull [#sigma];Entries");

  output->Write(); 

  cout<<outputFname<<" created..."<<endl;
  
  return 0;
}
