################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP_130/src/api/api_lib.c \
../App/Common/ethernet/lwIP_130/src/api/api_msg.c \
../App/Common/ethernet/lwIP_130/src/api/err.c \
../App/Common/ethernet/lwIP_130/src/api/netbuf.c \
../App/Common/ethernet/lwIP_130/src/api/netdb.c \
../App/Common/ethernet/lwIP_130/src/api/netifapi.c \
../App/Common/ethernet/lwIP_130/src/api/sockets.c \
../App/Common/ethernet/lwIP_130/src/api/tcpip.c 

OBJS += \
./App/Common/ethernet/lwIP_130/src/api/api_lib.o \
./App/Common/ethernet/lwIP_130/src/api/api_msg.o \
./App/Common/ethernet/lwIP_130/src/api/err.o \
./App/Common/ethernet/lwIP_130/src/api/netbuf.o \
./App/Common/ethernet/lwIP_130/src/api/netdb.o \
./App/Common/ethernet/lwIP_130/src/api/netifapi.o \
./App/Common/ethernet/lwIP_130/src/api/sockets.o \
./App/Common/ethernet/lwIP_130/src/api/tcpip.o 

C_DEPS += \
./App/Common/ethernet/lwIP_130/src/api/api_lib.d \
./App/Common/ethernet/lwIP_130/src/api/api_msg.d \
./App/Common/ethernet/lwIP_130/src/api/err.d \
./App/Common/ethernet/lwIP_130/src/api/netbuf.d \
./App/Common/ethernet/lwIP_130/src/api/netdb.d \
./App/Common/ethernet/lwIP_130/src/api/netifapi.d \
./App/Common/ethernet/lwIP_130/src/api/sockets.d \
./App/Common/ethernet/lwIP_130/src/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP_130/src/api/%.o: ../App/Common/ethernet/lwIP_130/src/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


