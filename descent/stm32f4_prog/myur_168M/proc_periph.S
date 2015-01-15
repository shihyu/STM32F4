#if 0

@.equ STACK_TOP, 0x20000800
.text
.global _start
.code 16
.syntax unified
_start:
  .word STACK_TOP, start 
  .type start, function @ let lsb to 1

  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1 @ svc isr
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
#endif

#define ENABLE_SYSTICK

.syntax unified
.code 16
.text
.global init_proc
.type start, function @ let lsb to 1
init_proc:
@  bl init_c_runtime
@  bl init
  ldr r0, =cur_proc
  mov r1, #1
  str r1, [r0]


  ldr r0, =stack_frame_a

  ldr r1, =#0xffffffff
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_a
  str r1, [r0, #24] @ setup pc
@  mov r1, #0x21000000
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr

  ldr r0, =a_sp
  ldr r1, =stack_frame_a
  sub r1, #4 @ save for r7
  str r1, [r0]

#ifdef ENABLE_SYSTICK
@ 0xe000ed24 check systick isr active
@ 0xe000e018 check systick count
  ldr r0, =0xe000e010 @ control reg
  mov r1, #0
  str r1, [r0]
  ldr r1, =0x3fff
  str r1, [r0, #4]
  str r1, [r0, #8]
  mov r1, #0x7
  str r1, [r0] @ enable systick
#endif
  svc 0
@  bx lr

.type proc_b, function @ let lsb to 1
proc_b:
@  movs r1, #2
  nop
  bl put_b
@  svc 0
  nop
  b proc_b



.type proc_a, function @ let lsb to 1
proc_a:
  nop
  nop
  nop
  nop
  nop
@  movs r0, #1
  bl put_a
@  svc 0
  nop
  b proc_a


.type del_func, function @ let lsb to 1
del_func:
  mov r5, #5
  b del_func


#if 0
.global test_and_set
.type test_and_set, function @ let lsb to 1
test_and_set:
  push {r1, r2, lr}
try_to_lock:
  ldr r1, =lock
  ldrex r2, [r1]
  cmp r2, #0
  bne lock_device_fail
device_is_not_locked:
  mov r0, #1
  strex r2, r0, [r1]
  cmp r2, #0
  bne lock_device_fail
lock_device_succeed:
  mov r0, #0
  pop {r1, r2, pc}
#endif



#if 1
.global asm_set
.type asm_set, function @ let lsb to 1
asm_set:
#if 0
  @ldr r0, =0x22000008
  ldr r0, =0x22001a80
  mov r1, #1
  str r1, [r0]
#else
  ldr r0, =asm_bit_band
  sub r0, #0x20000000
  lsl r0, #5 @ x 32
  add r0, #0x22000000
  mov r1, #1
  str r1, [r0]
#endif
  bx lr

.global asm_clear
.type asm_clear, function @ let lsb to 1
asm_clear:
  ldr r0, =asm_bit_band
  sub r0, #0x20000000
  lsl r0, #5
  add r0, #0x22000000
  mov r1, #0
  str r1, [r0]
  bx lr
#endif
.global int_isr
.type int_isr, function @ let lsb to 1
int_isr:
  push {r7}
  mov r3, sp @ save cur sp
  @add     r3, sp, #0

  ldr r0, =cur_proc
  ldr r1, [r0]
  cmp r1, #1
  beq.n 1f
  @ not 1, cur proc is proc_a
  @ save sp to a_sp,
  @ set sp by b_sp
  @ set cur_proc to 1

  ldr r1, =a_sp
  str r3, [r1]
  ldr r1, =b_sp
  mov r2, #1
  b 2f

1:
  @ eq 1, cur proc is proc_b, save sp to b_sp,
  @ set sp by a_sp
  @ set cur_proc to 0
  ldr r1, =b_sp
  str r3, [r1]
  ldr r1, =a_sp
  mov r2, #0
2:

  str r2, [r0] @ write 1 or 0 to cur_proC

  ldr sp, [r1]
@  mov sp, r1
  pop {r7}
  bx lr
  #movs pc, proc_a

.global asm_inc
asm_inc:
  push {r0, r1, r2, lr}
1:
  ldr r0, =sv
  ldrex r1,[r0]
  add   r1,r1,#1
  strex r1,r1,[r0]
  cmp   r1,#0  @ Test if non-zero
  bne   1b
  pop {r0, r1, r2, pc}
  
.global asm_dec
asm_dec:
  push {r0, r1, r2, lr}
1:
  ldr r0, =sv
  ldrex r1,[r0]
  sub   r1,r1,#1
  strex r1,r1,[r0]
  cmp   r1,#0  @ Test if non-zero
  bne   1b
  pop {r0, r1, r2, pc}

@.global asm_set_sv
@.type asm_set_sv, function @ let lsb to 1
asm_set_sv:
.global test_and_set
.type test_and_set, function @ let lsb to 1
test_and_set:
  push {r1, r2, r3, lr}
try_to_lock:
  ldr r1, =lock
  ldrex r3, [r1]
  cmp r3, #0
  bne lock_device_fail
device_is_not_locked:
  mov r0, #1
  strex r2, r0, [r1]
  cmp r2, #0
  bne lock_device_fail
lock_device_succeed:
  cmp r3, #1 @ compare old and new value
  beq lock_device_fail

  mov r0, #0
  pop {r1, r2, r3, pc}
lock_device_fail:
  mov r0, #1
  pop {r1, r2, r3, pc}

#.bss
#.section ".stackarea"
.data

sram_begin:

.space  0x40, 0
stack_frame_a:
.word 1 @r0
.word proc_a @r1
.word 3 @r2
.word 0 @r3
.word 0 @r12
.word del_func @lr @ del_func
.word proc_a @pc @ proc_a
.word 0x21000000 @psr

.space  0x40, 0
stack_frame_b:
.word 0 @r0
.word 0 @r1
.word 0 @r2
.word 0 @r3
.word 0 @r12
.word del_func @lr
.word proc_b @pc
.word 0x21000000 @psr

cur_proc:
.word 1

asm_bit_band:
.word 0

.global sv
sv:
.word 1

.global lock
lock:
.word 0

a_sp:
.word 0
b_sp:
.word 0

#if 0
.section ".stackarea"
.space  0x400, 0
STACK_TOP:
#endif




#if 0
ref: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dht0008a/ch01s03s03.html

ARM Synchronization Primitives Development Article
Home > ARM Synchronization Primitives > Practical uses > Implementing a semaphore
1.3.3. Implementing a semaphore

The functions in Example 1.6 show an implementation of a simple blocking semaphore:

    sem_dec decrements a semaphore if its value is greater than 0, or blocks until it is able to decrement it. If blocked, it invokes the WAIT_FOR_UPDATE macro before retrying.

    sem_inc increments a semaphore, invoking the SIGNAL_UPDATE macro to notify blocked processes or processors of the change if the previous value was 0.

WAIT_FOR_UPDATE and SIGNAL_UPDATE are described in Power-saving features.

Example 1.6. implementing a semaphore

; sem_dec
; Declare for use from C as extern void sem_dec(void * semaphore);
    EXPORT sem_dec
sem_dec PROC
1   LDREX   r1, [r0]
    CMP     r1, #0        ; Test if semaphore holds the value 0
    BEQ     %f2           ; If it does, block before retrying
    SUB     r1, #1        ; If not, decrement temporary copy
    STREX   r2, r1, [r0]  ; Attempt Store-Exclusive
    CMP     r2, #0        ; Check if Store-Exclusive succeeded
    BNE     %b1           ; If Store-Exclusive failed, retry from start
    DMB                   ; Required before accessing protected resource
    BX      lr

2   ; Take appropriate action while waiting for semaphore to be incremented
    WAIT_FOR_UPDATE       ; Wait for signal to retry
    B       %b1
    ENDP


; sem_inc
; Declare for use from C as extern void sem_inc(void * semaphore);
    EXPORT sem_inc
sem_inc PROC
1   LDREX   r1, [r0]
    ADD     r1, #1        ; Increment temporary copy
    STREX   r2, r1, [r0]  ; Attempt Store-Exclusive
    CMP     r2, #0        ; Check if Store-Exclusive succeeded
    BNE     %b1           ; Store failed - retry immediately
    CMP         r0, #1        ; Store successful - test if incremented from zero
    DMB                   ; Required before releasing protected resource
    BGE         %f2           ; If initial value was 0, signal update
    BX      lr

2   ; Signal waiting processors or processes
    SIGNAL_UPDATE
    BX      lr
    ENDP


The semaphore variable passed to these functions must be 32 bits in size, located at a 4-byte aligned address. You must initialize it to a value greater than or equal to 0 before first use.

sem_dec performs a Load-Exclusive from the address passed in R0. If this location holds the value 0, the function invokes WAIT_FOR_UPDATE before retrying. If the location holds a value greater than zero, it decrements it and attempts to update the semaphore value using a Store-Exclusive. If the Store-Exclusive fails, for example because another agent has modified the variable after the Load-Exclusive step, it retries from the start. When the Store-Exclusive succeeds, it executes a DMB and returns.

sem_inc performs a Load-Exclusive from the address passed in R0. It then increments this value and attempts to update the location using a Store-Exclusive. If the Store-Exclusive fails, it retries immediately from the Load-Exclusive step. If the Store-Exclusive succeeds, it checks what the value of the semaphore was before incremented, and then executes a DMB. If the value was 0, there could be processes or processors waiting for this semaphore to be incremented, so it invokes the SIGNAL_UPDATE macro before returning.

Example 1.7 shows how you can call these functions from C source code. The function add_task.adds an object of type struct task to a queue and calls sem_inc to atomically increment task_semaphore to signal that a task has been added. The function get_task calls sem_dec to atomically decrement task_semaphore, or block until it is able to do so, and then takes an object off the queue.

Example 1.7. synchronizing a task queue

extern void sem_inc(void * semaphore);
extern void sem_dec(void * semaphore);

unsigned int task_semaphore = 0;

void add_task(struct task * task)
{
    /* Add task to queue */
    ...

    /* Increment semaphore to show task has been added*/
    sem_inc(&task_semaphore);

    return;
}

struct task * void get_task(void)
{
    struct task * tmptask;

    /* Decrement semaphore, or block until it indicates a task is available */
    sem_dec(&task_semaphore);

    /* Take task from queue */
    ...

    return tmptask;
}


ref: http://www.doulos.com/knowhow/arm/Hints_and_Tips/Implementing_Semaphores/

LOCKED EQU 0           ; define value indicating

 LDR     r12, <addr>   ; preload semaphore address
 LDR     r1, =LOCKED   ; preload "locked" value

spin_lock
 LDREX   r0, [r12]     ; load semaphore value
 CMP     r0, #LOCKED   ; if semaphore was locked already
 STREXNE r0, r1, [r12] ;    try to claim
 CMPNE   r0, #1        ;    and check success
 BEQ     spin_lock     ; retry if claiming semaphore failed.
#endif
