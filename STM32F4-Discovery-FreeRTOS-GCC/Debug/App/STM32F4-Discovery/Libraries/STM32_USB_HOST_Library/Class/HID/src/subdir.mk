################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_keybd.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_mouse.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_keybd.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_mouse.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_keybd.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/usbh_hid_mouse.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/HID/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


