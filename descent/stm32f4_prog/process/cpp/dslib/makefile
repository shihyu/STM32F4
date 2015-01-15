CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -fno-exceptions -fno-rtti -std=c++11
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
INC=-I ../../../inc
CXX=arm-none-eabi-g++

all: libperi.a

libperi.a: lib_mygpio_led.o libur_168M.o share.o
	arm-none-eabi-ar rcs $@ $^
%.o:%.S
	$(CXX) $(MYCFLAGS) $(INC) -c $< 

%.o:%.cpp
	$(CXX) $(MYCFLAGS) $(INC) -c $< 

clean:
	rm -rf *.o *.a
