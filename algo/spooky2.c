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

#include <sys/types.h>
#include <stdint.h>
#include <string.h>

#define VARS   12
#define BLOCK  (VARS * sizeof(uint64_t))
#define ROL(x,y) ((x) << (y) | ((x) >> (64 - (y))))

#define mix(data,s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11) {\
	 s0 += (data)[0];     s2 ^= s10;   s11 ^= s0;     s0 = ROL(s0,11);   s11 += s1;  \
	 s1 += (data)[1];     s3 ^= s11;   s0 ^= s1;      s1 = ROL(s1,32);    s0 += s2;  \
	 s2 += (data)[2];     s4 ^= s0;    s1 ^= s2;      s2 = ROL(s2,43);    s1 += s3;  \
	 s3 += (data)[3];     s5 ^= s1;    s2 ^= s3;      s3 = ROL(s3,31);    s2 += s4;  \
	 s4 += (data)[4];     s6 ^= s2;    s3 ^= s4;      s4 = ROL(s4,17);    s3 += s5;  \
	 s5 += (data)[5];     s7 ^= s3;    s4 ^= s5;      s5 = ROL(s5,28);    s4 += s6;  \
	 s6 += (data)[6];     s8 ^= s4;    s5 ^= s6;      s6 = ROL(s6,39);    s5 += s7;  \
	 s7 += (data)[7];     s9 ^= s5;    s6 ^= s7;      s7 = ROL(s7,57);    s6 += s8;  \
	 s8 += (data)[8];    s10 ^= s6;    s7 ^= s8;      s8 = ROL(s8,55);    s7 += s9;  \
	 s9 += (data)[9];    s11 ^= s7;    s8 ^= s9;      s9 = ROL(s9,54);    s8 += s10; \
	s10 += (data)[10];    s0 ^= s8;    s9 ^= s10;    s10 = ROL(s10,22);   s9 += s11; \
	s11 += (data)[11];    s1 ^= s9;    s10 ^= s11;   s11 = ROL(s11,46);  s10 += s0;  \
}

#define endpart(h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11) {\
	h11+= h1;    h2 ^= h11;   h1 = ROL(h1,44);  \
	h0 += h2;    h3 ^= h0;    h2 = ROL(h2,15);  \
	h1 += h3;    h4 ^= h1;    h3 = ROL(h3,34);  \
	h2 += h4;    h5 ^= h2;    h4 = ROL(h4,21);  \
	h3 += h5;    h6 ^= h3;    h5 = ROL(h5,38);  \
	h4 += h6;    h7 ^= h4;    h6 = ROL(h6,33);  \
	h5 += h7;    h8 ^= h5;    h7 = ROL(h7,10);  \
	h6 += h8;    h9 ^= h6;    h8 = ROL(h8,13);  \
	h7 += h9;    h10^= h7;    h9 = ROL(h9,38);  \
	h8 += h10;   h11^= h8;    h10= ROL(h10,53); \
	h9 += h11;   h0 ^= h9;    h11= ROL(h11,42); \
	h10+= h0;    h1 ^= h10;   h0 = ROL(h0,54);  \
}

#define end(data,h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11) {\
	h0 += data[0];   h1 += data[1];   h2 += data[2];   h3 += data[3]; \
	h4 += data[4];   h5 += data[5];   h6 += data[6];   h7 += data[7]; \
	h8 += data[8];   h9 += data[9];   h10 += data[10]; h11 += data[11]; \
	endpart(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11); \
	endpart(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11); \
	endpart(h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11); \
}

static void spooky2_128(const char *str, unsigned long len, uint64_t *hash1, uint64_t *hash2)
{
	const uint64_t *block;
	uint64_t h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
	unsigned long nblock;
	uint64_t buf[VARS];
	size_t r, i;

	h0 = h3 = h6 = h9  = *hash1;
	h1 = h4 = h7 = h10 = *hash2;
	h2 = h5 = h8 = h11 = 0xdeadbeefdeadbeefLL;
	nblock = len / BLOCK;
	block = (const uint64_t *)str;

	for (i = 0; i < nblock; i++, block += VARS)
		mix(block, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);

	// handle the last partial block of BLOCK bytes
	r = len % BLOCK;
	if (r != 0) {
		memcpy(buf, block, r);
		memset((uint8_t *)buf + r, 0, sizeof(buf) - r);
		((uint8_t *)buf)[sizeof(buf) - 1] = r;

		// do some final mixing
		end(buf, h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11);
	}

	*hash1 = h0;
	*hash2 = h1;
}

unsigned int spooky2_32(const char *str, unsigned long len, unsigned int seed)
{
	uint64_t hash1, hash2;
	hash1 = hash2 = seed;
	spooky2_128(str, len, &hash1, &hash2);
	return (hash2 & 0xffffffff);
}
