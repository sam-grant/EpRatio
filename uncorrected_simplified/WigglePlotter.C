//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"


void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  // ctt = new clusterTrackerTrackReader(input_file);  
  // ctc = new clusterTrackerClusterReader(input_file);  
   cr = new clusterReader(input_file);  
}


void Plotter::InitHistos() {

  //arguments (^ = optional) :
  // name (also used as title), nbins, xlow, xhigh, xtitle^, ytitle^, line colour^
  plot1D("time", 100, 0, 700, "time [us]");
  plot1D("energy", 700, 0, 7000, "energy [MeV]");

  double binWidth = 0.1491;
  double startTime = 30.;
  double endTime = 500.;
  int nbins = (endTime - startTime) / binWidth;
  endTime = startTime + (nbins * binWidth);
  
  plot1D("data", nbins, startTime, endTime, "time [us]");

  //make plots for each calo - calos are number 1-24
  for (int i(1); i < 25; i++){
    plot2D("energyVsTime_"+std::to_string(i), nbins, startTime, endTime, 700, 0, 7000, "time [us]", "energy [MeV]");
    plot1D("energy_"+std::to_string(i), 700, 0, 7000, "energy [MeV]");
    plot1D("data_"+std::to_string(i), nbins, startTime, endTime, "time [us]");
  }

};



//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  int iCluster = 0;
  //loop over the clusterTree/clusters tree:
  while( NextClEvent() ) {
    // if (iCluster > 10000) break; //why?
    
    const double time = cr->time * 0.00125;
    const double energy =  cr->energy;

    Fill1D("time", time);
    Fill1D("energy", energy);

    TString caloNum = std::to_string(cr->caloNum);
    
    Fill1D( "energy_"+caloNum, energy);
    Fill2D( "energyVsTime_"+caloNum, time, energy);
    
    if (time >= 30. && energy > 1700.){
      Fill1D("data", time);
      Fill1D("data_"+caloNum, time);
    }
    iCluster++;
  }

  
  return;
}





