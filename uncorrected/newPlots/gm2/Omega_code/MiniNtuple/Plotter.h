//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Mar 17 13:38:56 2019 by ROOT version 6.16/00
// from TTree Plotter/Plotter
// found on file: ntuple.root
//////////////////////////////////////////////////////////

#ifndef Plotter_h
#define Plotter_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2.h>
#include <iostream>
#include "Ntuple_Classes.h"

class Plotter {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain
  Int_t           fCurrent; //!current Tree number in a TChain
  
  // Declaration of leaf types
  Int_t           subRunNum;
  Int_t           eventNum;
  std::vector<Cluster> Cl13, *ClP13, Cl19, *ClP19;
  std::vector<Track> Tr13, *TrP13, Tr19, *TrP19;
  
  // List of branches
  TBranch        *b_subRunNum;   //!
  TBranch        *b_eventNum;   //!
  TBranch        *b_Clusters_13;   //!
  TBranch        *b_Tracks_13;   //!
  TBranch        *b_Clusters_19;   //!
  TBranch        *b_Tracks_19;   //!
  
  Plotter(TString filename, TString output_file_name);
  virtual ~Plotter();
  virtual Int_t    GetEntry(Long64_t entry);
  virtual void     Init(TTree *tree);
  virtual void     Loop();
  void ReadEvent(int jentry);

  TString output_name;

  void InitHistos();
  TH1* plot1DMaker(TString name, int nbins, float xlow, float xhigh, TString xtitle="x axis", TString ytitle="", int col=2);  
  TH2* plot2DMaker(TString name, int nbinsx, float xlow, float xhigh, int nbinsy, float ylow, float yhigh, TString xtitle="x axis", TString ytitle="", int col=2);
  void plot1D(TString name, int nbins, float xlow, float xhigh, TString xtitle="x axis", TString ytitle="", int col=2);  
  void Fill1D(TString name, double val, double weight=1);
  void plot2D(TString name, int xnbins, float xlow, float xhigh, int ynbins, float ylow, float yhigh, TString xtitle="x axis", TString ytitle="", int col=2);
  void Fill2D(TString name, double xval, double yval, double weight=1);
  std::vector<TH1*> plots1D;
  std::vector<TH2*> plots2D;

  
  
};

#endif

#ifdef Plotter_cxx



void Plotter::ReadEvent(int jentry) {
  fChain->LoadTree(jentry);
  fChain->GetEntry(jentry);
  Tr13 = (*TrP13);
  Cl13 = (*ClP13);
  Tr19 = (*TrP19);
  Cl19 = (*ClP19);
}

Plotter::Plotter(TString filename, TString output_file_name) : fChain(0), output_name(output_file_name)
{
  TFile *f = new TFile(filename);
  TTree * tree=0;
  f->GetObject("Event",tree);
  Init(tree);
  InitHistos();
}

Plotter::~Plotter()
{

  TFile * output_file = new TFile(output_name, "RECREATE");
  output_file->cd();
  
  for(int i=0; i<plots1D.size(); i++) {
    if(plots1D[i]->GetEntries()==0) std::cout <<"1D Plot not used: "<<plots1D[i]->GetName()<<std::endl;
    else plots1D[i]->Write();
  }
  for(int i=0; i<plots2D.size(); i++) {
    if(plots2D[i]->GetEntries()==0) std::cout <<"2D Plot not used: "<<plots2D[i]->GetName()<<std::endl;
    else plots2D[i]->Write();
  }
  
  output_file->Close();
  std::cout<<"Plots written to "<<output_file->GetName()<<std::endl;
  delete output_file;
  
  for(int i=0; i<plots1D.size(); i++) delete plots1D[i];
  for(int i=0; i<plots2D.size(); i++) delete plots2D[i];
  plots1D.clear();
  plots2D.clear();


  
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Plotter::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}

void Plotter::Init(TTree *tree) {
  // Set branch addresses and branch pointers  
  ClP13=0;
  TrP13=0;
  ClP19=0;
  TrP19=0;
  
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  // fChain->SetMakeClass(1);
  
  //  fChain->SetBranchStatus("*",0);  // disable all branches by default
  // fChain->SetBranchStatus("Clusters",0);  // disable all branches by default
  // fChain->SetBranchStatus("Tracks",0);  // disable all branches by default
  
  fChain->SetBranchAddress("subRunNum", &subRunNum, &b_subRunNum);
  fChain->SetBranchAddress("eventNum", &eventNum, &b_eventNum);
  fChain->SetBranchAddress("Clusters_13", &ClP13, &b_Clusters_13);
  fChain->SetBranchAddress("Tracks_13", &TrP13, &b_Tracks_13);
  fChain->SetBranchAddress("Clusters_19", &ClP19, &b_Clusters_19);
  fChain->SetBranchAddress("Tracks_19", &TrP19, &b_Tracks_19);
  
}


