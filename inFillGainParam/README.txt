Logic
-------

Time distributions come out of ../makePlots2/fits_time_normalised_xtal.root, these are fitted by gainFitter_xtal.cc and quality cuts are applied: 

Quality cuts:

      if(4 < chiSqrNDF || chiSqrNDF <  0.25) continue;
      if (N < 100000) continue;

These cuts reduce number of crystals from 94 to 32.

Results go to taus_time_normalised_xtal_Q.root or "*noQ.root"

Then, we extract the parameters and dump them into a ROOT file via: inFillGainParams_laser_xtal.cc and *sam_xtal.cc.

From here, we can draw scatter plots, get the statistical pull in 1 and 2D (as in xtal num on x), the fluctuation. C code names should be self explanatory. 
