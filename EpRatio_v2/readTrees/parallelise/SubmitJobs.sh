# Make list of all files
echo "Creating MainFileList.txt"
rm -rf MainFileList.txt && touch MainFileList.txt
for file in `ls /gm2/data/g2be/Production/Trees/Run1/*.root`; do
	echo $file >> MainFileList.txt
done
# Split in blocks of 15 
echo "Splitting MainFileList.txt"
rm -f SplitFileList*
split MainFileList.txt -l 15 -a 3 -d SplitFileList
for file in `ls SplitFileList*`; do 
  mv $file ${file}.txt
done

for file in `ls SplitFileList*`; do
	echo $file 
done | xargs -i --max-procs=3 bash -c ". RunJob.sh {}"