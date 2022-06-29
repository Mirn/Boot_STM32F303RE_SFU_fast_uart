################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/SFU/packet_receiver.c \
../src/SFU/sfu_commands.c 

OBJS += \
./src/SFU/packet_receiver.o \
./src/SFU/sfu_commands.o 

C_DEPS += \
./src/SFU/packet_receiver.d \
./src/SFU/sfu_commands.d 


# Each subdirectory must supply rules for building sources it contributes
src/SFU/%.o: ../src/SFU/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -Wunused -Wuninitialized -Wall -Wextra -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -DUSE_HAL_DRIVER -DSTM32F303xE -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../kiss/inc -I../src/usart_lib -I../src/SFU -I../src -std=gnu11 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


