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

  plot1DTr("qc_pval", 100,0,1, "Track p-value");
  plot1DTr("qc_dt", 100,-15,15, "Track-cluster #Delta t [ns]");
  plot1DTr("qc_dR", 100,0,50, "Track-cluster #Delta R [mm]");
  plot1DTr("qc_Eop", 100,-3.5,1, "log (cluster energy / track momentum)");
  plot2DTr("qc_Evsp", 100, 0,4000, 100,0,4000,  "Track momentum [MeV]", "Cluster energy [MeV]");
  plot1DTr("qc_p", 100,0,3500, "Track momentum [MeV]");
  plot1DTr("qc_Nxtal", 7,-0.5,6.5, "Number of crystals in cluster");

  plot2DTr("check_Evsp", 100, 0,4000, 100,0,4000,  "Track momentum [MeV]", "Cluster energy [MeV]");
  
  plot2DTr("mu_angle_vs_E", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_E_pop1", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_E_pop2", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_x", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_pop1", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_pop2", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");

  plot1DTr("mu_p_pop1_left", 200,0,4000, "track momentum [MeV]");
  plot1DTr("mu_p_pop1_right", 200,0,4000, "track momentum [MeV]");
  plot1DTr("mu_t_pop1_left", 100, 0, 100000, "cluster time [ns]");
  plot1DTr("mu_t_pop1_right", 100, 0, 100000, "cluster time [ns]");

  plot1DTr("mu_p_pop2", 200,0,4000, "track momentum [MeV]");
  plot1DTr("mu_t_pop2", 100, 0, 100000, "cluster time [ns]");

  
  
  plot2DTr("mu_angle2_vs_E", 250, 80, 300, 100, -0.1, 0.1, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle2_vs_y", 300,-150, 150, 100, -0.1, 0.1, "track y [mm]", "angle [rad]");

  plot2DTr("mu_angle_vs_E_2hit", 250, 80, 300, 100, 0.05, 0.25, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle_vs_x_2hit", 300,-150, 150, 100, 0.05, 0.25, "track x [mm]", "angle [rad]");

  plot2DTr("mu_angle2_vs_E_2hit", 250, 80, 300, 100, -0.1, 0.1, "calo energy [MeV]", "angle [rad]");
  plot2DTr("mu_angle2_vs_y_2hit", 300,-150, 150, 100, -0.1, 0.1, "track y [mm]", "angle [rad]");
  
  plot1DTr("mu_x", 300,-150, 150, "x [mm]");
  plot1DTr("mu_y", 300,-150, 150, "y [mm]");
  plot2DTr("mu_xy", 300,-150, 150, 300,-150, 150, "x [mm]", "y [mm]");
  plot2DTr("mu_xy_extrap", 300,-150, 150, 300,-150, 150, "x [mm]", "y [mm]");
  plot2DTr("mu_E_vs_x", 300,-150, 150, 250, 80, 300, "x [mm]", "E [MeV]");
  plot2DTr("mu_E_vs_x_extrap", 300,-150, 150, 250, 80, 300, "x [mm]", "E [MeV]");
  plot2DTr("mu_E_vs_y", 300,-150, 150, 250, 80, 300, "y [mm]", "E [MeV]");
  plot2DTr("mu_E_vs_y_extrap", 300,-150, 150, 250, 80, 300, "y [mm]", "E [MeV]");

  plot2DTr("mu_E_vs_z_extrap", 300, -75, 75, 250, 80, 300, "Exit z [mm]", "E [MeV]");

  plot2DTr("tr_Eop_vs_z_extrap", 300, -75, 75, 150, 0, 1.5, "Exit z [mm]", "E/p ");
  plot2DTr("tr_Eop_vs_z_extrap_posx", 300, -75, 75, 150, 0, 1.5, "Exit z [mm]", "E/p ");
  plot2DTr("tr_Eop_vs_z_extrap_negx", 300, -75, 75, 150, 0, 1.5, "Exit z [mm]", "E/p ");
  plot2DTr("tr_x_vs_z_extrap", 300, -75, 75, 300,-150,150, "Exit z [mm]", "x [mm] ");

  
  plot1DTr("mu_E_fid", 250, 50, 300,  "E [MeV]");
  plot1DTr("mu_E_nfid", 250, 50, 300, "E [MeV]");
  plot1DTr("mu_E_2hit", 250, 50, 300, "E [MeV]");

  plot2DTr("mu_xy_fid", 300,-150, 150, 300,-150, 150, "x [mm]", "y [mm]");
  plot2DTr("mu_xy_nfid", 300,-150, 150, 300,-150, 150, "x [mm]", "y [mm]");


  plot2DTr("mu_angle2_vs_angle1_fid", 100, 0.05, 0.25, 100,-0.1,0.1, "angle [rad]", "angle [rad]");
  plot2DTr("mu_angle2_vs_angle1_nfid", 100, 0.05, 0.25, 100,-0.1,0.1, "angle [rad]", "angle [rad]");

  plot2DTr("mu_E_vs_angle_fid", 100, 0.14, 0.23, 250, 80, 300, "angle [rad]", "calo energy [MeV]");
  plot2DTr("mu_E_vs_angle_nfid", 100, 0.14, 0.23, 250, 80, 300, "angle [rad]", "calo energy [MeV]");
  plot2DTr("mu_E_vs_R_fid", 150,0,150, 250, 80, 300, "R [mm]", "calo energy [MeV]");
  plot2DTr("mu_E_vs_R_nfid", 150,0,150, 250, 80, 300, "R [mm]", "calo energy [MeV]");



};



//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {


  

  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {

    
    //    if(ctt->hitVolume == true) continue;
    Fill1DTr("qc_pval", ctt->trackPValue );

    if(ctt->trackPValue < 0.05) continue;
   


    //========================== SNIP!
    const double dt = ctt->trackTimeDiff;
    Fill1DTr("qc_dt", dt );
    //    if(dt<-10 || dt>6) continue;        

    if(ctt->clusterCaloNum==13){
      if (dt<-8 || dt>3 ) continue;
    }
    else {
      if(dt<-9 || dt>1) continue;        
    }
    //========================== SNIP!
  
    //========================== SNIP!
    const double caloX_raw = ctt->clusterX;
    const double caloY_raw = ctt->clusterY;
    const double caloX = 112.5 - 25*(caloX_raw);
    const double caloY = SetCaloY(ctt->clusterCaloNum, caloY_raw);
    const double trX = ctt->caloVertexPosX;
    const double trY = ctt->caloVertexPosY;

    const double dX = caloX - trX;
    const double dY = caloY - trY;
    const double dR = sqrt(dX*dX + dY*dY);

    const int caloNum = CaloNum(caloX_raw, caloY_raw);
    if(caloNum <-0.01) continue;
    
    Fill1DTr("qc_dR", dR );
    if(dR>30) continue;
    //========================== SNIP!

    

    const double logEop = log(ctt->clusterEoverP);
    //classify the tracks:
    bool lostMu=false;
    bool positron=false;
    if( logEop>-3.2 && logEop<-2.4) lostMu=true;
    else if( /*dX>-0.4 && dX<0.5 && */ logEop>-0.3 && logEop<0.2 ) positron=true;

    if( lostMu ) {
      Fill1DTr("qc_p", ctt->trackMomentum );
      if(ctt->clusterCaloNum==13 &&  ctt->trackMomentum< 2200) lostMu=false;
      if(ctt->clusterCaloNum==19 &&  ctt->trackMomentum< 2350) lostMu=false;
    }


    
    const double z_exit = ExtrapolateToExit(trX, trY); //extrapolate to end of calorimeter
    Fill2DTr("tr_Eop_vs_z_extrap", z_exit, ctt->clusterEoverP );
    if(trX>80) Fill2DTr("tr_Eop_vs_z_extrap_posx", z_exit, ctt->clusterEoverP );
    else if(trX<-80) Fill2DTr("tr_Eop_vs_z_extrap_negx", z_exit, ctt->clusterEoverP );
    Fill2DTr("tr_x_vs_z_extrap", z_exit, trX );

    //========================== SNIP!
    Fill1DTr("qc_Eop", logEop );
    Fill2DTr("qc_Evsp", ctt->trackMomentum, ctt->clusterE );
    
    if( !(lostMu) ) continue;
    //========================== SNIP!

   // -75 + 25*(caloY_raw); //SetCaloY(ctt->clusterCaloNum, caloY_raw);

    double trX_ex = trX;
    double trY_ex = trY;    
    Extrapolate(trX_ex, trY_ex, 140); //extrapolate to end of calorimeter


    Fill1DTr("qc_Nxtal",  ctt->clusterHits );
    if( ctt->clusterHits > 2) continue;
  
      
    const double angle = ctt->trackMomentumTheta * cos(ctt->trackMomentumPhi) ;
    const double angle2 = ctt->trackMomentumTheta * sin(ctt->trackMomentumPhi) ;
    Fill1DTr("mu_x", trX);
    Fill1DTr("mu_y", trY);
    
    if(trX<-106) Fill2DTr("check_Evsp", ctt->trackMomentum, ctt->clusterE );
    
    
    Fill2DTr("mu_xy", trX, trY);
    Fill2DTr("mu_xy_extrap", trX_ex, trY_ex);
    
    Fill2DTr("mu_E_vs_x", trX, ctt->clusterE );
    Fill2DTr("mu_E_vs_x_extrap", trX_ex, ctt->clusterE );
    
    Fill2DTr("mu_E_vs_y", trY, ctt->clusterE );
    Fill2DTr("mu_E_vs_y_extrap", trY_ex, ctt->clusterE );
      Fill2DTr("mu_E_vs_z_extrap", z_exit, ctt->clusterE );

      const double R = sqrt(trX*trX + trY*trY);

      if( ctt->clusterHits==1) {
	if(Fiducial(trX, trY) ) {
	  Fill1DTr("mu_E_fid", ctt->clusterE );
	  Fill2DTr("mu_E_vs_angle_fid", ctt->trackMomentumTheta, ctt->clusterE);
	  Fill2DTr("mu_E_vs_R_fid", R, ctt->clusterE);
	  Fill2DTr("mu_angle2_vs_angle1_fid", angle, angle2);
	  Fill2DTr("mu_xy_fid", trX, trY );
	}
	else {
	  Fill1DTr("mu_E_nfid", ctt->clusterE );
	  Fill2DTr("mu_E_vs_angle_nfid", ctt->trackMomentumTheta, ctt->clusterE);
	  Fill2DTr("mu_E_vs_R_nfid", R, ctt->clusterE);
	  Fill2DTr("mu_angle2_vs_angle1_nfid", angle, angle2);
	  Fill2DTr("mu_xy_nfid", trX, trY );
	}
      }
      
      Fill2DTr("mu_angle_vs_E", ctt->clusterE, angle);
      Fill2DTr("mu_angle_vs_x", trX, angle);
      
      Fill2DTr("mu_angle2_vs_E", ctt->clusterE, angle2);
      Fill2DTr("mu_angle2_vs_y", trY, angle2);
      
      if(angle > 0.163 + trX*0.12/190) {
	Fill2DTr("mu_angle_vs_E_pop1", ctt->clusterE, angle);
	Fill2DTr("mu_angle_vs_x_pop1", trX, angle);
	
	if(trX<25) {
	  Fill1DTr("mu_p_pop1_left", ctt->trackMomentum);
	  Fill1DTr("mu_t_pop1_left", ctt->clusterTime);
	}
	else {
	  Fill1DTr("mu_p_pop1_right", ctt->trackMomentum);
	  Fill1DTr("mu_t_pop1_right", ctt->clusterTime);
	}
      }
      else {
	Fill2DTr("mu_angle_vs_E_pop2", ctt->clusterE, angle);
	Fill2DTr("mu_angle_vs_x_pop2", trX, angle);
	Fill1DTr("mu_p_pop2", ctt->trackMomentum);
	Fill1DTr("mu_t_pop2", ctt->clusterTime);
	
      }
      


      
    
    if(ctt->clusterHits==2) {
      
      const double angle = ctt->trackMomentumTheta * cos(ctt->trackMomentumPhi) ;
      const double angle2 = ctt->trackMomentumTheta * sin(ctt->trackMomentumPhi) ;
      
      Fill2DTr("mu_angle_vs_E_2hit", ctt->clusterE, angle);
      Fill2DTr("mu_angle_vs_x_2hit", trX, angle);
      
      Fill2DTr("mu_angle2_vs_E_2hit", ctt->clusterE, angle2);
      Fill2DTr("mu_angle2_vs_y_2hit", trY, angle2);
      Fill1DTr("mu_E_2hit", ctt->clusterE );
      
    }
    
    
    
    
    
    
  } //event loop
  
  
  
  return;
}





