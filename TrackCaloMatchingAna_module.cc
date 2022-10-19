//////////////////////////////////////////////////////////////////
// Perform matching between tracks and calo clusters, making plots
// Written/modified by: James Mott, Tammy Walton, Sam Grant
//////////////////////////////////////////////////////////////////

// Include needed ART headers
#include "art/Framework/Core/EDAnalyzer.h"
#include "art/Framework/Core/ModuleMacros.h"
#include "art/Framework/Principal/Event.h"
#include "art/Framework/Services/Optional/TFileService.h"
#include "art/Framework/Services/Registry/ServiceHandle.h"
#include "canvas/Persistency/Common/FindManyP.h"

//Geant4
#include "Geant4/G4SystemOfUnits.hh"

//decay vertex art record
#include "gm2dataproducts/strawtracker/DecayVertexArtRecord.hh"
#include "gm2dataproducts/calo/ClusterArtRecord.hh"
#include "gm2dataproducts/daq/CCCArtRecord.hh"

//Utils
#include "gm2geom/common/Gm2Constants_service.hh"
#include "gm2geom/strawtracker/StrawTrackerGeometry_service.hh"
#include "gm2util/common/dataModuleDefs.hh"
#include "gm2util/common/RootManager.hh"
#include "gm2tracker/quality/TrackQuality_service.hh"
#include "gm2calo/util/CaloGeomUtil.hh"

//C++ includes
#include <iostream>
#include <string>
#include <vector>

// Class declaration
class TrackCaloMatchingAna : public art::EDAnalyzer {

public:

  explicit TrackCaloMatchingAna(fhicl::ParameterSet const& pset);

  //Override desired art::EDAnalyzer functions
  void beginJob() override;
  void beginRun(art::Run const & r) override;
  void analyze(const art::Event& event ) override;
  void endJob() override;

private:

  //Producer labels
  std::string vertexModuleLabel_;
  std::string vertexInstanceLabel_;
  std::string decayVertexInstanceName_;
  std::string matchedModuleLabel_;
  std::string matchedInstanceLabel_;

  //ROOT plotting members
  std::unique_ptr<RootManager> rm_;
  std::string dirName_;

  //Helper tools
  gm2geom::CoordSystemsStoreData cs_;
  art::ServiceHandle<gm2geom::StrawTrackerGeometryService> sgeom_;
  art::ServiceHandle<gm2strawtracker::TrackQuality> trackQuality_;
  gm2calo::CaloGeomUtil caloGeomUtils_;

  //FCL config
  std::string energyCalibModule_;
  std::string preGainCorrModule_;
  bool applyTrackQuality_; // Track level cuts
  std::vector<double> coincidenceTimeWindow_;
  std::vector<TDirectory*> dirs_;
  bool perXtal_; // Run E/p gain plots crystal-by-crystal
  bool applyCaloVertexQuality_; // Forwards vertex cuts
  bool applyPositronVertexQuality_; // Positron selection
  bool applyLostMuonVertexQuality_; // Lost muon selection

};

//
// Class implementation
//

TrackCaloMatchingAna::TrackCaloMatchingAna(fhicl::ParameterSet const& pset)
: art::EDAnalyzer(pset)

, vertexModuleLabel_(pset.get<std::string>("vertexModuleLabel", dataModuleDefs::vertexModuleLabel()) )
, vertexInstanceLabel_(pset.get<std::string>("vertexInstanceLabel", dataModuleDefs::forwardExtrapInstanceLabel()) )
, decayVertexInstanceName_( pset.get<std::string>("decayVertexInstanceName",dataModuleDefs::backExtrapInstanceLabel()) )
, matchedModuleLabel_(pset.get<std::string>("matchedModuleLabel", "trackCaloMatching") )
, matchedInstanceLabel_(pset.get<std::string>("matchedInstanceLabel", "") )
, rm_()
, dirName_(pset.get<std::string>("dirName", "TrackCaloMatches") )
, cs_()
, sgeom_()
, caloGeomUtils_()
, energyCalibModule_(pset.get<std::string>("energyCalibModule", "energyCalibratorDAQ") )
, preGainCorrModule_(pset.get<std::string>("preGainCorrModule", "stdplaserCorrector") )
, applyTrackQuality_(pset.get<bool>("applyTrackQuality",true) )
, coincidenceTimeWindow_(pset.get<vector<double> >("coincidenceTimeWindow",{-24,24}) )
, perXtal_(pset.get<bool>("perXtal",false) ) // Makes E/p vs time per xtal
, applyCaloVertexQuality_(pset.get<bool>("applyCaloVertexQuality",false) )
, applyPositronVertexQuality_(pset.get<bool>("applyPositronVertexQuality",false) )
, applyLostMuonVertexQuality_(pset.get<bool>("applyLostMuonVertexQuality",false) )

{

  if (applyPositronVertexQuality_ && applyLostMuonVertexQuality_) {
    throw cet::exception("TrackCaloMatchingAna") << "You have selected both positrons and lost muons, please use one or the other (or neither) in your fcl file: applyPostronVertexQuality or applyLostMuonVertexQuality\n";
  }

}


 void TrackCaloMatchingAna::beginJob() {

  // Create a ROOT file and manager 
  art::ServiceHandle<art::TFileService> tfs;
  auto& outputRootFile = tfs->file();
  rm_.reset( new RootManager("TrackCaloMatchingAna", &outputRootFile) );

  // Create directory structure (do it here so that they're in reasonable order)
  auto topDir = rm_->GetDir(&outputRootFile,dirName_,true); //true -> create if doesn't exist

  // Make some sub-directories for tracker stations
  for(auto s : sgeom_->geom().whichScallopLocations) {

    std::string subDir = Form("Station[%d]",s);
    auto stationDir = rm_->GetDir(topDir,subDir.c_str(),true);
    dirs_.push_back(stationDir);

  }  

  // List of directories we're going to book histograms in
  auto tmpDirs = dirs_;
  tmpDirs.push_back(topDir);

  // Book histograms
  for(auto d : tmpDirs) {

    rm_->Add(d, new TH1F("MatchesPerTrack", ";Matched clusters per track", 11, -1, 10));
    rm_->Add(d, new TH1F("CaloTime", ";Calo cluster time [ns]", 1000, 0, 800000));
    rm_->Add(d, new TH1F("TimeDiff", ";Calo cluster time - track vertex time [ns]", 480, coincidenceTimeWindow_.at(0), coincidenceTimeWindow_.at(1)));
    rm_->Add(d, new TH1F("TimeDiffAll", ";Calo cluster time - track vertex time [ns]", 800, -1000, 1000));
    rm_->Add(d, new TH1D("RadialDiff", ";Calo radial position - track vertex radial position [mm]",1000,0,100)); 
    rm_->Add(d, new TH2F("StrawDriftTime", ";Straw hit time [ns] - calo cluster time;Straw Layer", 80, coincidenceTimeWindow_.at(0), 100 + coincidenceTimeWindow_.at(0), 96, 0, 96));
    rm_->Add(d, new TH1F("CaloEnergy", ";Calo energy [MeV]", 1000, 0, 4000));
    rm_->Add(d, new TH1F("TrackMomentum", ";Track momentum [MeV]", 1000, 0, 4000));
    rm_->Add(d, new TH2F("EvsP", ";Track momentum [MeV];Calo cluster energy [MeV]", 1000, 0, 4000, 1000, 0, 4000));
    rm_->Add(d, new TH1F("EoverP", ";Calo cluster energy / track momentum", 600, 0, 3));
    rm_->Add(d, new TH1F("LogEoverP", ";Log( calo cluster energy / track momentum )", 600, -3.5, 1.0));
    rm_->Add(d, new TH2F("TrackPositionAll", ";Track Radial Position [mm];Track Vertical Position [mm]", 1100, -275, 275, 300, -150, 150));
    rm_->Add(d, new TH2F("TrackPositionNoCluster", ";Track Radial Position [mm];Track Vertical Position [mm]", 1100, -275, 275, 300, -150, 150));
    rm_->Add(d, new TH2F("TrackPositionCluster", ";Track Radial Position [mm];Track Vertical Position [mm]", 1100, -275, 275, 300, -150, 150));
    rm_->Add(d, new TH2F("CaloEfficiency", ";Track Radial Position [mm];Track Vertical Position [mm]", 1100, -275, 275, 300, -150, 150));
    rm_->Add(d, new TH2F("CaloInefficiency", ";Track Radial Position [mm];Track Vertical Position [mm]", 1100, -275, 275, 300, -150, 150));

    // Gain plots
    rm_->Add(d, new TH2F("EoverPvsTime", ";Calo cluster time [ns];Calo cluster energy / track momentum", 50, 0, 4200*50, 600, 0, 3));
    rm_->Add(d, new TH2F("EoverPvsTimePreGainCorr", ";Calo cluster time [ns];Calo cluster energy / track Momentum", 50, 0, 4200*50, 600, 0, 3));

    // Make gain plots per calo crystal if required
    if(perXtal_) {

      // Loop over crystals 
      for (int xtal(0); xtal < 54; xtal++) {

        rm_->Add(d, new TH2F(("EoverPvsTimeXtal_"+std::to_string(xtal)).c_str(), ";Cluster time [ns];Cluster energy / track momentum", 50, 0, 4200*50, 600, 0, 3));
        rm_->Add(d, new TH2F(("EoverPvsTimePreGainCorrXtal_"+std::to_string(xtal)).c_str(), ";Calo cluster time [ns];Calo energy / track momentum", 50, 0, 4200*50, 600, 0, 3));
      
      }

    }

  }

} // beginJob


