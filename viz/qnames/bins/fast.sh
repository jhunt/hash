#!/usr/bin/env gnuplot
set terminal png

set style boxplot outliers
set style fill solid 0.25 border -1
set style boxplot outliers pointtype 7
set style data boxplot
set boxwidth  0.2
set pointsize 0.5

unset key
set border 2
set xtics nomirror
set ytics nomirror
set xtics ( \
      "djb2/32"     1, \
      "jenkins1/32" 2, \
      "kr/32"       3, \
      "lookup3/32"  4, \
      "sdbm/32"     5, \
      "spooky2/32"  6 \
) scale 0.0

datafile = 'data/qnames/bins.dat'
plot datafile using (1.0):2, \
     datafile using (2.0):3, \
     datafile using (3.0):4, \
     datafile using (4.0):5, \
     datafile using (5.0):6, \
     datafile using (6.0):7
