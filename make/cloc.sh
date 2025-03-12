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
    exts=$2
    if [ -z $exts ]; then exts=cpp,h; fi
    str=$(cloc $1 --md --include-ext=$exts | grep -v '^---')
    echo "Language${str#*Language}"
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
