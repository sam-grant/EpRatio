//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

// This is for the 9 day, where we have to remove the corrections

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1.h"

using namespace std;

int CaloNum(int caloX, int caloY) {
  return caloX+9*caloY;
}

// IFG function
double ifg(double time, double G0, double amp, double tau) {
  // We get time in ns and tau in us 
  tau = tau * 1000;
  double G = G0*(1-amp*exp(-time/tau));
  return 1;//G;
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
    // plot2D("St"+std::to_string(stn)+"_Ep_vs_t",cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
    // plot2D("St"+std::to_string(stn)+"_x_vs_y",200,-150,150,200,-120,120,"Forwards Extrapolated Track Position X [mm]","Forwards Extrapolated Track Position X [mm]");
    for(int brd(0); brd<2; brd++) {
      plot2D("St"+std::to_string(stn)+"_Ep_vs_t_"+std::to_string(brd),cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "E/p");
      //      plot2D("St"+std::to_string(stn)+"_G_vs_t_"+std::to_string(brd),cycles,0,4200*cycles,1000,0.5,1.5,"In Fill Time [ns]", "G(t)");
    }
      
  }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {
  
  // // Quality cut variable 
  // bool qualityFail;
  // // Set a cut to be skipped
  // int skipCut = 18; 

  // // Initialise an empty vector to store the results from 64 bit Q
  // vector<int> failedCuts_;
  // for(int i = 0; i < 64; i++){
  //   failedCuts_.push_back(0);
  // }

  // Get E/p means for normalisation and G0 varible
  //  string inputName = "../AnalyseTime/RootFiles/PlotsEpXtalFid.root";
  string inputName1 = "../AnalyseTime/RootFiles/PlotsEpXtal_9day.root";
  TFile *input1 = TFile::Open(inputName1.c_str());
  // Get ifg params
  string inputName2 = "../ReadNTuples/RootFiles/ifg_9day.root";
  TFile *input2 = TFile::Open(inputName2.c_str());
  

  std::cout<<"t * G * amp * tau"<<std::endl;

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
          
      // Scale factor
      string h1 = "St"+std::to_string(caloSt)+"_Ep_vs_xtal";
      TH1D *scale = (TH1D*)input1->Get(h1.c_str());
      double scaleFactor = scale->GetBinContent(xtal+1);
      if(scaleFactor==0) continue;
      // Amplitude
      string h2 = "amp_"+std::to_string(caloSt);
      TH1D *amplitude = (TH1D*)input2->Get(h2.c_str());
      double amp = amplitude->GetBinContent(xtal+1);
      //      if(amp==0) continue;
      // Tau
      string h3 = "tau_"+std::to_string(caloSt);
      TH1D *recTime = (TH1D*)input2->Get(h3.c_str());
      double tau = recTime->GetBinContent(xtal+1);
      // if(tau==0) continue;

      // Undo correction
      // Assume normalisation is one
      double G = ifg(t,1.0,amp,tau);

      std::cout<<t<<" * "<<G<<" * "<<amp<<" * "<<tau<<std::endl;
      double E = am->cluEne[i] / G;
      double Ep = E/p;

      Ep = Ep;// / scaleFactor;

      //      if(xtal==4||xtal==35||xtal==27||xtal==49) std::cout<<"Oh no "<<xtal<<std::endl;
      // Seperate boards
      int shortLifeXtal[22] = {0,9,10,11,14,15,18,19,20,23,24,27,30,31,34,35,36,39,40,43,44,45};
      int brd;
      for (int j = 0 ; j < 22 ; j++ ) {
        if (xtal == shortLifeXtal[j]) {
          brd = 0;
          break;
        }
        else {
          brd = 1;
        }
      }
      //      std::cout<<xtal<<endl;
      // Fill1D("St"+std::to_string(caloSt)+"_dR",dR);
      // Fill1D("St"+std::to_string(caloSt)+"_dt",dt);
      // Fill1D("St"+std::to_string(caloSt)+"_logEop",logEop);
      // Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t",t,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t_"+std::to_string(brd),t,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_G_vs_t_"+std::to_string(brd),t,G);
      // Fill2D("St"+std::to_string(caloSt)+"_E_vs_p",p,E);      
      // Fill2D("St"+std::to_string(caloSt)+"_x_vs_y",caloX,caloY);      
    }
  }
  
  return;
  
}
