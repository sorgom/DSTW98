#!/bin/bash
#   ====================================
#   run DSTW in Docker container (ubuntu)
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
bindir=linux/bin
projfile=dstw.proj

cd $myDir
make -j dstw_gen dstw_runtime config=ci

cd $buildDir
#   gen required proj data file
$bindir/dstw_gen $projfile
#   start app in background
$bindir/dstw_runtime $projfile