void TrackCaloMatchingAna::beginRun(art::Run const & r) {

  //Get coord systems
  cs_ = artg4::dataFromRunOrService<gm2geom::CoordSystemsStoreData, gm2geom::CoordSystemsStore>
  ( r, dataModuleDefs::coordSysModuleLabel(), dataModuleDefs::coordSysInstanceLabel() );
  if ( cs_.size() == 0 ) {
    mf::LogWarning("TrackCaloMatchingAna") << "This run does not contain any data associated with the coordinate system\n";
  }
}//beginRun


void TrackCaloMatchingAna::analyze(const art::Event& event) {

  auto topDir = rm_->GetDir(dirName_);

  //
  // Get forward extrapolated vertices (intersection with calo face)
  // 
  gm2strawtracker::DecayVertexArtRecordCollection vertices;
  art::Handle<gm2strawtracker::DecayVertexArtRecordCollection> vertexDataHandle;
  bool foundVertex = event.getByLabel(vertexModuleLabel_, vertexInstanceLabel_, vertexDataHandle);
  if ( ! foundVertex ) {
    throw cet::exception("TrackCaloMatching") << "No track vertices in this event (\"" << vertexModuleLabel_ << "\":\"" << vertexInstanceLabel_ << "\")\n";
  }
  vertices = *vertexDataHandle;

  //
  // Use association to grab calo cluster associated with our vertex
  //
  art::FindManyP<gm2calo::ClusterArtRecord> matchedHits(vertexDataHandle, event, art::InputTag(matchedModuleLabel_, matchedInstanceLabel_));

  //
  // Start looping over forwards vertices
  //
  for (unsigned int i_vertex = 0; i_vertex < (*vertexDataHandle).size(); i_vertex++) {

    // Get corresponding vertex
    auto vertex = vertices.at(i_vertex);

    // Track level quality cuts 
    if (applyTrackQuality_ && !trackQuality_->goodTrack(vertex.track)) continue;

    // Get name of sub-directory
    std::string subDir = Form("Station[%d]",vertex.island->station);
    auto statDir = rm_->GetDir(topDir,subDir.c_str(),false);

    // Transfer clusters to vector from Art::Assns
    std::vector<art::Ptr<gm2calo::ClusterArtRecord> > clusters;
    // std::vector<unsigned int const*> clusterIDs; //cluster matched within vector of clusters
    matchedHits.get(i_vertex, clusters); // vector of clusters matched with a vertex @ i_vertex 

    // Fill number of matches
    rm_->Get<TH1*>(topDir, "MatchesPerTrack")->Fill(clusters.size());
    rm_->Get<TH1*>(statDir, "MatchesPerTrack")->Fill(clusters.size());

    // Track position at calorimeter
    gm2geom::CoordSystem3Vector vertexPos = vertex.position.transform(cs_, Form("CalorimeterNumber[%d]",vertex.island->station));
    rm_->Get<TH2*>(topDir, "TrackPositionAll")->Fill(vertexPos.x(), vertexPos.y());
    rm_->Get<TH2*>(statDir, "TrackPositionAll")->Fill(vertexPos.x(), vertexPos.y());

    if (clusters.size() == 0) {

      rm_->Get<TH2*>(topDir, "TrackPositionNoCluster")->Fill(vertexPos.x(), vertexPos.y());
      rm_->Get<TH2*>(statDir, "TrackPositionNoCluster")->Fill(vertexPos.x(), vertexPos.y());

    // Look for case with one track and one cluster
    } else if (clusters.size() == 1) {

      // Get calo cluster
      art::Ptr <gm2calo::ClusterArtRecord> thisCluster = clusters.at(0);
      gm2calo::ClusterArtRecord cluster = *thisCluster;

       // Vertex level quality cuts
      if (applyCaloVertexQuality_ && !trackQuality_->goodCaloVertex(vertex,cluster)) continue;
      if (applyPositronVertexQuality_ && !trackQuality_->goodPositronVertex(vertex,cluster)) continue;
      if (applyLostMuonVertexQuality_ && !trackQuality_->goodLostMuonVertex(vertex,cluster)) continue;
      
      // Get radial difference
      caloGeomUtils_.loadConstants(cluster);
      double caloX = caloGeomUtils_.getCaloX(cluster);
      double caloY = caloGeomUtils_.getCaloY(cluster);
      double dX = caloX - vertexPos.x();
      double dY = caloY - vertexPos.y();
      double dR = sqrt(dX*dX + dY*dY);

      // Get calo time
      double caloTime = cluster.time*1.25; // Convert from clock ticks to ns

      // Get calo energy before in-Fill and STDP Gain Corrections
      double uncorrEnergy = 0;
      double energyCalibFactor = 0;
      double lastEnergy = 0;

      for(unsigned int iHit = 0; iHit < cluster.crystalHits.size(); iHit++) {

        auto crystalHit = cluster.crystalHits[iHit];

        // Loop back through module chain that made this hit (with art::Ptr uncalibratedHit)
        bool lastModuleIFG = false;
        bool lastModuleEnergyCal = false;

        while (crystalHit) {
          art::Handle<gm2calo::CrystalHitArtRecordCollection> hitHandle;
          event.get(crystalHit.id(), hitHandle);
           // std::cout << "hit produced by " << hitHandle.provenance()->moduleLabel() << ": (E, t) = (" << crystalHit->energy << ", " << crystalHit->time << ")" << std::endl;                                              
           // If last module was in fill gain module, then this one contains the uncorrected energy
          if(lastModuleIFG) {
            uncorrEnergy += crystalHit->energy/energyCalibFactor;
            break;
          }

          // If last module was energy calibrator then we can calculate the ADC-to-energy factor (which is linear and can be applied before/after the STDP)
          if(lastModuleEnergyCal) {
            energyCalibFactor = crystalHit->energy / lastEnergy;
            lastModuleEnergyCal = false;
          }

          // Check whether this module is the preGainCorrModule
          if(hitHandle.provenance()->moduleLabel() == preGainCorrModule_) lastModuleIFG = true;

          // Check whether this module is the ADC-to-energy module
          if(hitHandle.provenance()->moduleLabel() == energyCalibModule_) lastModuleEnergyCal = true;

          // Grab next hit back in calibration chain
          lastEnergy = crystalHit->energy;
          crystalHit = crystalHit->uncalibratedHit;
        }

        if(perXtal_) {    
        // // Get corresponding vertex
          const int xtalNum = cluster.crystalHits[iHit]->xtalNum;

          for(auto d : {topDir, statDir}){ // Dir

            rm_->Get<TH1*>(d, ("EoverPvsTimeXtal_"+std::to_string(xtalNum)).c_str())->Fill(caloTime, cluster.energy/vertex.track->momentum.mag());

            rm_->Get<TH1*>(d, ("EoverPvsTimePreGainCorrXtal_"+std::to_string(xtalNum)).c_str())->Fill(caloTime, uncorrEnergy/vertex.track->momentum.mag());

          } // dir
        } // if xtal
      } // iHit 

    for(auto d : {topDir, statDir}){

     rm_->Get<TH1*>(d, "CaloTime")->Fill(caloTime);
     rm_->Get<TH1*>(d, "TimeDiff")->Fill(caloTime - vertex.time);
     rm_->Get<TH1*>(d, "TimeDiffAll")->Fill(caloTime - vertex.time);
     rm_->Get<TH1*>(d, "RadialDiff")->Fill(dR);
     rm_->Get<TH1*>(d, "CaloEnergy")->Fill(cluster.energy);
     rm_->Get<TH1*>(d, "TrackMomentum")->Fill(vertex.track->momentum.mag());
     rm_->Get<TH2*>(d, "EvsP")->Fill(vertex.track->momentum.mag(),cluster.energy);
     rm_->Get<TH1*>(d, "EoverP")->Fill(cluster.energy/vertex.track->momentum.mag());
     rm_->Get<TH1*>(d, "LogEoverP")->Fill(log(cluster.energy/vertex.track->momentum.mag()));
     rm_->Get<TH1*>(d, "EoverPvsTime")->Fill(caloTime, cluster.energy/vertex.track->momentum.mag());
     rm_->Get<TH1*>(d, "EoverPvsTimePreGainCorr")->Fill(caloTime, uncorrEnergy/vertex.track->momentum.mag());

     // Individual straws (looking to understand odd t0 behaviour)
     for(auto & dcaDigit : vertex.track->strawDCADigits){
       rm_->Get<TH2*>(d, "StrawDriftTime")->Fill(dcaDigit->digit->calTime - caloTime, sgeom_->geom().getGlobalLayer(dcaDigit->digit->wireID));
     }

      // If you want to do something with this position relative to the clusters
     rm_->Get<TH2*>(d, "TrackPositionCluster")->Fill(vertexPos.x(), vertexPos.y());

    }

  } else {

      // Put something here when there's more than one cluster for a given track
      //      mf::LogWarning("priority") << "WARNING: TrackCaloMatchingAna " << event.id() << " : Vertex " << i_vertex << " has " << clusters.size() << " matched clusters. Skipping...\n";

      // Fill all time difference plot - helps locate peak if some of the timings have changed
      for (auto thisCluster : clusters){
        gm2calo::ClusterArtRecord cluster = *thisCluster;

        // Get corresponding vertex
        auto vertex = vertices.at(i_vertex);

        // Fill some plots
        double caloTime = cluster.time*1.25; // Convert from clock ticks to ns
        rm_->Get<TH1*>(topDir, "TimeDiffAll")->Fill(caloTime - vertex.time);
        rm_->Get<TH1*>(statDir, "TimeDiffAll")->Fill(caloTime - vertex.time);
      }

       rm_->Get<TH2*>(topDir, "TrackPositionCluster")->Fill(vertexPos.x(), vertexPos.y());
       rm_->Get<TH2*>(statDir, "TrackPositionCluster")->Fill(vertexPos.x(), vertexPos.y());
    }

  }
   
} //analyze

