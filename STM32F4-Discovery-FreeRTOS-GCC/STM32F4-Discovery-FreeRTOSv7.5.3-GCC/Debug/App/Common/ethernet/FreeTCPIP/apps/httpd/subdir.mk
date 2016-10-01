################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/FreeTCPIP/apps/httpd/http-strings.c \
../App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-cgi.c \
../App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-fs.c \
../App/Common/ethernet/FreeTCPIP/apps/httpd/httpd.c 

OBJS += \
./App/Common/ethernet/FreeTCPIP/apps/httpd/http-strings.o \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-cgi.o \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-fs.o \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd.o 

C_DEPS += \
./App/Common/ethernet/FreeTCPIP/apps/httpd/http-strings.d \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-cgi.d \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd-fs.d \
./App/Common/ethernet/FreeTCPIP/apps/httpd/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/FreeTCPIP/apps/httpd/%.o: ../App/Common/ethernet/FreeTCPIP/apps/httpd/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


