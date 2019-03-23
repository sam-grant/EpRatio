//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// samuel.grant.18@ucl.ac.uk

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
  plot2D("xy_calo_raw",500,-1,7,500,-1,7,"Calo Position X [mm]","Calo Position Y [mm]");

  for (int i = 0 ;  i < 4 ; i++) {

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

      if(am -> decayHitVolume[i] == true) continue;
      if( am->trkPvalue[i] < 0.05) continue;
      
      const double dt = am->Tdiff[i];

      double E = am->cluEne[i];

      double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
     
      const double logEop = log(am->EovP[i]);

      double t = am -> decayTime[i];

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

      //  Fill2D("xy_calo_raw",caloX_raw,caloY_raw);

      if(xtalNum <-0.01) continue;
      
      const double caloX = 112.5 - 25*(caloX_raw);
      const double caloY = SetCaloY(caloSt, caloY_raw);
      // -75 + 25*(caloY_raw); //SetCaloY(ctt->clusterCaloNum, caloY_raw);
     
      double trX = am->vX[i];
      double trY = am->vY[i];
      if (trX == 0 && trY == 0) continue;

      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);
      
      if(dR > 30) continue;

      double Ep = E/p;

     //========================== SNIP!

      // Fiducial cut 
      int k;
      if (Fiducial(caloX, caloY) == true) {k=0;}
      else if (Fiducial(caloX, caloY) == false) {k=1;}
      bool region[4] = {false};

      if(logEop>-0.3 && logEop<0.2 ) region[0]=true;
      if(0.92 < Ep && Ep < 1.0) region[1]=true;
      if (1000 < E && E < 2500) region[2]=true;
      if(region[1]==true && region[2]==true) region[3]=true;

      for (int i = 0 ; i < 4 ; i++ ) {
   
	if(region[i]) {
	  
	  Fill2D("E_vs_p_"+std::to_string(i),p,E);
	  Fill2D("Ep_vs_E_"+std::to_string(i),E,Ep);
	  Fill2D("Ep_vs_p_"+std::to_string(i),p,Ep);
	  Fill2D("Ep_vs_t_"+std::to_string(i),t,Ep);
	  Fill2D("Ep_vs_t_early_"+std::to_string(i),t,Ep);
	  Fill2D("Ep_vs_p_"+std::to_string(i),p,Ep);
	  Fill2D("xy_calo_"+std::to_string(i),caloX,caloY);

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

  /*


  
  

  //loop over the clusterTracker/tracker tree:
  while( NextClTrTrEvent() ) {

    //    if(ctt->hitVolume == true) continue;
    if(ctt->trackPValue < 0.05) continue;

    const double logEop = log(ctt->clusterEoverP);
    const double dt = ctt->trackTimeDiff;
    Fill1DTr("Eop", logEop);
    Fill2DTr("E_vs_p", ctt->trackMomentum, ctt->clusterE);
    Fill1DTr("dt", dt );
    
    //calo range from 0->8 in x (needs flipping), 0->5 in y
    //tracker range from -120 -> 100 in x, -50 to 50 in y
    // x scaling ~9/220=0.041; y scaling ~ 6/100 = 0.06

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

    //the raw distributions:
    Fill2DTr("xy_calo_raw", caloX_raw, caloY_raw);
    Fill2DTr("xy_calo", caloX, caloY);
    Fill2DTr("xy_track", trX, trY);
    Fill2DTr("x", caloX, trX );    
    Fill2DTr("y", caloY, trY );

    const double dX = caloX - trX;
    const double dY = caloY - trY;
    const double dR = sqrt(dX*dX + dY*dY);
    Fill1DTr("dR", dR );

    //========================== SNIP!
    
    if(ctt->trackTimeDiff<-10 || ctt->trackTimeDiff>6) continue;
    if(dR>30) continue;
        
    //========================== SNIP!

    Fill2DTr("Eop_vs_dX", dX, logEop);
    Fill2DTr("Eop_vs_dY", dY, logEop);
    Fill2DTr("xy_calo_cut", caloX, caloY);
    Fill2DTr("xy_track_cut", trX, trY);
  
    //classify the tracks:
    bool lostMu=false;
    bool positron=false;
    bool neg = false;
    bool pos = false;
    if(logEop>-3.2 && logEop<-2.4) lostMu=true;
    else if( /*dX>-0.4 && dX<0.5 && *//* logEop>-0.3 && logEop<0.2 ) positron=true;

    //========================== SNIP!
    if( !(lostMu||positron) ) continue;
    //========================== SNIP!

   
    if(lostMu) {

      Fill2DTr("mu_xy_calo", caloX, caloY);
      Fill2DTr("mu_xy_track", trX, trY);

      if(ctt->clusterHits==1) {
	const int caloNum = CaloNum(caloX_raw, caloY_raw);
	if(caloNum > -1) {
	  Fill2DTr("mu_xy_track_"+std::to_string(caloNum), trX, trY);
	  const double angle = ctt->trackMomentumTheta * cos(ctt->trackMomentumPhi) ;
	  Fill1DTr("mu_angle_track_"+std::to_string(caloNum), angle);
	  Fill1DTr("mu_x_track_"+std::to_string(caloNum), trX);
	  Fill1DTr("mu_y_track_"+std::to_string(caloNum), trY);
	  Fill1DTr("mu_p_track_"+std::to_string(caloNum),  ctt->trackMomentum );
	  Fill1DTr("mu_E_"+std::to_string(caloNum), ctt->clusterE);

	  Fill1DTr("mu_time", ctt->clusterTime);

	}

      }


      
      Fill1DTr("mu_dX_"+std::to_string((int)caloX_raw)+"_"+std::to_string((int)caloY_raw), dX);
      Fill1DTr("mu_dY_"+std::to_string((int)caloX_raw)+"_"+std::to_string((int)caloY_raw), dY);
      
    }
    else {  
      Fill2DTr("pos_xy_calo", caloX, caloY);
      Fill2DTr("pos_xy_track", trX, trY);
      Fill1DTr("pos_dx", dX);
      Fill1DTr("pos_dy", dY);
      Fill2DTr("pos_p_x", trX, ctt->trackMomentum);
      //      cout<<"clusterX: "<<caloX_raw<<", converted to mm: "<<caloX<<endl;
      //      cout<<"clusterY: "<<caloY_raw<<", converted to mm: "<<caloY<<endl;

      Fill1DTr("pos_dX_"+std::to_string((int)caloX_raw)+"_"+std::to_string((int)caloY_raw), dX);
      Fill1DTr("pos_dY_"+std::to_string((int)caloX_raw)+"_"+std::to_string((int)caloY_raw), dY);

      


    }

  }
  return;
}

*/



