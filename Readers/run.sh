#!/bin/bash
for file in `ls ../../60hr_v9_17_01/gm2*.root`; do
#for file in `ls ../../60hr_test_tree/gm2*.root`; do    
    echo $file
         ./plotter_time_xtal $file
#       ./plotter_Ep_xtal_check $file
#    ./plotter_demo_plots $file
done

hadd time_xtal.root plots*.root
