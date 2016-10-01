################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/ParTest.c \
../App/STM32F4-Discovery/main.c \
../App/STM32F4-Discovery/stm32f4xx_it.c 

OBJS += \
./App/STM32F4-Discovery/ParTest.o \
./App/STM32F4-Discovery/main.o \
./App/STM32F4-Discovery/stm32f4xx_it.o 

C_DEPS += \
./App/STM32F4-Discovery/ParTest.d \
./App/STM32F4-Discovery/main.d \
./App/STM32F4-Discovery/stm32f4xx_it.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/%.o: ../App/STM32F4-Discovery/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


