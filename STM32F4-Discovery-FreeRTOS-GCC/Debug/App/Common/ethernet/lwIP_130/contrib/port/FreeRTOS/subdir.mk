################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP_130/contrib/port/FreeRTOS/sys_arch.c 

OBJS += \
./App/Common/ethernet/lwIP_130/contrib/port/FreeRTOS/sys_arch.o 

C_DEPS += \
./App/Common/ethernet/lwIP_130/contrib/port/FreeRTOS/sys_arch.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP_130/contrib/port/FreeRTOS/%.o: ../App/Common/ethernet/lwIP_130/contrib/port/FreeRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


