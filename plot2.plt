!/usr/bin/gnuplot -p

plot "data0.0.dat" using 1:6 title "Epsilon= 0.0" w l, \
     "data0.5.dat" using 1:6 title" Epsilon= 0.5" w l, \
     "data0.9.dat" using 1:6 title "Epsilon= 0.9" w l, \
     "data0.999.dat" using 1:6 title "Epsilon= 0.999" w l

set xlabel "Time since last apocenter passage"
set ylabel "Radial distance between bodies"

set key outside
#set yrange [-1:1]
#set xrange [-1:1]
set title "phys3071 as07 melsom 42593249"
set size square

set term postscript color
set output "as07-melsom-42593249-plot2.ps"
replot
