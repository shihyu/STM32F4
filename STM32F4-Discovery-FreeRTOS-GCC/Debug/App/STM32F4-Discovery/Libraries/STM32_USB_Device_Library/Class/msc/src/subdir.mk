################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_bot.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_data.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_msc_scsi.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/usbd_storage_template.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_Device_Library/Class/msc/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


