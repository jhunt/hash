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
      "murmur3"  1, \
      "djb2"     2, \
      "fnv1a"    3, \
      "jenkins1" 4, \
      "kr"       5, \
      "lookup3"  6, \
      "sdbm"     7, \
      "spooky2"  8, \
      "xor"      9  \
) scale 0.0

datafile = 'data/words/bins.dat'
plot datafile using (1.0):1, \
     datafile using (2.0):2, \
     datafile using (3.0):3, \
     datafile using (4.0):4, \
     datafile using (5.0):5, \
     datafile using (6.0):6, \
     datafile using (7.0):7, \
     datafile using (8.0):8, \
     datafile using (9.0):9
