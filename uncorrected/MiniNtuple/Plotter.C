#define Plotter_cxx
#include "Plotter.h"
#include "TH1.h"

using std::cout;
using std::endl;
using std::vector;

void Plotter::InitHistos() {

  plot1D("dt", 1000,-1000,1000, "#Delta t [ns]");
  plot1D("track_dt", 1000,-1000,1000, "#Delta t [ns]");
  plot1D("dt_double", 1000,-1000,1000, "#Delta t [ns]");
  plot1D("dt_single", 1000,-1000,1000, "#Delta t [ns]");
  plot2D("Ep", 100,0,4000, 100,0,400, "p [MeV]", "E [MeV]");
  plot1D("nmatch_single", 6,-0.5, 5.5, "# matches");
  plot1D("nmatch_double", 6,-0.5, 5.5, "# matches");


}


void Plotter::Loop()
{
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  
  Long64_t nbytes = 0, nb = 0;
  //  for (Long64_t jentry=0; jentry<nentries;jentry++) {
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    ReadEvent(jentry);
    
    for(int j=0; j<Tr13.size()-1; j++){
      for(int k=j+1; k<Tr13.size(); k++){
	Fill1D("track_dt", Tr13[k].time - Tr13[j].time);
      }
    }
    
    
    for(int i=0; i<Cl13.size(); i++){
      //      if( !(i%5000) )cout<<i<<endl;
      bool single_mu = false;
      if(Cl13[i].energy > 400 || Cl13[i].energy < 130) continue;
      if(Cl13[i].energy < 220) single_mu=true;
      else if (Cl13[i].energy < 300) continue;

      vector<int> mch;
      for(int j=0; j<Tr13.size(); j++){
	const float dt = Tr13[j].time - Cl13[i].time;
	Fill1D("dt", dt);
	if(fabs(dt)>12) continue;
	Fill2D("Ep", Tr13[j].trackMomentum, Cl13[i].energy);
	if(Tr13[j].trackMomentum<2200) continue;
	mch.push_back(j);
      }

      //number of matching tracks
      if(single_mu) Fill1D("nmatch_single", mch.size());
      else Fill1D("nmatch_double", mch.size());
      if(mch.size()==0) continue;


      const double ref_time = Tr13[mch[0]].time;
      
      for(int j=0; j<Tr13.size(); j++){
	if(j==mch[0]) continue;
	if(Tr13[j].trackMomentum<2200) continue;
	const float dt = Tr13[j].time - ref_time;
	if(single_mu) Fill1D("dt_single", dt);
	else Fill1D("dt_double", dt);



	
      }
      
	mch.clear();

	
    }//calo loop 




    
  }//end of loop over entries
  
}//end of function
