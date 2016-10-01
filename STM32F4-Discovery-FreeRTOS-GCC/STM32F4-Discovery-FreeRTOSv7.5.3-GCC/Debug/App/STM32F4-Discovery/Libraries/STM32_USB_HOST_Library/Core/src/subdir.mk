################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_hcs.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_ioreq.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_stdreq.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_hcs.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_ioreq.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_stdreq.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_hcs.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_ioreq.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/usbh_stdreq.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Core/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


