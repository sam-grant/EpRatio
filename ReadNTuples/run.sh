#for file in `ls ../../Ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons*.root`; do
for file in `ls /mnt/strawRaid01/omegaEU/9day_5040A/gm2skim_ana_*.root`; do
#gm2liv:/mnt/strawRaid01/omegaEU/9day_5040A/gm2skim*.root`; do
    echo $file
#    ./PlotterEpXtal_9day $file
#    ./PlotterTimeBreakout_9day $file
    ./PlotterTimeXtal_9day $file
done

hadd -f RootFiles/RawTimeXtal_9day.root plots*.root