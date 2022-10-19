inputDir="MainPlots" #CutParamPlots" # "MainPlots" #
files=""

for i in {25044..24685}; do 
   
    files=${inputDir}/plots_run2C_${i}.*.root
    echo "Hadding files "$files
    hadd -f trackCaloMatchingPlots_run2C.${i}.root $files
    wait
done

echo "Performing final hadd"

hadd -f trackCaloMatchingPlots_run2C.root trackCaloMatchingPlots_run2C.*.root
#echo $files
#
#hadd -f cutParamPlots_60h.root $files#
#hadd -f cutParamPlots_HK.root $files
#hadd -f cutParamPlots_9d.root $files
#hadd -f trackCaloMatchingPlots_60h.root $files
#
#    echo ${inputDir}/plots_Run1_${i}.root
#done

 #   echo ${inputDir}/plots_Run1_${i}.root
#done

  #  echo ${inputDir}/plots_Run1_${i}.root
#done