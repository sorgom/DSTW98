#!/bin/bash
#   =============================================
#   build everything
#   run all binaries except system tests
#   =============================================
cd $(dirname $0)
cd ..
if [ $1 = "-c" ]; then make -s -C make clean config=release; fi
make -s -C make -j config=release

tot=0
for bin in $(ls build/linux/release/* | grep -v systemtests); do
echo ==== $(basename $bin)
$bin
ret=$?
echo return: $ret
tot=$((tot+ret))
done
if [ $tot -eq 0 ]; then echo OK; fi
exit $tot
