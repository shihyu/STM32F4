################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/FreeTCPIP/psock.c \
../App/Common/ethernet/FreeTCPIP/timer.c \
../App/Common/ethernet/FreeTCPIP/uip.c \
../App/Common/ethernet/FreeTCPIP/uip_arp.c 

OBJS += \
./App/Common/ethernet/FreeTCPIP/psock.o \
./App/Common/ethernet/FreeTCPIP/timer.o \
./App/Common/ethernet/FreeTCPIP/uip.o \
./App/Common/ethernet/FreeTCPIP/uip_arp.o 

C_DEPS += \
./App/Common/ethernet/FreeTCPIP/psock.d \
./App/Common/ethernet/FreeTCPIP/timer.d \
./App/Common/ethernet/FreeTCPIP/uip.d \
./App/Common/ethernet/FreeTCPIP/uip_arp.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/FreeTCPIP/%.o: ../App/Common/ethernet/FreeTCPIP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


