################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AHexParser_prg.c \
../src/H7SEG_program.c \
../src/HDAC_program.c \
../src/HIR_program.c \
../src/HLEDMATRIX_program.c \
../src/HSTP_program.c \
../src/HTFT_program.c \
../src/MDMA_program.c \
../src/MEXTI_program.c \
../src/MFMI_program.c \
../src/MGPIO_program.c \
../src/MNVIC_program.c \
../src/MRCC_program.c \
../src/MSPI_program.c \
../src/MSTK_program.c \
../src/MUART_program.c \
../src/OS_program.c \
../src/Reciver_main.c \
../src/main.c 

OBJS += \
./src/AHexParser_prg.o \
./src/H7SEG_program.o \
./src/HDAC_program.o \
./src/HIR_program.o \
./src/HLEDMATRIX_program.o \
./src/HSTP_program.o \
./src/HTFT_program.o \
./src/MDMA_program.o \
./src/MEXTI_program.o \
./src/MFMI_program.o \
./src/MGPIO_program.o \
./src/MNVIC_program.o \
./src/MRCC_program.o \
./src/MSPI_program.o \
./src/MSTK_program.o \
./src/MUART_program.o \
./src/OS_program.o \
./src/Reciver_main.o \
./src/main.o 

C_DEPS += \
./src/AHexParser_prg.d \
./src/H7SEG_program.d \
./src/HDAC_program.d \
./src/HIR_program.d \
./src/HLEDMATRIX_program.d \
./src/HSTP_program.d \
./src/HTFT_program.d \
./src/MDMA_program.d \
./src/MEXTI_program.d \
./src/MFMI_program.d \
./src/MGPIO_program.d \
./src/MNVIC_program.d \
./src/MRCC_program.d \
./src/MSPI_program.d \
./src/MSTK_program.d \
./src/MUART_program.d \
./src/OS_program.d \
./src/Reciver_main.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F401xC -DUSE_HAL_DRIVER -DHSE_VALUE=16000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f4-hal" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


