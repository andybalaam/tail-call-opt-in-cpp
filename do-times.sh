#!/bin/bash

METHOD=$1

for NUM in 100000 1000000 10000000 20000000 30000000; do
{
    time -f "%E" ./times_two $METHOD $NUM > times-$METHOD.txt
}; done