void Plotter::plot1D(TString name, int nbins, float xlow, float xhigh, TString xtitle, TString ytitle, int col){
  plots1D.push_back(plot1DMaker(name, nbins, xlow, xhigh, xtitle, ytitle, col));
}

void Plotter::plot2D(TString name, int xnbins, float xlow, float xhigh, int ynbins, float ylow, float yhigh, TString xtitle, TString ytitle, int col){
  plots2D.push_back(plot2DMaker(name, xnbins, xlow, xhigh, ynbins, ylow, yhigh, xtitle, ytitle, col));
}

TH1 * Plotter::plot1DMaker(TString name, int nbins, float xlow, float xhigh, TString xtitle, TString ytitle, int col){
  TH1 * p = new TH1D(name, name, nbins, xlow, xhigh);
  p->Sumw2();
  p->SetDirectory(0);
  p->SetXTitle(xtitle);
  p->SetYTitle(ytitle);
  p->GetXaxis()->SetLabelSize(0.04);
  p->GetYaxis()->SetLabelSize(0.04);
  p->GetXaxis()->SetTitleOffset(1.2);
  p->GetYaxis()->SetTitleOffset(1.2);
  p->GetXaxis()->SetLabelFont(42);
  p->GetYaxis()->SetLabelFont(42);
  p->GetXaxis()->SetTitleFont(42);
  p->GetYaxis()->SetTitleFont(42);
  p->SetTitle(0);
  p->SetLineWidth(2);
  p->SetLineColor(col);
  p->SetMarkerColor(col);
  p->SetMarkerSize(1.5);
  return p;
}

TH2 * Plotter::plot2DMaker(TString name, int nbinsx, float xlow, float xhigh, int nbinsy, float ylow, float yhigh, TString xtitle, TString ytitle, int col){
  TH2 * p = new TH2D(name, name, nbinsx, xlow, xhigh, nbinsy, ylow, yhigh);
  p->Sumw2();
  p->SetDirectory(0);
  p->SetXTitle(xtitle);
  p->SetYTitle(ytitle);
  p->GetXaxis()->SetLabelSize(0.04);
  p->GetYaxis()->SetLabelSize(0.04);
  p->GetXaxis()->SetTitleOffset(1.2);
  p->GetYaxis()->SetTitleOffset(1.2);
  p->GetXaxis()->SetLabelFont(42);
  p->GetYaxis()->SetLabelFont(42);
  p->GetXaxis()->SetTitleFont(42);
  p->GetYaxis()->SetTitleFont(42);
  p->SetTitle(0);
  p->SetLineWidth(2);
  p->SetLineColor(col);
  p->SetMarkerColor(col);
  p->SetMarkerSize(1.5);
  return p;
}


void Plotter::Fill1D(TString name, double val, double weight) {
  for(int i=0; i<plots1D.size(); i++){
    if(name.CompareTo(plots1D[i]->GetName())) continue;
    plots1D[i]->Fill(val, weight);
    return;
  }
  std::cout<<"Plot1D "<<name<<" not found!"<<std::endl;
}

void Plotter::Fill2D(TString name, double xval, double yval, double weight) {
  for(int i=0; i<plots2D.size(); i++){
    if(name.CompareTo(plots2D[i]->GetName())) continue;
    plots2D[i]->Fill(xval, yval, weight);
    return;
  }
  std::cout<<"Plot2D "<<name<<" not found!"<<std::endl;
}


//============================================

int main(int argc, char *argv[]){

  TString fileName="";
  
  if (argc < 2){
    std::cout<<"Using hard-coded file list"<<std::endl;
    fileName = "/scratch/gm2/Omega/60hr/60hr_v9_17_01_mini/ntuple_15921.root";
  }
  else if (argc > 3){
    std::cout<<"Only takes one argument: the input file name"<<std::endl;
    return 1;
  }
  else fileName = argv[1];
  
  size_t found = fileName.Last('.');
  TString run = fileName(found-5,5);
  
  std::cout << "Reading " << fileName <<", run: "<<run<<std::endl;

  Plotter * a = new Plotter(fileName, "plots_"+run+".root");
  a->Loop();
  delete a;
  
  
  return 1;
}
  
#endif
