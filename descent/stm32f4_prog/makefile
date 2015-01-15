CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

all: pendsv_c.bin

%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 
	#arm-none-eabi-gcc $(MYCFLAGS_NO_LD) $(INC) -c $< 

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

user_button.elf: user_button.o exti.o syscfg.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

systick.elf: systick.o 
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

pendsv_c.o: stm32.h lib_mygpio_led.h

pendsv_c.elf: pendsv_c.o lib_mygpio_led.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

%.bin:%.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

pendsv.elf: pendsv.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^

process_1.bin: process_1.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@
process_1.elf: process_1.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -o $@ $<
process_1.o: process_1.S
	#arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	arm-none-eabi-gcc -nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -c $< 

two_stack.bin: two_stack.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

two_stack.elf: two_stack.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^
two_stack.o: two_stack.S
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

myc.bin: myc.elf
	arm-none-eabi-objcopy -Obinary $< $@
myc.elf: myc.o
	arm-none-eabi-gcc $(LD_FLAGS) $(INC) -o $@ $< 

proc_periph.bin: proc_periph.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@

proc_periph.elf: proc_periph.o gpio_led.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -Tbss 0x20000100 -o $@ $^

proc_periph.o: proc_periph.S
	#arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

gpio_led.o: gpio_led.c gpio_led.h
	arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c $<


myur_led.bin: myur_led.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur_led.elf: myur_led.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -o $@ $< 

process.bin: process.elf
	arm-none-eabi-objcopy -R .data -O binary $< $@
process.elf: process.o
	arm-none-eabi-ld -Ttext 0x0 -Tdata 0x20000000 -o $@ $<
process.o: process.S
	arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<

myur.bin: myur.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur.elf: myur.o
	arm-none-eabi-gcc $(LD_FLAGS) -o $@ $^

factorial.bin: factorial.elf
	arm-none-eabi-objcopy -O binary $< $@

factorial.elf: factorial.o
	arm-none-eabi-ld -Ttext 0x0 -o $@ $<
	
factorial.o: factorial.S
	arm-none-eabi-as -g -mcpu=cortex-m3 -mthumb -o $@ $<
	#arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c hello.c

hello.bin: hello.elf
	arm-none-eabi-objcopy -O binary hello.elf hello.bin

hello.o: hello.c stm32.h
	arm-none-eabi-gcc $(CFLAGS) -mcpu=cortex-m3 -mthumb -nostartfiles -c hello.c

hello.elf: hello.o
	arm-none-eabi-ld -T stm32.ld -o hello.elf hello.o

mygpio_led.bin: mygpio_led.elf
	arm-none-eabi-objcopy -Obinary $< $@
mygpio_led.elf: mygpio_led.c
	arm-none-eabi-gcc $(LD_FLAGS) $(INC) -o $@ $< 
clean:
	rm -rf *.o *.bin *.elf
