inputDir="MainPlots" #CutParamPlots" # "MainPlots" #
files=""
for i in {15921..15991}; do 
#for i in {16113..16234}; do 
#for i in {16355..16514}; do 
#for i in {17065..17527}; do 
#for i in {15921..17527}; do 

    file=${inputDir}/plots_Run1_${i}.root
    if [ ! -f "${file}" ]; then
	continue
    fi
    files=$files" "$file #{inputDir}/plots_Run1_${i}.root
done
echo $files
#hadd -f trackCaloMatchingPlots_60h.root $filse
#hadd -f cutParamPlots_60h.root $files#
#hadd -f cutParamPlots_HK.root $files
#hadd -f cutParamPlots_9d.root $files
hadd -f trackCaloMatchingPlots_60h.root $files
#
#    echo ${inputDir}/plots_Run1_${i}.root
#done

 #   echo ${inputDir}/plots_Run1_${i}.root
#done

  #  echo ${inputDir}/plots_Run1_${i}.root
#done