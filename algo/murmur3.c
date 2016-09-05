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

static const uint32_t C1 = 0xcc9e2d51;
static const uint32_t C2 = 0x1b873593;
static const uint32_t R1 = 15;
static const uint32_t R2 = 13;
static const uint32_t M  = 5;
static const uint32_t N  = 0xe6546b64;

/* rotate (x) to the left (y) bits */
#define ROL(x,y) ((x) << (y) | ((x) >> (32 - (y))))

unsigned int murmur3_32(const char *str, unsigned long len, unsigned int seed)
{
	uint32_t hash, k;
	unsigned long nhead;
	const uint32_t *head;
	const uint8_t  *tail;
	int i;

	hash = seed;
	nhead = len / 4;
	head = (const uint32_t *)str;

	for (i = 0; i < nhead; i += 4) {
		k = ROL(head[i] * C1, R1) * C2;
		hash = ROL(hash^k, R2) * M + N;
	}

	k = 0;
	tail = (uint8_t *)str + (len / 4);
	switch (len & 3) {
	case 3: k ^= tail[2] << 16;
	case 2: k ^= tail[1] << 8;
	case 1: k ^= tail[0];
	        hash ^= ROL(k * C1, R1) * C2;
	}

	hash ^= (uint32_t)len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return hash;
}
