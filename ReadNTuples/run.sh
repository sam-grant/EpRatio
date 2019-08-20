for file in `ls gm2liv:/mnt/strawRaid01/omegaEU/9day_5040A/gm2skim*.root`; do
    echo $file
        ./PlotterTimeBreakout $file
done
hadd RootFiles/RawTimeBreakout9day.root
