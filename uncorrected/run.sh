#!/bin/bash
#ssh sgrant@plus1.hep.ucl.ac.uk
#for file in `ls /unix/muons/g-2/omegaEU/60h_5036B/gm2*.root`; do
for file in `ls ../../v9_17_01_new/gm2*.root`; do
    echo $file
    ./plotter_uncorrected_crystals $file
 #   ./plotter_uncorrected_quality_new $file
done

hadd t_by_xtal_normalised_brd.root plots*.root
