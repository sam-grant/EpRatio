// Make plots of the fluctuation, combined between both stations
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
#include "TGraphErrors.h"

using namespace std;

// Fluctation is basically the fractional error
double frac_val(TH1D *laser_hist, TH1D *ep_hist, int iter) {
    double laser_value = laser_hist->GetBinContent(iter+1);
    double ep_value = ep_hist->GetBinContent(iter+1);
    double laser_error = laser_hist->GetBinError(iter+1);
    double ep_error = ep_hist->GetBinError(iter+1);
    // Fractional shift
    double result = (laser_value - ep_value) / laser_value;
    return result;
}

void draw(TH1D *hist, string name, TFile *output) {
  //  TH1D *hist_clone = (TH1D*)hist->Clone("hist_clone");
  // hist_clone->Fill(value);  
  TCanvas *c = new TCanvas("c","c",1500,1000);
  //  gStyle->SetOptStat(112211);
  hist->SetStats(0);//111111);
  hist->SetLineWidth(2);
  hist->SetLineColor(kBlack);
  //hist_clone->SetTitle(title.c_str());
  hist->Draw();
  gPad->SetGrid();
  hist->SetDirectory(output);
  //  gPad->SetGrid();
  c->SaveAs(name.c_str());
  //  delete hist_clone;
  delete c;
  return;
}

int main() {

  string cut[4] = {"Q","statCut","errCut","chiCut"};
  for (int icut(0); icut < 4; icut++) {
    
    bool full = true;
    
  bool quality = true;
  string all;
  if(full) all = "_full_";
  else if(!full) all = "_";
  string input_Ep_name, input_laser_name, output_name, label;

  if(quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_"+cut[icut]+".root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "fluc"+all+cut[icut]+".root";
    label = all+cut[icut]+".png";
  }
  else if(!quality) {
    input_Ep_name = "inFillGainParams_Ep_xtal_errors_noQ.root";
    input_laser_name = "inFillGainParams_laser_xtal_errors"+all+"Q.root";
    output_name = "fluc"+all+"noQ.root";
    label = all+"noQ.png";
  }
  // Set output                                                                                    
  TFile *output = new TFile(output_name.c_str(),"RECREATE");
  
  TFile *laser_input = TFile::Open(input_laser_name.c_str());
  TFile *Ep_input = TFile::Open(input_Ep_name.c_str());
  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};
  string name[2] = {"fluc_tau.png","fluc_amp.png"};//{"fluc_tau1D_13.png","fluc_tau1D_19.png","fluc_amp1D_13.png","fluc_amp1D_19.png"};
  //  string title[2] = {"Recovery Time: Fractional Shift per Crystal;Fractional Shift;Entries","Amplitude Fractional Shift per Crystal;Fractional Shift;Entries"};//{"Calo 13 | Recovery Time Fluctuation;Fluctuation;Entries","Calo 19 | Recovery Time Fluctuation;Fluctuation;Entries","Calo 13 | Amplitude Fluctuation;Fluctuation;Entries","Calo 19 | Amplitude Fluctuation;Fluctuation;Entries"};
  string title[4] = {"Calo 13 | Recovery Time: Fractional Shift per Crystal;Crystal Number;Fractional Shift","Calo 19 | Recovery Time: Fractional Shift per Crystal;Crystal Number;Fractional Shift","Calo 13 | Amplitude: Fractional Shift per Crystal;Crystal Number;Fractional Shift","Calo 19 | Amplitude: Fractional Shift per Crystal;Crystal Number;Fractional Shift"};

  // book historgrams
  // TH1D *fluc = new TH1D("fluc","fluc",54,-0.5,53.5);

  //  TH1D *tau_fluc = new TH1D("tau_fluc","tau_fluc",40,-5,3);//54,-0.5,53.5);
  //  TH1D *amp_fluc = new TH1D("amp_fluc","amp_fluc",15,-3,3);//54,-0.5,53.5);
  TH1D *tau13_fluc = new TH1D("tau13_fluc","tau13_fluc",54,-0.5,53.5);
  TH1D *amp13_fluc = new TH1D("amp13_fluc","amp13_fluc",54,-0.5,53.5);
  TH1D *tau19_fluc = new TH1D("tau19_fluc","tau19_fluc",54,-0.5,53.5);
  TH1D *amp19_fluc = new TH1D("amp19_fluc","amp19_fluc",54,-0.5,53.5);
  TH1D *laser_hist;
  TH1D *Ep_hist;
  double value;
  double error;

  for(int i(0); i<4; i++) {

    laser_hist = (TH1D*)laser_input->Get(h[i].c_str());

    Ep_hist = (TH1D*)Ep_input->Get(h[i].c_str());
    //    if(i!=0)continue;
    for (int xtal(0); xtal<54; xtal++) {

      //  value = fluc_val(laser_hist,Ep_hist,xtal);
      // Cut out station 19
      //      if((i==0 || i==1)&& xtal == 23) continue;
      //      error = fluc_err(laser_hist,Ep_hist,xtal);
      value = frac_val(laser_hist,Ep_hist,xtal);
      if (value == 1) continue; // AKA, the Ep value is zero
      //      if( fabs(error) > fabs(value))continue;
      cout << i << " " << xtal << " " << value << endl;//"+/-" << error << " " << (error/value) * 100 <<endl;


      if(i==0) {
	tau13_fluc->SetBinContent(xtal+1,value);//,xtal+1);//*(1/fabs(error)));
	tau13_fluc->SetBinError(xtal+1,error);//,xtal+1);
	tau13_fluc->SetTitle(title[i].c_str());
      }
      if(i==1){
	tau19_fluc->SetBinContent(xtal+1,value);//,xtal+1);//*(1/fabs(error)));
	tau19_fluc->SetBinError(xtal+1,error);//,xtal+1);
		tau19_fluc->SetTitle(title[i].c_str());
      }
       if(i==2) {
	amp13_fluc->SetBinContent(xtal+1,value);//,xtal+1);//*(1/fabs(error)));
	amp13_fluc->SetBinError(xtal+1,error);//,xtal+1);
	amp13_fluc->SetTitle(title[i].c_str());
      }
       if(i==3) {
	amp19_fluc->SetBinContent(xtal+1,value);//,xtal+1);//*(1/fabs(error)));
	amp19_fluc->SetBinError(xtal+1,error);//,xtal+1);
       	amp19_fluc->SetTitle(title[i].c_str());
      }	
 
      //      fluc->SetBinWidth(error);
    }

  }	  


  // overlay
  draw(tau13_fluc,"tau13_frac_xtal"+label,output);
  draw(amp13_fluc,"amp13_frac_xtal"+label,output);

  draw(tau19_fluc,"tau19_frac_xtal"+label,output);
  draw(amp19_fluc,"amp19_frac_xtal"+label,output);
  // for(int i(2); i<4; i++) {

//   laser_hist = (TH1D*)laser_input->Get(h[i].c_str());

//   Ep_hist = (TH1D*)Ep_input->Get(h[i].c_str());

//   fluctuation();
 

// fluctuation(fluc,laser_amp13,Ep_amp13,title[1],name[1]);

  laser_input->Close();

  Ep_input->Close();

 cout << "\n-----------------\nCreated : "<<output_name<<endl;
  }
return 0;
}
 
