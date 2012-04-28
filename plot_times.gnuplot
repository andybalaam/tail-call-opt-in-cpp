
plot \
    "times-hardware.txt"  smooth csplines title column(2) with lines linewidth 4, \
    "times-loop.txt"      smooth csplines title column(2) with lines linewidth 4, \
    "times-recursive.txt" smooth csplines title column(2) with lines linewidth 4, \
    "times-tail_call.txt" smooth csplines title column(2) with lines linewidth 4

