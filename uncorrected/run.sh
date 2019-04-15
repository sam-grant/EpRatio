#!/bin/bash

#for file in `ls /unix/muons/g-2/omegaEU/60h_5036B/gm2*.root`; do
for file in `ls /unix/muons/g-2/omegaEU/v9_17_01_new/gm2*.root`; do
    echo $file
   # ./plotter_scale_factor2
    # ignore truncated file 
    #[[ $file == *30.root ]] && continue ; 
   #  ./plotter_crystals_clean $file
     ./plotter_uncorrected_quality_new $file
     #./plotter_scale_factor $file
    # ./plotter_enery $file
done

hadd xtal2.root plots*.root
