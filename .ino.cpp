#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-05-18 20:17:37

#include "Arduino.h"
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Time.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
void setupReseau() ;
void setup() ;
void loop() ;
void readRupteurs() ;
void getOSCMessages() ;
void setupMoteurs() ;
void loopServoAngle() ;
void loopEngrenages() ;
void setupPaupieres() ;
void loopPaupieres() ;
void mockPaupieres() ;
void mockEngrenage() ;
void toggleEngrenage(OSCMessage &msg);
void changeSensEngrenage(OSCMessage &msg);
void changeVitesseEngrenage(OSCMessage &msg);
void changeAngleOeilGauche(OSCMessage &msg);
void changeAngleOeilDroit(OSCMessage &msg);
void changePositionPaupiereGauche0(OSCMessage &msg);
void changePositionPaupiereGauche25(OSCMessage &msg);
void changePositionPaupiereGauche50(OSCMessage &msg);
void changePositionPaupiereGauche75(OSCMessage &msg);
void changePositionPaupiereDroite0(OSCMessage &msg);
void changePositionPaupiereDroite25(OSCMessage &msg);
void changePositionPaupiereDroite50(OSCMessage &msg);
void changePositionPaupiereDroite75(OSCMessage &msg);


#include "a_variables.ino"
#include "b_golem.ino"
#include "c_oscSetter.ino"

#endif
