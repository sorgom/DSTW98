#!/bin/bash
#   ====================================
#   run coverage using gcov
#   ====================================
cd $(dirname $0)
cd ..
repo=$(pwd)
appDir=$repo/application/components
makeDir=$repo/make
buildDir=$repo/build
objDir=linux/obj/debug/gcovapp
binDir=$buildDir/linux/debug

if [ $1 = "-c" ]; then make -s -C $makeDir -j config=debug clean; fi
make -s -C $makeDir -j config=debug gcovapp gcovtests

cd $buildDir
rm -f *.gcov
$binDir/gcovtests
gcov -o $objDir $appDir/*/src/*.cpp > /dev/null 2> /dev/null

out () { printf "%-25s: %4d\n" $1 $2; }

files=$(ls *.cpp.gcov 2> /dev/null)
if test -z "$files"; then
    echo "no coverage data found"
    exit 0
fi

echo uncovered LOC:
tot=0
for cf in $files; do
    nuc=$(grep -c '#####:' $cf)
    tot=$((tot+nuc))
    out ${cf%.*} $nuc
done
echo
if test $tot -ne 0; then
    out TOTAL $tot
else echo OK
fi
out files $(echo $files | wc -w)
rm *.gcov
exit $tot
