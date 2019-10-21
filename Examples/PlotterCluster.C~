//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

int CaloNum(int caloX, int caloY) {
  return caloX+9*caloY;
}

void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  // ctt = new clusterTrackerTrackReader(input_file, "clusterTracker");  
  // cr = new clusterTrackerClusterReader(input_file);  
  cr = new clusterReader(input_file);  
  //  tr = new trackerReader(input_file);  
  //am = new allmuonsReader(input_file);  
}

void Plotter::InitHistos() {
  const int cycles = 50;
  //  plot1D("cuts",64,-0.5,63.5,"Cut Index","Entries");
  for (int stn(13); stn < 20 ; stn = stn + 6) {
    // plot1D("St"+std::to_string(stn)+"_logEop",200,-3.5,1,"Log(E/p)","Entries");
    // plot1D("St"+std::to_string(stn)+"_dR",200,0,70,"dR [mm]","Entries");
    // plot1D("St"+std::to_string(stn)+"_dt",200,-15,15,"dt [ns]","Entries");
    //  plot2D("St"+std::to_string(stn)+"_E_vs_p",200,0,4000,200,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]"); 
    // plot2D("St"+std::to_string(stn)+"_Ep_vs_t",cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    // for(int xtal(0); xtal<54; xtal++) {
    //   plot2D("St"+std::to_string(stn)+"_Ep_vs_t_"+std::to_string(xtal),cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    // }
  }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {
  
  std::cout<<"runNum * subRunNum * eventNum * bunchNum * caloNum * xtalNum * midasSeri"<<std::endl;
  std::cout<<"************************************************************************"<<std::endl;
  // Get E/p means for normalisation
  // string inputName = "../Analyse/RootFiles/plots_EpXtal.root";
  // TFile *input = TFile::Open(inputName.c_str());
  
  while( NextClEvent() ) {

    //loop over the matches in this event:
     for(int i=0; i<cr->nHit; i++) {

      if(cr->nHit != 1) continue;       

      int runNum = cr->runNum;
      int subRunNum = cr->subRunNum;
      int eventNum = cr->eventNum;
      int bunchNum = cr->bunchNum;
      int caloNum = cr->caloNum;
      double xtalNum = cr->xtalNums[0];
      int midasSeri = cr->midasSerialNum;

      std::cout<<" * "<<runNum<<" * "<<subRunNum<<" * "<<eventNum<<" * "<<bunchNum<<" * "<<caloNum<<" * "<<xtalNum<<" * "<<midasSeri<<std::endl;

      // Fill1D("St"+std::to_string(caloNum)+"_dR",dR);
      // Fill1D("St"+std::to_string(caloNum)+"_dt",dt);
      // Fill1D("St"+std::to_string(caloNum)+"_logEop",logEop);
      // Fill2D("St"+std::to_string(caloNum)+"_Ep_vs_t",t,Ep);
      // Fill2D("St"+std::to_string(caloNum)+"_Ep_vs_t_"+std::to_string(xtal),t,Ep);
      // Fill2D("St"+std::to_string(caloNum)+"_E_vs_p",p,E);       
     }
  }
  
  return;
  
}
