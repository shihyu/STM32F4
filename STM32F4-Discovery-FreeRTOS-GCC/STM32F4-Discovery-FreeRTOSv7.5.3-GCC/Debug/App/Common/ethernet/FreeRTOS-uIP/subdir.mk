################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/FreeRTOS-uIP/psock.c \
../App/Common/ethernet/FreeRTOS-uIP/timer.c \
../App/Common/ethernet/FreeRTOS-uIP/uip-split.c \
../App/Common/ethernet/FreeRTOS-uIP/uip.c \
../App/Common/ethernet/FreeRTOS-uIP/uip_arp.c \
../App/Common/ethernet/FreeRTOS-uIP/uiplib.c 

OBJS += \
./App/Common/ethernet/FreeRTOS-uIP/psock.o \
./App/Common/ethernet/FreeRTOS-uIP/timer.o \
./App/Common/ethernet/FreeRTOS-uIP/uip-split.o \
./App/Common/ethernet/FreeRTOS-uIP/uip.o \
./App/Common/ethernet/FreeRTOS-uIP/uip_arp.o \
./App/Common/ethernet/FreeRTOS-uIP/uiplib.o 

C_DEPS += \
./App/Common/ethernet/FreeRTOS-uIP/psock.d \
./App/Common/ethernet/FreeRTOS-uIP/timer.d \
./App/Common/ethernet/FreeRTOS-uIP/uip-split.d \
./App/Common/ethernet/FreeRTOS-uIP/uip.d \
./App/Common/ethernet/FreeRTOS-uIP/uip_arp.d \
./App/Common/ethernet/FreeRTOS-uIP/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/FreeRTOS-uIP/%.o: ../App/Common/ethernet/FreeRTOS-uIP/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


