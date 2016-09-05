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

unsigned int xor_32(const char *str, unsigned long len, unsigned int seed)
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
		hash ^= head[i];
	}

	k = 0;
	tail = (uint8_t *)str + (len / 4);
	switch (len & 3) {
	case 3: k ^= tail[2] << 16;
	case 2: k ^= tail[1] << 8;
	case 1: k ^= tail[0];
	        hash ^= k;
	}

	return hash;
}
