// Scan over time slices and plotd Ep vs E
// Sam Grant April-June 2019
// samuel.grant.18@ucl.ac.uk
// April-June 2019

#include <iostream>
//#include <vector>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TAttMarker.h"
#include "TLine.h"

using namespace std;

/* void draw(vector<TH1D *> hist_, string fname, int stn, int par, int err, bool save) { */

/*   string calo, para, tpara, axes; */
/*   string us = ""; */

/*   if(stn/\*  == 13) calo = "Stn 12, "; *\/ */
/*   /\* else calo = "Stn 18,"; *\/ */
/*   /\* axes = " *\/ */
/*   /\* gStyle->SetPalette(kRainBow); *\/ */
/*   /\* int nColors = gStyle->GetNumberOfColors(); *\/ */
/*   /\* int nHistos = hist_.size();; *\/ */
/*   /\* //cout<<hist_.size()<<endl; *\/ */
/*   /\*  */
/*   /\* TLegend *leg = new TLegend(0.79,0.69,0.89,0.89); *\/ */

/*   /\* for(int i(0); i<hist_.size(); i++) { *\/ */
/*   /\*   int histoColor = (float)nColors / hist_.size() * i; *\/ */
/*   /\*    */
/*   /\*   if(i==0) hist_.at(i)->Draw(); *\/ */
/*   /\*   hist_.at(i)->Draw("same"); *\/ */
/*   /\*  } *\/ */
    
/*   if(save) c->SaveAs(("Plots/"+fname+".png").c_str()); */
  
/*   delete c; */
/*   return; */
/* } */
  
int main() {
  //  string suffix = "_skip18";
  string suffix = "";
  // Define number of g-2 cycles to use 
  int cycles = 50;
  // To save plots to png then save = true  
  bool save = true;
  // Open input ROOT file
  string input_fname = "RootFiles/PlotsEnergyCorrectedTimeSlice.root";
  TFile *input = TFile::Open(input_fname.c_str());
  //  TFile *output = new TFile("A
  cout << "Reading ... " << input_fname << endl;
  string slice[7] = {"0-30 #mus","30-60 #mus","60-90 #mus","90-120 #mus","120-150 #mus","150-180 #mus","180-210 #mus"};
     // Station loop
    for (int stn(13); stn < 20; stn = stn + 6) {
      vector<TH1D *> scanVecA_;
      vector<TH1D *> scanVecTau_;	   
      string nameA, nameTau;
	TCanvas *c = new TCanvas("c","c",3000,2000);
	TLegend *leg = new TLegend(0.79,0.69,0.89,0.89);
      for(int t(0); t < 7; t++) {
	string h = "St"+to_string(stn)+"_Ep_vs_E_1_"+to_string(t);
	TH1D *hist = (TH1D*)input->Get(h.c_str());
	// Skip empty ones
	if(hist == 0) continue;


	hist->SetLineWidth(5);

	hist->GetYaxis()->SetRangeUser(0.8,1.2);
	gStyle->SetPalette(55);
	hist->SetLineColor(t+1);//gStyle->GetColorPalette(t));
	leg->AddEntry(hist,(slice[t]).c_str());
	if(t==0) hist->Draw();
	else hist->Draw("same");//"same");
        
	//	hist->SetTitle(slice[t].c_str());	

	hist->SetTitle(("Stn "+to_string(stn-1)+", Fiducial Region;Cluster Energy, E [GeV];Cluster Energy, E / Track Momentum, p").c_str());
      }
	  //	c->BuildLegend(0.79,0.69,0.89,0.89);
	  leg->Draw("same");
      	c->SaveAs(("Plots/St"+to_string(stn)+"_Ep_vs_E_t_slices.png").c_str());


	delete c;
    }

    
     input->Close();
    return 0; 
}



