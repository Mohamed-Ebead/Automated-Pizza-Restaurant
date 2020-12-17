################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC_program.c \
../src/GPIO_program.c \
../src/RCC_program.c \
../src/RGB_LED_program.c \
../src/SPI_program.c \
../src/STK_program.c \
../src/System_program.c \
../src/TFT_program.c \
../src/main.c 

OBJS += \
./src/ADC_program.o \
./src/GPIO_program.o \
./src/RCC_program.o \
./src/RGB_LED_program.o \
./src/SPI_program.o \
./src/STK_program.o \
./src/System_program.o \
./src/TFT_program.o \
./src/main.o 

C_DEPS += \
./src/ADC_program.d \
./src/GPIO_program.d \
./src/RCC_program.d \
./src/RGB_LED_program.d \
./src/SPI_program.d \
./src/STK_program.d \
./src/System_program.d \
./src/TFT_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"E:\IMT_ARM\Work_Space\ADC_TFT\include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


