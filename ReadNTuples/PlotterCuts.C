// Make plots of cut parameters with no cuts applied
// Sam Grant - August 2019

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

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
  /* const int cycles = 50; */
  /* plot1D("cuts",64,-0.5,63.5,"Cut Index","Entries"); */
  /* plot2D("E_vs_p_0",1000,0,4000,1000,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]"); */
  /* plot2D("E_vs_p_1",1000,0,4000,1000,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]"); */
  plot2D("E_vs_p_2",1000,0,4000,1000,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]");
  /* for (int stn(13); stn < 20 ; stn = stn + 6) { */
  /*   plot1D("St"+std::to_string(stn)+"_logEop",200,-3.5,1,"Log(E/p)","Entries"); */
  /*   plot1D("St"+std::to_string(stn)+"_dR",200,0,50,"dR [mm]","Entries"); */
  /*   plot1D("St"+std::to_string(stn)+"_dt",200,-15,15,"dt [ns]","Entries"); */
  /* } */
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  // Quality cut variable
  bool qualityFail;
  // Set a cut to be skipped
  int skipCut = 18;

  // Initialise an empty vector to store the results from 64 bit Q
  vector<int> failedCuts_;
  for(int i = 0; i < 64; i++){
    failedCuts_.push_back(0);
  }
  
  while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {
      if(am->nhits[i] != 1) continue;
      
     // Empty vector to contain the results bit by bit (refreshing each event)
      vector<int> failedCutsBits_;
      for(int i = 0; i < 64; i++){
        failedCutsBits_.push_back(0);
      }
      // Scan across the cut bits and find the non zero ones
      // Put these in a hist, and a vector
      // 64 bit integer refering to the cut results
      long long Q1 = am->trkPositronVertexQualityStatus[i];
      long long Q2 = am->trkLostMuonVertexQualityStatus[i];
      
      for (int iCut = 63; iCut >= 0; iCut--) {
	failedCutsBits_.at(iCut) = (Q1 >> iCut) & 1;
        if( (Q1 >> iCut) & 1 ) {
	  failedCuts_.at(iCut)++;
	  if(iCut==18) continue;
	  if(iCut==19) iCut = iCut - 1;
	  //          Fill1D("cuts",iCut);
        }
      }

      /* for (int iCut = 63; iCut >= 0; iCut--) { */
      /*   if( (Q2 >> iCut) & 1 ) { */
      /* 	  if(iCut!=20) continue; */
      /* 	  if(iCut==20) iCut = iCut - 1; */
      /*     Fill1D("cuts",iCut); */
      /*   } */
      /* } */


      // Define the qualityFail bool (if skipping cuts)
      for (int iCut = 0; iCut < 63; iCut++) {
        if(iCut == skipCut) continue;
        if(failedCutsBits_.at(iCut) == 0) {
          qualityFail = false;
        }
        else {
          qualityFail = true;
          break;
        }
      }

      // If using all cuts, just set (Q == true) continue;
      //      std::cout<<" qualityFail: "<<qualityFail<<std::endl;
      if(qualityFail == true) continue;

      
      double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
      
      double logEop = log(am->EovP[i]);
      double dt = am->Tdiff[i];
      int caloSt = am->cluCaloNum[i];
      int trkSt = am->trkStationNum[i];
      double caloX_raw = am->cluX[i];
      double caloY_raw = am->cluY[i];
      int xtal = CaloNum(caloX_raw, caloY_raw);
      double caloX = 112.5 - 25*(caloX_raw);
      double caloY = SetCaloY(caloSt, caloY_raw);
      double trX = am->vX[i];
      double trY = am->vY[i];
      double dX = caloX - trX;
      double dY = caloY - trY;
      double dR = sqrt(dX*dX + dY*dY);
      double t = (am -> cluTime[i]);
      //      if(t<4200) continue;
      double E = am->cluEne[i];
      double Ep = E/p;

      //      if(Q1==0) {

	/* Fill1D("St"+std::to_string(caloSt)+"_dR",dR); */
	/* Fill1D("St"+std::to_string(caloSt)+"_dt",dt); */
	/* Fill1D("St"+std::to_string(caloSt)+"_logEop",logEop); */
	/* Fill2D("E_vs_p_0",p,E); */
	//	if(
      if(-3.2 < logEop && logEop < -2.4 && p > 2300) {
	Fill2D("E_vs_p_2",p,E);
      }
      /* else if(Q2==0) { */
      /* 	Fill2D("E_vs_p_1",p,E); */
      /* } */
    } 
  }
  
  return;
  
}
