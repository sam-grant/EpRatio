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


  
  for (int i = 0 ;  i < 5 ; i++) {
    // Region Loop (first number)
    plot2D("E_vs_p_"+std::to_string(i),500,0,4000,500,0,4000,"p [MeV]","E [MeV]");
    plot2D("Ep_vs_E_"+std::to_string(i),500,0,4000,500,0.71,1.25,"E [MeV]","E/p");
    plot2D("Ep_vs_t_"+std::to_string(i),150,0,5*126000,500,0.71,1.25,"t [ns]","E/p");
    plot2D("Ep_vs_t_early_"+std::to_string(i),50,0,210000,500,0.71,1.25,"t [ns]", "E/p");
    plot2D("Ep_vs_p_"+std::to_string(i),500,0,4000,500,0.71,1.25,"p [MeV]","E/p");
    plot2D("xy_calo_"+std::to_string(i),500,-150,150,500,-120,120,"Calo Position X [mm]","Calo Position Y [mm]");

    for (int j = 0 ; j < 2 ; j++ ) {

      // 0 fiducial, 1 non fiducial (second number)
      plot2D("E_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0,4000,"p [MeV]","E [MeV]");
      plot2D("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0.71,1.25,"E [MeV]","E/p");
      plot2D("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(j),150,0,5*126000,500,0.71,1.25,"t [ns]","E/p");
      plot2D("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(j),50,0,210000,500,0.71,1.25,"t [ns]", "E/p");
      plot2D("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(j),500,0,4000,500,0.71,1.25,"p [MeV]","E/p");
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

      //    if(ctt->hitVolume == true) continue;
    
      if( am->trkPvalue[i] < 0.05) continue;

      
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
      if (t < 30000) continue;
      double E = am->cluEne[i];
      double Ep = E/p;
      //========================== SNIP!
      
      // Fiducial cut 
      int k;

      if (Fiducial(caloX, caloY) == true) {k=0;}
      else if (Fiducial(caloX, caloY) == false) {k=1;}
 
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
      Fill2D("E_vs_p_"+std::to_string(i),p,E);
      Fill2D("Ep_vs_E_"+std::to_string(i),E,Ep);
      Fill2D("Ep_vs_p_"+std::to_string(i),p,Ep);
      Fill2D("Ep_vs_t_"+std::to_string(i),t,Ep);
      Fill2D("Ep_vs_t_early_"+std::to_string(i),t,Ep);
      Fill2D("Ep_vs_p_"+std::to_string(i),p,Ep);
      Fill2D("xy_calo_"+std::to_string(i),caloX,caloY);

      // Fiducial and non-fiducial tracks
      Fill2D("E_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,E);
      Fill2D("Ep_vs_E_"+std::to_string(i)+"_"+std::to_string(k),E,Ep);
      Fill2D("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,Ep);
      Fill2D("Ep_vs_t_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
      Fill2D("Ep_vs_t_early_"+std::to_string(i)+"_"+std::to_string(k),t,Ep);
      Fill2D("Ep_vs_p_"+std::to_string(i)+"_"+std::to_string(k),p,Ep);
      Fill2D("xy_calo_"+std::to_string(i)+"_"+std::to_string(k),caloX,caloY);
	  

    }

    }



      
      
    }
    
    }


      return;


    }
