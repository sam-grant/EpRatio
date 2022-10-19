#!/bin/bash

for file in `ls /gm2/data/g2be/Production/TrackQualityTrees/run2C/*.root`; do
    echo $file
    ./Plotter $file
done

#hadd -f ../plots/60h/trackAndTrackCaloPlots_60h.root plots_60h_*.root
