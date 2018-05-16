
reset
set terminal png
set term png size 600, 600
set output "mpi-latency.png"

load "grid.cfg"
load "xyboarder.cfg"

set size square
set xtics font ", 14"
set ytics font ", 14"
set xlabel "packet size (bytes)" font ",14"
set ylabel "nano seconds per request" font ",14"
set key top left font ",14"

set style data linespoints
set style fill pattern 2 border lt 1
# set key fixed right top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid
set key noinvert samplen 4 spacing 1 width 0 height 2
set key opaque

set xtics rotate

set style line 1 lt rgb "blue" lw 2 ps 2 pt 9
set style line 2 lt rgb "red" lw 2 ps 2 pt 5
set style line 3 lt rgb "orange" lw 2 ps 2 pt 3
set style line 4 lt rgb "purple" lw 2 ps 2 pt 1
set style line 5 lt rgb "#000000" lw 2 ps 2 pt 8


plot "data" using (log($1)):2:xtic(1) title 'SMP 1' ls 2, \
     "data" using (log($1)):3:xtic(1) title 'SMP 2' ls 3, \
     "data" using (log($1)):4:xtic(1) title 'SMP 4' ls 4, \
     "data" using (log($1)):5:xtic(1) title 'SMP 8' ls 5
