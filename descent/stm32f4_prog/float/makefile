# another option : -mfloat-abi=softfp

CFLAGS=-g
MYCFLAGS=-fno-common -O0 -g -mcpu=cortex-m3 -mthumb -I../inc
MYCXXFLAGS = -fno-exceptions -fno-rtti
LD_FLAGS=-Wl,-T./stm32.ld -nostartfiles
CXX=arm-none-eabi-g++

CFLAGS += $(MYCFLAGS)
CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS)

float_hard.bin: float_hard.elf
	arm-none-eabi-objcopy -Obinary $< $@

float_hard.elf: float_hard.o k_stdio_hard.o
	$(CXX) $(LD_FLAGS) -o $@ $^

float.bin: float.elf
	arm-none-eabi-objcopy -Obinary $< $@

float.elf: float.o k_stdio.o
	$(CXX) $(LD_FLAGS) -o $@ $^ -lgcc
	#$(CXX) $(LD_FLAGS) -o $@ $^

float.o: float.cpp 
	$(CXX) $(CFLAGS) $(CXXFLAGS) -mfloat-abi=soft -c $<


k_stdio.o: k_stdio.cpp k_stdio.h
	$(CXX) $(CFLAGS) $(CXXFLAGS) -mfloat-abi=soft -c $<

k_stdio_hard.o: k_stdio.cpp k_stdio.h
	$(CXX) $(CFLAGS) $(CXXFLAGS) -mfloat-abi=hard -o $@ -c $<

float_hard.o: float_hard.cpp
	$(CXX) $(CFLAGS) $(CXXFLAGS) -mfloat-abi=hard -c $<

clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean: clean
	find . -type l -exec rm -f {} \;
