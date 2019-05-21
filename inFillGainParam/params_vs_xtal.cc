// Extract differences and plots per xtal
// Also overlay the 1D guys


// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include <fstream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAttMarker.h"

using namespace std;

double meanBinContent(TH1D *hist) {

  double binCont;
  double sum;
  double result; 
  for (int xtal = 0; xtal<54; xtal++) {

    binCont = hist->GetBinContent(xtal+1);
    sum = sum + binCont; 
  }
  //double result = sum/54;
  return result = sum/54;
  delete hist;
}

void difference(TH1D *laser, TH1D *sam, TFile *output, string title, string fname) {
  // Add function doesn't ignore empty bins 
  //  laser->Add(sam,-1);
  // laser->Add(sam,-1);
    // need to ignore empty bins, this now biases means
  // how to fix??
   TH1D *h = new TH1D("h","h",54,-0.5,53.5);
  double value1, error1, value2, diff;
  for (int i = 0; i < 54; i++) {
    value1 = sam->GetBinContent(i+1);
    error1 = sam->GetBinError(i+1);
    cout << error1 << endl;
    if (value1 == 0) continue;
    value2 = laser->GetBinContent(i+1);
    diff = value2-value1;
    if (diff == 0) continue;
    
    cout << i <<" "<<value1 <<" "<< value2 <<" "<<diff<<endl;
   
    h->SetBinContent(i+1,diff);
  }
  
  TCanvas *c = new TCanvas();
  
  h->SetTitle(title.c_str());//"Calo 13 | #Delta#tau;Crytal Number;#Delta#tau [#mus]");
  h->SetStats(false);
  // h->SetMarkerColor(kBlack);
  //  h->SetLineWidth(0);
  //  h->SetMarkerStyle(kStar);
  h->Draw("P0");

  //  output->Write();
  c->SaveAs(fname.c_str());//"tau13_diff.png");
  h->SetDirectory(output);

  delete c;
  // delete h;

}

void one_dim(TFile *laser, TFile *sam, string name, string title, string fname) {

  TCanvas *c = new TCanvas();
  
  TH1D *h1 = (TH1D*)laser->Get(name.c_str());//"tau 13");
  TH1D *h2 = (TH1D*)sam->Get(name.c_str());//"tau 13");
  
  h1->SetTitle("Laser");
  h2->SetTitle("E/p Ratio");
  h1->SetStats(0);
  h1->SetLineColor(kRed);
  h2->SetLineColor(kGreen-3);
  h1->Draw();
  h2->Draw("same");
  c->BuildLegend(0.79,0.79,0.89,0.89);
  h1->SetTitle(title.c_str());//"Calo 13 | Recovery Times;In Fill Time [#mus];Entries"); 
  c->SaveAs(fname.c_str());//"calo13_taus.png");
  delete c;
  delete h1;
  delete h2;
  
  return;
}

int main() {

  // open output csv file 
    ofstream textFile;
   textFile.open("delta_tau_and_amp.csv");

   // Output
  TFile *output = new TFile("comparison.root","RECREATE");

  
  //All inputs
  TFile *laser_xtal = TFile::Open("inFillGainParams_laser_xtal.root");
  TFile *sam_xtal = TFile::Open("inFillGainParams_sam_xtal.root");
  TFile *laser_1d = TFile::Open("inFillGainParams_laser.root");
  TFile *sam_1d = TFile::Open("inFillGainParams_Sam2.root");
 
  TH1D *tau13_laser = (TH1D*)laser_xtal->Get("tau 13");
  TH1D *tau13_sam = (TH1D*)sam_xtal->Get("tau 13");
  TH1D *tau19_laser = (TH1D*)laser_xtal->Get("tau 19");
  TH1D *tau19_sam = (TH1D*)sam_xtal->Get("tau 19");
  
  TH1D *amp13_laser = (TH1D*)laser_xtal->Get("amp 13");
  TH1D *amp13_sam = (TH1D*)sam_xtal->Get("amp 13");
  TH1D *amp19_laser = (TH1D*)laser_xtal->Get("amp 19");
  TH1D *amp19_sam = (TH1D*)sam_xtal->Get("amp 19");

  difference(tau13_laser,tau13_sam,output,"Calo 13 | #Delta#tau;Crytal Number;#Delta#tau [#mus]","tau13_diff.png");
  difference(tau19_laser,tau19_sam,output,"Calo 19 | #Delta#tau;Crytal Number;#Delta#tau [#mus]","tau19_diff.png");
  difference(amp13_laser,amp13_sam,output,"Calo 13 | #DeltaA;Crytal Number;#DeltaA","amp13_diff.png");
  difference(amp13_laser,amp13_sam,output,"Calo 19 | #DeltaA;Crytal Number;#DeltaA","amp19_diff.png");

  one_dim(laser_1d,sam_1d,"tau 13","Calo 13 | Recovery Times;In Fill Time [#mus];Entries","calo13_taus.png");
  one_dim(laser_1d,sam_1d,"tau 19","Calo 19 | Recovery Times;In Fill Time [#mus];Entries","calo19_taus.png");
  one_dim(laser_1d,sam_1d,"amp 13","Calo 13 | Amplitudes;Amplitude;Entries","calo13_amps.png");
  one_dim(laser_1d,sam_1d,"amp 19","Calo 19 | Amplitudes;Amplitude;Entries","calo13_amps.png");

  //////////////////////////////////
  cout <<"**************RESULT**************"<<endl;
  cout <<"mean difference tau 13 " << meanBinContent(tau13_laser) <<" us" <<endl;
  cout <<"mean tau 19 " << meanBinContent(tau19_laser) <<" us"<<endl;
  cout <<"mean amp 13 " << meanBinContent(amp13_laser) << endl;
  cout <<"mean amp 19 " << meanBinContent(amp19_laser) << endl;

  output->Write();
  output->Close();
  //delete output;
  return 0;
}
