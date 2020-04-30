// Ping-pong a counter between two processes.
// Only need to start one of these -- splits into two with fork.

#include "lib.h"

void
umain(void)
{
        u_int w1,w2, i,j;

        u_int x=0x800,y=0x1802;
        ipc_send_double(x,y,0,0,0);
        
        for (;;) {
                writef("%x am waiting.....\n", syscall_getenvid());
                i = ipc_recv(&w1, 0, 0);
                writef("%x got %d from %x\n", syscall_getenvid(), i, w1);
                j = ipc_recv(&w2, 0, 0);
                writef("%x got %d from %x\n", syscall_getenvid(), j, w2);

                if (i!=j)
                    user_panic("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
                if (i == 5) {
                        return;
                }

                i++;
                writef("\n@@@@@send %d from %x to %x x\n",i, syscall_getenvid(), w1, w2);
                ipc_send_double(w1,w2, i, 0, 0);

                if (i == 10) {
                        return;
                }
        }

}
