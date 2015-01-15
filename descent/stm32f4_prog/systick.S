# test systick

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
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1
  .word systick_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1

start:

@ ref:  arm cortex-m3: 嵌入式系統設計入門 p8-12
@ 0xe000e010, 0xe000e014, 0xe000e018
@ systick setting
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

@ watch 0xe000ed24, 0xe000ed04 ref: arm cortex-m3: 嵌入式系統設計入門 p8-9
  mov r1, #0x33
deadloop:
  mov r1, #0x22
  b deadloop

systick_isr:
  PUSH    {lr}
  mov r0, #0x05
  mov r1, #0x27
  @bx lr
  POP     {pc}

int_isr:
  nop
  movs r1, #0xf
@  push {r1}
  bx lr

