# not process switch, this is context switch

@.equ STACK_TOP, 0x20000800
.text
.global _start
.code 16
.syntax unified
_start:
  .word STACK_TOP, start 
  .type start, function @ let lsb to 1

  .word int_isr+1
  .word hardf_isr+1
  .word mmf_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word svc_isr+1 @ svc isr
  .word int_isr+1
  .word int_isr+1
  .word pendsv_handle+1
  .word systick_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1

start:
  @ pendsv priority
  ldr r0, =0xe000ed22
  mov r1, #0xff
  strb r1, [r0]

  @ systick priority
  ldr r0, =0xe000ed23
  mov r1, #0xff
  strb r1, [r0]

  @ svc priority
  ldr r0, =0xe000ed1f
  mov r1, #0xff
  strb r1, [r0]

  @ init a proc
  ldr r0, =proc_a_stack

  @ setup proc a psr
  mov r1, #0x21000000
  str r1, [r0, #(-4)]

  @ setup proc a pc
  ldr r1, =proc_a
  str r1, [r0, #(-8)]

  @@@@@@@@@@@@@@@@@@@

  @ init b proc
  ldr r0, =proc_b_stack

  @ setup proc b psr
  mov r1, #0x21000000
  str r1, [r0, #(-4)]

  @ setup proc b pc
  ldr r1, =proc_b
  str r1, [r0, #(-8)]

  @@@@@@@@@@@@@@@@@@@

  ldr r0, =proc_a_sp
  ldr r1, =proc_a_stack
  sub r1, #(16*4)
  str r1, [r0]

  ldr r0, =proc_b_sp
  ldr r1, =proc_b_stack
  sub r1, #(16*4)
  str r1, [r0]

  ldr r0, =cur_proc
  mov r1, #0
  str r1, [r0]

  ldr r1, =proc_a_sp
  ldr r0, [r1]

  @ ref: scmrtos-code/Ports/CortexM3/GCC/OS_Target_asm.S
  LDR     r4, [r0, #(4 * 14)]     @ Load process entry point into R4
  add     r0, #(4 * 16)           @ emulate context restore
  mov sp, r0
@  dsb
  isb                             @ Insert a barrier

@ systick setting
#if 1
@ 0xe000ed24 check systick isr active
@ 0xe000e018 check systick count
@ ref: arm cortex-m3: 嵌入式系統設計入門 p8-12

  ldr r0, =0xe000e010 @ SysTick Ctrl & Status Reg
  mov r1, #0
  str r1, [r0]
  ldr r1, =0x3fff
  str r1, [r0, #4]
  str r1, [r0, #8]
  mov r1, #0x7
  str r1, [r0] @ enable systick
#endif

  cpsie   i @ Enable interrupts at processor level

  bx r4 @ run proc_a

.type proc_a, function @ let lsb to 1
proc_a:
  movs r0, #0x90
  push {r0}
  movs r1, #0x91
  pop {r0}
  b proc_a

.type proc_b, function @ let lsb to 1
proc_b:
  movs r0, #0x20
  movs r1, #0x21
  movs r2, #0x22
  movs r3, #0x23
  movs r4, #0x24
  movs r5, #0x25
  movs r6, #0x26
  movs r7, #0x27
  movs r8, #0x28
  movs r9, #0x29
  movs r10, #0x2a
  movs r11, #0x2b
  movs r12, #0x2c
  nop
  svc 0
  b proc_b


int_isr:
  mov r0, #67
  bx lr

hardf_isr:
  mov r0, #0x3b
  bx lr
@ memory manage fault
mmf_isr:
  mov r0, #0x3a
  bx lr

systick_isr:
#if 1
  @ enable pendsv ref: STM32F207 高性能网络型 MCU 嵌入式系统设计 p 412
  ldr r0, =0xe000ed04
  ldr r1, [r0]
  orr r1, #0x10000000
  str r1, [r0]
#endif
  bx lr

svc_isr:
  bx lr

pendsv_handle:
  cpsid i @Prevent interruption during context switch

  push {r4-r11}

  @ choice another process
  ldr r1, =cur_proc
  ldr r0, [r1]

  cmp r0, #1
  beq.n 1f
  @ current proc a, switch to proc b
  ldr r2, =proc_a_sp
  str sp, [r2] @ save cur process sp

  mov r3, #1
  str r3, [r1]

  ldr r0, =proc_b_sp

  b 2f
1:
  @ current proc b, switch to proc a
  ldr r2, =proc_b_sp
  str sp, [r2] @ save cur process sp

  mov r3, #0
  str r3, [r1]

  ldr r0, =proc_a_sp

2:

  ldr r0, [r0]

  mov sp, r0
  pop {R4-R11}     // Restore r4-11 from new process stack

  cpsie i
  bx lr


.data

proc_a_sp:
.word 1
proc_b_sp:
.word 2

proc_a_ptr:
.space  0x300, 0
proc_a_stack:

proc_b_ptr:
.space  0x300, 0
proc_b_stack:


cur_proc:
.word 

.space  0x300, 0
STACK_TOP:
