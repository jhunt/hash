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

#include <stdio.h>
#include <string.h>

typedef unsigned int (*hash_fn)(const char*, unsigned long, unsigned int);

#define HASH_FN(f) extern unsigned int (f)(const char*, unsigned long, unsigned int)
HASH_FN(murmur3_32);
#undef HASH_FN

static void usage(const char *name)
{
	if (name)
		fprintf(stderr, "USAGE: %s <algo>\n\n", name);

	fprintf(stderr, "Supported hash algorithms:\n"
	                "  - murmur3_32\n");
}

static int run(hash_fn f)
{
	int n = 0;
	char *p, buf[8192];

	while (fgets(buf, 8192, stdin) != NULL) {
		n++;
		p = strrchr(buf, '\n');
		if (!p) {
			fprintf(stderr, "WARNING: line %d too long (>8192 characters); skipping\n", n);
			continue;
		}
		*p = '\0';

		printf("H(\"%s\") = %#8x\n", buf, f(buf, strlen(buf), 0));
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}

#define CHECK(s) if (strcmp(argv[1], #s) == 0) return run(s)
	CHECK(murmur3_32);
#undef CHECK

	fprintf(stderr, "Unrecognized hash algorithm '%s'\n", argv[1]);
	usage(NULL);
	return 1;
}
