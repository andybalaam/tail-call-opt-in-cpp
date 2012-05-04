
set key left top
set xlabel "iterations"
set ylabel "exection time (secs)"
set format x "%.0f"
set xtics 10000000

set terminal svg butt linewidth 2 font "Arial, 16"
set output "times_bw.svg"

plot [0:27000000] [0:16] \
    "times-hardware.txt"  title column(2) with lines linewidth 2 lc -1, \
    "times-loop.txt"      title column(2) with lines linewidth 2 lc -1, \
    "times-recursive.txt" title column(2) with lines linewidth 2 lc -1, \
    "times-tail_call.txt" title column(2) with lines linewidth 2 lc -1

