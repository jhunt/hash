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

IMAGES := viz/words/bins/scatter.png  \
          viz/words/bins/boxplot.png  \
          viz/words/bins/fast.png     \
          viz/words/ns/boxplot.png    \
          viz/words/ns/fast.png       \
          \
          viz/qnames/bins/scatter.png \
          viz/qnames/bins/boxplot.png \
          viz/qnames/bins/fast.png    \
          viz/qnames/ns/boxplot.png   \
          viz/qnames/ns/middle.png    \
          viz/qnames/ns/fast.png

HASH_SRC := algo/murmur3.c  \
            algo/djb2.c     \
            algo/jenkins1.c \
            algo/kr.c       \
            algo/lookup3.c  \
            algo/sdbm.c     \
            algo/spooky2.c  \
            algo/xor.c
HASH_OBJ := $(HASH_SRC:.c=.o)

DATA_FILES := data/words/bins.dat  \
              data/words/ns.dat    \
              data/qnames/bins.dat \
              data/qnames/ns.dat

CFLAGS := -O0

default: plot
plot: $(IMAGES)

datafiles: $(DATA_FILES)
rerun: dataclean datafiles

data/words/bins.dat: run
	mkdir -p data/words
	./run bins >$@ <corpus/words-all
data/words/ns.dat: run
	mkdir -p data/words
	./run ns   >$@ <corpus/words-all

data/qnames/bins.dat: run
	mkdir -p data/qnames
	./run bins >$@ <corpus/qnames
data/qnames/ns.dat: run
	mkdir -p data/qnames
	./run ns   >$@ <corpus/qnames


viz/words/bins/scatter.png: viz/words/bins/scatter.sh data/words/bins.dat
	mkdir -p viz/words/bins
	gnuplot < $< > $@
viz/words/bins/boxplot.png: viz/words/bins/boxplot.sh data/words/bins.dat
	mkdir -p viz/words/bins
	gnuplot < $< > $@
viz/words/bins/fast.png: viz/words/bins/fast.sh data/words/bins.dat
	mkdir -p viz/words/bins
	gnuplot < $< > $@

viz/words/ns/boxplot.png: viz/words/ns/boxplot.sh data/words/ns.dat
	gnuplot < $< > $@
viz/words/ns/fast.png: viz/words/ns/fast.sh data/words/ns.dat
	gnuplot < $< > $@


viz/qnames/bins/scatter.png: viz/qnames/bins/scatter.sh data/qnames/bins.dat
	mkdir -p viz/qnames/bins
	gnuplot < $< > $@
viz/qnames/bins/boxplot.png: viz/qnames/bins/boxplot.sh data/qnames/bins.dat
	mkdir -p viz/qnames/bins
	gnuplot < $< > $@
viz/qnames/bins/fast.png: viz/qnames/bins/fast.sh data/qnames/bins.dat
	mkdir -p viz/qnames/bins
	gnuplot < $< > $@

viz/qnames/ns/boxplot.png: viz/qnames/ns/boxplot.sh data/qnames/ns.dat
	gnuplot < $< > $@
viz/qnames/ns/middle.png: viz/qnames/ns/middle.sh data/qnames/ns.dat
	gnuplot < $< > $@
viz/qnames/ns/fast.png: viz/qnames/ns/fast.sh data/qnames/ns.dat
	gnuplot < $< > $@


run.o: run.c $(HASH_SRC)
run: run.o $(HASH_OBJ)

clean:
	rm -f run run.o $(HASH_OBJ)
dataclean:
	rm -f $(DATA_FILES)
