//
// Created by Nicolas David on 11/17/17.
//

#include <SPI.h>
#include <Ethernet.h>
#include <Adafruit_MotorShield.h>

Adafruit_MotorShield shieldMotor = Adafruit_MotorShield();

//++++++++++++paupiere+++++++++++++
Adafruit_DCMotor *moteurEngrenageBas = shieldMotor.getMotor(1);
Adafruit_DCMotor *moteurEngrenageMilieu = shieldMotor.getMotor(2);
Adafruit_DCMotor *moteurEngrenageHaut = shieldMotor.getMotor(3);

Adafruit_DCMotor moteursDC[3] = {*moteurEngrenageBas, *moteurEngrenageMilieu, *moteurEngrenageHaut};

unsigned int localPort = 8888;      // local port to listen for UDP packets

EthernetUDP Udp;

byte mac[] = {
        0xDE, 0xAD, 0xBE, 0xEF, 0xFE,
        0xED}; // you can find this written on the board of some Arduino Ethernets or shields

//the Arduino's IP
IPAddress ip(192, 168, 0, 155);
IPAddress remote;


//Variable OSC
bool activEngrenages[3] = {false, false, false};
bool engrenagesAvance[3] = {false, false, false};

//MARK : Setup functions

void setupReseau() {
    Serial.println("Connexion au reseau");
    Ethernet.begin(mac, ip);
    Udp.begin(localPort);
    // print Arduino's IP
    Serial.println(Ethernet.localIP());
}

void toggleEngrenage(int moteurId, bool run) {
    if (run) {
        activEngrenages[moteurId] = true;
    } else {
        activEngrenages[moteurId] = false;
    }
}

void changeSensEngrenage(int moteurId, bool avance) {
    if (avance) {
        engrenagesAvance[moteurId] = true;
    } else {
        engrenagesAvance[moteurId] = false;
    }

}

void setupMoteursDC() {
    Serial.println("Initialisation des moteursDC");
    for (int i = 0; i < 3; i++) {
        moteursDC[i].setSpeed(255);
    }
    Serial.println("Moteurs DC activés");
}

//MARK: Setup

void setup() {
    Serial.begin(9600);
    Serial.println("Serial setup");
    shieldMotor.begin();
    setupMoteursDC();
    setupReseau();
    //setupLed();
    //testReseau();
}

//MARK: Loop functions

void udpMotorsDC(const int receivedBytes[]) {
    Serial.println("Receive byte");
    if (receivedBytes[0] == 0 && receivedBytes[1] == 0) {
        //Serial.println("Engrenage desactive 1");
        toggleEngrenage(0, false);
    }
    if (receivedBytes[0] == 1) {
        //Serial.println("Engrenage avance 1");
        toggleEngrenage(0, true);
        changeSensEngrenage(0, true);
    }
    if (receivedBytes[1] == 1) {
        //Serial.println("Engrenage recule 1");
        toggleEngrenage(0, true);
        changeSensEngrenage(0, false);
    }
    if (receivedBytes[2] == 0 && receivedBytes[3] == 0) {
        //Serial.println("Engrenage desactive 2");
        toggleEngrenage(1, false);
    }
    if (receivedBytes[2] == 1) {
        //Serial.println("Engrenage avance 2");
        toggleEngrenage(1, true);
        changeSensEngrenage(1, true);
    }
    if (receivedBytes[3] == 1) {
        //Serial.println("Engrenage recule 2");
        toggleEngrenage(1, true);
        changeSensEngrenage(1, false);
    }
    if (receivedBytes[4] == 0 && receivedBytes[5] == 0) {
        //Serial.println("Engrenage desactive 3");
        toggleEngrenage(2, false);
    }
    if (receivedBytes[4] == 1) {
        //Serial.println("Engrenage avance 3");
        toggleEngrenage(2, true);
        changeSensEngrenage(2, true);
    }
    if (receivedBytes[5] == 1) {
        //Serial.println("Engrenage recule 3");
        toggleEngrenage(2, true);
        changeSensEngrenage(2, false);
    }
}

unsigned long BtoI(int start, int numofbits, const int bits[]) {    //binary array to integer conversion
    unsigned long integer = 0;
    unsigned long mask = 1;
    for (int i = numofbits + start - 1; i >= start; i--) {
        if (bits[i]) integer |= mask;
        mask = mask << 1;
    }
    return integer;
}

void receiveUDP() {
    int size;
    if ((size = Udp.parsePacket()) > 0) {
        if (!remote) {
            remote = Udp.remoteIP();
        }
        int receivedBytes[6];
        int byteIterator = 0;
        while (size--) {
            if (byteIterator < 6) {
                receivedBytes[byteIterator] = Udp.read();
                byteIterator++;
            }
        }
        udpMotorsDC(receivedBytes);
    }
}

void loopMotorDC() {
    for (int i = 0; i < 3; i++) {
        if (activEngrenages[i] == true) {
            if (engrenagesAvance[i] == true) {
                moteursDC[i].run(FORWARD);
            } else {
                moteursDC[i].run(BACKWARD);
            }
            //Si engrenage activé
        } else {
            moteursDC[i].run(RELEASE);
        }
    }
}

//MARK: Loop Function

void loop() {
    /*unsigned long loopTime = millis() - startTime; //Calculate the time since last time the cycle was completed
    if (loopTime > 5000) //If time is over 2000 millis, set the startTime to millis so the loop time will be reset to zero
    {
        startTime = millis();
        testReseau();
    }*/

    receiveUDP();
    loopMotorDC();
}
