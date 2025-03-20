#!/bin/bash
#   ====================================
#   run DSTW in ubuntu Docker container
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
cd ..
repo=$(pwd)
makeDir=$repo/make
buildDir=$repo/build
#   straight build
ciDir=$buildDir/linux/ci
#   mem leak build
mlDir=$buildDir/linux/memleak
report=$repo/testing/valgrind_report.md

out() { echo $* | tee -a $report; }
#   start / end markdown code block
quote() { echo "\`\`\`" >> $report; }

heading() { out; out "## TEST: $1"; }

valgrind_opts="-s --leak-check=full --log-fd=1 --default-suppressions=no"

#   run valgrind with sed to avoid git diff due to PID output
run() { valgrind $valgrind_opts $* | sed s/^==[0-9]*==/======/ | tee -a $report; }

#   build (with no report)
cd $makeDir
#   build app
make -j dstw_gen dstw_runtime dstw_stop systemtests config=debug
if [ $? -ne 0 ]; then
    echo "build app failed"
    exit 1
fi
#   build memleak
make -j memleak config=memleak
if [ $? -ne 0 ]; then
    echo "build memleak failed"
    exit 1
fi

echo "# valgrind report" | tee $report
out $(date +%F)

heading "memory leaked app"
quote
run $mlDir/memleak
quote

#   gen required proj data file
$ciDir/dstw_gen

heading "runtime no action"
quote
run $ciDir/dstw_runtime
quote

heading "runtime read"
quote
run $ciDir/dstw_runtime X
quote

heading "runtime read, run, stop"
quote
run $ciDir/dstw_runtime X X & pid=$!
sleep 1

$ciDir/dstw_stop
wait $pid;
quote
sleep 2

heading "runtime read, run, system tests, stop"
quote
run $ciDir/dstw_runtime X X & pid=$!
sleep 2
$ciDir/systemtests -b -v 2>&1 | tee -a $report
$ciDir/dstw_stop
wait $pid;
quote
