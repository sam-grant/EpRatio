//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

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
  const int cycles = 50;
  //plot1D("cuts",64,-0.5,63.5,"Cut Index","Entries");
  for (int stn(13); stn < 20 ; stn = stn + 6) {
    //plot1D("St"+std::to_string(stn)+"_logEop",200,-3.5,1,"Log(E/p)","Entries");
    //plot1D("St"+std::to_string(stn)+"_dR",200,0,70,"dR [mm]","Entries");
    //plot1D("St"+std::to_string(stn)+"_dt",200,-15,15,"dt [ns]","Entries");
    //plot2D("St"+std::to_string(stn)+"_E_vs_p",200,0,4000,200,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]"); 
    //plot2D("St"+std::to_string(stn)+"_Ep_vs_t",cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    for(int xtal(0); xtal<54; xtal++) {
      plot2D("St"+std::to_string(stn)+"_Ep_vs_t_"+std::to_string(xtal),cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    }
  }
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

  // Get E/p means for normalisation
  string inputName = "../AnalyseTime/RootFiles/PlotsEpXtalFid.root";
  TFile *input = TFile::Open(inputName.c_str());
  
  while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {

      if(am->nhits[i] != 1) continue;       

      // Empty vector to contain the results bit by bit (refreshing each event)
      vector<int> failedCutsBits_;
      for(int i = 0; i < 64; i++){
	failedCutsBits_.push_back(0);
      }

      // 64 bit integer refering to the cut results
      long long Q = am->trkPositronVertexQualityStatus[i];
      // long long Q
      // Scan across the bits and find the non zero ones
      // Put these in a hist, and a vector
      for (int iCut = 63; iCut >= 0; iCut--) {
	//	std::cout<<((Q >> iCut) & 1);
	failedCutsBits_.at(iCut) = (Q >> iCut) & 1;
	if( (Q >> iCut) & 1 ) {
	  failedCuts_.at(iCut)++;
      	  Fill1D("cuts",iCut);
	}
      }

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
      //if(caloSt > 19) continue;
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
      if(t<4200) continue;
      double E = am->cluEne[i];
      double Ep = E/p;
      //Normalisation
      string h = "St"+std::to_string(caloSt)+"_Ep_vs_xtal";
      TH1D *scale = (TH1D*)input->Get(h.c_str());
      double scaleFactor = scale->GetBinContent(xtal+1);
      if(scaleFactor==0) continue;
      Ep = Ep / scaleFactor;
      
      //Fill1D("St"+std::to_string(caloSt)+"_dR",dR);
      //Fill1D("St"+std::to_string(caloSt)+"_dt",dt);
      //Fill1D("St"+std::to_string(caloSt)+"_logEop",logEop);
      //Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t",t,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t_"+std::to_string(xtal),t,Ep);
      //Fill2D("St"+std::to_string(caloSt)+"_E_vs_p",p,E);       

    }
  }
  
  return;
  
}
