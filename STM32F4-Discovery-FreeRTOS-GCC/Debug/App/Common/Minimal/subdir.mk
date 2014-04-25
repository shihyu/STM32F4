################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/Minimal/AltBlckQ.c \
../App/Common/Minimal/AltBlock.c \
../App/Common/Minimal/AltPollQ.c \
../App/Common/Minimal/AltQTest.c \
../App/Common/Minimal/BlockQ.c \
../App/Common/Minimal/GenQTest.c \
../App/Common/Minimal/IntQueue.c \
../App/Common/Minimal/PollQ.c \
../App/Common/Minimal/QPeek.c \
../App/Common/Minimal/QueueOverwrite.c \
../App/Common/Minimal/QueueSet.c \
../App/Common/Minimal/TimerDemo.c \
../App/Common/Minimal/blocktim.c \
../App/Common/Minimal/comtest.c \
../App/Common/Minimal/comtest_strings.c \
../App/Common/Minimal/countsem.c \
../App/Common/Minimal/crflash.c \
../App/Common/Minimal/crhook.c \
../App/Common/Minimal/death.c \
../App/Common/Minimal/dynamic.c \
../App/Common/Minimal/flash.c \
../App/Common/Minimal/flash_timer.c \
../App/Common/Minimal/flop.c \
../App/Common/Minimal/integer.c \
../App/Common/Minimal/recmutex.c \
../App/Common/Minimal/semtest.c \
../App/Common/Minimal/sp_flop.c 

OBJS += \
./App/Common/Minimal/AltBlckQ.o \
./App/Common/Minimal/AltBlock.o \
./App/Common/Minimal/AltPollQ.o \
./App/Common/Minimal/AltQTest.o \
./App/Common/Minimal/BlockQ.o \
./App/Common/Minimal/GenQTest.o \
./App/Common/Minimal/IntQueue.o \
./App/Common/Minimal/PollQ.o \
./App/Common/Minimal/QPeek.o \
./App/Common/Minimal/QueueOverwrite.o \
./App/Common/Minimal/QueueSet.o \
./App/Common/Minimal/TimerDemo.o \
./App/Common/Minimal/blocktim.o \
./App/Common/Minimal/comtest.o \
./App/Common/Minimal/comtest_strings.o \
./App/Common/Minimal/countsem.o \
./App/Common/Minimal/crflash.o \
./App/Common/Minimal/crhook.o \
./App/Common/Minimal/death.o \
./App/Common/Minimal/dynamic.o \
./App/Common/Minimal/flash.o \
./App/Common/Minimal/flash_timer.o \
./App/Common/Minimal/flop.o \
./App/Common/Minimal/integer.o \
./App/Common/Minimal/recmutex.o \
./App/Common/Minimal/semtest.o \
./App/Common/Minimal/sp_flop.o 

C_DEPS += \
./App/Common/Minimal/AltBlckQ.d \
./App/Common/Minimal/AltBlock.d \
./App/Common/Minimal/AltPollQ.d \
./App/Common/Minimal/AltQTest.d \
./App/Common/Minimal/BlockQ.d \
./App/Common/Minimal/GenQTest.d \
./App/Common/Minimal/IntQueue.d \
./App/Common/Minimal/PollQ.d \
./App/Common/Minimal/QPeek.d \
./App/Common/Minimal/QueueOverwrite.d \
./App/Common/Minimal/QueueSet.d \
./App/Common/Minimal/TimerDemo.d \
./App/Common/Minimal/blocktim.d \
./App/Common/Minimal/comtest.d \
./App/Common/Minimal/comtest_strings.d \
./App/Common/Minimal/countsem.d \
./App/Common/Minimal/crflash.d \
./App/Common/Minimal/crhook.d \
./App/Common/Minimal/death.d \
./App/Common/Minimal/dynamic.d \
./App/Common/Minimal/flash.d \
./App/Common/Minimal/flash_timer.d \
./App/Common/Minimal/flop.d \
./App/Common/Minimal/integer.d \
./App/Common/Minimal/recmutex.d \
./App/Common/Minimal/semtest.d \
./App/Common/Minimal/sp_flop.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/Minimal/%.o: ../App/Common/Minimal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


