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

#define FNV_32_PRIME 0x01000193

static unsigned int fnv_32(const char *str, unsigned long len, unsigned int seed)
{
	unsigned int hash;
	unsigned long i;

	hash = seed;
	for (i = 0; i < len; ++i) {
		hash ^= str[i];
		hash *= FNV_32_PRIME;
	}
	return hash;
}

unsigned int fnv1a_32(const char *str, unsigned long len, unsigned int seed)
{
	return fnv_32(str, len, fnv_32("chongo <Landon Curt Noll> /\\../\\", 32, 0));
}
