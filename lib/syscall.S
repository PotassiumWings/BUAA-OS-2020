#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>
#include <stackframe.h>
#include <unistd.h>

/*** exercise 4.2 ***/
NESTED(handle_sys,TF_SIZE, sp)
    SAVE_ALL                            // Macro used to save trapframe
    CLI                                 // Clean Interrupt Mask
    nop
    .set at                             // Resume use of $at

    // TODO: Fetch EPC from Trapframe, calculate a proper value and store it back to trapframe.
	lw		t0, TF_EPC(sp)
	addiu	t0, t0, 4
	sw		t0, TF_EPC(sp)
    // TODO: Copy the syscall number into $a0.
	lw		a0, TF_REG4(sp) 
    addiu   a0, a0, -__SYSCALL_BASE     // a0 <- relative syscall number
    sll     t0, a0, 2                   // t0 <- relative syscall number times 4
    la      t1, sys_call_table          // t1 <- syscall table base
    addu    t1, t1, t0                  // t1 <- table entry of specific syscall
    lw      t2, 0(t1)                   // t2 <- function entry of specific syscall

    lw      t0, TF_REG29(sp)            // t0 <- user's stack pointer
	lw      t3, TF_REG5(sp)                  // t3 <- 参数数量
    li      t5, 0
    
    // add a0-a3
    lw          a0, TF_REG4(sp)
    lw          a1, TF_REG6(sp)
    lw          a2, TF_REG7(sp)
    lw          a3, 16(t0)
    
    get_sp_pos:
    	beq t5,t3,end_get_sp_pos
    	nop
    	addiu sp,sp,-4
    	addiu t5,t5,1
    	j get_sp_pos
    	nop
    end_get_sp_pos:
    addiu sp,sp,-4

    sw t3,0(sp)
    li t5,3
    addiu t6,t0,20
    addiu t7,sp,16
    
    add_to_sp:
		ble t3,t5,end_add_to_sp
		nop
		lw t8,0(t6)
		sw t8,0(t7)
		addiu t6,t6,4
		addiu t7,t7,4
		addiu t5,t5,1
		j add_to_sp
		nop
	end_add_to_sp:
	
        /*
    lw      t3, 16(t0)                  // t3 <- the 5th argument of msyscall
    lw      t4, 20(t0)                  // t4 <- the 6th argument of msyscall

    // TODO: Allocate a space of six arguments on current kernel stack and copy the six arguments to proper location
    	lw          a0, TF_REG4(sp)
        lw              a1, TF_REG5(sp)
        lw              a2, TF_REG6(sp)
        lw              a3, TF_REG7(sp)
        addiu   sp, sp, -24
        sw              t3, 16(sp)
        sw              t4, 20(sp)
        addiu   sp, sp, -24
        sw      a0, 0(sp)
        sw      a1, 4(sp)
        sw      a2, 8(sp)
        sw      a3, 12(sp)
        sw      t3, 16(sp)
        sw      t4, 20(sp)*/


    jalr    t2                          // Invoke sys_* function
    nop

    // TODO: Resume current kernel stack
    //    addiu   sp, t7,16
    lw      t0,0(sp);
	li t1,0
	renew_sp:
		beq t1,t0,end_renew
		nop
		addiu sp,sp,4
		addiu t1,t1,1
		j renew_sp
		nop
	end_renew:
	addiu sp,sp,4	

    sw      v0, TF_REG2(sp)             // Store return value of function sys_* (in $v0) into trapframe

    j       ret_from_exception          // Return from exeception
    nop
END(handle_sys)

sys_call_table:                         // Syscall Table
.align 2
    .word sys_putchar
    .word sys_getenvid
    .word sys_yield
    .word sys_env_destroy
    .word sys_set_pgfault_handler
    .word sys_mem_alloc
    .word sys_mem_map
    .word sys_mem_unmap
    .word sys_env_alloc
    .word sys_set_env_status
    .word sys_set_trapframe
    .word sys_panic
    .word sys_ipc_can_send
    .word sys_ipc_recv
    .word sys_cgetc
	.word sys_super_multi_parameter

