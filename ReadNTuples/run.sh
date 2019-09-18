for file in `ls ../../Ntuples/60hr_5036B_allMuons/gm2rootTrees_allMuons*.root`; do
#gm2liv:/mnt/strawRaid01/omegaEU/9day_5040A/gm2skim*.root`; do
    echo $file
        ./PlotterTimeXtal $file
done
hadd RootFiles/RawTimeXtalFid.root plots*.root
