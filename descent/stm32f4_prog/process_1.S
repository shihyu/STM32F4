# use save sp to do process switch

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

start:
  ldr r0, =cur_proc
  mov r1, #1
  str r1, [r0]

#if 0
  ldr r0, =cur_proc
  ldr r0, [r0]
  cmp r0, #1
  beq.n 1f
  @ not 1, cur proc is proc_a
  @ save sp to a_sp,
  @ set sp by b_sp

  ldr r1, =a_sp
  str r7, [r1]
  ldr r1, =b_sp
  b 2f

1:
  @ eq 1, cur proc is proc_b, save sp to b_sp,
  @ set sp by a_sp
  ldr r1, =b_sp
  str r7, [r1]
  ldr r1, =a_sp
2:

d:
  b d
#endif


#if 0
  ldr r0, =a_sp
  ldr r1, =#stack_frame_a
  str r1, [r0]

  ldr r0, =b_sp
  ldr r1, =#stack_frame_b
  str r1, [r0]

  ldr r5, =cur_proc
  mov r1, #0
  str r1, [r5]

  movs r3, #3
  movs r5, #5
  @ldr r1, [r0, #4]!

  ldr r0, =stack_frame_a

@  ldr r1, =del_func
@  str r1, [r0, #20] @ setup lr

  ldr r1,=#0xffffffff
  str r1, [r0, #20] @ setup lr

  @ldr r1, =proc_a
  adr r1, proc_a
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

  ldr r1,=#0xffffffff
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_b
  str r1, [r0, #24] @ setup pc
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr


  @ldr sp, =stack_frame_a
  @mov r0, #0x20000100
  @ldr sp, [r0, #16]
@  ldr sp,=#0x20000040
#endif


  ldr r0, =stack_frame_a

  ldr r1,=#0xffffffff
  str r1, [r0, #20] @ setup lr

  ldr r1, =proc_a
  str r1, [r0, #24] @ setup pc
@  mov r1, #0x21000000
  mov r1, #0x1000000
  str r1, [r0, #28] @ setup psr

  ldr r0, =a_sp
  ldr r1, =stack_frame_a
  str r1, [r0]


  svc 0

.type proc_b, function @ let lsb to 1
proc_b:
  movs r1, #2
  nop
  svc 0
  nop
  b proc_b


deadloop:
  b deadloop

.type proc_a, function @ let lsb to 1
proc_a:
  movs r0, #1
  nop
  svc 0
  nop
  b proc_a


.type del_func, function @ let lsb to 1
del_func:
  mov r5, #5
  b del_func

int_isr:
  mov r7, sp @ save cur sp

  ldr r0, =cur_proc
  ldr r1, [r0]
  cmp r1, #1
  beq.n 1f
  @ not 1, cur proc is proc_a
  @ save sp to a_sp,
  @ set sp by b_sp
  @ set cur_proc to 1

  ldr r1, =a_sp
  str r7, [r1]
  ldr r1, =b_sp
  mov r2, #1
  b 2f

1:
  @ eq 1, cur proc is proc_b, save sp to b_sp,
  @ set sp by a_sp
  @ set cur_proc to 0
  ldr r1, =b_sp
  str r7, [r1]
  ldr r1, =a_sp
  mov r2, #0
2:

  str r2, [r0] @ write 1 or 0 to cur_proC

  ldr sp, [r1]
@  mov sp, r1
  bx lr
  #movs pc, proc_a


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

a_sp:
.word 0
b_sp:
.word 0

.space  0x100, 0
STACK_TOP:
