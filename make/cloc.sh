#!/bin/bash
md=CLOC.md

sub()
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
sub specification >> $md
sub application >> $md
sub testing >> $md
