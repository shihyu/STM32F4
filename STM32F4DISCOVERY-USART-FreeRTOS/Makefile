# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
# 

OPT = 0

# Object files directory
# Warning: this will be removed by make clean!
#
OBJDIR = obj

# Target file name (without extension)
TARGET = $(OBJDIR)/STM32F4_Test

# Define all C source files (dependencies are generated automatically)
#
SOURCES += src/uart.c
SOURCES += src/ustime.c
SOURCES += src/main.c
SOURCES += src/startup_stm32f4xx.s
SOURCES += src/system_stm32f4xx.c
SOURCES += src/syscalls.c
SOURCES += src/modbus.c
SOURCES += src/test.c

SOURCES += FreeRTOS/Source/tasks.c
SOURCES += FreeRTOS/Source/queue.c
SOURCES += FreeRTOS/Source/list.c
SOURCES += FreeRTOS/Source/croutine.c
SOURCES += FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/misc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
SOURCES += libs/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

OBJECTS  = $(addprefix $(OBJDIR)/,$(addsuffix .o,$(basename $(SOURCES))))

# Place -D, -U or -I options here for C and C++ sources
CPPFLAGS += -Isrc
CPPFLAGS += -IFreeRTOS/Source/include
CPPFLAGS += -Ilibs/CMSIS/Include
CPPFLAGS += -Ilibs/Device/STM32F4xx/Include
CPPFLAGS += -Ilibs/STM32F4xx_StdPeriph_Driver/inc

#---------------- Compiler Options C ----------------
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
CFLAGS  = -O$(OPT)
CFLAGS += -std=gnu99
CFLAGS += -gdwarf-2
CFLAGS += -ffunction-sections
CFLAGS += -fdata-sections
CFLAGS += -Wall
#CFLAGS += -Wextra
#CFLAGS += -Wpointer-arith
#CFLAGS += -Wstrict-prototypes
#CFLAGS += -Winline
#CFLAGS += -Wunreachable-code
#CFLAGS += -Wundef
CFLAGS += -Wa,-adhlns=$(OBJDIR)/$(*F).lst

# Optimize use of the single-precision FPU
#
CFLAGS += -fsingle-precision-constant

# This will not work without recompiling libs
#
# CFLAGS += -fshort-double

#---------------- Compiler Options C++ ----------------
#
CXXFLAGS  = $(CFLAGS)

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler
#  -adhlns:   create listing
#
ASFLAGS = -Wa,-adhlns=$(OBJDIR)/$(*F).lst


#---------------- Linker Options ----------------
#  -Wl,...:     tell GCC to pass this to linker
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS += -lm
LDFLAGS += -Wl,-Map=$(TARGET).map,--cref
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Tsrc/stm32_flash.ld

#============================================================================


# Define programs and commands
TOOLCHAIN = arm-none-eabi
CC        = $(TOOLCHAIN)-gcc
OBJCOPY   = $(TOOLCHAIN)-objcopy
OBJDUMP   = $(TOOLCHAIN)-objdump
SIZE      = $(TOOLCHAIN)-size
NM        = $(TOOLCHAIN)-nm
OPENOCD   = openocd
DOXYGEN   = doxygen
STLINK    = tools/ST-LINK_CLI.exe


ifeq (AMD64, $(PROCESSOR_ARCHITEW6432))
  SUBWCREV = tools/SubWCRev64.exe
else
  SUBWCREV = tools/SubWCRev.exe
endif


# Compiler flags to generate dependency files
GENDEPFLAGS = -MMD -MP -MF $(OBJDIR)/$(*F).d


# Combine all necessary flags and optional flags
# Add target processor to flags.
#
#CPU = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft
#CPU = -mcpu=cortex-m4 -mthumb 
#

CPU = -mcpu=cortex-m4 -mthumb -mfloat-abi=softfp -mfpu=fpv4-sp-d16

CFLAGS   += $(CPU)
CXXFLAGS += $(CPU)
ASFLAGS  += $(CPU)
LDFLAGS  += $(CPU)

# Default target.
all:  gccversion build showsize

build: elf hex lss sym bin

elf: $(TARGET).elf
hex: $(TARGET).hex
bin: $(TARGET).bin
lss: $(TARGET).lss
sym: $(TARGET).sym


doxygen:
	@echo
	@echo Creating Doxygen documentation
	@$(DOXYGEN)

# Display compiler version information
gccversion: 
	@$(CC) --version


# Show the final program size
showsize: elf
	@echo
	@$(SIZE) $(TARGET).elf 2>/dev/null


# Flash the device  
flash: hex
#	$(OPENOCD) -f "openocd.cfg" -c "flash_image $(TARGET).elf; shutdown"
	$(STLINK) -c SWD -P $(TARGET).hex -Run


# Target: clean project
clean:
	@echo Cleaning project:
	rm -rf $(OBJDIR)
	rm -rf docs/html


# Create extended listing file from ELF output file
%.lss: %.elf
	@echo
	@echo Creating Extended Listing: $@
	$(OBJDUMP) -h -S -z $< > $@


# Create a symbol table from ELF output file
%.sym: %.elf
	@echo
	@echo Creating Symbol Table: $@
	$(NM) -n $< > $@


# Link: create ELF output file from object files
.SECONDARY: $(TARGET).elf
.PRECIOUS:  $(OBJECTS)
$(TARGET).elf: $(OBJECTS)
	@echo
	@echo Linking: $@
	$(CC) $^ $(LDFLAGS) --output $@ 


# Create final output files (.hex, .eep) from ELF output file.
%.hex: %.elf
	@echo
	@echo Creating hex file: $@
	$(OBJCOPY) -O ihex $< $@

# Create bin file :
%.bin: %.elf
	@echo
	@echo Creating bin file: $@
	$(OBJCOPY) -O binary $< $@


# Compile: create object files from C source files
$(OBJDIR)/%.o : %.c
	@echo
	@echo Compiling C: $<
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $(GENDEPFLAGS) $< -o $@ 


# Compile: create object files from C++ source files
$(OBJDIR)/%.o : %.cpp
	@echo
	@echo Compiling CPP: $<
	$(CC) -c $(CPPFLAGS) $(CXXFLAGS) $(GENDEPFLAGS) $< -o $@ 


# Assemble: create object files from assembler source files
$(OBJDIR)/%.o : %.s
	@echo
	@echo Assembling: $<
	$(CC) -c $(CPPFLAGS) $(ASFLAGS) $< -o $@


# Create object file directories
$(shell mkdir -p $(OBJDIR) 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/src 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/FreeRTOS/Source/ 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/FreeRTOS/Source/portable/GCC/ARM_CM4F 2>/dev/null)
$(shell mkdir -p $(OBJDIR)/libs/STM32F4xx_StdPeriph_Driver/src 2>/dev/null)

# Include the dependency files
-include $(wildcard $(OBJDIR)/*.d)


# Listing of phony targets
.PHONY: all build flash clean \
        doxygen elf lss sym \
        showsize gccversion
