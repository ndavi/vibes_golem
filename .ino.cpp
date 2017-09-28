#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-09-28 18:44:17

#include "Arduino.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
void setupReseau() ;
void setup() ;
void loop() ;
void receiveUDP() ;
void sendPacket(byte bytes[]) ;
void readRupteurs() ;
void setupMoteurs() ;
void loopEngrenages() ;
void setupPaupieres() ;
void loopPaupieres() ;
unsigned long BtoI(int start, int numofbits, int bits[]);
void changePositionPaupiere(int numMotor, String sens);
void toggleEngrenage(bool run) ;
void changeSensEngrenage(bool avance) ;


#include "a_variables.ino"
#include "b_golem.ino"
#include "c_oscSetter.ino"

#endif
