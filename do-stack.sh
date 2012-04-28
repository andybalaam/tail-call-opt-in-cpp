#!/bin/bash

METHOD=$1

NUM=100000

echo -e stack\\t$METHOD

rm -f massif.txt

set -x

valgrind \
    --tool=massif \
    --stacks=yes \
    --heap=no \
    --time-unit=ms \
    --massif-out-file=massif.txt \
    ./times_two $METHOD $NUM 2> /dev/null

set +x

egrep "^(mem_stacks_B=|time=)" massif.txt | cut -d= -f2 | python two2one.py
#less massif.txt
rm massif.txt

