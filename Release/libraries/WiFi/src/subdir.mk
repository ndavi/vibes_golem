################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFi.cpp \
/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiClient.cpp \
/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiServer.cpp \
/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiUdp.cpp 

LINK_OBJ += \
./libraries/WiFi/src/WiFi.cpp.o \
./libraries/WiFi/src/WiFiClient.cpp.o \
./libraries/WiFi/src/WiFiServer.cpp.o \
./libraries/WiFi/src/WiFiUdp.cpp.o 

CPP_DEPS += \
./libraries/WiFi/src/WiFi.cpp.d \
./libraries/WiFi/src/WiFiClient.cpp.d \
./libraries/WiFi/src/WiFiServer.cpp.d \
./libraries/WiFi/src/WiFiUdp.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/WiFi/src/WiFi.cpp.o: /home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFi.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/OSC" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/WiFi/src/WiFiClient.cpp.o: /home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiClient.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/OSC" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/WiFi/src/WiFiServer.cpp.o: /home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiServer.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/OSC" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/WiFi/src/WiFiUdp.cpp.o: /home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src/WiFiUdp.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/OSC" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


