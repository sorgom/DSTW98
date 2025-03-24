#!/bin/bash
#   ====================================
#   run system tests
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
cd ..
repo=$(pwd)
buildDir=$repo/build
makeDir=$repo/make
binDir=linux/release

cd $makeDir
make -j dstw_gen dstw_runtime dstw_stop systemtests config=release
if [ $? -ne 0 ]; then exit 1; fi

cd $buildDir
ret=0

$binDir/dstw_stop
sleep 1

#   gen required proj data file
$binDir/dstw_gen

#   start app in background
$binDir/dstw_runtime X X & pid=$!

#   run tests
sleep 1
$binDir/systemtests
ret=$((ret+$?))

#   stop app
$binDir/dstw_stop

#   wait for app to finish
if ! wait $pid; then
    ret=$((ret+1))
fi
exit $ret
