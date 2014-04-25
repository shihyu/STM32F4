################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwip-1.4.0/src/core/ipv6/icmp6.c \
../App/Common/ethernet/lwip-1.4.0/src/core/ipv6/inet6.c \
../App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6.c \
../App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6_addr.c 

OBJS += \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/icmp6.o \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/inet6.o \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6.o \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6_addr.o 

C_DEPS += \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/icmp6.d \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/inet6.d \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6.d \
./App/Common/ethernet/lwip-1.4.0/src/core/ipv6/ip6_addr.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwip-1.4.0/src/core/ipv6/%.o: ../App/Common/ethernet/lwip-1.4.0/src/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


