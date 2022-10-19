#!/bin/bash

for file in `ls /gm2/data/g2be/Production/TrackAndTrackCaloTrees/Run1/HK_final/trackAndTrackCaloTrees_*.root`; do
    echo $file
    ./Plotter $file
done

hadd -f ../plots/HK/trackAndTrackCaloPlots_HK.root plots_HK_*.root
