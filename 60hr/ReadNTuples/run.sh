#for file in `ls ../../Ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons*.root`; do
for file in `ls /mnt/strawRaid01/omegaEU/60hr_v9_17_01/gm2*.root`; do

    echo $file
    ./PlotterTimeXtal_60hr $file
#    ./PlotterEpXtalFid_60hr $file

#    ./PlotterTimeBreakout_9day $file
#    ./PlotterDemoPlots_9day $file
#    ./PlotterVertRadTracker_9day $file
#    ./PlotterVertRadAllMuons_9day $file
done

#hadd ../ROOT/RawEpXtalFid_60hr.root plots*.root
hadd ../ROOT/RawTimeXtalFid_60hr.root plots*.root

