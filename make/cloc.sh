#!/bin/bash
#   =========================================
#   count C++ lines of code
#   - with cloc tool
#   - mark down format
#   - without cloc tool headings
#   - without cloc tool separator lines (---)
#   =========================================
clc()
{
    echo
    echo "## $(basename $1)"
    out=0
    cloc $1 --md --include-ext=cpp,h | grep -v '^---' | while read i; do
        [[ "$i" =~ ^Language ]] && out=1
        [[ $out -eq 1 ]] && echo "$i"
    done
}
cd $(dirname $0)
cd ..
md=CLOC.md
echo "# CLOC" > $md
date +'%Y-%m-%d' >> $md
clc specification >> $md
clc application >> $md
clc testing >> $md

cat $md
