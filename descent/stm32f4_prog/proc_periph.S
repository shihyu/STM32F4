# process switch and blink led
# ref : http://tw.m.wretch.yahoo.com/blog/DreamYeh/888788
# comment: #, @

#define ENABLE_SYSTICK

.extern init_stm32f4
.equ STACK_TOP, 0x20001000
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
  .word int_isr+1 @ sysick isr
  .word int_isr+1
  .word int_isr+1
  .word int_isr+1

start:
  ldr r5, =cur_proc
  mov r1, #0
  str r1, [r5]

  bl init_stm32f4
  bl asm_led12_off
  bl asm_led14_off

  bl asm_delay

  bl asm_led12_on
  bl asm_led14_on

@  bl delay_func


@
@  # 0xe000e014
@  # 0xe000e018
@  # 0xe000e01c
@
@loop:
@  nop
@  b loop

  movs r3, #3
  movs r5, #5
  @ldr r1, [r0, #4]!

  ldr r0, =stack_frame_a

@  ldr r1, =del_func
@  str r1, [r0, #20] @ setup lr

  ldr r1,=del_func
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_a
  @adr r1, proc_a
  str r1, [r0, #24] @ setup pc
@  mov r1, #0x21000000
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr

@  ldr lr, =#0xfffffff9

@  ldr sp,=#0x20000060
@  ldr sp, [r0, #32]

@  bx lr





  ldr r0, =stack_frame_b

@  ldr r1, =del_func
@  str r1, [r0, #20] @ setup lr

  ldr r1,=del_func
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_b
  str r1, [r0, #24] @ setup pc
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr


  @ldr sp, =stack_frame_a
  @mov r0, #0x20000100
  @ldr sp, [r0, #16]
@  ldr sp,=#0x20000040

#ifdef ENABLE_SYSTICK
@ 0xe000ed24 check systick isr active
@ 0xe000e018 check systick count
  ldr r0, =0xe000e010 @ control reg
  mov r1, #0
  str r1, [r0]
  ldr r1, =0xffffff
  str r1, [r0, #4]
  str r1, [r0, #8]
  mov r1, #0x7
  str r1, [r0] @ enable systick
#else
  svc 0
#endif


deadloop:
  nop
  b deadloop

.type proc_a, function @ let lsb to 1
proc_a:
  movs r0, #1
  bl asm_led12_on
  bl asm_delay
@  bl asm_led12_off
@  bl delay_func
  nop
@  svc 0
  nop
  b proc_a

.type proc_b, function @ let lsb to 1
proc_b:
  movs r1, #2
  bl asm_led14_on
  bl asm_delay
@  bl asm_led14_off
@  bl delay_func
  nop
@  svc 0
  nop
  b proc_b

.type del_func, function @ let lsb to 1
del_func:
  mov r5, #5
  b del_func

int_isr:
  nop
@  ldr sp, =#isr_stack

  bl asm_led12_off
  bl asm_led14_off
  bl asm_delay
  movs r5, #5
  ldr r5, =cur_proc
  ldr r0, [r5]
  cmp r0, #0
  ittee eq
  ldreq sp,=#stack_frame_a
  moveq r1, #1
  ldrne sp,=#stack_frame_b
  movne r1, #0

#if 0
  cmp r0, #0
  it eq
  bleq asm_led14_off

  cmp r0, #0
  it ne
  blne asm_led12_off
@  blne asm_led12_off
#endif

  str r1, [r5]
  mov lr, #0xfffffff9
  bx lr
  #movs pc, proc_a

asm_led12_on:
  mov.w   r3, #3072       
  movt    r3, #16386     
  mov.w   r2, #4096     
  strh    r2, [r3, #24]
  bx lr


asm_led12_off:
  mov.w   r3, #3072      
  movt    r3, #16386    
  mov.w   r2, #4096    
  strh    r2, [r3, #26]
  bx      lr

asm_led14_on:
  mov.w   r3, #3072  
  movt    r3, #16386   
  mov.w   r2, #16384  
  strh    r2, [r3, #24]
  bx      lr

asm_led14_off:
  mov.w   r3, #3072     
  movt    r3, #16386   
  mov.w   r2, #16384  
  strh    r2, [r3, #26]
  bx      lr


asm_delay:
  movs r0, #0x200000
  movs r1, #0

loop:
  adds r1, r0
  subs r0, #1
  bne loop
  bx lr


#.bss
#.section ".stackarea"
.data

sram_begin:
.space  0x40, 0
STACK_TOP:

stack_frame_a:
.word 1 @r0
.word proc_a @r1
.word 3 @r2
.word 0 @r3
.word 0 @r12
.word del_func @lr @ del_func
.word proc_a @pc @ proc_a
.word 0x21000000 @psr

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

.space  0x200, 0
isr_stack:


