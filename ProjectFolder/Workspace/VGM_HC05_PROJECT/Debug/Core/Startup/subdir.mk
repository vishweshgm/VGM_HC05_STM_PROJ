################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f407vgtx.s 

S_DEPS += \
./Core/Startup/startup_stm32f407vgtx.d 

OBJS += \
./Core/Startup/startup_stm32f407vgtx.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/startup_stm32f407vgtx.o: ../Core/Startup/startup_stm32f407vgtx.s
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -c -I"C:/Users/gmvis/STM32CubeIDE/VGM_HC05_STM_PROJ/VGM_HC05_PROJECT/Drivers/hc05/inc" -x assembler-with-cpp -MMD -MP -MF"Core/Startup/startup_stm32f407vgtx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

