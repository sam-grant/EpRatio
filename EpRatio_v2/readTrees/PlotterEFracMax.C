//////////////////////////////
// Sam Grant                //
// Test branch variables    //
// Read tracker branch      //
//////////////////////////////

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"

const float g2Period = 4.365;
const float eFracMaxCut = 0.85;

void Plotter::InitTrees(TString input_file) {
   ttc = new trackAndTrackCaloReader(input_file);
   //tr = new trackerReader(input_file); 
}

void Plotter::InitHistos() {

  // Cut params
  plot1D("eFracMax",100,0,1,"Cluster energy fraction in the most energetic crystal");
  plot1D("caloVertexClusterTimeDiff",35,-20,15,"Calo vertex time #minus cluster time [ns]");
  plot1D("caloVertexClusterRadialDiff",100,0,100,"Calo vertex time #minus cluster time [mm]");
  plot1D("logEoverP",140,-5,3,"log(E/p)");
  plot2D("EvsP",128,0,3200,128,0,3200,"Cluster energy [MeV]","Track momentum [MeV]");

  //plot1D("decayVertexTime",4700, 0, 4700*0.148936, "Cluster time [ns]","Decay vertices");
  //plot1D("trackClusterRadialDiff",1000,0,100, ";Calo radial position #minus track vertex radial position [mm]""")
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {
  //    int count = 0;
  //loop over the clusterTracker/tracker tree:
  while( NextTrackAndTrackCaloEvent() ) {
    
    //if(!ttc->passCaloVertexQuality) continue;
/*    if(!ttc->hasCaloVertex) continue;*/
    if(!ttc->hasDecayVertex) continue;
    if(!ttc->passTrackQuality) continue;
    //if(!ttc->passDecayVertexQuality) continue;

    int stn = ttc->station;
    // Filter out laser fills
    // if(ttc->inFillLaserCount!=0) continue;
    // Cluster varaibles are arrays


    for(int i = 0; i<ttc->nCluMatches; i++) { 

      // if(!ttc->passPositronVertexQuality[i]) continue;

      Fill1D("eFracMax",ttc->xtalMaxEnergyFrac[i]);
      Fill2D("EvsP",ttc->trackMomentum,ttc->clusterEnergy[i]);
      Fill1D("logEoverP",ttc->logEoverP[i]);
      Fill1D("caloVertexClusterRadialDiff",ttc->caloVertexClusterRadialDiff[i]);
      Fill1D("caloVertexClusterTimeDiff",ttc->caloVertexClusterTimeDiff[i]);

    }


  }

  delete ttc;
  //delete tr;
  return;

}
