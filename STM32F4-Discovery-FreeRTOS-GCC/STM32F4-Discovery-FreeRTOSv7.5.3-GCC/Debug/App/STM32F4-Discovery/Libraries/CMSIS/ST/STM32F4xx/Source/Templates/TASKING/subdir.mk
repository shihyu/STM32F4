################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TASKING/cstart_thumb2.asm 

OBJS += \
./App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TASKING/cstart_thumb2.o 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TASKING/%.o: ../App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/TASKING/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


