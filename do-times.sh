#!/bin/bash

METHOD=$1

NUMS="20000000 100000 1000000 10000000  20000000 21000000 22000000 23000000"

for NUM in $NUMS ; do
{
    echo -e -n $NUM\\t
    /usr/bin/time -f "%e" ./times_two $METHOD $NUM 2>&1
}; done

