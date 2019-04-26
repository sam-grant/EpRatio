// Code to make E/p vs E and E/p vs t for positrons

#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TProfile.h"
#include "TGraph.h"
#include "TF1.h"
#include "TAttLine.h"
#include "TNtuple.h" 
#include "TObject.h"

using namespace std;

int main() {

  int stn;
  string name;
 
  for (int i = 0 ; i < 2 ; i++ ) { // Station Loop

    if (i == 0 ) { 
      stn = 12;
   
    } 
    else if (i == 1) {
      stn = 18;
 
    }
    cout<<"-----------------------------------------------\nStation"<<stn<<endl;
 
    for (int j = 0 ; j < 4 ; j++ ) { // Plot region loop
      if (j == 0 ) { 
	
	name = "Positrons (Tracker & Calo)";
      } 
      else if ( j == 1 ) {
       
	name = "Core Region (Tracker & Calo)";
      }
      else if ( j == 2 ) {
       
	name = "High Flux Region (Tracker & Calo)";
      }
      else if ( j == 3) {
       
	name = "High Flux in Core Region (Tracker & Calo)";
      }

      cout<<"-----------------------------------------------\n"<<name<<"\n-----------------------------------------------"<<endl; 

      string h1 = "St"+to_string(stn)+"_Ep_vs_E_"+to_string(j);
      string h2 = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(j);
      string h3 = "St"+to_string(stn)+"_Ep_vs_t_early_"+to_string(j);

      string fname1 = "../plots/St"+to_string(stn)+"_Ep_vs_E_"+to_string(j)+".png";
      string fname2 = "../plots/St"+to_string(stn)+"_Ep_vs_t_"+to_string(j)+".png";
      string fname3 = "../plots/St"+to_string(stn)+"_Ep_vs_t_early_"+to_string(j)+".png";
      string fname4 = "../plots/St"+to_string(stn)+"_profile_E_"+to_string(j)+".png";
      string fname5 = "../plots/St"+to_string(stn)+"_profile_t_"+to_string(j)+".png";
      string fname6 = "../plots/St"+to_string(stn)+"_profile_t_early_"+to_string(j)+".png";
      string fname7 = "../plots/St"+to_string(stn)+"_gauss_t_"+to_string(j)+".png";


      string title1 = "Stn "+to_string(stn)+" | E/p vs E - "+name+";Energy in Calo [GeV];Energy in Calo / Track Momentum";
      string title2 = "Stn "+to_string(stn)+" | E/p vs t - "+name+";Absolute Time [#mus];Energy in Calo / Track Momentum";

      TFile *f1 = TFile::Open("../cluster_master/merged_core_cluster.root");
  
      TH2D *E = (TH2D*)f1->Get(h1.c_str());
      TH2D *t = (TH2D*)f1->Get(h2.c_str());
      TH2D *t_early = (TH2D*)f1->Get(h3.c_str());

      f1->Save();

      // Draw gain plots
  
      gStyle->SetPalette(55);
      // 1) E/p vs. E
      TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
      E->Draw("COLZ");
          if ( j == 0 ) {
	    //	E -> GetYaxis() -> SetRangeUser(0.7,1.3);
      }
      E->GetYaxis()->SetTitleOffset(1);
      // Convert to us
      E->GetXaxis()->SetLimits(0,4);
      c1->SetRightMargin(0.13);
      E->SetStats(0);
      gPad->SetGrid();
      E->SetTitle(title1.c_str());
      c1->SaveAs(fname1.c_str());

      delete c1;

      // 2) E/p vs. t
      TCanvas *c2 = new TCanvas("c2","c2",2000,1000);
      t->Draw("COLZ"); 
      if ( j == 0 ) {
	//	t -> GetYaxis() -> SetRangeUser(0.7,1.3);
      }//t->GetXaxis()->SetRangeUser(19000,42000);
      // Change to micro seconds! 
      t->GetXaxis()->SetLimits(0,126*5);
      c2->SetRightMargin(0.13);
      t->SetStats(0);
      gPad->SetGrid();
      t->SetTitle(title2.c_str());
      c2->SaveAs(fname2.c_str());
      delete c2;

      // 3) E/p vs. t_early
      TCanvas *c3 = new TCanvas("c3","c3",2000,1000);
      t_early->Draw("COLZ"); 
      if ( j == 0 ) {
	//	t -> GetYaxis() -> SetRangeUser(0.7,1.3);
      }//t->GetXaxis()->SetRangeUser(19000,42000);
      // Change to micro seconds! 
      t_early->GetXaxis()->SetLimits(0,4.2*50);
      c3->SetRightMargin(0.13);
      t_early->SetStats(0);
      gPad->SetGrid();
      t_early->SetTitle(title2.c_str());
      c3->SaveAs(fname3.c_str());
      delete c3;

      // Make Profiles - Must be a better way

      // E/p vs E 
      TCanvas *c4 = new TCanvas("c4", "c4", 2000, 1000);
      TProfile *tpf1 = E->ProfileX();
      tpf1->SetLineWidth(4);
      tpf1->SetStats(0);
      tpf1->Draw();
      if ( j == 0 ) {
	tpf1-> GetYaxis()->SetRangeUser(0.8,1.15);
      }
      if ( j == 1 ) {
	tpf1-> GetYaxis()->SetRangeUser(0.925,1.0);
      }
      if ( j == 2 && i == 0 ) {
	tpf1-> GetYaxis()->SetRangeUser(0.948,0.96);
	tpf1-> GetXaxis()->SetRangeUser(1.6,1.8);
      }
      if ( j == 2 && i == 1 ) {
	tpf1-> GetYaxis()->SetRangeUser(0.956,0.965);
	tpf1-> GetXaxis()->SetRangeUser(1.6,1.8);
      }
      if ( j == 3 && i == 0) {
	tpf1-> GetYaxis()->SetRangeUser(0.9587,0.9596);
	tpf1-> GetXaxis()->SetRangeUser(1.6,1.8);
      }
      if ( j == 3 && i == 1) {
        tpf1-> GetYaxis()->SetRangeUser(0.9601,0.9608);
       	tpf1-> GetXaxis()->SetRangeUser(1.6,1.8);
      }
      tpf1->SetName("Profile in X");
      tpf1->SetLineColor(kBlack);
      tpf1->SetMarkerColor(kBlack);
      tpf1->SetTitle(title1.c_str());
      c4->SaveAs(fname4.c_str());
      delete c4;

      TCanvas *c5 = new TCanvas("c5", "c5", 2000, 1000);
      TProfile *tpf2 = t->ProfileX();
      tpf2->SetLineWidth(4);
      tpf2->SetStats(0);
      tpf2->Draw();
      // tpf2->GetYaxis() -> SetRangeUser(0.9425,0.975);
      tpf2->SetName("Profile in X");
      tpf2->SetLineColor(kBlack);
      tpf2->SetMarkerColor(kBlack);
      tpf2->SetTitle(title2.c_str());
      c5->SaveAs(fname5.c_str());
      delete c5;

      TCanvas *c6 = new TCanvas("c6", "c6", 2000, 1000);
      TProfile *tpf3 = t_early->ProfileX();
      tpf3->GetXaxis()->SetRangeUser(5,50*4.2);
      tpf3->SetLineWidth(4);
      tpf3->SetStats(0);
      tpf3->Draw();
      // tpf3 -> GetYaxis() -> SetRangeUser(0.9425,0.975);
      tpf3->SetName("Profile in X");
      tpf3->SetLineColor(kBlack);
      tpf3->SetMarkerColor(kBlack);
      tpf3->SetTitle(title2.c_str());
      c6->SaveAs(fname6.c_str());
      delete c6;
      /*
      // Set and make gauss fits 
      TObjArray *slices = new TObjArray(20);
      for (int k = 0 ; 20 > k ; k++ ) { 
	Int_t bin = E->GetBin(binx,biny,binz=0);
	E->GetBinContent(bin);
      }
      
      TCanvas *c7 = new TCanvas("c7", "c7", 2000, 1000);
      //TProfile *tpf4 = t_early->ProfileX();
      E->FitSlicesX(&aSlices);
      
      
     c7->SaveAs(fname7.c_str());
      delete c7;
      */


      /*
      TCanvas *c7 = new TCanvas("c7", "c7", 2000, 1000);
      string slice;
      TH1D *Ey;
      for (int k = 0 ; k < 20 ; k++ ) {
	
	if (E
	cout<<"Slice "<<k<<endl;
	Ey = (TH1D*)E->ProfileY();  
	Ey->Fit("gaus");
	// Ey->Draw();
      }
      Ey->Draw();
      c7->SaveAs(fname7.c_str());
      delete c7;
      */
      //  delete f1, E, t, tpf1, tpf2, tpf3; 

    }

  }
 
   
  return 0;

}
