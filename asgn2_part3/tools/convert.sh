mkdir jpg
for f in `ls *.ppm`
do
newname="${f%.*}"
echo $newname
convert $f -quality 99 jpg/$newname'.jpg'
done;
