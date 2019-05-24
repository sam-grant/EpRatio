// Preliminary fitting code for gain distributions 
// Sam Grant - April 2019
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

double gain_sag(double *x, double *par) {
  
  double time = x[0];
  double N0 = par[0]; // Overall normalisation
  double A = par[1];//0.5; // Amplitude of the sag;
  double tau = par[2];//12; // Time constant of the rising exponential

  double N  = N0 * ( 1 - A * ( exp( - time / tau ) ) );
  return N;
  
}

int main() {

  bool save = false;//true;
  string in;
  
   // output_fname = "taus_normalised_xtals_boards2.root";
  string input_fname = "../makePlots2/fits_time_normalised_xtal.root";
  string output_fname = "taus_time_normalised_xtal2_testing.root";
  string output_fname2 = "inFillGainParams_Sam2.root";

  TFile *input = TFile::Open(input_fname.c_str());
  cout << "Reading ... " << input_fname << endl;
  
  TFile *output = new TFile(output_fname.c_str(), "recreate");
  TFile *output2 = new TFile(output_fname2.c_str(), "recreate");
  

  TH1D *taus13 = new TH1D("tau 13","Calo 13",64,0,16);
  TH1D *taus19 = new TH1D("tau 19","Calo 19",64,0,16);
  TH1D *amps13 = new TH1D("amp 13","Calo 13",50,0,0.05);
  TH1D *amps19 = new TH1D("amp 19","Calo 19",50,0,0.05);
  //station loop
  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {
    // board loop
    //  for (int brd = 1 ; brd < 3 ; brd++ ) {
      // cut region region
    // for (int cut = 0 ; cut < 4 ; cut++ ) {

    //	if ( cut != 1 ) continue; // Select 60%
	  cout<<"Stn "<<stn<<endl;
	for (int xtal = 0 ; xtal < 54 ; xtal++) {
	  
	 
	  const int earlyTime = 4.2*50;
	  // Fit function with 4 paramters 
	  TF1 *f1 = new TF1("f1", gain_sag, 0, earlyTime, 3);//earlyTime, 3);
	  f1->SetNpx(10000);

	  string h = "St"+to_string(stn)+"_fit_Ep_vs_t_early_"+to_string(xtal);
	  TH1D *t_early = (TH1D*)input->Get(h.c_str());
	  if(t_early == 0) continue;
 
	  //Set parameters
	  //f1->SetParameter(1,0.0005);//,0.001); 
	  //  f1->SetParLimits(1,0.00001,0.0001);
	  // f1->SetParameter(1,0.001);//,0.001); ]
	
	  f1->SetParameter(2,10);
	  f1->SetParName(0,"G_{0}");
	  f1->SetParName(1,"A");
	  f1->SetParName(2,"#tau_{r}");
	  // Perform fit
	  t_early->Fit(f1,"QM");

	  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
	  t_early->SetStats(1);
	  gStyle->SetOptStat(0);
	  gStyle->SetOptFit();
	  t_early->SetLineWidth(2);

	  gStyle->SetStatX(0.49);
	  gStyle->SetStatY(0.89);
	  t_early->GetXaxis()->SetTitle("Fill Time [#mus]");
	  t_early->GetYaxis()->SetRangeUser(0.99,1.01);
	  t_early->GetXaxis()->SetRangeUser(0,4.2*50);
	  t_early->Draw();
	  t_early->SetDirectory(output);
	  
	  if (save){
	    c1->SaveAs((h+"_testing.png").c_str());
	  }
	  delete c1;
	 
	  if(stn==13){
	    taus13->Fill(f1->GetParameter(2));
	    amps13->Fill(f1->GetParameter(1));
	  }
	  if(stn==19){
	    taus19->Fill(f1->GetParameter(2));
	    amps19->Fill(f1->GetParameter(1));
	  }

	  cout<<xtal<<","<<f1->GetParameter(1)<<","<<f1->GetParameter(2)<<endl;
    }
  }

  TCanvas *c2 = new TCanvas();//"c2","c2",2000,1000);
  taus13->SetLineColor(kOrange+2);
  taus19->SetLineColor(kBlue+2);
  taus13->SetLineWidth(2);
  taus19->SetLineWidth(2);
  taus13->Draw();
  taus19->Draw("same");
  c2->BuildLegend(0.79,0.79,0.89,0.89);
  taus13->SetTitle("Recovery times;In Fill Time [#mus];N");
  taus13->SetDirectory(output2);
  taus19->SetDirectory(output2);
  c2->SaveAs("tau_sam.png");
  delete c2;

  TCanvas *c3 = new TCanvas();//"c3","c3",2000,1000);
  amps13->SetLineColor(kOrange+2);
  amps19->SetLineColor(kBlue+2);
  amps13->SetLineWidth(2);
  amps19->SetLineWidth(2);
  amps13->Draw();
  amps19->Draw("same");
  c3->BuildLegend(0.79,0.79,0.89,0.89);
  amps13->SetTitle("Amplitudes;Amplitude;N");
  amps13->SetDirectory(output2);
  amps19->SetDirectory(output2);
 
  c3->SaveAs("amps_sam.png");
  delete c3;
	  
  output->Write();
  output->Close();
  output2->Write();
  output2->Close();
  input->Close();
  
  return 0; 
}



