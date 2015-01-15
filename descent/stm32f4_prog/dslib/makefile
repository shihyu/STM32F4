CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb
MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
INC=-I ../inc

all: libperi.a

libperi.a: lib_mygpio_led.o libur_168M.o share.o
	arm-none-eabi-ar rcs $@ $^
%.o:%.S
	arm-none-eabi-gcc $(MYCFLAGS_NO_LD) $(INC) -c $< 
	#arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

%.o:%.c
	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

clean:
	rm -rf *.o *.a
