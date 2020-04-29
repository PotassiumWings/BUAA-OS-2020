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
    
    lw t0, TF_EPC(sp)
    addiu t0,t0,4
    sw t0, TF_EPC(sp)


    // TODO: Copy the syscall number into $a0.
    
    lw a0, TF_REG4(sp)  // first parameter: a0, 4


    addiu   a0, a0, -__SYSCALL_BASE     // a0 <- relative syscall number
    sll     t0, a0, 2                   // t0 <- relative syscall number times 4
    la      t1, sys_call_table          // t1 <- syscall table base
    addu    t1, t1, t0                  // t1 <- table entry of specific syscall
    lw      t2, 0(t1)                   // t2 <- function entry of specific syscall

    lw      t0, TF_REG29(sp)            // t0 <- user's stack pointer
    //lw      t3, 16(t0)                  // t3 <- the 5th argument of msyscall
    //lw      t4, 20(t0)                  // t4 <- the 6th argument of msyscall

    // TODO: Allocate a space of six arguments on current kernel stack and copy the six arguments to proper location

    //addiu sp, sp, -24
    //sw a0, 0(sp)
    //sw a1, 4(sp)
    //sw a2, 8(sp)
    //sw a3, 12(sp)
    //sw t3, 16(sp)
    //sw t4, 20(sp)
    
    //lw a0, TF_REG4(sp)
    //lw a1, TF_REG5(sp)
    //lw a2, TF_REG6(sp)
    //lw a3, TF_REG7(sp)
    //addiu sp, sp, -24
    //sw t3, 16(sp)
    //sw t4, 20(sp)
    
    lw a1, TF_REG5(sp)  // a1 = parameter count
    move t6, 0            // t6 = sp jump delta
    addi t7, t6, 4      // t7 = 4

    ble a1, t7, NO_SV   // no need to change sp, count <= 4
    nop
    move t6, a1           // t6 = count
    sll t6, t6, 2       // t6 = count * 4

    subu sp, sp, t6     // sp move t6

    move t3, 0            // t3 = 0
    addi t4, t0, 16     // t4 = 16 + t0 (from)
    addi t5, sp, 16     // t5 = 16 + sp (to)

loop_cnt:
    bge t3, a1, loop_cnt_end    // t3 < a1
    nop
    
    lw s0, 0(t4)
    sw s0, 0(t5)

    addiu t3, t3, 1
    addiu t4, t4, 4
    addiu t5, t5, 4

    j loop_cnt
    nop


loop_cnt_end:
NO_SV:
    


    
    jalr    t2                          // Invoke sys_* function
    nop
    
    // TODO: Resume current kernel stack

    addiu sp, sp, t6    // sp move t6

    
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
