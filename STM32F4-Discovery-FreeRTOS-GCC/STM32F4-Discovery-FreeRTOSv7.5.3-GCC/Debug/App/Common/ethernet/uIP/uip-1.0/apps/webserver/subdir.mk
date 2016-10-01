################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Common/ethernet/uIP/uip-1.0/apps/webserver/http-strings.c \
../App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-cgi.c \
../App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fs.c \
../App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fsdata.c \
../App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd.c 

OBJS += \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/http-strings.o \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-cgi.o \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fs.o \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fsdata.o \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd.o 

C_DEPS += \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/http-strings.d \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-cgi.d \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fs.d \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd-fsdata.d \
./App/Common/ethernet/uIP/uip-1.0/apps/webserver/httpd.d 


# Each subdirectory must supply rules for building sources it contributes
App/Common/ethernet/uIP/uip-1.0/apps/webserver/%.o: ../App/Common/ethernet/uIP/uip-1.0/apps/webserver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


