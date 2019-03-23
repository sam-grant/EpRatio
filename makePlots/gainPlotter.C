// Code to make E/p vs E, E/p vs p, and E/p vs t plots
// Using either gain corrected, or uncorrected
// It also performs gauss fits in Y to slices in X

// Sam Grant 
// March 2019
// samuel.grant.18@ucl.ac.uk

#include <iostream>
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TProfile.h"
#include "TF1.h"
#include "TDirectory.h"
#include "TObject.h"
#include "TGraph.h"
#include "TLegend.h"

using namespace std;

// Fit gaussians to slices along the x-axis and plot their means
void fitSlicesGaus(TH2D *hist, string title, string fname,string g_fname) {//,int region,int type) {
 
  int nBins = hist->GetNbinsX(); 

  // Change this to change the number of slices
  int nSlices = nBins;

  // Get the length of the slice in x
  int length = nBins / nSlices;

  // Define the gaussian 
  TF1 *gFunc = new TF1("gFunc", "gaus");

  // Declare step edges
  int loStep;
  int hiStep;

  // Book a 1D hist for the Y projection slices
  TH1 *projY;

  // Book a 1D hist to take the results of each fit on it's X axis
  TH1 *projX = hist -> ProjectionX("prX");
  projX -> Rebin(length);
  projX -> Reset();

  // Threshold (minimum number of bins), to define the fit range
  double threshold;
  double fitMin;
  double fitMax;

  // Slice loop
  for(int i = 0 ; i < nSlices; i++) {
   
    // Define steps
    loStep = i*length;
    hiStep = (i+1)*length;

    // Perform projection
    projY = hist->ProjectionY("prY",loStep,hiStep-1);

    if (projY -> GetEntries() < 500) continue; //'quality' cut

    //Define the threshold, trying to avoid those tails. Half maximum seems reasonable (?)
    threshold = (projY -> GetMaximum())/2;
    
    // Define the fit range
    fitMin = projY -> GetBinCenter( projY -> FindFirstBinAbove(threshold,1));
    fitMax = projY -> GetBinCenter( projY -> FindLastBinAbove(threshold,1));
    // "Q" : supress printing "M" use minuit to improve fit result
    projY -> Fit(gFunc,"QM","",fitMin,fitMax);
    // Fill a histogram with the fit results
     projX -> SetBinContent(i+1, gFunc->GetParameter(1));
     projX -> SetBinError(i+1, gFunc->GetParError(1));
     // Draw fits to slices, to see what's going on
    TCanvas *c1 = new TCanvas();
    projY -> Draw();
    //gFunc -> DrawCopy("same");
    projY->SetMarkerColor(kBlue);
    projY->SetLineColor(kBlue);
    gPad->SetGrid();
    // c1->SaveAs((g_fname+to_string(i)+".pdf").c_str());

    delete c1;

  } // End slice loop

  delete gFunc;

  //  delete gFunc;
  // Generate the profile 
  TProfile *tpf = new TProfile();
  tpf = hist -> ProfileX();
   // Draw out the means, and compare with the profile 
  TCanvas *c2 = new TCanvas();
  projX->Draw();
  projX->SetTitle(title.c_str());
  projX->GetYaxis()->SetRangeUser(0.9,1);
 projX->SetMarkerColor(kGreen+2);
  projX->SetLineColor(kGreen+2);
  // projX->GetYaxis()->SetRangeUser(tpf->GetMinimum(),tpf->GetMaximum()); 
  projX->SetStats(0);
  
  
  tpf->Draw("same");
  tpf->SetMarkerColor(kMagenta+2);
  tpf->SetLineColor(kMagenta+2);
  tpf->SetStats(0);
  c2->SaveAs(fname.c_str());

  delete c2, tpf, projX;

  return;

}




// Colour map plotter
void cmap(TH2D *hist, string title, string fname) { // int region, int type) {

  TCanvas *c = new TCanvas("c", "c", 2000, 1000);
  gStyle->SetPalette(55);
  hist->Draw("COLZ");
  hist->SetStats(0);
  //  hist -> GetYaxis() -> SetRangeUser(yLo,yHi);
  // hist -> GetXaxis() -> SetRangeUser(xLo,xHi);
  hist-> SetTitle(title.c_str());
  c->SetRightMargin(0.13);
  c->SaveAs(fname.c_str());
    
  delete c, hist;
  return;

}





