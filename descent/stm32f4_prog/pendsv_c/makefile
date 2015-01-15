CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
INC=-I ../inc

all: pendsv.bin

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

pendsv.o: pendsv.c stm32.h ../inc/lib_mygpio_led.h \
 ../inc/stm32f4xx_gpio.h ../inc/stm32f4xx.h ../inc/core_cm4.h \
  ../inc/core_cmInstr.h ../inc/core_cmFunc.h ../inc/core_cm4_simd.h

pendsv.elf: pendsv.o ../dslib/libperi.a
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

%.bin:%.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

clean:
	rm -rf *.o *.bin *.elf
