// Plot the statistical pull per xtal
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

using namespace std;
// Define pull
double pull(double Ep_content,double laser_content, double Ep_error, double laser_error) {
  double sigma = sqrt(Ep_error*Ep_error + laser_error*laser_error);
  double result = (Ep_content - laser_content) / sigma;
  return result; 
}
// Drawing function
void draw(TH1D *hist, TFile *output, string name, string title) {
  TCanvas *c = new TCanvas();
  hist->GetXaxis()->SetNdivisions(27);
  hist->SetStats(0);
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


  // Get input
  bool full = false;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  bool quality = true;                                                                                               
  string input_Ep_name, input_laser_name, output_name, label;                                                                                       
  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_Q.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "stat_pull_1D"+all+"Q.root";
    label = all+"Q.png";
  }                                                                                                                                                 
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "stat_pull_1D"+all+"noQ.root";
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
  TH1D *pull_tau13 = new TH1D("pull_tau_13","pull_tau_13",54,-0.5,53.5);
  TH1D *pull_tau19 = new TH1D("pull_tau_19","pull_tau_19",54,-0.5,53.5);
  TH1D *pull_amp13 = new TH1D("pull_amp_13","pull_amp_13",54,-0.5,53.5);
  TH1D *pull_amp19 = new TH1D("pull_amp_19","pull_amp_19",54,-0.5,53.5);

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  
  double pull_value;
  double Ep_content;
  double Ep_error;
  double laser_content;
  double laser_error;
  // Start hist loop
  for (int ihist(0); ihist < 4; ihist++) {                                                                                
    cout<<"hist : "<<h[ihist]<<endl;
    // Start xtal loop
    for(int xtal(0); xtal < 54; xtal++) {                                                                                 
      // Get histograms
      Ep = (TH1D*)input_Ep->Get(h[ihist].c_str());
      laser = (TH1D*)input_laser->Get(h[ihist].c_str());                                                                  
      // Get values and errors
      Ep_content = Ep->GetBinContent(xtal+1);
      Ep_error = Ep->GetBinError(xtal+1);
      if (Ep_content == 0) continue;
      laser_content = laser->GetBinContent(xtal+1);
      laser_error = laser->GetBinError(xtal+1);                                                                         
      if(laser_content == 0) continue;                                                              
      // Calculate pull
      pull_value=pull(Ep_content,laser_content,Ep_error,laser_error);                                                   
      // Print                                                                                                 
      cout<<"xtal: "<<xtal<<"; pull: "<<pull_value<<endl;                                                               
      // Fill
      if(ihist==0) pull_tau13->SetBinContent(xtal+1,pull_value);                                                                        
      if(ihist==1) pull_tau19->SetBinContent(xtal+1,pull_value);                                                                        
      if(ihist==2) pull_amp13->SetBinContent(xtal+1,pull_value);                                                                        
      if(ihist==3) pull_amp19->SetBinContent(xtal+1,pull_value);                                                                        
    }                                                                                                                     
  }          
  draw(pull_tau13,output,("pull_tau13_err"+label).c_str(),"Calo 13 | Recovery Time Pull;Crystal Number;Pull [#sigma]");
  draw(pull_tau19,output,("pull_tau19_err"+label).c_str(),"Calo 19 | Recovery Time Pull ;Crystal Number;Pull [#sigma]");
  draw(pull_amp13,output,("pull_amp13_err"+label).c_str(),"Calo 13 | Amplitude Pull;Crystal Number;Pull [#sigma]");
  draw(pull_amp19,output,("pull_amp19_err"+label).c_str(),"Calo 19 | Amplitude Pull;Crystal Number;Pull [#sigma]");

  output->Write();
  output->Close();

  return 0;
}
