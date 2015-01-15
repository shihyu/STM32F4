CFLAGS=-g
MYCFLAGS=-I.. -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -nodefaultlibs -nostdlib -ffreestanding -nostartfiles
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles -nodefaultlibs -nostdlib -ffreestanding -nostartfiles


all: sample.bin

%.bin:%.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@
%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

%.o:%.c stm32.h
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

sample.elf: sample.o my_setjmp.o exti.o syscfg.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

clean:
	rm -rf *.o *.bin *.elf
