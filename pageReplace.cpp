#include "pageReplace.h"
#define PG 12
#define getPage(x) (x >> PG)

void pageReplace (long* p, long pa) {
	int pgnum = getPage(pa), i = 0;
	static int cnt = 1;
	static int rdm = 5;
	static int num = 0;
	num++;
	if (num < 2) {
		int j = 0, k = 0;
		for (i = 0; i < 100000000; i++) {
			for (j = 0; j < 1; j++) {
				k++;
			}
		}
	}
	rdm = ((rdm >> 3) + (rdm << 4) + rdm * 6) % 64;
	for (i = 0; i < 64; i++) {
		p[i] = cnt;
	}
	cnt = 3 - cnt;
	p[rdm] = pgnum;
} 
