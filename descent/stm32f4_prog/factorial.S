# ARM Cortex-M3 嵌入式系統 設計入門 p 19-3 
.equ STACK_TOP, 0x20000800
.text
.global _start
.code 16
.syntax unified
_start:
  .word STACK_TOP, start
  .type start, function 
  # let lsb to 1

start:
  movs r0, #10
  movs r1, #0

loop:
  adds r1, r0
  subs r0, #1
  bne loop

deadloop:
  b deadloop
.end

