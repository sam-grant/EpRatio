// Preliminary fitting code for gain distributions 
// Sam Grant - April 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"

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

  bool save = true;
  bool scaled = false;
  string in;

  cout << "Scaled? Yes (y) or no (n): ";
  cin >> in;

  if (in == "y") { scaled = true; }
  else if (in == "n" ) { scaled = false; }
  else {
    cout << "Error, try again" << endl;
    return 0;
  }
  
  string input_fname;
  string output_fname;
  
  if (scaled) {
    input_fname = "../makePlots/fits_t_by_xtal_normalised_brd2.root";
    output_fname = "taus_normalised_xtals_boards2.root";
  }
  else if ( !scaled ) {
    input_fname = "../makePlots/fits_t_by_xtal_unnormalised_brd2.root";
    output_fname = "taus_unnormalised_xtals_boards2.root";  }

  TFile *input = TFile::Open(input_fname.c_str());
  cout << "Reading ... " << input_fname << endl;
  
  TFile *output = new TFile(output_fname.c_str(), "recreate");
  //station loop
  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {
    // board loop
    for (int brd = 1 ; brd < 3 ; brd++ ) {
      // crystal fiducial region
      for (int fidXtal = 0 ; fidXtal < 2 ; fidXtal++ ) {
	
	const int earlyTime = 4.2*50;
	// Fit function with 4 paramters 
	TF1 *f1 = new TF1("f1", gain_sag, 0, earlyTime, 3);//earlyTime, 3);
	f1->SetNpx(10000);

	string h = "St"+to_string(stn)+"_fit_Ep_vs_t_early_"+to_string(fidXtal)+"_"+to_string(brd);
	TH1D *t_early = (TH1D*)input->Get(h.c_str());
	if(t_early == 0) continue;
 
	//Set parameters
	//f1->SetParameter(1,0.0005);//,0.001); 
	//  f1->SetParLimits(1,0.00001,0.0001);
	// f1->SetParameter(1,0.001);//,0.001); 
	f1->SetParameter(2,10);
	f1->SetParName(0,"G_{0}");
	f1->SetParName(1,"A");
	f1->SetParName(2,"#tau_{r}");
	// Perform fit
	t_early->Fit(f1,"M");
  
	TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
	t_early->SetStats(1);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit();

	gStyle->SetStatX(0.49);
	gStyle->SetStatY(0.89);
	t_early->GetXaxis()->SetTitle("Fill Time [#mus]");
	t_early->GetYaxis()->SetRangeUser(0.98,1.02);
	t_early->Draw();
	//	gStyle->SetOptFit();
	//	t_early
	//  t_early->SetStats(0);
	// t_early->SetTitle(";;");
	// t_all->SetTitle("E/p vs t (early), e^{+}, High Flux;Absolute Time [#mus];E/p");

	if (save){
	c1->SaveAs((h+".png").c_str());
	}
	t_early->SetDirectory(output);
	delete c1;
      }
    }
  }
  output->Write();
  output->Close();
  
  return 0; 
}



