#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-05-13 21:11:50

#include "Arduino.h"
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
void toggleEngrenage(OSCMessage &msg, int addrOffset );
void changeSensEngrenage(OSCMessage &msg, int addrOffset );
void changeVitesseEngrenage(OSCMessage &msg, int addrOffset );
void changeAngleOeilGauche(OSCMessage &msg, int addrOffset );
void changeAngleOeilDroit(OSCMessage &msg, int addrOffset );
void setupReseau() ;
void setup() ;
void loop() ;
void getOSCMessages() ;
void setupMoteurs() ;
void loopMoteurs() ;

#include "golem_vibes.ino"


#endif
