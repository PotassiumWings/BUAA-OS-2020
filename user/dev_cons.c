#include "lib.h"


void u_myoutput(void *arg, const char *s, int l) {
	int i;

	// special termination call
	if ((l == 1) && (s[0] == '\0')) {
		return;
	}

	for (i = 0; i < l; i++) {
		syscall_write_dev(&s[i],0x10000000,1);

		if (s[i] == '\n') {
			syscall_putchar(&s[i],0x10000000,1);
		}
	}
}

int ugetStr(char *buff) {
	char c = 0;
	int now_index = 0;
	while (c != '\r') {
		syscall_read_dev(&c,0x10000000,1);
		syscall_writed_dev(&c,0x10000000,1);
		buff[now_index++] = c;
	}
	buff[now_index++]='\0';
	return now_index;
}

void uwritef(char *fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	user_lp_Print(u_myoutput,0,fmt,ap);
	va_end(ap);
}
