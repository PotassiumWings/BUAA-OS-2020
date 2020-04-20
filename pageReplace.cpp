#include "pageReplace.h"
#define MAXPAGE 64
#define PG 12
#define getPage(x) (x >> PG)

#define MAXQUEUELEN 9000000
int queue[10000000], hd, tl, cir; // circulate queue
int vis[1500000]; // page in queue num
int pos[1500000]; // in p index
void push_Q (int x) {
	if (tl == MAXQUEUELEN) {
		tl = 0;
		cir++;
	} else {
		tl++;
	}
	queue[tl] = x;
	vis[x]++;
}
int pop_Q_one () {
	if (hd == MAXQUEUELEN) {
		hd = 0;
		cir--;
	} else {
		hd++;
	}
	vis[queue[hd]]--;
	if (vis[queue[hd]]) return -1;
	return pos[queue[hd]];
}
int pop_Q () {
	while ((cir && hd > tl) || (!cir && hd < tl)) {
		// del an element that doesnt exist in p 
		int x = pop_Q_one();
		if (x != -1)
			return x;
	}
	while(1);
}
void pageReplace_one (long* p, long pa) {
	int i, pgnum = getPage(pa);
	static int full = 0;
	static int cnt = 0;
	
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
		cnt++;
		// update full
		if (cnt == MAXPAGE) {
			full = 1;
		}
	}
} 
void pageReplace (long* p, long pa) {
    pageReplace_one(p, pa);
    if (true) {
        pageReplace_one(p, pa + (1 << PG));
    }
}
