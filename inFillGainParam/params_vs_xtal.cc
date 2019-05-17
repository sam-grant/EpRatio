// Extract differences and plots per xtal
// Also overlay the 1D guys


// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TAttMarker.h"

using namespace std;

int main() {
  //All inputs
  TFile *laser_xtal = TFile::Open("inFillGainParams_laser_xtal.root");
  TFile *sam_xtal = TFile::Open("inFillGainParams_sam_xtal.root");
  TFile *laser_1d = TFile::Open("inFillGainParams_laser.root");
  TFile *sam_1d = TFile::Open("inFillGainParams_Sam2.root");
  // Output
  TFile *output = new TFile("comparison.root","RECREATE");

    
  // Deltas
  TH1D *dtau13 = new TH1D("dtau13","Calo 13",54,-0.5,53.5);
  TH1D *dtau19 = new TH1D("dtau19","Calo 19",54,-0.5,53.5);
  TH1D *damp13 = new TH1D("damp13","Calo 13",54,-0.5,53.5);
  TH1D *damp19 = new TH1D("damp19","Calo 19",54,-0.5,53.5);

  TH1D *tau13_laser = (TH1D*)laser_xtal->Get("tau 13");
  TH1D *tau13_sam = (TH1D*)sam_xtal->Get("tau 13");
  tau13_laser -> Add(tau13_sam,-1);
  TCanvas *a1 = new TCanvas();
  tau13_laser->SetTitle("Calo 13 | #Delta#tau;Crytal Number;#Delta#tau [#mus]");
  tau13_laser->Draw();
  a1->SaveAs("tau13_diff.png");
  
  TH1D *tau19_laser = (TH1D*)laser_xtal->Get("tau 19");
  TH1D *tau19_sam = (TH1D*)sam_xtal->Get("tau 19");
  tau19_laser -> Add(tau19_sam,-1);
  TCanvas *a2 = new TCanvas();
  tau19_laser->SetTitle("Calo 19 | #Delta#tau;Crytal Number;#Delta#tau [#mus]");
  tau19_laser->SetStats(0);
  tau19_laser->SetMarkerColor(kBlack);
  tau19_laser->SetLineWidth(0);
  tau19_laser->SetMarkerStyle(kStar);
  tau19_laser->Draw("P");
  //  tau19_laser->Draw();
  a2->SaveAs("tau19_diff.png");


  TH1D *amp13_laser = (TH1D*)laser_xtal->Get("amp 13");
  TH1D *amp13_sam = (TH1D*)sam_xtal->Get("amp 13");
  amp13_laser -> Add(amp13_sam,-1);
  TCanvas *a3 = new TCanvas();
  amp13_laser->SetTitle("Calo 13 | #DeltaA;Crytal Number;#DeltaA");
  amp13_laser->SetStats(0);
  amp13_laser->SetMarkerColor(kBlack);
  amp13_laser->SetLineWidth(0);
  amp13_laser->SetMarkerStyle(kStar);
  amp13_laser->Draw("P");
  a3->SaveAs("amp13_diff.png");


  TH1D *amp19_laser = (TH1D*)laser_xtal->Get("amp 19");
  TH1D *amp19_sam = (TH1D*)sam_xtal->Get("amp 19");
  amp19_laser -> Add(amp19_sam,-1);
  TCanvas *a4 = new TCanvas();
  amp19_laser->SetTitle("Calo 19 | #DeltaA;Crytal Number;#DeltaA");
  amp19_laser->SetStats(0);
  amp19_laser->SetMarkerColor(kBlack);
  amp19_laser->SetLineWidth(0);
  amp13_laser->SetMarkerStyle(kStar);
  amp19_laser->Draw("P");
  // amp19_laser->Draw();
  a4->SaveAs("amp19_diff.png");
 
  //station loop
  // for (int stn = 13 ; stn < 20 ; stn = stn + 6 ) {

  //  d


    
    // crystal loop
    //  for (int xtal = 0; xtal < 54; xtal++) {


      
    //  value1 = laser_xtal->GetBinContent(xtal+1);
    //  if(value1==0)continue;
    //  value2 = sam_xtal->GetBinContent(xtal+1);
    //  if(value2==0)continue;
    // diff = value1 - value2;
    // TH1

      
		    
      

  //   }

   
  //  }


    TCanvas *c1 = new TCanvas();
  TH1D *h1 = (TH1D*)laser_1d->Get("tau 13");
  TH1D *h2 = (TH1D*)sam_1d->Get("tau 13");
  h1->SetTitle("Laser");
  h2->SetTitle("E/p Ratio");
  h1->SetStats(0);
  h1->SetLineColor(kRed);
  h2->SetLineColor(kGreen-3);
  h1->Draw();
  h2->Draw("same");
  c1->BuildLegend(0.79,0.79,0.89,0.89);
  h1->SetTitle("Calo 13 | Recovery Times;In Fill Time [#mus];Entries"); 
  c1->SaveAs("calo13_taus.png");


  TCanvas *c2 = new TCanvas();
  TH1D *h3 = (TH1D*)laser_1d->Get("tau 19");
  TH1D *h4 = (TH1D*)sam_1d->Get("tau 19");
  h3->SetStats(0);
  h3->SetTitle("Laser");
  h2->SetTitle("E/p Ratio");
  h3->SetLineColor(kRed);
  h2->SetLineColor(kGreen-3);
  h3->Draw();
  h2->Draw("same");
  c2->BuildLegend(0.79,0.79,0.89,0.89);
  h3->SetTitle("Calo 19 | Recovery Times;In Fill Time [#mus];Entries");
  c2->SaveAs("calo19_taus.png");
  // delete c2;

  TCanvas *c3 = new TCanvas();
  TH1D *h5 = (TH1D*)laser_1d->Get("amp 13");
  TH1D *h6 = (TH1D*)sam_1d->Get("amp 13");
  h5->SetTitle("Laser");
  h6->SetTitle("E/p Ratio");
  h5->SetStats(0);
  h5->SetLineColor(kRed);
  h6->SetLineColor(kGreen-3);
  h5->Draw();
  h6->Draw("same");
  c3->BuildLegend(0.79,0.79,0.89,0.89);
  h5->SetTitle("Calo 13 | Amplitudes;Amplitude;Entries"); 
  c3->SaveAs("calo13_amps.png");


  TCanvas *c4 = new TCanvas();
  TH1D *h7 = (TH1D*)laser_1d->Get("amp 19");
  TH1D *h8 = (TH1D*)sam_1d->Get("amp 19");
  h7->SetStats(0);
  h7->SetTitle("Laser");
  h8->SetTitle("E/p Ratio");
  h7->SetLineColor(kRed);
  h8->SetLineColor(kGreen-3);
  h7->Draw();
  h8->Draw("same");
  c4->BuildLegend(0.79,0.79,0.89,0.89);
  h7->SetTitle("Calo 19 | Amplitudes;Amplitude;Entries");
  c4->SaveAs("calo19_amps.png");
  

  return 0;
}
