################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/HDAC_Program.c \
../src/HIR_Program.c \
../src/HKPD_Program.c \
../src/HLCD_Program.c \
../src/HLDMX_Program.c \
../src/HS2P_Program.c \
../src/HTFT_Program.c \
../src/MDMA_Program.c \
../src/MEXTI_Config.c \
../src/MEXTI_Program.c \
../src/MGPIO_Program.c \
../src/MNVIC_Program.c \
../src/MRCC_Program.c \
../src/MSPI_Program.c \
../src/MSYSTICK_Program.c \
../src/MUSART_Program.c \
../src/SRTOS_Program.c \
../src/_initialize_hardware.c \
../src/_write.c \
../src/main.c \
../src/stm32f4xx_hal_msp.c 

OBJS += \
./src/HDAC_Program.o \
./src/HIR_Program.o \
./src/HKPD_Program.o \
./src/HLCD_Program.o \
./src/HLDMX_Program.o \
./src/HS2P_Program.o \
./src/HTFT_Program.o \
./src/MDMA_Program.o \
./src/MEXTI_Config.o \
./src/MEXTI_Program.o \
./src/MGPIO_Program.o \
./src/MNVIC_Program.o \
./src/MRCC_Program.o \
./src/MSPI_Program.o \
./src/MSYSTICK_Program.o \
./src/MUSART_Program.o \
./src/SRTOS_Program.o \
./src/_initialize_hardware.o \
./src/_write.o \
./src/main.o \
./src/stm32f4xx_hal_msp.o 

C_DEPS += \
./src/HDAC_Program.d \
./src/HIR_Program.d \
./src/HKPD_Program.d \
./src/HLCD_Program.d \
./src/HLDMX_Program.d \
./src/HS2P_Program.d \
./src/HTFT_Program.d \
./src/MDMA_Program.d \
./src/MEXTI_Config.d \
./src/MEXTI_Program.d \
./src/MGPIO_Program.d \
./src/MNVIC_Program.d \
./src/MRCC_Program.d \
./src/MSPI_Program.d \
./src/MSYSTICK_Program.d \
./src/MUSART_Program.d \
./src/SRTOS_Program.d \
./src/_initialize_hardware.d \
./src/_write.d \
./src/main.d \
./src/stm32f4xx_hal_msp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/stm32f4xx_hal_msp.o: ../src/stm32f4xx_hal_msp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -Wno-missing-prototypes -Wno-missing-declarations -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/stm32f4xx_hal_msp.d" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


