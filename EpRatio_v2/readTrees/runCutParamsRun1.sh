#!/bin/bash

for file in `ls /gm2/data/g2be/Production/Trees/Run1/trackRecotrees_*.root`; do
    echo $file
    ./PlotterCutParams $file
done

# hadd -f ../plots/9d/trackAndTrackCaloPlots_9d.root plots_9d_*.root
