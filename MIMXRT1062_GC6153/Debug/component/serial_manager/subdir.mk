################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/serial_manager/fsl_component_serial_manager.c \
../component/serial_manager/fsl_component_serial_port_uart.c 

OBJS += \
./component/serial_manager/fsl_component_serial_manager.o \
./component/serial_manager/fsl_component_serial_port_uart.o 

C_DEPS += \
./component/serial_manager/fsl_component_serial_manager.d \
./component/serial_manager/fsl_component_serial_port_uart.d 


# Each subdirectory must supply rules for building sources it contributes
component/serial_manager/%.o: ../component/serial_manager/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DXIP_BOOT_HEADER_DCD_ENABLE=1 -DSKIP_SYSCLK_INIT -DCPU_MIMXRT1062DVL6A -DCPU_MIMXRT1062DVL6A_cm7 -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DSDK_OS_FREE_RTOS -DXIP_EXTERNAL_FLASH=1 -DXIP_BOOT_HEADER_ENABLE=1 -DSERIAL_PORT_TYPE_UART=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\board" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\user\devices" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\user\drivers" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\user\tasks" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\source" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\freertos\freertos_kernel\include" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\freertos\template\ARM_CM4F" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\freertos\freertos_kernel\portable\GCC\ARM_CM4F" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\drivers" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\xip" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\drivers\freertos" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\component\serial_manager" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\component\uart" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\utilities" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\component\lists" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\CMSIS" -I"D:\MIMXRT1060_APP\MIMXRT1062_APP\MIMXRT1062_GC6153\device" -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


