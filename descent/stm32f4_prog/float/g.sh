# for qemu
#file user_button.elf
file float.elf
b _start
#b WinMain
#b exti0_isr
target remote localhost:1234
