################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../System/Delay.c \
../System/Timer.c \
../System/pid.c 

OBJS += \
./System/Delay.o \
./System/Timer.o \
./System/pid.o 

C_DEPS += \
./System/Delay.d \
./System/Timer.d \
./System/pid.d 


# Each subdirectory must supply rules for building sources it contributes
System/%.o System/%.su System/%.cyclo: ../System/%.c System/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Stm32Project/SideProject/cubeide/car_RTOS/car_RTOS/Hardware" -I"D:/Stm32Project/SideProject/cubeide/car_RTOS/car_RTOS/System" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-System

clean-System:
	-$(RM) ./System/Delay.cyclo ./System/Delay.d ./System/Delay.o ./System/Delay.su ./System/Timer.cyclo ./System/Timer.d ./System/Timer.o ./System/Timer.su ./System/pid.cyclo ./System/pid.d ./System/pid.o ./System/pid.su

.PHONY: clean-System

