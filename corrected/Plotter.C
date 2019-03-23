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


  for (int i = 0 ;  i < 5 ; i++) {

    // Region Loop (first number)
    plot2DTr("E_vs_p_"+std::to_string(i),500,0,4000,500,0,4000,"p [MeV]","E [MeV]");
    plot2DTr("Ep_vs_E_"+std::to_string(i),500,0,4000,500,0.71,1.25,"E [MeV]","E/p");
    plot2DTr("Ep_vs_t_"+std::to_string(i),150,0,5*126000,500,0.71,1.25,"t [ns]","E/p");
    plot2DTr("Ep_vs_t_early_"+std::to_string(i),50,0,210000,500,0.71,1.25,"t [ns]", "E/p");
    plot2DTr("Ep_vs_p_"+std::to_string(i),500,0,4000,500,0.71,1.25,"p [MeV]","E/p");
    plot2DTr("xy_calo_"+std::to_string(i),500,-150,150,500,-120,120,"Calo Position X [mm]","Calo Position Y [mm]");

    for (int j = 0 ; j < 2 ; j++ ) {

      // 0 fiducial, 1 non fiducial (second number)
      plot2DTr("E_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0,4000,"p [MeV]","E [MeV]");
      plot2DTr("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0.71,1.25,"E [MeV]","E/p");
      plot2DTr("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(j),150,0,5*126000,500,0.71,1.25,"t [ns]","E/p");
      plot2DTr("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(j),50,0,210000,500,0.71,1.25,"t [ns]", "E/p");
      plot2DTr("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0.71,1.25,"p [MeV]","E/p");
      plot2DTr("xy_calo_"+std::to_string(i)+"_"+std::to_string(j),500,-150,150,500,-120,120,"Calo Position X [mm]","Calo Position Y [mm]");
    }

  }

}


void Plotter::Run() {
  
  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {
    
    // Volume cut, P value cut, Momentum cut at 2.3 GeV====

    if(ctt->hitVolume == true) continue;
    if(ctt->trackPValue < 0.05) continue;

    // Time difference
    const double dt = ctt->trackTimeDiff;
    
    // Calo Energy
    const double E = ctt->clusterE;

    // Track Momentum
    const double p = ctt -> trackMomentum;

    //====E/p====
    const double logEop = log(ctt->clusterEoverP);

    //====Tracker decay times, ns====
    double t = (ctt -> decayTime);

   
    
    // dt matching
    if ( dt < -10 && dt > 6) continue;

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


    //====cut 30 us, completely wipes out lost muons====
    // if (t < 30000) continue;    

    //====Decay radii, tracker and calo====
    const double magicRadius = 7112; //[mm]
    const double dX = caloX - cTrX;
    const double dY = caloY - cTrY;
    const double cR = sqrt(dX*dX + dY*dY);
    const double R = sqrt(TrX*TrX+TrZ*TrZ) - magicRadius;

    // Clean up zeros
    if (TrX == 0 && TrY == 0 && TrZ == 0) continue;

    // Check which cal crystal gets hit:
    const int caloNum = CaloNum(caloX_raw, caloY_raw);
 
    // dR Match

    const double dR = sqrt(dX*dX + dY*dY);
    if (dR > 30) continue;

    const double Ep = E/p;

    // Time cut 
    if (t < 30000) continue;

    // Fiducial cut 
    int k;

    if (Fiducial(cTrX, cTrY) == true) {k=0;}
    else if (Fiducial(cTrX, cTrY) == false) {k=1;}
 
    bool region[5] = {false};
    
    // Positrons    
    if(logEop>-0.3 && logEop<0.2 ) region[0]=true;
    // High Flux - Energy
    if (1250 < E && E < 2250) region[1]=true;
    // High Flux - Momentum
    if (1400 < p && p < 2400) region[2]=true;
    // High Flux - Energy - Positrons
    if(region[0]==true && region[1]==true) region[3]=true;
    // High Flux - Momentum - Positrons
    if(region[0]==true && region[2]==true) region[4]=true;
    
    for (int i = 0 ; i < 5 ; i++ ) {
   
      if(region[i]) {
	// All calo & tracker tracks
	Fill2DTr("E_vs_p_"+std::to_string(i),p,E);
	Fill2DTr("Ep_vs_E_"+std::to_string(i),E,Ep);
	Fill2DTr("Ep_vs_p_"+std::to_string(i),p,Ep);
	Fill2DTr("Ep_vs_t_"+std::to_string(i),t,Ep);
	Fill2DTr("Ep_vs_t_early_"+std::to_string(i),t,Ep);
	Fill2DTr("Ep_vs_p_"+std::to_string(i),p,Ep);
	Fill2DTr("xy_calo_"+std::to_string(i),cTrX,cTrY);

	// Fiducial and non-fiducial tracks
	Fill2DTr("E_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,E);
	Fill2DTr("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(k),E,Ep);
	Fill2DTr("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,Ep);
	Fill2DTr("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
	Fill2DTr("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
	Fill2DTr("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,Ep);
	Fill2DTr("xy_calo_"+std::to_string(i)+"_"+std::to_string(k),cTrX,cTrY);
	  

      }

    }

  } //event loop

  delete ctt;
  return;

}





