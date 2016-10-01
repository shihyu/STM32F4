################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/drivers/Atmel/at91lib/peripherals/ac97c/ac97c.c 

OBJS += \
./App/Common/drivers/Atmel/at91lib/peripherals/ac97c/ac97c.o 

C_DEPS += \
./App/Common/drivers/Atmel/at91lib/peripherals/ac97c/ac97c.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/drivers/Atmel/at91lib/peripherals/ac97c/%.o: ../App/Common/drivers/Atmel/at91lib/peripherals/ac97c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


