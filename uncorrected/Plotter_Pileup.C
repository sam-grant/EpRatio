//Simple code to make plots from the Europa OmegaA ntuples
// gavin.hesketh@ucl.ac.uk

//Enable the tree you want to use here
//to use a particular branch, make sure it is uncommented in Reader.C
//branch variables are listed in Reader.h

//This simple example makes plots of E/p andE vs p for matched tracks & clusters

#define Plotter_C
#include "Plotter.h"
#include "TMath.h"


class track{
public:
  track(double t, double mom, double En, double pv, bool l_m) : time(t), p(mom), E(En), pval(pv), lost_muon(l_m) {};
  double time;
  double p;
  double E;
  double pval;
  double Eop() { return E/p;};
  bool lost_muon;
};




void Write(TFile * f, TH1 * plot) { 
  f->cd();
  if(plot->GetEntries()==0) cout <<"1D Plot not used: "<<plot->GetName()<<endl;
  else plot->Write();
}
void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  ctt = new clusterTrackerTrackReader(input_file);  
  // ctc = new clusterTrackerClusterReader(input_file);  
  // cr = new clusterReader(input_file);  
  // tr = new trackerReader(input_file);  
}

void Plotter::InitHistos() {

  //define the histograms here
  //arguments (^ = optional) :
  // name (also used as title), nbins, xlow, xhigh, xtitle^, ytitle^, line colour^
 

};



//=========================================================

//loop over the entries in the tree, making plots:

