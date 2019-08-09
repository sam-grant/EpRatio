#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"


int CaloNum(int caloX, int caloY) {
  return caloX+9*caloY;
}

void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  // ctt = new clusterTrackerTrackReader(input_file, "clusterTracker");  
  // cr = new clusterTrackerClusterReader(input_file);  
  // cl = new clusterReader(input_file);  
  //  tr = new trackerReader(input_file);  
  am = new allmuonsReader(input_file);  
}

void Plotter::InitHistos() {

  double ymin = 0.5;
  double ymax = 1.5;
  
  for (int stn = 13; stn < 20 ; stn = stn + 6) {
       plot2D("St"+std::to_string(stn)+"_Ep_vs_xtal",54,-0.5,53.5,1000,ymin,ymax,"Crystal Number","E/p");
       plot2D("St"+std::to_string(stn)+"_trkX_vs_trkY",200,-150,150,200,-120,120,"Forwards extrapolated track position X [mm]","Forwards extrapolated track positrion y [mm]");
   }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  // Quality cut var
  bool qualityFail;
  // Set a cut to be skipped
  int skipCut = 18;

  // Initialise an empty vector to store the results from 64 bit Q
  vector<int> failedCuts_;
  for(int i = 0; i < 64; i++){
    failedCuts_.push_back(0);
  }
  //loop over the clusterTracker/tracker tree:

  while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {

      if(am->nhits[i] != 1) continue;
      if(am->cluTime[i] < 60000) continue;

      // Empty vector to contain the results bit by bit (refreshing each event)
      vector<int> failedCutsBits_;
      for(int i = 0; i < 64; i++){
        failedCutsBits_.push_back(0);
      }

      // 64 bit integer refering to the cut results
      long long Q = am->trkPositronVertexQualityStatus[i];

      // Scan across the bits and find the non zero ones
      // Put these in a hist, and a vector
      for (int iCut = 63; iCut >= 0; iCut--) {
        failedCutsBits_.at(iCut) = (Q >> iCut) & 1;
        if( (Q >> iCut) & 1 ) {
          failedCuts_.at(iCut)++;
        }
      }

      // Define the qualityFail bool (if skipping cuts)
      for (int iCut = 0; iCut < 63; iCut++) {
        if(iCut == skipCut) continue;
        if(failedCutsBits_.at(iCut) == 0) {
          qualityFail = false;
        }
        else {
          qualityFail = true;
          break;
        }
      }

      // If using all cuts, just set (Q == true) continue;
      if(qualityFail) continue;

      int caloSt = am->cluCaloNum[i];
      if(caloSt > 19) continue;

      int trkSt = am->trkStationNum[i];
      double trX = am->vX[i];
      double trY = am->vY[i];
      double caloX_raw = am->cluX[i];
      double caloY_raw = am->cluY[i];
      int xtal = CaloNum(caloX_raw, caloY_raw);

      if(!FiducialHacky(xtal)) continue;
      //      std::cout<<xtal<<std::endl;

      double E = am->cluEne[i];
      double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i]+ am->trkMomZ[i]*am->trkMomZ[i]);
      double Ep = E/p;

      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_xtal",xtal,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_trkX_vs_trkY",trX,trY);
    }
  }
  return;
}
