#!/bin/bash

METHOD=$1

NUMS="100000 1000000 10000000 20000000 21000000 22000000 23000000 24000000 25000000 26000000"

echo -e iterations\\t$METHOD

# Ensure caches etc. are stable
./times_two $METHOD 20000000 > /dev/null
./times_two $METHOD 20000000 > /dev/null
./times_two $METHOD 20000000 > /dev/null

for NUM in $NUMS ; do
{
    echo -e -n $NUM\\t
    /usr/bin/time -f "%e" ./times_two $METHOD $NUM 2>&1
    echo -e -n $NUM\\t
    /usr/bin/time -f "%e" ./times_two $METHOD $NUM 2>&1
    echo -e -n $NUM\\t
    /usr/bin/time -f "%e" ./times_two $METHOD $NUM 2>&1
}; done

