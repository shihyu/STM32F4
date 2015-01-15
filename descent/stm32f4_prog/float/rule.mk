CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../inc -mfloat-abi=soft
MYCXXFLAGS = -fno-exceptions -fno-rtti
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
CXX=arm-none-eabi-g++
%.dpp: %.cpp
	set -e; rm -f $@ ; $(CXX) -MM $(MYCFLAGS) $< > $@.$$$$ ; sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@ ; rm -f $@.$$$$

