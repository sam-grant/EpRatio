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
#include "TDirectory.h"
using namespace std;

void scaler(TH1D *hist, double scaleFactor, double scaleFactorError) { 
  
  int nbins = hist->GetNbinsX();

  for(int bin = 0 ; bin < nbins ; bin++) {
    double binContent = hist->GetBinContent(bin+1);
    double new_binContent = binContent/scaleFactor;
    double binError = hist->GetBinError(bin+1);
   
    if (binContent == 0) continue; 
    hist->SetBinContent(bin+1,new_binContent);///sf1);

    double term1 = scaleFactorError/scaleFactor;
    double term2 = binError/binContent;
    double new_binError = new_binContent*sqrt(term1*term1+term2*term2);
    hist->SetBinError(bin+1,new_binError);
 
  }
 
  return;

}

int main() {
 
  TFile *input1 = TFile::Open("fits_corrected_nandita.root");
  TFile *input2 = TFile::Open("fits_uncorrected_nandita.root");
  TFile *output = new TFile("overlaid_E_slices.root", "RECREATE");
  // Station loop
  for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {

      string h0 = "St"+to_string(stn)+"_fit_Ep_vs_xtal_0";
      string h1 = "St"+to_string(stn)+"_fit_E_vs_xtal_1";
      string h2 = "St"+to_string(stn)+"_fit_Ep_vs_xtal_2";
      string h3 = "St"+to_string(stn)+"_fit_Ep_vs_xtal_3";

      TH1D *lo_c = (TH1D*)input1->Get(h0.c_str());
      TH1D *mu_c = (TH1D*)input1->Get(h1.c_str());
      TH1D *med_c = (TH1D*)input1->Get(h2.c_str());
      TH1D *hi_c = (TH1D*)input1->Get(h3.c_str());

      TH1D *lo_u = (TH1D*)input2->Get(h0.c_str());
      TH1D *mu_u = (TH1D*)input2->Get(h1.c_str());
      TH1D *med_u = (TH1D*)input2->Get(h2.c_str());
      TH1D *hi_u = (TH1D*)input2->Get(h3.c_str());
    
      // Get scale factors
      double lo_c_sf = lo_c->GetBinContent(23);
      double mu_c_sf= mu_c->GetBinContent(23);
      double med_c_sf = med_c->GetBinContent(23);
      double hi_c_sf = hi_c->GetBinContent(23);

      double lo_u_sf = lo_u->GetBinContent(23);
      double mu_u_sf= mu_u->GetBinContent(23);
      double med_u_sf = med_u->GetBinContent(23);
      double hi_u_sf = hi_u->GetBinContent(23);

      lo_c->Scale(1./lo_c_sf);
      mu_c->Scale(1./mu_c_sf);
      med_c->Scale(1./med_c_sf);
      hi_c->Scale(1./hi_c_sf);

      lo_u->Scale(1./lo_u_sf);
      mu_u->Scale(1./mu_u_sf);
      med_u->Scale(1./med_u_sf);
      hi_u->Scale(1./hi_u_sf);


      TCanvas *c1  = new TCanvas();

      lo_c->SetTitle("e^{+}: 0-1200 MeV");
      mu_c->SetTitle("Lost #mu^{+}");
      med_c->SetTitle("e^{+}: 1200-2400 MeV");
      hi_c->SetTitle("e^{+}: 2400-3600 MeV");
       
      lo_c->SetLineColor(kBlue);
      lo_c->SetMarkerColor(kBlue);
      mu_c->SetLineColor(kBlack);
      mu_c->SetMarkerColor(kBlack);
      med_c->SetLineColor(kGreen);
      med_c->SetMarkerColor(kGreen);
      hi_c->SetLineColor(kRed);
      hi_c->SetMarkerColor(kRed);

      lo_c->GetYaxis()->SetRangeUser(0.75,1.15);

      lo_c->Draw();
      mu_c->Draw("same");
      med_c->Draw("same");
      hi_c->Draw("same");

      c1->BuildLegend(0.69,0.79,0.89,0.89);

      gPad->SetGridx();
      lo_c->SetTitle(("Calo "+to_string(stn)+" | Gain Corrected;Crystal Number; Normalised Units").c_str());
      string fname1 = "St"+to_string(stn)+"_slices_gain_corrected.pdf";

      c1->SaveAs(fname1.c_str());

      c1->Write();//SetDirectory(output);
      delete c1;




      TCanvas *c2  = new TCanvas();

       lo_u->SetTitle("e^{+}: 0-1200 MeV");
 mu_u->SetTitle("Lost #mu^{+}");
       med_u->SetTitle("e^{+}: 1200-2400 MeV");
      hi_u->SetTitle("e^{+}: 2400-3600 MeV");
       
      lo_u->SetLineColor(kBlue);
      lo_u->SetMarkerColor(kBlue);
      mu_u->SetLineColor(kBlack);
      mu_u->SetMarkerColor(kBlack);
      med_u->SetLineColor(kGreen);
      med_u->SetMarkerColor(kGreen);
      hi_u->SetLineColor(kRed);
      hi_u->SetMarkerColor(kRed);

      lo_u->GetYaxis()->SetRangeUser(0.75,1.15);

      lo_u->Draw();
      mu_u->Draw("same");
      med_u->Draw("same");
      hi_u->Draw("same");

      c2->BuildLegend(0.69,0.79,0.89,0.89);

      gPad->SetGridx();

      lo_u->SetTitle(("Calo "+to_string(stn)+" | Gain Uncorrected;Crystal Number; Normalised Units").c_str());

      string fname2 = "St"+to_string(stn)+"_slices_gain_uncorrected.pdf";

      c2->SaveAs(fname2.c_str());
      lo_u->SetDirectory(output);
      delete c2;


            // Ratios
      ////////////////////////////
      // Ratios

      TCanvas *c3  = new TCanvas();
      // c3->Divide(1,3);
      // c3->cd(1);
      //   TH1D *clone1 = (TH1D*)lo_c->Clone("clone1");
      lo_c->SetTitle("e^{+}: 0-1200 MeV");
      lo_c->Divide(mu_c);
      med_c->Divide(mu_c);
      hi_c->Divide(mu_c);

      lo_c->Draw();
      med_c->Draw("same");
      hi_c->Draw("same");

      // lo_c->SetTitle(("Calo "+to_string(stn)+" | Gain Corrected Ratios;Crystal Number; Arb. Units").c_str());
      lo_c->GetYaxis()->SetRangeUser(0.75,1.15);
      gPad->SetGridy();
      
      c3->BuildLegend(0.69,0.79,0.89,0.89);
      lo_c->SetTitle(("Calo "+to_string(stn)+" | Gain Corrected Ratios;Crystal Number; Arb. Units").c_str());
      string fname3 = "St"+to_string(stn)+"_ratio_corrected.pdf";
      c3->SaveAs(fname3.c_str());
      delete c3;




      TCanvas *c4  = new TCanvas();
      // c3->Divide(1,3);
      // c3->cd(1);
      // TH1D      lo_c->SetTitle("e^{+}: 0-1200 MeV"); *lo_u = (TH1D*)lo_u->Clone("lo_u");
      lo_u->SetTitle("e^{+}: 0-1200 MeV");
      lo_u->Divide(mu_u);
      med_u->Divide(mu_u);
      hi_u->Divide(mu_u);

      lo_u->Draw();
      med_u->Draw("same");
      hi_u->Draw("same");

      //  lo_u->SetTitle(("Calo "+to_string(stn)+" | Gain Uncorrected Ratios;Crystal Number; Arb. Units").c_str());
      lo_u->GetYaxis()->SetRangeUser(0.75,1.15);
      gPad->SetGridy();
      
    c4->BuildLegend(0.69,0.79,0.89,0.89);
    lo_u->SetTitle(("Calo "+to_string(stn)+" | Gain Uncorrected Ratios;Crystal Number; Arb. Units").c_str());
      string fname4 = "St"+to_string(stn)+"_ratio_uncorrected.pdf";
      c4->SaveAs(fname4.c_str());
      delete c4;

      // delete 

  }

  
  output->Write();
  output->Close();
  return 0;
}
