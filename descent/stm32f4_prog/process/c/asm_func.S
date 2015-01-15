.text
.global _start
.code 16
.syntax unified

@void run(u32* sp);
@ sp put in r0
.global run
run:
  ldr     r4, [r0, #(4 * 14)]     @ Load process entry point into R4
  add     r0, #(4 * 16)           @ emulate context restore
  mov sp, r0

  bl asm_init_systick

  cpsie i @ Enable interrupts at processor level
  bx r4 


@ void asm_init_systick();
.global asm_init_systick
asm_init_systick:
@ systick setting
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
  bx lr

@void pendsv_isr(void)
.type pendsv_isr, function
.global pendsv_isr
pendsv_isr:
  cpsid i @Prevent interruption during context switch

  push {r4-r11}

  mov r0, sp

  ldr r1, =kernel_stack
  mov sp, r1
  push {lr}
  bl schedule
  pop {lr}

  mov sp, r0
  pop {R4-R11}     // Restore r4-11 from new process stack

  cpsie i
  bx lr



.section .stackares,"aw",%progbits
.space  0x200, 0
kernel_stack:

