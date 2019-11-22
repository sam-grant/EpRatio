for file in `ls /mnt/strawRaid01/omegaEU/9day_5040A/gm2skim_ana_*.root`; do

    echo $file
#    ./PlotterEpXtalFid_9day $file
#    ./PlotterTimeXtal_9day $file
#    ./PlotterTimeXtalCorr_9day $file
    ./PlotterTimeCalo_9day $file
done

#hadd ../ROOT/RawEpMeansFid_9day.root plots*.root
#hadd ../ROOT/RawTimeXtalFid_9day.root plots*.root
#hadd ../ROOT/RawTimeXtalFidCorr_9day.root plots*.root
hadd ../ROOT/RawTimeCalo_9day.root plots*.root