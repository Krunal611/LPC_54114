################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/device/class/usb_device_audio.c \
../usb/device/class/usb_device_ccid.c \
../usb/device/class/usb_device_cdc_acm.c \
../usb/device/class/usb_device_cdc_rndis.c \
../usb/device/class/usb_device_class.c \
../usb/device/class/usb_device_hid.c \
../usb/device/class/usb_device_msc.c \
../usb/device/class/usb_device_msc_ufi.c \
../usb/device/class/usb_device_phdc.c \
../usb/device/class/usb_device_printer.c \
../usb/device/class/usb_device_video.c 

OBJS += \
./usb/device/class/usb_device_audio.o \
./usb/device/class/usb_device_ccid.o \
./usb/device/class/usb_device_cdc_acm.o \
./usb/device/class/usb_device_cdc_rndis.o \
./usb/device/class/usb_device_class.o \
./usb/device/class/usb_device_hid.o \
./usb/device/class/usb_device_msc.o \
./usb/device/class/usb_device_msc_ufi.o \
./usb/device/class/usb_device_phdc.o \
./usb/device/class/usb_device_printer.o \
./usb/device/class/usb_device_video.o 

C_DEPS += \
./usb/device/class/usb_device_audio.d \
./usb/device/class/usb_device_ccid.d \
./usb/device/class/usb_device_cdc_acm.d \
./usb/device/class/usb_device_cdc_rndis.d \
./usb/device/class/usb_device_class.d \
./usb/device/class/usb_device_hid.d \
./usb/device/class/usb_device_msc.d \
./usb/device/class/usb_device_msc_ufi.d \
./usb/device/class/usb_device_phdc.d \
./usb/device/class/usb_device_printer.d \
./usb/device/class/usb_device_video.d 


# Each subdirectory must supply rules for building sources it contributes
usb/device/class/%.o: ../usb/device/class/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__LPC5411X__ -DCORE_M4 -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -DCPU_LPC54114J256BD64 -DCPU_LPC54114J256BD64_cm4 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -D__MULTICORE_MASTER -I../board -I../source -I../ -I../drivers -I../CMSIS -I../device -I../component/serial_manager -I../component/uart -I../utilities -I../usb/include -I../usb/phy -I../osa -I../usb/device/class -I../usb/device/source -I../usb/device/include -I../usb/device/source/ehci -I../usb/device/source/khci -I../usb/device/source/lpcip3511 -I../source/generated -I../usb/host/class -I../usb/host -I../startup -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


