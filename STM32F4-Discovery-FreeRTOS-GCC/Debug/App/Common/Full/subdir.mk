################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/Full/BlockQ.c \
../App/Common/Full/PollQ.c \
../App/Common/Full/comtest.c \
../App/Common/Full/death.c \
../App/Common/Full/dynamic.c \
../App/Common/Full/events.c \
../App/Common/Full/flash.c \
../App/Common/Full/flop.c \
../App/Common/Full/integer.c \
../App/Common/Full/print.c \
../App/Common/Full/semtest.c 

OBJS += \
./App/Common/Full/BlockQ.o \
./App/Common/Full/PollQ.o \
./App/Common/Full/comtest.o \
./App/Common/Full/death.o \
./App/Common/Full/dynamic.o \
./App/Common/Full/events.o \
./App/Common/Full/flash.o \
./App/Common/Full/flop.o \
./App/Common/Full/integer.o \
./App/Common/Full/print.o \
./App/Common/Full/semtest.o 

C_DEPS += \
./App/Common/Full/BlockQ.d \
./App/Common/Full/PollQ.d \
./App/Common/Full/comtest.d \
./App/Common/Full/death.d \
./App/Common/Full/dynamic.d \
./App/Common/Full/events.d \
./App/Common/Full/flash.d \
./App/Common/Full/flop.d \
./App/Common/Full/integer.d \
./App/Common/Full/print.d \
./App/Common/Full/semtest.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/Full/%.o: ../App/Common/Full/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


