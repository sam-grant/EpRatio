
#!/bin/bash
for file in `ls ../../ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons_159*.root`; do
    echo $file
    #    ./PlotterEpXtal $file
    #    ./PlotterEpXtalFid $file
    #    ./PlotterTimeXtal $file
        ./PlotterTimeBreakout $file
    #    ./PlotterCuts $file
done

#hadd RootFiles/TimeXtalLong.root plots*.root
#hadd RootFiles/EpXtal.root plots*.root
#hadd RootFiles/TimeBreakoutLong.root plots*.root
#hadd -f RootFiles/trkPositron.root plots*.root
#hadd -f RootFiles/RawEpXtalFid.root
hadd -f RootFiles/RawTimeBreakout.root
