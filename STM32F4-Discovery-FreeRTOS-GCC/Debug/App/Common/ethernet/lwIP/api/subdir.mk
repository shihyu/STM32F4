################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/lwIP/api/api_lib.c \
../App/Common/ethernet/lwIP/api/api_msg.c \
../App/Common/ethernet/lwIP/api/err.c \
../App/Common/ethernet/lwIP/api/sockets.c \
../App/Common/ethernet/lwIP/api/tcpip.c 

OBJS += \
./App/Common/ethernet/lwIP/api/api_lib.o \
./App/Common/ethernet/lwIP/api/api_msg.o \
./App/Common/ethernet/lwIP/api/err.o \
./App/Common/ethernet/lwIP/api/sockets.o \
./App/Common/ethernet/lwIP/api/tcpip.o 

C_DEPS += \
./App/Common/ethernet/lwIP/api/api_lib.d \
./App/Common/ethernet/lwIP/api/api_msg.d \
./App/Common/ethernet/lwIP/api/err.d \
./App/Common/ethernet/lwIP/api/sockets.d \
./App/Common/ethernet/lwIP/api/tcpip.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/lwIP/api/%.o: ../App/Common/ethernet/lwIP/api/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


