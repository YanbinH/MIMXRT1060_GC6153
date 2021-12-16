################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/freertos/fsl_lpi2c_freertos.c \
../drivers/freertos/fsl_lpspi_freertos.c \
../drivers/freertos/fsl_lpuart_freertos.c 

OBJS += \
./drivers/freertos/fsl_lpi2c_freertos.o \
./drivers/freertos/fsl_lpspi_freertos.o \
./drivers/freertos/fsl_lpuart_freertos.o 

C_DEPS += \
./drivers/freertos/fsl_lpi2c_freertos.d \
./drivers/freertos/fsl_lpspi_freertos.d \
./drivers/freertos/fsl_lpuart_freertos.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/freertos/%.o: ../drivers/freertos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DSKIP_SYSCLK_INIT -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\board" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\user\devices" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\user\drivers" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\user\tasks" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\source" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\freertos\freertos_kernel\include" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\freertos\template\ARM_CM4F" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\drivers" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\xip" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\drivers\freertos" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\component\serial_manager" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\component\uart" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\utilities" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\component\lists" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\CMSIS" -I"F:\Study\Github\MIMXRT1060_GC6153\MIMXRT1062_GC6153\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


