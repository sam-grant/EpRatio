// Get the abs statisical pull betwen laser and E/p
// Some of the messiest code ever written

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"

using namespace std;

double pull(double sam_content,double laser_content, double sam_error, double laser_error) {
  double sigma = sqrt(sam_error*sam_error + laser_error*laser_error);
  double result = (sam_content - laser_content)/sigma;
  // result = sqrt(result*result);
  return result; 
}

void draw(TH1D *hist, TFile *output, string name, string title) {
  TCanvas *c = new TCanvas();
  hist->SetStats(0);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  // hist->SetLineFill(0);
  hist->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGrid();
  c->SaveAs(name.c_str());
  hist->SetDirectory(output);
  delete c;
  return;
}


int main() {
  
  string input_Ep_name = "inFillGainParams_sam_xtal_errors_Q.root";
  string input_laser_name = "inFillGainParams_laser_xtal_errors_Q.root";

  TFile *input_Ep = TFile::Open(input_Ep_name.c_str());
  TFile *input_laser = TFile::Open(input_laser_name.c_str());

  // Set output
  TFile *output = new TFile("stat_pull.root","RECREATE");

   // book historgrams 
  TH1D *pull_tau13 = new TH1D("pull_tau_13","pull_tau_13",54,-0.5,53.5);
  TH1D *pull_tau19 = new TH1D("pull_tau_19","pull_tau_19",54,-0.5,53.5);
  TH1D *pull_amp13 = new TH1D("pull_amp_13","pull_amp_13",54,-0.5,53.5);
  TH1D *pull_amp19 = new TH1D("pull_amp_19","pull_amp_19",54,-0.5,53.5);
  pull_tau13->GetXaxis()->SetNdivisions(27);
  pull_tau19->GetXaxis()->SetNdivisions(27);
  pull_amp13->GetXaxis()->SetNdivisions(27);
  pull_amp19->GetXaxis()->SetNdivisions(27);

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};

  TH1D *Ep;
  TH1D *laser;

  double pull_value;
  double Ep_content;
  double Ep_error;
  double laser_content;
  double laser_error;
  


for (int ihist(0); ihist < 4; ihist++) {                                                                                
    cout<<"hist : "<<h[ihist]<<endl;                                                                                      
    for(int xtal(0); xtal < 54; xtal++) {                                                                                 
                                                                                                                          
      Ep = (TH1D*)input_Ep->Get(h[ihist].c_str());                                                                        
      laser = (TH1D*)input_laser->Get(h[ihist].c_str());                                                                  
                                                                                                                          
      Ep_content = Ep->GetBinContent(xtal+1);                                                                             
        Ep_error = Ep->GetBinError(xtal+1);                                                                               
        if (Ep_error == 0 || Ep_content == 0) continue;                                                                   
                                                                                                                          
        laser_content = laser->GetBinContent(xtal+1);                                                                     
        laser_error = laser->GetBinError(xtal+1);                                                                         
        if(laser_error == 0 || laser_content == 0) continue;                                                              
                                                                                                                          
                                                                                                                          
        //   if(laser_error > factor*laser_content || Ep_error >  factor*Ep_content) continue;                            
        pull_value=pull(Ep_content,laser_content,Ep_error,laser_error);                                                   
                                                                                                                          
        cout<<"xtal: "<<xtal<<"; pull: "<<pull_value<<endl;                                                               
        if(ihist==0) pull_tau13->SetBinContent(xtal+1,pull_value);                                                                        
        if(ihist==1) pull_tau19->SetBinContent(xtal+1,pull_value);                                                                        
        if(ihist==2) pull_amp13->SetBinContent(xtal+1,pull_value);                                                                        
        if(ihist==3) pull_amp19->SetBinContent(xtal+1,pull_value);                                                                        
          //      }                                                                                                       
    }                                                                                                                     
  }          



 
    
  draw(pull_tau13,output,"pull_tau13_err.png","Calo 13 | Recovery Time Pull;Crystal Number;Pull [#sigma]");
  draw(pull_tau19,output,"pull_tau19_err.png","Calo 19 | Recovery Time Pull ;Crystal Number;Pull [#sigma]");
  draw(pull_amp13,output,"pull_amp13_err.png","Calo 13 | Amplitude Pull;Crystal Number;Pull [#sigma]");
  draw(pull_amp19,output,"pull_amp19_err.png","Calo 19 | Amplitude Pull;Crystal Number;Pull [#sigma]");


  ///////////////////////////////////////////////////////////////

  output->Write();
  output->Close();

  return 0;
}
