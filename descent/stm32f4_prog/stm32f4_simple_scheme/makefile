include rule.mk

# make STACK_REG=1 will go -finstrument-functions
ifndef STACK_REG
CFLAGS += $(MYCFLAGS)
else
# only for -finstrument-functions
CFLAGS += $(MYCFLAGS) -DSP_STATUS -finstrument-functions
endif

CXXFLAGS += $(MYCXXFLAGS) $(CFLAGS)



myur.bin: myur.elf
	arm-none-eabi-objcopy -Obinary $< $@
myur.elf: myur.o cell.o  s_eval.o  token_container.o k_stdio.o cstring.o
	$(CXX) $(LD_FLAGS) -o $@ $^

sources = cell.cpp  k_stdio.cpp  myur.cpp  s_eval.cpp  token_container.cpp gdeque.cpp cstring.cpp

include $(sources:.cpp=.dpp)

# useless MYCFLAGS_NO_LD=-nostartfiles -fno-common -O0 -g -mcpu=cortex-m3 -mthumb


#%.o:%.S
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 

#%.o:%.c
#	arm-none-eabi-gcc $(MYCFLAGS) $(INC) -c $< 




	
clean:
	rm -rf *.o *.elf *.bin *.dpp *.dpp.*
distclean: clean
	find . -type l -exec rm -f {} \;
