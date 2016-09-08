#!/usr/bin/env gnuplot
set terminal png

set yrange [0:100]

datafile = 'data/ns.dat'
plot datafile index 0 using 1 title column, \
     datafile index 0 using 2 title column, \
     datafile index 0 using 3 title column, \
     datafile index 0 using 4 title column, \
     datafile index 0 using 5 title column, \
     datafile index 0 using 6 title column, \
     datafile index 0 using 7 title column, \
     datafile index 0 using 8 title column
