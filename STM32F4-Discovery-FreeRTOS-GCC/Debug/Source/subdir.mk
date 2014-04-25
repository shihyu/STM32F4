################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/croutine.c \
../Source/list.c \
../Source/queue.c \
../Source/tasks.c \
../Source/timers.c 

OBJS += \
./Source/croutine.o \
./Source/list.o \
./Source/queue.o \
./Source/tasks.o \
./Source/timers.o 

C_DEPS += \
./Source/croutine.d \
./Source/list.d \
./Source/queue.d \
./Source/tasks.d \
./Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Source/%.o: ../Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


