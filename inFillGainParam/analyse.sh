make
echo "#########################################################"
echo "Running gainFitter_xtal.exe"
./gainFitter_xtal.exe
echo "#########################################################"
echo "Running inFillGainParams_laser_xtal.exe"
./inFillGainParams_laser_xtal.exe
echo "#########################################################"
echo "Running inFillGainParams_Ep_xtal.exe"
./inFillGainParameters_Ep_xtal.exe
echo "#########################################################"
echo "Running scatter_plots.exe"
./scatter_plots.exe
echo "#########################################################"
echo "Running fluc_1D.exe"
./fluc_1D.exe
echo "#########################################################"
echo "Running stat_pull.exe"
./stat_pull.exe

