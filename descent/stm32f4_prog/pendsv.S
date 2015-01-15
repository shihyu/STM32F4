# test pendSV handler and systick

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
  .word svc_isr+1 @ svc isr
  .word int_isr+1
  .word int_isr+1
  .word pendsv_handle+1
  .word systick_isr+1
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1

start:

  @ ref:  arm cortex-m3: 嵌入式系統設計入門 p8-10
@  ldr r0, =0xe000ed0c
@  ldr r1, =0x05fa0500
@  strb r1, [r0]
@
@ ref: @ Cortex™-M3 Technical Reference Manual (file name: DDI0337E_cortex_m3_r1p1_trm.pdf)
@    System Handler Priority Registers (p8-27)
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


@ systick setting
#if 0
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
#else
  svc 0
#endif

@  cpsie i

@ watch 0xe000ed24, 0xe000ed04 ref: arm cortex-m3: 嵌入式系統設計入門 p8-9
  mov r1, #0x33
deadloop:
  mov r1, #0x22
  b deadloop

pendsv_handle:
  movs r2, #0x12
  nop
  bx lr

svc_isr:
  push {r4-r11, lr}
#if 1
  @ enable pendsv ref: STM32F207 高性能网络型 MCU 嵌入式系统设计 p 412
  ldr r0, =0xe000ed04 
  ldr r1, [r0]
  orr r1, #0x10000000
  str r1, [r0]
#endif
  nop
  movs r3, #0x56
  pop {r4-r11, pc}
  #bx lr

systick_isr:
  PUSH    {R14}
  @ enable pendsv ref: STM32F207 高性能网络型 MCU 嵌入式系统设计 p 412
  ldr r0, =0xe000ed04 
  ldr r1, [r0]
  orr r1, #0x10000000
  str r1, [r0]
  movs r0, #0x98
@  bx lr
  POP     {R14}

int_isr:
  nop
  movs r1, #0xf
@  push {r1}
  bx lr

.data
.space  0x200, 0
psp_stack_top:

.space  0x400, 0
msp_stack_top:
