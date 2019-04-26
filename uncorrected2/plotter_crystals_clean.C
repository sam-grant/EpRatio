//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// modified by: samuel.grant.18@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h


//Just going with one region



#define Plotter_C
#include "Plotter.h"
#include "TMath.h"


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

  const double ymin = 0.71;
  const double ymax = 1.25;

  for (int stn = 13; stn < 20 ; stn = stn + 6) {
    for (int fidXtal = 0 ; fidXtal < 3 ; fidXtal++) { 
      plot2D("St"+std::to_string(stn)+"_Ep_vs_xtal_"+std::to_string(fidXtal),54,0,53,200,ymin,ymax,"Crystal Number","E/p");
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
      const int xTal = CaloNum(caloX_raw, caloY_raw);

      //Convert to mm from calo number I believe
      const double caloX = 112.5 - 25*(caloX_raw);
      const double caloY = SetCaloY(caloSt, caloY_raw);
      // -75 + 25*(caloY_raw); //SetCaloY(ctt->clusterCaloNum, caloY_raw);
     
      // Tracker decay vertices
      double trX = am->vX[i];
      double trY = am->vY[i];

      //the raw distributions:
      //  Fill2D("xy_calo_raw", caloX_raw, caloY_raw);
      //Fill2D("xy_calo", caloX, caloY);
      //Fill2D("xy_track", trX, trY);
      
      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);
      
      if(dR>30) continue;

      double t = (am -> decayTime[i]);

      double E = am->cluEne[i];
      double Ep = E/p;
      //========================== SNIP!

      bool region[5] = {false};
      // All Tracks   
      region[0] = true;
      // Positrons 
      if(logEop>-0.3 && logEop<0.2 ) region[1]=true;
      // High Flux - Energy - All Tracsk
      if (1250 < E && E < 2250) region[2]=true;
      // High Flux - Energy - Positrons
      if(region[1]==true && region[2]==true) region[3]=true;   
      if(!region[3]) continue;

      int fidXtal;
      if(FiducialXtal(trX,trY)) {fidXtal = 1;}
      else if(!FiducialXtal(trX,trY)) {fidXtal = 2;}
 
      if (t < 60000) continue;

      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_xtal_0",xTal,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_xtal_"+std::to_string(fidXtal),xTal,Ep);
    
    }
    
  }

  return;

}
