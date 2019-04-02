!/usr/bin/gnuplot -p

#plot "adv0.0.d" using 1:6 title "Epsilon= 0.0" w l, \
#     "adv0.5.d" using 1:6 title" Epsilon= 0.5" w l, \
#     "adv0.9.d" using 1:6 title "Epsilon= 0.9" w l, \
#     "adv0.999.d" using 1:6 title "Epsilon= 0.999" w l

plot "adv.d" using 1:6 w l

set xlabel "Time since last apocenter passage"
set ylabel "Radial distance between bodies"

set key outside
# set yrange [-1:1]
# set xrange [-1:1]
set title "phys3071 as07 melsom 42593249"
set size square

set term postscript color
set output "as07-melsom-42593249-plot3.ps"
replot
