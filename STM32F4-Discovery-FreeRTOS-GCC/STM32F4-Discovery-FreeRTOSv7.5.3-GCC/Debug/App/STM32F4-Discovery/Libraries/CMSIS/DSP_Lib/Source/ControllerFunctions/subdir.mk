################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_f32.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q15.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_init_q31.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_f32.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q15.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_pid_reset_q31.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_f32.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/arm_sin_cos_q31.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/%.o: ../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Source/ControllerFunctions/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


