//#include "MyRootStuff.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TF1.h"
#include "TFile.h"
#include "TRandom3.h"
#include <iostream>
using std::cout;
using std::endl;
//using namespace MyRootStuff;

int main() {

  TRandom3 *rand = new TRandom3();

  TF1 *wiggle = new TF1("wiggle","exp(-0.005*x) * (20.+sin(1.5*x))",0,60);


  TH1 * dt_plot = new TH1F("toy", "dt", 100, -10,10);
  TH1 * dt2_plot = new TH1F("toy_2", "dt", 100, -10,10);
  TH1 * dt3_plot = new TH1F("toy_3", "dt", 100, -10,10);
  TH1 * dt4_plot = new TH1F("toy_4", "dt", 100, -10,10);

  const int ntot= 50000000;
  for(int i=0; i<ntot; i++) {
    if( !(i%1000000) ) cout<<"Processed "<<i/(float)ntot<<endl;
    const double r1 = wiggle->GetRandom(20,30);
    const double dt =  wiggle->GetRandom(r1-10, r1+10) - r1;

    const double r2 = wiggle->GetRandom(21,41);
    const double dt2 =  wiggle->GetRandom(r2-10, r2+10) - r2;

    const double r3 = wiggle->GetRandom(22,42);
    const double dt3 =  wiggle->GetRandom(r3-10, r3+10) - r3;

    const double r4 = wiggle->GetRandom(30,40);
    const double dt4 =  wiggle->GetRandom(r4-10, r4+10) - r4;

    //    const double dt =  wiggle->GetRandom(0,100) - r1;

    dt_plot->Fill( dt );
    dt2_plot->Fill( dt2 );
    dt3_plot->Fill( dt3 );
    dt4_plot->Fill( dt4 );
    
  }

  TCanvas * c = new TCanvas();
  gPad->SetGrid();
  wiggle->Draw();
  c->Print("figures/toy_wiggle.pdf");
  //  delete c;

  //GRID();
  dt_plot->SetXTitle("#Deltat");

  /*
  Draw(dt_plot, "toy_dt", "#Deltat");
  Draw(dt_plot_flat, "toy_dt_flat", "#Deltat");
  Draw(dt_plot_time_dep, "toy_dt_time_dep", "#Deltat");
  */
  
  dt_plot->DrawCopy();
  c->Print("figures/toy_dt.pdf");

  TFile * out = new TFile("toy_plots.root", "RECREATE");
  out->cd();
  wiggle->Write();
  dt_plot->Write();
  dt2_plot->Write();
  dt3_plot->Write();
  dt4_plot->Write();
  out->Close();
  
  
  return 1;
}
