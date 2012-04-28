
set key left top
set xlabel "iterations"
set ylabel "exection time (secs)"
set format x "%.0f"
set xtics 10000000

plot [0:27000000] [0:16] \
    "times-hardware.txt"  title column(2) with lines linewidth 4, \
    "times-loop.txt"      title column(2) with lines linewidth 4, \
    "times-recursive.txt" title column(2) with lines linewidth 4, \
    "times-tail_call.txt" title column(2) with lines linewidth 4

