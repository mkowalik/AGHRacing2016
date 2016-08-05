################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_initialize_hardware.c \
../src/_write.c \
../src/adc.c \
../src/can.c \
../src/gpio.c \
../src/stm32f0xx_hal_msp.c \
../src/stm32f0xx_it.c \
../src/tim.c \
../src/usart.c 

CPP_SRCS += \
../src/main.cpp 

OBJS += \
./src/_initialize_hardware.o \
./src/_write.o \
./src/adc.o \
./src/can.o \
./src/gpio.o \
./src/main.o \
./src/stm32f0xx_hal_msp.o \
./src/stm32f0xx_it.o \
./src/tim.o \
./src/usart.o 

C_DEPS += \
./src/_initialize_hardware.d \
./src/_write.d \
./src/adc.d \
./src/can.d \
./src/gpio.d \
./src/stm32f0xx_hal_msp.d \
./src/stm32f0xx_it.d \
./src/tim.d \
./src/usart.d 

CPP_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -Wall -Wextra  -g -DSTM32F042 -DSTM32F042x6 -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m0 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -flto -Wall -Wextra  -g -DSTM32F042 -DSTM32F042x6 -DUSE_HAL_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f0-hal" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


