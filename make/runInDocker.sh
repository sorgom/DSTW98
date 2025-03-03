#!/bin/bash
#   ====================================
#   run DSTW in ubuntu Docker container
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
reportsDir=$(pwd)/reports
report=$reportsDir/valgrind_report.txt
bindir=$buildDir/linux/memleak

mkdir -p $reportsDir
rm -f $report

#   build
cd $myDir
make -j memleak dstw_gen dstw_runtime config=memleak

#   run memleak test
echo "# memleak test" >> $report
valgrind -s --leak-check=full $bindir/memleak X >> $report

#   gen required proj data file
$bindir/dstw_gen
#   start app with valgrind - needs to be stopped with dstw_stop from another terminal
echo "# runtime test" >> $report
valgrind -s --leak-check=full $bindir/dstw_runtime X >> $report
