/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>

// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset_now = offset_begin;
	int offset = 0;
	int op_status=0;
	int read=0;
	int can_read=0;

	while (offset_begin + offset < offset_end) {
        // Your code here
        // error occurred, then panic.
        offset_now=offset_begin+offset;
        //设置id diskno
        if(syscall_write_dev(&diskno,0x13000010,4)!=0){
        	user_panic("write failed!\n");
		}
		//设置offset
		if(syscall_write_dev(&offset_now,0x13000000,4)!=0){
        	user_panic("write failed!\n");
		}
		//设置value
		if(syscall_write_dev(&read,0x13000020,4)!=0){
        	user_panic("write failed!\n");
		}
		//获取操作状态status
		if(syscall_read_dev(&op_status,0x13000030,4)!=0){
        	user_panic("write failed!\n");
		}
		if(op_status==0){
			user_panic("read failed!\n");
		}
		//获取data
		if(syscall_read_dev(dst+offset,0x13004000,0x200)!=0){
        	user_panic("read failed!\n");
		}
		offset=offset+0x200;
	}
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{
        // Your code here
	// int offset_begin = ;
	// int offset_end = ;
	// int offset = ;
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset_now = offset_begin;
	int offset = 0;
	int op_status=0;
	int write=1;
	int can_read=0;
	writef("diskno: %d\n", diskno);
	// while ( < ) {
	    // copy data from source array to disk buffer.

            // if error occur, then panic.
	// }
	while (offset_begin + offset < offset_end) {
        // Your code here
        // error occurred, then panic.
        offset_now=offset_begin+offset;
        //设置id diskno
        if(syscall_write_dev(&diskno,0x13000010,4)!=0){
        	user_panic("write failed!\n");
		}
		//设置offset
		if(syscall_write_dev(&offset_now,0x13000000,4)!=0){
        	user_panic("write failed!\n");
		}
		//写入data
		if(syscall_write_dev(src+offset,0x13004000,0x200)!=0){
        	user_panic("read failed!\n");
		}
		//写入value
		if(syscall_write_dev(&write,0x13000020,4)!=0){
        	user_panic("write failed!\n");
		}
		//获取status
		if(syscall_read_dev(&op_status,0x13000030,4)!=0){
        	user_panic("write failed!\n");
		}
		if(op_status==0){
			user_panic("read failed!\n");
		}
		offset=offset+0x200;
	}
}

