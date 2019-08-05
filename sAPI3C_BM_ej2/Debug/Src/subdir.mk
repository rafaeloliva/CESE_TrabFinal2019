################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c 

OBJS += \
./Src/main.o 

C_DEPS += \
./Src/main.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_FULL_LL_DRIVER '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F411xE -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/Inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/Drivers/CMSIS/Include" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/lib/sapi3c/abstract_modules/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/lib/sapi3c/base/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/lib/sapi3c/board/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/lib/sapi3c/soc/core/inc" -I"C:/Work_EmbdSTM32/2019/CL3/sAPI3C_BM_ej2/lib/sapi3c/soc/peripherals/inc"  -O3 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


