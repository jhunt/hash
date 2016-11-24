#!/usr/bin/env gnuplot
set terminal png

#!/usr/bin/env gnuplot
set terminal png

set style fill solid 0.25 border -1
set style boxplot nooutliers pointtype 7
set style data boxplot
set boxwidth  0.2
set pointsize 0.5
set yrange [10:50]

unset key
set border 2
set xtics nomirror
set ytics nomirror
set xtics ( \
      "murmur3"  1, \
      "xor"      2  \
) scale 0.0

datafile = 'data/qnames/ns.dat'
plot datafile using (1.0):1, \
     datafile using (2.0):9
