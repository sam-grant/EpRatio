//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk

//Enable the tree you want to use here
//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

//This simple example makes plots of E/p andE vs p for matched tracks & clusters

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"


void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  ctt = new clusterTrackerTrackReader(input_file);  
  // cr = new clusterTrackerClusterReader(input_file);  
  // cl = new clusterReader(input_file);  
}

void Plotter::InitHistos() {

  //define the histograms here
  //arguments (^ = optional) :
  // name (also used as title), nbins, xlow, xhigh, xtitle^, ytitle^, line colour^
  plot1D("Eop", 100, -4,4, "log (E/p)");

  //2D: name xbins, xlo, xhi, ybins, ylo, yhi, xtitle, ytitle
  plot2D("E_vs_p", 100, 0,4000, 100, 0,4000, "p", "E");
  
};



//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {

    if(ctt->clusterCaloNum ==19) continue;

    const double logEop = log(ctt->clusterEoverP);
    Fill1D("Eop", logEop);
    Fill2D("E_vs_p", ctt->trackMomentum, ctt->clusterE);

  } //end of loop over entries

  return;
}





