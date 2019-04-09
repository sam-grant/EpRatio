#!/bin/bash

#for file in `ls /unix/muons/g-2/omegaEU/60h_5036B/gm2*.root`; do
for file in `ls /unix/muons/g-2/omegaEU/v9_17_01_new/gm2*.root`; do
    echo $file
    # ignore truncated file 
    #[[ $file == *30.root ]] && continue ; 

    ./plotter_uncorrected_quality_new $file

done

hadd merged_uncorrected_new_D.root plots*.root
