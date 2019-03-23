// Code to make E/p vs E and E/p vs t for all tracks 

#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TProfile.h"

using namespace std;

int main() {

  int stn;
  
  for (int i = 0 ; i < 2 ; i++) {
    if ( i == 0 ) { stn = 12; }
    else if ( i == 1 ) { stn = 18; }

    string h1 = "St"+to_string(stn)+"_Ep_vs_E";
    string h2 = "St"+to_string(stn)+"_Ep_vs_t";
    string h3 = "St"+to_string(stn)+"_Ep_vs_t_early";

    string fname1 = "../plots/St"+to_string(stn)+"_Ep_vs_E.png";
    string fname2 = "../plots/St"+to_string(stn)+"_Ep_vs_t.png";
    string fname3 = "../plots/St"+to_string(stn)+"_Ep_vs_t_early.png";
      string fname4 = "../plots/St"+to_string(stn)+"_Profile_t_.png";
      string fname5 = "../plots/St"+to_string(stn)+"_Profile_E_.png";

    string title1 = "Stn "+to_string(stn)+" | E/p vs E - All Tracks (Tracker & Calo);Energy in Calo [GeV];Energy in Calo / Track Momentum";
    string title2 = "Stn "+to_string(stn)+" | E/p vs t - All Tracks (Tracker & Calo);Absolute Time [#mus];Energy in Calo / Track Momentum";
    

    //string file1 = "../cluster_master/merged_cluster.root";

    TFile *f1 = TFile::Open("../cluster_master/merged_cluster.root");
  
    //TFile *f1 = TFile::Open("../cluster_master/plots_60hr_v9_11_00_15921.root");
  
    TH2D *E = (TH2D*)f1->Get(h1.c_str());
    TH2D *t = (TH2D*)f1->Get(h2.c_str());
    TH2D *t_early = (TH2D*)f1->Get(h3.c_str());

    f1->Save();

    // Draw
  
    gStyle->SetPalette(55);
  
    TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
    E->Draw("COLZ");
    E->GetYaxis()->SetTitleOffset(1);
    // Convert to us
    E->GetXaxis()->SetLimits(0,4);
    c1->SetRightMargin(0.13);
    //gPad->SetExponentOffset(1.5);
    // E->TGaxis()->SetExponentOffset(-0.05, 0.01, "x");
    // E->GetXaxis()->SetExponentOffset(1.4);
    E->SetStats(0);
    gPad->SetGrid();
    E->SetTitle(title1.c_str());
    c1->SaveAs(fname1.c_str());
    delete c1;

    TCanvas *c5 = new TCanvas("c4", "c4", 2000, 1000);
      TProfile *tpf1 = E->ProfileX();
      tpf1->Draw();
      //     if ( j == 0 ) {
      //	tpf1-> GetYaxis() -> SetRangeUser(0.7,1.3);
	//  }
      tpf1->SetName("Profile in X");
      tpf1 -> SetLineColor(kBlack);
      tpf1 -> SetMarkerColor(kBlack);
      tpf1-> SetTitle(title1.c_str());
      c5->SetRightMargin(0.13);
      c5->SaveAs(fname5.c_str());
      delete c5;

    TCanvas *c2 = new TCanvas("c2","c2",2000,1000);

    t->Draw("COLZ"); 
    // Change to micro seconds! 
    t->GetXaxis()->SetLimits(0,126*5);
    c2->SetRightMargin(0.13);
    t->SetStats(0);
    gPad->SetGrid();
    t->SetTitle(title2.c_str());
    c2->SaveAs(fname2.c_str());
    delete c2;

    TH2D *early = (TH2D*)t->Clone("early");
    early->GetXaxis()->SetLimits(0,126*5);

    TCanvas *c3 = new TCanvas("c3","c3",2000,1000);
    early->Draw("COLZ");
    early -> GetYaxis() -> SetRangeUser(0.7,1.3);

     
    // early->GetXaxis()->SetRangeUser(0,200000);
    //
    //  early_early->GetXaxis()->SetRangeUser(0,200000); 
    //   early->GetXaxis()->SetLimits(0,126*5);
    early->GetXaxis()->SetRangeUser(0,200);
    c3->SetRightMargin(0.13);
    early->SetStats(0);
    gPad->SetGrid();
    //t->GetXaxis()->SetRangeUser(0,);
    early->SetTitle(title2.c_str());
    c3->SaveAs(fname3.c_str());
    delete c3;

    TCanvas *c4 = new TCanvas("c4", "c4", 2000, 1000);
    TProfile *tpf = early->ProfileX();
    tpf->Draw();

    tpf-> GetYaxis() -> SetRangeUser(0.9425,0.975);
  
    tpf->SetName("Profile in X");
    tpf -> SetLineColor(kBlack);
    tpf -> SetMarkerColor(kBlack);
    tpf-> SetTitle(title2.c_str());
    c4->SetRightMargin(0.13);
    c4->SaveAs(fname4.c_str());
    delete c4;

    delete f1, E, t, tpf; 

  }

  // delete f1, E, t, c1, c2, c3; 
   
  return 0;

}
