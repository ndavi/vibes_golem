#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2017-05-17 23:30:58

#include "Arduino.h"
#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Time.h>
#include <OscUDP.h>
void setupReseau() ;
void setup() ;
void loop() ;
void readRupteurs() ;
void getOSCMessages() ;
void oscEvent(OscMessage &m) ;
void setupMoteurs() ;
void loopServoAngle() ;
void loopEngrenages() ;
void setupPaupieres() ;
void loopPaupieres() ;
void mockPaupieres() ;
void mockEngrenage() ;
void toggleEngrenage(OscMessage &msg);
void toggleEngrenageTest(OscMessage &msg, int test);
void changeSensEngrenage(OscMessage &msg);
void changeVitaesseEngrenage(OscMessage &msg);
void changeAngleOeilGauche(OscMessage &msg);
void changeAngleOeilDroit(OscMessage &msg);
void changePositionPaupiereGauche(OscMessage &msg);
void changePositionPaupiereDroite(OscMessage &msg);


#include "a_variables.ino"
#include "b_golem.ino"
#include "c_oscSetter.ino"

#endif
