################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/CommonTables/arm_common_tables.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/CommonTables/%.o: ../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/CommonTables/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


