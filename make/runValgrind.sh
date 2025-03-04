#!/bin/bash
#   ====================================
#   run DSTW in ubuntu Docker container
#   ====================================
#   created by Manfred Sorgo

cd $(dirname $0)
myDir=$(pwd)
cd ..
buildDir=$(pwd)/build
#   straight build
ciDir=$buildDir/linux/ci
#   mem leak build
mlDir=$buildDir/linux/memleak
report=$(pwd)/testing/valgrind_report.md

#   start / end markdown code block
quote() { echo "\`\`\`"; }

heading() { echo; echo "## TEST: $1"; }

#   build (with no report)
cd $myDir
#   build app
make -j dstw_gen dstw_runtime dstw_stop systemtests config=ci
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

#   redirect output to report file
exec 6>&1 7>&2 1<&- 2<&- 1>$report 2>&1

#   start output of file to stdout
tail -f $report >&6 & tid=$!

echo "# valgrind report"
echo $(date +%F)

heading "memory leaked app"
quote
valgrind -s --leak-check=full $mlDir/memleak
quote

#   gen required proj data file
$ciDir/dstw_gen

heading "runtime no action"
quote
valgrind -s --leak-check=full $ciDir/dstw_runtime
quote

heading "runtime read"
quote
valgrind -s --leak-check=full $ciDir/dstw_runtime X
quote

heading "runtime read, run, stop"
quote
valgrind -s --leak-check=full $ciDir/dstw_runtime X X & pid=$!
sleep 1

$ciDir/dstw_stop
wait $pid;
sleep 5
quote

heading "runtime read, run, system tests, stop"
quote
valgrind -s --leak-check=full $ciDir/dstw_runtime X X & pid=$!
sleep 1

$ciDir/systemtests -b -v
$ciDir/dstw_stop
wait $pid;
quote

#   stop output of file to stdout
kill -9 $tid