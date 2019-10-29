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
  // cl = new clusterReader(input_file);  
  //  tr = new trackerReader(input_file);  
  am = new allmuonsReader(input_file);  
}

void Plotter::InitHistos() {
  plot2D("VR",1000,-150,120,1000,-100,100,"Track radial position [mm]", "Track vertical position [mm]"); 
}

void Plotter::Run() {
  
  while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {

     if(am->trkPassPositronVertexQuality[i] == false) continue;

      Fill2D("VR",am->vX[i],am->vY[i]);

    }
  }
  
  return;
  
}
