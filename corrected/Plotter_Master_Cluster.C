// General plotter using the cluster matched tree

// gavin.hesketh@ucl.ac.uk
// samuel.grant.18@ucl.ac.uk

#define Plotter_cxx
#include "Plotter.h"
#include "TMath.h"

const double pi = 3.14159265359;

int CaloNum(int caloX, int caloY) {
  return caloX+9*caloY;
}
void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
   ctt = new clusterTrackerTrackReader(input_file, "clusterTracker");
  // cr = new clusterTrackerClusterReader(input_file);
  // cl = new clusterReader(input_file);
  // tr = new trackerReader(input_file);
}


void Plotter::InitHistos() {

  plot2DTr("Ep_vs_E",500,0,4000,500,0,4,"E [MeV]","E/p");
  plot2DTr("Ep_vs_t",500,0,5*126000,500,0,4, "t [ns]","E/p");
  plot2DTr("Ep_vs_t_early",500,0,4200,500,0,4,"t [ns]", "E/p");

}


void Plotter::Run() {
  
  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {
    
    // Define run number
    int run = ctt -> runNum;
  
    // Volume cut, P value cut, Momentum cut at 2.3 GeV====

    if(ctt->hitVolume == true) continue;
    if(ctt->trackPValue < 0.05) continue;

    // Time difference
    const double dt = ctt->trackTimeDiff;
    
    //====Calo Energy
    const double E = ctt->clusterE;

    //====E/p====
    const double logEop = log(ctt->clusterEoverP);

    // Track Momentum
    const double p = ctt -> trackMomentum;

    const double caloX_raw = ctt->clusterX;
    const double caloY_raw = ctt->clusterY;
    const double caloX = 112.5 - 25*(caloX_raw);
    const double caloY = SetCaloY(ctt->clusterCaloNum, caloY_raw);
    // -75 + 25*(caloY_raw); //SetCaloY(ctt->clusterCaloNum, caloY_raw);

    //====Calo Decay Vertices====
    double cTrX = ctt->caloVertexPosX;
    double cTrY = ctt->caloVertexPosY;

    //====Tracker decay vertices====
    double TrX = ctt->decayVertexPosX; 
    double TrY = ctt->decayVertexPosY;
    double TrZ = ctt->decayVertexPosZ;

    //====Tracker decay times, ns====
    double t = (ctt -> decayTime);
     //====cut 30 us, completely wipes out lost muons====
    // if (t < 30000) continue;    

    //====Decay radii, tracker and calo====
    const double magicRadius = 7112; //[mm]
    const double dX = caloX - cTrX;
    const double dY = caloY - cTrY;
    const double cR = sqrt(dX*dX + dY*dY);
    const double R = sqrt(TrX*TrX+TrZ*TrZ) - magicRadius;

    //====Angle of rotation in xz plane, dependant on quadrant====
    /* xz plane with theta going clockwise, 12 o'clock: inflector, station 1
       6 o'clock we have station 13
       9 o'clock we have station 19 */
    double theta = 0;

    if ( TrX > 0 && TrZ > 0) { // quad 1
      theta = atan(TrZ/TrX);
      } 
    else if ( TrX < 0 && TrZ > 0 ) { // quad 2
      theta = -1 * atan(TrX/TrZ) + pi/2 ;
    } 
    else if (  TrX < 0 && TrZ < 0 ) { // quad 3
      theta = atan(TrZ/TrX) + pi;
    } 
    else if ( TrX > 0 && TrZ < 0 ) { // quad 4
      theta = -1 * atan(TrX/TrZ)+ 3*pi/2; 
    }
   
    // Clean up zeros
    if (TrX == 0 && TrY == 0 && TrZ == 0) continue;

    // Check which cal crystal gets hit:
    const int caloNum = CaloNum(caloX_raw, caloY_raw);
    if(caloNum < -0.01) continue;

    // Hard cut on radius to get rid of low tail
    if (R > 200 || R < -200) continue;
 
    // dR Match

    const double dR = sqrt(dX*dX + dY*dY);

    const double Ep = E/p;
    // dR cut

    if (dR > 30) continue;

    // dt cut

    // Convert to us

    if ( dt < -10 && dt > 6) continue;


      Fill2DTr("Ep_vs_E",E,Ep);
      Fill2DTr("Ep_vs_t",t,Ep);
      Fill2DTr("Ep_vs_t_early",t,Ep);
 
  } //event loop



  delete ctt;
  return;

}





