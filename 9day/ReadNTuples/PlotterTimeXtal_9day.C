//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

double IFG(double time, double amp, double tau) {
  tau = tau * 1000;
  return ( 1 - amp * exp( -time / tau ) );
}

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
  //  plot1D("cuts",64,-0.5,63.5,"Cut Index","Entries");
  for (int stn(13); stn < 20 ; stn = stn + 6) {
    // plot1D("St"+std::to_string(stn)+"_logEop",200,-3.5,1,"Log(E/p)","Entries");
    // plot1D("St"+std::to_string(stn)+"_dR",200,0,70,"dR [mm]","Entries");
    // plot1D("St"+std::to_string(stn)+"_dt",200,-15,15,"dt [ns]","Entries");
    // plot2D("St"+std::to_string(stn)+"_E_vs_p",200,0,4000,200,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]"); 
    //plot2D("St"+std::to_string(stn)+"_Ep_vs_t",cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    for(int xtal(0); xtal<54; xtal++) {
      plot2D("St"+std::to_string(stn)+"_Ep_vs_t_"+std::to_string(xtal),cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    }
  }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {
  
  // Get E/p means for normalisation
  TFile *normInput = TFile::Open("../ROOT/PlotsEpXtalFid_9day.root");
  TFile *ifgInput = TFile::Open("../ROOT/LaserParametersProduction_9day.root");

  while( NextallmuonsEvent() ) {

    //loop over the matches in this event:
    for(int i=0; i<am->nmatches; i++) {

      if(am->nhits[i] != 1) continue;       

      if(am->trkPassPositronVertexQuality[i] == false) continue;

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
      
      // Function
      TH1D *Amp = (TH1D*)ifgInput->Get(("amp_"+std::to_string(caloSt)).c_str());
      TH1D *Tau = (TH1D*)ifgInput->Get(("tau_"+std::to_string(caloSt)).c_str());
      double amp = Amp->GetBinContent(xtal+1);
      double tau = Tau->GetBinContent(xtal+1);

      // Normalisation
      TH1D *scale = (TH1D*)normInput->Get(("St"+std::to_string(caloSt)+"_Ep_vs_xtal").c_str());
      double G0 = scale->GetBinContent(xtal+1);
      if(G0==0) continue;

      double G = IFG(t,amp,tau);

      double Ep = E/p;

      Ep = Ep * G / G0; // G includes normalisation

      // Fill1D("St"+std::to_string(caloSt)+"_dR",dR);
      // Fill1D("St"+std::to_string(caloSt)+"_dt",dt);
      // Fill1D("St"+std::to_string(caloSt)+"_logEop",logEop);
      //      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t",t,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t_"+std::to_string(xtal),t,Ep);
      // Fill2D("St"+std::to_string(caloSt)+"_E_vs_p",p,E);       

    }
  }
  
  return;
  
}
