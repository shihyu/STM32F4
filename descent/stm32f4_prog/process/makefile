CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

all: process_2.bin

%.bin:%.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

process_2.elf: process_2.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^
clean:
	rm -rf *.o *.bin *.elf
