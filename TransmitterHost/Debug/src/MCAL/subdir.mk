################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MCAL/MDMA_program.c \
../src/MCAL/MEXTI_program.c \
../src/MCAL/MFMI_program.c \
../src/MCAL/MGPIO_program.c \
../src/MCAL/MNVIC_program.c \
../src/MCAL/MRCC_program.c \
../src/MCAL/MSPI_program.c \
../src/MCAL/MSTK_program.c \
../src/MCAL/MUART_program.c 

OBJS += \
./src/MCAL/MDMA_program.o \
./src/MCAL/MEXTI_program.o \
./src/MCAL/MFMI_program.o \
./src/MCAL/MGPIO_program.o \
./src/MCAL/MNVIC_program.o \
./src/MCAL/MRCC_program.o \
./src/MCAL/MSPI_program.o \
./src/MCAL/MSTK_program.o \
./src/MCAL/MUART_program.o 

C_DEPS += \
./src/MCAL/MDMA_program.d \
./src/MCAL/MEXTI_program.d \
./src/MCAL/MFMI_program.d \
./src/MCAL/MGPIO_program.d \
./src/MCAL/MNVIC_program.d \
./src/MCAL/MRCC_program.d \
./src/MCAL/MSPI_program.d \
./src/MCAL/MSTK_program.d \
./src/MCAL/MUART_program.d 


# Each subdirectory must supply rules for building sources it contributes
src/MCAL/%.o: ../src/MCAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


