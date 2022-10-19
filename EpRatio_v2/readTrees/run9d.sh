#!/bin/bash

for file in `ls /gm2/data/g2be/Production/TrackAndTrackCaloTrees/Run1/9d/trackAndTrackCaloTrees_*.root`; do
    echo $file
    ./Plotter $file
done

hadd -f ../plots/9d/trackAndTrackCaloPlots_9d.root plots_9d_*.root
