# Make output for specific job (so we can do more than one at a time)
output="MainPlots" # "CutParamPlots"

# Label piped input file
inFile=$1

echo "Running files in ${1}"

cd ../

files=""

for line in `cat parallelise/${1}`; do

	files=$files" "$line
done

echo $files

#./PlotterCutParams $files
./Plotter $files

wait

echo "Job finished: transferring files"

# for line in `cat parallelise/${1}`; do

#    	subRun=${file##*_}
#     subRun=${subRun%*.root}
# 	# wait
# 	mv plots_run2C_${subRun}.root parallelise/${output}

# done

cd parallelise
