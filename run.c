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
#include "timer.h"

typedef unsigned int (*hash_fn)(const char*, unsigned long, unsigned int);

#define NUM_ALGOS 8
extern unsigned int  (murmur3_32)(const char*, unsigned long, unsigned int);
extern unsigned int     (djb2_32)(const char*, unsigned long, unsigned int);
extern unsigned int (jenkins1_32)(const char*, unsigned long, unsigned int);
extern unsigned int       (kr_32)(const char*, unsigned long, unsigned int);
extern unsigned int  (lookup3_32)(const char*, unsigned long, unsigned int);
extern unsigned int  (spooky2_32)(const char*, unsigned long, unsigned int);
extern unsigned int     (sdbm_32)(const char*, unsigned long, unsigned int);
extern unsigned int      (xor_32)(const char*, unsigned long, unsigned int);

static struct {
	const char *label;
	hash_fn     fn;
} algos[NUM_ALGOS] = {
	{ "murmur3/32",  murmur3_32  },
	{ "djb2/32",     djb2_32     },
	{ "jenkins1/32", jenkins1_32 },
	{ "kr/32",       kr_32       },
	{ "lookup3/32",  lookup3_32  },
	{ "spooky2/32",  spooky2_32  },
	{ "sdbm/32",     sdbm_32     },
	{ "xor/32",      xor_32      },
};

static void usage(const char *name)
{
	if (name)
		fprintf(stderr, "USAGE: %s (bins|ns)\n\n", name);
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		usage(argv[0]);
		return 1;
	}

	if (strcmp(argv[1], "bins") == 0) {
		int i, j, n = 0;
		char *p, buf[8192];
		int bins[NUM_ALGOS][64] = {0};
		unsigned int h;

		while (fgets(buf, 8192, stdin) != NULL) {
			n++;
			p = strrchr(buf, '\n');
			if (!p) {
				fprintf(stderr, "WARNING: line %d too long (>8192 characters); skipping\n", n);
				continue;
			}
			*p = '\0';

			for (i = 0; i < NUM_ALGOS; i++) {
				bins[i][(algos[i].fn)(buf, strlen(buf), 0) % 64]++;
			}
		}

		for (j = 0; j < NUM_ALGOS; j++) {
			printf("%s%s", j > 0 ? "\t" : "", algos[j].label);
		}
		printf("\n");

		for (i = 0; i < 64; i++) {
			for (j = 0; j < NUM_ALGOS; j++) {
				printf("%s%d", j > 0 ? "\t" : "", bins[j][i]);
			}
			printf("\n");
		}
		return 0;
	}

	if (strcmp(argv[1], "ns") == 0) {
		int i, j, n = 0;
		char *p, buf[8192];
		timer t;
		size_t l;

		for (j = 0; j < NUM_ALGOS; j++) {
			printf("%s%s", j > 0 ? "\t" : "", algos[j].label);
		}
		printf("\n");

		while (fgets(buf, 8192, stdin) != NULL) {
			n++;
			p = strrchr(buf, '\n');
			if (!p) {
				fprintf(stderr, "WARNING: line %d too long (>8192 characters); skipping\n", n);
				continue;
			}
			*p = '\0';

			l = strlen(buf);
			for (j = 0; j < NUM_ALGOS; j++) {
				timed(&t) {
					(algos[i].fn)(buf, l, 0);
				}
				printf("%s%llu", j > 0 ? "\t" : "", timer_value(&t));
			}
			printf("\n");
		}

		return 0;
	}

	usage(argv[0]);
	return 1;
}
