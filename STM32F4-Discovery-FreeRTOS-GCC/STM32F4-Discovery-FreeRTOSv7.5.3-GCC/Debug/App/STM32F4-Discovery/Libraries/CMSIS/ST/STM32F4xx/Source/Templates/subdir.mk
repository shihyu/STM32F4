################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/%.o: ../App/STM32F4-Discovery/Libraries/CMSIS/ST/STM32F4xx/Source/Templates/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


