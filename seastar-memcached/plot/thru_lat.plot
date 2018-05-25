
reset
set terminal png
set term png size 400, 400
set size square

set style line 101 lc rgb '#00000' lt 1 lw 2
set border 4095 front ls 101 lw 2
set tics nomirror out scale 0.75
set format '%g'

set xtics font ", 14"
set ytics font ", 14"
set key at 6,73 font ",14"

# set yrange [0:70]
set style data linespoints
# set style fill pattern 2 border lt 1
set key noinvert samplen 4 spacing 1 width 0 height 2
set key opaque

# set xrange [-0.5:3.3]
set style line 1 lt rgb "#000000" lw 2 ps 2 pt 3
set style line 2 lt rgb "#000000" lw 2 ps 2 pt 4

set output "latency.png"
set key fixed right top  noreverse enhanced autotitle
set xlabel "outstanding threads" font ",14"
set ylabel "micro-seconds per response" font ",14"
plot "thru_lat.dat" using (log($1)):2:xtic(1) title 'POSIX' ls 1, \
     "thru_lat.dat" using (log($1)):4:xtic(1) title 'DPDK' ls 2


set output "throughput.png"
set key fixed right bottom  noreverse enhanced autotitle
set xlabel "outstanding threads" font ",14"
set ylabel "Mbyte per second" font ",14"
plot "thru_lat.dat" using (log($1)):3:xtic(1) title 'POSIX' ls 1, \
    "thru_lat.dat" using (log($1)):5:xtic(1) title 'DPDK' ls 2
