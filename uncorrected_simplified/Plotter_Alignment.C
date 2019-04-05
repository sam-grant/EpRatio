//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk

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
  ctt = new clusterTrackerTrackReader(input_file, "clusterTracker");  
  // cr = new clusterTrackerClusterReader(input_file);  
  // cl = new clusterReader(input_file);  
}

void Plotter::InitHistos() {

  //arguments (^ = optional) :
  // name (also used as title), nbins, xlow, xhigh, xtitle^, ytitle^, line colour^
  plot2DTr("mu_xy_track", 300,-150,150, 200,-100,100, "track x", "track y");
  plot1DTr("mu_time", 100, 0, 100000, "cluster time [ns]");
  
  plot2DTr("mu_split_xy_track", 300,-150,150, 200,-100,100, "track x", "track y");
  plot1DTr("mu_split_time", 100, 0, 100000, "cluster time [ns]");

  plot1DTr("mu_17_left_E", 250, 0, 500, "calo energy [MeV]");
  plot1DTr("mu_17_right_E", 250, 0, 500, "calo energy [MeV]");

  plot1DTr("mu_17_left_p", 200, 0, 4000, "track momentum [MeV]");
  plot1DTr("mu_17_right_p", 200, 0, 4000, "track momentum [MeV]");

  plot1DTr("mu_17_left_pVal", 100, 0, 1, "p-value");
  plot1DTr("mu_17_right_pVal", 100, 0, 1, "p-value");

  plot1DTr("mu_17_left_y_decay", 100, -2000, 2000, "decay y [mm]");
  plot1DTr("mu_17_right_y_decay", 100, -2000, 2000, "decay y [mm]");

  plot1DTr("mu_18_left_E", 250, 0, 500, "calo energy [MeV]");
  plot1DTr("mu_18_right_E", 250, 0, 500, "calo energy [MeV]");

  plot1DTr("mu_18_left_p", 200, 0, 4000, "track momentum [MeV]");
  plot1DTr("mu_18_right_p", 200, 0, 4000, "track momentum [MeV]");

  plot1DTr("mu_18_left_pVal", 100, 0, 1, "p-value");
  plot1DTr("mu_18_right_pVal", 100, 0, 1, "p-value");

  plot1DTr("mu_18_left_y_decay", 100, -1000, 1000, "decay y [mm]");
  plot1DTr("mu_18_right_y_decay", 100, -1000, 1000, "decay y [mm]");

  plot1D("mu_cluster_hits", 11, -0.5, 10.5, "p-value");

  
  plot2DTr("mu_angle_vs_E", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_E_pop1", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_E_pop2", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_x", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_pop1", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_pop2", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");

  plot1DTr("mu_p_pop1_left", 200,0,4000, "track momentum [MeV]");
  plot1DTr("mu_p_pop1_right", 200,0,4000, "track momentum [MeV]");
  
  
  
  plot2DTr("mu_angle2_vs_E", 250, 80, 300, 100, -0.1, 0.1, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle2_vs_y", 300,-150, 150, 100, -0.1, 0.1, "track y [mm]", "angle [rad]");

  plot2DTr("mu_angle_vs_E_2hit", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_2hit", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");

  plot2DTr("mu_angle2_vs_E_2hit", 250, 80, 300, 100, -0.1, 0.1, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle2_vs_y_2hit", 300,-150, 150, 100, -0.1, 0.1, "track y [mm]", "angle [rad]");


  
  for(int i=0; i<9*6; i++)  {
    plot2DTr("mu_xy_track_"+std::to_string(i), 600,-150,150, 400,-100,100, "track x [mm]", "track y [mm]");
    plot1DTr("mu_angle_track_"+std::to_string(i), 100,-0.5, 0.5, "angle [rad]");
    plot1DTr("mu_x_track_"+std::to_string(i), 300,-150, 150, "track x [mm]");
    plot1DTr("mu_y_track_"+std::to_string(i), 200,-100, 100, "track y [mm]");
    plot1DTr("mu_p_track_"+std::to_string(i), 200, 0, 4000, "track momentum [MeV]");
    plot1DTr("mu_E_"+std::to_string(i), 250, 0, 500, "calo energy [MeV]");
    plot1DTr("mu_dR_"+std::to_string(i), 100, 0, 100, "#Delta R [mm]");

    plot2DTr("mu_split_xy_track_"+std::to_string(i), 600,-150,150, 400,-100,100, "track x [mm]", "track y [mm]");
    plot1DTr("mu_split_angle_track_"+std::to_string(i), 100,-0.5, 0.5, "angle [rad]");
    plot1DTr("mu_split_x_track_"+std::to_string(i), 300,-150, 150, "track x [mm]");
    plot1DTr("mu_split_y_track_"+std::to_string(i), 200,-100, 100, "track y [mm]");
    plot1DTr("mu_split_p_track_"+std::to_string(i), 200, 0, 4000, "track momentum [MeV]");
    plot1DTr("mu_split_E_"+std::to_string(i), 250, 0, 500, "calo energy [MeV]");



  }



};



//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {


  

  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {

    //    if(ctt->hitVolume == true) continue;
    if(ctt->trackPValue < 0.05) continue;
    if(ctt->trackMomentum < 2300) continue;


    //========================== SNIP!
    const double dt = ctt->trackTimeDiff;
    if(dt<-10 || dt>6) continue;        
    //========================== SNIP!
  

    
    //========================== SNIP!
    const double logEop = log(ctt->clusterEoverP);
    //classify the tracks:
    bool lostMu=false;
    bool positron=false;
    if(logEop>-3.2 && logEop<-2.4) lostMu=true;
    else if( /*dX>-0.4 && dX<0.5 && */ logEop>-0.3 && logEop<0.2 ) positron=true;
    if( !(lostMu) ) continue;
    //========================== SNIP!




    const double caloX_raw = ctt->clusterX;
    const double caloY_raw = ctt->clusterY;
    const double caloX = 112.5 - 25*(caloX_raw);
    const double caloY = SetCaloY(ctt->clusterCaloNum, caloY_raw);
    // -75 + 25*(caloY_raw); //SetCaloY(ctt->clusterCaloNum, caloY_raw);

    double trX = ctt->caloVertexPosX;
    double trY = ctt->caloVertexPosY;
    //  Extrapolate(trX, trY, 35.6); //1/4 way through calo cell
    //    Extrapolate(trX, trY, 64.9); //cluster z posn
    // Extrapolate(trX, trY, 105.6); 
    //  Extrapolate(trX, trY, 120.6); 
    //      cout <<ctt->caloVertexPosZ<<endl;
    // Z is -70.6

    //========================== SNIP!
    const double dX = caloX - trX;
    const double dY = caloY - trY;
    const double dR = sqrt(dX*dX + dY*dY);

    const int caloNum = CaloNum(caloX_raw, caloY_raw);
    if(caloNum <-0.01) continue;
    
    Fill1DTr("mu_dR_"+std::to_string(caloNum), dR);
    if(dR>30) continue;
    //========================== SNIP!
    
    
    
    if(lostMu) {
      
      //const int caloNum = CaloNum(caloX_raw, caloY_raw);
      //if(caloNum <-0.01) continue;
      Fill1D("mu_cluster_hits", ctt->clusterHits);
      
      
      if(ctt->clusterHits==1) {
	  Fill2DTr("mu_xy_track_"+std::to_string(caloNum), trX, trY);
	  const double angle = ctt->trackMomentumTheta * cos(ctt->trackMomentumPhi) ;
	  const double angle2 = ctt->trackMomentumTheta * sin(ctt->trackMomentumPhi) ;
	  Fill1DTr("mu_angle_track_"+std::to_string(caloNum), angle);
	  Fill1DTr("mu_x_track_"+std::to_string(caloNum), trX);
	  Fill1DTr("mu_y_track_"+std::to_string(caloNum), trY);
	  Fill1DTr("mu_p_track_"+std::to_string(caloNum),  ctt->trackMomentum );
	  Fill1DTr("mu_E_"+std::to_string(caloNum), ctt->clusterE);

	  Fill1DTr("mu_time", ctt->clusterTime);
	  Fill2DTr("mu_angle_vs_E", ctt->clusterE, angle);

	  if(angle > 0.163 + trX*0.12/190) {
	    Fill2DTr("mu_angle_vs_E_pop1", ctt->clusterE, angle);
	    Fill2DTr("mu_angle_vs_x_pop1", trX, angle);

	    if(trX<25) Fill1DTr("mu_p_pop1_left", ctt->trackMomentum);
	    else Fill1DTr("mu_p_pop1_right", ctt->trackMomentum);

	  }
	  else {
	    Fill2DTr("mu_angle_vs_E_pop2", ctt->clusterE, angle);
	    Fill2DTr("mu_angle_vs_x_pop2", trX, angle);
	  }
	  
	  Fill2DTr("mu_angle_vs_x", trX, angle);
	  Fill2DTr("mu_angle2_vs_E", ctt->clusterE, angle2);
	  Fill2DTr("mu_angle2_vs_y", trY, angle2);

	  if(caloNum==18) {
	    if(trX<100) {
	      // cout<<"ok: "<<caloX_raw<<" "<< caloY_raw<<endl;
	      Fill1DTr("mu_18_left_E", ctt->clusterE);
	      Fill1DTr("mu_18_left_p", ctt->trackMomentum);
	      Fill1DTr("mu_18_left_pVal", ctt->trackPValue);
	      Fill1DTr("mu_18_left_y_decay", ctt->decayVertexPosY);
	    }
	    else {
	      // cout<<"Dip: "<<caloX_raw<<" "<< caloY_raw<<endl;
	      Fill1DTr("mu_18_right_E", ctt->clusterE);
	      Fill1DTr("mu_18_right_p", ctt->trackMomentum);
	      Fill1DTr("mu_18_right_pVal", ctt->trackPValue);
	      Fill1DTr("mu_18_right_y_decay", ctt->decayVertexPosY);
	    }
	  }
	  else if(caloNum==17) {
	    if(trX<-116) {
	      //  cout<<"ok: "<<caloX_raw<<" "<< caloY_raw<<endl;
	      Fill1DTr("mu_17_left_E", ctt->clusterE);
	      Fill1DTr("mu_17_left_p", ctt->trackMomentum);
	      Fill1DTr("mu_17_left_pVal", ctt->trackPValue);
	      Fill1DTr("mu_17_left_y_decay", ctt->decayVertexPosY);
	    }
	    else if(trX>-107) {
	      // cout<<"Dip: "<<caloX_raw<<" "<< caloY_raw<<endl;
	      Fill1DTr("mu_17_right_E", ctt->clusterE);
	      Fill1DTr("mu_17_right_p", ctt->trackMomentum);
	      Fill1DTr("mu_17_right_pVal", ctt->trackPValue);
	      Fill1DTr("mu_17_right_y_decay", ctt->decayVertexPosY);
	    }
	  
	    
	  }
	  
      }//single cluster 
      
      
      else  if(ctt->clusterHits==2) {
	Fill2DTr("mu_split_xy_track_"+std::to_string(caloNum), trX, trY);
	const double angle = ctt->trackMomentumTheta * cos(ctt->trackMomentumPhi) ;
	const double angle2 = ctt->trackMomentumTheta * sin(ctt->trackMomentumPhi) ;

	Fill1DTr("mu_split_angle_track_"+std::to_string(caloNum), angle);
	Fill1DTr("mu_split_x_track_"+std::to_string(caloNum), trX);
	Fill1DTr("mu_split_y_track_"+std::to_string(caloNum), trY);
	Fill1DTr("mu_split_p_track_"+std::to_string(caloNum),  ctt->trackMomentum );
	Fill1DTr("mu_split_E_"+std::to_string(caloNum), ctt->clusterE);
	Fill1DTr("mu_split_time", ctt->clusterTime);

	Fill2DTr("mu_angle_vs_E_2hit", ctt->clusterE, angle);
	Fill2DTr("mu_angle_vs_x_2hit", trX, angle);
	Fill2DTr("mu_angle2_vs_E_2hit", ctt->clusterE, angle2);
	Fill2DTr("mu_angle2_vs_y_2hit", trY, angle2);
	
      }

 
      

    }

  } //event loop


  
  return;
}





