// Sam Grant - August 2019
// Draw xtal fits on a single canvas

// WIP

#include <iostream>
#include <cmath>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TGraphErrors.h"

using namespace std;

int main() {

  // Take command line input for dataset used
  string dataset;
  cout << "Enter run-1 dataset: 60h 9d HK EG\n";
  cin >> dataset;
  if (dataset == "60h" || dataset == "9d" || dataset == "HK" || dataset == "EG") { 
     cout << "Starting\n" << endl;
  } else { 
    cout<<"Invalid dataset, stopping"<<endl;
  }


  string fitName;
  string fitMode;
  cout << "Select fit mode: '1' (SingleGaus) '2' (DoubleGaus) '3' (LanGaus)\n";
  cin >> fitName;
  if (fitName == "1") {
    fitMode = "SingleGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl; 
  } else if(fitName == "2") {
    fitMode = "DoubleGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl;
  } else if(fitName == "3") {
    fitMode = "LanGaus";
    cout << "Using fitMode: "<< fitMode << "\nStarting\n" << endl;
  } else {
    cout<<"Invalid fitmode, stopping"<<endl;
    exit(0);
  }

  string inputFname = "../plots/"+dataset+"/fitsEpTimeXtal_"+fitMode+"_"+dataset+".root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout<<"Reading... "<<inputFname<<endl;

  int place = 0;     
  // int edgeXtals[26] = {0,1,2,3,4,5,6,7,8,9,17,18,26,27,35,36,44,45,46,47,48,49,50,51,52,53}

  // Need same number of rows as columns
  int cols = 5; // -1; 
  int rows = 5; // -1;

  // Always 5 across
  // Always retain equal number across and down to retain geometry


/*  if(dataset == "60h" && fitMode == "SingleGaus") {
    cols = 5;
    rows = 5;
  } else if(dataset == "9d" && fitMode == "SingleGaus") {
    cols = 5;
    rows = 5;
  } else if(dataset == "HK" && fitMode == "SingleGaus") {
    cols = 5;
    rows = 5;
  } else if(dataset == "EG" && fitMode == "SingleGaus") {
    cols = 5;
    rows = 5;
  } else if(dataset == "60h" && fitMode == "LanGaus") {
    cols = 3;
    rows = 3;
  } else if(dataset == "9d" && fitMode == "LanGaus") {
    cols = 4;
    rows = 4;
  } else if(dataset == "HK" && fitMode == "LanGaus") {
    cols = 2;
    rows = 2;
  }*/

  // int rows = count / cols;
  // if(dataset == "HK") rows = 3;
  // cout<<round(count/2)<<endl;

  // Count crystals
  int count = 0;

  TCanvas *c1  = new TCanvas("c1","c1",600,600);    
  c1->Divide(cols,rows);

  for (int stn(12) ; stn < 19 ; stn = stn + 6 ) {

    for(int xtal(0); xtal<54; xtal++) {

      string name = "S"+to_string(stn)+"/EoverPvsTimeXtal_"+to_string(xtal);
      // Change input if need be
      TGraphErrors *h = (TGraphErrors*)input->Get(name.c_str());
/*      TH1D *h = (TH1D*)input->Get(name.c_str());*/
      if(h==0) continue;
  
      if(dataset=="60h" && stn==12 && xtal==26) continue;
      if( (dataset=="9d" && stn==18) && (xtal==2 || xtal==46) ) continue;
      count++;
      // Some formatting
      h->SetTitle(("Station "+to_string(stn)+", Crystal "+to_string(xtal)+";In-fill time [#mus];E/p").c_str());
      h->GetYaxis()->SetTitleOffset(1.25);
      h->GetXaxis()->SetRange(0,23);
/*      h->Draw();*/
      gStyle->SetOptFit(0);
      gStyle->SetOptStat(0);
/*      h->Draw();*/
/*      gPad->Update();*/

      c1->cd(place+1);
      place++;
      cout<<place<<" "<<xtal<<endl;
/*      h->SetStats(0);*/
      h->Draw("AP");

    }

  }
  
  std::cout<<"xtals:\t"<<count<<std::endl;

  string fname = "../images/"+dataset+"/fitMap_"+fitMode+"_"+dataset; // +".pdf";
  c1->SaveAs((fname+".pdf").c_str());
  c1->SaveAs((fname+".C").c_str());
  c1->SaveAs((fname+".png").c_str());
  
  
  delete c1;
  return 0;
}
