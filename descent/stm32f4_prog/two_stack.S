# use msp, psp 2 stack

.equ STACK_TOP, 0x20000800
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

start:
  mrs r0, control @ read control to r0

  movs r0, #10

  ldr sp, =#msp_stack_top @ msp

  push {r0}

  ldr r0, =#psp_stack_top
  msr psp, r0

  mov r0, #0x3
  msr control, r0

  mrs r0, control

  push {r0}

  svc 0

deadloop:
  nop
  b deadloop

int_isr:
  nop
  movs r1, #0xf
  push {r1}
  bx lr

.data
.space  0x200, 0
psp_stack_top:

.space  0x400, 0
msp_stack_top:
