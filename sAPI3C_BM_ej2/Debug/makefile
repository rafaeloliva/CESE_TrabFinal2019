################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include startup/subdir.mk
-include lib/sapi3c/soc/peripherals/src/subdir.mk
-include lib/sapi3c/soc/core/src/subdir.mk
-include lib/sapi3c/board/src/subdir.mk
-include lib/sapi3c/base/src/subdir.mk
-include lib/sapi3c/abstract_modules/src/subdir.mk
-include Src/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: sAPI3C_BM_ej2.elf

# Tool invocations
sAPI3C_BM_ej2.elf: $(OBJS) $(USER_OBJS) ../STM32F411RETx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -specs=nosys.specs -specs=nano.specs -T"../STM32F411RETx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "sAPI3C_BM_ej2.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "sAPI3C_BM_ej2.elf" "sAPI3C_BM_ej2.hex"
	arm-none-eabi-size "sAPI3C_BM_ej2.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
