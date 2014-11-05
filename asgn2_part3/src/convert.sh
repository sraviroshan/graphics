mkdir jpg
for f in `ls *.ppm`
do
newname="${f%.*}"
convert $f -quality 80% jpg/$newname'.jpg'
done;