void Plotter::Run() {

  //loop over the clusterTracker/tracker tree:
  vector<track*> tracks[200];
  
  //  TH1 *time[200];
  TH1 *time_diff_single_event[200];
  TH1 *time_diff_double_event[200];
  
  TH1 *time_diff_single = plot1DMaker("time_diff_single", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_single_tcut = plot1DMaker("time_diff_single_tcut", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_single_pval = plot1DMaker("time_diff_single_pval", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_single_pval_tcut = plot1DMaker("time_diff_single_pval_tcut", 300, 0, 150, "track time i - track time j [ns]" );
  TH2 *track_momentum_single = plot2DMaker("track_momentum_single", 180, 2200, 4000, 400, 0, 4000, "track 1 momentum [MeV]", "track 2 momentum [MeV]" );


  TH1 *time_diff_double = plot1DMaker("time_diff_double", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_double_tcut = plot1DMaker("time_diff_double_tcut", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_double_pval = plot1DMaker("time_diff_double_pval", 300, 0, 150, "track time i - track time j [ns]" );
  TH1 *time_diff_double_pval_tcut = plot1DMaker("time_diff_double_pval_tcut", 300, 0, 150, "track time i - track time j [ns]" );
  TH2 *track_momentum_double = plot2DMaker("track_momentum_double", 180, 2200, 4000, 400, 0, 4000, "track 1 momentum [MeV]", "track 2 momentum [MeV]" );

  TH2 *E_vs_p = plot2DMaker("E_vs_p", 180, 2200, 4000, 410, 0, 410, "track momentum [MeV]", "cluster energy [MeV]" );



  
  /*
  for(int i=0; i<200; i++) {
    
    time_diff_single_event[i] = plot1DMaker("time_diff_55_55_"+std::to_string(i), 4000, 0, 30, "track time i - track time j [ns]" );
  }
  */

  
  while( NextClTrTrEvent() ) {
    
    if(ctt->clusterCaloNum!=13) continue;
    //    if( ctt->time < 55000) continue;
    // Fill1D("time", ctt->time/1000);
    //    times[ctt->eventNum].push_back(ctt->time/1000);
    bool lost_muon=true;
    if(ctt->trackPValue<0.05) lost_muon=false;
    const double dt = ctt->trackTimeDiff;
    if(ctt->clusterCaloNum==13){
      if (dt<-8 || dt>3 ) lost_muon=false;
    }
    else {
      if(dt<-9 || dt>1) lost_muon=false;        
    }

    const double caloX_raw = ctt->clusterX;
    const double caloY_raw = ctt->clusterY;
    const double caloX = 112.5 - 25*(caloX_raw);
    const double caloY = SetCaloY(ctt->clusterCaloNum, caloY_raw);
    const double trX = ctt->caloVertexPosX;
    const double trY = ctt->caloVertexPosY;
    
    const double dX = caloX - trX;
    const double dY = caloY - trY;
    const double dR = sqrt(dX*dX + dY*dY);
    if(dR>70) lost_muon=false;
    const double p = ctt->trackMomentum;
    const double E = ctt->clusterE;
    if(p < 2300) lost_muon=false;
    if(E > 400) lost_muon=false;
    if(E < 110) lost_muon=false;
    if(E > 230 && E < 300) lost_muon=false;
    
    tracks[ctt->eventNum].push_back( new track(ctt->clusterTime, p, E, ctt->trackPValue, lost_muon) );
    
  } //end of loop over entries
  



  
  cout<<"plotting time differences"<<endl;
 
  for(int ievent=0; ievent<200; ievent++) {
    
    cout<<"Processing event "<<ievent<<endl;
    
    
    for(int i=0; i<tracks[ievent].size(); i++) {
      
      if(!tracks[ievent][i]->lost_muon) continue;
      
      E_vs_p->Fill(tracks[ievent][i]->p, tracks[ievent][i]->E);
      
      for(int j=0; j<tracks[ievent].size(); j++) {
	if(j==i) continue;
	
	const double dt =  fabs(tracks[ievent][i]->time - tracks[ievent][j]->time);
	//if(dt>30) continue;

	//double mip:
	if(tracks[ievent][i]->E > 290)  {
	  time_diff_double->Fill( dt );
	  if(tracks[ievent][i]->time > 30000)  time_diff_double_tcut->Fill( dt );
	  if(dt<0.5) track_momentum_double->Fill( tracks[ievent][i]->p, tracks[ievent][j]->p );
	  if(tracks[ievent][j]->pval > 0.05) {
	    time_diff_double_pval->Fill( dt );
	    if(tracks[ievent][i]->time > 30000)  time_diff_double_pval_tcut->Fill( dt );
	  }
	}
	else {
	  time_diff_single->Fill( dt );
	  if(tracks[ievent][i]->time > 30000)  time_diff_single_tcut->Fill( dt );
	  if(dt<0.5) track_momentum_single->Fill( tracks[ievent][i]->p, tracks[ievent][j]->p  );
	  if(tracks[ievent][j]->pval > 0.05) {
	    time_diff_single_pval->Fill( dt );
	    if(tracks[ievent][i]->time > 30000)  time_diff_single_pval_tcut->Fill( dt );
	  }

	}
	/*
	if(dt<3) {
	  //if(tracks[ievent][i]->pval<0.0001) cout<<tracks[ievent][i]->pval<<endl;
	  pval_55_55_lo->Fill( tracks[ievent][i]->pval, tracks[ievent][j]->pval );
	}
	else if(dt>10) {
	  pval_55_55_hi->Fill( tracks[ievent][i]->pval, tracks[ievent][j]->pval );
	}
	*/
      }// j loop
      
    }//loop over times _p1
    tracks[ievent].clear();
    
    
  }//loop over events
  












  

  TFile * output_file = new TFile("time_diff_"+output_name, "RECREATE");
  output_file->cd();


  Write(output_file, E_vs_p );
  Write(output_file, time_diff_single );
  Write(output_file, time_diff_single_tcut );
  Write(output_file, time_diff_single_pval );
  Write(output_file, time_diff_single_pval_tcut );
  Write(output_file, track_momentum_single );

  Write(output_file, time_diff_double );
  Write(output_file, time_diff_double_tcut );
  Write(output_file, time_diff_double_pval );
  Write(output_file, time_diff_double_pval_tcut );
  Write(output_file, track_momentum_double );


  /*
  for(int i=0; i<200; i++) {
    Write(output_file, time[i]);

    Write(output_file, time_diff_55_55_event[i] );

  }
  */
  cout<<"Plots really written to: "<< output_file->GetName()<<endl;
  output_file->Close();
  
  return;
}





