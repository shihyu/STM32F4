# test svc software interrupt
# ref : http://tw.m.wretch.yahoo.com/blog/DreamYeh/888788
# comment: #, @

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
  ldr r0, =stack_frame_a

  ldr r1,=#0xfffffff9
  str r1, [r0, #20] @ setup lr

  adr r1, proc_a
  str r1, [r0, #24] @ setup pc
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr

  @@@@@@@@@@@@@@@@@@@@@

  ldr r0, =stack_frame_b

  ldr r1,=#0xfffffff9
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_b
  str r1, [r0, #24] @ setup pc
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr

  @@@@@@@@@@@@@@@@@@@@@
  ldr r5, =cur_proc
  mov r1, #0
  str r1, [r5]

  svc 0

deadloop:
  b deadloop

.type proc_a, function @ let lsb to 1
proc_a:
  movs r0, #1
  svc 0
  nop
  b proc_a

.type proc_b, function @ let lsb to 1
proc_b:
  movs r1, #2
  nop
  svc 0
  b proc_b

int_isr:
  movs r5, #5
  ldr r5, =cur_proc
  ldr r0, [r5]
  cmp r0, #0
  ittee eq
  ldreq sp,=#stack_frame_a
  moveq r1, #1
  ldrne sp,=#stack_frame_b
  movne r1, #0

  str r1, [r5]
  bx lr
.data

stack_frame_a:
.word 9 @r0
.word 8 @r1
.word 7 @r2
.word 6 @r3
.word 5 @r12
.word 4 @lr 
.word 3 @pc @ proc_a
.word 2 @psr

stack_frame_b:
.word 1 @r0
.word 2 @r1
.word 3 @r2
.word 4 @r3
.word 5 @r12
.word 6 @lr
.word 7 @pc
.word 8 @psr

cur_proc:
.word 1
