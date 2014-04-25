################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwip-1.4.0/ports/win32/WinPCap/arch.c 

OBJS += \
./App/Common/ethernet/lwip-1.4.0/ports/win32/WinPCap/arch.o 

C_DEPS += \
./App/Common/ethernet/lwip-1.4.0/ports/win32/WinPCap/arch.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwip-1.4.0/ports/win32/WinPCap/%.o: ../App/Common/ethernet/lwip-1.4.0/ports/win32/WinPCap/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


