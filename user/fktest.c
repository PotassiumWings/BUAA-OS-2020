#include "lib.h"


void umain()
{
	int a = 0;
	int id = 0;
    int i;

    syscall_ipc_can_multi_send(1, 4, 0, 10, 1,2,3,4,5,6,7,8,9,10);

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
