#!/bin/bash

echo "Testing against the original..."
originalPass=true

output=`./debruijn.exe input/small.fa -k=3 --originalPrint`
againstFile="test/orginal/small_3.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/small.fa -k=4 --originalPrint`
againstFile="test/orginal/small_4.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/small.fa -k=8 --originalPrint`
againstFile="test/orginal/small_8.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/medium.fa -k=4 --originalPrint`
againstFile="test/orginal/medium_4.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/medium.fa -k=10 --originalPrint`
againstFile="test/orginal/medium_10.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/medium.fa -k=100 --originalPrint`
againstFile="test/orginal/medium_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/medium.fa -k=1000 --originalPrint`
againstFile="test/orginal/medium_1000.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/large.fa -k=100 --originalPrint`
againstFile="test/orginal/large_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/large.fa -k=1000 --originalPrint`
againstFile="test/orginal/large_1000.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_100.fa -k=4 --originalPrint`
againstFile="test/orginal/gen/rand_100_4.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_100.fa -k=8 --originalPrint`
againstFile="test/orginal/gen/rand_100_8.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000.fa -k=4 --originalPrint`
againstFile="test/orginal/gen/rand_1000_4.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000.fa -k=8 --originalPrint`
againstFile="test/orginal/gen/rand_1000_8.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000.fa -k=10 --originalPrint`
againstFile="test/orginal/gen/rand_1000_10.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_10000.fa -k=10 --originalPrint`
againstFile="test/orginal/gen/rand_10000_10.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_10000.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_10000_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_100000.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_100000_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_1.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_1_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_2.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_2_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_3.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_3_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_4.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_4_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_5.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_5_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi

output=`./debruijn.exe input/gen/rand_1000000_6.fa -k=100 --originalPrint`
againstFile="test/orginal/gen/rand_1000000_6_100.out"
orginal=`cat $againstFile`

if [ "$output" = "$orginal" ]; then
	echo $againstFile "OK"
else
	echo $againstFile "NOT OK!!!!!!!!"
	let originalPass=false
fi