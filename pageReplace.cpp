#include "pageReplace.h"
#define MAXPAGE 64
#define PG 12
#define getPage(x) (x >> PG)
//#pragma GCC optimize("-O2")
//#pragma GCC optimize(3)

#define MAXQUEUELEN 500
// (hd,tl]
int queue[512], hd, tl; // circulate queue
char vis[524288]; // page in queue num
char pos[524288]; // in p index
//inline 
void push_Q (int x) {
	if (tl == MAXQUEUELEN) {
		tl = 0;
	} else {
		++tl;
	}
	queue[tl] = x;
	++vis[x];
}
int pop_Q () {
	while (1) {
		int x;
		// del an element that doesnt exist in p 
		if (hd == MAXQUEUELEN) {
			hd = 0;
		} else {
			++hd;
		}
		if (!--vis[queue[hd]]) 
			return pos[queue[hd]];
	}
}
void pageReplace (long* p, long pa) {
	int pgnum = getPage(pa);
	static int full = 0;
	static int cnt = 0;

	if (vis[pgnum] >= 7) {
		return;
	}

	push_Q(pgnum);

	// exist in p
	if (vis[pgnum] >= 2) {
		return;	
	}
	
	// p full
	if (full) {
		int position = pop_Q();
		p[position] = pgnum;
		pos[pgnum] = position;
	}
	// not full
	else {
		p[cnt] = pgnum;
		pos[pgnum] = cnt;
		// update full
		if (++cnt == MAXPAGE) {
			full = 1;
		}
	}
} 
