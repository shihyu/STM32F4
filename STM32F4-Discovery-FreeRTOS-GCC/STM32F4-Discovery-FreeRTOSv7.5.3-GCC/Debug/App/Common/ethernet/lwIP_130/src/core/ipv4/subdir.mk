################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP_130/src/core/ipv4/autoip.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/icmp.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/igmp.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/inet.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/inet_chksum.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/ip.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/ip_addr.c \
../App/Common/ethernet/lwIP_130/src/core/ipv4/ip_frag.c 

OBJS += \
./App/Common/ethernet/lwIP_130/src/core/ipv4/autoip.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/icmp.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/igmp.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/inet.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/inet_chksum.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip_addr.o \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip_frag.o 

C_DEPS += \
./App/Common/ethernet/lwIP_130/src/core/ipv4/autoip.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/icmp.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/igmp.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/inet.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/inet_chksum.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip_addr.d \
./App/Common/ethernet/lwIP_130/src/core/ipv4/ip_frag.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP_130/src/core/ipv4/%.o: ../App/Common/ethernet/lwIP_130/src/core/ipv4/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


