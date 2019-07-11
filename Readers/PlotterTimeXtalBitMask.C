//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk
// modified by: samuel.grant.18@ucl.ac.uk

//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"
#include "TFile.h"
//#include <bitset>
#include "TH1.h"
/* int setCutBit(int nCut, long long &qualityStatus, bool failCut){ */
/*   if(failCut){ // |= is a bitwise "Or", ULL is an unsigned long long */
/*     // << shifts left and adds zeros at the right end. */
/*     qualityStatus |= (1ULL << nCut); */
/*   } else { // &= is a bitwise "and"  */
/*     qualityStatus &= ~(1ULL << nCut); */
/*   } */
/*   return; */
/* } */

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
      plot1D("cuts",64,0,63,"Cut Index","Entries");
  for (int stn = 13; stn < 20 ; stn = stn + 6) {
    for(int xtal = 0; xtal < 1; xtal++) {

      plot1D("St"+std::to_string(stn)+"_logEop_"+std::to_string(xtal),200,-3.5,1,"Log(E/p)","Entries");
      plot1D("St"+std::to_string(stn)+"_dR_"+std::to_string(xtal),200,0,70,"dR [mm]","Entries");
      plot1D("St"+std::to_string(stn)+"_dt_"+std::to_string(xtal),200,-15,15,"dt [ns]","Entries");
      plot2D("St"+std::to_string(stn)+"_Ep_vs_t_"+std::to_string(xtal),50,0,4200*50,1000,0,4,"In Fill Time [ns]", "E/p");
      plot2D("St"+std::to_string(stn)+"_E_vs_p_"+std::to_string(xtal),200,0,4000,200,0,4000,"Track Momentum [MeV]","Cluster Energy [MeV]");
      
      //plot1D("St"+std::to_string(stn)+"_p_"+std::to_string(xtal),6,1200,2400,"Track Momentum [MeV]","Entries");
      //plot1D("St"+std::to_string(stn)+"_E_"+std::to_string(xtal),6,1200,2400,"Cluster Energy [MeV]","Entries");

    }
  }
}

//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {


  bool failCut = false;
  // TFile *input1 = TFile::Open("../makePlots2/time_xtal.root");  
     
  //loop over the clusterTracker/tracker tree:
 vector<int> failedCuts_;
   for(int i = 0; i < 64; i++){
     failedCuts_.push_back(0);
   }
  
  
 while( NextallmuonsEvent() ) {

   // vector<string> cutNames_;
   //cutsNames_.at(0) = "nHits";
   
   
    //loop over the matches in this event:
   for(int i=0; i<am->nmatches; i++) {

     // scan accoss
     long long Q = am->trkPositronVertexQualityStatus[i]; 

     /* the loop above shifts the bit to print into the least significant bit (bit 0) of a temporary and ANDs it with 1 to remove all the other (higher order) bits and leave a 0 or 1. It starts with the most significant bit (63) and iterates down to the least significant bit (0), ensuring that the bits are printed in the correct order. */
     //     std::cout<<std::bitset<64>(Q);
     //x     TH1 *cuts = new TH1("cuts","cuts",65,-0.5,63.5);
     
     for (int iCut = 63; iCut >= 0; iCut--) {
       if( (Q >> iCut) & 1 ) {
	 failedCuts_.at(iCut)++;
      	 Fill1D("cuts",iCut);
	 cout<<iCut<<endl;
	 //	 cuts->SetBinContent(iCut+1,1);
	  }
        }
     
     // cout<<"\n"<<endl;

       double p = sqrt(am->trkMomX[i]*am->trkMomX[i] + am->trkMomY[i]*am->trkMomY[i] + am->trkMomZ[i]*am->trkMomZ[i]);
      
      const double logEop = log(am->EovP[i]);
      const double dt = am->Tdiff[i];
 
      int caloSt = am->cluCaloNum[i];

      const double caloX_raw = am->cluX[i];
      const double caloY_raw = am->cluY[i];
      int xtal = CaloNum(caloX_raw, caloY_raw);
      const double caloX = 112.5 - 25*(caloX_raw);
      const double caloY = SetCaloY(caloSt, caloY_raw);
      const double caloY_test = -(75.0 - 25*(caloY_raw));

      double trX = am->vX[i];
      double trY = am->vY[i];
  
      const double dX = caloX - trX;
      const double dY = caloY - trY;
      const double dR = sqrt(dX*dX + dY*dY);

      double t = (am -> cluTime[i]);

      double E = am->cluEne[i];
      double Ep = E/p;

      const double hits = am->nhits[i];
      if(hits != 1) continue;

      xtal = 0;
      //      cout<<caloSt<<endl;
     
      Fill1D("St"+std::to_string(caloSt)+"_dR_"+std::to_string(xtal),dR);
      Fill1D("St"+std::to_string(caloSt)+"_dt_"+std::to_string(xtal),dt);
      Fill1D("St"+std::to_string(caloSt)+"_logEop_"+std::to_string(xtal),logEop);
      Fill2D("St"+std::to_string(caloSt)+"_Ep_vs_t_"+std::to_string(xtal),t,Ep);
      Fill2D("St"+std::to_string(caloSt)+"_E_vs_p_"+std::to_string(xtal),p,E);      

   }
   ///   for(int t(0); t<64; t++)
   // cout<<t<<" "<<failedCuts_.at(t)<<"\n"<<endl;
   // Fill1D(cut
   
 }
  
 // input1 -> Close();
  
 return;
  
}
