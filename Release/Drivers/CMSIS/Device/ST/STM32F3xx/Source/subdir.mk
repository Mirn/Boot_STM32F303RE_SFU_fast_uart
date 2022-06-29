################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32F3xx/Source/system_stm32f3xx.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32F3xx/Source/system_stm32f3xx.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32F3xx/Source/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32F3xx/Source/%.o: ../Drivers/CMSIS/Device/ST/STM32F3xx/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -O2 -fmessage-length=0 -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -Wunused -Wuninitialized -Wall -Wextra -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -DUSE_HAL_DRIVER -DSTM32F303xE -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Include -I../kiss/inc -I../src/usart_lib -I../src/SFU -I../src -std=gnu11 -Wbad-function-cast -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


