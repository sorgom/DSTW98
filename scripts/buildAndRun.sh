#!/bin/bash
#   ====================================
#   build and run all tests and app
#   ====================================
cd $(dirname $0)
cd ..
buildDir=$(pwd)/build
makeDir=$(pwd)/make
binDir=$buildDir/linux/ci

cd $makeDir
make -j config=ci

cd $buildDir
tot=0
for bin in $(ls $binDir/* | grep -v systemtests); do
echo ==== $(basename $bin)
$bin
ret=$?
echo return: $ret
tot=$((tot+ret))
done
if [ $tot -eq 0 ]; then echo OK; fi
exit $tot
