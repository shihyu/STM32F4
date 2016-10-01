################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_bot.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_fatfs.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_scsi.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_bot.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_fatfs.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_scsi.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_bot.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_fatfs.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/usbh_msc_scsi.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_HOST_Library/Class/MSC/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


