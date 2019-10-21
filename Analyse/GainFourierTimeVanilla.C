// Sam Grant April-June 2019
// samuel.grant.18@ucl.ac.uk
// April-June 2019

#include <iostream>
#include "TF1.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TDirectory.h"
#include "TVirtualFFT.h"
#include "TROOT.h"

using namespace std;

void FFT(TH1D *hist, double maxTime, string fftFname) {
  TH1D *histClone = (TH1D*)hist->Clone("histClone");
  // Book empty histogram to record the magitudes
  TH1 *mag = 0;
  // Execute fourier transform
  TVirtualFFT::SetTransform(0);
  mag = histClone -> FFT(mag,"MAG");
  
    //Rescale x-axis by dividing by the function domain
  TAxis *xaxis = mag -> GetXaxis();
  int nBins = histClone -> GetNbinsX();
  double *ba = new double[nBins+1];
  xaxis -> GetLowEdge(ba);
  double Scale = 1./(maxTime - 0);
  ba[nBins] = ba[nBins-1] + xaxis -> GetBinWidth(nBins);
  
  for (int i = 0; i < nBins + 1; i++) {
       ba[i] *= Scale;
  }
  // Book a new fft histCloneogram
  TH1D* fft = new TH1D("fft", "fft", nBins, ba);
  for (int i = 0; i < nBins+1; i++) {
    fft -> SetBinContent(i, mag -> GetBinContent(i));
    fft -> SetBinError(i, mag -> GetBinError(i));
  }
  fft -> SetTitle(";Frequency [MHz];Normalised Magnitude");
  fft -> SetStats(0);
  fft -> SetName(fftFname.c_str());
  fft -> Scale(1.0 / fft -> Integral());

  double binWidth = maxTime / nBins ;
  double sampleRate = 1 / binWidth;
  double nyquistFreq = 0.5 * sampleRate;

  std::cout << "binWidth " << binWidth <<" us"<< std::endl;
  std::cout << "sampleRate " << sampleRate <<" MHz"<< std::endl;
  std::cout << "nyquistFreq " << nyquistFreq <<" MHz"<< std::endl;  

  // Book canvas, make it high def
  TCanvas *c1 = new TCanvas("c1","c1",3000,2000);
  //  fft->GetXaxis()->SetTitle("Frequency [MHz]");
  fft->GetXaxis()->SetRangeUser(0,nyquistFreq);
  gPad->SetLogy();
  fft->Draw();
  c1->SaveAs(("Plots/"+fftFname+".png").c_str());

  delete c1;
  delete fft;
  delete mag;
  return;
  
}

int main() {
  
  bool quality = true;
  // To save plots to png then save = true  
  bool save = true;

  //  string suffix = "_skip18";
  string suffix = "";
  // Define number of g-2 cycles to use 
  int cycles = 50;
  int range = 12;

  // Counter for crystals 
  int counter = 0;
 
  // Open input ROOT file
  string inputFname = "RootFiles/PlotsTimeCorrected.root";
  TFile *input = TFile::Open(inputFname.c_str());
  cout << "Reading ... " << inputFname << endl;

  if(quality) suffix = suffix+"_Q";
  else if(!quality) suffix = suffix+"_noQ";

  // Book output ROOT file
  string outputFname = "RootFiles/FFTCorrected.root";
  TFile *output = new TFile(outputFname.c_str(), "recreate");
  
  // Define time limit
  const int maxTime = 4.2*cycles;

  // Station loop
  for (int stn(13); stn < 20; stn = stn + 6) {
    if(stn != 13 ) continue;
    // Fid loop
    for (int fid(0); fid < 2; fid++) {
       if(fid != 0) continue;
      // Book histogram
      string h = "St"+to_string(stn)+"_Ep_vs_t_"+to_string(fid);
      TH1D *hist = (TH1D*)input->Get(h.c_str());

      // Skip empty ones
      if(hist == 0) continue;

      FFT(hist,4.2*range,"St"+to_string(stn)+"_FFT_"+to_string(fid));
    }
  }
  // Print out the number of xtals that pass quality cuts
  //  cout << "\nSurviving brds: " << counter << endl;

  // Write and close input/output
  output->Write();
  output->Close();
  input->Close();

  cout << "Created: " << outputFname << endl;
  return 0; 
}



