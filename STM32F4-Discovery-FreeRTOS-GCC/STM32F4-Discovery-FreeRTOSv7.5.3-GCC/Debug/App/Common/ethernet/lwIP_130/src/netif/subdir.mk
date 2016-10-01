################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP_130/src/netif/etharp.c \
../App/Common/ethernet/lwIP_130/src/netif/ethernetif.c \
../App/Common/ethernet/lwIP_130/src/netif/loopif.c \
../App/Common/ethernet/lwIP_130/src/netif/slipif.c \
../App/Common/ethernet/lwIP_130/src/netif/stf91x_ethernetif.c 

OBJS += \
./App/Common/ethernet/lwIP_130/src/netif/etharp.o \
./App/Common/ethernet/lwIP_130/src/netif/ethernetif.o \
./App/Common/ethernet/lwIP_130/src/netif/loopif.o \
./App/Common/ethernet/lwIP_130/src/netif/slipif.o \
./App/Common/ethernet/lwIP_130/src/netif/stf91x_ethernetif.o 

C_DEPS += \
./App/Common/ethernet/lwIP_130/src/netif/etharp.d \
./App/Common/ethernet/lwIP_130/src/netif/ethernetif.d \
./App/Common/ethernet/lwIP_130/src/netif/loopif.d \
./App/Common/ethernet/lwIP_130/src/netif/slipif.d \
./App/Common/ethernet/lwIP_130/src/netif/stf91x_ethernetif.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP_130/src/netif/%.o: ../App/Common/ethernet/lwIP_130/src/netif/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


