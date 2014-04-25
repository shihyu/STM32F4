################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/portable/MemMang/heap_1.c \
../Source/portable/MemMang/heap_2.c \
../Source/portable/MemMang/heap_3.c \
../Source/portable/MemMang/heap_4.c 

OBJS += \
./Source/portable/MemMang/heap_1.o \
./Source/portable/MemMang/heap_2.o \
./Source/portable/MemMang/heap_3.o \
./Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Source/portable/MemMang/heap_1.d \
./Source/portable/MemMang/heap_2.d \
./Source/portable/MemMang/heap_3.d \
./Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Source/portable/MemMang/%.o: ../Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


