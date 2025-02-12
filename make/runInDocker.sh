#!/bin/bash
#   ====================================
#   run DSTW in ubuntu Docker container
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
bindir=linux/docker

cd $myDir
make -j dstw_gen dstw_runtime config=docker

cd $buildDir
#   gen required proj data file
$bindir/dstw_gen $projfile
#   start app with valgrind
valgrind --leak-check=full $bindir/dstw_runtime X
