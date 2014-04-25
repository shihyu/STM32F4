################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_mal.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_flash_if.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_mem_if_template.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_otp_if.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_mal.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_flash_if.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_mem_if_template.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_otp_if.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_dfu_mal.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_flash_if.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_mem_if_template.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/usbd_otp_if.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/dfu/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


