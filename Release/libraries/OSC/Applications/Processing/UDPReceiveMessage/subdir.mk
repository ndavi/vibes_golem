################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
PDE_SRCS += \
../libraries/OSC/Applications/Processing/UDPReceiveMessage/UDPReceiveMessage.pde 

PDE_DEPS += \
./libraries/OSC/Applications/Processing/UDPReceiveMessage/UDPReceiveMessage.pde.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/OSC/Applications/Processing/UDPReceiveMessage/UDPReceiveMessage.o: ../libraries/OSC/Applications/Processing/UDPReceiveMessage/UDPReceiveMessage.pde
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_UNO_WIFI_DEV_ED -DARDUINO_ARCH_AVR -DESP_CH_UART -DESP_CH_UART_BR=19200  -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/OSC" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/standard" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


