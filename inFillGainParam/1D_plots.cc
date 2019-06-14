// Generate 1D plots of E/p and laser 
// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"


using namespace std;

void draw(TH1D *hist1, TH1D *hist2, string title, string fname) {

  TCanvas *c = new TCanvas();
  hist1->SetTitle("Laser");
  hist2->SetTitle("E/p Ratio");
  hist1->SetStats(0);
  //  hist1->SetOptStat(11111);
  // hist1->SetTitle(title.c_str());
  hist1->SetLineColor(kRed);
  hist2->SetLineColor(kGreen-3);
  hist1->SetLineWidth(2);
  hist2->SetLineWidth(2);
  hist1->Draw();
  hist2->Draw("same");
  c->BuildLegend(0.79,0.79,0.89,0.89);
  hist1->SetTitle(title.c_str());
  c->SaveAs(fname.c_str());
  delete c;

  return;
}


int main() {

  bool save = false;//true;
  string in;
  
   // output_fname = "taus_normalised_xtals_boards2.root";
  string input_sam = "inFillGainParams_Ep_xtal_errors_noQ.root";
  string input_laser = "inFillGainParams_laser_xtal_errors_Q.root";

  TFile *sam = TFile::Open(input_sam.c_str());
  TFile *laser = TFile::Open(input_laser.c_str());
  
  cout << "Reading ... " << endl;
  

  
  // Book histograms
  TH1D *sam_tau13 = new TH1D("tau_13_ep","Calo 13",64,0,16);
  TH1D *sam_tau19 = new TH1D("tau_19_ep","Calo 19",64,0,16);
  TH1D *sam_amp13 = new TH1D("amp_13_ep","Calo 13",50,0,0.05);
  TH1D *sam_amp19 = new TH1D("amp_19_ep","Calo 19",50,0,0.05);

  TH1D *laser_tau13 = new TH1D("tau_13_l","Calo 13",64,0,16);
  TH1D *laser_tau19 = new TH1D("tau_19_l","Calo 19",64,0,16);
  TH1D *laser_amp13 = new TH1D("amp_13_l","Calo 13",50,0,0.05);
  TH1D *laser_amp19 = new TH1D("amp_19_l","Calo 19",50,0,0.05);

  TH1D *sam1 = (TH1D*)sam->Get("tau_13");
  TH1D *sam2 = (TH1D*)sam->Get("tau_19");
  TH1D *sam3 = (TH1D*)sam->Get("amp_13");
  TH1D *sam4 = (TH1D*)sam->Get("amp_19");

  TH1D *laser1 = (TH1D*)laser->Get("tau_13");
  TH1D *laser2 = (TH1D*)laser->Get("tau_19");
  TH1D *laser3 = (TH1D*)laser->Get("amp_13");
  TH1D *laser4 = (TH1D*)laser->Get("amp_19");
  
  //station loop
  double value;
  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {


	  // Crystal loop
	for (int xtal = 0 ; xtal < 54 ; xtal++) {
	 
      
	  if(stn==13){
	    value = sam1->GetBinContent(xtal+1);
	    if(value == 0) continue;
	    sam_tau13->Fill(value);//sam1->GetBinContent(xtal+1));
	    sam_amp13->Fill(sam3->GetBinContent(xtal+1));
	    laser_tau13->Fill(laser1->GetBinContent(xtal+1));
	    laser_amp13->Fill(laser3->GetBinContent(xtal+1));
	  }
	  
	  if(stn==19){
	    sam_tau19->Fill(sam2->GetBinContent(xtal+1));
	    sam_amp19->Fill(sam4->GetBinContent(xtal+1));
	    laser_tau19->Fill(laser2->GetBinContent(xtal+1));
	    laser_amp19->Fill(laser4->GetBinContent(xtal+1));
	  }
	 
	}
  }

  draw(laser_tau13,sam_tau13,"Calo 13 | Recovery Times;In Fill Time [#mus];Entries","tau13_compare_1D.png");
  draw(laser_tau19,sam_tau19,"Calo 19 | Recovery Times;In Fill Time [#mus];Entries","tau19_compare_1D.png");

  draw(laser_amp13,sam_amp13,"Calo 13 | Amplitudes;Amplitude;Entries","amp13_compare_1D.png");
  draw(laser_amp19,sam_amp19,"Calo 19 | Amplitudes;Amplitude;Entries","amp19_compare_1D.png");
 
  sam->Close();
  laser->Close();
  return 0; 
}



