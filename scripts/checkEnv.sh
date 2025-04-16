#!/bin/bash
#   ====================================
#   check for availability of tools
#   ====================================

for call in python python3 py gcov cppcheck valgrind; do
    printf "%-12s : %s\n" $call $(which $call)
done
echo
for call in python python3; do
    if [ ! -z $(which $call) ]; then
        printf "%-12s : " $call
        echo $($call --version)
    fi
done
