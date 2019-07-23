#!/bin/bash
for file in `ls ../../ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons_159*.root`; do
    echo $file
    #    ./PlotterEpXtal $file
    #    ./PlotterTimeXtal $file
    ./PlotterTimeBreakout $file
done

#hadd RootFiles/TimeXtalLong.root plots*.root
#hadd RootFiles/EpXtal.root plots*.root
hadd RootFiles/TimeBreakoutLong.root plots*.root

