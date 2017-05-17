################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src/utility/twi.c 

C_DEPS += \
./libraries/Wire/src/utility/twi.c.d 

LINK_OBJ += \
./libraries/Wire/src/utility/twi.c.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/Wire/src/utility/twi.c.o: /home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src/utility/twi.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


