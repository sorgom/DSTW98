#!/bin/bash
#   ====================================
#   run system tests
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
cd ..
if [ $1 = "-c" ]; then make -s -C make clean config=release; fi
make -s -C make -j dstw_gen dstw_runtime dstw_stop systemtests config=release
if [ $? -ne 0 ]; then exit 1; fi

cd build/linux/release
ret=0

./dstw_stop
sleep 1

#   gen required proj data file
./dstw_gen

#   start app in background
./dstw_runtime X X & pid=$!

#   run tests
sleep 1
./systemtests
ret=$((ret+$?))

#   stop app
./dstw_stop

#   wait for app to finish
if ! wait $pid; then
    ret=$((ret+1))
fi
exit $ret
