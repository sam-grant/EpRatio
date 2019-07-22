#!/bin/bash
for file in `ls ../../ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons_159*.root`; do
    echo $file
    #    ./PlotterEpXtal $file
    ./PlotterTimeXtal $file
done

hadd RootFiles/timeXtal.root plots*.root


