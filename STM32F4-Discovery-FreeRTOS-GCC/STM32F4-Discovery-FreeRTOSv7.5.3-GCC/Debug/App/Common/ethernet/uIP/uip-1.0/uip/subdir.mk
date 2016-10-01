################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/uIP/uip-1.0/uip/psock.c \
../App/Common/ethernet/uIP/uip-1.0/uip/timer.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uip-fw.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uip-neighbor.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uip-split.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uip.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uip_arp.c \
../App/Common/ethernet/uIP/uip-1.0/uip/uiplib.c 

OBJS += \
./App/Common/ethernet/uIP/uip-1.0/uip/psock.o \
./App/Common/ethernet/uIP/uip-1.0/uip/timer.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-fw.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-neighbor.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-split.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uip.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uip_arp.o \
./App/Common/ethernet/uIP/uip-1.0/uip/uiplib.o 

C_DEPS += \
./App/Common/ethernet/uIP/uip-1.0/uip/psock.d \
./App/Common/ethernet/uIP/uip-1.0/uip/timer.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-fw.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-neighbor.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uip-split.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uip.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uip_arp.d \
./App/Common/ethernet/uIP/uip-1.0/uip/uiplib.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/uIP/uip-1.0/uip/%.o: ../App/Common/ethernet/uIP/uip-1.0/uip/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


