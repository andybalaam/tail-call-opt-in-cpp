#!/usr/bin/env python

# Take every pair of input lines and make them one line separated by a space

import sys

inf = sys.stdin

while True:
    l1 = inf.readline().strip()
    if l1 == "":
        break;
    l2 = inf.readline().strip()
    if l2 == "":
        raise Exception( "missing pair!" )
    print l1, l2
    #break

