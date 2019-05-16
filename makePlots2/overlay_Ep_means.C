// Sam Grant 
// May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TStyle.h"
//#include "TAxis.h"
#include "TLegend.h"

using namespace std;
 
int main() {
 
  TFile *input1 = TFile::Open("fits_corrected_nandita.root");
  TFile *input2 = TFile::Open("fits_uncorrected_nandita.root");

  // Station loop
  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {

    // for(int energy = 0; energy < 4; energy++) {
      int energy = 3;
      if(energy==1) continue;
      // cout << energy << end
      string title, name;
      if(energy==0) {
	title = "e^{+} Slice: 0-1200 MeV";
	name = "overlay_0";
      }
      if(energy==2) {
	title = "e^{+} Slice: 1200-2400 MeV";
	name = "overlay_2";
      }
      if(energy==3) {
	title = "e^{+} Slice: 2400-3600 MeV";
	name = "overlay_3";
      }
      // Lost muons
      string h1 = "St"+to_string(stn)+"_fit_E_vs_xtal_1";
      // Positrons
      string h2 = "St"+to_string(stn)+"_fit_Ep_vs_xtal_"+to_string(energy);
      // Book histograms
      TH1D *mu_cor = (TH1D*)input1->Get(h1.c_str());
      TH1D *mu_unc = (TH1D*)input2->Get(h1.c_str());
      TH1D *e_cor = (TH1D*)input1->Get(h2.c_str());
      TH1D *e_unc = (TH1D*)input2->Get(h2.c_str());
    
      // Get scale factors
      double mu_cor_sf = mu_cor->GetBinContent(23);
      double mu_unc_sf= mu_unc->GetBinContent(23);
      double mu_cor_sf_err = mu_cor->GetBinError(23);
      double mu_unc_sf_err = mu_unc->GetBinError(23);

      double e_cor_sf = e_cor->GetBinContent(23);
      double e_unc_sf = e_unc->GetBinContent(23);
      double e_cor_sf_err = e_cor->GetBinError(23);
      double e_unc_sf_err = e_unc->GetBinError(23);

      mu_cor->Scale(1./mu_cor_sf);
      cout<<mu_cor_sf<<endl;
      mu_unc->Scale(1./mu_unc_sf);
      e_cor->Scale(1./e_cor_sf);
      e_unc->Scale(1./e_unc_sf);
      // uncorrected lost muons
      /*
      for(int bin = 0 ; bin < 54 ; bin++) {
	double binContent = mu_unc->GetBinContent(bin+1);
	double new_binContent = binContent/mu_unc_sf;
	double binError = mu_unc->GetBinError(bin+1);

	if (binContent == 0) continue; 
	mu_unc->SetBinContent(bin+1,new_binContent);///sf1);

	double term1 = mu_unc_sf_err/mu_unc_sf;
	double term2 = binError/binContent;
	// cout << term1 << endl;
	double new_binError = new_binContent*sqrt(term1*term1+term2*term2);
	mu_unc->SetBinError(bin+1,new_binError);
 
      }

      // corrected lost muons
      for(int bin = 0 ; bin < 54 ; bin++) {
	double binContent = mu_cor->GetBinContent(bin+1);
	double new_binContent = binContent/mu_cor_sf;
	double binError = mu_cor->GetBinError(bin+1);

	if (binContent == 0) continue; 
	mu_cor->SetBinContent(bin+1,new_binContent);

	double term1 = mu_cor_sf_err/mu_cor_sf;
	double term2 = binError/binContent;
	// cout << term1 << endl;
	double new_binError = new_binContent*sqrt(term1*term1+term2*term2);
	mu_cor->SetBinError(bin+1,new_binError);

      }

      // uncorrected positrons
      for(int bin = 0 ; bin < 54 ; bin++) {
	double binContent = e_unc->GetBinContent(bin+1);
	double new_binContent = binContent/e_unc_sf;
	double binError = e_unc->GetBinError(bin+1);

	if (binContent == 0) continue; 
	e_unc->SetBinContent(bin+1,new_binContent);///sf1);

	double term1 = e_unc_sf_err/e_unc_sf;
	double term2 = binError/binContent;
	// cout << term1 << endl;
	double new_binError = new_binContent*sqrt(term1*term1+term2*term2);
	e_unc->SetBinError(bin+1,new_binError);

      }
      // corrected positrons
      for(int bin = 0 ; bin < 54 ; bin++) {
	double binContent = e_cor->GetBinContent(bin+1);
	double new_binContent = binContent/e_cor_sf;
	double binError = e_cor->GetBinError(bin+1);

	if (binContent == 0) continue; 
	e_cor->SetBinContent(bin+1,new_binContent);///sf1);

	double term1 = e_cor_sf_err/e_cor_sf;
	double term2 = binError/binContent;
	// cout << term1 << endl;
	double new_binError = new_binContent*sqrt(term1*term1+term2*term2);
	e_cor->SetBinError(bin+1,new_binError);

      }


      */
      // Corrected
      TCanvas *c1  = new TCanvas();
      // c1->Divide(1,3);
      mu_cor->SetTitle("Gain Corrected (Lost Muons)");
       mu_unc->SetTitle("Gain Uncorrected (Lost Muons)");
      e_cor->SetTitle("Gain Corrected (Positrons)");
       e_unc->SetTitle("Gain Uncorrected (Positrons)");

      mu_cor->SetLineColor(kRed);
      mu_cor->SetMarkerColor(kRed);
      mu_unc->SetLineColor(kGreen);
      mu_unc->SetMarkerColor(kGreen);
      e_cor->SetLineColor(kBlue);
      e_cor->SetMarkerColor(kBlue);
      e_unc->SetLineColor(kOrange+1);
      e_unc->SetMarkerColor(kOrange+1);
      mu_unc->SetLineColor(kGreen);
      mu_unc->SetMarkerColor(kGreen);
 
      mu_cor->GetYaxis()->SetRangeUser(0.7,1.15);
      mu_cor->Draw();
      mu_unc->Draw("same");
      e_cor->Draw("same");
      e_unc->Draw("same");
      c1->BuildLegend(0.59,0.79,0.89,0.89);
      gPad->SetGridx();
      mu_cor->SetTitle(("Calo "+to_string(stn)+" | "+title+";Crystal Number; Arb. Units").c_str());
      string foo = "St"+to_string(stn)+"_"+name+".pdf";
      c1->SaveAs(foo.c_str());
      delete c1;





      TCanvas *c2  = new TCanvas();
      c2->Divide(1,2);
      c2->cd(1);
      mu_cor->Divide(e_cor);
      mu_cor->SetLineColor(kCyan+2);
      mu_cor->SetMarkerColor(kCyan+2);
      mu_cor->SetTitle(("Calo "+to_string(stn)+" | Gain Corrected Ratio "+title+";Crystal Number; Arb. Units").c_str());
      mu_cor->GetYaxis()->SetRangeUser(0.75,1.15);
      gPad->SetGridy();
      mu_cor->Draw();

      c2->cd(2);
      mu_unc->Divide(e_unc);
      mu_unc->SetLineColor(kMagenta+2);
      mu_unc->SetMarkerColor(kMagenta+2);
      mu_unc->SetTitle(("Calo "+to_string(stn)+" | Gain Uncorrected Ratio "+title+";Crystal Number; Arb. Units").c_str());
      mu_unc->GetYaxis()->SetRangeUser(0.75,1.15);
      gPad->SetGridy();
      mu_unc->Draw();
      //  TH1D *mu_unc = (TH1D*)input2->Get(h1.c_str());
      //string title = "St "+to_string(stn)+" | E/p vs Crystal Number;Crystal Number;E/p (normalised to xtal 22)";
      //  mu_cor->SetTitle(("Calo "+to_string(stn)+" | Normalised to crystal 22;Crystal Number; Arb. Units").c_str());
      // mu_cor->SetName("Gain Corrected");
      //   mu_unc->SetName("Gain Uncorrected");
      string foo2 = "St"+to_string(stn)+"_ratio_"+name+".pdf";
      c2->SaveAs(foo2.c_str());
      delete c2;
      // }
  }

  return 0;
}
