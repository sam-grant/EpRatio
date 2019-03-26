#!/bin/bash

for file in `ls /unix/muons/g-2/omegaEU/60h_5036B/gm2*.root`; do

    echo $file
    # ignore truncated file 
    #[[ $file == *30.root ]] && continue ; 

    ./plotter_uncorrected $file

done

hadd merged_uncorrected2.root plots*.root
