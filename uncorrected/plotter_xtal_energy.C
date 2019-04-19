//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// modified by: samuel.grant.18@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h


//Just going with one region

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
  for (int stn = 13; stn < 20 ; stn = stn + 6) {
    for (int fidXtal = 0; fidXtal < 2; fidXtal++) {
      plot2D("St"+std::to_string(stn)+"_E_vs_xtal_"+std::to_string(fidXtal),54,-0.5,53.5,20,0,4000,"Crystal Number", "Energy in Calo [MeV]");
      plot2D("St"+std::to_string(stn)+"_xy_calo_"+std::to_string(fidXtal),500,-150,150,500,-120,120,"Calo Decay Position X [mm]", "Calo Decay Position Y [mm]");
    }
  }
}
//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  //loop over the clusterTracker/tracker tree:

 while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {

      // require quality cut pass
      if(am->trkPassTrackQuality[i] == false) continue;
      
      double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
      
      const double logEop = log(am->EovP[i]);
      const double dt = am->Tdiff[i];
 
      const int caloSt = am->cluCaloNum[i];
      if(caloSt==13){
	if (dt<-8 || dt>3 ) continue;
      }
      else {
	if(dt<-9 || dt>1) continue;        
      }
      
      //calo range from 0->8 in x (needs flipping), 0->5 in y
      //tracker range from -120 -> 100 in x, -50 to 50 in y
      // x scaling ~9/220=0.041; y scaling ~ 6/100 = 0.06
      
      const double caloX_raw = am->cluX[i];
      const double caloY_raw = am->cluY[i];
      const int xtal = CaloNum(caloX_raw, caloY_raw);
      //Convert to mm from calo number I believe
      const double caloX = 112.5 - 25*(caloX_raw);
      const double caloY = SetCaloY(caloSt, caloY_raw);
      // Tracker decay vertices
      double trX = am->vX[i];
      double trY = am->vY[i];

      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);
      
      if(dR>30) continue;

      double t = (am -> decayTime[i]);
      // if (t < 60000) continue;

      double E = am->cluEne[i];
      double Ep = E/p;

      //========================== SNIP!
  
      bool region[3] = {false};
      // Positrons 
      if(logEop>-0.3 && logEop<0.2 ) region[0]=true;
      // High Flux - Energy - All Tracsk
      if (1200 < E && E < 2400) region[1]=true;
      // High Flux - Energy - Positrons
      if(region[0]==true && region[1]==true) region[2]=true;   
      // Select high flux positrons
      if(!region[2]) continue;

      ///////////////////////////////////////////////////////////////////////////
      Fill2D("St"+std::to_string(caloSt)+"_E_vs_xtal_0",xtal,E);
      Fill2D("St"+std::to_string(caloSt)+"_xy_calo_0",trX,trY);
      if (FiducialXtal(trX, trY)) { 
	Fill2D("St"+std::to_string(caloSt)+"_E_vs_xtal_1",xtal,E);
	Fill2D("St"+std::to_string(caloSt)+"_xy_calo_1",trX,trY);
      }
      ////////////////////////////////////////////////////////////////////////////
    }  
 }
 return;
  
}
