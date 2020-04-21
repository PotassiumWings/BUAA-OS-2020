#include "pageReplace.h"
#define MAXPAGE 64
#define PG 12
#define getPage(x) (x >> PG)

#define MAXQUEUELEN 400
int queue[405], hd, tl; //, cir; // circulate queue
char vis[530000]; // page in queue num
char pos[530000]; // in p index
void push_Q (int x) {
	if (tl == MAXQUEUELEN) {
		tl = 0;
		//cir++;
	} else {
		tl++;
	}
	queue[tl] = x;
	vis[x]++;
}
int pop_Q_one () {
	if (hd == MAXQUEUELEN) {
		hd = 0;
		// cir--;
	} else {
		hd++;
	}
	vis[queue[hd]]--;
	if (vis[queue[hd]]) return -1;
	return pos[queue[hd]];
}
int pop_Q () {
	//while ((cir && hd > tl) || (!cir && hd < tl)) {
    while (1) {
		// del an element that doesnt exist in p 
		int x = pop_Q_one();
		if (x != -1)
			return x;
	}
	// while(1);
}
void pageReplace (long* p, long pa) {
	int i, pgnum = getPage(pa);
	static int full = 0;
	static int cnt = 0;
	
	if (vis[pgnum] >= 5) {
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
		cnt++;
		// update full
		if (cnt == MAXPAGE) {
			full = 1;
		}
	}
} 
