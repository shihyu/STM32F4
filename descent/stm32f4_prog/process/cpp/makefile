CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -std=c++11 -fno-exceptions -fno-rtti -ffreestanding
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles -ffreestanding
INC=-I ../../inc

CXX=arm-none-eabi-g++

all: cs.bin

%.bin:%.elf
	arm-none-eabi-objcopy -O binary $< $@

OBJS = asm_func.o cs.o stm32.o asm_syscall.o syscall.o process.o

cs.elf: $(OBJS) dslib/libperi.a
	$(CXX) $(LD_FLAGS) -o $@ $^

dslib/libperi.a: 
	(cd dslib;make)
%.o:%.S
	$(CXX) $(MYCFLAGS) $(INC) -c $< 

%.o:%.cpp
	$(CXX) $(MYCFLAGS) $(INC) -c $< 
cs.o: cs.cpp stm32.h

process.o: process.cpp process.h
	$(CXX) $(MYCFLAGS) $(INC) -c $< 

clean:
	rm -rf *.bin *.elf dslib/libperi.a ; find . -name  "*.o" -exec rm -f {} \;
