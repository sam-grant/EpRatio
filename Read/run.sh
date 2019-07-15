#!/bin/bash
for file in `ls ../../ntuples/60hr_5036B_allMuons/gm2*.root`; do
    echo $file
         ./PlotterTimeAllMuons $file
done

hadd allMuons.root plots*.root
mv *.root /RootFiles
