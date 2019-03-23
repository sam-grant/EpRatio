#define Skimmer_C
#include "Skimmer.h"


bool sort_clusters_by_time( Cluster i, Cluster j) { return i.time < j.time; }
bool sort_tracks_by_time( Track i, Track j) { return i.time < j.time; }



void Skimmer::InitNtuple() {


  //=============================================================================
  //set up the slimmed file:
  outfile = new TFile(output_file_name, "RECREATE");
  outtree = new TTree("Event", "Event");
  outtree->SetDirectory (outfile);

  outtree->Branch("subRunNum", &o_subRunNum, "subRunNum/I");
  outtree->Branch("eventNum", &o_eventNum, "eventNum/I");
  outtree->Branch("Clusters_13", "std::vector<Cluster>", &o_clusters_13);
  outtree->Branch("Tracks_13", "std::vector<Track>", &o_tracks_13);
  outtree->Branch("Clusters_19", "std::vector<Cluster>", &o_clusters_19);
  outtree->Branch("Tracks_19", "std::vector<Track>", &o_tracks_19);

};



//=========================================================

//loop over the entries in the tree, making plots:

void Skimmer::Run() {

  const int nSR=500, nE=500;


  static vector<Track> tracks_13[nSR][nE];
  static vector<Cluster> clusters_13[nSR][nE];

  static  vector<Track> tracks_19[nSR][nE];
  static  vector<Cluster> clusters_19[nSR][nE];
  
  
  cout<<"Processing calo."<<endl;
  while( NextClEvent() ) {
    if ( cr->caloNum!=13 && cr->caloNum !=19 ) continue;  
    // cout<<cr->subRunNum<<" "<<cr->eventNum<<endl;
    if(cr->subRunNum>=nSR || cr->eventNum >= nE) return;
    if ( cr->caloNum==13) clusters_13[cr->subRunNum][cr->eventNum].push_back( MakeCluster() );
    else  clusters_19[cr->subRunNum][cr->eventNum].push_back( MakeCluster() );
  }
  
  
  cout<<"Processing tracks."<<endl;
  while( NextTrEvent() ) {
    if(tr->subRunNum>=nSR || tr->eventNum >= nE) return;
    if(tr->trackPValue < 0.05) continue;
    if(tr->station==12) tracks_13[tr->subRunNum][tr->eventNum].push_back( MakeTrack() );
    else tracks_19[tr->subRunNum][tr->eventNum].push_back( MakeTrack() );
  }
  
  
  //=======================================
  
  
  cout<<"Sort by time: "<<endl;
  for(int i=0; i<nSR; i++) {
    cout<<"Process subrun: "<<i<<endl;
    int nclu=0, ntr=0;
    for(int j=0; j<nE; j++) {
      if(clusters_13[i][j].size()==0 || tracks_13[i][j].size()==0) continue;
      if(clusters_19[i][j].size()==0 || tracks_19[i][j].size()==0) continue;
      nclu += clusters_13[i][j].size();
      nclu += clusters_19[i][j].size();
      std::sort (clusters_13[i][j].begin(), clusters_13[i][j].end(), sort_clusters_by_time); 
      std::sort (clusters_19[i][j].begin(), clusters_19[i][j].end(), sort_clusters_by_time); 
      
      ntr+=tracks_13[i][j].size();
      ntr+=tracks_19[i][j].size();
      std::sort (tracks_13[i][j].begin(), tracks_13[i][j].end(), sort_tracks_by_time);
      std::sort (tracks_19[i][j].begin(), tracks_19[i][j].end(), sort_tracks_by_time);
      
      o_subRunNum=i;
      o_eventNum=j;
      o_clusters_13=clusters_13[i][j];
      o_tracks_13=tracks_13[i][j];
      o_clusters_19=clusters_19[i][j];
      o_tracks_19=tracks_19[i][j];
      outtree->Fill();
    }
    cout<<"Contained clusters: "<<nclu<<", tracks: "<<ntr<<endl;

  }
 
  outfile->Write();
  outfile->Close();
  
   return;
}



