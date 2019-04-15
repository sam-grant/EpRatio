#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"

using namespace std;


double energy_wiggle(double *x, double *par) {
  
  double time = x[0];
  double N0 = 1;//par[0]; // Overall normalisation
  double a = 90;//par[1];
  double b = 3/2;//par[2];
  double c = -5/2;//par[3];
  double d = 5/4;//0.945;//par[4];

  double N  = N0* ( a*time*time*time + b*time*time + c*time + d );
  return N;
  
}


int main() {
  

  TF1 *f1 = new TF1("f1", energy_wiggle,-3,3);//, 1.250, 2.250);
  f1 -> SetNpx(5000);
  // Draw it and save
  TCanvas *c1 = new TCanvas("c1","c1",2000,1000);
  f1->Draw();
  f1->SetTitle("Energy Wiggle Function;Energy in Calo[GeV];E/p");
  c1->SaveAs("energy_wiggle_function.png");

  delete c1;
  delete f1;

  return 0;

}


