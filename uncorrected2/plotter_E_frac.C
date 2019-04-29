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
    for (int fid = 0; fid < 3; fid++) {
      // for (int frac = 1 ; frac < 3 ; frac++) {
      plot1D("St"+std::to_string(stn)+"_efrac_"+std::to_string(fid),101,-0.005,1.005,"Cluster fractional energy","N");
      plot2D("St"+std::to_string(stn)+"_efrac_vs_p_"+std::to_string(fid),20,0,4000,101,-0.005,1.005,"Track Momentum [MeV]","Cluster fractional energy");
      // }
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

      const double efrac = am->efracmaxclu[i];
      
      const double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
      const double E = am->cluEne[i];
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
      const double trX = am->vX[i];
      const double trY = am->vY[i];

      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);
      
      if(dR>30) continue;


      

      //========================== SNIP!
  
      bool region[3] = {false};
      // Positrons 
      if(logEop>-0.3 && logEop<0.2) region[0]=true;
      // High Flux - Energy - All Tracsk
      if (1200 < E && E < 2400) region[1]=true;
      // High Flux - Energy - Positrons
      if(region[0]==true && region[1]==true) region[2]=true;   
      // Select high flux positrons
      if(!region[2]) continue;

      // if (xtal != 21 ) continue;
      ////////////////////////////////////////////
      /* 0 means no fiducial cut 
	 1 means xtal fiducial cut 
	 2 means calo fiducial cut */
      
      Fill1D("St"+std::to_string(caloSt)+"_efrac_0",efrac);
      Fill2D("St"+std::to_string(caloSt)+"_efrac_vs_p_0",p,efrac);
       
      if (FiducialXtal(trX, trY)) { //
	Fill1D("St"+std::to_string(caloSt)+"_efrac_1",efrac);
	Fill2D("St"+std::to_string(caloSt)+"_efrac_vs_p_1",p,efrac);
      }
      if(FiducialMain(trX, trY)) {
	  Fill1D("St"+std::to_string(caloSt)+"_efrac_2",efrac);
	  Fill2D("St"+std::to_string(caloSt)+"_efrac_vs_p_2",p,efrac);
	}
			       

     
	}
    
    }
    
    delete am;
    return;
  
  }
  
