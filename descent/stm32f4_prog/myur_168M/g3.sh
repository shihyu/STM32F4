# for stm32f4
#file myur_168M.elf
file proc_periph.elf
b main
# qemu
target remote localhost:1234

# openocd
#target remote localhost:3333

# st-util
#target remote localhost:4242
