CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -std=c99
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
INC=-I ../../inc

all: cs.bin

%.bin:%.elf
	arm-none-eabi-objcopy -O binary $< $@

cs.elf: asm_func.o cs.o stm32.o ../../dslib/libperi.a
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 
cs.o: cs.c stm32.h

clean:
	rm -rf *.o *.bin *.elf
