################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/pwr.c \
../src/uart.c \
../src/uart_sleep.c 

SRC_OBJS += \
./src/pwr.o \
./src/uart.o \
./src/uart_sleep.o 

C_DEPS += \
./src/pwr.d \
./src/uart.d \
./src/uart_sleep.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: CrossCore GCC ARM Embedded C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -ffunction-sections -fdata-sections -DCORE0 -D_DEBUG -D_RTE_ -D__ADUCM3029__ -D__SILICON_REVISION__=0x100 @includes-b6408f0323f20657ee0cc8ac1e3d0223.txt -Wall -c -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


