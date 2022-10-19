# Make list of all files
echo "Creating MainFileList.txt"
rm -rf MainFileList.txt && touch MainFileList.txt
for file in `ls /gm2/data/g2be/Production/TrackQualityTrees/run2C/*.root`; do
   	subRun=${file##*_}
    subRun=${subRun%*.root}
    echo $subRun

	if [ ! -f MainPlots/plots_run2C_${subRun}.root ]; then
  	echo $file >> MainFileList.txt
	fi
done

# Split in blocks of 15 
echo "Splitting MainFileList.txt"
rm -f SplitFileList*
split MainFileList.txt -l 15 -a 3 -d SplitFileList

for list in `ls SplitFileList*`; do
	echo $list
done | xargs -i --max-procs=3 bash -c ". RunJob.sh {}"