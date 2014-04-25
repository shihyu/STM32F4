################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP_132/src/core/dhcp.c \
../App/Common/ethernet/lwIP_132/src/core/dns.c \
../App/Common/ethernet/lwIP_132/src/core/init.c \
../App/Common/ethernet/lwIP_132/src/core/mem.c \
../App/Common/ethernet/lwIP_132/src/core/memp.c \
../App/Common/ethernet/lwIP_132/src/core/netif.c \
../App/Common/ethernet/lwIP_132/src/core/pbuf.c \
../App/Common/ethernet/lwIP_132/src/core/raw.c \
../App/Common/ethernet/lwIP_132/src/core/stats.c \
../App/Common/ethernet/lwIP_132/src/core/sys.c \
../App/Common/ethernet/lwIP_132/src/core/tcp.c \
../App/Common/ethernet/lwIP_132/src/core/tcp_in.c \
../App/Common/ethernet/lwIP_132/src/core/tcp_out.c \
../App/Common/ethernet/lwIP_132/src/core/udp.c 

OBJS += \
./App/Common/ethernet/lwIP_132/src/core/dhcp.o \
./App/Common/ethernet/lwIP_132/src/core/dns.o \
./App/Common/ethernet/lwIP_132/src/core/init.o \
./App/Common/ethernet/lwIP_132/src/core/mem.o \
./App/Common/ethernet/lwIP_132/src/core/memp.o \
./App/Common/ethernet/lwIP_132/src/core/netif.o \
./App/Common/ethernet/lwIP_132/src/core/pbuf.o \
./App/Common/ethernet/lwIP_132/src/core/raw.o \
./App/Common/ethernet/lwIP_132/src/core/stats.o \
./App/Common/ethernet/lwIP_132/src/core/sys.o \
./App/Common/ethernet/lwIP_132/src/core/tcp.o \
./App/Common/ethernet/lwIP_132/src/core/tcp_in.o \
./App/Common/ethernet/lwIP_132/src/core/tcp_out.o \
./App/Common/ethernet/lwIP_132/src/core/udp.o 

C_DEPS += \
./App/Common/ethernet/lwIP_132/src/core/dhcp.d \
./App/Common/ethernet/lwIP_132/src/core/dns.d \
./App/Common/ethernet/lwIP_132/src/core/init.d \
./App/Common/ethernet/lwIP_132/src/core/mem.d \
./App/Common/ethernet/lwIP_132/src/core/memp.d \
./App/Common/ethernet/lwIP_132/src/core/netif.d \
./App/Common/ethernet/lwIP_132/src/core/pbuf.d \
./App/Common/ethernet/lwIP_132/src/core/raw.d \
./App/Common/ethernet/lwIP_132/src/core/stats.d \
./App/Common/ethernet/lwIP_132/src/core/sys.d \
./App/Common/ethernet/lwIP_132/src/core/tcp.d \
./App/Common/ethernet/lwIP_132/src/core/tcp_in.d \
./App/Common/ethernet/lwIP_132/src/core/tcp_out.d \
./App/Common/ethernet/lwIP_132/src/core/udp.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP_132/src/core/%.o: ../App/Common/ethernet/lwIP_132/src/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


