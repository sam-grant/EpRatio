// Sam Grant
// Read in-fill gain parameters and output 1D pull distribution
// samuel.grant.18@ucl.ac.uk
// May 2019

  #include <iostream>
  #include "TH1D.h"
  #include "TCanvas.h"
  #include "TFile.h"
  #include "TStyle.h"
  #include "TDirectory.h"
  #include "TPaveStats.h"
  #include "TAttFill.h"
  #include "TLegend.h"
  #include "SetSigFigs.h"

using namespace std;

// Define pull
double pull(double EpValue,double laserValue, double EpError, double laserError) {
  double sigma = sqrt(EpError*EpError + laserError*laserError);
  return (laserValue - EpValue) / sigma;
}

  // Drawing function
  void draw(TH1D *hist0, TH1D *hist1, TH1D *hist2, TFile *output, string name, string title) {
    
    hist0->SetStats(0);
    hist0->SetLineColor(kBlack);
    gStyle->SetOptStat(2211);
    gStyle->SetStatFormat("6.3g");
    hist1->Draw();
    gPad->Update();

    //Collect stats of the first histogram
    TPaveStats *tps1 = (TPaveStats*) hist1 -> FindObject("stats");



    tps1->SetX1NDC(0.65);
    tps1->SetX2NDC(0.89);
    tps1->SetY1NDC(0.65);
    tps1->SetY2NDC(0.88);

    double X1 = tps1->GetX1NDC();
    double Y1 = tps1->GetY1NDC();
    double X2 = tps1->GetX2NDC();
    double Y2 = tps1->GetY2NDC();

    cout<<X1<<" "<<X2<<" "<<Y1<<" "<<Y2<<endl;

    hist2->Draw();
    gPad->Update();
   
    TPaveStats *tps2 = (TPaveStats*) hist2 -> FindObject("stats");


    // Put stat box beneath the first
    tps2->SetX1NDC(X1);
    tps2->SetX2NDC(X2);
    tps2->SetY1NDC((Y1-0.025)-(Y2-Y1));
    tps2->SetY2NDC(Y1-0.025);

    TCanvas *c = new TCanvas("c","",800,600);//3000,2000);

    hist1->GetXaxis()->CenterTitle(true);
    hist1->GetYaxis()->CenterTitle(true);
    hist1->SetTitleSize(.75);
    hist1->GetXaxis()->SetTitleSize(.04);
    hist1->GetYaxis()->SetTitleSize(.04);
    hist1->GetYaxis()->SetTitleOffset(1.1);//0.70);
    hist1->GetXaxis()->SetTitleOffset(1.1);//0.75);

    /////////// Set colour scheme /////////////
    float transpancy = 0.0;
    hist1->SetLineColor(kBlue);
    hist2->SetLineColor(kGreen-3);
    hist1->SetFillColorAlpha(kBlue, transpancy);
    hist2->SetFillColorAlpha(kGreen-3, transpancy);
    tps1->SetTextColor(kBlack);
    tps1->SetLineColor(kBlue);
    tps1->SetFillColorAlpha(kBlue,transpancy);
    tps2->SetTextColor(kBlack);
    tps2->SetLineColor(kGreen-3);
    tps2->SetFillColorAlpha(kGreen-3,transpancy);
    ///////////////////////////////////////////
 
    int lineWidth = 3;
    hist0->SetLineWidth(lineWidth);
    hist1->SetLineWidth(lineWidth);
    hist2->SetLineWidth(lineWidth);
    tps1->SetLineWidth(lineWidth);
    tps2->SetLineWidth(lineWidth);
    gPad->SetFrameLineWidth(lineWidth); 

 //   gPad->Update(); 
    hist1->SetTitle(title.c_str());

    hist1->Draw("same");//"same");
    hist2->Draw("same");
    hist0->Draw("same");
    tps1->Draw("same");
    tps2->Draw("same");

    //xc gPad->RedrawAxis(); 

    //xcgPad->RedrawAxis();
    c->SaveAs(name.c_str());
    
    delete c;
    
    hist1->SetDirectory(output);
    hist2->SetDirectory(output);
    
    return;
  }

int main() {

  string inputFnameEp = "RootFiles/EpParameters_Q.root";
  string inputFnameLaser = "RootFiles/LaserParameters.root";

  cout<<"Reading... "<<inputFnameEp<<endl;
  cout<<"Reading... "<<inputFnameLaser<<endl;

  string outputFname = "RootFiles/Statistics.root";//1DStatPlots"+suffix+".root";
    
  // Set input
  TH1D *Ep, *laser;

  string h[4] = {"tau_13","tau_19","amp_13","amp_19"};

  TFile *inputEp = TFile::Open(inputFnameEp.c_str());
  TFile *inputLaser = TFile::Open(inputFnameLaser.c_str());
 
  // Set output
  TFile *output = new TFile(outputFname.c_str(),"RECREATE");

  double pullValue, EpValue, laserValue, EpError, laserError;
  
  // Book histograms
  int factor = 1;
  
  TH1D *dummy = new TH1D("dummy","dummy",20*factor,-5,5);
  TH1D *pullHistAmp = new TH1D("#alpha","pullHistAmp",20*factor,-5,5);//7,-0.5,3); 
  TH1D *pullHistTau = new TH1D("#tau_{r}","pullHistTau",20*factor,-5,5);//9,-3.5,1);//20*factor,-5,5);

  int counter = 0;

  // Start hist loop
  for (int iHist(0); iHist < 4; iHist++) {
    
    // Start xtal loop
    for (int xtal(0); xtal < 54; xtal++) {

      Ep = (TH1D*)inputEp->Get(h[iHist].c_str());
      laser = (TH1D*)inputLaser->Get(h[iHist].c_str());
      
      // Get pullValues and errors
      EpValue = Ep->GetBinContent(xtal+1);
      EpError = Ep->GetBinError(xtal+1);

      if (EpValue == 0) continue;

      laserValue = laser->GetBinContent(xtal+1);
      laserError = laser->GetBinError(xtal+1);

      if (laserValue == 0) continue;
      
      // Calculate pull
      pullValue= pull(EpValue,laserValue,EpError,laserError);
     
      // Print
      cout<<"xtal: "<<xtal<<"; pull: "<<pullValue<<endl;

      if(iHist < 2) {
      pullHistTau->Fill(pullValue);
      }
      else if(iHist >= 2) {
      pullHistAmp->Fill(pullValue);
      }
      else {
	cout<<"**Error in histogram filling**"<<endl;
      counter++;
      }

    }
    
  }

  cout<<"xtals: "<<counter<<endl;

  pullHistAmp->GetYaxis()->SetRangeUser(0,7);
  draw(dummy,pullHistAmp,pullHistTau,output,"PlotsGoldList/PullOverlay1D2.pdf",";Pull [#sigma];Entries / 1#sigma");

  output->Write(); 

  cout<<outputFname<<" created..."<<endl;
  
  return 0;
}
