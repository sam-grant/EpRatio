#!/bin/bash

for file in `ls /gm2/data/g2be/Production/TrackAndTrackCaloTrees/Run1/60h/trackAndTrackCaloTrees_*.root`; do
    echo $file
    ./Plotter $file
done

hadd -f ../plots/60h/trackAndTrackCaloPlots_60h.root plots_60h_*.root
