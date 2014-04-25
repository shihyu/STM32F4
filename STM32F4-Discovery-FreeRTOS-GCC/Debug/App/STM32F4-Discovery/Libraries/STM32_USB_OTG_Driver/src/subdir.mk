################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_bsp_template.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_core.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd_int.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd_int.c \
../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_otg.c 

OBJS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_bsp_template.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_core.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd_int.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd_int.o \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_otg.o 

C_DEPS += \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_bsp_template.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_core.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_dcd_int.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_hcd_int.d \
./App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/usb_otg.d 


# Each subdirectory must supply rules for building sources it contributes
App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/%.o: ../App/STM32F4-Discovery/Libraries/STM32_USB_OTG_Driver/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


