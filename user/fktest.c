#include "lib.h"


void umain()
{
	int a = 0;
	int id = 0;
    int i;

	if ((id = fork()) == 0) {
		if ((id = fork()) == 0) {
			a += 3;

			for (i=0;i<20;i++) {
				writef("\t\tthis is child2 :a:%d\n", a);
			}
		}

		a += 2;

		for (i=0;i<20;i++) {
			writef("\tthis is child :a:%d\n", a);
		}
	}

	a++;

	for (i=0;i<20;i++) {
		writef("this is father: a:%d\n", a);
	}
}