int main() {

  // Take input for gain corrected or uncorrected
  bool gainCorr;
  string input;
  cout << "Gain corrected? Yes (y) or no (n): ";
  cin >> input;

  if (input == "y") { gainCorr = true; }
  else if (input == "n" ) { gainCorr = false; }
  else {
    cout << "Error, try again" << endl;
    return 0;
  }

  string whichFile;

  if ( gainCorr ) { 
    whichFile = "../corrected/merged_corrected.root";
  }
  else if ( !gainCorr ) { 
    whichFile = "../uncorrected/merged_uncorrected.root";
  }
    
  TFile *rootFile = TFile::Open(whichFile.c_str());
    
  int stn;
  
  // Start station loop  
  for (int i = 0 ; i < 2 ; i++ ) { 

    if (gainCorr) {
      if (i == 0 ) { stn = 12; } 
      else if (i == 1) {stn = 18; }
      cout << "\nStation: "+to_string(stn)+"\n";
    }

    // Start plot region loop
    for (int j = 0 ; j < 4 ; j++ ) { 

      string name;
      double yMin, yMax;

      if (j == 0 ) { 

	name = "Positrons (Tracker & Calo)";


      } 

      else if ( j == 1 ) {
       
	name = "Core Region (Tracker & Calo)";


      }

      else if ( j == 2 ) {
       
	name = "High Flux Region (Tracker & Calo)";

      }

      else if ( j == 3 ) {
       
	name = "High Flux in Core Region (Tracker & Calo)";


      }

      cout << "\nRegion: " << name << endl;
 
      for (int l = 0 ; l < 2 ; l++ ) { // Fiducial Loop

	// Some strings to make changing things "easier"
	string prefix, dir0, dir1, dir2;//, ffid, tfid; 

	string fmat2 = ".png";
	string fmat1 = ".pdf"; 
	
	if (gainCorr == true) {
	  prefix = "Stn "+to_string(stn)+" | ";
	  dir0 = "St"+to_string(stn)+"_";
	  dir1 = "../testPlots/corrected/St"+to_string(stn)+"_";
	  dir2 = "../testPlots/corrected/gaus/";
	}

	else if (gainCorr == false) {
	  prefix = "";
	  dir0 = "";
	  dir1 = "../testPlots/uncorrected/";
	  dir2 = "../testPlots/uncorrected/gaus/";

	}

	string ffid, tfid;; // For file names
	 // For titles
	if (l == 0 ) { 
	  cout << tfid << endl;
	  ffid = "fid";
	  tfid = " Fiducial";
	} 
	else if (l == 1 ) { 
	  cout << tfid << endl;
	  ffid = "nonFid";
	  tfid = " Non Fiducial";
	}
	
	string ffoo[5] = {"E_vs_p_","Ep_vs_E_","Ep_vs_p_","Ep_vs_t_","Ep_vs_t_early_"};
	string tfoo[5] = {"E vs p - ","E/p vs E - ","Ep vs p - ","Ep vs t - ","Ep vs t (early) -"};
	string afoo[4] = {";Track Momentum [GeV];Energy in Calo [GeV]",";Energy in Calo [GeV];Energy in Calo / Track Momentum", ";Track Momentum [GeV];Energy in Calo / Track Momentum",";Absolute Time [#mus];Energy in Calo / Track Momentum"};

	string title[4], ftitle[4], h[5], fh[5],  fname1[5],fname2[5], f_fname[5], g_fname[5];//f_fname1[5];// = {prefix+"E vs p - "+name+";Track Momentum [GeV];Energy in Calo [GeV]";

	//string f_fname[5];
	//string g_fname[5]; // Gaussians 

	for  (int i = 0 ; i < 5 ; i++ ) {
	  title[i] = (prefix+tfoo[i]+name+afoo[i]);
	  ftitle[i] = prefix+tfoo[i]+name+tfid+afoo[i]; 
	  h[i] = dir0+ffoo[i]+to_string(j);
	  fh[i] = dir0+ffoo[i]+to_string(j)+"_"+to_string(l);
	  fname1[i] = dir1+"fit"+ffoo[i]+to_string(j)+fmat1;
	  fname2[i] = dir1+"cmap"+ffoo[i]+to_string(j)+fmat2;
	  f_fname[i] = dir1+ffoo[i]+to_string(j)+"_"+ffid+fmat1;
	  g_fname[i] = dir2+"gauss_"+ffoo[i]+to_string(j);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Book the 2D histograms and whack them into an array
	//	TObjArray *arr = new TObjArray(5); 
	TH2D *Ep = (TH2D*)rootFile->Get(h[0].c_str());
	TH2D *E = (TH2D*)rootFile->Get(h[1].c_str());
	TH2D *p = (TH2D*)rootFile->Get(h[2].c_str());
	TH2D *t = (TH2D*)rootFile->Get(h[3].c_str());
	TH2D *t_early = (TH2D*)rootFile->Get(h[4].c_str());
	//	arr->Add(Ep);//,E,p,t,t_early);
	//	//	arr->Add(E);
//	//	arr->Add(p);
	  //	arr->Add(t);
	//	arr->Add(t_early);
	// Convert to GeV and us by setting some limits by hand
	
	//  g]->GetXaxis()->SetLimits(0,4);
	//	gain[0]->GetYaxis()->SetLimits(0,4);
	Ep->GetXaxis()->SetLimits(0,4);
	Ep->GetYaxis()->SetLimits(0,4);
	//	gain[1]->GetXaxis()->SetLimits(0,4);
	E->GetXaxis()->SetLimits(0,4);
	//gain[2]->GetXaxis()->SetLimits(0,4);
	p->GetXaxis()->SetLimits(0,4);
	//	gain[3]->GetXaxis()->SetLimits(0,4.2*1500);
	t->GetXaxis()->SetLimits(0,4.2*1500);
	//	gain[4]->GetXaxis()->SetLimits(0,4.2*50);
	t_early->GetXaxis()->SetLimits(0,4.2*50);
	
	//  rootFile -> Save();
       
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

       	if (l == 0 ) {
	  // fitSlicesGaus(TH2D *hist, string title, string fname,string g_fname,int region,int type)
	  fitSlicesGaus(Ep,title[0],fname1[0],g_fname[0]);//,j,0);
	  fitSlicesGaus(E,title[1],fname1[1],g_fname[1]);//,j,1);
	  fitSlicesGaus(p,title[2],fname1[2],g_fname[2]);//,j,2);
	  fitSlicesGaus(t,title[3],fname1[3],g_fname[3]);//,j,3);
	  fitSlicesGaus(t_early,title[4],fname1[4],g_fname[4]);//,j,4);
	  //cmap(TH2D *hist, string title, string fname) {
	  cmap(Ep,title[0],fname2[0]);//,j,0);
          cmap(E,title[1],fname2[1]);//,j,1);
	  cmap(p,title[2],fname2[2]);//,j,2);
	  cmap(t,title[3],fname2[3]);//,j,3;
	  cmap(t_early,title[3],fname2[4]);//,j,4);
	  // for (int i = 0 ; i < 5 ; i++ ) { 
	  //  fitSlicesGaus(arr,title[i],fname1[i],g_fname[i]);
	  // cmap(arr,title[i],fname2[i]);
	    // delete gain[i];
	  // }
	  }

	delete  Ep, E, p, t, t_early;
	  /*
	  // fitSlicesGaus(TH2D *hist, string title, string fname,string g_fname,int region,int type)
	  fitSlicesGaus(Ep,title[0],fname1[0],g_fname[0]);//,j,0);
	  fitSlicesGaus(E,title[1],fname1[1],g_fname[1]);//,j,1);
	  fitSlicesGaus(p,title[2],fname1[2],g_fname[2]);//,j,2);
	  fitSlicesGaus(t,title[3],fname1[3],g_fname[3]);//,j,3);
	  fitSlicesGaus(t_early,title[4],fname1[4],g_fname[4]);//,j,4);
	  //cmap(TH2D *hist, string title, string fname) {
	  cmap(Ep,title[0],fname2[0]);//,j,0);
          cmap(E,title[1],fname2[1]);//,j,1);
	  cmap(p,title[2],fname2[2]);//,j,2);
	  cmap(t,title[3],fname2[3]);//,j,3;
	  cmap(t_early,title[3],fname2[4]);//,j,4);
	}

	/* Plot 2D colour maps
	   cmap(TH2D *hist, double xLo, double xHi, double yLo, double yHi, string fileName, string title)
	   Reminder: j tells you which regions we're in. 0 is positrons, 1 is core, 2 is high flux, 3 is high flux & core */


	  //	delete ; 
	 
      } // Fiducial Loop

    }// Region Loop

    // Stop station loop if there are no specified stations
    if (!gainCorr) break;

  } // Station Loop
    
  delete rootFile;
  cout << "\n-----------------End----------------" << endl;
  return 0;

}