void TrackCaloMatchingAna::endJob() {

  // Calculate efficiency/inefficiency
  std::vector<TDirectory*> plotDirs;
  plotDirs.push_back(rm_->GetDir(dirName_));
  for (auto d : dirs_) plotDirs.push_back(d);

  for(auto d : plotDirs){

    TH2* hEfficNumer = rm_->Get<TH2*>(d, "TrackPositionCluster");
    TH2* hInefficNumer = rm_->Get<TH2*>(d, "TrackPositionNoCluster");
    TH2* hDenom = rm_->Get<TH2*>(d, "TrackPositionAll");
    TH2* hEffic = rm_->Get<TH2*>(d, "CaloEfficiency");
    TH2* hIneffic = rm_->Get<TH2*>(d, "CaloInefficiency");

    for(int bin_y = 1; bin_y <= hEffic->GetNbinsY(); bin_y++){
      for(int bin_x = 1; bin_x <= hEffic->GetNbinsX(); bin_x++){
        double nTracks = hDenom->GetBinContent(bin_x,bin_y);
        if(nTracks > 0){
          hEffic->SetBinContent(bin_x,bin_y,hEfficNumer->GetBinContent(bin_x,bin_y)/nTracks);
          hIneffic->SetBinContent(bin_x,bin_y,hInefficNumer->GetBinContent(bin_x,bin_y)/nTracks);
        }
      } // bin_x
    } // bin_y
  } // plotDirs
} //endJob

DEFINE_ART_MODULE(TrackCaloMatchingAna)
