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
  track(double t, double p, int s) : time(t), pval(p), subrun(s) {};
  double time;
  double pval;
  int subrun;
};




void Write(TFile * f, TH1 * plot) { 
  f->cd();
  if(plot->GetEntries()==0) cout <<"1D Plot not used: "<<plot->GetName()<<endl;
  else plot->Write();
}
void Plotter::InitTrees(TString input_file) {
  //initialise the trees you want to read
  //then enable the relevant branches in Reader.C
  // ctt = new clusterTrackerTrackReader(input_file);  
  // ctc = new clusterTrackerClusterReader(input_file);  
  // cr = new clusterReader(input_file);  
  tr = new trackerReader(input_file);  
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
  
  TH1 *time[200];
  TH1 *time_diff_55_55_event[200];
  
  TH1 *time_diff_55_55 = plot1DMaker("time_diff_55_55", 4000, 0, 30, "track time i - track time j [ns]" );
  TH2 *pval_55_55_lo = plot2DMaker("pval_55_55_lo", 1001, -0.001, 1, 1001, -0.001, 1, "p-value", "p-value" );
  TH2 *pval_55_55_hi = plot2DMaker("pval_55_55_hi", 1001, -0.001, 1, 1001, -0.001, 1, "p-value", "p-value" );



  for(int i=0; i<200; i++) {
    time[i] = plot1DMaker("time_"+std::to_string(i), 1000, 0, 1000, "track time i - track time j [#mu s]" );
    
    time_diff_55_55_event[i] = plot1DMaker("time_diff_55_55_"+std::to_string(i), 4000, 0, 30, "track time i - track time j [ns]" );
  }


  
  while( NextTrEvent() ) {
    
    if(tr->station!=18) continue;
    //    if(tr->trackPValue<0.01) continue;
    if( tr->time < 55000) continue;
    // Fill1D("time", tr->time/1000);
    //    times[tr->eventNum].push_back(tr->time/1000);
    const double pval =  tr->trackPValue < 0.0001 ?  -0.0001 : tr->trackPValue;
    tracks[tr->eventNum].push_back( new track(tr->time, pval, tr->subRunNum) );
         
  } //end of loop over entries
  



  
  cout<<"plotting time differences"<<endl;
 
  for(int ievent=0; ievent<200; ievent++) {
   
    cout<<"Processing event "<<ievent<<endl;


    //no p-value cut:
    for(int i=0; i<tracks[ievent].size(); i++) {
      time[ievent]->Fill(tracks[ievent][i]->time);
      for(int j=i+1; j<tracks[ievent].size(); j++) {
	const double dt =  fabs(tracks[ievent][i]->time - tracks[ievent][j]->time);
	if(dt>30) continue;
	time_diff_55_55->Fill( dt );
	time_diff_55_55_event[ievent]->Fill( dt );

	if(dt<3) {
	  //if(tracks[ievent][i]->pval<0.0001) cout<<tracks[ievent][i]->pval<<endl;
	  pval_55_55_lo->Fill( tracks[ievent][i]->pval, tracks[ievent][j]->pval );
	}
	else if(dt>10) {
	  pval_55_55_hi->Fill( tracks[ievent][i]->pval, tracks[ievent][j]->pval );
	}
	
      }// j loop
      
    }//loop over times _p1
    tracks[ievent].clear();
    
    
  }//loop over events
  












  

  TFile * output_file = new TFile("time_diff_"+output_name, "RECREATE");
  output_file->cd();


  Write(output_file, time_diff_55_55 );
  Write(output_file, pval_55_55_lo );
  Write(output_file, pval_55_55_hi );

  for(int i=0; i<200; i++) {
    Write(output_file, time[i]);

    Write(output_file, time_diff_55_55_event[i] );

  }

  cout<<"Plots really written to: "<< output_file->GetName()<<endl;
  output_file->Close();
  
  return;
}





