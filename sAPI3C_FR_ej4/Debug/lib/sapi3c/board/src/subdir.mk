################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/sapi3c/board/src/sapi3c_board.c \
../lib/sapi3c/board/src/stm32f4xx_hal_msp.c \
../lib/sapi3c/board/src/stm32f4xx_hal_timebase_tim.c \
../lib/sapi3c/board/src/stm32f4xx_it.c \
../lib/sapi3c/board/src/syscalls.c \
../lib/sapi3c/board/src/system_stm32f4xx.c 

OBJS += \
./lib/sapi3c/board/src/sapi3c_board.o \
./lib/sapi3c/board/src/stm32f4xx_hal_msp.o \
./lib/sapi3c/board/src/stm32f4xx_hal_timebase_tim.o \
./lib/sapi3c/board/src/stm32f4xx_it.o \
./lib/sapi3c/board/src/syscalls.o \
./lib/sapi3c/board/src/system_stm32f4xx.o 

C_DEPS += \
./lib/sapi3c/board/src/sapi3c_board.d \
./lib/sapi3c/board/src/stm32f4xx_hal_msp.d \
./lib/sapi3c/board/src/stm32f4xx_hal_timebase_tim.d \
./lib/sapi3c/board/src/stm32f4xx_it.d \
./lib/sapi3c/board/src/syscalls.d \
./lib/sapi3c/board/src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
lib/sapi3c/board/src/%.o: ../lib/sapi3c/board/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/Drivers/CMSIS/Include" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/abstract_modules/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/base/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/board/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/soc/core/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/soc/peripherals/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/external_peripherals/ili9341" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_FR_ej4/lib/sapi3c/external_peripherals/inc"  -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


