CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -fno-exceptions -fno-rtti
MYCFLAGS_NO_LD=-nostartfiles -ffreestanding -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles

all: mycpp.bin

myp.elf: myp.o
	arm-none-eabi-g++ $(LD_FLAGS) -Wl,-Map,$@.map -o $@ $^

%.o:%.S
	arm-none-eabi-g++ $(MYCFLAGS) $(INC) -c $< 

%.o:%.cpp
	arm-none-eabi-g++ $(MYCFLAGS) $(INC) -c $< 

mycpp.o: mycpp.cpp stm32.h

mycpp.elf: mycpp.o
	arm-none-eabi-g++ $(LD_FLAGS) -o $@ $^

%.bin:%.elf
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf *.o *.bin *.elf
