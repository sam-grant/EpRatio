#include "MyRootStuff.h"
using namespace MyRootStuff;




void MergePlot(TString plotname, TString file="time_diff_plots.root") {
  cout<<"Merging "<<plotname<<" from "<<file<<endl;
  TH1 * merged_plot=0;
  TFile * tmpfile = new TFile(file, "READ");
  for(int i=0 ; i<200; i++) {
    TH1 * tmp = (TH1F*)tmpfile->Get((TString)(plotname+"_"+std::to_string(i)));
    if (!tmp) continue;
    if(!merged_plot) merged_plot = (TH1*)tmp->Clone();
    else merged_plot->Add(tmp);
  }
  merged_plot->SetDirectory(0);
  tmpfile->Close();
  tmpfile = new TFile("plots.root", "UPDATE");
  merged_plot->SetName(plotname);
  merged_plot->Write();
  tmpfile->Close();
  return;
}



void Draw(TString plotname) {

  TFile *file = new TFile("plots.root", "READ");
  TH1 *  plot = (TH1D*)file->Get(plotname);
  //normalise the plot:
  plot->Scale( 1./plot->Integral() );
  plot->SetStats(0);
  //  plot->Rebin();

  TCanvas * c = new TCanvas();
  c->cd();
  gPad->SetGrid();
  plot->DrawCopy();
  c->Print("figures/"+plotname+"_all.pdf");

   plot->SetAxisRange(0, 10, "X");
  plot->DrawCopy();
  c->Print("figures/"+plotname+".pdf");

  plot->SetAxisRange(0, 1, "X");
  plot->DrawCopy();
  c->Print("figures/"+plotname+"_zoom.pdf");
  return;
}




int main() {


  //reading and merging all the plots takes time, so see if we can load a pre-saved one:
  TFile * file = new TFile("plots.root");
  
  //if there is no pre-saved one, make it!
  if(file->IsZombie()) {
    cout<<"No plot found, re-merging runs!"<<endl;     

    MergePlot("time_diff_55_55");
    MergePlot("time_diff_55_55_p01");
    MergePlot("time_diff_60_60_p01");
    MergePlot("time_diff_55_55_p1");
    MergePlot("time_diff_60_60_p1");
    //    MergePlot("time_diff_50_70_p1");
    // MergePlot("time_diff_50_70_unique_p1");
    
    cout<<"Merging complete!"<<endl;
  }
  file->Close();

  Draw("time_diff_55_55_p01");
  Draw("time_diff_60_60_p01");

  Draw("time_diff_55_55_p1");
  Draw("time_diff_60_60_p1");
//  Draw("time_diff_50_70_p1");
  // Draw("time_diff_50_70_unique_p1");


  TH2 * pval_lo = Read2D("pval_55_55_lo", "time_diff_plots.root");
  TH2 * pval_hi = Read2D("pval_55_55_hi", "time_diff_plots.root");

  //  pval_lo->Rebin2D(2,2);
  //  pval_hi->Rebin2D(2,2);
  
  pval_lo->Scale(1./pval_lo->GetEntries());
  pval_hi->Scale(1./pval_hi->GetEntries());

   pval_lo->Add(pval_hi,-1);
   //  pval_hi->Add(pval_lo,-1);
  cout<<"1"<<endl;
  
  TCanvas * c = new TCanvas();
  pval_lo->Draw("COLZ");
  c->Print("figures/pval.pdf");

  pval_lo->SetAxisRange(-0.01, 0.01, "X");
  pval_lo->SetAxisRange(-0.01, 0.01, "Y");
  c->Print("figures/pval_zoom.pdf");

  cout<<"2"<<endl;

  TFile * f = new TFile("output.root", "RECREATE");
  f->cd();
  pval_lo->Write();
  f->Close();
  
  return 1;
  
}
