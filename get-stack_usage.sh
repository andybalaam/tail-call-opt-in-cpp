#!/bin/bash

METHOD=$1
OUTFILE=$2

valgrind --tool=massif --stacks=yes --heap=no --massif-out-file=massif.txt ./times_two $METHOD 100000
grep mem_stacks_B massif.txt | cut -d= -f2 > $OUTFILE
rm massif.txt

