################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/arm_class_marks_example_f32.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM0.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM3.c \
../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM4.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/arm_class_marks_example_f32.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM0.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM3.o \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM4.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/arm_class_marks_example_f32.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM0.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM3.d \
./App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/system_ARMCM4.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/%.o: ../App/STM32F4-Discovery/Libraries/CMSIS/DSP_Lib/Examples/arm_class_marks_example/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


