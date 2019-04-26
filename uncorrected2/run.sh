#!/bin/bash
#ssh sgrant@plus1.hep.ucl.ac.uk
#for file in `ls /unix/muons/g-2/omegaEU/60h_5036B/gm2*.root`; do
for file in `ls ../../60hr_v9_17_01/gm2*.root`; do
    echo $file
   # ./plotter_uncorrected_crystals $file
 #   ./plotter_uncorrected_quality_new $file
   # ./plotter_time_normalised $file
    ./plotter_Ep_xtal_check $file
done

hadd Ep_xtal_check.root plots*.root
