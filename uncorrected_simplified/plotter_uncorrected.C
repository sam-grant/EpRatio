//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// modified by: samuel.grant.18@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

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

  double ymin;
  double ymax;

  // Start region loop
  for (int i = 0 ;  i < 4 ; i++) {
    //Mess around with the ranges, all tracks needs a bigger range
    if (i == 0 || i == 2) {
      ymin = 0.0;
      ymax = 5;
    }
    else {
      ymin = 0.71;
      ymax = 1.25;
    }
    // Start fiducial loop
    for (int j = 0 ; j < 3 ; j++ ) {
      // 0 all tracks, 1 fiducial, 2 non fiducial
      plot2D("E_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0,4000,"p [MeV]","E [MeV]");
      plot2D("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,ymin,ymax,"E [MeV]","E/p");
      plot2D("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(j),150,0,5*126000,500,ymin,ymax,"t [ns]","E/p");
      plot2D("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(j),50,0,210000,500,ymin,ymax,"t [ns]", "E/p");
      plot2D("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,ymin,ymax,"p [MeV]","E/p");
      plot2D("xy_calo_"+std::to_string(i)+"_"+std::to_string(j),500,-150,150,500,-120,120,"Calo Position X [mm]","Calo Position Y [mm]");
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

      if(am->decayHitVolume[i] == true) continue;
    
      if( am->trkPvalue[i] < 0.05) continue;
      // require quality cut pass
      if(am->trkPassTrackQuality[i] == false) continue;
      
      
      double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
      // Fill2D("E_vs_p", p, am->cluEne[i]);
      
      const double logEop = log(am->EovP[i]);
      const double dt = am->Tdiff[i];
      //Fill1D("Eop", logEop);
      // Fill1D("dt", dt );

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
      const int xtalNum = CaloNum(caloX_raw, caloY_raw);
      if(xtalNum <-0.01) continue;
      
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
      // Time cut 
      //  if (t < 30000) continue;
      double E = am->cluEne[i];
      double Ep = E/p;
      //========================== SNIP!
      
      // Fiducial cut 
      int k;
      if (Fiducial(caloX, caloY) == true) {k=1;}
      else if (Fiducial(caloX, caloY) == false) {k=2;}
 
      bool region[5] = {false};
    
      // All Tracks   
      region[0] = true;
      // Positrons 
      if(logEop>-0.3 && logEop<0.2 ) region[1]=true;
      // High Flux - Energy - All Tracsk
      if (1250 < E && E < 2250) region[2]=true;
      // High Flux - Energy - Positrons
      if(region[1]==true && region[2]==true) region[3]=true;   
    
      for (int i = 0 ; i < 4 ; i++ ) {
   
	if(region[i]) {
	  // All tracks
	  Fill2D("E_vs_p_"+std::to_string(i)+"_0",p,E);
	  Fill2D("Ep_vs_E_"+std::to_string(i)+"_0",E,Ep);
	  Fill2D("Ep_vs_p_"+std::to_string(i)+"_0",p,Ep);
	  Fill2D("Ep_vs_t_"+std::to_string(i)+"_0",t,Ep);
	  Fill2D("Ep_vs_t_early_"+std::to_string(i)+"_0",t,Ep);
	  Fill2D("xy_calo_"+std::to_string(i)+"_0",caloX,caloY);
	  // Fiducial and non-fiducial tracks
	  Fill2D("E_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,E);
	  Fill2D("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(k),E,Ep);
	  Fill2D("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,Ep);
	  Fill2D("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
	  Fill2D("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
	  Fill2D("xy_calo_"+std::to_string(i)+"_"+std::to_string(k),caloX,caloY);	  
	}

      }
      
      
    }
    
  }

  return;

}
