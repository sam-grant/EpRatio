#!/bin/bash
for file in `ls ../../60hr_v9_17_01/gm2*.root`; do
    echo $file
     ./plotter_example $file
done

hadd example.root plots*.root
