//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk

#ifndef Skimmer_h
#define Skimmer_h

#include "Reader.h"
#include "Ntuple_Classes.h"

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;


class Skimmer {

 public:
  Skimmer(TString input_file_name, TString output_name="");

  void InitNtuple();
  void Run();
  bool NextClEvent(){return cr->NextEvent();}
  bool NextTrEvent(){return tr->NextEvent();}
  Cluster MakeCluster();
  Track MakeTrack();

  TString output_file_name;
  TFile *outfile;
  TTree *outtree;
  
  int o_subRunNum;
  int o_eventNum;
  std::vector<Cluster> o_clusters_13, o_clusters_19;
  std::vector<Track> o_tracks_13, o_tracks_19;
  
  clusterReader *cr;
  trackerReader *tr;


};

#endif

//==============================================================================

#ifdef Skimmer_C

Skimmer::Skimmer(TString input_file, TString output_file) : output_file_name(output_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  // ctt = new clusterTrackerTrackReader(input_file, "clusterTracker");  
  // cr = new clusterTrackerClusterReader(input_file);  
   cr = new clusterReader(input_file);  
  tr = new trackerReader(input_file);  
  //   am = new allmuonsReader(input_file);

  InitNtuple();
  
}






Cluster Skimmer::MakeCluster() {
  return Cluster( cr->nHit,
		  cr->energy,
		  cr->time,
		  cr->x,
		  cr->y );
}


Track Skimmer::MakeTrack() {
  return Track( tr->trackMomentum,
		tr->trackMomentumX,
		tr->trackMomentumY,
		tr->trackMomentumZ,
		tr->trackMomentumUnc,
		tr->decayVertexPosX,
		tr->decayVertexPosY,
		tr->decayVertexPosZ,
		tr->decayVertexMomX,
		tr->decayVertexMomY,
		tr->decayVertexMomZ,
		tr->decayVertexUncR,
		tr->decayVertexUncY,
		tr->decayVertexUncPR,
		tr->decayVertexUncPY,
		tr->caloVertexPosX,
		tr->caloVertexPosY,
		tr->caloVertexPosZ,
		tr->caloVertexMomX,
		tr->caloVertexMomY,
		tr->caloVertexMomZ,
		tr->caloVertexUncX,
		tr->caloVertexUncY,
		//tr->caloVertexUncPX,
		//tr->caloVertexUncPY,
		tr->trackT0,
		tr->time,
		tr->decayTime,
		tr->hitVolume,
		tr->trackPValue,
		tr->nHits,
		tr->nUHits,
		tr->nVHits,
		tr->missedLayersFrac,
		tr->minDriftTime,
		tr->maxDriftTime,
		tr->maxResidual,
		tr->extrapolatedDistance);
}



//=========================================================


// Can call the Plotter with a list of files to read.
// Defaults to a single hard-coded file
// Will make a separate output file for each input file.

int main(int argc, char *argv[]){

  TString fileName="";
  
  if (argc < 2){
    cout<<"Using hard-coded file list"<<endl;
    fileName = "/scratch/gm2/Omega/60hr/60hr_v9_17_01/gm2rootTrees_ana_15921.root";
    cout << "Reading " << fileName <<endl;
  }
  else if (argc > 3){
    cout<<"Only takes one argument: the input file name"<<endl;
    return 1;
  }
  else fileName = argv[1];
  
  size_t found = fileName.Last('.');
  TString run = fileName(found-5,5);
  
  cout << "Reading " << fileName <<", run: "<<run<<endl;

    
  Skimmer *p = new Skimmer(fileName, "ntuple_"+run+".root");
  p->Run();
  delete p;
  
  
  return 1;
}
  
#endif
