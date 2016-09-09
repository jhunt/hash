# Copyright (c) 2016 James Hunt
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
#

IMAGES := viz/bins/scatter.png \
          viz/bins/boxplot.png \
          viz/bins/fast.png \
          viz/ns/scatter.png \
          viz/ns/boxplot.png \
          viz/ns/fast.png

HASH_SRC := algo/murmur3.c \
            algo/djb2.c \
            algo/jenkins1.c \
            algo/kr.c \
            algo/lookup3.c \
            algo/sdbm.c \
            algo/spooky2.c \
            algo/xor.c
HASH_OBJ := $(HASH_SRC:.c=.o)

default: $(IMAGES)

CFLAGS := -O0

datafiles: data/bins.dat data/ns.dat
data/bins.dat: run
	./run bins >$@ <corpus/words-all
data/ns.dat: run
	./run ns   >$@ <corpus/words-all

viz/bins/scatter.png: viz/bins/scatter.sh data/bins.dat
	gnuplot < $< > $@
viz/bins/boxplot.png: viz/bins/boxplot.sh data/bins.dat
	gnuplot < $< > $@
viz/bins/fast.png: viz/bins/fast.sh data/bins.dat
	gnuplot < $< > $@

viz/ns/scatter.png: viz/ns/scatter.sh data/ns.dat
	gnuplot < $< > $@
viz/ns/boxplot.png: viz/ns/boxplot.sh data/ns.dat
	gnuplot < $< > $@
viz/ns/fast.png: viz/ns/fast.sh data/ns.dat
	gnuplot < $< > $@

run.o: run.c $(HASH_SRC)
run: run.o $(HASH_OBJ)

clean:
	rm -f run run.o $(HASH_OBJ)
