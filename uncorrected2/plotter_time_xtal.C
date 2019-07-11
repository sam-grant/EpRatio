//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// modified by: samuel.grant.18@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

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
      for(int xtal = 0; xtal < 54; xtal++) {
       	plot2D("St"+std::to_string(stn)+"_Ep_vs_t_early_"+std::to_string(xtal),50,0,4200*50,1000,0,4,"In Fill Time [ns]", "E/p");
	//plot1D("St"+std::to_string(stn)+"_p_"+std::to_string(xtal),6,1200,2400,"Track Momentum [MeV]","Entries");
	//plot1D("St"+std::to_string(stn)+"_E_"+std::to_string(xtal),6,1200,2400,"Cluster Energy [MeV]","Entries");

    }
  }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  // TFile *input1 = TFile::Open("../makePlots2/time_xtal.root");  
     
  //loop over the clusterTracker/tracker tree:

 while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {
      // Require quality cut pass
      //      if(am->trkPassTrackQuality[i] == false) continue;
      
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
      const double caloX = 112.5 - 25*(caloX_raw);
      const double caloY = SetCaloY(caloSt, caloY_raw);
      const double caloY_test = -(75.0 - 25*(caloY_raw));

      //  cout << caloY << " " << caloY_test << endl;
      // Forward extrapolated track position
      double trX = am->vX[i];
      double trY = am->vY[i];
  
      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);

      //      cout<<caloX<<" "<<trX<<" "<<caloY<<" "<<trY<<" "<<dR<<endl;
      
      if(dR>30) continue;

      double t = (am -> cluTime[i]);
      if (t < 4200) continue;

      double E = am->cluEne[i];
      double Ep = E/p;

      //========================== SNIP!
  
      bool region[3] = {false};
      // Positrons 
      if(logEop>-0.3 && logEop<0.2 ) region[0]=true;
      // High Flux - Energy - All Tracsk
      if(!region[0]) continue;

      ////////////////////////////////////////////
      //Energy Fraction Cut

      // const double efrac = am->efracmaxclu[i];
       //////////
      // Require 1 hit
      const double hits = am->nhits[i];
      if(hits != 1) continue;
      
      /////////////////////////
      //Normalisation
       Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t_early_"+std::to_string(xtal),t,Ep);
      //      Fill1D("St"+std::to_string(caloSt)+"_E_"+std::to_string(xtal),E);
      //Fill1D("St"+std::to_string(caloSt)+"_p_"+std::to_string(xtal),p);
      
    }
    
 }
  
 // input1 -> Close();
  
 return;
  
}
