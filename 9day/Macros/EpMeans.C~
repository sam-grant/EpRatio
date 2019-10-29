

// Plotting code for gain par per xtal scatter plots 
// Sam Grant - May 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"

using namespace std;

int main() {

  string inputFname = "RootFiles/PlotsEpXtalFid.root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout<<"Reading... "<<inputFname<<endl;
  
  TCanvas *c2 = new TCanvas("c2","c2",3000,2000);
  TLegend *leg = new TLegend(0.79,0.79,0.89,0.89);
  
  for(int stn(13); stn < 20; stn = stn + 6) {
    
    string histName = "St"+to_string(stn)+"_Ep_vs_xtal";
    string cmapName = "St"+to_string(stn)+"_cmap_Ep_vs_xtal";
    
    TH2D *h1 = (TH2D*)input->Get(histName.c_str());
    TH2D *h2 = (TH2D*)input->Get(cmapName.c_str());

    h1->SetStats(0);
    h2->SetStats(0);
    
    h1->SetTitle(("Stn "+to_string(stn-1)).c_str());
    h2->SetTitle(("Stn "+to_string(stn-1)+";Crystal Number;Cluster Energy, E / Track Momentum, p").c_str());

    gStyle->SetPalette(kRainBow);

    TCanvas *c1 = new TCanvas("c1","c1",3000,2000);    
    h2->Draw("COLZ");
    c1->SaveAs(("Plots/St"+to_string(stn)+"EpMeanCmap.png").c_str());
    delete c1;

    h1->SetLineWidth(10);
    if(stn==13) h1->SetLineColor(kBlue);
    else if(stn==19) h1->SetLineColor(kRed);
    else break;
    h1->GetYaxis()->SetRangeUser(0.85,1.04);
    leg->AddEntry(h1);
    leg->SetBorderSize(0);
    if(stn==13) h1->Draw();
    else h1->Draw("same");
    h1->SetTitle(";Crystal Number;Cluster Energy, E / Track Momentum, p");

  }

  gPad->SetGridx();
  leg->Draw("same");
  c2->SaveAs("Plots/EpMeans.png");

  return 0;
}
