// Plot the fractional uncertainty in 1D
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
double pull(double Ep_content,double laser_content, double Ep_error, double las\
er_error) {
  double sigma = sqrt(Ep_error*Ep_error + laser_error*laser_error);
  double result = (Ep_content - laser_content) / sigma;
  return result;
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title) {
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist->SetName("Pull");
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
  string cut[4] = {"Q","statCut","errCut","chiCut"};
  for (int icut(0); icut < 4; icut++) {

  // Get input
  bool full = true;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  bool quality = true;//false;
  string input_Ep_name, input_laser_name, output_name, label;
  
  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_"+cut[icut]+".root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "pull_shift_1D"+all+""+cut[icut]+".root";
    label = all+cut[icut]+".png";
  }
  
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "pull_shift_1D"+all+"noQ.root";
    label = all+"noQ.png";
  }  

  TFile *input_Ep = TFile::Open(input_Ep_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());
  // Book input histograms
  TH1D *Ep;
  TH1D *laser;
  // Set output
  TFile *output = new TFile(output_name.c_str(),"RECREATE");
  // Book histograms
  int nBins = 12;
  TH1D *hist = new TH1D("hist","hist",nBins,-3,3);
 
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  
  double pullValue, Ep_content, laser_content, Ep_error, laser_error;
  // Start hist loop
  for (int ihist(0); ihist < 4; ihist++) {
    
    cout<<"hist : "<<h[ihist]<<endl;
    // Start xtal loop
    for(int xtal(0); xtal < 54; xtal++) {
      
      // Get histograms
      Ep = (TH1D*)input_Ep->Get(h[ihist].c_str());
      laser = (TH1D*)input_laser->Get(h[ihist].c_str());
      
      // Get pullValues and errors
      Ep_content = Ep->GetBinContent(xtal+1);
      Ep_error = Ep->GetBinError(xtal+1);
      if (Ep_content == 0) continue;
      laser_content = laser->GetBinContent(xtal+1);
      laser_error = laser->GetBinError(xtal+1);
      if(laser_content == 0) continue;
      
      // Calculate pull
      pullValue=pull(Ep_content,laser_content,Ep_error,laser_error);
      
      // Print
      
      cout<<"xtal: "<<xtal<<"; pull: "<<pullValue<<endl;
      
      // Fill
   
      hist->Fill(pullValue);
      
    }
    
  }
  
 
    draw(hist,output,("pull_shift_1D"+label).c_str(),"Calos 13 & 19 | Pull (All Parameters);Fractional Uncertainty;Entries");
  
  cout<<"\n--------------------\n"<<output_name<<" created"<<endl;
  output->Write();
  output->Close();

  }

  return 0;
}
