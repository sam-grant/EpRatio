#ifndef CANVAS_h
#define CANVAS_h
#include <iostream>
#include "TH2D.h"

using std::string; 

void canvas(TH2D *hist, int iteration, double loLim, double hiLim, string fileName, string title); 

#endif

