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

// Colour map plotter
void cmap(TH2D *hist, string title, string fname) { // int region, int type) {

  TCanvas *c = new TCanvas("c", "c", 2000, 1000);
  gStyle->SetPalette(55);
  hist->SetStats(0);
  // hist->DrawCopy("COLZ");
  hist->SetTitle(title.c_str());
  c->SetRightMargin(0.13);
  hist->DrawCopy("COLZ");
  c->SaveAs(fname.c_str()); 

  delete c, hist;
  return;
}

// Fit gaussians to slices along the x-axis and plot their means
void fitSlicesGaus(TH2D *hist, string title, string fname,string g_fname) {//,int region,int type) {
  
  int nBins = hist->GetNbinsX(); 
  // Hardcode this to change the number of slices
  int nSlices = nBins;
  // Get the length of the slice in x
  int length = nBins / nSlices;
  // Define the gaussian 
  TF1 *gFunc = new TF1("gFunc", "gaus");
  // Declare step edges
  int loStep;
  int hiStep;
  // Book a 1D hist for the Y projection slices
  TH1D *projY;
  // Book a 1D hist to take the results of each fit on it's X axis
  TH1D *projX = hist -> ProjectionX("prX");
  projX -> Rebin(length);
  projX -> Reset();
  // Threshold (minimum number of bins), to define the fit range
  double threshold;
  double fitMin;
  double fitMax;
  double chisqNDF;

  // Slice loop
  for(int i = 0 ; i < nSlices; i++) {
    // Define steps
    loStep = i*length;
    hiStep = (i+1)*length;
    // Perform projection
    projY = hist->ProjectionY("prY",loStep,hiStep-1);
    // Clean up bins with nothing in them
    if (projY -> GetEntries() < 1) continue; 
    //Define the threshold, trying to avoid those tails. Half maximum works. Hacky but never mind.
    threshold = (projY -> GetMaximum())*(1/2);
    // Define the fit range
    fitMin = projY -> GetBinCenter( projY -> FindFirstBinAbove(threshold,1));
    fitMax = projY -> GetBinCenter( projY -> FindLastBinAbove(threshold,1));
    // "Q" : supress printing "M" use minuit to improve fit result
    projY -> Fit(gFunc,"QM","",fitMin,fitMax);
    chisqNDF = (gFunc -> GetChisquare()) / (gFunc -> GetNDF()) ;
    
    //if (chisqNDF < 0 || 4  < chisqNDF ) continue;
    cout << "chisqndf = " << chisqNDF << endl;
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

  //Force the ranges to be sensible if ROOT's stupid autoscale fails like normal
  double xmin = projX->GetBinCenter( projX -> FindFirstBinAbove(0,1) );
  double xmax = projX->GetBinCenter( projX -> FindLastBinAbove(0,1) );
  projX->GetXaxis()->SetRangeUser(xmin,xmax);

  // Generate the profile 
  TProfile *tpf = new TProfile();
  tpf = hist -> ProfileX();
  // Draw the means, and compare with the profile 
  projX->SetName("X Slice Gauss Fits");
  tpf->SetName("X Profile");
  TCanvas *c2 = new TCanvas();
  projX->Draw();
  // tpf->Draw("same");
  projX->SetTitle(title.c_str());
  projX->GetXaxis()->SetRangeUser(xmin,xmax);
  projX->SetMarkerColor(kMagenta);
  projX->SetLineColor(kMagenta+2);
  projX->SetStats(0);
  tpf->SetMarkerColor(kMagenta+2);
  tpf->SetLineColor(kMagenta+2);
  tpf->SetStats(0);
  //gPad->SetGrid();
  // c2->BuildLegend();
  c2->SaveAs(fname.c_str());

  delete c2, tpf, projX;
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
  // Pick the corresponding file
  string whichFile;
  if ( gainCorr ) { 
    whichFile = "../corrected/merged_corrected2.root";//../uncorrected/plots_Documents_forSa.root";//"../corrected/merged_corrected.root";
  }
  else if ( !gainCorr ) { 
     whichFile = "../uncorrected/forSam_qON.root";//"../uncorrected/plots_Documents_forSa.root";//merged_uncorrected.root";
    //  whichFile = "/unix/muons/g-2/omegaEU/forSam_withCorrection_50.root";
  }
    
  // Open it
  TFile *rootFile = TFile::Open(whichFile.c_str());
    
  int stn;
  // Start station loop  
  for (int i = 0 ; i < 2 ; i++ ) { 
    // Uncorrected ntuples do not define stations, account for this
    if (gainCorr) {
      if (i == 0 ) { stn = 12; } 
      else if (i == 1) {stn = 18; }
      cout << "\nStation: "+to_string(stn)+"\n";
    }

    // Start plot region loop
    for (int j = 0 ; j < 4 ; j++ ) { 

      string name;
      double yMin, yMax;
      if ( j == 0 ) { 
	name = "All Tracks";
      }
      else if (j == 1 ) { 
	name = "e^{+}";
      } 
      else if ( j == 2 ) {     
	name = "All Tracks, High Flux";
      }

      else if ( j == 3 ) {
	name = "e^{+}, High Flux";
      }

      cout << "\nRegion: " << name << endl;

      // Start fiducial region loop
      for (int l = 0 ; l < 3 ; l++ ) {
	// Define all the strings needed for filenames, titles, booking histograms
	string prefix, dir0, dir1, dir2, fid;
	string fmat1 = ".png";
	string fmat2 = ".pdf"; 
	string title[6], h[6], fit_fname[5], cmap_fname[6], g_fname[5];
	string ffoo[6] = {"E_vs_p_","Ep_vs_E_","Ep_vs_p_","Ep_vs_t_","Ep_vs_t_early_","xy_calo_"};
	string tfoo[6] = {"E vs p, ","E/p vs E, " ,"Ep vs p, ","Ep vs t, ","Ep vs t (early), ","XY Cluster, "};
	string afoo[6] = {";Track Momentum [GeV];Energy in Calo [GeV]",";Energy in Calo [GeV];Energy in Calo / Track Momentum", ";Track Momentum [GeV];Energy in Calo / Track Momentum",";Absolute Time [#mus];Energy in Calo / Track Momentum",";Absolute Time [#mus];Energy in Calo / Track Momentum",";X Cluster Position [mm];Y Cluster Position [mm]"};

	if (gainCorr == true) {
	  prefix = "Stn "+to_string(stn)+" | ";
	  dir0 = "St"+to_string(stn)+"_";
	  dir1 = "../plots/corrected/St"+to_string(stn)+"_";
	  dir2 = "../plots/corrected/gaus/";
	}
	else if (gainCorr == false) {
	  prefix = "";
	  dir0 = "";
	  // dir1 = "../plots/uncorrected/";
	  dir1 = "../plots/forSam/qON/";
	  dir2 = "../plots/uncorrected/gaus/";
	}

	// For titles
	if (l == 1 ) { 
      
	  cout << fid << endl;
	  //  ffid = "fid";
	  fid = ", Fiducial";
	} 
	else if (l == 2 ) { 
       
	  cout << fid << endl;
	  // ffid = "nonFid";
	  fid = ", Non Fiducial";
	}

	// Put strings together for iterating hist/file/title names
	for  (int i = 0 ; i < 6 ; i++ ) {

	  h[i] = dir0+ffoo[i]+to_string(j)+"_"+to_string(l);
	  cmap_fname[i] = dir1+"cmap_"+ffoo[i]+to_string(j)+to_string(l)+fmat1;

	  if (i < 5) {
	    fit_fname[i] = dir1+"fit_"+ffoo[i]+to_string(j)+to_string(l)+fmat1;
	    g_fname[i] = dir2+"gauss_"+ffoo[i]+to_string(j)+to_string(l);
	  }
 
	  if (l==0) {
	    title[i] = prefix+tfoo[i]+name+afoo[i];
	  }
	  else {
	    title[i] = prefix+tfoo[i]+name+fid+afoo[i];
	  }

	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Book the 2D histograms
       	TH2D *Ep = (TH2D*)rootFile->Get(h[0].c_str());
	TH2D *E = (TH2D*)rootFile->Get(h[1].c_str());
	TH2D *p = (TH2D*)rootFile->Get(h[2].c_str());
	TH2D *t = (TH2D*)rootFile->Get(h[3].c_str());
	TH2D *t_early = (TH2D*)rootFile->Get(h[4].c_str());
	TH2D *xy_calo = (TH2D*)rootFile->Get(h[5].c_str());
	//	cout << h[1] << endl;
	//	Ep->GetXaxis()->SetLimits(0,4);
	//Ep->GetYaxis()->SetLimits(0,4);
	E->GetXaxis()->SetLimits(0,4);
	p->GetXaxis()->SetLimits(0,4);
	t->GetXaxis()->SetLimits(0,4.2*1500);
	t_early->GetXaxis()->SetLimits(0,4.2*50);

	cmap(Ep,title[0],cmap_fname[0]);
	cmap(E,title[1],cmap_fname[1]);
	cmap(p,title[2],cmap_fname[2]);
	cmap(t,title[3],cmap_fname[3]);
	cmap(t_early,title[4],cmap_fname[4]);
	cmap(xy_calo,title[5],cmap_fname[5]);

      	//fitSlicesGaus(Ep,title[0],fit_fname[0],g_fname[0]);
	fitSlicesGaus(E,title[1],fit_fname[1],g_fname[1]);
	fitSlicesGaus(p,title[2],fit_fname[2],g_fname[2]);
	fitSlicesGaus(t,title[3],fit_fname[3],g_fname[3]);
	fitSlicesGaus(t_early,title[4],fit_fname[4],g_fname[4]);

	//	cmap(Ep,title[0],cmap_fname[0]);

	delete E, p, t, t_early;
      	 
      } // Fiducial Loop

    }// Region Loop

    // Stop station loop if there are no specified stations, (uncorrected does not specify stations
    if (!gainCorr) break;

  } // Station Loop
    
  delete rootFile;
  cout << "\n-----------------End----------------" << endl;
  return 0;

}
