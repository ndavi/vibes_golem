//
// Created by Nicolas David on 11/17/17.
//

#include <SPI.h>
#include <Adafruit_MotorShield.h>


Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();

//++++++++++++paupiere+++++++++++++
Adafruit_DCMotor *moteurEngrenageBas = shieldMotor.getMotor(1);
Adafruit_DCMotor *moteurEngrenageMilieu = shieldMotor.getMotor(3);
Adafruit_DCMotor *moteurEngrenageHaut = shieldMotor.getMotor(2);

//MARK : Setup functions

void setupMoteursDC() {
    shieldMotor.begin();
    Serial.println("Initialisation des moteursDC");
    moteurEngrenageBas->setSpeed(255);
    moteurEngrenageHaut->setSpeed(255);
    moteurEngrenageMilieu->setSpeed(255);
    Serial.println("Moteurs DC activés");
}

//MARK: Setup

void setup() {
    Serial.begin(9600);
    Serial.println("Serial setup");
    setupMoteursDC();
}

//MARK: Loop Function

void loop() {
    moteurEngrenageBas->setSpeed(255);
    moteurEngrenageHaut->setSpeed(255);
    moteurEngrenageMilieu->setSpeed(255);
    moteurEngrenageMilieu->run(FORWARD);
    moteurEngrenageHaut->run(FORWARD);
    moteurEngrenageBas->run(FORWARD);
    Serial.print("Moteur avance");
}
