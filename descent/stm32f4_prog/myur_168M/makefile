CFLAGS=-g
MYCFLAGS=-Wl,-T./stm32.ld -nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
#MYCFLAGS=-Wl,-T./stm32.ld -g -O2 -mlittle-endian -mthumb -mcpu=cortex-m4 -ffreestanding -nostdlib 

CFLAGS=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb

proc_periph.bin: proc_periph.elf
	arm-none-eabi-objcopy -O binary $< $@

proc_periph.elf: ur.o proc_periph.o
	arm-none-eabi-ld -Tstm32.ld -o $@ $^

proc_periph.o: proc_periph.S
	arm-none-eabi-gcc $(CFLAGS) $(INC) -c $< 

ur.o: ur.c stm32.h
	arm-none-eabi-gcc $(CFLAGS) $(INC) -c $< 

ur.s: ur.c
	arm-none-eabi-gcc $(CFLAGS) $(INC) -S $< 

myur_168M.o: myur_168M.c
	arm-none-eabi-gcc $(CFLAGS) $(INC) -c $< 

myur_168M.bin: myur_168M.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur_168M.elf: myur_168M.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -o $@ $< 

clean:
	rm -rf *.o *.bin *.elf
