#!/bin/bash

for file in `ls /gm2/data/g2be/Production/TrackAndTrackCaloTrees/Run1/EG/trackAndTrackCaloTrees_*.root`; do
    echo $file
    ./Plotter $file
done

hadd -f ../plots/EG/trackAndTrackCaloPlots_EG.root plots_EG_*.root
