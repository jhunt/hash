/* Copyright (c) 2016 James Hunt

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to
   deal in the Software without restriction, including without limitation the
   rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
   sell copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
   IN THE SOFTWARE.
*/

#include <stdint.h>

#define ROL(x,y) ((x) << (y) | ((x) >> (32 - (y))))

unsigned int lookup3_32(const char *str, unsigned long len, unsigned int seed)
{
	unsigned long i;
	unsigned int a, b, c;

	a = b = c = 0xdeadbeef + (((uint32_t)len) << 2) + seed;
	while (len > 3) {
		a += str[0];
		b += str[1];
		c += str[2];

		a -= c;  a ^= ROL(c, 4);  c += b;
		b -= a;  b ^= ROL(a, 6);  a += c;
		c -= b;  c ^= ROL(b, 8);  b += a;
		a -= c;  a ^= ROL(c,16);  c += b;
		b -= a;  b ^= ROL(a,19);  a += c;
		c -= b;  c ^= ROL(b, 4);  b += a;

		len -= 3;
		str += 3;
	}
	switch (len) {
	case 3: c += str[2];
	case 2: b += str[1];
	case 1: a += str[0];
	        c ^= b; c -= ROL(b,14);
	        a ^= c; a -= ROL(c,11);
	        b ^= a; b -= ROL(a,25);
	        c ^= b; c -= ROL(b,16);
	        a ^= c; a -= ROL(c,4);
	        b ^= a; b -= ROL(a,14);
	        c ^= b; c -= ROL(b,24);
	case 0: break;
	}

	return c;
}
