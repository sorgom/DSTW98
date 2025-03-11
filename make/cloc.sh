#!/bin/bash
#   =========================================
#   count lines of code
#   - with cloc tool
#   - mark down format
#   - without cloc tool headings
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
clc specification >> $md
clc application >> $md
clc testing >> $md
