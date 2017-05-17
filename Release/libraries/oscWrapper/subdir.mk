################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../libraries/oscWrapper/OSCData.cpp \
../libraries/oscWrapper/OSCMessage.cpp \
../libraries/oscWrapper/OscSerial.cpp \
../libraries/oscWrapper/OscUDP.cpp \
../libraries/oscWrapper/SLIPEncodedSerial.cpp 

C_SRCS += \
../libraries/oscWrapper/OSCMatch.c 

C_DEPS += \
./libraries/oscWrapper/OSCMatch.c.d 

LINK_OBJ += \
./libraries/oscWrapper/OSCData.cpp.o \
./libraries/oscWrapper/OSCMatch.c.o \
./libraries/oscWrapper/OSCMessage.cpp.o \
./libraries/oscWrapper/OscSerial.cpp.o \
./libraries/oscWrapper/OscUDP.cpp.o \
./libraries/oscWrapper/SLIPEncodedSerial.cpp.o 

CPP_DEPS += \
./libraries/oscWrapper/OSCData.cpp.d \
./libraries/oscWrapper/OSCMessage.cpp.d \
./libraries/oscWrapper/OscSerial.cpp.d \
./libraries/oscWrapper/OscUDP.cpp.d \
./libraries/oscWrapper/SLIPEncodedSerial.cpp.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/oscWrapper/OSCData.cpp.o: ../libraries/oscWrapper/OSCData.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/oscWrapper" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/oscWrapper/OSCMatch.c.o: ../libraries/oscWrapper/OSCMatch.c
	@echo 'Building file: $<'
	@echo 'Starting C compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-gcc" -c -g -Os -Wall -Wextra -std=gnu11 -ffunction-sections -fdata-sections -flto -fno-fat-lto-objects -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/oscWrapper/OSCMessage.cpp.o: ../libraries/oscWrapper/OSCMessage.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/oscWrapper" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/oscWrapper/OscSerial.cpp.o: ../libraries/oscWrapper/OscSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/oscWrapper" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/oscWrapper/OscUDP.cpp.o: ../libraries/oscWrapper/OscUDP.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/oscWrapper" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '

libraries/oscWrapper/SLIPEncodedSerial.cpp.o: ../libraries/oscWrapper/SLIPEncodedSerial.cpp
	@echo 'Building file: $<'
	@echo 'Starting C++ compile'
	"/home/nico/Documents/sloeber//arduinoPlugin/packages/arduino/tools/avr-gcc/4.9.2-atmel3.5.4-arduino2/bin/avr-g++" -c -g -Os -Wall -Wextra -std=gnu++11 -fpermissive -fno-exceptions -ffunction-sections -fdata-sections -fno-threadsafe-statics -flto -mmcu=atmega328p -DF_CPU=16000000L -DARDUINO=10609 -DARDUINO_AVR_ETHERNET -DARDUINO_ARCH_AVR   -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/cores/arduino" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/oscWrapper" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Time" -I"/home/nico/Documents/sloeber-workspace/golem_vibes/libraries/Adafruit_Motor_Shield" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/variants/ethernet" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Servo/1.1.2/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/SPI/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire" -I"/home/nico/Documents/sloeber/arduinoPlugin/packages/arduino/hardware/avr/1.6.18/libraries/Wire/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/WiFi/1.2.6/src" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2" -I"/home/nico/Documents/sloeber/arduinoPlugin/libraries/Ethernet/1.1.2/src" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -D__IN_ECLIPSE__=1 -x c++ "$<"  -o  "$@"
	@echo 'Finished building: $<'
	@echo ' '


