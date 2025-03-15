#!/bin/bash
#   ====================================
#   build and run all tests and app
#   ====================================
cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
bindir=$buildDir/linux/ci

cd $myDir
make -j config=ci

cd $buildDir
tot=0
for bin in $(ls $bindir/* | grep -v systemtests); do
echo ==== $(basename $bin)
$bin
ret=$?
echo return: $ret
tot=$((tot+ret))
done
if [ $tot -eq 0 ]; then echo OK; fi
exit $tot
