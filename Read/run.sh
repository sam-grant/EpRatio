#!/bin/bash
for file in `ls ../../ntuples/60hr_5036B_allMuons/gm2*.root`; do
    echo $file
         ./PlotterTimeXtal $file
done

hadd RootFiles/timeXtal.root plots*.root


