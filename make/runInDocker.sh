#!/bin/bash
#   ====================================
#   run DSTW in Docker container (ubuntu)
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
bindir=linux/docker
projfile=dstw.proj

cd $myDir
make -j dstw_gen dstw_runtime config=docker

cd $buildDir
#   gen required proj data file
$bindir/dstw_gen $projfile
#   start app with valgrind
valgrind $bindir/dstw_runtime $projfile
