################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Hardware/ADC.c \
../Hardware/Encoder.c \
../Hardware/Motor.c \
../Hardware/OLED.c \
../Hardware/PWM1.c \
../Hardware/PWM2.c \
../Hardware/PWM3.c \
../Hardware/PWM4.c \
../Hardware/UART1.c \
../Hardware/UART2.c 

OBJS += \
./Hardware/ADC.o \
./Hardware/Encoder.o \
./Hardware/Motor.o \
./Hardware/OLED.o \
./Hardware/PWM1.o \
./Hardware/PWM2.o \
./Hardware/PWM3.o \
./Hardware/PWM4.o \
./Hardware/UART1.o \
./Hardware/UART2.o 

C_DEPS += \
./Hardware/ADC.d \
./Hardware/Encoder.d \
./Hardware/Motor.d \
./Hardware/OLED.d \
./Hardware/PWM1.d \
./Hardware/PWM2.d \
./Hardware/PWM3.d \
./Hardware/PWM4.d \
./Hardware/UART1.d \
./Hardware/UART2.d 


# Each subdirectory must supply rules for building sources it contributes
Hardware/%.o Hardware/%.su Hardware/%.cyclo: ../Hardware/%.c Hardware/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"D:/Stm32Project/SideProject/cubeide/car_RTOS/car_RTOS/Hardware" -I"D:/Stm32Project/SideProject/cubeide/car_RTOS/car_RTOS/System" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Hardware

clean-Hardware:
	-$(RM) ./Hardware/ADC.cyclo ./Hardware/ADC.d ./Hardware/ADC.o ./Hardware/ADC.su ./Hardware/Encoder.cyclo ./Hardware/Encoder.d ./Hardware/Encoder.o ./Hardware/Encoder.su ./Hardware/Motor.cyclo ./Hardware/Motor.d ./Hardware/Motor.o ./Hardware/Motor.su ./Hardware/OLED.cyclo ./Hardware/OLED.d ./Hardware/OLED.o ./Hardware/OLED.su ./Hardware/PWM1.cyclo ./Hardware/PWM1.d ./Hardware/PWM1.o ./Hardware/PWM1.su ./Hardware/PWM2.cyclo ./Hardware/PWM2.d ./Hardware/PWM2.o ./Hardware/PWM2.su ./Hardware/PWM3.cyclo ./Hardware/PWM3.d ./Hardware/PWM3.o ./Hardware/PWM3.su ./Hardware/PWM4.cyclo ./Hardware/PWM4.d ./Hardware/PWM4.o ./Hardware/PWM4.su ./Hardware/UART1.cyclo ./Hardware/UART1.d ./Hardware/UART1.o ./Hardware/UART1.su ./Hardware/UART2.cyclo ./Hardware/UART2.d ./Hardware/UART2.o ./Hardware/UART2.su

.PHONY: clean-Hardware

