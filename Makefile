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

default: run
	./check < corpus/words-all
	./check < corpus/words-all serious {djb2,kr,jenkins1,lookup3,murmur3,sdbm}_32

HASH_SRC := algo/murmur3.c \
            algo/djb2.c \
            algo/jenkins1.c \
            algo/kr.c \
            algo/lookup3.c \
            algo/sdbm.c \
            algo/xor.c
HASH_OBJ := $(HASH_SRC:.c=.o)

run.o: run.c $(HASH_SRC)
run: run.o $(HASH_OBJ)

clean:
	rm -f run run.o $(HASH_OBJ)
