for item in *
do
if [ -f $item ]; then
		ls -l $item
		file $item
	else
		echo $item is not a regular file.
	fi
done
