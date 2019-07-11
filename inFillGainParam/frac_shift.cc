// Plot the fractional uncertainty per xtal
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
// Define fractional shift
double frac_shift(double laser_value, double Ep_value) {
    // Fractional shift
    double result = (laser_value - Ep_value) / laser_value;
    return result;
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title) {
  TCanvas *c = new TCanvas("c","c",1500,1000);
  hist->GetXaxis()->SetNdivisions(27);
  hist->SetStats(0);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  hist->SetTitle(title.c_str());
  hist->SetMarkerStyle(kStar);
  hist->SetMarkerSize(3);
  hist->Draw();
  gPad->SetGrid();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}

int main() {
  string cut[4] = {"Q","statCut","errCut","chiCut"};
  for (int icut(0); icut < 1; icut++) {

  // Get input
  bool full = true;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  bool quality = false;
  string input_Ep_name, input_laser_name, output_name, label;
  
  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_veryEarly_"+cut[icut]+".root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "frac_shift"+all+"_veryEarly_"+cut[icut]+".root";
    label = all+cut[icut]+".png";
  }
  
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_veryEarly_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "frac_shift"+all+"veryEarly_noQ.root";
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
  TH1D *tau13 = new TH1D("tau_13","tau_13",54,-0.5,53.5);
  TH1D *tau19 = new TH1D("tau_19","tau_19",54,-0.5,53.5);
  TH1D *amp13 = new TH1D("amp_13","amp_13",54,-0.5,53.5);
  TH1D *amp19 = new TH1D("amp_19","amp_19",54,-0.5,53.5);

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  
  double fracValue, Ep_content, laser_content;
  // Start hist loop
  for (int ihist(0); ihist < 4; ihist++) {
    
    cout<<"hist : "<<h[ihist]<<endl;
    // Start xtal loop
    for(int xtal(0); xtal < 54; xtal++) {
      
      // Get histograms
      Ep = (TH1D*)input_Ep->Get(h[ihist].c_str());
      laser = (TH1D*)input_laser->Get(h[ihist].c_str());
      
      // Get fracValues and errors
      Ep_content = Ep->GetBinContent(xtal+1);
      if (Ep_content == 0) continue;
      laser_content = laser->GetBinContent(xtal+1);
      if(laser_content == 0) continue;
      
      // Calculate pull
      fracValue=frac_shift(laser_content,Ep_content);
      
      // Print
      
      cout<<"xtal: "<<xtal<<"; frac: "<<fracValue<<endl;
      
      // Fill
   
      if(ihist==0) tau13->SetBinContent(xtal+1,fracValue);
      
      if(ihist==1) tau19->SetBinContent(xtal+1,fracValue);
      
      if(ihist==2) amp13->SetBinContent(xtal+1,fracValue);
      
      if(ihist==3) amp19->SetBinContent(xtal+1,fracValue);
      
    }
    
  }
  
  draw(tau13,output,("frac_tau13_err"+label).c_str(),"Calo 13 | Recovery Time Fractional Uncertainty;Crystal Number;Fractional Uncertainty");
  
  draw(tau19,output,("frac_tau19_err"+label).c_str(),"Calo 19 | Recovery Time Fractional Uncertainty ;Crystal Number;Fractional Uncertainty");
  
  draw(amp13,output,("frac_amp13_err"+label).c_str(),"Calo 13 | Amplitude Fractional Uncertainty;Crystal Number;Fractional Uncertainty");
  
  draw(amp19,output,("frac_amp19_err"+label).c_str(),"Calo 19 | Amplitude Fractional Uncertainty;Crystal Number;Fractional Uncertainty");
  
  cout<<"\n--------------------\n"<<output_name<<" created"<<endl;
  output->Write();
  output->Close();
  }
  return 0;
}
