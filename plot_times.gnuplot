
plot \
    "times-hardware.txt"  smooth unique title column(2) with lines linewidth 4, \
    "times-loop.txt"      smooth unique title column(2) with lines linewidth 4, \
    "times-recursive.txt" smooth unique title column(2) with lines linewidth 4, \
    "times-tail_call.txt" smooth unique title column(2) with lines linewidth 4

