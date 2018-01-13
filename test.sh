#!/bin/bash

output=`./debruijn.exe input/small.fa -k=4 --orginalPrint`
orginal=`cat test/orginal/small_4.out`

if [ "$output" = "$orginal" ]; then
	echo "Izlaz je dobar"
else
	echo "Izlaz nije dobar"
fi
