################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/bsp_driver_sd.c \
../Application/User/current_data_provider.c \
../Application/User/dashboard.c \
../Application/User/data_snapshot_maker.c \
../Application/User/ecumaster.c \
../Application/User/error_logger.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/fatfs.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/freertos.c \
../Application/User/itoa.c \
../Application/User/logged_data_types.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/main.c \
../Application/User/sd_card_saver.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_hal_msp.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_hal_timebase_TIM.c \
C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_it.c \
../Application/User/telemetry.c \
../Application/User/uart_wrapper.c 

OBJS += \
./Application/User/bsp_driver_sd.o \
./Application/User/current_data_provider.o \
./Application/User/dashboard.o \
./Application/User/data_snapshot_maker.o \
./Application/User/ecumaster.o \
./Application/User/error_logger.o \
./Application/User/fatfs.o \
./Application/User/freertos.o \
./Application/User/itoa.o \
./Application/User/logged_data_types.o \
./Application/User/main.o \
./Application/User/sd_card_saver.o \
./Application/User/stm32f4xx_hal_msp.o \
./Application/User/stm32f4xx_hal_timebase_TIM.o \
./Application/User/stm32f4xx_it.o \
./Application/User/telemetry.o \
./Application/User/uart_wrapper.o 

C_DEPS += \
./Application/User/bsp_driver_sd.d \
./Application/User/current_data_provider.d \
./Application/User/dashboard.d \
./Application/User/data_snapshot_maker.d \
./Application/User/ecumaster.d \
./Application/User/error_logger.d \
./Application/User/fatfs.d \
./Application/User/freertos.d \
./Application/User/itoa.d \
./Application/User/logged_data_types.d \
./Application/User/main.d \
./Application/User/sd_card_saver.d \
./Application/User/stm32f4xx_hal_msp.d \
./Application/User/stm32f4xx_hal_timebase_TIM.d \
./Application/User/stm32f4xx_it.d \
./Application/User/telemetry.d \
./Application/User/uart_wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/bsp_driver_sd.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/bsp_driver_sd.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/%.o: ../Application/User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/fatfs.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/fatfs.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/freertos.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/freertos.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/main.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_msp.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_hal_timebase_TIM.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_hal_timebase_TIM.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Application/User/stm32f4xx_it.o: C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/Src/stm32f4xx_it.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo %cd%
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -std=c99 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F407xx -I../../../Inc -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User/SH1106" -I"C:/Users/kowalik/Desktop/AGHRacingLoggerGitOK/AGHRacingLogger/SW4STM32/AGHRacingLogger/Application/User" -I../../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../../Middlewares/Third_Party/FatFs/src -I../../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../../../Drivers/CMSIS/Include -I../../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../../Inc -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


