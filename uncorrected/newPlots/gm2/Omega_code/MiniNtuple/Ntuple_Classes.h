#ifndef Ntuple_Classes_h
#define Ntuple_Classes_h

#include "TObject.h"

class Cluster : public TObject {
 public:
 Cluster(): nHit(0), energy(0), time(0), x(0), y(0) {};
 Cluster(int nH, float e, float t, float ix, float iy) :
  nHit(nH), energy(e), time(t*1.25), x(ix), y(iy) {};
  ~Cluster() {};
  
  int nHit;
  float energy, time, x, y;

  ClassDef(Cluster,2); 
};

class Track : public TObject {
 public:
 Track():
   trackMomentum(0),
   trackMomentumX(0),
   trackMomentumY(0),
   trackMomentumZ(0),
   trackMomentumUnc(0),
   decayVertexPosX(0),
   decayVertexPosY(0),
   decayVertexPosZ(0),
   decayVertexMomX(0),
   decayVertexMomY(0),
   decayVertexMomZ(0),
   decayVertexUncR(0),
   decayVertexUncY(0),
   decayVertexUncPR(0),
   decayVertexUncPY(0),
   caloVertexPosX(0),
   caloVertexPosY(0),
   caloVertexPosZ(0),
   caloVertexMomX(0),
   caloVertexMomY(0),
   caloVertexMomZ(0),
   caloVertexUncX(0),
   caloVertexUncY(0),
     //   caloVertexUncPX(0),
     //   caloVertexUncPY(0),
   trackT0(0),
   time(0),
   decayTime(0),
    hitVolume(0),
   trackPValue(0),
    nHits(0),
     nUHits(0),
     nVHits(0),
   missedLayersFrac(0),
   minDriftTime(0),
   maxDriftTime(0),
   maxResidual(0),
   extrapolatedDistance(0) {};
  ~Track() {};

 Track(float i_trackMomentum,
       float i_trackMomentumX,
       float i_trackMomentumY,
       float i_trackMomentumZ,
       float i_trackMomentumUnc,
       float i_decayVertexPosX,
       float i_decayVertexPosY,
       float i_decayVertexPosZ,
       float i_decayVertexMomX,
       float i_decayVertexMomY,
       float i_decayVertexMomZ,
       float i_decayVertexUncR,
       float i_decayVertexUncY,
       float i_decayVertexUncPR,
       float i_decayVertexUncPY,
       float i_caloVertexPosX,
       float i_caloVertexPosY,
       float i_caloVertexPosZ,
       float i_caloVertexMomX,
       float i_caloVertexMomY,
       float i_caloVertexMomZ,
       float i_caloVertexUncX,
       float i_caloVertexUncY,
       //       float i_caloVertexUncPX,
       //       float i_caloVertexUncPY,
       float i_trackT0,
       float i_time,
       float i_decayTime,
       bool  i_hitVolume,
       float i_trackPValue,
       int   i_nHits,
       int   i_nUHits,
       int   i_nVHits,
       float i_missedLayersFrac,
       float i_minDriftTime,
       float i_maxDriftTime,
       float i_maxResidual,
       float i_extrapolatedDistance):
    trackMomentum(i_trackMomentum),
     trackMomentumX(i_trackMomentumX),
     trackMomentumY(i_trackMomentumY),
     trackMomentumZ(i_trackMomentumZ),
     trackMomentumUnc(i_trackMomentumUnc),
     decayVertexPosX(i_decayVertexPosX),
     decayVertexPosY(i_decayVertexPosY),
     decayVertexPosZ(i_decayVertexPosZ),
     decayVertexMomX(i_decayVertexMomX),
     decayVertexMomY(i_decayVertexMomY),
     decayVertexMomZ(i_decayVertexMomZ),
     decayVertexUncR(i_decayVertexUncR),
     decayVertexUncY(i_decayVertexUncY),
     decayVertexUncPR(i_decayVertexUncPR),
     decayVertexUncPY(i_decayVertexUncPY),
     caloVertexPosX(i_caloVertexPosX),
     caloVertexPosY(i_caloVertexPosY),
     caloVertexPosZ(i_caloVertexPosZ),
     caloVertexMomX(i_caloVertexMomX),
     caloVertexMomY(i_caloVertexMomY),
     caloVertexMomZ(i_caloVertexMomZ),
     caloVertexUncX(i_caloVertexUncX),
     caloVertexUncY(i_caloVertexUncY),
     //   caloVertexUncPX(i_caloVertexUncPX),
     //     caloVertexUncPY(i_caloVertexUncPY),
     trackT0(i_trackT0),
     time(i_time),
     decayTime(i_decayTime),
     hitVolume(i_hitVolume),
     trackPValue(i_trackPValue),
     nHits(i_nHits),
     nUHits(i_nUHits),
     nVHits(i_nVHits),
     missedLayersFrac(i_missedLayersFrac),
     minDriftTime(i_minDriftTime),
     maxDriftTime(i_maxDriftTime),
     maxResidual(i_maxResidual),
     extrapolatedDistance(i_extrapolatedDistance) {};


   //class members:
   float trackMomentum;
  float trackMomentumX;
  float trackMomentumY;
  float trackMomentumZ;
  float trackMomentumUnc;
  float decayVertexPosX;
  float decayVertexPosY;
  float decayVertexPosZ;
  float decayVertexMomX;
  float decayVertexMomY;
  float decayVertexMomZ;
  float decayVertexUncR;
  float decayVertexUncY;
  float decayVertexUncPR;
  float decayVertexUncPY;
  float caloVertexPosX;
  float caloVertexPosY;
  float caloVertexPosZ;
  float caloVertexMomX;
  float caloVertexMomY;
  float caloVertexMomZ;
  float caloVertexUncX;
  float caloVertexUncY;
  // float caloVertexUncPX;
  //float caloVertexUncPY;
  float trackT0;
  float time;
  float decayTime;
  bool  hitVolume;
  float trackPValue;
  int   nHits;
  int   nUHits;
  int   nVHits;
  float missedLayersFrac;
  float minDriftTime;
  float maxDriftTime;
  float maxResidual;
  float extrapolatedDistance;


  ClassDef(Track,2); 
  
};

  
#endif
