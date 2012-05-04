
set key right top
set xlabel "time (ms)"
set ylabel "stack size (bytes)"
set log y

#set format x "%.0f"
set xtics 2000

set terminal svg butt linewidth 2 font "Arial, 16"
set output "stack_bw.svg"

plot \
    "stack-hardware.txt"  title column(2) with lines linewidth 2 lc -1, \
    "stack-loop.txt"      title column(2) with lines linewidth 2 lc -1, \
    "stack-recursive.txt" title column(2) with lines linewidth 2 lc -1, \
    "stack-tail_call.txt" title column(2) with lines linewidth 2 lc -1

