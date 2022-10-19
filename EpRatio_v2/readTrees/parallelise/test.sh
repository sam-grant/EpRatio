# Label piped input file
inFile=$1

echo "Running files in ${1}"

# cd ../

files=""
for line in `cat $1`; do

	# subRun=${line%.*}
 #  	subRun=${subRun##*_}
#  	echo "Running subRun $subRun"
#	echo $line

	files=$files" "$line
	#./PlotterCutParams $line
	# wait
	# mv plots_*_${subRun}.root parallelise/${output}

done

echo $files

# cd parallelise
