for file in `ls /mnt/strawRaid01/omegaEU/9day_5040A/gm2skim_ana_*.root`; do

    echo $file
    ./PlotterEpXtalFid_9day $file

done

hadd ../ROOT/RawEpMeansFid_9day.root